/*
 * BetweennessCentrality.hpp
 *
 *  Created on: Feb 26, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__ALGORITHMS__CENTRALITY__BETWEENNESS_CENTRALITY_HPP
#define EGOA__ALGORITHMS__CENTRALITY__BETWEENNESS_CENTRALITY_HPP

#ifdef OPENMP_AVAILABLE
    #include <omp.h>
#endif // OPENMP_AVAILABLE

#include "Algorithms/PathFinding/DominatingThetaPath.hpp"
#include "IO/Statistics/DtpRuntimeCollection.hpp"

namespace egoa {

enum class CentralityCounter {
    counterAtEdges    = 0,
    counterAtVertices = 1
};

/**
 * @brief      Class for betweenness centrality.
 * @details    This algorithm measures the centrality of a graph based on a
 *     path finding algorithm, e.g., the shortest path, or dominating theta
 *     path. The @f$\dtp@f$ betweenness centrality
 *     @f$c_{\sbc}\colon\edges\to\posreals@f$ is defined by
 *     @f[
 *      c_{\sbc} := \frac{1}{m_B}\sum_{\source\in\vertices}\sum_{\sink\in\vertices\setminus\{\source\}} \frac{\sigma_{\dtp}(\source,\sink,\edge)}{\sigma_{\dtp}(\source,\sink)},
 *     @f]
 *     where @f$\sigma_{\dtp}(\source,\sink,\edge)@f$ is the number of
 *     @f$\dtp{s}@f$ between @f$\source@f$ and @f$\sink@f$ that use the edge
 *     @f$\edge@f$, @f$\sigma_{\dtp}(\source,\sink)@f$ is the total number of
 *     @f$\dtp{\text{s}}@f$ from the source @f$\source@f$ to a sink
 *     @f$\sink@f$, and @f$m_B = |\vertices|\cdot(|\vertices|-1)@f$ is a
 *     normalizing constant.
 *
 * @pre        The template parameter used for GraphType should have an
 *     interface similar to StaticGraph or DynamicGraph. However, the minimum
 *     requirements on the graph type are
 *     - @p for_all_vertex_identifiers<IsParallel>, and
 *     - see the minimum requirement of the PathFindingAlgorithm, e.g.,
 *       DominatingThetaPath.
 *
 * @tparam     GraphType              The graph should at least provide the
 *     same interface as the StaticGraph.
 * @tparam     PathFindingAlgorithm   The path finding algorithm that is used
 *     within the betweenness centrality algorithm such as DTP.
 * @tparam     MeasurementCollection  The collection used for the measurements
 *     such as IO::DtpRuntimeCollection.
 * @tparam     CentralityCounterType  The centrality counter decides whether
 *     to count edges or vertices.
 *
 * @see StaticGraph
 * @see DominatingThetaPath
 * @see IO::DtpRuntimeCollection
 * @see CentralityCounter
 */
template< typename GraphType                        = StaticGraph< Vertices::ElectricalProperties<Vertices::IeeeBusType>
                                                                 , Edges::ElectricalProperties >
        , typename PathFindingAlgorithm             = DominatingThetaPath<GraphType>
        , typename MeasurementCollection            = IO::DtpRuntimeCollection
        , CentralityCounter CentralityCounterType   = CentralityCounter::counterAtEdges > /**< Distinguish between counting edges or vertices. */
class BetweennessCentrality {
    public:
#pragma mark TYPE_ALIASING
        // Graph specific types
        using TGraph                 = GraphType;                   /**< The graph type.  */
        using TVertex                = typename TGraph::TVertex;    /**< The vertex type. */
        using TVertexId              = typename TGraph::TVertexId;  /**< The vertex identifier type. */
        using TEdge                  = typename TGraph::TEdge;      /**< The edge type. */
        using TEdgeId                = typename TGraph::TEdgeId;    /**< The edge identifier type. */

        using TAlgorithm             = PathFindingAlgorithm;        /**< The path finding algorithm in use for the Betweenness Centrality such as DTP. */
        using TMeasurementCollection = MeasurementCollection;       /**< The collection used for the measurements such as IO::DtpRuntimeCollection. */
        using TMeasurementRow        = typename TMeasurementCollection::TRow; /**< The row type of the collection used for the measurements. */

    protected:
#ifdef OPENMP_AVAILABLE
        using TAlgoHandling          = std::vector<TAlgorithm>;
        using TNumberOfPaths         = std::vector<std::vector<Types::count>>;
        using TRelativeNumberOfPaths = std::vector<std::vector<Types::real>>;
#else
        using TAlgoHandling          = TAlgorithm;
        using TNumberOfPaths         = std::vector<Types::count>;
        using TRelativeNumberOfPaths = std::vector<Types::real>;
#endif
    public:
        ///@name Constructors and Destructor
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS

            /**
             * @brief      Constructs the betweenness centrality object.
             *
             * @param      graph  The const graph.
             */
            BetweennessCentrality ( TGraph const & graph )
            : countersSize_(0)
            , graph_( graph )
#if defined(OPENMP_AVAILABLE)
            , algo_( omp_get_max_threads(), TAlgorithm( graph_ ) )
#else
            , algo_( graph_ )
#endif
            {}

            /**
             * @brief      Destroys the object.
             */
            ~BetweennessCentrality () {}

        ///@}

        ///@name Execute the Betweenness Centrality Algorithm
        ///@{
#pragma mark EXECUTE_ALGORITHM

            /**
             * @brief      Run the betweenness centrality.
             * @details    If OpenMP is available this method will run in
             *     parallel. Note that standard container are thread safe
             *     while writing writing on their own dedicated object.
             *     However, this is not true when the object is a boolean. For
             *     more information see <a
             *     href="https://en.cppreference.com/w/cpp/container">
             *     https://en.cppreference.com/w/cpp/container </a>.
             */
            inline void Run ()
            {
                TNumberOfPaths         numberOfPaths;
                TRelativeNumberOfPaths relativeNumberOfPaths;

                Clear ( numberOfPaths, relativeNumberOfPaths );

                graph_.template for_all_vertex_identifiers<ExecutionPolicy::sequential> ( [   this
                                                                   , & numberOfPaths
                                                                   , & relativeNumberOfPaths ] ( TVertexId vertexId )
                {
#ifdef OPENMP_AVAILABLE
                    Algorithm()[omp_get_thread_num()].Clear();
                    Algorithm()[omp_get_thread_num()].Source( vertexId );
                    Algorithm()[omp_get_thread_num()].Run();
                    Algorithm()[omp_get_thread_num()].NumberOfLabels();
                    TotalNumberOfPaths( numberOfPaths, relativeNumberOfPaths );
#ifdef EGOA_ENABLE_STATISTIC_BETWEENNESS_CENTRALITY // COLLECT RUNTIME INFORMATION
                    #pragma omp critical
                    { // More information concerning standard container
                      // concurrency under "Thread safety":
                      // https://en.cppreference.com/w/cpp/container
                        Collection() += Algorithm()[omp_get_thread_num()].Statistic();
                    }
#endif // EGOA_ENABLE_STATISTIC_BETWEENNESS_CENTRALITY

// ################################################################################
// ################################################################################
// ################################################################################

#else // OPENMP IS NOT AVAILABLE

                    Algorithm().Clear();
                    Algorithm().Source ( vertexId );
                    Algorithm().Run();
                    TotalNumberOfPaths ( numberOfPaths, relativeNumberOfPaths );

#ifdef EGOA_ENABLE_STATISTIC_BETWEENNESS_CENTRALITY
                    Collection() += Algorithm().Statistic();
#endif // EGOA_ENABLE_STATISTIC_BETWEENNESS_CENTRALITY
#endif // OPENMP_AVAILABLE
                });
                JoinThreadBasedResults ( numberOfPaths
                                       , relativeNumberOfPaths
                                       , 1 / static_cast<Types::real>( graph_.NumberOfVertices() * ( graph_.NumberOfVertices() - 1 ) ) );
            }
        ///@}

        ///@name Getter and Setter
        ///@{
#pragma mark GETTER_AND_SETTER

            /**
             * @brief      Getter for the total relative number of paths per edge.
             *
             * @return     The total relative number of paths per edge.
             */
            inline std::vector<Types::real> const & TotalRelativeNumberOfPaths () const
            {
                USAGE_ASSERT ( totalRelativeNumberOfPaths_.size() == countersSize_ );
                return totalRelativeNumberOfPaths_;
            }

            /**
             * @brief      Getter for the total number of paths per edge.
             *
             * @return     The total number of paths per edge.
             */
            inline std::vector<Types::count> const & TotalNumberOfPaths () const
            {
                USAGE_ASSERT ( totalNumberOfPaths_.size() == countersSize_ );
                return totalNumberOfPaths_;
            }

            /**
             * @brief      Setter for the algorithm.
             *
             * @return     The algorithm.
             */
            inline TAlgoHandling & Algorithm ()
            {
                return algo_;
            }

            /**
             * @brief      Getter for the algorithm.
             *
             * @return     The algorithm.
             */
            inline TAlgoHandling const & Algorithm () const
            {
                return algo_;
            }

            /**
             * @brief      Getter for the measurement collection.
             *
             * @return     A vector of measurements.
             */
            inline TMeasurementCollection const & Collection () const
            {
                return collection_;
            }

            /**
             * @brief      Setter for the measurement collection.
             *
             * @return     A vector of measurements.
             */
            inline TMeasurementCollection & Collection ()
            {
                return collection_;
            }
        ///@}

        ///@name Modifier
        ///@{
#pragma mark MODIFIER

            /**
             * @brief      Clears the measurement collection.
             */
            inline void Clear ()
            {
                collection_.Clear();

                if ( CentralityCounterType == CentralityCounter::counterAtEdges )
                {
                    countersSize_ = graph_.NumberOfEdges();
                } else {
                    countersSize_ = graph_.NumberOfVertices();
                }

                totalRelativeNumberOfPaths_.assign ( countersSize_, 0.0 );
                totalNumberOfPaths_.assign         ( countersSize_, 0   );
            }
        ///@}

    protected:

        ///@name Total Number of Paths
        ///@{
#pragma mark TOTAL_NUMBER_OF_PATHS

            /**
             * @brief      Join the thread based result from OpenMP.
             * @details    This method abstracts the usage of OpenMP.
             *
             * @param      numberOfPaths          The number of paths.
             * @param      relativeNumberOfPaths  The relative number of paths.
             * @param      m_BNormalization       The normalization factor,
             *     e.g., for the @f$\SBC@f$ @f$\sbc@f$ the normalization
             *     factor is defined by @f$m_B = |V|\cdot (|V|-1)@f$.
             */
            inline void JoinThreadBasedResults ( TNumberOfPaths         const & numberOfPaths
                                               , TRelativeNumberOfPaths const & relativeNumberOfPaths
                                               , Types::real            const & m_BNormalization      )
            {
#ifdef OPENMP_AVAILABLE
                ESSENTIAL_ASSERT ( totalRelativeNumberOfPaths_.size() == countersSize_ );
                ESSENTIAL_ASSERT ( relativeNumberOfPaths.size()       == omp_get_max_threads () );
                ESSENTIAL_ASSERT ( relativeNumberOfPaths[0].size()    == countersSize_ );
                ESSENTIAL_ASSERT ( totalNumberOfPaths_.size()         == countersSize_ );
                ESSENTIAL_ASSERT ( numberOfPaths.size()               == omp_get_max_threads () );
                ESSENTIAL_ASSERT ( numberOfPaths[0].size()            == countersSize_ );

                for ( Types::count counterThreads = 0
                    ; counterThreads < omp_get_max_threads()
                    ; ++counterThreads )
                {
                    for ( Types::count counterEdgesOrVertices = 0
                        ; counterEdgesOrVertices < countersSize_
                        ; ++counterEdgesOrVertices )
                    {
                        // Total relative number of paths per edge
                        totalRelativeNumberOfPaths_[counterEdgesOrVertices]    += relativeNumberOfPaths[counterThreads][counterEdgesOrVertices];
                        totalNumberOfPaths_[counterEdgesOrVertices]            += numberOfPaths[counterThreads][counterEdgesOrVertices];
                    }
                }

                std::transform ( totalRelativeNumberOfPaths_.begin()
                               , totalRelativeNumberOfPaths_.end()
                               , totalRelativeNumberOfPaths_.begin()
                               , std::bind( std::multiplies<Types::real>(), std::placeholders::_1, m_BNormalization ) );

#else // OPENMP IS NOT AVAILABLE
                ESSENTIAL_ASSERT ( totalRelativeNumberOfPaths_.size() == countersSize_ );
                ESSENTIAL_ASSERT ( relativeNumberOfPaths.size()       == countersSize_ );
                ESSENTIAL_ASSERT ( totalNumberOfPaths_.size()         == countersSize_ );
                ESSENTIAL_ASSERT ( numberOfPaths.size()               == countersSize_ );

                // Total relative number of paths per edge
                totalRelativeNumberOfPaths_ = relativeNumberOfPaths;
                totalNumberOfPaths_         = numberOfPaths;

                std::transform ( totalRelativeNumberOfPaths_.begin()
                               , totalRelativeNumberOfPaths_.end()
                               , totalRelativeNumberOfPaths_.begin()
                               , std::bind( std::multiplies<Types::real>(), std::placeholders::_1, m_BNormalization ) );
#endif
            }

            /**
             * @brief      Total number of paths.
             * @details    This method abstracts the usage of the
             *     CentralityCounter and OpenMP.
             *
             * @param      numberOfPaths          The number of paths.
             * @param      relativeNumberOfPaths  The relative number of paths.
             */
            inline void TotalNumberOfPaths ( TNumberOfPaths         & numberOfPaths
                                           , TRelativeNumberOfPaths & relativeNumberOfPaths )
            {
#ifdef OPENMP_AVAILABLE
                if ( CentralityCounterType == CentralityCounter::counterAtEdges )
                {
                    Algorithm()[ omp_get_thread_num() ].TotalNumberOfPathsThroughEdge ( numberOfPaths[ omp_get_thread_num() ]
                                                                                      , relativeNumberOfPaths[ omp_get_thread_num() ] );
                } else {
                    Algorithm()[ omp_get_thread_num() ].TotalNumberOfPathsThroughVertex ( numberOfPaths[ omp_get_thread_num() ]
                                                                                        , relativeNumberOfPaths[ omp_get_thread_num() ] );
                }
#else
                if ( CentralityCounterType == CentralityCounter::counterAtEdges )
                {
                    Algorithm().TotalNumberOfPathsThroughEdge   ( numberOfPaths, relativeNumberOfPaths );
                } else {
                    Algorithm().TotalNumberOfPathsThroughVertex ( numberOfPaths, relativeNumberOfPaths );
                }
#endif
            }
        ///@}

        ///@name Protected Modifiers
        ///@{
#pragma mark PROTECTED_MODIFIERS

            /**
             * @brief      Clear all.
             *
             * @param      numberOfPaths          The number of paths.
             * @param      relativeNumberOfPaths  The relative number of paths.
             */
            inline void Clear ( TNumberOfPaths         & numberOfPaths
                              , TRelativeNumberOfPaths & relativeNumberOfPaths )
            {
                Clear();
#ifdef OPENMP_AVAILABLE
                numberOfPaths.assign         ( omp_get_max_threads(), std::vector<Types::count> ( countersSize_, 0   ) );
                relativeNumberOfPaths.assign ( omp_get_max_threads(), std::vector<Types::real>  ( countersSize_, 0.0 ) );
#else
                numberOfPaths.assign         ( countersSize_, 0   );
                relativeNumberOfPaths.assign ( countersSize_, 0.0 );
#endif
            }
        ///@}

#pragma mark MEMBERS
    private:
        Types::count              countersSize_;    /**< */
        TGraph            const & graph_;           /**< The graph @f$\graph = (\vertices,\edges)@f$ on which the DTP is calculated. */
        TAlgoHandling             algo_;            /**< Multiple path finding algorithm are used for the parallelization. */
        TMeasurementCollection    collection_;      /**< The collection of measurements. */

        std::vector<Types::real>  totalRelativeNumberOfPaths_;   /**< */
        std::vector<Types::count> totalNumberOfPaths_;           /**< */
};

} // egoa

#endif // EGOA__ALGORITHMS__CENTRALITY__BETWEENNESS_CENTRALITY_HPP

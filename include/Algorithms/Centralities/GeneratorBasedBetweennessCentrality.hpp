/*
 * GeneratorBasedBetweennessCentrality.hpp
 *
 *  Created on: Feb 26, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__ALGORITHMS__CENTRALITY__GENERATOR_BASED__BETWEENNESS_CENTRALITY_HPP
#define EGOA__ALGORITHMS__CENTRALITY__GENERATOR_BASED__BETWEENNESS_CENTRALITY_HPP

#ifdef OPENMP_AVAILABLE
    #include <omp.h>
#endif // OPENMP_AVAILABLE

#include "Algorithms/PathFinding/DominatingThetaPath.hpp"
#include "Algorithms/Centralities/BetweennessCentrality.hpp"
#include "IO/Statistics/DtpRuntimeCollection.hpp"

namespace egoa {

/**
 * @brief      Class for the generator-based betweenness centrality.
 * @details    This algorithm measures the centrality of a graph based on a
 *     path finding algorithm, e.g., the shortest path, or dominating theta
 *     path. The switching centrality
 *     @f$c_{\scu}\colon\edges\to\posreals@f$ is defined by
 *     @f[
 *      c_{\scu} := \frac{1}{m_B}\sum_{\source\in\generators}\sum_{\sink\in\consumers} \frac{\omega_{\dtp}(\source,\sink,\edge)}{\omega_{\dtp}(\source,\sink)},
 *     @f]
 *     where @f$\omega_{\dtp}(\source,\sink,\edge)@f$ is the number of
 *     @f$\dtp@f$-paths between @f$\source@f$ and @f$\sink@f$ that use the edge
 *     @f$\edge@f$, @f$\omega_{\dtp}(\source,\sink)@f$ is the total number of
 *     $f$\dtp@f$-paths from the source @f$\source@f$ to a sink
 *     @f$\sink@f$, and @f$m_B = |\generators|\cdot|\consumers|@f$ is a
 *     normalizing constant.
 *
 * @pre        The template parameter used for NetworkType should have an
 *     interface similar to the PowerGrid. However, the minimum
 *     requirements on the network type are
 *     - for_all_generator_identifiers<IsParallel>, and
 *     - for the included graph see the minimum requirement of the
 *       PathFindingAlgorithm, e.g., DominatingThetaPath.
 *
 * @tparam     NetworkType            The network should provide a similar
 *     interface as the PowerGrid.
 * @tparam     PathFindingAlgorithm   The path finding algorithm that is used
 *     within the betweenness centrality algorithm such as DominatingThetaPath.
 * @tparam     MeasurementCollection  The collection used for the measurements
 *     such as IO::DtpRuntimeCollection.
 * @tparam     CentralityCounterType  The centrality counter decides whether
 *     to count edges or vertices.
 *
 * @see BetweennessCentrality
 * @see PowerGrid
 * @see DominatingThetaPath
 * @see IO::DtpRuntimeCollection
 * @see CentralityCounter
 */
template< typename NetworkType                      = PowerGrid< StaticGraph< Vertices::ElectricalProperties<Vertices::IeeeBusType>
                                                                            , Edges::ElectricalProperties >
                                                               , Vertices::GeneratorProperties<>
                                                               , Vertices::LoadProperties<Vertices::IeeeBusType> >
        , typename PathFindingAlgorithm             = DominatingThetaPath<typename NetworkType::TGraph>
        , typename MeasurementCollection            = IO::DtpRuntimeCollection
        , CentralityCounter CentralityCounterType   = CentralityCounter::counterAtEdges > /**< Distinguish between counting edges or vertices. */
class GeneratorBasedBetweennessCentrality final : public BetweennessCentrality < typename NetworkType::TGraph
                                                                               , PathFindingAlgorithm
                                                                               , MeasurementCollection
                                                                               , CentralityCounterType >
{
    public:
#pragma mark TYPE_ALIASING
        // Graph specific types
        using TNetwork               = NetworkType;
        using TBetweennessCentrality = BetweennessCentrality < typename TNetwork::TGraph
                                                             , PathFindingAlgorithm
                                                             , MeasurementCollection
                                                             , CentralityCounterType >;
        using TGeneratorId           = Types::generatorId;
    private:
        using typename TBetweennessCentrality::TNumberOfPaths;
        using typename TBetweennessCentrality::TRelativeNumberOfPaths;
    public:
        ///@name Constructors and Destructor
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS
            GeneratorBasedBetweennessCentrality ( TNetwork const & network )
            : TBetweennessCentrality( network.Graph() )
            , network_( network )
            {}

            /**
             * @brief      Destroys the object.
             */
            ~GeneratorBasedBetweennessCentrality () {}

        ///@}

        ///@name Execute the Betweenness Centrality Algorithm
        ///@{
#pragma mark EXECUTE_ALGORITHM

            /**
             * @brief      Run the generator-based betweenness centrality.
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

                this->Clear ( numberOfPaths, relativeNumberOfPaths );

                network_.template for_all_vertex_identifiers_with_generator<ExecutionPolicy::parallel> ( [
                    this
                    , & numberOfPaths
                    , & relativeNumberOfPaths ] ( TGeneratorId vertexId )
                {
#ifdef OPENMP_AVAILABLE
                    this->Algorithm()[omp_get_thread_num()].Clear();
                    this->Algorithm()[omp_get_thread_num()].Source( vertexId );
                    this->Algorithm()[omp_get_thread_num()].Run();
                    this->Algorithm()[omp_get_thread_num()].NumberOfLabels();
                    this->TotalNumberOfPaths( numberOfPaths, relativeNumberOfPaths );

#ifdef EGOA_ENABLE_STATISTIC_BETWEENNESS_CENTRALITY // COLLECT RUNTIME INFORMATION
                    #pragma omp critical
                    { // More information concerning standard container
                      // concurrency under "Thread safety":
                      // https://en.cppreference.com/w/cpp/container
                        this->Algorithm()[omp_get_thread_num()].Statistic().NumberOfGenerators  = network_.NumberOfGenerators();
                        this->Algorithm()[omp_get_thread_num()].Statistic().NumberOfLoads       = network_.NumberOfLoads();
                        this->Collection() += this->Algorithm()[omp_get_thread_num()].Statistic();
                    }
#endif // EGOA_ENABLE_STATISTIC_BETWEENNESS_CENTRALITY

// ################################################################################
// ################################################################################
// ################################################################################

#else // OPENMP IS NOT AVAILABLE

                    this->Algorithm().Clear();
                    this->Algorithm().Source ( vertexId );
                    this->Algorithm().Run();
                    this->TotalNumberOfPaths ( numberOfPaths, relativeNumberOfPaths );

#ifdef EGOA_ENABLE_STATISTIC_BETWEENNESS_CENTRALITY
                    this->Collection() += this->Algorithm().Statistic();
#endif // EGOA_ENABLE_STATISTIC_BETWEENNESS_CENTRALITY
#endif // OPENMP_AVAILABLE
                });
                this->JoinThreadBasedResults ( numberOfPaths
                                             , relativeNumberOfPaths
                                             , 1 / static_cast<Types::real>( network_.NumberOfGenerators() * network_.NumberOfLoads() ) );
            }
        ///@}

#pragma mark MEMBERS
    private:
        TNetwork          const & network_;           /**< The network @f$\network = (\graph = (\vertices,\edges),\generators,\consumers, \capacity, \susceptance, \dots )@f$ on which the generator-based betweenness centrality is calculated. */
};

} // egoa

#endif // EGOA__ALGORITHMS__CENTRALITY__GENERATOR_BASED__BETWEENNESS_CENTRALITY_HPP

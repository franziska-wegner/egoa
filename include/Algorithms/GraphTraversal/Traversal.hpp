/*
 * Traversal.hpp
 *
 *  Created on: Feb 18, 2019
 *      Author: Franziska Wegner
 */
#ifndef EGOA__ALGORITHMS__GRAPH_TRAVERSAL__TRAVERSAL__HPP
#define EGOA__ALGORITHMS__GRAPH_TRAVERSAL__TRAVERSAL__HPP

#include <vector>

#include "Auxiliary/Constants.hpp"
#include "Auxiliary/ExecutionPolicy.hpp"

#include "Exceptions/Assertions.hpp"

namespace egoa{

namespace internal {

template< typename GraphType, bool IsDirected >
class GraphTypeLoopDifferentiation;

} // namespace internal

/**
 * @brief      Interface for graph traversal.
 *
 * @tparam     GraphType   GraphType  The graph should at least provide the same interface
 *     as the StaticGraph().
 * @tparam     IsDirected  If @p true the graph is treated as a directed graph,
 *     if @p false the graph is treated as an undirected graph.
 */
template< typename GraphType,
          bool IsDirected    = false >
class Traversal {
    public:
        using TGraph    = GraphType;
        using TVertexId = typename GraphType::TVertexId;

        ///@name Constructors and destructor
        ///@{
#pragma mark CONSTRUCTOR_AND_DESTRUCTOR

            /**
             * @brief      Constructs a new instance.
             *
             * @param      graph   The graph
             * @param[in]  source  The source
             */
            Traversal ( TGraph const & graph, TVertexId source )
            : graph_    ( graph  )
            , source_   ( source )
            , visited_  ( std::vector<bool>( graph.NumberOfVertices(), false ) )
            , processed_( std::vector<bool>( graph.NumberOfVertices(), false ) )
            , parent_   ( std::vector<TVertexId>( graph.NumberOfVertices(), Const::NONE ) ) {}

            virtual ~Traversal() {}
        ///@}

#pragma mark GETTER_AND_SETTER
        /**
         * @brief      Getter and setter for the source vertex.
         *
         * @return     The source's identifier.
         */
        ///@{
            inline TVertexId   Source() const { return source_; }
            inline TVertexId & Source()       { return source_; }
        ///@}

#pragma mark RESULT_EXTRACTION
        virtual inline void Result ( std::vector<TVertexId> parent )
        {
            // @todo Implement, see MST
            throw std::runtime_error("Not implemented yet!");
        }

    protected:

        ///@name Vertex visited methods
        ///@{
#pragma mark VERTEX_VISITED_METHODS
            /**
             * @brief      Sets the vertex at @p vertexId to visited.
             *
             * @param[in]  vertexId  The vertex identifier.
             */
            inline void SetVertexVisitedAt ( TVertexId vertexId )
            {
                USAGE_ASSERT ( graph_.VertexExists ( vertexId ) );
                visited_[vertexId] = true;
            }

            /**
             * @brief      Getter and setter to access the visited field.
             * @details    A vertex is visited if it is traversed (touched) for
             *     the first time (added to the queue).
             *
             * @param[in]  vertexId  The vertex identifier.
             *
             * @return     @p true if the vertex was visited, otherwise @p false.
             */
            inline bool VisitedVertexAt ( TVertexId vertexId ) const
            {
                USAGE_ASSERT ( graph_.VertexExists ( vertexId ) );
                return visited_[vertexId];
            }
        ///@}

        ///@name Vertex processed methods
        ///@{
#pragma mark VERTEX_PROCESSED_METHODS
            /**
             * @brief      Sets the vertex at @p vertexId to processed.
             *
             * @param[in]  vertexId  The vertex identifier.
             */
            inline void SetVertexProcessedAt ( TVertexId vertexId )
            {
                USAGE_ASSERT ( graph_.VertexExists ( vertexId ) );
                processed_[vertexId] = true;
            }

            /**
             * @brief      Getter and setter to access the process field.
             * @details    A vertex is processed if it is removed from the queue.
             *     Note that this means all its children will be visited
             *     subsequently.
             *
             * @param[in]  vertexId  The vertex identifier.
             *
             * @return     @p true if the vertex is processed, otherwise @p false.
             */
            inline bool ProcessedVertexAt ( TVertexId vertexId ) const
            {
                USAGE_ASSERT ( graph_.VertexExists ( vertexId ) );
                return processed_[vertexId];
            }
        ///@}

    public:
#pragma mark PARENT_METHODS
        /**
         * @brief      Getter and setter for the parent relation
         *
         * @param[in]  vertexId  The vertex identifier.
         *
         * @return     The vertex identifier of the parent.
         */
        ///@{
            inline TVertexId & ParentOf ( TVertexId vertexId )
            {
                USAGE_ASSERT ( graph_.VertexExists ( vertexId ) );
                return parent_[vertexId];
            }

            inline TVertexId ParentOf ( TVertexId vertexId ) const
            {
                USAGE_ASSERT ( graph_.VertexExists ( vertexId ) );
                return parent_[vertexId];
            }
        ///@}

        ///@name Pre and post processing methods
        ///@{
#pragma mark FURTHER_PROCESSING

            // virtual inline void PreprocessingVertexWith  ( TVertexId vertex ) = 0;
            // virtual inline void PostprocessingVertexWith ( TVertexId vertex ) = 0;
            // virtual inline void ProcessingEdgeWith ( TVertexId     source,
            //                                          TVertexId     target,
            //                                          Types::edgeId edgeId ) = 0;
        ///@}

    protected:
#pragma mark OTHER_METHODS
        /**
         * @brief      Clear and resize all vectors
         */
        inline void Clear ()
        {
            visited_.clear ();
            visited_.resize ( graph_.NumberOfVertices(), false );

            processed_.clear ();
            processed_.resize ( graph_.NumberOfVertices(), false );

            parent_.clear ();
            parent_.resize ( graph_.NumberOfVertices(), Const::NONE );
        }

        inline bool VertexExists ( TVertexId vertexId )
        {
            return graph_.VertexExists ( vertexId );
        }

        inline bool NumberOfVertices()
        {
            return graph_.NumberOfVertices ( );
        }

        /**
         * @name       Edge iterators.
         * @details    If the template parameter @p IsDirected is set to true
         *     the iterators loop over outgoing edges of the vertex only,
         *     otherwise it loops over all edges at the vertex.
         */
        ///@{
#pragma mark LOOPS
            /**
             * @brief      The @p for loop over all (outgoing) edges that is
             *     breakable.
             *
             * @param      vertexId  The vertex identifier.
             * @param[in]  function  The function, e.g., lambda function.
             *
             * @code{.cpp}
             *      breakable_for_all_edges_at(
             *          []( TEdge const & edge )
             *          {
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     FUNCTION  The function object that is called for
             *     all incident (outgoing) edges at @p vertexId.
             */
            template<typename FUNCTION>
            inline void breakable_for_all_edges_at ( TVertexId const & vertexId
                                                   , FUNCTION          function ) const
            {
                internal::GraphTypeLoopDifferentiation<TGraph, IsDirected>
                    ::breakable_for_all_edges_at ( graph_, vertexId, function );
            }

            /**
             * @brief      The @p for loop over all (outgoing) edges.
             *
             * @param      vertexId  The vertex identifier.
             * @param[in]  function  The function
             *
             * @code{.cpp}
             *      for_all_edges_at ( vertexId
             *          , []( TEdge const & edge )
             *          {
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     FUNCTION  The function object that is called for
             *     all incident (outgoing) edges at @p vertexId.
             */
            template<typename FUNCTION>
            inline void for_all_edges_at ( TVertexId const & vertexId
                                         , FUNCTION          function ) const
            {
                internal::GraphTypeLoopDifferentiation<TGraph, IsDirected>
                    ::for_all_edges_at ( graph_, vertexId, function );
            }
        ///@}
#pragma mark FRIEND
    private:
        friend class internal::GraphTypeLoopDifferentiation<TGraph, true>;
        friend class internal::GraphTypeLoopDifferentiation<TGraph, false>;

#pragma mark MEMBERS
    private:
        TGraph const &          graph_;        /**< The graph G=(V,E) */

        TVertexId               source_;       /**< Source vertex from which BFS starts */
        std::vector<bool>       visited_;      /**< Vertex already visited */
        std::vector<bool>       processed_;    /**< Vertex already processed */
        std::vector<TVertexId>  parent_;       /**< BFS structure in form of parent pointers */
};

namespace internal {

#pragma mark DIRECTED_GRAPH_LOOP

template<typename GraphType>
class GraphTypeLoopDifferentiation< GraphType, true > {
    // Type aliasing
    using TGraph  = GraphType;
    using TVertexId = typename GraphType::TVertexId;

    public:
        template<typename FUNCTION>
        static inline
        void breakable_for_all_edges_at ( TGraph    const & graph
                                        , TVertexId const & vertex
                                        , FUNCTION          function )
        {
            graph.template for_out_edges_at<ExecutionPolicy::breakable> ( vertex, function );
        }

        template<typename FUNCTION>
        static inline
        void for_all_edges_at ( TGraph    const & graph
                              , TVertexId const & vertex
                              , FUNCTION          function )
        {
            graph.template for_out_edges_at<ExecutionPolicy::sequential> ( vertex, function );
        }
};

#pragma mark UNDIRECTED_GRAPH_LOOP

template<typename GraphType>
class GraphTypeLoopDifferentiation< GraphType, false > {
    // Type aliasing
    using TGraph  = GraphType;
    using TVertexId = typename GraphType::TVertexId;

    public:
        template<typename FUNCTION>
        static inline
        void breakable_for_all_edges_at ( TGraph    const & graph
                                        , TVertexId const & vertex
                                        , FUNCTION          function )
        {
            graph.template for_all_edges_at<ExecutionPolicy::breakable> ( vertex, function );
        }

        template<typename FUNCTION>
        static inline
        void for_all_edges_at ( TGraph          & graph
                              , TVertexId const & vertex
                              , FUNCTION          function )
        {
            graph.template for_all_edges_at<ExecutionPolicy::sequential> ( vertex, function );
        }
};

} // namespace internal

} // namespace Traversal


#endif // EGOA__ALGORITHMS__GRAPH_TRAVERSAL__TRAVERSAL__HPP

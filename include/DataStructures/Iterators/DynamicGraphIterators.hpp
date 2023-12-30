/*
 * DynamicGraphIterators.hpp
 *
 *  Created on: Mar 4, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */

#ifndef EGOA__DATASTRUCTURES__GRAPHS__ITERATORS__DYNAMIC_GRAPH_ITERATORS_HPP
#define EGOA__DATASTRUCTURES__GRAPHS__ITERATORS__DYNAMIC_GRAPH_ITERATORS_HPP

#ifdef OPENMP_AVAILABLE
    #include <omp.h>
#endif

#include "GraphIterators.hpp"

namespace egoa::internal {

/**
 * @brief      The @p for loops for @p DynamicGraph
 *
 * @tparam     GraphType   The type of the graph, e.g., @p DynamicGraph<VertexType, EdgeType>.
 *                         If the graph type is @p const, const references to the vertices
 *                         and edges are passed to the function objects.
 * @tparam     Policy      The execution policy.
 *
 * @see        DynamicGraph
 * @see        ExecutionPolicy
 */
template<typename GraphType, ExecutionPolicy Policy>
class DynamicGraphLoopDifferentiation
    : public GraphLoopDifferentiation<GraphType, Policy>
{};

#ifdef OPENMP_AVAILABLE

/**
 * @brief      The parallel @p for loops for DynamicGraph.
 *
 * @tparam     GraphType  The type of the graph.
 */
template<typename GraphType>
class DynamicGraphLoopDifferentiation<GraphType, ExecutionPolicy::parallel>
    : public GraphLoopDifferentiation<GraphType, ExecutionPolicy::parallel> {

    using TGraph    = GraphType;
    using TVertex   = typename TGraph::TVertex;
    using TVertexId = typename TGraph::TVertexId;
    using TEdgeId   = typename TGraph::TEdgeId;

    public:
        /// @name Parallel Vertex Loops
        /// @{
#pragma mark PARALLEL_VERTEX_LOOPS

            /**
             * @brief      The parallel @p for loop over all vertex identifiers
             *             in the graph @f$\graph@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for all vertices.
             *                       It must accept one argument of type @p Types::vertexId
             *                       e.g.,
             * @code{.cpp}
             *      []( Types::vertexId vertexId )
             *      {
             *          // Do something with the vertex identifier.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_vertex_identifiers ( TGraph & graph
                                            , FUNCTION function )
            {
                #pragma omp parallel for
                    for ( TVertexId vertexId = 0
                        ; vertexId < graph.vertices_.size()
                        ; ++vertexId )
                    {
                        if (!graph.VertexExists(vertexId)) continue;
                        TVertexId copy = vertexId;
                        function( copy );
                    }
            }

            /**
             * @brief      The parallel @p for loop over all vertex objects @f$\vertices@f$
             *             in the graph @f$\graph@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for all vertices.
             *                       It must accept one argument of type @p TGraph::TVertex,
             *                       e.g.,
             * @code{.cpp}
             *      []( TVertex & vertex )
             *      {
             *          // Do something with the vertex object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_vertices ( TGraph & graph
                                  , FUNCTION function )
            {
                #pragma omp parallel for
                    for ( TVertexId vertexId = 0
                        ; vertexId < graph.vertices_.size()
                        ; ++vertexId )
                    {
                        if (!graph.VertexExists(vertexId)) continue;
                        function( graph.VertexAt(vertexId) );
                    }
            }

            /**
             * @brief      The parallel @p for loop over all pairs of vertex identifiers
             *             and vertex tuples in the graph @f$\graph@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for all vertices.
             *                       It must accept two arguments of types @p Types::vertexId
             *                       and @p TGraph::TVertex, e.g.,
             * @code{.cpp}
             *      []( Types::vertexId vertexId, TVertex & vertex )
             *      {
             *          // Do something with the vertex identifier and object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_vertex_tuples ( TGraph & graph
                                       , FUNCTION function )
            {
                #pragma omp parallel for
                    for ( TVertexId vertexId = 0
                        ; vertexId < graph.vertices_.size()
                        ; ++vertexId )
                    {
                        if (!graph.VertexExists(vertexId)) continue;
                        TVertexId copy = vertexId;
                        function( copy, graph.VertexAt(vertexId) );
                    }
            }
        /// @}

        /// @name Parallel Edge Loops
        /// @{
#pragma mark PARALLEL_EDGE_LOOPS

            /**
             * @brief      The parallel @p for loop over all indentifiers of edges in the
             *             graph @f$\graph@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for all edges.
             *                       It must accept one argument of type @p Types::edgeId,
             *                       e.g.,
             * @code{.cpp}
             *      []( Types::edgeId edgeId )
             *      {
             *          // Do something with the edge identifier.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_edge_identifiers ( TGraph & graph
                                          , FUNCTION function )
            {
                #pragma omp parallel for
                    for ( TEdgeId edgeId = 0
                        ; edgeId < graph.edges_.size()
                        ; ++edgeId )
                    {
                        if (!graph.EdgeExists(edgeId)) continue;
                        TEdgeId copy = edgeId;
                        function( copy );
                    }
            }

            /**
             * @brief      The parallel @p for loop over all edges @f$\edges@f$ in the
             *             graph @f$\graph@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for all edges.
             *                       It must accept one argument of type @p TGraph::TEdge,
             *                       e.g.,
             * @code{.cpp}
             *      []( TEdge & edge )
             *      {
             *          // Do something with the edge object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_edges ( TGraph & graph
                               , FUNCTION function )
            {
                #pragma omp parallel for
                    for ( TEdgeId edgeId = 0
                        ; edgeId < graph.edges_.size()
                        ; ++edgeId )
                    {
                        if (!graph.EdgeExists(edgeId)) continue;
                        function( graph.EdgeAt(edgeId) );
                    }
            }

            /**
             * @brief      The parallel @p for loop over all pairs of edge identifiers and
             *             edge objects in the graph @f$\graph@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for all edges.
             *                       It must accept two arguments of types @p Types::edgeId
             *                       and @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( Types::edgeId edgeId, TEdge & edge )
             *      {
             *          // Do something with the edge.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_edge_tuples ( TGraph & graph
                                     , FUNCTION function )
            {
                #pragma omp parallel for
                    for ( TEdgeId edgeId = 0
                        ; edgeId < graph.edges_.size()
                        ; ++edgeId )
                    {
                        if (!graph.EdgeExists(edgeId)) continue;
                        TEdgeId copy = edgeId;
                        function( copy, graph.EdgeAt(edgeId) );
                    }
            }
        /// @}
};

#else // OPENMP_AVAILABLE

/**
 * @brief      If OpenMP is not available, the parallel loops are run sequentially.
 *
 * @tparam     GraphType  The type of the graph
 */
template<typename GraphType>
class DynamicGraphLoopDifferentiation<GraphType, ExecutionPolicy::parallel>
    : public DynamicGraphLoopDifferentiation<GraphType, ExecutionPolicy::sequential> {
};
#endif // OPENMP_AVAILABLE


} // namespace egoa::internal

#endif // EGOA__DATASTRUCTURES__GRAPHS__ITERATORS__DYNAMIC_GRAPH_ITERATORS_HPP

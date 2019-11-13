/*
 * StaticGraphIterators.hpp
 *
 *  Created on: Dec 05, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__GRAPHS__ITERATORS__STATIC_GRAPH_ITERATORS_HPP
#define EGOA__DATA_STRUCTURES__GRAPHS__ITERATORS__STATIC_GRAPH_ITERATORS_HPP

#ifdef OPENMP_AVAILABLE
    #include <omp.h>
#endif

#include "Auxiliary/ExecutionPolicy.hpp"

#include "DataStructures/Graphs/Iterators/GraphIterators.hpp"

namespace egoa::internal {

/**
 * @brief      The @p for loops for @p StaticGraph
 * @details    The usage of templates is faster instead of ordinary function
 *     pointers such as std::function ( see
 *     https://stackoverflow.com/questions/14677997/stdfunction-vs-template
 *     for more information). This is the reason why the following code is not
 *     used 
 *     inline void for_all_<SOME_FUNCTION>(std::function<void(TVertex & vertex)> function) {}
 *     
 *
 * @tparam     GraphType   The type of the graph, e.g., @p StaticGraph<VertexType, EdgeType>.
 *                         If the graph type is @p const, const references to the vertices
 *                         and edges are passed to the function objects.
 * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
 *
 * @see        StaticGraph
 * @see        ExecutionPolicy
 */
template<typename GraphType, ExecutionPolicy Policy>
class StaticGraphLoopDifferentiation
    : public GraphLoopDifferentiation<GraphType, Policy>
{};

/**
 * @brief      The sequential @p for loops for @p StaticGraph.
 *
 * @tparam     GraphType  The type of the graph.
 */
template<typename GraphType>
class StaticGraphLoopDifferentiation<GraphType, ExecutionPolicy::sequential>
    : public GraphLoopDifferentiation<GraphType, ExecutionPolicy::sequential> {

    // Type aliasing
    using TGraph    = GraphType;
    using TVertex   = typename TGraph::TVertex;
    using TVertexId = typename TGraph::TVertexId;
    using TEdgeId   = typename TGraph::TEdgeId;

    public:
        ///@name Sequential Vertex Loops
        ///@{
#pragma mark SEQUENTIAL_VERTEX_LOOPS
            /**
             * @brief      The @p for loop over all vertex identifiers in the
             *             graph @f$\graph@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for all vertices.
             *                       It must accept one argument of type @p TGraph::TVertexId,
             *                       e.g.,
             * @code{.cpp}
             *      []( Types::vertexId vertexId ) 
             *      { 
             *          // Do something with the vertex identifier 
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
                for ( TVertexId vertexId = 0
                    ; vertexId < graph.NumberOfVertices()
                    ; ++vertexId ) 
                {
                    auto copy = vertexId;
                    function( copy );
                }
            }

            /**
             * @brief      The @p for loop over all pairs of vertex identifiers
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
            static inline
            void for_all_vertex_tuples ( TGraph & graph
                                      , FUNCTION function )
            {
                for ( TVertexId vertexId = 0
                    ; vertexId < graph.NumberOfVertices()
                    ; ++vertexId ) 
                {
                    auto copy = vertexId;
                    function( copy, graph.VertexAt(vertexId) );
                }
            }
        ///@}

        ///@name Sequential Edge Loops
        ///@{
#pragma mark SEQUENTIAL_EDGE_LOOPS

            /**
             * @brief      The @p for loop over all indentifiers of edges in the
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
            static inline 
            void for_all_edge_identifiers ( TGraph & graph
                                          , FUNCTION function )
            {
                for (TEdgeId edgeId = 0
                    ; edgeId < graph.NumberOfEdges()
                    ; ++edgeId )
                {
                    auto copy = edgeId;
                    function( copy );
                }
            }

            /**
             * @brief      The @p for loop over all pairs of edge identifiers and
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
            static inline 
            void for_all_edge_tuples ( TGraph & graph
                                    , FUNCTION function )
            {
                for ( TEdgeId edgeId = 0
                    ; edgeId < graph.NumberOfEdges()
                    ; ++edgeId )
                {
                    auto copy = edgeId;
                    function( copy, graph.EdgeAt(edgeId) );
                }
            }
        /// @}
};

/**
 * @brief      Breakable @p for loops for @p StaticGraph.
 * @details    The loops are aborted if the function returns @p false.
 *
 * @tparam     GraphType  The type of the graph.
 */
template<typename GraphType>
class StaticGraphLoopDifferentiation<GraphType, ExecutionPolicy::breakable>
    : public GraphLoopDifferentiation<GraphType, ExecutionPolicy::breakable> {
    using TGraph    = GraphType;
    using TVertexId = typename GraphType::TVertexId;
    using TVertex   = typename GraphType::TVertex;
    using TEdgeId   = typename GraphType::TEdgeId;
    
    public:
        /// @name Breakable Vertex Loops
        /// @{
#pragma mark BREAKABLE_VERTEX_LOOPS

            /**
             * @brief      The breakable @p for loop over all vertex identifiers
             *             in the graph @f$\graph@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for all vertices.
             *                       It must accept one argument of type @p Types::vertexId
             *                       e.g.,
             * @code{.cpp}
             *      []( Types::vertexId vertexId ) -> bool 
             *      {
             *          bool whetherToContinue = true;
             *          // Do something with the vertex identifier.
             *          return whetherToContinue;
             *      }
             * @endcode
             *
             * @tparam     FUNCTION The type of the function object.
             */
            template<typename FUNCTION>
            static inline
            void for_all_vertex_identifiers ( TGraph   & graph
                                            , FUNCTION   function )
            {
                bool toContinue = true;
                for ( TVertexId vertexId = 0
                    ; vertexId < graph.NumberOfVertices()
                    ; ++vertexId )
                {
                    auto copy = vertexId;
                    toContinue = function( copy );
                    if (!toContinue) return;
                }
            }

            /**
             * @brief      The breakable @p for loop over all pairs of vertex identifiers
             *             and vertex tuples in the graph @f$\graph@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for all vertices.
             *                       It must accept two arguments of types @p Types::vertexId
             *                       and @p TGraph::TVertex, e.g.,
             * @code{.cpp}
             *      []( Types::vertexId vertexId, TVertex & vertex ) -> bool 
             *      {
             *          bool whetherToContinue = true;
             *          // Do something with the vertex identifier and object.
             *          return whetherToContinue;
             *      }
             * @endcode
             *
             * @tparam     FUNCTION The type of the function object.
             */
            template<typename FUNCTION>
            static inline
            void for_all_vertex_tuples ( TGraph   & graph
                                      , FUNCTION   function )
            {
                bool toContinue = true;
                for ( TVertexId vertexId = 0
                    ; vertexId < graph.NumberOfVertices()
                    ; ++vertexId )
                {
                    auto copy = vertexId;
                    toContinue = function( copy, graph.VertexAt(vertexId) );
                    if (!toContinue) return;
                }
            }
        /// @}

        /// @name Breakable Edge Loops
        /// @{
#pragma mark BREAKABLE_EDGE_LOOPS

            /**
             * @brief      The breakable @p for loop over all identifiers of edges in the
             *             graph @f$\graph@f$.
             * @details    The loop is aborted if the function returns @p
             *     false, otherwise it continues.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for all edges.
             *                       It must accept one argument of type @p Types::edgeId,
             *                       e.g.,
             * @code{.cpp}
             *      []( Types::edgeId edgeId ) -> bool 
             *      {
             *          bool whetherToContinue = true;
             *          // Do something with the edge identifier
             *          return whetherToContinue;
             *      }
             * @endcode
             *
             * @tparam     FUNCTION The type of the function object.
             */
            template<typename FUNCTION>
            static inline
            void for_all_edge_identifiers ( TGraph   & graph
                                          , FUNCTION   function )
            {
                bool toContinue = true;
                for ( TEdgeId edgeId = 0
                    ; edgeId < graph.NumberOfEdges()
                    ; ++edgeId )
                {
                    auto copy = edgeId;
                    toContinue = function( copy );
                    if (!toContinue) return;
                }
            }

            /**
             * @brief      The breakable @p for loop over all pairs of edge identifiers and
             *             edge objects in the graph @f$\graph@f$.
             * @details    The loop is aborted if the function returns @p
             *     false, otherwise it continues.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for all edges.
             *                       It must accept two arguments of types @p Types::edgeId
             *                       and @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( Types::edgeId edgeId, TEdge & edge ) -> bool
             *      {
             *          bool whetherToContinue = true;
             *          // Do something with the edge
             *          return whetherToContinue;
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            static inline
            void for_all_edge_tuples ( TGraph   & graph
                                    , FUNCTION   function )
            {
                bool toContinue = true;
                for ( TEdgeId edgeId = 0
                    ; edgeId < graph.NumberOfEdges()
                    ; ++edgeId )
                {
                    auto copy = edgeId;
                    toContinue = function( copy, graph.EdgeAt(edgeId) );
                    if (!toContinue) return;
                }
            }

        /// @}
};

#ifdef OPENMP_AVAILABLE

/**
 * @brief      The parallel @p for loops for @p StaticGraph.
 *
 * @tparam     GraphType  The type of the graph.
 */
template<typename GraphType>
class StaticGraphLoopDifferentiation<GraphType, ExecutionPolicy::parallel>
    : public GraphLoopDifferentiation<GraphType, ExecutionPolicy::parallel> {
    // Type aliasing
    using TGraph    = GraphType;
    using TVertex   = typename TGraph::TVertex;
    using TVertexId = typename TGraph::TVertexId;
    using TEdgeId   = typename TGraph::TEdgeId;

    public:
        ///@name Parallel Vertex Loops
        ///@{
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
            static inline
            void for_all_vertex_identifiers ( TGraph & graph
                                            , FUNCTION function )
            {
                #pragma omp parallel for
                    for ( TVertexId vertexId = 0
                        ; vertexId < graph.NumberOfVertices()
                        ; ++vertexId )
                    {
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
            static inline
            void for_all_vertices ( TGraph & graph
                                  , FUNCTION function )
            {
                #pragma omp parallel for
                    for ( TVertexId vertexId = 0
                        ; vertexId < graph.NumberOfVertices()
                        ; ++vertexId )
                    {
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
            static inline
            void for_all_vertex_tuples ( TGraph & graph
                                      , FUNCTION function )
            {
                #pragma omp parallel for
                    for ( TVertexId vertexId = 0
                        ; vertexId < graph.NumberOfVertices()
                        ; ++vertexId )
                    {
                        auto copy = vertexId;
                        function( copy, graph.VertexAt(vertexId) );
                    }
            }
        ///@}

        ///@name Parallel Edge Loops
        ///@{
#pragma mark PARALLEL_EDGE_LOOPS

            /**
             * @brief      The parallel @p for loop over all identifiers of edges in the
             *             graph @f$\graph@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for all edges.
             *                       It must accept one argument of type @p Types::edgeId,
             *                       e.g.,
             * @code{.cpp}
             *      []( Types::edgeId edgeId ) 
             *      { 
             *          // Do something with the edge identifier 
             *      }
             * @endcode
             *
             * @tparam     FUNCTION The type of the function object.
             */
            template<typename FUNCTION>
            static inline
            void for_all_edge_identifiers ( TGraph & graph
                                          , FUNCTION function )
            {
                #pragma omp parallel for
                    for ( TEdgeId edgeId = 0
                        ; edgeId < graph.NumberOfEdges()
                        ; ++edgeId )
                    {
                        auto copy = edgeId;
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
             *      []( TEdge edge ) 
             *      { 
             *          // Do something with the edge object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION The type of the function object.
             */
            template<typename FUNCTION>
            static inline
            void for_all_edges ( TGraph & graph
                               , FUNCTION function )
            {
                #pragma omp parallel for
                    for ( TEdgeId edgeId = 0
                        ; edgeId < graph.NumberOfEdges()
                        ; ++edgeId )
                    {
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
             *      []( Types::edgeId edgeId, TEdge edge ) 
             *      { 
             *          // Do something with the edge.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            static inline
            void for_all_edge_tuples ( TGraph & graph
                                    , FUNCTION function )
            {
                #pragma omp parallel for
                    for ( TEdgeId edgeId = 0
                        ; edgeId < graph.NumberOfEdges()
                        ; ++edgeId )
                    {
                        auto copy = edgeId;
                        function( copy, graph.EdgeAt(edgeId) );
                    }
            }
        ///@}
};

#else // OPENMP_AVAILABLE

/**
 * @brief      If OpenMP is not available, fall back to sequential execution
 *     of the loops.
 *
 * @tparam     GraphType  The type of the graph.
 */
template<typename GraphType>
class StaticGraphLoopDifferentiation<GraphType, ExecutionPolicy::parallel>
    : public StaticGraphLoopDifferentiation<GraphType, ExecutionPolicy::sequential> {
};
#endif

} // namespace egoa::internal

#endif // EGOA__DATA_STRUCTURES__GRAPHS__ITERATORS__STATIC_GRAPH_ITERATORS_HPP

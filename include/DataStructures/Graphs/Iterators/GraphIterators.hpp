/*
 * GraphIterators.hpp
 *
 *  Created on: Mar 4, 2019
 *      Author: Matthias Wolf
 */

#ifndef EGOA__DATASTRUCTURES__GRAPHS__ITERATORS__GRAPH_ITERATORS_HPP
#define EGOA__DATASTRUCTURES__GRAPHS__ITERATORS__GRAPH_ITERATORS_HPP

#ifdef OPENMP_AVAILABLE
    #include <omp.h>
#endif

#include "Auxiliary/ExecutionPolicy.hpp"
#include "Auxiliary/Types.hpp"

namespace egoa::internal {

/**
 * @brief      The base class for @p for loops for graphs
 * @details    Implementations for the loops are defined in the
 *             template specializations for the different execution
 *             policies.
 *
 * @tparam     GraphType  The type of the graph.
 * @tparam     Policy     The execution policy.
 */
template<typename GraphType, ExecutionPolicy Policy>
class GraphLoopDifferentiation {};

/**
 * @brief      The base class for sequential @p for loops for graphs.
 *
 * @tparam     GraphType  The type of the graph
 */
template<typename GraphType>
class GraphLoopDifferentiation<GraphType, ExecutionPolicy::sequential> {
    // Type aliasing
    using TGraph    = GraphType;
    using TVertex   = typename TGraph::TVertex;
    using TVertexId = typename TGraph::TVertexId;
    using TEdgeId   = typename TGraph::TEdgeId;

    public:
        /// @name Sequential Vertex Loops
        /// @{
#pragma mark SEQUENTIAL_VERTEX_LOOPS

            /**
             * @brief      The @p for loop over all vertex identifiers in the
             *             graph @f$\graph@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for
             *                       all vertices. It must accept one argument
             *                       of type @p TGraph::TVertexId, e.g.,
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
            void for_all_vertex_identifiers( TGraph & graph,
                                             FUNCTION function )
            {
                for ( auto & vertex : graph.Vertices() ) 
                {
                    auto id = vertex.Identifier();
                    function( id );
                }
            }

            /**
             * @brief      The @p for loop over all vertex objects @f$\vertices@f$
             *             in the graph @f$\graph@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for
             *                       all vertices. It must accept one argument
             *                       of type @p TGraph::TVertex, e.g.,
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
            void for_all_vertices ( TGraph & graph,
                                    FUNCTION function )
            {
                for ( auto & vertex : graph.Vertices() ) 
                {
                    function( vertex );
                }
            }

            /**
             * @brief      The @p for loop over all pairs of vertex identifiers
             *             and vertex tuples in the graph @f$\graph@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for
             *                       all vertices. It must accept two
             *                       arguments of types @p Types::vertexId and
             *                       @p TGraph::TVertex, e.g.,
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
            void for_all_vertex_tuples ( TGraph & graph,
                                         FUNCTION function )
            {
                for ( auto & vertex : graph.Vertices() ) 
                {
                    auto id = vertex.Identifier();
                    function( id, vertex );
                }
            }
        /// @}

        /// @name Sequential Edge Loops
        /// @{
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
            inline static
            void for_all_edge_identifiers( TGraph & graph,
                                           FUNCTION function )
            {
                for ( auto & edge : graph.Edges() ) 
                {
                    auto id = edge.Identifier();
                    function( id );
                }
            }

            /**
             * @brief      The @p for loop over all edges @f$\edges@f$ in the
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
            void for_all_edges ( TGraph & graph,
                                 FUNCTION function )
            {
                for ( auto & edge : graph.Edges() ) 
                {
                    function( edge );
                }
            }

            /**
             * @brief      The @p for loop over all pairs of edge identifiers and
             *             edge objects in the graph @f$\graph@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for
             *                       all edges. It must accept two arguments
             *                       of types @p Types::edgeId and @p
             *                       TGraph::TEdge, e.g.,
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
            void for_all_edge_tuples ( TGraph & graph,
                                       FUNCTION function )
            {
                for ( auto & edge : graph.Edges() ) 
                {
                    auto id = edge.Identifier();
                    function( id, edge );
                }
            }
        /// @}

        /// @name Sequential Neighborhood Loops
        /// @{
#pragma mark SEQUENTIAL_NEIGHBORHOOD_LOOPS

            /**
             * @brief      The @p for loop over all edges at a vertex @f$v\in\vertices@f$.
             * @details    This is a loop over incoming and outgoing edges.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertex    The vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for all edges at
             *                       @f$v@f$. It must accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      { 
             *          // Do something with the edge object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_edges_at ( TGraph        & graph
                                  , TVertex const & vertex
                                  , FUNCTION        function )
            {
                for_all_edges_at( graph, vertex.Identifier(), function );
            }

            /**
             * @brief      The @p for loop over all edges at a vertex
             *     @f$v\in\vertices@f$.
             * @details    This is a loop over incoming and outgoing edges.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertexId  The identifier of the vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for all edges at
             *                       @f$v@f$. It must accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      { 
             *          // Do something with the edge object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_edges_at ( TGraph      & graph
                                  , TVertexId vertexId
                                  , FUNCTION  function )
            {
                for ( auto edgeId : graph.InEdgeIdsAt(vertexId) ) 
                {
                    function( graph.EdgeAt(edgeId) );
                }
                for ( auto edgeId : graph.OutEdgeIdsAt(vertexId) ) 
                {
                    function( graph.EdgeAt(edgeId) );
                }
            }

            /**
             * @brief      The @p for loop over all incoming edges of a vertex
             *     @f$v\in\vertices@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertex    The vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for
             *                       all incoming edges of @f$v@f$. It must
             *                       accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      { 
             *          // Do something with the edge object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_in_edges_at ( TGraph        & graph
                                 , TVertex const & vertex
                                 , FUNCTION        function )
            {
                for_in_edges_at( graph, vertex.Identifier(), function );
            }

            /**
             * @brief      The @p for loop over all incoming edges of a vertex
             *     @f$v\in\vertices@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertexId  The identifier of the vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for
             *                       all incoming edges of @f$v@f$. It must
             *                       accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      { 
             *          // Do something with the edge object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_in_edges_at ( TGraph    & graph
                                 , TVertexId   vertexId
                                 , FUNCTION    function )
            {
                for ( auto edgeId : graph.InEdgeIdsAt(vertexId) )
                {
                    function( graph.EdgeAt(edgeId) );
                }
            }

            /**
             * @brief      The @p for loop over all outgoing edges of a vertex
             *     @f$v\in\vertices@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertex    The vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for
             *                       all outgoing edges of @f$v@f$. It must
             *                       accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      { 
             *          // Do something with the edge object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_out_edges_at ( TGraph        & graph
                                  , TVertex const & vertex
                                  , FUNCTION        function )
            {
                for_out_edges_at( graph, vertex.Identifier(), function );
            }

             /**
             * @brief      The @p for loop over all outgoing edges of a vertex
             *     @f$v\in\vertices@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertexId  The identifier of the vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for
             *                       all outgoing edges of @f$v@f$. It must
             *                       accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      { 
             *          // Do something with the edge object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_out_edges_at ( TGraph    & graph
                                  , TVertexId   vertexId
                                  , FUNCTION    function )
            {
                for ( auto edgeId : graph.OutEdgeIdsAt(vertexId) )
                {
                    function( graph.EdgesAt( edgeId ) );
                }
            }
        /// @}
};

/**
 * @brief      Breakable @p for loops for graphs.
 * @details    The loops are aborted if the function returns @p false.
 *
 * @tparam     GraphType  The type of the graph.
 */
template<typename GraphType>
class GraphLoopDifferentiation<GraphType, ExecutionPolicy::breakable> {
    // Type aliasing
    using TGraph    = GraphType;
    using TVertex   = typename TGraph::TVertex;
    using TVertexId = typename TGraph::TVertexId;
    using TEdgeId   = typename TGraph::TEdgeId;

    public:
        /// @name Breakable Vertex Loops
        /// @{
#pragma mark BREAKABLE_VERTEX_LOOPS

            /**
             * @brief      The breakable @p for loop over all vertex identifiers
             *             in the graph @f$\graph@f$.
             * @details    The loop is aborted if the function returns @p false.
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
            inline static
            void for_all_vertex_identifiers( TGraph & graph,
                                             FUNCTION function )
            {
                for ( auto & vertex : graph.Vertices() ) 
                {
                    auto id = vertex.Identifier();
                    bool toContinue = function( id );
                    if (!toContinue) return;
                }
            }

            /**
             * @brief      The breakable @p for loop over all vertex objects
             *             @f$\vertices@f$ in the graph @f$\graph@f$.
             * @details    The loop is aborted if the function returns @p false.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for
             *                       all vertices. It must accept one argument
             *                       of type @p TGraph::TVertex, e.g.,
             * @code{.cpp}
             *      []( TVertex & vertex ) -> bool 
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
            inline static
            void for_all_vertices( TGraph & graph,
                                   FUNCTION function )
            {
                for ( auto & vertex : graph.Vertices() ) 
                {
                    bool toContinue = function( vertex );
                    if (!toContinue) return;
                }
            }

            /**
             * @brief      The breakable @p for loop over all pairs of vertex
             *             identifiers and vertex tuples in the graph
             *             @f$\graph@f$.
             * @details    The loop is aborted if the function returns @p false.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for
             *                       all vertices. It must accept two
             *                       arguments of types @p Types::vertexId and
             *                       @p TGraph::TVertex, e.g.,
             * @code{.cpp}
             *      []( Types::vertexId vertexId, TVertex vertex ) -> bool 
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
            inline static
            void for_all_vertex_tuples( TGraph & graph,
                                        FUNCTION function )
            {
                for ( auto & vertex : graph.Vertices() ) 
                {
                    auto id = vertex.Identifier();
                    bool toContinue = function( id, vertex );
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
             * @details    The loop is aborted if the function returns @p false.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for all edges.
             *                       It must accept one argument of type @p Types::edgeId,
             *                       e.g.,
             * @code{.cpp}
             *      []( Types::edgeId edgeId ) -> bool 
             *      {
             *          bool whetherToContinue = true;
             *          // Do something with the edge identifier.
             *          return whetherToContinue;
             *      }
             * @endcode
             *
             * @tparam     FUNCTION The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_edge_identifiers( TGraph & graph,
                                           FUNCTION function )
            {
                for ( auto & edge : graph.Edges() ) 
                {
                    auto id = edge.Identifier();
                    bool toContinue = function( id );
                    if (!toContinue) return;
                }
            }

            /**
             * @brief      The breakable @p for loop over all edges @f$\edges@f$ in the
             *             graph @f$\graph@f$.
             * @details    The loop is aborted if the function returns @p false.            
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for all edges.
             *                       It must accept one argument of type @p TGraph::TEdge,
             *                       e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      {
             *          bool whetherToContinue = true;
             *          // Do something with the edge object.
             *          return whetherToContinue;
             *      }
             * @endcode
             *
             * @tparam     FUNCTION The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_edges( TGraph & graph,
                                FUNCTION function )
            {
                for ( auto & edge : graph.Edges() ) 
                {
                    bool toContinue = function( edge );
                    if (!toContinue) return;
                }
            }

            /**
             * @brief      The breakable @p for loop over all pairs of edge identifiers and
             *             edge objects in the graph @f$\graph@f$.
             * @details    The loop is aborted if the function returns @p false.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  function  The function object that is called for all edges.
             *                       It must accept two arguments of types @p Types::edgeId
             *                       and @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( Types::edgeId edgeId, TEdge & edge ) 
             *      {
             *          bool whetherToContinue = true;
             *          // Do something with the edge.
             *          return whetherToContinue;
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_edge_tuples( TGraph & graph,
                                           FUNCTION function )
            {
                for ( auto & edge : graph.Edges() ) 
                {
                    auto id = edge.Identifier();
                    bool toContinue = function( id, edge );
                    if (!toContinue) return;
                }
            }
        /// @}

        /// @name Breakable Neighborhood Loops
        /// @{
#pragma mark BREAKABLE_NEIGHBORHOOD_LOOPS
            /**
             * @brief      The breakable @p for loop over all edges at a
             *     vertex @f$v\in\vertices@f$.
             * @details    This is a loop over incoming and outgoing edges.
             *     The loop is aborted if the function returns @p false.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertex    The vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for all edges at
             *                       @f$v@f$. It must accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      {
             *          bool whetherToContinue = true;
             *          // Do something with the edge object.
             *          return whetherToContinue;
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_edges_at ( TGraph &        graph,
                                    TVertex const & vertex,
                                    FUNCTION        function )
            {
                for_all_edges_at( graph, vertex.Identifier(), function );
            }

            /**
             * @brief      The breakable @p for loop over all edges at a
             *     vertex @f$v\in\vertices@f$.
             * @details    This is a loop over incoming and outgoing edges.
             *     The loop is aborted if the function returns @p false.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertexId  The identifier of the vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for all edges at
             *                       @f$v@f$. It must accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      {
             *          bool whetherToContinue = true;
             *          // Do something with the edge object.
             *          return whetherToContinue;
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_edges_at ( TGraph &  graph,
                                    TVertexId vertexId,
                                    FUNCTION  function )
            {
                for ( auto edgeId : graph.InEdgeIdsAt(vertexId) ) 
                {
                    bool toContinue = function( graph.EdgeAt(edgeId) );
                    if (!toContinue) return;
                }
                for ( auto edgeId : graph.OutEdgeIdsAt(vertexId) ) 
                {
                    bool toContinue = function( graph.EdgeAt(edgeId) );
                    if (!toContinue) return;
                }
            }

            /**
             * @brief      The breakable @p for loop over all incoming edges
             *     of a vertex @f$v\in\vertices@f$.
             * @details    The loop is aborted if the function returns @p false.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertex    The vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for all incoming edges
             *                       of @f$v@f$. It must accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      {
             *          bool whetherToContinue = true;
             *          // Do something with the edge object.
             *          return whetherToContinue;
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_in_edges_at ( TGraph &        graph,
                                   TVertex const & vertex,
                                   FUNCTION        function)
            {
                for_in_edges_at( graph, vertex.Identifier(), function );
            }

            /**
             * @brief      The breakable @p for loop over all incoming edges
             *     of a vertex @f$v\in\vertices@f$.
             * @details    The loop is aborted if the function returns @p false.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertexId  The identifier of the vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for all incoming edges
             *                       of @f$v@f$. It must accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge edge ) 
             *      {
             *          bool whetherToContinue = true;
             *          // Do something with the edge object.
             *          return whetherToContinue;
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_in_edges_at ( TGraph &   graph,
                                   TVertexId  vertexId,
                                   FUNCTION   function )
            {
                for ( auto edgeID : graph.InEdgeIdsAt(vertexId) )
                {
                    bool toContinue = function( graph.EdgeAt(edgeID) );
                    if ( !toContinue ) return;
                }
            }

            /**
             * @brief      The breakable @p for loop over all outgoing edges
             *     of a vertex @f$v\in\vertices@f$.
             * @details    The loop is aborted if the function returns @p false.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertex    The vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for all outgoing edges
             *                       of @f$v@f$. It must accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      {
             *          bool whetherToContinue = true;
             *          // Do something with the edge object.
             *          return whetherToContinue;
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_out_edges_at ( TGraph &        graph,
                                    TVertex const & vertex,
                                    FUNCTION        function)
            {
                for_out_edges_at( graph, vertex.Identifier(), function );
            }

            /**
             * @brief      The breakable @p for loop over all outgoing edges
             *     of a vertex @f$v\in\vertices@f$.
             * @details    The loop is aborted if the function returns @p false.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertexId  The identifier of the vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for all outgoing edges
             *                       of @f$v@f$. It must accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      {
             *          bool whetherToContinue = true;
             *          // Do something with the edge object.
             *          return whetherToContinue;
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_out_edges_at ( TGraph &   graph,
                                    TVertexId  vertexId,
                                    FUNCTION   function )
            {
                for ( auto edgeID : graph.OutEdgeIdsAt(vertexId) )
                {
                    bool toContinue = function( graph.EdgeAt(edgeID) );
                    if ( !toContinue ) return;
                }
            }
};

#ifdef OPENMP_AVAILABLE

/**
 * @brief      The base class for parallel @p for loops for graphs.
 * @details    Not all loops are defined because some of them are
 *             impossible to define efficiently in general.
 *
 * @tparam     GraphType  The type of the graph.
 */
template<typename GraphType>
class GraphLoopDifferentiation<GraphType, ExecutionPolicy::parallel> {
    // Type aliasing
    using TGraph    = GraphType;
    using TVertex   = typename TGraph::TVertex;
    using TVertexId = typename TGraph::TVertexId;
    using TEdgeId   = typename TGraph::TEdgeId;

    public:
        /// @name Parallel Neighborhood Loops
        /// @{
#pragma PARALLEL_NEIGHBORHOOD_LOOPS
            /**
             * @brief      The parallel @p for loop over all edges at a vertex
             *     @f$v\in\vertices@f$.
             * @details    This is a loop over incoming and outgoing edges.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertex    The vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for all edges at
             *                       @f$v@f$. It must accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      { 
             *          // Do something with the edge object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_edges_at( TGraph        & graph,
                                   TVertex const & vertex,
                                   FUNCTION        function )
            {
                for_all_edges_at( graph, vertex.Identifier(), function );
            }

            /**
             * @brief      The parallel @p for loop over all edges at a vertex
             *     @f$v\in\vertices@f$.
             * @details    This is a loop over incoming and outgoing edges.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertexId  The identifier of the vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for all edges at
             *                       @f$v@f$. It must accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      { 
             *          // Do something with the edge object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             *
             * @todo Run the two loops in parallel
             */
            template<typename FUNCTION>
            inline static
            void for_all_edges_at ( TGraph &  graph,
                                    TVertexId vertexId,
                                    FUNCTION  function )
            {
                auto & inEdgeIds = graph.InEdgeIdsAt(vertexId);
                #pragma omp parallel for
                    for ( Types::index index = 0
                        ; index < inEdgeIds.size()
                        ; ++index )
                    {
                        function( graph.EdgeAt(inEdgeIds[index]) );
                    }

                auto & outEdgeIds = graph.OutEdgeIdsAt(vertexId);
                #pragma omp parallel for
                    for ( Types::index index = 0
                        ; index < outEdgeIds.size()
                        ; ++index )
                    {
                        function( graph.EdgeAt(outEdgeIds[index]) );
                    }
            }

            /**
             * @brief      The parallel @p for loop over all incoming edges of
             *     a vertex @f$v\in\vertices@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertex    The vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for
             *                       all incoming edges of @f$v@f$. It must
             *                       accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      { 
             *          // Do something with the edge object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_in_edges_at ( TGraph        & graph,
                                   TVertex const & vertex,
                                   FUNCTION        function )
            {
                for_in_edges_at( graph, vertex.Identifier(), function );
            }

            /**
             * @brief      The parallel @p for loop over all incoming edges of
             *     a vertex @f$v\in\vertices@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertexId  The identifier of the vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for
             *                       all incoming edges of @f$v@f$. It must
             *                       accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      { 
             *          // Do something with the edge object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_in_edges_at ( TGraph &  graph,
                                   TVertexId vertexId,
                                   FUNCTION  function )
            {
                auto & inEdgeIds = graph.InEdgeIdsAt(vertexId);
                #pragma omp parallel for
                    for ( Types::index index = 0
                        ; index < inEdgeIds.size()
                        ; ++index )
                    {
                        function( graph.EdgeAt(inEdgeIds[index]) );
                    }
            }

            /**
             * @brief      The parallel @p for loop over all outgoing edges of
             *     a vertex @f$v\in\vertices@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertex    The vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for
             *                       all outgoing edges of @f$v@f$. It must
             *                       accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      { 
             *          // Do something with the edge object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_out_edges_at ( TGraph        & graph,
                                    TVertex const & vertex,
                                    FUNCTION        function )
            {
                for_out_edges_at( graph, vertex.Identifier(), function );
            }

            /**
             * @brief      The parallel @p for loop over all outgoing edges of
             *     a vertex @f$v\in\vertices@f$.
             *
             * @param      graph     The graph @f$\graph = (\vertices, \edges)@f$.
             * @param[in]  vertexId  The identifier of the vertex @f$v\in\vertices@f$.
             * @param[in]  function  The function object that is called for
             *                       all outgoing edges of @f$v@f$. It must
             *                       accept one argument of type
             *                       @p TGraph::TEdge, e.g.,
             * @code{.cpp}
             *      []( TEdge & edge ) 
             *      { 
             *          // Do something with the edge object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_out_edges_at( TGraph &  graph,
                                   TVertexId vertexId,
                                   FUNCTION  function )
            {
                auto & outEdgeIds = graph.OutEdgeIdsAt(vertexId);
                #pragma omp parallel for
                    for ( Types::index index = 0
                        ; index < outEdgeIds.size()
                        ; ++index )
                    {
                        function( graph.EdgeAt(outEdgeIds[index]) );
                    }
            }
        /// @}
};

#else // OPENMP_AVAILABLE

/**
 * @brief      If OpenMP is not available, the loops are run sequentially.
 *
 * @tparam     GraphType  The type of the graph.
 */
template<typename GraphType>
class GraphLoopDifferentiation<GraphType, ExecutionPolicy::parallel>
    : public GraphLoopDifferentiation<GraphType, ExecutionPolicy::sequential> {
};

#endif // OPENMP_AVAILABLE

} // namespace egoa::internal

#endif // EGOA__DATASTRUCTURES__GRAPHS__ITERATORS__GRAPH_ITERATORS_HPP

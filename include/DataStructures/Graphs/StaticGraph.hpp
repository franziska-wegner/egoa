/*
 * StaticGraph.hpp
 *
 *  Created on: Nov 04, 2018
 *      Author: Franziska Wegner
 */
 
#ifndef EGOA__DATA_STRUCTURES__GRAPHS__STATIC_GRAPH_HPP
#define EGOA__DATA_STRUCTURES__GRAPHS__STATIC_GRAPH_HPP

#include <algorithm>
#include <tuple>
#include <type_traits>

#include "Auxiliary/ExecutionPolicy.hpp"

#include "DataStructures/Graphs/Iterators/StaticGraphIterators.hpp"
#include "DataStructures/Views/VectorView.hpp"

#include "Exceptions/Assertions.hpp"

#include "DataStructures/Graphs/Edges/Edge.hpp"
#include "DataStructures/Graphs/Vertices/Vertex.hpp"

namespace egoa {

/**
 * @brief      A graph data structure that supports adding vertices and edges.
 * @details    Both @p VertexProperties and @p EdgeProperties must be able to
 *             store an identifier, which can be accessed in the following
 *             way. Here, @p vertex and @p constVertex are objects of type @p
 *             VertexProperties and @p VertexProperties @p const,
 *             respectively, and @p vId is of type @p Types::vertexId.
 *             Similarly, @p edge and @p constEdge are objects of type @p
 *             EdgeProperties and @p EdgeProperties @p const, respectively,
 *             and @p eId is of type @p Types::edgeId.
 *
 *             Operation                                                      | Effect
 *             ---------------------------------------------------------------|-----------------------------
 *             @code vertex.Identifier() = vId;                      @endcode | The identifier of @p vertex is set to @p vId.
 *             @code Types::vertexId vId = constVertex.Identifier(); @endcode | @p vId is set to the identifier of @p vertex.
 *             @code edge.Identifier() = eId;                        @endcode | The identifier of @p edge is set to @p eId.
 *             @code Types::edgeId eId = constEdge.Identifier();     @endcode | @p eId is set to the identifier of @p edge.
 *             @code Types::vertexId vId = constEdge.Source();       @endcode | @p vId is set to the identifier of the source of @p edge.
 *             @code Types::vertexId vId = constEdge.Target();       @endcode | @p vId is set to the identifier of the target of @p edge.
 *
 * @tparam     VertexProperties  Type of a vertex, e.g., ElectricalVertex.
 * @tparam     EdgeProperties    Type of an edge, e.g., ElectricalEdge.
 */
template< typename VertexProperties
        , typename EdgeProperties>
class StaticGraph {
    public:
        // Template type aliasing
        using TGraph             = StaticGraph<VertexProperties
                                             , EdgeProperties>;
        // Vertices
        using TVertexProperties  = VertexProperties;
        using TVertex            = Vertices::Vertex<TVertexProperties>;
        using TVertexId          = Types::vertexId;
        // Edges
        using TEdgeProperties    = EdgeProperties;
        using TEdge              = Edges::Edge<TEdgeProperties>;
        using TEdgeId            = Types::edgeId;
        // Views
        using TVerticesView      = VectorView<TVertex, false>;
        using TConstVerticesView = VectorView<TVertex, true>;
        using TEdgesView         = VectorView<TEdge, false>;
        using TConstEdgesView    = VectorView<TEdge, true>;

        /**@name Constructors and Destructor */
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTOR    
        
            StaticGraph()
            : name_("")
            {}

            explicit StaticGraph ( Types::name name ) 
            : name_(std::move(name))
            {}
        ///@}

        /**@name Getter and Setter */
        ///@{
#pragma mark GETTER_AND_SETTER

            /**
             * @brief      Name of the graph.
             *
             * @return     The name of the graph.
             */
            inline Types::name Name() const
            {
                return name_;
            }

            /**
             * @brief      Number of vertices @f$n = |\vertices|@f$.
             *
             * @return     The number of vertices @f$n = |\vertices|@f$.
             */
            inline Types::count NumberOfVertices() const
            {
                return vertices_.size();   
            }
            
            /**
             * @brief      Number of edges @f$m = |\edges|@f$.
             *
             * @return     The number of edges @f$m = |\edges|@f$.
             */
            inline Types::count NumberOfEdges() const
            {
                return edges_.size();      
            }
        ///@}


        /**@name Vertex Related Methods */
        ///@{
#pragma mark VERTEX_RELATED_METHODS

            /**
             * @brief      A view on the vertices.
             * @details    If a vertex is added, the view is still valid but
             *             the iterators obtained via this view are
             *             invalidated.
             *
             *             If the graphs is destroyed, all views are
             *             invalidated and calling any member function on them
             *             has undefined behavior.
             *
             * @return     A view on the vertices
             */
            inline TVerticesView Vertices()
            {
                return TVerticesView( & vertices_ );
            }

            /**
             * @brief      A view on the vertices.
             * @details    The vertices can be modified via this view.
             *
             *             If a vertex is added, the view is still valid but
             *             the iterators obtained via this view are
             *             invalidated.
             *
             *             If the graphs is destroyed, all views are
             *             invalidated and calling any member function on them
             *             has undefined behavior.
             *
             * @return     A view on the vertices.
             */
            inline TConstVerticesView Vertices() const
            {
                return TConstVerticesView( & vertices_ );
            }

            /**
             * @brief      Whether a vertex with identifier @p id exists in the graph.
             *
             * @param[in]  id  The identifier of the vertex.
             *
             * @return     @p true if a vertex with identifier @p id exists,
             *             @p false otherwise.
             */
            inline bool VertexExists ( Types::vertexId id ) const
            {
                return id < NumberOfVertices();
            }

            /**
             * @brief      The vertex with identifier @p id.
             *
             * @pre        There is a vertex with identifier @p id in the graph.
             *
             * param[in]   id  The identifier of the vertex.
             *
             * @return     The vertex object.
             */
            inline TVertex & VertexAt ( Types::vertexId id )
            {
                USAGE_ASSERT ( VertexExists(id) );
                return vertices_[id];
            }

            /**
             * @brief      The vertex with identifier @p id.
             *
             * @pre        There is a vertex with identifier @p id in the graph.
             *
             * param[in]   id  The identifier of the vertex.
             *
             * @return     The vertex object.
             */
            inline TVertex const & VertexAt ( Types::vertexId id ) const
            {
                USAGE_ASSERT ( VertexExists(id) );
                return vertices_[id];
            }

            // Avoid implicit conversions on non-constructing functions
            inline TVertex       & VertexAt ( int  id )       = delete;
            inline TVertex       & VertexAt ( char id )       = delete;
            inline TVertex const & VertexAt ( int  id ) const = delete;
            inline TVertex const & VertexAt ( char id ) const = delete;

            /**
             * @brief      The vertex identifier of a vertex object.
             * @details    Calls @p vertex.Identifier().
             *
             * @param[in]  vertex  The vertex.
             *
             * @return     The vertex identifier.
             */
            inline Types::vertexId VertexId ( TVertex const & vertex ) const
            {
                return vertex.Identifier();
            }

            /**
             * @brief      Adds a vertex.
             *
             * @param      properties  The vertex properties.
             *
             * @return     The identifier of the vertex.
             */
            inline Types::vertexId AddVertex ( TVertexProperties const & properties )
            {
                return AddVertex( TVertexProperties(properties) );
            }

            /**
             * @brief      Adds a vertex.
             *
             * @param      properties  The vertex properties.
             *
             * @return     The identifier of the vertex.
             */
            inline Types::vertexId AddVertex ( TVertexProperties && properties )
            {
                Types::vertexId id  = vertices_.size();
                vertices_.emplace_back( id, std::move(properties) );
                inEdgeIds_.emplace_back( std::vector<Types::edgeId>() );
                outEdgeIds_.emplace_back( std::vector<Types::edgeId>() );
                
                ESSENTIAL_ASSERT (   vertices_.size() == NumberOfVertices() );
                ESSENTIAL_ASSERT (  inEdgeIds_.size() == NumberOfVertices() );
                ESSENTIAL_ASSERT ( outEdgeIds_.size() == NumberOfVertices() );

                return id;
            }

            // TODO: Write EmplaceVertex?

            /**
             * @brief      Applies @p function to all vertices and collects
             *     the result in a vector.
             *             
             * @param[in]  function  The function that is applied to all edges.
             * @code{.cpp}
             *      TResult function ( Types::vertexId, TVertex )
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             *
             * @return     A vector containing the results of the applications
             *             of @p function to all vertices.
             */
            template<typename FUNCTION>
            inline auto MapVertices ( FUNCTION function ) const
                    -> std::vector<decltype(function(std::declval<Types::vertexId>(), std::declval<TVertex>()))> 
            {
                using TResult = decltype(function(std::declval<Types::vertexId>(), std::declval<TVertex>()));
                std::vector<TResult> result;

                for_all_vertex_tuples<ExecutionPolicy::sequential>( 
                    [&]( Types::vertexId id, const TVertex & vertex ) 
                    {
                        result.push_back ( function(id, vertex) );
                    }
                );

                return result;
            }

            /**
             * @brief      Neighbors of a vertex.
             * @details    A vector containing the identifiers of the
             *             neighbors of the given vertex is returned. The
             *             order of the neighbors is unspecified.
             *
             * @pre        The vertex with identifier @p id exists.
             *
             * @param[in]  id  The id of a vertex.
             *
             * @return     The vertex identifiers of all neighbors.
             */
            inline std::vector<Types::vertexId> NeighborsOf ( Types::vertexId id ) const
            {
                USAGE_ASSERT ( VertexExists(id) );

                std::vector<Types::vertexId> vertexIds;
                NeighborsOf(id, vertexIds);
                return vertexIds;
            }

            /**
             * @brief      Neighbors of a vertex
             * @details    The neighbors of the vertex are appended to the
             *             vector @p vertexId. The order of the neighbors is
             *             unspecified.
             *
             *             Time complexity: @f$O(|\vertices|)@f$.
             *
             * @pre        The vertex with identifier @p id exists.
             *
             * @param[in]  id         The vertex identifier.
             * @param      vertexIds  The vector to which the identifiers of
             *     the neighbors are appended.
             */
            inline void NeighborsOf ( Types::vertexId                id
                                    , std::vector<Types::vertexId> & vertexIds ) const
            {
                USAGE_ASSERT ( VertexExists(id) );

                std::vector<bool> vertexVisited(NumberOfVertices(), false);

                for (Types::edgeId edgeId : OutEdgeIdsAt(id)) 
                {
                    Types::vertexId otherVertex = EdgeAt(edgeId).Target();
                    if (!vertexVisited[otherVertex]) 
                    {
                        vertexIds.push_back(otherVertex);
                        vertexVisited[otherVertex] = true;
                    }
                }
                for (Types::edgeId edgeId : InEdgeIdsAt(id)) 
                {
                    Types::vertexId otherVertex = EdgeAt(edgeId).Source();
                    if (!vertexVisited[otherVertex]) 
                    {
                        vertexIds.push_back(otherVertex);
                        vertexVisited[otherVertex] = true;
                    }
                }
            }

            /**
             * @brief      The indegree of the vertex with identifier @p id.
             *
             * @pre        There is a vertex with identifier @p id in the graph.
             *
             * @param[in]  id  The vertex identifier.
             *
             * @return     The number of incoming edges.
             */
            inline Types::count InDegreeAt ( Types::vertexId id ) const
            {
                USAGE_ASSERT ( VertexExists(id) );
                return InEdgeIdsAt(id).size();
            }

            /**
             * @brief      The outdegree of the vertex with identifier @p id.
             *
             * @pre        There is a vertex with identifier @p id in the graph.
             *
             * @param[in]  id  The vertex identifier.
             *
             * @return     The number of outgoing edges.
             */
            inline Types::count OutDegreeAt ( Types::vertexId id ) const
            {
                USAGE_ASSERT ( VertexExists(id) );
                return OutEdgeIdsAt(id).size();
            }

            /**
             * @brief      The degree of the vertex with identifier @p id.
             *
             * @pre        There is a vertex with identifier @p id in the graph.
             *
             * @param[in]  id  The vertex identifier.
             *
             * @return     The number of incident edges.
             */
            inline Types::count DegreeAt ( Types::vertexId id ) const
            {
                USAGE_ASSERT ( VertexExists(id) );
                return InDegreeAt(id) + OutDegreeAt(id);
            }

            /**
             * @brief      The identifiers of all incoming edges.
             *
             * @pre        There is a vertex with identifier @p id in the graph.
             *
             * @param[in]  id  The vertex identifier.
             *
             * @return     The identifiers of the incoming edges at vertex @p id.
             */
            inline std::vector<Types::edgeId> const & InEdgeIdsAt ( Types::vertexId id ) const
            {
                USAGE_ASSERT ( VertexExists(id) );
                return inEdgeIds_[id];
            }

            /**
             * @brief      The identifiers of all outgoing edges
             *
             * @pre        There is a vertex with identifier @p id in the graph.
             *
             * @param[in]  id  The vertex identifier.
             *
             * @return     The identifiers of the outgoing edges at vertex @p id.
             */
            inline std::vector<Types::edgeId> const & OutEdgeIdsAt ( Types::vertexId id ) const
            {
                USAGE_ASSERT ( VertexExists(id) );
                return outEdgeIds_[id];
            }

            /**
             * @brief      All edge identifiers of edges incident to a vertex.
             * @details    The order of the identifiers is unspecified.
             *
             * @pre        There is a vertex with identifier @p id in the graph.
             *
             * @param[in]  id  The vertex identifier.
             *
             * @return     The edge identifiers at a vertex @p id.
             */
            inline std::vector<Types::edgeId> EdgeIdsAt ( Types::vertexId id ) const
            {
                USAGE_ASSERT ( VertexExists(id) );

                std::vector<Types::edgeId> edgeIds;
                EdgeIdsAt(id, edgeIds);
                return edgeIds;
            }

            /**
             * @brief      All edge identifiers of edges incident to a vertex
             *             are added to the end of the vector @p edgeIds.
             * @details    The order of the identifiers is unspecified.
             *
             * @pre        There is a vertex with identifier @p id in the
             *     graph.
             *
             * @param[in]  id    The vertex id
             * @param      edgeIds  The vector to which the edge identifiers
             *     are appended.
             */
            inline void EdgeIdsAt ( Types::vertexId              id
                                  , std::vector<Types::edgeId> & edgeIds ) const
            {
                USAGE_ASSERT ( VertexExists(id) );

                auto & inIds  = InEdgeIdsAt(id);
                auto & outIds = OutEdgeIdsAt(id);
                edgeIds.insert( edgeIds.end(), inIds.begin(), inIds.end() );
                edgeIds.insert( edgeIds.end(), outIds.begin(), outIds.end() );
            }
        /// @}

        /**@name Edge related methods */
        ///@{
#pragma mark EDGE_RELATED_METHODS

            /**
             * @brief      A view on the edges.
             * @details    The edges can be modified via this view.
             *
             *             If an edge is added, the view is still valid but
             *             the iterators obtained via this view are
             *             invalidated.
             *
             *             If the graphs is destroyed, all view are
             *             invalidated and calling any member function on them
             *             has undefined behavior.
             *
             * @return     A view on the edges
             */
            inline TEdgesView Edges()
            {
                return TEdgesView ( & edges_ );
            }

            /**
             * @brief      A view on the edges.
             * @details    The edges cannot be modified via this view.
             *
             *             If an edge is added, the view is still valid but
             *             the iterators obtained via this view are
             *             invalidated.
             *
             *             If the graphs is destroyed, all view are
             *             invalidated and calling any member function on them
             *             has undefined behavior.
             *
             * @return     A view on the edges
             */
            inline TConstEdgesView Edges() const
            {
                return TConstEdgesView ( & edges_ );
            }

            /**
             * @brief      Whether an edge with the identifier @p id exists in
             *     the graph.
             *
             * @param[in]  id  The edge identifier
             *
             * @return     @p true if an edge with identifier @p id exists, @p
             *     false otherwise.
             */
            inline bool EdgeExists ( Types::edgeId id ) const
            {
                return id < NumberOfEdges();
            }

            /**
             * @brief      The edge with identifier @p id.
             *
             * @pre        The edge with identifier @p id exists.
             *
             * @param[in]  id  The edge identifier.
             *
             * @return     The edge object with identifier @p id.
             */
            inline TEdge & EdgeAt ( Types::edgeId id )
            {
                USAGE_ASSERT ( EdgeExists(id) );
                return edges_[id];
            }

            /**
             * @brief      The edge with identifier @p id.
             *
             * @pre        The edge with identifier @p id exists.
             *
             * @param[in]  id  The edge identifier.
             *
             * @return     The edge object with identifier @p id.
             */
            inline TEdge const & EdgeAt ( Types::edgeId id ) const
            {
                USAGE_ASSERT ( EdgeExists(id) );
                return edges_[id];
            }

            /**
             * @brief      Searches for the identifier of the edge
             *     @f$(\vertexa, \vertexb)@f$.
             * @details    If no such edge exists, @p Const::NONE is returned.
             *
             * @pre        Both @p source and @p target are identifiers of
             *     existing vertices.
             *
             * @param[in]  source  The source vertex @f$\vertexa@f$ of the
             *     edge @f$(\vertexa,\vertexb)@f$.
             * @param[in]  target  The target vertex @f$\vertexb@f$ of the
             *     edge @f$(\vertexa,\vertexb)@f$.
             *
             * @return     The edge identifier, or @p Const::NONE if the edge does not exist.
             */
            inline Types::edgeId EdgeId ( Types::vertexId source
                                        , Types::vertexId target ) const
            {
                USAGE_ASSERT ( VertexExists(source) );
                USAGE_ASSERT ( VertexExists(target) );

                if ( OutDegreeAt(source) <= InDegreeAt(target) ) 
                {
                    for ( Types::edgeId id : outEdgeIds_[source] ) 
                    {
                        if ( EdgeAt(id).Target() == target )
                            return id;
                    }
                } else {
                    for (Types::edgeId id : inEdgeIds_[target]) 
                    {
                        if ( EdgeAt(id).Source() == source )
                            return id;
                    }
                }

                return Const::NONE;
            }

             /**
             * @brief      Searches for an edge @f$(\vertexa, \vertexb)@f$.
             *
             * @pre        Both @p source and @p target are identifiers of existing vertices,
             *             and there is an edge from @p source to @p target.
             *
             * @param[in]  source  The source vertex @f$\vertexa@f$ of the
             *      edge @f$(\vertexa, \vertexb)@f$.
             * @param[in]  target  The target vertex @f$\vertexb@f$ of the
             *      edge @f$(\vertexa, \vertexb)@f$.
             *
             * @return     The edge @f$(\vertexa, \vertexb)@f$.
             */
            inline TEdge & Edge ( Types::vertexId source
                                , Types::vertexId target )
            {
                USAGE_ASSERT ( VertexExists(source) );
                USAGE_ASSERT ( VertexExists(target) );
                Types::edgeId id = EdgeId( source, target );
                USAGE_ASSERT ( id != Const::NONE );

                return EdgeAt( id );
            }

            /**
             * @brief      Searches for an edge @f$(\vertexa, \vertexb)@f$.
             *
             * @pre        Both @p source and @p target are identifiers of existing vertices,
             *             and there is an edge from @p source to @p target.
             *
             * @param[in]  source  The source vertex @f$\vertexa@f$ of the
             *      edge @f$(\vertexa, \vertexb)@f$.
             * @param[in]  target  The target vertex @f$\vertexb@f$ of the
             *      edge @f$(\vertexa, \vertexb)@f$.
             *
             * @return     The edge @f$(\vertexa, \vertexb)@f$.
             */
            inline TEdge const & Edge ( Types::vertexId source
                                      , Types::vertexId target ) const
            {
                USAGE_ASSERT ( VertexExists(source) );
                USAGE_ASSERT ( VertexExists(target) );
                Types::edgeId id = EdgeId( source, target );
                USAGE_ASSERT ( id != Const::NONE );

                return EdgeAt ( id );
            }

            /**
             * @brief      Adds an edge to the set of edges @f$\edges@f$.
             *
             * @pre        Source and target of the edge are existing vertices.
             *
             * @param[in]  source      The source vertex identifier.
             * @param[in]  target      The target vertex identifier.
             * @param      properties  The vertex properties.
             *
             * @return     The edge identifier.
             */
            inline Types::edgeId AddEdge ( Types::vertexId         source,
                                           Types::vertexId         target,
                                           TEdgeProperties const & properties )
            {
                USAGE_ASSERT ( VertexExists(source) );
                USAGE_ASSERT ( VertexExists(target) );
                return AddEdge ( source, target, TEdgeProperties(properties) );
            }

            /**
             * @brief      Adds an edge to the set of edges @f$\edges@f$.
             *
             * @pre        Source and target of the edge are existing vertices.
             *
             * @param[in]  source      The source vertex identifier.
             * @param[in]  target      The target vertex identifier.
             * @param      properties  The vertex properties.
             *
             * @return     The edge identifier.
             */
            inline Types::edgeId AddEdge ( Types::vertexId    source,
                                           Types::vertexId    target,
                                           TEdgeProperties && properties )
            {
                USAGE_ASSERT ( VertexExists(source) );
                USAGE_ASSERT ( VertexExists(target) );

                Types::edgeId id = edges_.size();

                edges_.emplace_back ( id, source, target, std::move(properties) );

                ESSENTIAL_ASSERT ( target < inEdgeIds_.size() );
                ESSENTIAL_ASSERT ( source < outEdgeIds_.size() );
                 inEdgeIds_[target].emplace_back(id);
                outEdgeIds_[source].emplace_back(id);

                ESSENTIAL_ASSERT ( edges_.size() == NumberOfEdges() );

                return id;
            }

            /**
             * @brief      Applies @p function to all edges and collects the
             *     result in a vector.
             *             
             * @param[in]  function  The function that is applied to all edges.
             * @code{.cpp}
             *      TResult function(Types::edgeId, TEdge)
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             *
             * @return     A vector containing the results of the applications
             *             of @p function to all edges.
             */
            template<typename FUNCTION>
            inline auto MapEdges ( FUNCTION function ) const
                    -> std::vector<decltype(function(std::declval<Types::edgeId>(), std::declval<TEdge>()))>
            {
                using TResult = decltype(function(std::declval<Types::edgeId>(), std::declval<TEdge>()));
                std::vector<TResult> result;

                for_all_edge_tuples<ExecutionPolicy::sequential>( 
                    [&]( Types::edgeId id, TEdge const & edge ) 
                    {
                        result.push_back(function(id, edge));
                    }
                );

                return result;
            }

            // Avoid implicit conversions on non-constructing functions
            inline TEdge       & EdgeAt ( int  index )                     = delete;
            inline TEdge       & EdgeAt ( char index )                     = delete;
            inline TEdge const & EdgeAt ( int  index )               const = delete;
            inline TEdge const & EdgeAt ( char index )               const = delete;
            inline Types::edgeId EdgeId ( int  source, int  target ) const = delete;
            inline Types::edgeId EdgeId ( char source, char target ) const = delete;
            inline Types::edgeId EdgeId ( int  source, char target ) const = delete;
            inline Types::edgeId EdgeId ( char source, int  target ) const = delete;
            inline TEdge       & Edge   ( int  source, int  target )       = delete;
            inline TEdge       & Edge   ( char source, char target )       = delete;
            inline TEdge       & Edge   ( char source, int  target )       = delete;
            inline TEdge       & Edge   ( int  source, char target )       = delete;
            inline TEdge const & Edge   ( int  source, int  target ) const = delete;
            inline TEdge const & Edge   ( char source, char target ) const = delete;
            inline TEdge const & Edge   ( int  source, char target ) const = delete;
            inline TEdge const & Edge   ( char source, int  target ) const = delete;
        ///@}

        /// @name Graph Properties
        /// @{
#pragma mark GRAPH_PROPERTIES
            /**
             * @brief      The minimum degree of the graph @f$\graph@f$.
             * @details    The minimum number of edges incident to any vertex
             *     in the graph. If the graph is empty, 0 is returned.
             *
             * @param      id    The vertex identifier with the minimum
             *     degree. If there are multiple vertices with the minimum
             *     degree, the one with the smallest identifier is returned.
             *     If the graph is empty, @p id is set to Const::NONE.
             *
             * @return     The minimum degree.
             */
            inline Types::count MinDegree ( Types::vertexId & id ) const
            {
                if (NumberOfVertices() == 0) 
                {
                    id = Const::NONE;
                    return 0;
                }
                auto result = std::min_element( vertices_.begin()
                                              , vertices_.end()
                    , [this]( TVertex const & left, TVertex const & right) 
                    {
                        return DegreeAt(left.Identifier()) < DegreeAt(right.Identifier());
                    }
                );
                id = result->Identifier();
                return DegreeAt(id);
            }

            /**
             * @brief      The minimum degree of the graph @f$\graph@f$.
             * @details    The minimum number of edges incident to any vertex
             *             in the graph. If the graph is empty, 0 is returned.
             *
             * @return     The minimum degree.
             */
            inline Types::count MinDegree() const
            {
                Types::vertexId dummy = 0;
                return MinDegree(dummy);
            }

            /**
             * @brief      The maximum degree of the graph @f$\graph@f$.
             * @details    The maximum number of edges incident to any vertex
             *             in the graph. If the graph is empty, 0 is returned.
             *
             * @param[in/out]   id  The vertex identifier with the maximum
             *                      degree. If there are multiple vertices
             *                      with the maximum degree, the one with the
             *                      smallest identifier is returned. If the
             *                      graph is empty, @p id is set to
             *                      Const::NONE.
             *
             * @return     The maximum degree.
             */
            inline Types::count MaxDegree ( Types::vertexId & id ) const
            {
                if (NumberOfVertices() == 0) 
                {
                    id = Const::NONE;
                    return 0;
                }
                auto result = std::max_element ( vertices_.begin()
                                               , vertices_.end()
                    , [this](const TVertex & left, TVertex const & right) 
                    {
                        return DegreeAt(left.Identifier()) < DegreeAt(right.Identifier());
                    }
                );
                id = result->Identifier();
                return DegreeAt(id);
            }

            /**
             * @brief      The maximum degree of the graph @f$\graph@f$.
             * @details    The maximum number of edges incident to any vertex
             *             in the graph. If the graph is empty, 0 is returned.
             *
             * @return     The maximum degree.
             */
            inline Types::count MaxDegree() const
            {
                Types::vertexId dummy = 0;
                return MaxDegree(dummy);
            }
        /// @}

        /// @name Output
        /// @{
#pragma mark OUTPUT

            /**
             * @brief      Dumps buses.
             *
             * @param      outputStream  The stream to write data to
             */
            inline void DumpBuses ( std::ostream & outputStream ) const
            {
                TVertexProperties::Header(outputStream);
                for_all_vertices<ExecutionPolicy::sequential> (
                    [&]( TVertex const & u )
                    { 
                        u.Properties().Line( outputStream ); 
                    }
                );
            }

            /**
             * @brief      Dumps branches.
             *
             * @param      outputStream  The stream to write data to
             */
            inline void DumpBranches ( std::ostream & outputStream ) const
            {
                TEdgeProperties::Header(outputStream);
                for_all_edges<ExecutionPolicy::sequential>(
                    [&]( TEdge const & e )
                    { 
                        e.Properties().Line( outputStream
                                           , VertexAt(e.Source()).Properties().Name()
                                           , VertexAt(e.Target()).Properties().Name() ); 
                    }
                );
            }

            /**
             * @brief      Write the static graph to an output stream.
             *
             * @param      outputStream  The stream to write data to, e.g., std::cout.
             * @param      rhs           The right hand side static graph.
             *
             * @return     The output stream.
             */
            friend std::ostream & operator<< ( std::ostream      & outputStream
                                             , StaticGraph const & rhs )
            {
                outputStream << std::string('-', 20);

                outputStream << "\nBuses\n"       << std::string(7, '-')  << "\n";
                rhs.DumpBuses(outputStream);

                outputStream << "\nBranches\n"    << std::string(9, '-')  << "\n";
                rhs.DumpBranches(outputStream);

                outputStream << "\nMinDegree: " << rhs.MinDegree() << "\n";
                outputStream << "MaxDegree: "   << rhs.MaxDegree() << "\n";

                return outputStream;
            }
        /// @}

        /// @name Vertex Loops
        /// @{
#pragma mark VERTEX_LOOPS
            /**
             * @brief      The @p for loop over all vertex identifiers in the
             *     graph.
             *
             * @param[in]  function  The function object that is called for
             *                       all vertices. It must accept one argument
             *                       of type @p Types::vertexId, e.g.,
             * @code{.cpp}
             *      for_all_vertex_identifiers (
             *          []( Types::vertexId vertexId ) 
             *          { 
             *              // Do something with the vertex identifier.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy   The execution policy.
             * @tparam     FUNCTION The type of the function object.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline 
            void for_all_vertex_identifiers ( FUNCTION function ) const
            {
                internal::StaticGraphLoopDifferentiation<TGraph const, Policy>
                    ::for_all_vertex_identifiers ( *this, function );
            }
        
            /**
             * @brief      The @p for loop over all vertex objects in the graph.
             *
             * @param[in]  function  The function object that is called for
             *                       all vertices. It must accept one argument
             *                       of type @p TVertex, e.g.,
             * @code{.cpp}
             *      for_all_vertices (
             *          []( TVertex & vertex ) 
             *          { 
             *              // Do something with the vertex object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy   The execution policy.
             * @tparam     FUNCTION The type of the function object.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline 
            void for_all_vertices ( FUNCTION function )
            {
                internal::StaticGraphLoopDifferentiation<TGraph, Policy>
                    ::for_all_vertices ( *this, function );
            }

            /**
             * @brief      The @p for loop over all vertex objects in the graph.
             *
             * @param[in]  function  The function object that is called for
             *                       all vertices. It must accept one argument
             *                       of type @p TVertex, e.g.,
             * @code{.cpp}
             *      for_all_vertices (
             *          []( TVertex const & vertex ) 
             *          { 
             *              // Do something with the vertex object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy   The execution policy.
             * @tparam     FUNCTION The type of the function object.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline 
            void for_all_vertices ( FUNCTION function ) const
            {
                internal::StaticGraphLoopDifferentiation<TGraph const, Policy>
                    ::for_all_vertices ( *this, function );
            }

            /**
             * @brief      The @p for loop over all pairs of vertex
             *             identifiers and vertex objects in the graph.
             *
             * @param[in]  function  The function object that is called for
             *                       all vertices. It must accept two
             *                       arguments of types @p Types::vertexId and
             *                       @p TVertex, e.g.,
             * @code{.cpp}
             *      for_all_vertex_tuples (
             *          []( Types::vertexId id, TVertex const & vertex ) 
             *          { 
             *              // Do something with the vertex identifier and object 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy   The execution policy.
             * @tparam     FUNCTION The type of the function object.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline 
            void for_all_vertex_tuples ( FUNCTION function )
            {
                internal::StaticGraphLoopDifferentiation<TGraph, Policy>
                    ::for_all_vertex_tuples ( *this, function );
            }

            /**
             * @brief      The @p for loop over all pairs of vertex identifiers and vertex objects
             *             in the graph.
             *
             * @param[in]  function  The function object that is called for all vertices.
             *                       It must accept two arguments of types @p Types::vertexId
             *                       and @p TVertex, e.g.,
             * @code{.cpp}
             *      for_all_vertex_tuples (
             *          []( Types::vertexId id, TVertex const & vertex ) 
             *          { 
             *              // Do something with the vertex identifier and object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy   The execution policy.
             * @tparam     FUNCTION The type of the function object.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline 
            void for_all_vertex_tuples ( FUNCTION function ) const 
            {
                internal::StaticGraphLoopDifferentiation<TGraph const, Policy>
                    ::for_all_vertex_tuples ( *this, function );
            }
        ///@}

        /// @name Edge Loops
        /// @{
#pragma mark EDGE_LOOPS
            /**
             * @brief      The @p for loop over all identifiers of edges in
             *     the graph.
             *
             * @param[in]  function  The function object that is called for
             *                       all edges. It must accept one argument of
             *                       type @p Types::edgeId, e.g.,
             * @code{.cpp}
             *      for_all_edge_identifiers (
             *          []( Types::edgeId edgeId ) 
             *          { 
             *              // Do something with the edge identifier.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy   The execution policy.
             * @tparam     FUNCTION The type of the function object.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline
            void for_all_edge_identifiers ( FUNCTION function ) const
            {
                internal::StaticGraphLoopDifferentiation<TGraph const, Policy>
                    ::for_all_edge_identifiers ( *this, function );
            }

            /**
             * @brief      The @p for loop over all edges in the graph.
             *
             * @param[in]  function  The function object that is called for
             *                       all edges. It must accept one argument of
             *                       type @p TEdge, e.g.,
             * @code{.cpp}
             *      for_all_edges (
             *          []( TEdge & edge ) 
             *          { 
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy   The execution policy..
             * @tparam     FUNCTION The type of the function object.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline 
            void for_all_edges ( FUNCTION function )
            {
                internal::StaticGraphLoopDifferentiation<TGraph, Policy>
                    ::for_all_edges ( *this, function );
            }

            /**
             * @brief      The @p for loop over all edges in the graph.
             *
             * @param[in]  function  The function object that is called for all edges.
             *                       It must accept one argument of type @p TEdge,
             *                       e.g.,
             * @code{.cpp}
             *      for_all_edges (
             *          []( TEdge const & edge ) 
             *          { 
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy   The execution policy.
             * @tparam     FUNCTION The type of the function object.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline 
            void for_all_edges ( FUNCTION function ) const
            {
                internal::StaticGraphLoopDifferentiation<TGraph const, Policy>
                    ::for_all_edges ( *this, function );
            }

            /**
             * @brief      The @p for loop over all pairs of edge identifiers
             *     and edge objects in the graph.
             *
             * @param[in]  function  The function object that is called for
             *                       all edges. It must accept two arguments
             *                       of types @p Types::edgeId and @p TEdge,
             *                       e.g.,
             * @code{.cpp}
             *      for_all_edge_tuples (
             *          []( Types::edgeId edgeId, TEdge & edge ) 
             *          { 
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy   The execution policy.
             * @tparam     FUNCTION The type of the function object.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline 
            void for_all_edge_tuples ( FUNCTION function )
            {
                internal::StaticGraphLoopDifferentiation<TGraph, Policy>
                    ::for_all_edge_tuples ( *this, function );
            }

            /**
             * @brief      The @p for loop over all pairs of edge identifiers
             *     and edge objects in the graph.
             *
             * @param[in]  function  The function object that is called for
             *                       all edges. It must accept two arguments
             *                       of types @p Types::edgeId and @p TEdge,
             *                       e.g.,
             * @code{.cpp}
             *      for_all_edge_tuples ( 
             *          []( Types::edgeId edgeId, TEdge const & edge ) 
             *          { 
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy   The execution policy.
             * @tparam     FUNCTION The type of the function object.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline 
            void for_all_edge_tuples ( FUNCTION function ) const
            {
                internal::StaticGraphLoopDifferentiation<TGraph const, Policy>
                    ::for_all_edge_tuples ( *this, function );
            }
        /// @}

        /// @name Neighborhood Loops
        /// @{
#pragma mark NEIGHBORHOOD_LOOPS
            /**
             * @brief      The @p for loop over all edges at a vertex object.
             * @details    This is a loop over incoming and outgoing edges.
             *
             * @param[in]  vertex    The vertex object
             * @param[in]  function  The function object that is called for all edges at
             *                       the vertex. It must accept one argument of type
             *                       @p TEdge, e.g.,
             * @code{.cpp}
             *      for_all_edges_at<ExecutionPolicy::sequential>( vertex
             *          , []( TEdge & edge ) 
             *          { 
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy    The execution policy.
             * @tparam     FUNCTION  The function object that is called for
             *     all incident edges at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline 
            void for_all_edges_at ( TVertex const & vertex
                                  , FUNCTION        function )
            {
                internal::StaticGraphLoopDifferentiation<TGraph, Policy>
                    ::for_all_edges_at ( *this, vertex, function );
            }

            /**
             * @brief      The @p for loop over all edges at a vertex object.
             * @details    This is a loop over incoming and outgoing edges.
             *
             * @param[in]  vertex    The vertex object
             * @param[in]  function  The function object that is called for all edges at
             *                       the vertex. It must accept one argument of type
             *                       @p TEdge, e.g.,
             * @code{.cpp}
             *      for_all_edges_at<ExecutionPolicy::sequential>( vertex
             *          , []( TEdge const & edge ) 
             *          { 
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy    The execution policy.
             * @tparam     FUNCTION  The function object that is called for
             *     all incident edges at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline 
            void for_all_edges_at ( TVertex const & vertex
                                  , FUNCTION        function ) const
            {
                internal::StaticGraphLoopDifferentiation<TGraph const, Policy>
                    ::for_all_edges_at ( *this, vertex, function );
            }

            /**
             * @brief      The @p for loop over all edges at a vertex.
             * @details    This is a loop over incoming and outgoing edges.
             *
             * @pre        There is a vertex with identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param[in]  function  The function object that is called for all edges at
             *                       the vertex. It must accept one argument of type
             *                       @p TEdge, e.g.,
             * @code{.cpp}
             *      for_all_edges_at ( vertexId
             *          , []( TEdge & edge ) 
             *          { 
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy   The execution policy.
             * @tparam     FUNCTION  The function object that is called for
             *     all incident edges at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline 
            void for_all_edges_at ( Types::vertexId const vertexId
                                  , FUNCTION              function )
            {
                USAGE_ASSERT( VertexExists(vertexId) );
                internal::StaticGraphLoopDifferentiation<TGraph, Policy>
                    ::for_all_edges_at ( *this, vertexId, function );
            }

            /**
             * @brief      The @p for loop over all edges at a vertex.
             * @details    This is a loop over incoming and outgoing edges.
             *
             * @pre        There is a vertex with identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param[in]  function  The function object that is called for all edges at
             *                       the vertex. It must accept one argument of type
             *                       @p TEdge, e.g.,
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
             * @tparam     Policy   The execution policy.
             * @tparam     FUNCTION  The function object that is called for
             *     all incident edges at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline 
            void for_all_edges_at ( Types::vertexId const vertexId
                                  , FUNCTION              function ) const
            {
                USAGE_ASSERT( VertexExists(vertexId) );
                internal::StaticGraphLoopDifferentiation<TGraph const, Policy>
                    ::for_all_edges_at ( *this, vertexId, function );
            }

            /**
             * @brief      The @p for loop over all incoming edges of a vertex.
             *
             * @param[in]  vertex    The vertex object.
             * @param[in]  function  The function object that is called for all incoming
             *                       edges at the vertex. It must accept one argument of
             *                       type @p TEdge, e.g.,
             * @code{.cpp}
             *      for_all_edges_at ( vertex
             *          , []( TEdge const & edge ) 
             *          { 
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy    The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION  The function object that is called for
             *     all incident incoming edges at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline
            void for_in_edges_at ( TVertex const & vertex
                                 , FUNCTION        function )
            {
                internal::StaticGraphLoopDifferentiation<TGraph, Policy>
                    ::for_in_edges_at ( *this, vertex, function );
            }

            /**
             * @brief      The @p for loop over all incoming edges of a vertex.
             *
             * @param[in]  vertex    The vertex object
             * @param[in]  function  The function object that is called for all incoming
             *                       edges at the vertex. It must accept one argument of
             *                       type @p TEdge, e.g.,
             * @code{.cpp}
             *      for_in_edges_at ( vertex
             *          , []( TEdge const & edge ) 
             *          { 
             *              // Do something with the edge object.
             *          }
             *      );    
             * @endcode
             *
             * @tparam     Policy    The execution policy.
             * @tparam     FUNCTION  The function object that is called for
             *     all incoming edges at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline
            void for_in_edges_at ( TVertex const & vertex
                                 , FUNCTION        function ) const
            {
                internal::StaticGraphLoopDifferentiation<TGraph const, Policy>
                    ::for_in_edges_at ( *this, vertex, function );
            }

            /**
             * @brief      The @p for loop over all incoming edges of a vertex.
             *
             * @pre        There is a vertex with identifier @p vertexId.
             *
             * @param[in]  vertexId  The identifier of the vertex
             * @param[in]  function  The function object that is called for all incoming
             *                       edges at the vertex. It must accept one argument of
             *                       type @p TEdge, e.g.,
             * @code{.cpp}
             *      for_in_edges_at ( vertexId
             *          , []( TEdge & edge ) 
             *          { 
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy    The execution policy.
             * @tparam     FUNCTION  The function object that is called for all incoming edges at @p vertexId
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline
            void for_in_edges_at ( Types::vertexId vertexId
                                 , FUNCTION        function )
            {
                USAGE_ASSERT( VertexExists(vertexId) );
                internal::StaticGraphLoopDifferentiation<TGraph, Policy>
                    ::for_in_edges_at ( *this, vertexId, function );
            }

            /**
             * @brief      The @p for loop over all incoming edges of a vertex.
             *
             * @pre        There is a vertex with identifier @p vertexId.
             *
             * @param[in]  vertexId  The identifier of the vertex
             * @param[in]  function  The function object that is called for all incoming
             *                       edges at the vertex. It must accept one argument of
             *                       type @p TEdge, e.g.,
             * @code{.cpp}
             *      for_in_edges_at ( vertexId
             *          , []( TEdge const & edge ) 
             *          { 
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy   The execution policy.
             * @tparam     FUNCTION  The function object that is called for all incoming edges at @p vertexId
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline
            void for_in_edges_at ( Types::vertexId vertexId
                                 , FUNCTION        function ) const
            {
                USAGE_ASSERT( VertexExists(vertexId) );
                internal::StaticGraphLoopDifferentiation<TGraph const, Policy>
                    ::for_in_edges_at ( *this, vertexId, function );
            }

            /**
             * @brief      The @p for loop over all outgoing edges of a vertex
             *
             * @param[in]  vertex    The vertex object.
             * @param[in]  function  The function object that is called for all outgoing
             *                       edges at the vertex. It must accept one argument of
             *                       type @p TEdge, e.g.,
             * @code{.cpp}
             *      for_out_edges_at ( vertex
             *          , []( TEdge & edge ) 
             *          { 
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy    The execution policy
             * @tparam     FUNCTION  The function object that is called for all outgoing edges of @p vertex
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline
            void for_out_edges_at ( TVertex const & vertex
                                  , FUNCTION        function )
            {
                internal::StaticGraphLoopDifferentiation<TGraph, Policy>
                    ::for_out_edges_at ( *this, vertex, function );
            }

            /**
             * @brief      The @p for loop over all outgoing edges of a vertex
             *
             * @param[in]  vertex    The vertex object.
             * @param[in]  function  The function object that is called for all outgoing
             *                       edges at the vertex. It must accept one argument of
             *                       type @p TEdge, e.g.,
             * @code{.cpp}
             *      for_out_edges_at ( vertex
             *          , []( TEdge const & edge ) 
             *          { 
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy   The execution policy.
             * @tparam     FUNCTION  The function object that is called for all outgoing edges of @p vertex
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline
            void for_out_edges_at ( TVertex const & vertex
                                  , FUNCTION        function ) const
            {
                internal::StaticGraphLoopDifferentiation<TGraph const, Policy>
                    ::for_out_edges_at ( *this, vertex, function );
            }

             /**
             * @brief      The @p for loop over all outgoing edges.
             *
             * @pre        There is a vertex with identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param[in]  function  The function object that is called for
             *                       all outgoing edges at the vertex. It must
             *                       accept one argument of type @p TEdge,
             *                       e.g.,
             * @code{.cpp}
             *      for_out_edges_at ( vertexId
             *          , []( TEdge & edge ) 
             *          { 
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy   The execution policy.
             * @tparam     FUNCTION  The function object that is called for
             *     all outgoing edges of @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline
            void for_out_edges_at( Types::vertexId vertexId
                                 , FUNCTION        function )
            {
                USAGE_ASSERT( VertexExists(vertexId) );
                internal::StaticGraphLoopDifferentiation<TGraph, Policy>
                    ::for_out_edges_at ( *this, vertexId, function );
            }

            /**
             * @brief      The @p for loop over all outgoing edges.
             *
             * @pre        There is a vertex with identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param[in]  function  The function object that is called for
             *                       all outgoing edges at the vertex. It must
             *                       accept one argument of type @p TEdge,
             *                       e.g.,
             * @code{.cpp}
             *      for_out_edges_at ( vertexId
             *          []( TEdge const & edge ) 
             *          { 
             *              // Do something with the edge object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy   The execution policy.
             * @tparam     FUNCTION  The function object that is called for
             *     all outgoing edges of @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
            inline 
            void for_out_edges_at( Types::vertexId vertexId
                                 , FUNCTION        function ) const
            {
                USAGE_ASSERT( VertexExists(vertexId) );
                internal::StaticGraphLoopDifferentiation<TGraph const, Policy>
                    ::for_out_edges_at ( *this, vertexId, function );
            }
        ///@}

#pragma mark MEMBERS
    private:
        Types::name                                     name_;              /**< Name of the graph, e.g., bus14 */

        std::vector<TVertex>                            vertices_;          /**< Vector of vertices */

        std::vector<TEdge>                              edges_;             /**< Vector of edges */

        std::vector< std::vector<Types::edgeId> >       inEdgeIds_;         /**< Ids of the incoming edges per vertex */
        std::vector< std::vector<Types::edgeId> >       outEdgeIds_;        /**< Ids of the outgoing edges per vertex */
};

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__GRAPHS__STATIC_GRAPH_HPP
 
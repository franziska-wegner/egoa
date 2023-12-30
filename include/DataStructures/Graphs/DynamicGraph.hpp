/*
 * DynamicGraph.hpp
 *
 *  Created on: Nov 04, 2018
 *      Author: Franziska Wegner, Matthias Wolf
 */

#ifndef EGOA__DATA_STRUCTURES__GRAPHS__DYNAMIC_GRAPH_HPP
#define EGOA__DATA_STRUCTURES__GRAPHS__DYNAMIC_GRAPH_HPP

#include <algorithm>
#include <type_traits>

#include "Auxiliary/Constants.hpp"
#include "Auxiliary/Types.hpp"

#include "DataStructures/Iterators/DynamicGraphIterators.hpp"

#include "Exceptions/Assertions.hpp"

#include "DataStructures/Graphs/Edges/Edge.hpp"
#include "DataStructures/Graphs/Vertices/Vertex.hpp"
#include "DataStructures/Iterators/OmittingIterator.hpp"

namespace egoa {

/**
 * @brief      A graph data structure that supports adding and removing vertices
 *             and edges.
 * @details    Both @p VertexProperties and @p EdgeProperties must be able to store an
 *             identifier, which can be accessed in the following way. Here, @p vertex and
 *             @p constVertex are objects of type @p VertexProperties and @p VertexProperties @p const,
 *             respectively, and @p vId is of type @p Types::vertexId.
 *             Similarly, @p edge and @p constEdge are objects of type @p EdgeProperties and
 *             @p EdgeProperties @p const, respectively, and @p eId is of type @p Types::edgeId.
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
 * @tparam     VertexProperties  The type of the vertices.
 * @tparam     EdgeProperties    The type of the edges.
 */
template <typename VertexProperties, typename EdgeProperties>
class DynamicGraph {
    template<typename ElementType, bool Const> class OmittingVectorView;
public:

    // Template type aliasing
    using TGraph             = DynamicGraph<VertexProperties, EdgeProperties>;
    // Vertices
    using TVertexProperties  = VertexProperties;
    using TVertex            = Vertices::Vertex<TVertexProperties>;
    using TVertexId          = Types::vertexId;
    // Edges
    using TEdgeProperties    = EdgeProperties;
    using TEdge              = Edges::Edge<TEdgeProperties>;
    using TEdgeId            = Types::edgeId;
    //
    using TVerticesView      = OmittingVectorView<TVertex, false>;
    using TConstVerticesView = OmittingVectorView<TVertex, true>;
    using TEdgesView         = OmittingVectorView<TEdge, false>;
    using TConstEdgesView    = OmittingVectorView<TEdge, true>;

    /**
     * @brief      The constructor.
     *
     * @param[in]  name  The name of the graph. The default value is "".
     */
    explicit DynamicGraph(Types::name name = "")
    : name_(std::move(name))
    {}

    ///@name Getter and setter
    ///@{
#pragma mark SETTER_AND_GETTER
        /**
         * @brief      The name of the graph.
         */
        inline Types::name  Name()             const  { return name_; }
        /**
         * @brief      The number of vertices @f$n = |\vertices|@f$ in the graph.
         */
        inline Types::count NumberOfVertices() const  { return numberOfVertices_; }
        /**
         * @brief      The number of edges @f$m = |\edges|@f$ in the graph.
         */
        inline Types::count NumberOfEdges()    const  { return numberOfEdges_; }
    ///@}

    /**@name Vertex related methods */
    ///@{
#pragma mark VERTEX_RELATED_METHODS
        /**
         * @brief      A view on the vertices.
         * @details    The vertices can be modified via this view.
         *
         *             If a vertex is added or removed, the view is still valid but
         *             the iterators obtained via this view are invalid.
         *
         *             If the graph is destroyed, all views are invalid and calling
         *             member functions on them has undefined behavior.
         */
        inline TVerticesView Vertices()
        {
            return TVerticesView ( & vertices_
                                 , & vertexExists_
                                 , & numberOfVertices_ );
        }

        /**
         * @brief      A view on the vertices.
         * @details    The vertices cannot be modified via this view.
         *
         *             If a vertex is added or removed, the view is still valid but
         *             the iterators obtained via this view are invalid.
         *
         *             If the graph is destroyed, all views are invalid and calling
         *             member functions on them has undefined behavior.
         */
        inline TConstVerticesView Vertices() const
        {
            return TConstVerticesView ( & vertices_
                                      , & vertexExists_
                                      , & numberOfVertices_ );
        }

        /**
         * @brief      Whether a vertex with identifier @p id exists in the graph.
         *
         * @param[in]  id  The identifier of the vertex.
         *
         * @return     @p true if a vertex with identifier @p id exists,
         *             @p false otherwise.
         */
        inline bool  VertexExists ( Types::vertexId id ) const
        {
            return id < vertexExists_.size() && vertexExists_[id];
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
        inline       TVertex & VertexAt ( int  id )       = delete;
        inline       TVertex & VertexAt ( char id )       = delete;
        inline const TVertex & VertexAt ( int  id ) const = delete;
        inline const TVertex & VertexAt ( char id ) const = delete;

        /**
         * @brief      The vertex identifier of a vertex object.
         * @details    Calls @p vertex.Identifier().
         *
         * @param      vertex  The vertex.
         *
         * @return     The vertex identifier.
         */
        inline Types::vertexId VertexId ( TVertex const & vertex ) const
        {
            return vertex.Identifier();
        }

        /**
         * @brief      Adds a vertex.
         * @details    The identifier of the vertex passed as argument
         *             is set to the identifier of the vertex in the graph.
         *
         * @param      properties  The vertex properties.
         *
         * @return     The identifier of the vertex.
         */
        inline Types::vertexId AddVertex ( TVertexProperties & properties )
        {
            return AddVertex ( TVertexProperties(properties) );
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
            return AddVertex ( TVertexProperties(properties) );
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
            // TODO: Find a free place in the vector if it exists.
            auto id = vertices_.size();

            vertices_.emplace_back(id, std::move(properties));

            vertexExists_.push_back(true);
            ++numberOfVertices_;

            inEdgeIds_.emplace_back();
            outEdgeIds_.emplace_back();

            return id;
        }

        // TODO: maybe write EmplaceVertex?

        /**
         * @brief      Remove a vertex and all incident edges.
         *
         * @pre        There is a vertex with identifier @p id in the graph.
         *
         * @param      id The identifier of the vertex to remove.
         */
        inline void RemoveVertexAt ( Types::vertexId id )
        {
            USAGE_ASSERT ( VertexExists(id) );

            RemoveAllIncidentEdgesAt(id);

            vertexExists_[id] = false;
            --numberOfVertices_;
        }

        /**
         * @brief      Applies @p function to all vertices and collects the result in a vector.
         *
         * @param[in]  function  The function that is applied to all edges.
         *                       @code
         *                       TResult function(Types::vertexId, TVertex)
         *                       @endcode
         *
         * @tparam     FUNCTION  The type of the function object.
         *
         * @return     A vector containing the results of the applications of @p function
         *             to all vertices.
         */
        template<typename FUNCTION>
        inline auto MapVertices ( FUNCTION function ) const
                -> std::vector<decltype(function(std::declval<Types::vertexId>(), std::declval<TVertex>()))>
        {
            using TResult = decltype(function(std::declval<Types::vertexId>(), std::declval<TVertex>()));
            std::vector<TResult> result;

            for_all_vertex_tuples<ExecutionPolicy::sequential>(
                [&]( Types::vertexId id, TVertex const & vertex )
                {
                    result.push_back ( function(id, vertex) );
                }
            );

            return result;
        }

        /**
         * @brief      Neighbors of a vertex.
         * @details    A vector containing the identifiers of the neighbors of
         *             the given vertex is returned. The order of the
         *             neighbors is unspecified.
         *
         * @pre        There is a vertex with identifier @p id in the graph.
         *
         * @param[in]  id  The id of a vertex
         *
         * @return     The vertex identifiers of all neighbors.
         */
        inline std::vector<Types::vertexId> NeighborsOf ( Types::vertexId id ) const
        {
            USAGE_ASSERT ( VertexExists(id) );

            std::vector<Types::vertexId> result;
            NeighborsOf(id, result);
            return result;
        }

        /**
         * @brief      Neighbors of a vertex.
         * @details    The neighbors of the vertex are appended to the vector
         *             @p vertexId. The order of the neighbors is unspecified.
         *
         *             Time complexity: @f$O(|\vertices|)@f$.
         *
         * @pre        There is a vertex with identifier @p id in the graph.
         *
         * @param[in]  id  The vertex identifier.
         * @param      vertexIds  The vector to which the identifiers of the
         *     neighbors are appended.
         */
        inline void NeighborsOf ( Types::vertexId                id
                                , std::vector<Types::vertexId> & vertexIds ) const
        {
            USAGE_ASSERT ( VertexExists(id) );

            std::vector<bool> vertexVisited(vertices_.size(), false);

            for (Types::edgeId edgeId : OutEdgeIdsAt(id)) {
                Types::vertexId otherVertex = EdgeAt(edgeId).Target();
                if (!vertexVisited[otherVertex]) {
                    vertexIds.push_back(otherVertex);
                    vertexVisited[otherVertex] = true;
                }
            }
            for (Types::edgeId edgeId : InEdgeIdsAt(id)) {
                Types::vertexId otherVertex = EdgeAt(edgeId).Source();
                if (!vertexVisited[otherVertex]) {
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
         * @brief      All edge identifiers of edges incident to a
         *             vertex are added to the end of the vector @p edgeIds.
         * @details    The order of the identifiers is unspecified.
         *
         * @pre        There is a vertex with identifier @p id in the graph.
         *
         * @param[in]  id    The vertex id
         * @param      edgeIds  The vector to which the edge identifiers are appended.
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

    ///@}

    /**@name Edge Related Methods */
    ///@{
#pragma mark EDGE_RELATED_METHODS

        /**
         * @brief      A view on the edges.
         * @details    The edges can be modified via this view.
         *
         *             If an edge is added or removed, the view is still valid but
         *             the iterators obtained via this view are invalid.
         *
         *             If the graph is destroyed, all views are invalid and calling
         *             member functions on them has undefined behavior.
         */
        inline TEdgesView Edges()
        {
            return TEdgesView ( & edges_
                              , & edgeExists_
                              , & numberOfEdges_ );
        }

         /**
         * @brief      A view on the edges.
         * @details    The edges cannot be modified via this view.
         *
         *             If an edge is added or removed, the view is still valid but
         *             the iterators obtained via this view are invalid.
         *
         *             If the graph is destroyed, all views are invalid and calling
         *             member functions on them has undefined behavior.
         */
        inline TConstEdgesView Edges() const
        {
            return TConstEdgesView ( & edges_
                                   , & edgeExists_
                                   , & numberOfEdges_ );
        }

        /**
         * @brief      Whether an edge with identifier @p id exists.
         * @details    Time complexity: @f$O(1)@f$.
         *
         * @param[in]  id  The edge identifier.
         *
         * @return     @p true if an edge with identifier @p id exists,
         *             @p false otherwise.
         */
        inline bool EdgeExists ( Types::edgeId id ) const
        {
            return id < edgeExists_.size() && edgeExists_[id];
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
         * @brief      Searches for the identifier of the edge @f$(\vertexa,
         *     \vertexb)@f$.
         * @details    If no such edge exists, @p Const::NONE is returned.
         *
         * @pre        Both @p source and @p target are identifiers of existing vertices.
         *
         * @param[in]  source  The source vertex @f$\vertexa@f$ of the edge
         *     @f$(\vertexa,\vertexb)@f$.
         * @param[in]  target  The target vertex @f$\vertexb@f$ of the edge
         *     @f$(\vertexa,\vertexb)@f$.
         *
         * @return     The edge identifier, or @p Const::NONE if the edge does
         *     not exist.
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
         * @pre        Both @p source and @p target are identifiers of
         *             existing vertices, and there is an edge from @p source
         *             to @p target.
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
         * @pre        Both @p source and @p target are identifiers of
         *             existing vertices, and there is an edge from @p source
         *             to @p target.
         *
         * @param[in]  source  The source vertex @f$\vertexa@f$ of the
         *      edge @f$(\vertexa, \vertexb)@f$.
         * @param[in]  target  The target vertex @f$\vertexb@f$ of the
         *      edge @f$(\vertexa, \vertexb)@f$.
         *
         * @return     The edge @f$(\vertexa, \vertexb)@f$.
         */
        inline const TEdge & Edge ( Types::vertexId source
                                  , Types::vertexId target ) const
        {
            USAGE_ASSERT ( VertexExists(source) );
            USAGE_ASSERT ( VertexExists(target) );
            Types::edgeId id = EdgeId( source, target );
            USAGE_ASSERT ( id != Const::NONE );

            return EdgeAt( id );
        }

        /**
         * @brief      Adds an edge to the set of edges @f$\edges@f$.
         * @details    The identifier of the edge passed as argument
         *             is set to the ID of the edge in the graph.
         *
         * @pre        Source and target of the edge are existing vertices.
         *
         * @param      edge  The edge object.
         *
         * @return     The edge identifier.
         */
        inline Types::edgeId AddEdge ( Types::vertexId   source
                                     , Types::vertexId   target
                                     , TEdgeProperties & properties )
        {
            USAGE_ASSERT( VertexExists( source ) );
            USAGE_ASSERT( VertexExists( target ) );
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
        inline Types::edgeId AddEdge ( Types::vertexId         source
                                     , Types::vertexId         target
                                     , TEdgeProperties const & properties )
        {
            USAGE_ASSERT( VertexExists(source) );
            USAGE_ASSERT( VertexExists(target) );
            return AddEdge( source, target, TEdgeProperties(properties) );
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
        inline Types::edgeId AddEdge ( Types::vertexId    source
                                     , Types::vertexId    target
                                     , TEdgeProperties && properties )
        {
            USAGE_ASSERT ( VertexExists(source) );
            USAGE_ASSERT ( VertexExists(target) );

            // TODO: Find empty slot instead of always adding to the end?
            Types::edgeId edgeId = edges_.size();
            edges_.emplace_back(edgeId, source, target, std::move(properties));

            edgeExists_.emplace_back(true);
            ++numberOfEdges_;

            ESSENTIAL_ASSERT ( edgeExists_.size() == edges_.size() );
            ESSENTIAL_ASSERT ( numberOfEdges_     <= edges_.size() );

            ESSENTIAL_ASSERT ( source < outEdgeIds_.size() );
            ESSENTIAL_ASSERT ( target < inEdgeIds_.size()  );

            outEdgeIds_[source].push_back(edgeId);
            inEdgeIds_[target].push_back(edgeId);

            return edgeId;
        }

        /**
         * @brief      Removes the edge with identifier @p id.
         *
         * @pre        There is an edge with identifier @p id in the graph.
         *
         * @param      id  The identifier of the edge.
         */
        inline void RemoveEdgeAt ( Types::edgeId id )
        {
            USAGE_ASSERT( EdgeExists(id) );
            // remove edge
            Types::vertexId source = EdgeAt(id).Source();
            Types::vertexId target = EdgeAt(id).Target();

            //edges_.erase( edges_.begin() + id );
            edgeExists_[id] = false;
            --numberOfEdges_;

            //in/out edges
            auto iteratorIn = std::find( inEdgeIds_[target].begin(), inEdgeIds_[target].end(), id );
            auto iteratorOut = std::find( outEdgeIds_[source].begin(), outEdgeIds_[source].end(), id );
            inEdgeIds_[target].erase( iteratorIn );
            outEdgeIds_[source].erase( iteratorOut );
        }

        /**
         * @brief      Removes all incident edges at the vertex with identifier @p id.
         *
         * @pre        There is a vertex with identifier @p id in the graph.
         *
         * @param      id  The identifier of the vertex.
         */
        inline void RemoveAllIncidentEdgesAt ( Types::vertexId id )
        {
            USAGE_ASSERT ( VertexExists(id) );

            using std::begin, std::end;

            for (Types::edgeId edgeId : inEdgeIds_[id])
            {
                ESSENTIAL_ASSERT( EdgeExists(edgeId) );

                Types::vertexId other = EdgeAt(edgeId).Source();
                auto & edgesAtOther = outEdgeIds_[other];
                auto it = std::find( begin(edgesAtOther), end(edgesAtOther), edgeId );
                ESSENTIAL_ASSERT( it != end(edgesAtOther) );
                edgesAtOther.erase(it);

                edgeExists_[edgeId] = false;
            }

            for (Types::edgeId edgeId : outEdgeIds_[id])
            {
                ESSENTIAL_ASSERT( EdgeExists(edgeId) );

                Types::vertexId other = EdgeAt(edgeId).Target();
                auto & edgesAtOther   = inEdgeIds_[other];
                auto it = std::find( begin(edgesAtOther), end(edgesAtOther), edgeId );
                ESSENTIAL_ASSERT( it != end(edgesAtOther) );
                edgesAtOther.erase(it);

                edgeExists_[edgeId] = false;
            }

            numberOfEdges_ -= inEdgeIds_[id].size();
            numberOfEdges_ -= outEdgeIds_[id].size();
            inEdgeIds_[id].clear();
            outEdgeIds_[id].clear();
        }

        /**
         * @brief      Applies @p function to all edges and collects the result in a vector.
         *
         * @param[in]  function  The function that is applied to all edges.
         *                       @code
         *                       TResult function(Types::edgeId, TEdge)
         *                       @endcode
         *
         * @tparam     FUNCTION  The type of the function object.
         *
         * @return     A vector containing the results of the applications of @p function
         *             to all edges.
         */
        template<typename FUNCTION>
        inline auto MapEdges(FUNCTION function) const
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
        inline       TEdge &EdgeAt ( int  index )                     = delete;
        inline       TEdge &EdgeAt ( char index )                     = delete;
        inline const TEdge &EdgeAt ( int  index ) const               = delete;
        inline const TEdge &EdgeAt ( char index ) const               = delete;
        inline       Types::edgeId   EdgeId ( int  source, int  target ) const = delete;
        inline       Types::edgeId   EdgeId ( char source, char target ) const = delete;
        inline       Types::edgeId   EdgeId ( int  source, char target ) const = delete;
        inline       Types::edgeId   EdgeId ( char source, int  target ) const = delete;
        inline       TEdge &Edge   ( int  source, int  target )       = delete;
        inline       TEdge &Edge   ( char source, char target )       = delete;
        inline       TEdge &Edge   ( char source, int  target )       = delete;
        inline       TEdge &Edge   ( int  source, char target )       = delete;
        inline const TEdge &Edge   ( int  source, int  target ) const = delete;
        inline const TEdge &Edge   ( char source, char target ) const = delete;
        inline const TEdge &Edge   ( int  source, char target ) const = delete;
        inline const TEdge &Edge   ( char source, int  target ) const = delete;
    /// @}

    /// @name Update Methods
    /// @{
#pragma mark UPDATE_METHODS

        /**
         * @brief Update vertices
         * @details Shrink vertex array
         */
        inline void UpdateVertices()
        {
            if (NumberOfVertices() == vertices_.size())
            {
                // There are no edges marked as deleted
                return;
            }

            using std::swap;

            for ( Types::vertexId id = 0
                ; id < vertices_.size()
                ; ++id)
            {
                if (vertexExists_[id]) continue;

                while ( !vertexExists_.back() )
                {
                    vertices_.pop_back();
                    vertexExists_.pop_back();
                    inEdgeIds_.pop_back();
                    outEdgeIds_.pop_back();
                }

                if ( id == vertices_.size() )
                {
                    // All vertices behind the one at position id were marked as
                    // deleted and have been removed. There is nothing left to do.
                    break;
                }

                ESSENTIAL_ASSERT ( vertexExists_.back() );
                ESSENTIAL_ASSERT ( vertices_.size()   == vertexExists_.size() );
                ESSENTIAL_ASSERT ( inEdgeIds_.size()  == vertexExists_.size() );
                ESSENTIAL_ASSERT ( outEdgeIds_.size() == vertexExists_.size() );

                swap(vertexExists_[id], vertexExists_.back());
                vertexExists_.pop_back();

                swap(vertices_[id], vertices_.back());
                vertices_.pop_back();
                vertices_[id].identifier_ = id;

                swap(inEdgeIds_[id], inEdgeIds_.back());
                inEdgeIds_.pop_back();
                for ( auto & edge : inEdgeIds_[id] )
                {
                    EdgeAt(edge).target_ = id;
                }

                swap(outEdgeIds_[id], outEdgeIds_.back());
                outEdgeIds_.pop_back();
                for ( auto & edge : outEdgeIds_[id] )
                {
                    EdgeAt(edge).source_ = id;
                }

            }

            ESSENTIAL_ASSERT ( vertexExists_.size() == NumberOfVertices() );
            ESSENTIAL_ASSERT ( vertices_.size()     == NumberOfVertices() );
            ESSENTIAL_ASSERT ( inEdgeIds_.size()    == NumberOfVertices() );
            ESSENTIAL_ASSERT ( outEdgeIds_.size()   == NumberOfVertices() );
        }

        /**
         * @brief      Deletes all edges that were marked as deleted.
         * @details    Afterwards, the edges use the identifiers between 0 and
         *     @f$m-1@f$.
         *
         *             Time complexity: @f$O(1)@f$ if no edge is marked as deleted,
         *                              @f$O(|\edges|)@f$ otherwise. Here,
         *                              @f$\edges@f$ includes both active
         *                              edges and edges that were marked as
         *                              deleted.
         */
        inline void UpdateEdges()
        {
            if ( NumberOfEdges() == edges_.size() )
            {
                // There are no edges marked as deleted.
                return;
            }

            using std::swap;

            // delete all entries where the edges do not exist
            for ( Types::edgeId id = 0
                ; id < edges_.size()
                ; ++id)
            {
                if (edgeExists_[id]) continue;

                while (!edgeExists_.back())
                {
                    edgeExists_.pop_back();
                    edges_.pop_back();
                }

                if (id == edges_.size())
                {
                    // All edges behind the one at id were marked as deleted as well
                    // and have been removed. We have nothing to do anymore.
                    break;
                }

                ESSENTIAL_ASSERT ( edgeExists_.back() );
                ESSENTIAL_ASSERT ( edgeExists_.size() == edges_.size() );

                swap(edgeExists_[id], edgeExists_.back());
                swap(edges_[id], edges_.back());
                edges_[id].Identifier() = id;
                edgeExists_.pop_back();
                edges_.pop_back();

                ESSENTIAL_ASSERT( edgeExists_[id] );
            }

            ESSENTIAL_ASSERT ( edges_.size()      == NumberOfEdges() );
            ESSENTIAL_ASSERT ( edgeExists_.size() == NumberOfEdges() );

            // Rebuild the vectors containing the incident edges since the IDs may have changed.
            // TODO: This could be implemented more efficiently by only updating affected vertices.
            for ( auto & edges : inEdgeIds_ )
            {
                edges.clear();
            }
            for ( auto & edges : outEdgeIds_ )
            {
                edges.clear();
            }

            std::for_each ( Edges().begin(), Edges().end(),
                [this]( TEdge & edge )
                {
                    Types::vertexId source = edge.Source();
                    Types::vertexId target = edge.Target();

                    inEdgeIds_[target].push_back(edge.Identifier());
                    outEdgeIds_[source].push_back(edge.Identifier());
                }
            );
        }
    ///@}


    /// @name Graph Properties
    /// @{
#pragma mark GRAPH_PROPERTIES

        /**
         * @brief      The minimum degree of the graph @f$\graph@f$.
         * @details    The minimum number of edges incident to any vertex in
         *             the graph. If the graph is empty, 0 is returned.
         *
         * @param[in/out]   id  The vertex identifier with the minimum degree.
         *                      If there are multiple vertices with the minimum
         *                      degree, the one with the smallest identifier is returned.
         *                      If the graph is empty, @p id is set to Const::NONE.
         *
         * @return     The minimum degree.
         */
        inline Types::count MinDegree ( Types::vertexId & id ) const
        {
            if ( NumberOfVertices() == 0 )
            {
                id = Const::NONE;
                return 0;
            }
            TConstVerticesView vertices = Vertices();

            auto result = std::min_element ( vertices.begin(), vertices.end(),
                [&]( TVertex const & left, TVertex const & right )
                {
                    return DegreeAt( left.Identifier() ) < DegreeAt( right.Identifier() );
                }
            );

            id = result->Identifier();
            return DegreeAt(id);
        }

        /**
         * @brief      The minimum degree of the graph @f$\graph@f$.
         * @details    The minimum number of edges incident to any vertex in
         *             the graph. If the graph is empty, 0 is returned.
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
         * @details    The maximum number of edges incident to any vertex in
         *             the graph. If the graph is empty, 0 is returned.
         *
         * @param[in/out]   id  The vertex identifier with the maximum degree.
         *                      If there are multiple vertices with the
         *                      maximum degree, the one with the smallest
         *                      identifier is returned. If the graph is empty,
         *                      @p id is set to Const::NONE.
         *
         * @return     The maximum degree.
         */
        inline Types::count MaxDegree ( Types::vertexId & id ) const
        {
            if ( NumberOfVertices() == 0 )
            {
                id = Const::NONE;
                return 0;
            }
            TConstVerticesView vertices = Vertices();

            auto result = std::max_element ( vertices.begin(), vertices.end(),
                [&]( TVertex const & left, TVertex const & right )
                {
                    return DegreeAt( left.Identifier() ) < DegreeAt( right.Identifier() );
                }
            );
            id = result->Identifier();
            return DegreeAt(id);
        }

        /**
         * @brief      The maximum degree of the graph @f$\graph@f$.
         * @details    The maximum number of edges incident to any vertex in
         *             the graph. If the graph is empty, 0 is returned.
         *
         * @return     The maximum degree.
         */
        inline Types::count MaxDegree() const
        {
            Types::vertexId dummy = 0;
            return MaxDegree(dummy);
        }
    /// @}

    /// @name Vertex Loops
    /// @{
#pragma mark VERTEX_LOOPS

        /**
         * @brief      The @p for loop over all vertex identifiers in the
         *     graph.
         *
         * @param[in]  function  The function object that is called for all
         *                       vertices. It must accept one argument of type
         *                       @p Types::vertexId e.g.,
         * @code{.cpp}
         *      []( Types::vertexId vertexId )
         *      {
         *          // Do something with the vertex identifier.
         *      }
         * @endcode
         *
         * @tparam     Policy   The execution policy.
         * @tparam     FUNCTION The type of the function object.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_all_vertex_identifiers ( FUNCTION function ) const
        {
            internal::DynamicGraphLoopDifferentiation<TGraph const, Policy>
                ::for_all_vertex_identifiers ( *this, function );
        }

        /**
         * @brief      The @p for loop over all vertex objects in the graph.
         *
         * @param[in]  function  The function object that is called for all
         *                       vertices. It must accept one argument of type
         *                       @p TVertex e.g.,
         * @code{.cpp}
         *      []( TVertex & vertex )
         *      {
         *          // Do something with the vertex object.
         *      }
         * @endcode
         *
         * @tparam     Policy   The execution policy.
         * @tparam     FUNCTION The type of the function object.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_all_vertices ( FUNCTION function )
        {
            internal::DynamicGraphLoopDifferentiation<TGraph, Policy>
                ::for_all_vertices ( *this, function );
        }

        /**
         * @brief      The @p for loop over all vertex objects in the graph.
         *
         * @param[in]  function  The function object that is called for all
         *                       vertices. It must accept one argument of type
         *                       @p TVertex e.g.,
         * @code{.cpp}
         *      []( TVertex const & vertex )
         *      {
         *          // Do something with the vertex object.
         *      }
         * @endcode
         *
         * @tparam     Policy   The execution policy.
         * @tparam     FUNCTION The type of the function object.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_all_vertices( FUNCTION function ) const
        {
            internal::DynamicGraphLoopDifferentiation<TGraph const, Policy>
                ::for_all_vertices ( *this, function );
        }

        /**
         * @brief      The @p for loop over all pairs of vertex identifiers
         *             and vertex objects in the graph.
         *
         * @param[in]  function  The function object that is called for all
         *                       vertices. It must accept two arguments of
         *                       types @p Types::vertexId and @p TVertex,
         *                       e.g.,
         * @code{.cpp}
         *      []( Types::vertexId id, TVertex const & vertex )
         *      {
         *          // Do something with the vertex identifier and object.
         *      }
         * @endcode
         *
         * @tparam     Policy   The execution policy.
         * @tparam     FUNCTION The type of the function object.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_all_vertex_tuples ( FUNCTION function )
        {
            internal::DynamicGraphLoopDifferentiation<TGraph, Policy>
                ::for_all_vertex_tuples ( *this, function );
        }

        /**
         * @brief      The @p for loop over all pairs of vertex identifiers
         *             and vertex objects in the graph.
         *
         * @param[in]  function  The function object that is called for all
         *                       vertices. It must accept two arguments of
         *                       types @p Types::vertexId and @p TVertex,
         *                       e.g.,
         * @code{.cpp}
         *      []( Types::vertexId id, TVertex const & vertex )
         *      {
         *          // Do something with the vertex identifier and object.
         *      }
         * @endcode
         *
         * @tparam     Policy   The execution policy.
         * @tparam     FUNCTION The type of the function object.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_all_vertex_tuples ( FUNCTION function ) const
        {
            internal::DynamicGraphLoopDifferentiation<TGraph const, Policy>
                ::for_all_vertex_tuples ( *this, function );
        }
    /// @}

    /// @name Edge loops
    /// @{
#pragma mark EDGE_LOOPS

        /**
         * @brief      The @p for loop over all indentifiers of edges in the graph
         *
         * @param[in]  function  The function object that is called for all
         *                       edges. It must accept one argument of type @p
         *                       Types::edgeId, e.g.,
         * @code{.cpp}
         *      []( Types::edgeId edgeId )
         *      {
         *          // Do something with the edge identifier.
         *      }
         * @endcode
         *
         * @tparam     Policy   The execution policy.
         * @tparam     FUNCTION The type of the function object.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_all_edge_identifiers ( FUNCTION function ) const
        {
            internal::DynamicGraphLoopDifferentiation<TGraph const, Policy>
                ::for_all_edge_identifiers ( *this, function );
        }

        /**
         * @brief      The @p for loop over all edges in the graph
         *
         * @param[in]  function  The function object that is called for all
         *                       edges. It must accept one argument of type @p
         *                       TEdge, e.g.,
         * @code{.cpp}
         *      []( TEdge & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy   The execution policy..
         * @tparam     FUNCTION The type of the function object.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_all_edges ( FUNCTION function )
        {
            internal::DynamicGraphLoopDifferentiation<TGraph, Policy>
                ::for_all_edges ( *this, function );
        }

        /**
         * @brief      The @p for loop over all edges in the graph
         *
         * @param[in]  function  The function object that is called for all
         *                       edges. It must accept one argument of type @p
         *                       TEdge, e.g.,
         * @code{.cpp}
         *      []( TEdge const & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy   The execution policy.
         * @tparam     FUNCTION The type of the function object.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_all_edges ( FUNCTION function ) const
        {
            internal::DynamicGraphLoopDifferentiation<TGraph const, Policy>
                ::for_all_edges ( *this, function );
        }

        /**
         * @brief      The @p for loop over all pairs of edge identifiers and
         *     edge objects in the graph.
         *
         * @param[in]  function  The function object that is called for all
         *                       edges. It must accept two arguments of types
         *                       @p Types::edgeId and @p TEdge, e.g.,
         * @code{.cpp}
         *      []( Types::edgeId edgeId, TEdge & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy   The execution policy.
         * @tparam     FUNCTION The type of the function object.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_all_edge_tuples ( FUNCTION function )
        {
            internal::DynamicGraphLoopDifferentiation<TGraph, Policy>
                ::for_all_edge_tuples ( *this, function );
        }

        /**
         * @brief      The @p for loop over all pairs of edge identifiers and
         *     edge objects in the graph.
         *
         * @param[in]  function  The function object that is called for all edges.
         *                       It must accept two arguments of types @p Types::edgeId
         *                       and @p TEdge, e.g.,
         * @code{.cpp}
         *      []( Types::edgeId edgeId, TEdge const & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy   The execution policy.
         * @tparam     FUNCTION The type of the function object.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_all_edge_tuples ( FUNCTION function ) const
        {
            internal::DynamicGraphLoopDifferentiation<TGraph const, Policy>
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
         * @param[in]  function  The function object that is called for all
         *                       edges at the vertex. It must accept one
         *                       argument of type @p TEdge, e.g.,
         * @code{.cpp}
         *      []( TEdge & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy   The execution policy.
         * @tparam     FUNCTION The type of the function object.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_all_edges_at ( TVertex const & vertex, FUNCTION function )
        {
            internal::DynamicGraphLoopDifferentiation<TGraph, Policy>
                ::for_all_edges_at ( *this, vertex, function );
        }

        /**
         * @brief      The @p for loop over all edges at a vertex object.
         * @details    This is a loop over incoming and outgoing edges.
         *
         * @param[in]  vertex    The vertex object
         * @param[in]  function  The function object that is called for all
         *                       edges at the vertex. It must accept one
         *                       argument of type @p TEdge, e.g.,
         * @code{.cpp}
         *      []( TEdge const & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy   The execution policy.
         * @tparam     FUNCTION The type of the function object.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_all_edges_at ( TVertex const & vertex
                              , FUNCTION        function ) const
        {
            internal::DynamicGraphLoopDifferentiation<TGraph const, Policy>
                ::for_all_edges_at ( *this, vertex, function );
        }

        /**
         * @brief      The @p for loop over all edges at a vertex.
         * @details    This is a loop over incoming and outgoing edges.
         *
         * @pre        There is a vertex with identifier @p vertexId.
         *
         * @param[in]  vertexId  The vertex identifier.
         * @param[in]  function  The function object that is called for all
         *                       edges at the vertex. It must accept one
         *                       argument of type @p TEdge, e.g.,
         * @code{.cpp}
         *      []( TEdge & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy   The execution policy.
         * @tparam     FUNCTION The type of the function object.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_all_edges_at ( Types::vertexId vertexId
                              , FUNCTION        function )
        {
            USAGE_ASSERT( VertexExists(vertexId) );
            internal::DynamicGraphLoopDifferentiation<TGraph, Policy>
                ::for_all_edges_at ( *this, vertexId, function);
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
         *      []( TEdge const & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy   The execution policy.
         * @tparam     FUNCTION The type of the function object.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_all_edges_at ( Types::vertexId vertexId
                              , FUNCTION        function ) const
        {
            USAGE_ASSERT( VertexExists(vertexId) );
            internal::DynamicGraphLoopDifferentiation<TGraph const, Policy>
                ::for_all_edges_at ( *this, vertexId, function );
        }

        /**
         * @brief      The @p for loop over all incoming edges of a vertex.
         *
         * @param[in]  vertex    The vertex object
         * @param[in]  function  The function object that is called for all
         *                       incoming edges at the vertex. It must accept
         *                       one argument of type @p TEdge, e.g.,
         * @code{.cpp}
         *      []( TEdge & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy    The execution policy.
         * @tparam     FUNCTION  The function object that is called for all
         *     incoming edges at @p vertexId
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_in_edges_at( TVertex const & vertex, FUNCTION function )
        {
            internal::DynamicGraphLoopDifferentiation<TGraph, Policy>
                ::for_in_edges_at ( *this, vertex.Identifier(), function );
        }

        /**
         * @brief      The @p for loop over all incoming edges of a vertex.
         *
         * @param[in]  vertex    The vertex object
         * @param[in]  function  The function object that is called for all
         *                       incoming edges at the vertex. It must accept
         *                       one argument of type @p TEdge, e.g.,
         * @code{.cpp}
         *      []( TEdge const & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy    The execution policy.
         * @tparam     FUNCTION  The function object that is called for all
         *     incoming edges at @p vertexId
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_in_edges_at ( TVertex const & vertex
                             , FUNCTION        function ) const
        {
            internal::DynamicGraphLoopDifferentiation<TGraph const, Policy>
                ::for_in_edges_at ( *this, vertex.Identifier(), function );
        }

        /**
         * @brief      The @p for loop over all incoming edges of a vertex.
         *
         * @pre        There is a vertex with identifier @p vertexId.
         *
         * @param[in]  vertexId  The identifier of the vertex
         * @param[in]  function  The function object that is called for all
         *                       incoming edges at the vertex. It must accept
         *                       one argument of type @p TEdge, e.g.,
         * @code{.cpp}
         *      []( TEdge & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy    The execution policy.
         * @tparam     FUNCTION  The function object that is called for all
         *     incoming edges at @p vertexId.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_in_edges_at ( Types::vertexId vertexId
                             , FUNCTION        function )
        {
            USAGE_ASSERT( VertexExists(vertexId) );
            internal::DynamicGraphLoopDifferentiation<TGraph, Policy>
                ::for_in_edges_at ( *this, vertexId, function );
        }

        /**
         * @brief      The @p for loop over all incoming edges of a vertex.
         *
         * @pre        There is a vertex with identifier @p vertexId.
         *
         * @param[in]  vertexId  The identifier of the vertex
         * @param[in]  function  The function object that is called for all
         *                       incoming edges at the vertex. It must accept
         *                       one argument of type @p TEdge, e.g.,
         * @code{.cpp}
         *      []( TEdge const & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy   The execution policy.
         * @tparam     FUNCTION  The function object that is called for all
         *     incoming edges at @p vertexId.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_in_edges_at ( Types::vertexId vertexId
                             , FUNCTION        function ) const
        {
            USAGE_ASSERT( VertexExists(vertexId) );
            internal::DynamicGraphLoopDifferentiation<TGraph const, Policy>
                ::for_in_edges_at ( *this, vertexId, function );
        }

        /**
         * @brief      The @p for loop over all outgoing edges of a vertex
         *
         * @param[in]  vertex    The vertex object.
         * @param[in]  function  The function object that is called for all
         *                       outgoing edges at the vertex. It must accept
         *                       one argument of type @p TEdge, e.g.,
         * @code{.cpp}
         *      []( TEdge & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy    The execution policy.
         * @tparam     FUNCTION  The function object that is called for all
         *     outgoing edges of @p vertex.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_out_edges_at ( TVertex const & vertex
                              , FUNCTION        function )
        {
            internal::DynamicGraphLoopDifferentiation<TGraph, Policy>
                ::for_out_edges_at ( *this, vertex, function );
        }

        /**
         * @brief      The @p for loop over all outgoing edges of a vertex.
         *
         * @param[in]  vertex    The vertex object.
         * @param[in]  function  The function object that is called for all
         *                       outgoing edges at the vertex. It must accept
         *                       one argument of type @p TEdge, e.g.,
         * @code{.cpp}
         *      []( TEdge const & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy    The execution policy.
         * @tparam     FUNCTION  The function object that is called for all
         *     outgoing edges of @p vertex.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_out_edges_at ( TVertex const & vertex
                              , FUNCTION        function ) const
        {
            internal::DynamicGraphLoopDifferentiation<TGraph const, Policy>
                ::for_out_edges_at ( *this, vertex, function );
        }

         /**
         * @brief      The @p for loop over all outgoing edges.
         *
         * @pre        There is a vertex with identifier @p vertexId.
         *
         * @param[in]  vertexId  The vertex identifier.
         * @param[in]  function  The function object that is called for all
         *                       outgoing edges at the vertex. It must accept
         *                       one argument of type @p TEdge, e.g.,
         * @code{.cpp}
         *      []( TEdge & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy    The execution policy.
         * @tparam     FUNCTION  The function object that is called for all
         *     outgoing edges of @p vertex.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_out_edges_at ( Types::vertexId vertexId
                              , FUNCTION        function )
        {
            USAGE_ASSERT ( VertexExists(vertexId) );
            internal::DynamicGraphLoopDifferentiation<TGraph, Policy>
                ::for_out_edges_at ( *this, vertexId, function );
        }

        /**
         * @brief      The @p for loop over all outgoing edges.
         *
         * @pre        There is a vertex with identifier @p vertexId.
         *
         * @param[in]  vertexId  The vertex identifier.
         * @param[in]  function  The function object that is called for all
         *                       outgoing edges at the vertex. It must accept
         *                       one argument of type @p TEdge, e.g.,
         * @code{.cpp}
         *      []( TEdge const & edge )
         *      {
         *          // Do something with the edge object.
         *      }
         * @endcode
         *
         * @tparam     Policy    The execution policy.
         * @tparam     FUNCTION  The function object that is called for all
         *     outgoing edges of @p vertex.
         */
        template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>
        inline
        void for_out_edges_at ( Types::vertexId vertexId
                              , FUNCTION        function ) const
        {
            USAGE_ASSERT( VertexExists(vertexId) );
            internal::DynamicGraphLoopDifferentiation<TGraph const, Policy>
                ::for_out_edges_at ( *this, vertexId, function );
        }
    /// @}

#pragma mark ITERATORS
    private:
        /**
         * @brief      A view on a vector, in which some elements are invalid.
         * @details    To distiguish between valid and invalid elements, a
         *             @p std::vector<bool> is given.
         *
         * @tparam     ElementType  { description }
         * @tparam     Const        { description }
         */
        template<typename ElementType, bool Const>
        class OmittingVectorView
        {
            using TElement = ElementType;
            /**
             * The type of the underlying vector.
             */
            using TVector = typename std::conditional<Const,
                                std::vector<TElement> const,
                                std::vector<TElement>
                            >::type;
            /**
             * The type of the iterators of the underlying vector.
             */
            using TUnderlyingIterator        = typename std::conditional<Const,
                                                   typename TVector::const_iterator,
                                                   typename TVector::iterator
                                               >::type;
            /**
             * The type of the reverse iterators of the underlying vector.
             */
            using TUnderlyingReverseIterator = typename std::conditional<Const,
                                                   typename TVector::const_reverse_iterator,
                                                   typename TVector::reverse_iterator
                                               >::type;
        public:
            /**
             * The type of the iterator.
             */
            using TIterator        = OmittingIterator<
                                                TUnderlyingIterator,
                                                typename std::vector<bool>::const_iterator>;
            /**
             * The type of the reverse iterator.
             */
            using TReverseIterator = OmittingIterator<
                                                TUnderlyingReverseIterator,
                                                typename std::vector<bool>::const_reverse_iterator>;
            /**
             * The type of references to the element.
             */
            using TReference       = typename std::conditional<Const,
                                             TElement const &,
                                             TElement &
                                         >::type;

            /**
             * @brief      Constructs a view to the vector pointed to by @p elementVector.
             * @details    Elements for which the corresponding entry of @p existsVector
             *             is @p false are omitted.
             *
             * @param      elementVector  The vector of all elements.
             * @param      existsVector   The vector that indicates for each element whether
             *                            it is valid.
             * @param      counter        A pointer to a counter that counts the number
             *                            of valid elements.
             */
            explicit OmittingVectorView ( TVector                 * elementVector
                                        , std::vector<bool> const * existsVector
                                        , Types::count      const * counter )
            : elementVector_(elementVector),
              existsVector_(existsVector),
              counter_(counter)
            {}

            TIterator begin() const noexcept
            {
                return TIterator ( elementVector_->begin()
                                 , elementVector_->end()
                                 , existsVector_->begin());
            }

            TIterator end() const noexcept
            {
                return TIterator ( elementVector_->end()
                                 , elementVector_->end()
                                 , existsVector_->end() );
            }

            TReverseIterator rbegin() const noexcept
            {
                return TReverseIterator ( elementVector_->rbegin()
                                        , elementVector_->rend()
                                        , existsVector_->rbegin() );
            }

            TReverseIterator rend() const noexcept
            {
                return TReverseIterator ( elementVector_->rend()
                                        , elementVector_->rend()
                                        , existsVector_->rend() );
            }

            bool         empty() const noexcept { return size() == 0; }
            Types::count size()  const noexcept { return *counter_; }

            TReference   operator[] ( Types::index index ) const
            {
                USAGE_ASSERT( (*existsVector_)[index] );
                return (*elementVector_)[index];
            }

        private:
            TVector                 * elementVector_;
            std::vector<bool> const * existsVector_;
            Types::count      const * counter_;
        };

#pragma mark FRIENDS

#ifdef OPENMP_AVAILABLE
        friend internal::DynamicGraphLoopDifferentiation<TGraph, ExecutionPolicy::parallel>;
        friend internal::DynamicGraphLoopDifferentiation<TGraph const, ExecutionPolicy::parallel>;
#endif // OPENMP_AVAILABLE

#pragma mark MEMBERS

    private:
        Types::name                                name_;                   /**< Name of the graph */

        std::vector<TVertex>                       vertices_;               /**< Vector of vertices */
        std::vector<bool>                          vertexExists_;           /**< Exists vertex for lazy updating */
        Types::count                               numberOfVertices_ = 0;   /**< Number of vertices */

        std::vector<TEdge>                         edges_;                  /**< Vector of edges */
        std::vector<bool>                          edgeExists_;             /**< Exists edge for lazy updating */
        Types::count                               numberOfEdges_ = 0;      /**< Number of edges */

        std::vector< std::vector<Types::edgeId> >  inEdgeIds_;              /**< Ids of the incoming edges per vertex */
        std::vector< std::vector<Types::edgeId> >  outEdgeIds_;             /**< Ids of the outgoing edges per vertex */
};

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__GRAPHS__DYNAMIC_GRAPH_HPP

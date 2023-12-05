/*
 * ArticulationVertexDetection.hpp
 *
 *  Created on: Feb 17, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */
#ifndef EGOA__ALGORITHMS__GRAPH_TRAVERSAL__ARTICULATION_VERTEX_DETECTION__HPP
#define EGOA__ALGORITHMS__GRAPH_TRAVERSAL__ARTICULATION_VERTEX_DETECTION__HPP

#include "Algorithms/GraphTraversal/DepthFirstSearch.hpp"

namespace egoa { 

/**
 * @brief      Class to find articulation vertices.
 * @details    Key thing of the DFS is that it distinguish  the edges into
 *     tree edges and back edges.
 *
 * @tparam     GraphType  The graph should at least provide the same interface
 *     as the StaticGraph().
 * @tparam     IsDirected  If @p true the graph is treated as a directed graph,
 *     if @p false the graph is treated as an undirected graph.
 */
template< typename GraphType
        , bool IsDirected    = false >
class ArticulationVertexDetection : public DepthFirstSearch<GraphType, IsDirected> {
        using TTime = typename DepthFirstSearch<GraphType, IsDirected>::TTime;
    public:
        using TGraph    = GraphType;
        using TVertexId = typename TGraph::TVertexId;

#pragma mark CONSTRUCTOR_AND_DESTRUCTOR
        ArticulationVertexDetection ( TGraph const & graph, TVertexId source )
        : DepthFirstSearch<TGraph, IsDirected> ( graph, source )
        , timeOfOldestReachableAncestor_( graph.NumberOfVertices(), Const::NONE )
        , isArticulationVertex_( graph.NumberOfVertices(), false )
        , treeOutDegree_( std::vector<TVertexId>( graph.NumberOfVertices(), 0 ) )
        {}

        virtual ~ArticulationVertexDetection(){}

#pragma mark GETTER_AND_SETTER
    protected:
        /**
         * @brief      Accessors for the tree out degree.
         *
         * @param[in]  vertex  The vertex identifier.
         *
         * @return     @todo description
         */
        ///@{
            inline Types::count   TreeOutDegree ( TVertexId const vertex ) const { return treeOutDegree_[vertex]; }
            inline Types::count & TreeOutDegree ( TVertexId const vertex )       { return treeOutDegree_[vertex]; }
        ///@}

        inline TTime & TimeOfOldestReachableAncestor( TVertexId vertex ) {
            ESSENTIAL_ASSERT(vertex < timeOfOldestReachableAncestor_.size());
            return timeOfOldestReachableAncestor_[vertex];
        }

#pragma mark FURTHER_PROCESSING
        /**
         * @brief      Preprocessing vertex with @p vertexId.
         * @details    Sets the time of the oldest reachable vertex to the
         *             current entry time.
         *
         * @param[in]  vertex  The vertex identifier.
         */
        virtual inline void PreprocessingVertexWith ( TVertexId const vertex ) override 
        {
            TimeOfOldestReachableAncestor( vertex ) = this->EntryTimeAt( vertex );
        }

        /**
         * @brief      Update the oldest reachable ancestor.
         * @details    The oldest reachable ancestor is updated whenever a
         *     backward edge is detected that goes to a older vertex than the
         *     previous detected one. Note that the age can be easily
         *     determined by the time counter.
         *
         * @param[in]  source  The source identifier.
         * @param[in]  target  The target identifier.
         */
        virtual inline void ProcessingEdgeWith  ( TVertexId     source
                                                , TVertexId     target
                                                , Types::edgeId edgeId ) override
        {
            // Ignore edges that directly lead to the parent again.
            if (target == this->ParentOf(source)) {
                return;
            }

            DfsEdgeType edgeType = this->TypifyEdge ( source, target );

            if ( edgeType == DfsEdgeType::tree ) {
                ++TreeOutDegree ( source );
            }
        }

        virtual inline void PostprocessingEdgeWith(TVertexId     source,
                                                   TVertexId     target,
                                                   Types::edgeId edgeId ) override
        {
            // Ignore edges that directly lead to the parent again.
            if (target == this->ParentOf(source)) {
                return;
            }

            TTime oldestTimeSeenAtTarget = TimeOfOldestReachableAncestor( target );
            TTime & oldestTimeSeenAtSource = TimeOfOldestReachableAncestor( source );


            if ( oldestTimeSeenAtTarget >= this->EntryTimeAt( source )
                && !IsRoot( source ) ) {
                // The source is at least as old as the oldest reachable vertex
                // from the target. Therefore, the source is an articulation vertex.
                isArticulationVertex_[source] = true;
            }

            if (oldestTimeSeenAtSource > oldestTimeSeenAtTarget) {
                // Propagate the oldest vertex reached in the search.
                oldestTimeSeenAtSource = oldestTimeSeenAtTarget;
            }
        }

        /**
         * @brief      Decide which vertices are articulation vertices.
         *         
         * @param[in]  vertexId  The vertex identifier.
         */
        virtual inline void PostprocessingVertexWith ( TVertexId vertexId ) override 
        {
            if ( IsRoot( vertexId ) ) {
                isArticulationVertex_[ vertexId ] = (TreeOutDegree( vertexId ) > 1);
            }
        }

#pragma mark ARTICULATION_VERTEX_DETERMINATION
    public:
        /**
         * @brief      Determines if @p vertex is a @c root articulation vertex @c.
         * @details    If the root has two or more vertices it is---by the
         *     definition of DFS---an articulation vertex. Note that for
         *     undirected graphs there can be know crossing edge connecting
         *     two subtrees of G.
         *
         * @param[in]  vertex  The vertex identifier.
         *
         * @return     True if @p vertex is a root articulation vertex, False
         *     otherwise.
         */
        inline bool IsRootArticulationVertexAt ( TVertexId const vertex ) const
        {
            if ( IsRoot ( vertex ) ) { 
                if ( TreeOutDegree ( vertex ) > 1 ) {
                    // root articulation point
                    return true;
                }
            }
            return false;
        }

        /**
         * @brief      Determines if @p vertex is a @c parent articulation vertex @c.
         * @details    If the oldest reachable vertex of @p vertex is the
         *     parent and the parent is not a root, i.e., the parent of @p
         *     vertex is an articulation vertex.
         *
         * @param[in]  vertex  The vertex identifier.
         *
         * @return     True if @p vertex is a parent articulation vertex,
         *     False otherwise.
         */
        inline bool IsParentArticulationVertexAt ( TVertexId const vertex ) const
        {
            if ( this->ParentOf ( vertex ) == OldestReachableAncestor ( vertex ) 
               && !IsRoot ( this->ParentOf( vertex ) ) 
               ) 
            {
                return true;
            }
            return false;
        }

        /**
         * @brief      Determines if @p vertex and thus, its parent is a @c
         *     bridge articulation vertex @c.
         * @details    If the oldest reachable vertex from @p vertex is the
         *     vertex itself, the edge (ParentOf(vertex), vertex) is a bridge
         *     unless @p vertex is a leaf. If it is a bridge both vertices are
         *     articulation vertices.
         *
         * @param[in]  vertex  The vertex identifier.
         *
         * @return     (True, True) if the vertex's parent and @p vertex are
         *     bridge articulation vertex, (True, False) if the parent is
         *     articulation vertex and @p vertex is a leaf, False otherwise.
         */
        inline std::pair<bool,bool> IsBridgeArticulationVertexAt ( TVertexId const vertex ) const {
            if ( vertex == OldestReachableAncestor ( vertex ) ) {
                if ( TreeOutDegree ( vertex ) > 0 ) 
                { // The vertex is not a leaf
                    return std::make_pair<bool,bool>(true,true);
                }
                // Only the parent is an articulation vertex
                return std::make_pair<bool,bool>(true,false);
            }
            return std::make_pair<bool,bool>(false,false);
        }

        /**
         * @brief      Whether the vertex is an articulation vertex.
         *
         * @param[in]  vertex  The identifier of the vertex.
         *
         * @return     @c true if it is an articulation vertex, @c false otherwise.
         */
        inline bool IsArticulationVertexAt( TVertexId const vertex ) const {
            return isArticulationVertex_[vertex];
        }

        /**
         * @brief      Determines if @p vertex is a root.
         * @details    Note that infty represents the non-existence of a
         *     parent.
         *
         * @param[in]  vertex  The vertex identifier.
         *
         * @return     True if @p vertex is a root, False otherwise.
         */
        inline bool IsRoot ( TVertexId const vertex ) const
        {
            // if Const::NONE the parent of vertex represents a root
            return this->ParentOf ( vertex ) == Const::NONE;
        }

#pragma mark MEMBERS
    private:                                                                                
        std::vector<TTime>          timeOfOldestReachableAncestor_;   /**< Oldest reachable ancestor representing the vertex closest to the root */
        std::vector<Types::count>   treeOutDegree_;             /**< Number of outgoing DFS tree edges per vertex */
        std::vector<bool>           isArticulationVertex_;      /**< Whether the vertex is an articulation vertex */
};

} // namespace egoa

#endif // EGOA__ALGORITHMS__GRAPH_TRAVERSAL__ARTICULATION_VERTEX_DETECTION__HPP

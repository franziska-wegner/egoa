/*
 * BreadthFirstSearch.hpp
 *
 *  Created on: Jan 27, 2019
 *      Author: Franziska Wegner
 */
#ifndef EGOA__ALGORITHMS__GRAPH_TRAVERSAL__BREADTH_FIRST_SEARCH__HPP
#define EGOA__ALGORITHMS__GRAPH_TRAVERSAL__BREADTH_FIRST_SEARCH__HPP

#include "Algorithms/GraphTraversal/Traversal.hpp"
#include "DataStructures/Container/Queues/StdQueue.hpp"

namespace egoa {

/**
 * @brief      Class for the Breadth-First Search (BFS).
 * @details    BFS uses a queue that processes the vertices in First-in,
 *     First-out (FiFo) order. Thus, the traversal of a graph is level-wise.
 *     Not that if the graph G=(V,E) is undirected chords (non-tree edges) can
 *     only be between vertices on the same level or one level below (as the
 *     vertex would have been visited in the next step). For directed graphs,
 *     an chord (u,v) in E can only exists if v's level is higher (closer to
 *     the source vertex s) than u's.
 *
 *     The run time is in O(n + m).
 *
 * @pre        The queue uses the Type Types::vertexId. Note that the queue
 *     does not need to implement the element-wise loops.
 *
 * @tparam     GraphType  The graph should at least provide the same interface
 *     as the StaticGraph().
 * @tparam     QueueType  The queue should provide the same interface as Queue().
 * @tparam     IsDirected  If @p true the graph is treated as a directed graph,
 *     if @p false the graph is treated as an undirected graph.
 */
template< typename GraphType = StaticGraph<Vertices::ElectricalProperties<>,Edges::ElectricalProperties>
        , typename QueueType = StdQueue<GraphType::TVertexId>
        , bool     IsDirected= false >
class BFS final : Traversal<IsDirected> {
    public:
        // Type aliasing
        using TQueue    = QueueType;

    public:
#pragma mark CONSTRUCTOR_AND_DESTRUCTOR
        BFS ( TGraph const & graph, TVertex source )
        : TTraversal ( graph, source )
        , queue_()
        {}

        virtual ~BFS() {}

#pragma mark BREADTH_FIRST_SEARCH
        /**
         * @brief      Run Breadth-First search (BFS).
         */
        virtual inline void Run() {
            ESSENTIAL_ASSERT ( queue_.Empty() );

            EnqueueVertexWith  ( source_ );
            SetVertexVisitedAt ( source_ );

            while ( !queue_.Empty() ) {
                ESSENTIAL_ASSERT ( queue_.Empty() );
                TVertex sourceId = DequeueVertex();
                ESSENTIAL_ASSERT ( graph_.VertexExists ( sourceId ) );
                ESSENTIAL_ASSERT ( VisitedVertexAt ( sourceId ) );

                PreprocessingVertexWith ( sourceId );
                SetVertexProcessedAt    ( sourceId );

                for_all_edges_at( sourceId, []( ElectricalEdge & edge ) {
                    TVertex targetId = edge.Other  ( sourceId );
                    ESSENTIAL_ASSERT ( graph_.VertexExists ( targetId ) );

                    if ( !ProcessedVertexAt( targetId ) || graph_.IsDirected() ) {
                        ProcessingEdgeWith ( edge.Identifier() );
                    }
                    if ( !VisitedVertexAt( targetId ) ) {
                        EnqueueVertexWith  ( targetId );
                        SetVertexVisitedAt ( targetId );
                        ParentOf ( targetId ) = sourceId;
                    }
                });
                PostprocessingVertexWith ( sourceId );
            }
        }

    private:
#pragma mark QUEUE_METHODS
        /**
         * @brief      Add a vertex to the queue.
         * @pre        Only visited vertices that are unprocessed should be
         *     add to the queue.
         *
         * @param[in]  vertexId  The vertex identifier.
         */
        inline void EnqueueVertexWith ( TVertex vertexId ) {
            USAGE_ASSERT ( graph_.VertexExists ( vertexId ) );
            queue_.Push ( vertexId );
        }

        /**
         * @brief      Get the next unprocessed vertex.
         * @details    A vertex can only be dequeued if it is was marked as
         *     visited.
         *
         * @return     The next unprocessed but visited vertex.
         */
        inline TVertex DequeueVertex ( ) {
            USAGE_ASSERT ( graph_.VertexExists ( vertexId ) );
            TVertex vertexId = queue_.front();
            queue_.Pop();
            return vertexId;
        }

//exact behavior of the Breadth-First Search (BFS) depends on the processing methods
#pragma mark FURTHER_PROCESSING
        virtual inline void PreprocessingVertexWith  ( TVertex vertexId ) override {}
        virtual inline void PostprocessingVertexWith ( TVertex vertexId ) override {}
        virtual inline void ProcessingEdgeWith  ( TVertex sourceId
                                                , TVertex targetId ) override {}

#pragma mark MEMBERS
    private:
        TQueue                       queue_;        /**< The FIFO queue */

}; // class BFS

} // namespace egoa


#endif // EGOA__ALGORITHMS__GRAPH_TRAVERSAL__BREADTH_FIRST_SEARCH__HPP

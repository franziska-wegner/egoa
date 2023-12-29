/*
 * Prim.hpp
 *
 *  Created on: Nov 22, 2018
 *      Author: Franziska Wegner, Matthias Wolf
 */

#ifndef EGOA__ALGORITHMS__SPANNING_TREES__PRIM_HPP
#define EGOA__ALGORITHMS__SPANNING_TREES__PRIM_HPP

#include "Algorithms/SpanningTree/MST.hpp"

#include "DataStructures/Container/Queues/MappingBinaryHeap.hpp"

namespace egoa {
/**
 *  @brief An implementation of Prim's algorithm for finding minimum spanning
 *         trees.
 *
 *  @code{.cpp}
 *      Prim<TGraph> prim(graph, comparator);
 *      prim.Run();
 *      Subgraph<TGraph> spanningTree = prim.Result();
 *  @endcode
 *
 *  @tparam GraphType  The type of the graph.
 *  @tparam WeightType The type of the edge weights.
 */
template< typename GraphType>
class Prim final : public MST<GraphType> {

    using TSpanningTree = MST<GraphType>;
    using typename TSpanningTree::TGraph;
    using typename TSpanningTree::TEdge;
    using typename TSpanningTree::TComparator;

    public:
        Prim(TGraph & graph,
             TComparator comparator)
        : TSpanningTree( graph, std::move(comparator) )
        {}

        virtual ~Prim() {}

        /**
         * @brief      Prim's algorithm
         * @detail     Prim's algorithm is quite similar to Dijkstra's
         *     algorithm. Prim runs in O(|E| log |V|) using binary heaps.
         *     While using Fibonacci heaps the running time is then in O(|E| +
         *     |V| log |V|). The latter is an improvement while |V| << |E|.
         *
         *     Steps:
         *          1. While not all vertices are in the MST component
         *          2. Relax the incident edges to u if necessary
         *          3. Choose the edge that has the minimum weight between
         *          the grown MST component and the non-MST component, i.e.,
         *          no cycle will be created
         *
         * @pre  This algorithm assumes that the vertex identifiers all lie in
         *       the interval [0, NumberOfVertices() - 1].
         */
        virtual inline void Run ( ) override {
            Types::count const numberOfVertices = this->Graph().NumberOfVertices();

            if (numberOfVertices == 0) return;

            std::vector<bool> isVertexInMst( numberOfVertices, false );
            std::vector<bool> visited(numberOfVertices, false);
            std::vector<Types::edgeId> edgesInSpanningTree;

            // TODO: Use vector instead of the default unordered_map
            MappingBinaryHeap<Types::vertexId, Types::edgeId> heap(this->Comparator());

            Types::vertexId currentVertex = 0;
            visited[currentVertex] = true;

            while (true) {
                isVertexInMst[currentVertex] = true;

                // Iterate over all incident edges
                this->Graph().template for_all_edges_at<ExecutionPolicy::sequential>( currentVertex,
                    [&]( TEdge const & edge ) {
                        Types::vertexId neighbor = edge.Other( currentVertex );

                        // Ignore edges to vertices that have already been included in the MST
                        if (isVertexInMst[neighbor]) return;

                        if (!visited[neighbor])
                        { // The neighbor has not been visited before
                            heap.Insert(neighbor, edge.Identifier());
                            visited[neighbor] = true;
                        } else if ( this->Comparator()( edge.Identifier(), heap.KeyOf(neighbor) ) )
                        {
                            // Better edge to neighbor has been found
                            heap.ChangeKey(neighbor, edge.Identifier());
                        }
                });

                if (heap.Empty()) break;

                Types::edgeId parentEdge;
                std::tie(currentVertex, parentEdge) = heap.DeleteTop();
                edgesInSpanningTree.push_back(parentEdge);
            } // while loop

            this->SetResult(std::move(edgesInSpanningTree));
        }
};

} // namespace egoa


#endif // EGOA__ALGORITHMS__SPANNING_TREES__PRIM_HPP

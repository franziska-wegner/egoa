/*
 * Kruskal.hpp
 *
 *  Created on: Nov 22, 2018
 *      Author: Franziska Wegner, Matthias Wolf
 */

#ifndef EGOA__ALGORITHMS__SPANNING_TREES__KRUSKAL_HPP
#define EGOA__ALGORITHMS__SPANNING_TREES__KRUSKAL_HPP

#include "Algorithms/SpanningTree/MST.hpp"

#include "DataStructures/Container/UnionFind.hpp"

namespace egoa {
/**
 *  @brief An implementation of Kruskal's algorithm for finding minimum spanning
 *         trees.
 *
 *  @code{.cpp}
 *      Kuskal<TGraph> kruskal(graph, comparator);
 *      kruskal.Run();
 *      Subgraph<TGraph> spanningTree = kruskal.Result();
 *  @endcode
 *
 *  @tparam GraphType  The type of the graph.
 */
template<typename GraphType>
class Kruskal final : public MST<GraphType> {

    using TSpanningTree = MST<GraphType>;
    using typename TSpanningTree::TGraph;
    using typename TSpanningTree::TEdge;
    using typename TSpanningTree::TComparator;

    public:
        Kruskal(TGraph & graph,
                TComparator comparator)
        : TSpanningTree(graph, std::move(comparator))
        {}

        virtual ~Kruskal() {}

        /**
         * @brief Kruskal's Algorithm
         * @details Kruskal's algorithm runs in O(|E| lg |V|) using binary
         *     heaps and calculates a MST. It uses techniques that are also
         *     common for connected component algorithms.
         *     
         *     Steps:
         *          1. Increases the MST by exactly one edge in each iteration
         *          2. It starts with |V| components
         *          3. In each iteration the number of connected components shrinks by 1
         *          4. To manage the connected components it uses a disjoint-set data structure
         *                      
         */
        virtual inline void Run() override {
            UnionFind unionFind( this->Graph().NumberOfVertices() );

            // Fill vector with edge identifiers
            std::vector<Types::edgeId> edges;
            edges.reserve(this->Graph().NumberOfEdges());
            this->Graph().template for_all_edge_identifiers<ExecutionPolicy::sequential>([&edges](Types::edgeId id) {
                edges.push_back(id);
            });

            // Sort the edges by their weights
            std::sort( edges.begin(), edges.end(), this->Comparator());

            std::vector<Types::edgeId> spanningTreeEdges;

            for ( Types::edgeId edge : edges ) 
            {
                Types::vertexId source = this->Graph().EdgeAt( edge ).Source();
                Types::vertexId target = this->Graph().EdgeAt( edge ).Target();
                if ( !unionFind.InSameComponent( source, target ) ) {
                    unionFind.Union( source, target );
                    spanningTreeEdges.push_back( edge );
                }
            }

            this->SetResult(std::move(spanningTreeEdges));
        }
};

} // namespace egoa

#endif // EGOA__ALGORITHMS__SPANNING_TREES__KRUSKAL_HPP
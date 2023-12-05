/*
 * MST.hpp
 *
 *  Created on: Nov 11, 2018
 *      Author: Franziska Wegner, Matthias Wolf
 */

#ifndef EGOA__ALGORITHMS__SPANNING_TREE__MST_HPP
#define EGOA__ALGORITHMS__SPANNING_TREE__MST_HPP

#include <functional>
#include <ostream>
#include <utility>
#include <vector>

#include "Auxiliary/Constants.hpp"
#include "Auxiliary/ExecutionPolicy.hpp"
#include "Auxiliary/Types.hpp"

#include "DataStructures/Graphs/Subgraph.hpp"

namespace egoa {
/**
 *  @class MST
 *
 *  @brief      Base class for minimum spanning tree algorithms.
 *
 *  @details    Typically, minimum spanning tree algorithms are used like this:
 *  @code{.cpp}
 *      auto mstAlgorithm(graph, comparator);
 *      mstAlgorithm.Run();
 *      Subgraph<TGraph> mst = mstAlgorithm.Result();
 *  @endcode
 *
 *  @tparam GraphType   The type of the graph.
 */
template< typename GraphType>
class MST {
    protected:
        using TGraph        = GraphType;
        using TEdge         = typename TGraph::TEdge;
        using TComparator   = std::function<bool(Types::edgeId, Types::edgeId)>;

    public:
        MST ( TGraph    & graph,
              TComparator comparator)
        : graph_(graph)
        , comparator_(std::move(comparator))
        {}

        virtual ~MST() {}

        virtual void Run() = 0;

        /**
         * @brief      Returns the caluclated spanning tree after Run() has been called.
         *
         * @pre        Run() has been called.
         *
         * @return     The subgraph representing the calculated spanning tree.
         */
        inline Subgraph<TGraph> const & Result() const 
        {
            return spanningTree_;
        }

        friend std::ostream & operator<<( std::ostream & os, MST const & rhs ) 
        {
            auto & graph = rhs.spanningTree_.Graph();
            for ( auto edgeId : rhs.spanningTree_.Edges() ) 
            {
                auto & edge = graph.EdgeAt(edgeId);
                os << "(" << edge.Source() << ", " << edge.Target() << ");\n";
            }
            return os;
        }

    protected:

        /**
         * @brief      Builds a subgraph object representing the spanning tree
         *             given by the edges.
         *
         * @param      edges  The edges in the spanning tree.
         */
        void SetResult(std::vector<Types::edgeId> && edges) 
        {
            std::vector<Types::vertexId> vertices;
            vertices.reserve(Graph().NumberOfVertices());
            Graph().template for_all_vertex_identifiers<ExecutionPolicy::sequential>( [&vertices](Types::vertexId id) 
            {
                vertices.push_back(id);
            });

            spanningTree_ = Subgraph<TGraph> ( & graph_, std::move(vertices), std::move(edges) );
        }

        ///@name Getter and setter
        ///@{
            inline GraphType const   & Graph()      const { return graph_; }
            inline GraphType         & Graph()            { return graph_; }

            inline TComparator const & Comparator() const { return comparator_; }
        ///@}

    private:
        GraphType &       graph_;         /**< Undirected graph G = (V, E) */
        TComparator       comparator_;
        Subgraph<TGraph>  spanningTree_{&graph_, {}, {}};
};

} // namespace egoa

#endif // EGOA__ALGORITHMS__SPANNING_TREE__MST_HPP

/**
 * Subgraph.hpp
 *
 *  Created on: May 8, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */

#ifndef EGOA__DATA_STRUCTURES__GRAPHS__SUBGRAPH_HPP
#define EGOA__DATA_STRUCTURES__GRAPHS__SUBGRAPH_HPP

#include <algorithm>
#include <ostream>
#include <vector>

#include "DataStructures/Views/VectorView.hpp"

#include "Exceptions/Assertions.hpp"


namespace egoa {

/**
 * @brief      A subgraph of an existing graph.
 *
 * @tparam     GraphType  The type of the graph.
 */
template< typename GraphType>
class Subgraph {
public:
    /// @brief The type of the underlying graph.
    using TUnderlyingGraph = GraphType;
    using TVertexId = typename TUnderlyingGraph::TVertexId;
    using TEdgeId = typename TUnderlyingGraph::TEdgeId;
    using TVerticesView = VectorView<TVertexId, true>;
    using TEdgesView = VectorView<TEdgeId, true>;

    /**
     * @brief      The constructor.
     *
     * @pre        All vertex identifiers and edge identifiers must correspond
     *             to existing vertices and edges in the graph, respectively.
     *
     * @param      graph     A pointer to the underlying graph.
     * @param[in]  vertices  The identifiers of the vertices in the subgraph.
     * @param[in]  edges     The identifiers of the edges in the subgraph.
     */
    Subgraph(TUnderlyingGraph * graph,
             std::vector<TVertexId> vertices,
             std::vector<TEdgeId> edges)
    : underlyingGraph_(graph),
      vertices_(std::move(vertices)),
      edges_(std::move(edges))
    {
        USAGE_ASSERT(std::all_of(vertices_.begin(), vertices_.end(),
            [this](TVertexId id) {
                return underlyingGraph_->VertexExists(id);
            }));
        USAGE_ASSERT(std::all_of(edges_.begin(), edges_.end(),
            [this](TEdgeId id) {
                return underlyingGraph_->EdgeExists(id);
            }));

        std::sort(vertices_.begin(), vertices_.end());
        std::sort(edges_.begin(), edges_.end());
    }

    /**
     * @brief      The underlying graph.
     *
     * @return     A reference to the underlying graph.
     */
    TUnderlyingGraph & UnderlyingGraph() {
        return *underlyingGraph_;
    }

    /**
     * @brief      The underlying graph.
     *
     * @return     A reference to the underlying graph.
     */
    TUnderlyingGraph const & UnderlyingGraph() const {
        return *underlyingGraph_;
    }

    /**
     * @brief      A view on the identifiers of the vertices in the subgraph.
     *
     * @details    The identifiers are sorted in increasing order.
     */
    TVerticesView Vertices() const {
        return TVerticesView(&vertices_);
    }

    /**
     * @brief      A view on the identifiers of the edges in the subgraph.
     *
     * @details    The identifiers are sorted in increasing order.
     */
    TEdgesView Edges() const {
        return TEdgesView(&edges_);
    }

    friend bool operator==(Subgraph const & lhs, Subgraph const & rhs) {
        return lhs.underlyingGraph_ == rhs.underlyingGraph_ &&
               lhs.vertices_ == rhs.vertices_ &&
               lhs.edges_ == rhs.edges_;
    }

    friend bool operator!=(Subgraph const & lhs, Subgraph const & rhs) {
        return !(lhs == rhs);
    }

private:

    /**
     * @brief A pointer to the underlying graph.
     *
     * @details A pointer is used instead of a reference since otherwise a
     *          Subgraph object would not be assignable.
     */
    TUnderlyingGraph * underlyingGraph_;
    /**
     * @brief The identifiers of the vertices belonging to the subgraph.
     */
    std::vector<TVertexId> vertices_;
    /**
     * @brief The identifiers of the edges belong to the subgraph.
     */
    std::vector<TEdgeId> edges_;

};

template<typename GraphType>
inline std::ostream & operator<<(std::ostream & os,
                                 Subgraph<GraphType> const & subgraph) {
    os << "[G="
       << subgraph.UnderlyingGraph().Name()
       << ", V="
       << subgraph.Vertices()
       << ", E="
       << subgraph.Edges()
       << "]";
    return os;
}

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__GRAPHS__SUBGRAPH_HPP

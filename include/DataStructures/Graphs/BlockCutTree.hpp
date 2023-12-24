/*
 * BlockCutTree.hpp
 *
 *  Created on: May 14, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */
#ifndef EGOA__DATA_STRUCTURES__GRAPHS__BLOCK_CUT_TREE__HPP
#define EGOA__DATA_STRUCTURES__GRAPHS__BLOCK_CUT_TREE__HPP

#include <functional>
#include <stack>
#include <utility>
#include <vector>

#include "Algorithms/GraphTraversal/ArticulationVertexDetection.hpp"
#include "Algorithms/GraphTraversal/DepthFirstSearch.hpp"

#include "Auxiliary/Constants.hpp"
#include "Auxiliary/Types.hpp"

#include "DataStructures/Graphs/Subgraph.hpp"

#include "Exceptions/Assertions.hpp"

namespace egoa {

/// @defgroup   bctree  Block-cut tree related classes and functions
/// @details    This module contains all functions and classes that are related
///             to block-cut trees.
///             
///             To build a block-cut tree the functions
///             buildBlockCutTree(GraphType const &) or
///             BlockCutTree<GraphType>::Build(GraphType const &) can be used.

namespace internal {
    template<typename GraphType>
    class BlockCutTreeBuilder;
} // namespace internal

/**
 * @brief      A block-cut tree.
 *
 * @details    The block-cut tree is unrooted.
 *
 * @todo       Example how a block-cut tree is constructed and how it can be used.
 *
 * @tparam     GraphType  The type of the underlying graph.
 *
 * @ingroup    bctree
 */
template<typename GraphType>
class BlockCutTree final {
public:
    class Block;
    class CutVertex;

    using TGraph = GraphType;

private:
    BlockCutTree(TGraph const & graph)
    : graph_(graph),
      blocks_(),
      cutVertices_(graph.NumberOfVertices()),
      blockOfEdge_(graph.NumberOfEdges(), Const::NONE),
      blocksOfVertex_(graph.NumberOfVertices()),
      numberOfCutVertices_(0)
    {}

public:

    /**
     * @brief      Builds a @c BlockCutTree for a given graph.
     *
     * @param      graph  The graph.
     *
     * @return     The @c BlockCutTree.
     */
    static BlockCutTree Build(TGraph const & graph) {
        internal::BlockCutTreeBuilder builder(graph);
        return builder.Build();
    }

    /// @name Basic Properties
    /// @{
#pragma mark BASIC_PROPERTIES
    /**
     * @brief      The number of blocks in the block-cut tree.
     *
     * @return     The number of blocks.
     */
    Types::count NumberOfBlocks() const {
        return blocks_.size();
    }

    /**
     * @brief      The number of cut-vertices in the block-cut tree.
     *
     * @return     The number of cut-vertices.
     */
    Types::count NumberOfCutVertices() const {
        return numberOfCutVertices_;
    }

    /**
     * @brief      The underlying graph of the block-cut tree.
     *
     * @return     The underlying graph.
     */
    TGraph const & Graph() const {
        return graph_;
    }
    /// @}

    /// @name Topology
    /// @{
#pragma mark TOPOLOGY
    /**
     * @brief      All identifiers of the blocks a vertex belongs to.
     *
     * @param[in]  id    The identifier of the vertex.
     *
     * @return     A vector containing all identifiers of the blocks a vertex
     *             belongs to.
     */
    std::vector<Types::blockId> const & BlocksOfVertex(Types::vertexId id) const {
        return blocksOfVertex_[id];
    }

    /**
     * @brief      The identifiers of the block an edge belongs to.
     *
     * @param[in]  id    The identifier of the edge.
     *
     * @return     The block identifier.
     */
    Types::blockId BlockOfEdge(Types::edgeId id) const {
        return blockOfEdge_[id];
    }

    /**
     * @brief      Whether a vertex is a cut-vertex.
     *
     * @param[in]  id    The identifier of the vertex.
     *
     * @return     @c true if the vertex is a cut-vertex, @c false otherwise.
     */
    bool IsCutVertex(Types::vertexId id) const {
        return BlocksOfVertex(id).size() > 1;
    }

    /**
     * @brief      The block with identifier @c id.
     *
     * @param[in]  id    The identifier of the block.
     *
     * @return     The block with identifier @c id.
     */
    Block const & BlockAt(Types::blockId id) const {
        return blocks_[id];
    }

    /**
     * @brief      The cut-vertex with identifier @c id.
     *
     * @pre        The vertex with identifier @c id is a cut-vertex.
     *
     * @param[in]  id    The identifier of the cut-vertex.
     *
     * @return     The cut-vertex object with identifier @c id.
     */
    CutVertex const & CutVertexAt(Types::vertexId id) const {
        USAGE_ASSERT(IsCutVertex(id));
        return cutVertices_[id];
    }
    /// @}

    /**
     * @brief      A block.
     *
     * @ingroup    bctree
     */
    class Block final {
    public:
        Block(Types::blockId identifier,
              Subgraph<TGraph const> subgraph,
              std::vector<Types::vertexId> cutVertices)
        : identifier_(identifier),
          subgraph_(std::move(subgraph)),
          cutVertices_(std::move(cutVertices))
        {}

        /**
         * @brief      The identifier of the block.
         *
         * @return     The identifier of the block.
         */
        Types::blockId Identifier() const {
            return identifier_;
        }

        /**
         * @brief      The subgraph forming the block.
         *
         * @return     The subgraph forming the block.
         */
        egoa::Subgraph<TGraph const> const & Subgraph() const {
            return subgraph_;
        }

        /**
         * @brief      The cut-vertices of the block.
         *
         * @return     A vector containing the identifiers of the cut-vertices.
         */
        std::vector<Types::vertexId> const & CutVertices() const {
            return cutVertices_;
        }

        /**
         * @brief      Whether the block is a leaf of the block-cut tree.
         *
         * @return     @c true if the block is a leaf, @c false otherwise.
         */
        bool IsLeaf() const {
            return CutVertices().size() <= 1;
        }

        /**
         * @brief      Whether the block is a bridge.
         * 
         * @details    Bridges are blocks that consist of only one edge.
         *
         * @return     @c true if the block represents a bridge, @c false otherwise.
         */
        bool IsBridge() const {
            return Subgraph().Edges().size() == 1;
        }

    private:
        friend class egoa::internal::BlockCutTreeBuilder<TGraph>;

        Types::blockId identifier_;
        egoa::Subgraph<TGraph const> subgraph_;
        Types::vertexId parent_;
        std::vector<Types::vertexId> cutVertices_;
    };

    /**
     * @brief      Class for cut-vertices.
     *
     * @ingroup    bctree
     */
    class CutVertex {
    public:
        CutVertex()
        : identifier_(Const::NONE),
          blocks_()
        {}

        CutVertex(Types::vertexId identifier,
                  std::vector<Types::blockId> blocks)
        : identifier_(identifier),
          blocks_(blocks)
        {}

        /**
         * @brief      The vertex identifier.
         *
         * @details    This is the same identifier as in the underlying graph.
         *
         * @return     The vertex identifier.
         */
        Types::vertexId Identifier() const {
            return identifier_;
        }

        /**
         * @brief      The blocks the cut-vertex belongs to.
         *
         * @return     A vector containing the indentifiers of the blocks.
         */
        std::vector<Types::blockId> const & Blocks() const {
            return blocks_;
        }

    private:
        friend class egoa::internal::BlockCutTreeBuilder<TGraph>;

        Types::vertexId identifier_;
        std::vector<Types::blockId> blocks_;
    };

    friend class egoa::internal::BlockCutTreeBuilder<TGraph>;

#pragma mark MEMBERS
    /// @name Members
    /// @{
private:

    /**
     * @brief      The underlying graph.
     *
     * @details    A reference_wrapper is stored instead of a reference to make
     *             the block-cut tree assignable.
     */
    std::reference_wrapper<TGraph const> graph_;
    /**
     * @brief      The blocks in the block-cut tree ordered by their component
     *             identifiers.
     */
    std::vector<Block> blocks_;
    /**
     * @brief      The cut-vertices in the graph.
     * 
     * @details    The cut-vertex with identifier @c id is at position @c id
     *             in the vector. The positions that do not correspond to
     *             cut-vertices contain empty objects.
     */
    std::vector<CutVertex> cutVertices_;
    /**
     * @brief      For each edge the block it belongs to.
     *
     * @details    Note that each edge belongs to exactly one block.
     */
    std::vector<Types::blockId> blockOfEdge_;
    /**
     * @brief      For each vertex the blocks it belongs to.
     *
     * @details    A vertex is a cut-vertex if and only if it belongs to more
     *             than one block. For cut-vertices the first block
     *             is the parent block and the remaining blocks are
     *             the child blocks.
     *             For the root, all blocks are child blocks.
     */
    std::vector<std::vector<Types::blockId>> blocksOfVertex_;

    /**
     * @brief      The number of cut-vertices.
     *
     * @details    This is stored explicitly because cutVertices_ contains an
     *             entry for all vertices.
     */
    Types::count numberOfCutVertices_;
    /// @}
};

/**
 * @brief      Builds a block-cut tree
 *
 * @details    Convenience function for building a block-cut tree. Using the static
 *             member function @c BlockCutTree<GraphType>::Build() requires
 *             explicit template arguments. Here, these are deduced by the compiler.
 *
 * @param      graph      The graph for which the block-cut tree shall be built.
 *
 * @tparam     GraphType  The type of the graph.
 *
 * @return     The block-cut tree.
 *
 * @ingroup    bctree
 */
template<typename GraphType>
BlockCutTree<GraphType> buildBlockCutTree(GraphType const & graph) {
    return BlockCutTree<GraphType>::Build(graph);
}

namespace internal {

/**
 * @brief      A class to build BlockCutTree objects for a graph.
 *
 * @tparam     GraphType  The type of the graph.
 *
 * @ingroup    bctree
 */
template<typename GraphType>
class BlockCutTreeBuilder final : private ArticulationVertexDetection<GraphType, false> {
    class BlockUnderConstruction;

    using TGraph     = GraphType;
    using TVertexId  = typename TGraph::TVertexId;
    using TEdgeId    = typename TGraph::TEdgeId;
    using TDetection = ::egoa::ArticulationVertexDetection<TGraph, false>;
    using TTime      = typename DepthFirstSearch<GraphType, false>::TTime;

    template<typename T>
    using VectorStack = std::stack<T, std::vector<T>>;


public:
    /**
     * @brief      The constructor.
     *
     * @param      graph  The graph for which a block-cut tree shall be built.
     */
    BlockCutTreeBuilder(TGraph const & graph)
    : TDetection(graph, graph.Vertices()[0].Identifier()),
      graph_(graph),
      bcTree_(graph)
    {}

    /**
     * @brief      Builds the block-cut tree.
     *
     * @return     The BlockCutTree-object.
     */
    BlockCutTree<TGraph> && Build() {
        this->Run();

        ESSENTIAL_ASSERT(blockStack_.empty());
        ESSENTIAL_ASSERT(bcTree_.cutVertices_.size() == graph_.NumberOfVertices());
        ESSENTIAL_ASSERT(bcTree_.blocks_.size() == nextBlockId_);

        SortBlocks();
        return std::move(bcTree_);
    }

private:

    /// @name Steps of the Algorithm
    /// @{
#pragma mark ALGORITHM_STEPS
    /**
     * @brief      Sort all blocks in @c bcTree_.blocks_.
     */
    void SortBlocks() {
         auto compareById = [](auto const & lhs, auto const & rhs) {
            return lhs.Identifier() < rhs.Identifier();
        };
        using std::begin, std::end;
        std::sort(begin(bcTree_.blocks_), end(bcTree_.blocks_), compareById);
    }
    /// @}

protected:
    /// @name Traversal
    /// @{
#pragma mark TRAVERSAL
    virtual void PostprocessingEdgeWith(TVertexId source,
                                        TVertexId target,
                                        TEdgeId edgeId) override {
        TDetection::PostprocessingEdgeWith(source, target, edgeId);

        if (this->ParentOf(source) == target) {
            // Ignore edges that directly return to the parent.
            return;
        }

        auto type = this->TypifyEdge(source, target);
        if (type == DfsEdgeType::forward) {
            // The edge has already been considered in the other direction.
            return;
        }

        auto targetTime = this->TimeOfOldestReachableAncestor(target);

        ESSENTIAL_ASSERT(blockStack_.empty()
                         || CurrentBlock().timeOfOldestVertex <= targetTime);

        if (blockStack_.empty() || CurrentBlock().timeOfOldestVertex < targetTime) {
            // We reached a new block
            PushNextBlock(targetTime);
        }

        ESSENTIAL_ASSERT(CurrentBlock().timeOfOldestVertex == targetTime);

        AddEdgeToCurrentBlock(edgeId);

        // Vertices are added as the targets of the tree edges in the block.
        // All vertex except the one via which a block is reached are reached
        // exactly once via a tree edge.
        // The remaining vertex is added is added when the last tree
        // edge of the block is backtracked.
        if (type == DfsEdgeType::tree) {
            AddVertexToCurrentBlock(target);
            if (this->IsArticulationVertexAt(target)) {
                AddCutVertexToBlock(target);
            }
        }

        // If the source of the block was reached at or before
        // CurrentBlock().timeOfOldestVertex, it is the oldest vertex of the block
        // and all edges of the block have been collected.
        if (this->EntryTimeAt(source) <= CurrentBlock().timeOfOldestVertex) {
            AddVertexToCurrentBlock(source);
            if (this->IsArticulationVertexAt(source)) {
                AddCutVertexToBlock(source);
            }
            PopBlock();
        }
    }

    virtual void PostprocessingVertexWith(Types::vertexId vertex) override {
        TDetection::PostprocessingVertexWith(vertex);

        if (this->IsArticulationVertexAt(vertex)) {
            ++bcTree_.numberOfCutVertices_;
        }
    }
    /// @}

private:
    /// @name Adding Blocks
    /// @{
#pragma mark ADDING_BLOCKS
    /**
     * @brief      Initializes the next block.
     */
    void PushNextBlock(TTime time) {
        blockStack_.emplace(nextBlockId_++, time);
    }

    /**
     * @brief      Pops a block and adds it to the block-cut tree.
     */
    void PopBlock() {
        bcTree_.blocks_.push_back(std::move(blockStack_.top()).ToBlock(graph_));
        blockStack_.pop();
    }

    /**
     * @brief      Adds an edge to the current block.
     *
     * @param[in]  edge  The identifier of the edge to add.
     */
    void AddEdgeToCurrentBlock(TEdgeId edge) {
        bcTree_.blockOfEdge_[edge] = CurrentBlockId();
        CurrentBlock().edges.push_back(edge);
    }

    /**
     * @brief      Adds a vertex to the current block.
     *
     * @param[in]  vertex  The identifier of the vertex to add.
     */
    void AddVertexToCurrentBlock(TVertexId vertex) {
        bcTree_.blocksOfVertex_[vertex].push_back(CurrentBlockId());
        CurrentBlock().vertices.push_back(vertex);
    }

    void AddCutVertexToBlock(TVertexId vertex) {
        ESSENTIAL_ASSERT(this->IsArticulationVertexAt(vertex));
        bcTree_.cutVertices_[vertex].blocks_.push_back(CurrentBlockId());
        bcTree_.cutVertices_[vertex].identifier_ = vertex;
        CurrentBlock().cutVertices.push_back(vertex);
    }

    /**
     * @brief      The identifier of the current block.
     *
     * @return     The identifier of the current block.
     */
    Types::index CurrentBlockId() const {
        ESSENTIAL_ASSERT(!blockStack_.empty());
        return blockStack_.top().identifier;
    }

    BlockUnderConstruction & CurrentBlock() {
        ESSENTIAL_ASSERT(!blockStack_.empty());
        return blockStack_.top();
    }
    /// @}

    struct BlockUnderConstruction {
        using TBlock = typename BlockCutTree<TGraph>::Block;

        BlockUnderConstruction(Types::blockId id, TTime time)
        : identifier(id),
          timeOfOldestVertex(time)
        {}

        Types::blockId         identifier;
        TTime                  timeOfOldestVertex;
        std::vector<TVertexId> vertices;
        std::vector<TEdgeId>   edges;
        std::vector<TVertexId> cutVertices;

        TBlock ToBlock(TGraph const & graph) && {
            return TBlock(identifier,
                          Subgraph(&graph, std::move(vertices), std::move(edges)),
                          std::move(cutVertices));
        }
    };

#pragma mark MEMBERS

    TGraph const & graph_;
    egoa::BlockCutTree<TGraph> bcTree_;
    Types::index nextBlockId_ = 0;
    VectorStack<BlockUnderConstruction> blockStack_;
};

} // namespace internal

} // namespace egoa


#endif // EGOA__DATA_STRUCTURES__GRAPHS__BLOCK_CUT_TREE__HPP

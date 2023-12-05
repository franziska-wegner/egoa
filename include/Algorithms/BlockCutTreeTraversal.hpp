/*
 * BlockCutTreeTraversal.hpp
 *
 *  Created on: May 27, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */

#ifndef EGOA__ALGORITHMS__BLOCK_CUT_TREE_TRAVERSAL_HPP
#define EGOA__ALGORITHMS__BLOCK_CUT_TREE_TRAVERSAL_HPP

#include <functional>
#include <utility>
#include <variant>

#include "DataStructures/Graphs/BlockCutTree.hpp"

#include "Exceptions/Assertions.hpp"

namespace egoa {

/**
 * @brief      Traverses a block-cut tree in a post-order traversal, i.e., a
 *             node of the tree is visited directly after all its child nodes
 *             have been visited.
 *
 * @details    This base implementation does nothing for each node. To do
 *             something useful, implement the corresponding member function:
 *               - VisitLeaf
 *               - VisitCutVertex
 *               - VisitBlock
 *               - VisitRoot
 *
 * @tparam     GraphType  The type of the graph for which the block-cut tree was
 *                        computed.
 *
 * @ingroup    bctree
 */
template<typename GraphType>
class BlockCutTreeTraversal {
public:
    using TGraph = GraphType;
    using TTree = BlockCutTree<TGraph>;
    using Block = typename TTree::Block;
    using CutVertex = typename TTree::CutVertex;
    using TNode = std::variant<std::reference_wrapper<Block const>,
                               std::reference_wrapper<CutVertex const>>;


    /// @name Constructors
    /// @{
#pragma mark CONSTRUCTORS
    /**
     * @brief      A constructor.
     *
     * @details    The root is set to the first block.
     *
     * @param      bcTree  The block-cut tree.
     * @param      visitor The visitor.
     */
    BlockCutTreeTraversal(BlockCutTree<TGraph> const & bcTree)
    : BlockCutTreeTraversal(bcTree, std::cref(bcTree.BlockAt(0)))
    {}

    /**
     * @brief      A constructor.
     *
     * @param      bcTree  The block-cut tree.
     * @param      root    The root.
     * @param      visitor The visitor.
     */
    BlockCutTreeTraversal(BlockCutTree<TGraph> const & bcTree,
                          TNode root)
    : bcTree_(bcTree),
      root_(std::move(root)),
      rootId_(NodeToId(root_))
    {}

    /**
     * @brief      A constructor.
     *
     * @param      bcTree  The block-cut tree.
     * @param      root    The root.
     * @param      visitor The visitor.
     */
    BlockCutTreeTraversal(BlockCutTree<TGraph> const & bcTree,
                          CutVertex const & root)
    : bcTree_(bcTree),
      root_(root)
    {}
    /// @}

    /// @name Accessors
    /// @{
#pragma mark ACCESSORS
    TNode & Root() {
        return root_;
    }

    TNode const & Root() const {
        return root_;
    }
    /// @}

    /// @name Algorithm Execution
    /// @{
#pragma mark ALGORITHM_EXECUTION
    /**
     * @brief       Runs the algorithm.
     */
    void Run() {
        nodeStack_.push(rootId_);

        while (!nodeStack_.empty()) {
            Types::index currentId = nodeStack_.top();

            if (visited_[currentId]) {
                // All children of the current node have been visited.
                nodeStack_.pop();
                if (currentId == rootId_) {
                    VisitRoot(root_);
                } else if (IsBlock(currentId)) {
                    auto const & block = BlockAt(currentId);
                    if (block.IsLeaf()) {
                        VisitLeaf(block);
                    } else {
                        VisitBlock(block);
                    }
                } else {
                    VisitCutVertex(CutVertexAt(currentId));
                }
            } else {
                // We are visiting the node for the first time and have to visit
                // all its children first.
                visited_[currentId] = true;
                if (IsBlock(currentId)) {
                    auto const & block = BlockAt(currentId);
                    for (Types::vertexId neighbor : block.CutVertices()) {
                        if (visited_[neighbor]) continue;
                        nodeStack_.push(neighbor);
                    }
                } else {
                    auto const & cutVertex = CutVertexAt(currentId);
                    for (Types::blockId neighbor : cutVertex.Blocks()) {
                        Types::index normalizedId = bcTree_.Graph().NumberOfVertices() + neighbor;
                        if (visited_[normalizedId]) continue;
                        nodeStack_.push(normalizedId);
                    }
                }
            }
        }
    }
    /// @}

protected:
    /// @name Visiting
    /// @{
#pragma mark VISITING
    /**
     * @brief      This function is called for each leaf.
     *
     * @details    @c VisitBlock is not called for the block.
     *             This function is not called for the root even if the root has
     *             degree 1.
     *
     * @param      block  The block.
     */
    virtual void VisitLeaf(Block const & block) {};

    /**
     * @brief      This function is called for each cut-vertex.
     *
     * @details    This function is not called for the root even if the root is
     *             a cut-vertex.
     *
     * @param      cutVertex  The cut-vertex.
     */
    virtual void VisitCutVertex(CutVertex const & cutVertex) {};

    /**
     * @brief      This function is called for each inner block.
     *
     * @details    This function is not called for the root even if the root is
     *             a block.
     *
     * @param      block  The block.
     */
    virtual void VisitBlock(Block const & block) {};

    /**
     * @brief      This function is called for the root.
     *
     * @param      root  The root.
     */
    virtual void VisitRoot(TNode root) {};
    /// @}

private:

    /// @name Auxiliary
    /// @{
#pragma mark AUXILIARY
    bool IsBlock(Types::index id) const {
        ESSENTIAL_ASSERT(id < visited_.size());
        return id >= bcTree_.Graph().NumberOfVertices();
    }

    bool IsCutVertex(Types::index id) const {
        ESSENTIAL_ASSERT(id < visited_.size());
        return id < bcTree_.Graph().NumberOfVertices();
    }

    Types::index NodeToId(TNode const & node) const {
        if (std::holds_alternative<std::reference_wrapper<Block const>>(node)) {
            return std::get<std::reference_wrapper<Block const>>(node).get().Identifier()
                   + bcTree_.Graph().NumberOfVertices();
        } else {
            return std::get<std::reference_wrapper<CutVertex const>>(node).get().Identifier();
        }
    }

    Block const & BlockAt(Types::index identifier) const {
        ESSENTIAL_ASSERT(IsBlock(identifier));
        return bcTree_.BlockAt(identifier - bcTree_.Graph().NumberOfVertices());
    }

    CutVertex const & CutVertexAt(Types::index identifier) const {
        ESSENTIAL_ASSERT(IsCutVertex(identifier));
        return bcTree_.CutVertexAt(identifier);
    }
    /// @}

    /// @name Input Members
    /// @{
#pragma mark INPUT_MEMBERS
    BlockCutTree<TGraph> const & bcTree_;
    TNode root_;
    Types::index rootId_;
    /// @}

    /// @name Members for Traversal
    /// @{
#pragma mark TRAVERSAL_MEMBERS
    /**
     * @brief      The identifiers of the nodes on the stack.
     *
     * @details    To distiguish between block and cut-vertex identifiers, the
     *             block identifiers have an added offset of
     *             @c bcTree_.Graph().NumberOfVertices().
     */
    std::stack<Types::index, std::vector<Types::index>> nodeStack_;
    /**
     * @brief      Whether the node with the given identifier has been visited.
     */
    std::vector<bool> visited_ = std::vector<bool>(bcTree_.Graph().NumberOfVertices() + bcTree_.NumberOfBlocks(), false);
    /// @}
};

} // namespace egoa

#endif //EGOA__ALGORITHMS__BLOCK_CUT_TREE_TRAVERSAL_HPP

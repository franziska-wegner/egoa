/*
 * TestBlockCutTree.cpp
 *
 *  Created on: May 15, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */

#include "TestBlockCutTree.hpp"

namespace egoa::test {

////////////////////////////////////////////////////////////////////////////////
/// Triangle ///////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#pragma mark TestBlockCutTreeTriangle
TEST_F(TestBlockCutTreeTriangle, BasicProperties) {
    auto result = egoa::buildBlockCutTree(graph_);

    EXPECT_EQ(1, result.NumberOfBlocks());
    EXPECT_EQ(0, result.NumberOfCutVertices());
}

TEST_F(TestBlockCutTreeTriangle, Leaf) {
    auto result = egoa::buildBlockCutTree(graph_);

    EXPECT_TRUE(result.BlockAt(0).IsLeaf());
}


TEST_F(TestBlockCutTreeTriangle, MappingVertices) {
    auto result = egoa::buildBlockCutTree(graph_);

    for (auto const & vertex : graph_.Vertices()) {
        std::vector<Types::blockId> expectedBlocks{0};
        EXPECT_EQ(expectedBlocks, result.BlocksOfVertex(vertex.Identifier()));
        EXPECT_FALSE(result.IsCutVertex(vertex.Identifier()));
    }
}

TEST_F(TestBlockCutTreeTriangle, MappingEdges) {
    auto result = egoa::buildBlockCutTree(graph_);

    for (auto const & edge : graph_.Edges()) {
        EXPECT_EQ(0, result.BlockOfEdge(edge.Identifier()));
    }
}

TEST_F(TestBlockCutTreeTriangle, Block) {
    auto result = egoa::buildBlockCutTree(graph_);

    ASSERT_EQ(1, result.NumberOfBlocks());

    auto & block = result.BlockAt(0);
    EXPECT_EQ(0, block.Identifier());

    EXPECT_EQ(&graph_, &block.Subgraph().UnderlyingGraph());
    EXPECT_EQ(graph_.NumberOfVertices(), block.Subgraph().Vertices().size());
    EXPECT_EQ(graph_.NumberOfEdges(), block.Subgraph().Edges().size());

    EXPECT_TRUE(block.CutVertices().empty());

    EXPECT_TRUE(block.IsLeaf());
    EXPECT_FALSE(block.IsBridge());
}

////////////////////////////////////////////////////////////////////////////////
/// Star ///////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#pragma mark TestBlockCutTreeStar
TEST_F(TestBlockCutTreeStar, BasicProperties) {
    auto result = egoa::buildBlockCutTree(graph_);

    EXPECT_EQ(3, result.NumberOfBlocks());
    EXPECT_EQ(1, result.NumberOfCutVertices());
}

TEST_F(TestBlockCutTreeStar, Vertices) {
    auto result = egoa::buildBlockCutTree(graph_);

    for (auto const & vertex : graph_.Vertices()) {
        Types::vertexId id = vertex.Identifier();

        EXPECT_EQ(id == center_, result.IsCutVertex(id));
    }
}

TEST_F(TestBlockCutTreeStar, Center) {
    auto result = egoa::buildBlockCutTree(graph_);

    ASSERT_TRUE(result.IsCutVertex(center_));

    auto const & cutVertex = result.CutVertexAt(center_);

    EXPECT_EQ(center_, cutVertex.Identifier());

    std::vector<Types::blockId> expectedAdjacentBlocks{0, 1, 2};
    ExpectSameContent(expectedAdjacentBlocks, cutVertex.Blocks());
}

TEST_F(TestBlockCutTreeStar, Blocks) {
    auto result = egoa::buildBlockCutTree(graph_);

    std::vector<Types::blockId> blocks;
    for (auto const & edge : graph_.Edges()) {
        auto id = edge.Identifier();

        auto blockId = result.BlockOfEdge(id);
        auto const & block = result.BlockAt(blockId);

        blocks.push_back(blockId);

        EXPECT_TRUE(block.IsLeaf());
        EXPECT_TRUE(block.IsBridge());

        // Test that the block contains only the edge id
        using std::begin, std::end;
        std::vector<Types::edgeId> expectedEdges{id};
        auto edges = block.Subgraph().Edges();
        std::vector<Types::edgeId> actualEdges(begin(edges), end(edges));
        ExpectSameContent(expectedEdges, actualEdges);

        // Test that the block has one cut-vertex
        EXPECT_EQ(1, block.CutVertices().size());
        EXPECT_EQ(center_, block.CutVertices()[0]);
    }

    std::vector<Types::blockId> expectedBlocks{0, 1, 2};
    ExpectSameContent(expectedBlocks, blocks);

}

////////////////////////////////////////////////////////////////////////////////
/// Triangle with leaf /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
#pragma mark TestBlockCutTreeTriangleWithLeaf
TEST_F(TestBlockCutTreeTriangleWithLeaf, BasicProperties) {
    auto result = egoa::buildBlockCutTree(graph_);

    EXPECT_EQ(2, result.NumberOfBlocks());
    EXPECT_EQ(1, result.NumberOfCutVertices());
}

TEST_F(TestBlockCutTreeTriangleWithLeaf, Vertices) {
    auto result = egoa::buildBlockCutTree(graph_);

    for (auto const & vertex : graph_.Vertices()) {
        auto id = vertex.Identifier();

        EXPECT_EQ(id == center_, result.IsCutVertex(id));
    }
}

TEST_F(TestBlockCutTreeTriangleWithLeaf, CutVertex) {
    auto result = egoa::buildBlockCutTree(graph_);

    ASSERT_TRUE(result.IsCutVertex(center_));

    auto const & cutVertex = result.CutVertexAt(center_);

    EXPECT_EQ(center_, cutVertex.Identifier());

    std::vector<Types::blockId> expectedAdjacentBlocks{0, 1};
    ExpectSameContent(expectedAdjacentBlocks, cutVertex.Blocks());
}

TEST_F(TestBlockCutTreeTriangleWithLeaf, Blocks) {
    auto result = egoa::buildBlockCutTree(graph_);


    for (auto const & edge : graph_.Edges()) {
        auto id = edge.Identifier();
        auto blockOfEdge = result.BlockOfEdge(id);

        EXPECT_TRUE(result.BlockAt(blockOfEdge).IsLeaf());

        // Test that the block contains the edge id
        using std::begin, std::end;
        auto edges = result.BlockAt(blockOfEdge).Subgraph().Edges();
        auto it = std::find(begin(edges), end(edges), id);
        EXPECT_NE(end(edges), it);
    }
}

TEST_F(TestBlockCutTreeTriangleWithLeaf, Cycle) {
    auto result = egoa::buildBlockCutTree(graph_);

    Types::blockId const bId = result.BlockOfEdge(largeCycleEdges_.front());
    for (Types::edgeId eId : largeCycleEdges_) {
        EXPECT_EQ(bId, result.BlockOfEdge(eId));
    }

    auto const & block = result.BlockAt(bId);

    EXPECT_EQ(bId, block.Identifier());
    EXPECT_TRUE(block.IsLeaf());
    EXPECT_FALSE(block.IsBridge());

    Subgraph<const TGraph> expectedSubgraph(&graph_,
                                            largeCycleVertices_,
                                            largeCycleEdges_);

    EXPECT_EQ(expectedSubgraph, block.Subgraph());
}

TEST_F(TestBlockCutTreeTriangleWithLeaf, Bridge) {
    auto result = egoa::buildBlockCutTree(graph_);

    Types::blockId const bId = result.BlockOfEdge(bridgeEdge_);
    auto const & block = result.BlockAt(bId);

    EXPECT_EQ(bId, block.Identifier());
    EXPECT_TRUE(block.IsLeaf());
    EXPECT_TRUE(block.IsBridge());

    Subgraph<const TGraph> expectedSubgraph(&graph_,
                                            bridgeVertices_,
                                            {bridgeEdge_});

    EXPECT_EQ(expectedSubgraph, block.Subgraph());
}

} // namespace egoa::test

/*
 * TestBlockCutTree.hpp
 *
 *  Created on: May 15, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */

#ifndef EGOA__TESTS__DATA_STRUCTURES__GRAPHS__TEST_BLOCK_CUT_TREE_HPP
#define EGOA__TESTS__DATA_STRUCTURES__GRAPHS__TEST_BLOCK_CUT_TREE_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "DataStructures/Graphs/BlockCutTree.hpp"
#include "DataStructures/Graphs/StaticGraph.hpp"

#include "Helper/TestHelper.hpp"

namespace egoa::test {

using TGraph = egoa::StaticGraph<MinimalProperties, MinimalProperties>;

template<typename T>
void printBlocks(BlockCutTree<T> const & tree) {
    for (Types::blockId i = 0; i < tree.NumberOfBlocks(); ++i) {
        std::cout << tree.BlockAt(i).Subgraph() << std::endl;
    }
}

class TestBlockCutTreeTriangle : public ::testing::Test {
protected:
    void SetUp() override {
        graph_.AddVertex(MinimalProperties(0));
        graph_.AddVertex(MinimalProperties(1));
        graph_.AddVertex(MinimalProperties(2));
        graph_.AddEdge(0, 1, MinimalProperties(1));
        graph_.AddEdge(2, 0, MinimalProperties(20));
        graph_.AddEdge(1, 2, MinimalProperties(12));
    }

    TGraph graph_;
};

class TestBlockCutTreeStar : public ::testing::Test {
protected:
    void SetUp() override {
        graph_.AddVertex(MinimalProperties(0));
        center_ = graph_.AddVertex(MinimalProperties(1));
        graph_.AddVertex(MinimalProperties(2));
        graph_.AddVertex(MinimalProperties(3));
        graph_.AddEdge(0, 1, MinimalProperties(1));
        graph_.AddEdge(1, 2, MinimalProperties(12));
        graph_.AddEdge(3, 1, MinimalProperties(31));
    }

    TGraph graph_;
    Types::vertexId center_;
};

class TestBlockCutTreeTriangleWithLeaf : public ::testing::Test {
protected:
    void SetUp() override {
        Types::vertexId vId;
        vId = graph_.AddVertex(MinimalProperties(0));
        largeCycleVertices_.push_back(vId);

        vId = graph_.AddVertex(MinimalProperties(1));
        largeCycleVertices_.push_back(vId);
        bridgeVertices_.push_back(vId);
        center_ = vId;

        vId = graph_.AddVertex(MinimalProperties(2));
        largeCycleVertices_.push_back(vId);

        vId = graph_.AddVertex(MinimalProperties(3));
        bridgeVertices_.push_back(vId);

        Types::edgeId eId;

        eId = graph_.AddEdge(0, 1, MinimalProperties(1));
        largeCycleEdges_.push_back(eId);
        eId = graph_.AddEdge(0, 2, MinimalProperties(2));
        largeCycleEdges_.push_back(eId);
        eId = graph_.AddEdge(1, 2, MinimalProperties(12));
        largeCycleEdges_.push_back(eId);
        eId = graph_.AddEdge(3, 1, MinimalProperties(31));
        bridgeEdge_ = eId;
    }

    TGraph graph_;
    Types::vertexId center_;
    std::vector<Types::vertexId> bridgeVertices_;
    Types::edgeId bridgeEdge_;
    std::vector<Types::vertexId> largeCycleVertices_;
    std::vector<Types::edgeId> largeCycleEdges_;
};

} // namespace egoa::test

#endif // EGOA__TESTS__DATA_STRUCTURES__GRAPHS__TEST_BLOCK_CUT_TREE_HPP

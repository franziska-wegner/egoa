/*
 * TestSpanningTree.hpp
 *
 *  Created on: May 8, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */

#ifndef EGOA___TESTS___ALGORITHMS___SPANNING_TREE__TEST_SPANNING_TREE_HPP
#define EGOA___TESTS___ALGORITHMS___SPANNING_TREE__TEST_SPANNING_TREE_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>

#include "Auxiliary/Comparators.hpp"
#include "Auxiliary/Types.hpp"

#include "Algorithms/SpanningTree/Kruskal.hpp"
#include "Algorithms/SpanningTree/Prim.hpp"

#include "DataStructures/Graphs/StaticGraph.hpp"

#include "Helper/TestHelper.hpp"

namespace egoa::test {

using TGraph = egoa::StaticGraph<MinimalProperties, MinimalProperties>;
using TWeight = Types::integer;
using TWeightVector = std::vector<TWeight>;

template<typename GraphType>
class PrivateIdBasedComparator {
public:
    PrivateIdBasedComparator(GraphType const & graph) : graph_(graph) {}

    bool operator()(egoa::Types::edgeId lhs, egoa::Types::edgeId rhs) {
        return graph_.EdgeAt(lhs).Properties().PrivateId()
             < graph_.EdgeAt(rhs).Properties().PrivateId();
    }

private:
    GraphType const & graph_;
};

/**
 * @brief      A fixture for testing MST algorithms on empty graphs.
 *
 * @tparam     AlgorithmType  The type of the algorithm under test.
 */
template<typename AlgorithmType>
class TestSpanningTreeEmpty : public ::testing::Test {
protected:
    using TAlgorithm = AlgorithmType;

    TGraph graph_;
    TWeightVector weights_;
    TAlgorithm algo_{graph_, PrivateIdBasedComparator(graph_)};
};

template<typename AlgorithmType>
class TestSpanningTreeTriangle : public ::testing::Test {
protected:
    using TAlgorithm = AlgorithmType;

    TestSpanningTreeTriangle() {
        graph_.AddVertex(MinimalProperties(0));
        graph_.AddVertex(MinimalProperties(1));
        graph_.AddVertex(MinimalProperties(2));
        graph_.AddEdge(0, 1, MinimalProperties(12));
        graph_.AddEdge(1, 2, MinimalProperties(21));
        graph_.AddEdge(0, 2, MinimalProperties(23));
    }

    TGraph graph_;
    TAlgorithm algo_{graph_, PrivateIdBasedComparator(graph_)};
};


template<typename AlgorithmType>
class TestSpanningTreeFiveVertexGraph : public ::testing::Test {
protected:
    using TAlgorithm = AlgorithmType;

    TestSpanningTreeFiveVertexGraph() {
        graph_.AddVertex(MinimalProperties(0));
        graph_.AddVertex(MinimalProperties(1));
        graph_.AddVertex(MinimalProperties(2));
        graph_.AddVertex(MinimalProperties(3));
        graph_.AddVertex(MinimalProperties(4));
        graph_.AddEdge(0, 1, MinimalProperties(12));
        graph_.AddEdge(1, 2, MinimalProperties(15));
        graph_.AddEdge(0, 2, MinimalProperties(9));
        graph_.AddEdge(3, 0, MinimalProperties(8));
        graph_.AddEdge(4, 3, MinimalProperties(2));
        graph_.AddEdge(4, 2, MinimalProperties(8));
    }

    TGraph graph_;
    TAlgorithm algo_{graph_, PrivateIdBasedComparator(graph_)};
};

using AlgorithmTypes = ::testing::Types<
                          egoa::Kruskal<TGraph>,
                          egoa::Prim<TGraph>
                        >;

TYPED_TEST_SUITE(TestSpanningTreeEmpty, AlgorithmTypes);
TYPED_TEST_SUITE(TestSpanningTreeTriangle, AlgorithmTypes);
TYPED_TEST_SUITE(TestSpanningTreeFiveVertexGraph, AlgorithmTypes);

} // namespace egoa::test

#endif //EGOA___TESTS___ALGORITHMS___SPANNING_TREE__TEST_SPANNING_TREE_HPP

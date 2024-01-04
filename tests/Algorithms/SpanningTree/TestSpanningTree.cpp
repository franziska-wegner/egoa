/*
 * TestSpanningTree.cpp
 *
 *  Created on: May 8, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */

#include "TestSpanningTree.hpp"

namespace egoa::test {

#pragma mark EMPTY_GRAPH

TYPED_TEST(TestSpanningTreeEmpty, Run) {
    Subgraph<TGraph> expectedResult(&this->graph_, {}, {});

    this->algo_.Run();
    auto result = this->algo_.Result();
    EXPECT_EQ(expectedResult, result);
}

TYPED_TEST(TestSpanningTreeTriangle, Run) {
    Subgraph<TGraph> expectedResult(&this->graph_, {0, 1, 2}, {0, 1});

    this->algo_.Run();
    auto result = this->algo_.Result();
    EXPECT_EQ(expectedResult, result);
}

TYPED_TEST(TestSpanningTreeFiveVertexGraph, Run) {
    Subgraph<TGraph> expectedResult(&this->graph_,
        {0, 1, 2, 3, 4},
        {0, 3, 4, 5});

    this->algo_.Run();
    auto result = this->algo_.Result();
    EXPECT_EQ(expectedResult, result);
}

} // namespace egoa::test

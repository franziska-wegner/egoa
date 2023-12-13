/*
 * TestDynamicGraph.hpp
 *
 *  Created on: Mar 7, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */

#ifndef EGOA___TESTS___DATA_STRUCTURES___GRAPHS__TEST_DYNAMIC_GRAPH_HPP
#define EGOA___TESTS___DATA_STRUCTURES___GRAPHS__TEST_DYNAMIC_GRAPH_HPP

#include <unordered_map>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Helper/TestHelper.hpp"
#include "DataStructures/Graphs/TestGraph.hpp"

#include "DataStructures/Graphs/DynamicGraph.hpp"

namespace egoa::test {

class TestDynamicGraphEmpty
    : public TestGraphEmpty<egoa::DynamicGraph<MinimalProperties, MinimalProperties>> {
};

using TestDynamicGraphEmptyDeathTest = TestDynamicGraphEmpty;

class TestDynamicGraphSingleVertex
    : public TestGraphSingleVertex<egoa::DynamicGraph<MinimalProperties, MinimalProperties>> {
};

class TestDynamicGraphFourVertices
    : public TestGraphFourVertices<egoa::DynamicGraph<MinimalProperties, MinimalProperties>> {
};

class TestDynamicGraphBidirectedPath
    : public TestGraphBidirectedPath<egoa::DynamicGraph<MinimalProperties, MinimalProperties>> {
};

class TestDynamicGraphStar
    : public TestGraphStar<egoa::DynamicGraph<MinimalProperties, MinimalProperties>> {
};

} // namespace egoa::test

#endif // EGOA___TESTS___DATA_STRUCTURES___GRAPHS__TEST_DYNAMIC_GRAPH_HPP

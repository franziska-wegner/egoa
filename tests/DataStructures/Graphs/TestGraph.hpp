/*
 * TestGraph.hpp
 *
 *  Created on: Feb 12, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */

#ifndef EGOA___TESTS___DATA_STRUCTURES___GRAPHS__TEST_GRAPH_HPP
#define EGOA___TESTS___DATA_STRUCTURES___GRAPHS__TEST_GRAPH_HPP

#include <unordered_map>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Helper/TestHelper.hpp"

#include "DataStructures/Graphs/StaticGraph.hpp"
#include "DataStructures/Graphs/DynamicGraph.hpp"

namespace egoa::test {

template<typename GraphType>
void ExpectInDegrees(const GraphType & graph, const std::vector<Types::count> & expectedDegrees) {
    ASSERT_EQ(graph.NumberOfVertices(), expectedDegrees.size())
        << "Expected number of degrees does not equal the number of vertices";
    for (Types::vertexId i = 0; i < graph.NumberOfVertices(); ++i) {
        EXPECT_EQ(expectedDegrees[i], graph.InDegreeAt(i));
    }
}

template<typename GraphType>
void ExpectOutDegrees(const GraphType & graph, const std::vector<Types::count> & expectedDegrees) {
    ASSERT_EQ(graph.NumberOfVertices(), expectedDegrees.size())
        << "Expected number of degrees does not equal the number of vertices";
    for (Types::vertexId i = 0; i < graph.NumberOfVertices(); ++i) {
        EXPECT_EQ(expectedDegrees[i], graph.OutDegreeAt(i));
    }
}

/**
 * @brief Fixture for testing graphs
 */
template<typename GraphType>
class TestGraph : public ::testing::Test {
protected:
    using TGraph            = GraphType;
    using TVertex           = typename TGraph::TVertex;
    using TVertexProperties = typename TGraph::TVertexProperties;
    using TEdge             = typename TGraph::TEdge;
    using TEdgeProperties   = typename TGraph::TEdgeProperties;

    TestGraph(Types::string name = "Empty Graph") : graph_(name) {}

    Types::string assertionString(Types::string function, Types::string message) const {
        return buildAssertionString<GraphType>(function, message);
    }

    TGraph graph_;
    const TGraph & graphConst_ = graph_;
};

/**
 * Fixture for testing a graph without vertices and edges.
 */
template<typename GraphType>
using TestGraphEmpty = TestGraph<GraphType>;

/**
 * Fixture for death tests on an empty graph.
 */
template<typename GraphType>
using TestGraphEmptyDeathTest = TestGraph<GraphType>;

/**
 * @brief      Fixture for testing a graph with one vertex.
 *
 * @tparam     GraphType  The type of the graph.
 */
template<typename GraphType>
class TestGraphSingleVertex : public TestGraph<GraphType> {
protected:
    using typename TestGraph<GraphType>::TVertex;
    using typename TestGraph<GraphType>::TVertexProperties;

    TestGraphSingleVertex() : TestGraph<GraphType>("Single Vertex Graph") {};

    void SetUp() override {
        this->graph_.Name() = "Single Vertex Graph";
        id_ = this->graph_.AddVertex( TVertexProperties(0) );
    }

    Types::vertexId id_;
};

template<typename GraphType>
using TestGraphSingleVertexDeathTest = TestGraphSingleVertex<GraphType>;

/**
 * @brief      Fixture for testing a graph with four vertices and no edges.
 * @details    The identifier of the vertices are stored in @p vertexIds_.
 */
template<typename GraphType>
class TestGraphFourVertices : public TestGraph<GraphType> {
protected:
    using typename TestGraph<GraphType>::TVertex;
    using typename TestGraph<GraphType>::TVertexProperties;
    using typename TestGraph<GraphType>::TEdge;
    using typename TestGraph<GraphType>::TEdgeProperties;

    TestGraphFourVertices() : TestGraph<GraphType>("4K_1") {}

    void SetUp() override {
        for ( Types::count i = 0; i < 4; ++i ) 
        {
            vertexIds_.push_back(this->graph_.AddVertex(TVertexProperties(i)));
        }
    }

    std::vector<Types::vertexId> vertexIds_;
};

template<typename GraphType>
using TestGraphFourVerticesDeathTest = TestGraphFourVertices<GraphType>;

/**
 * @brief      Fixture for testing a graph with bidirected edges
 * @details    The graph is a path on three vertices.
 */
template<typename GraphType>
class TestGraphBidirectedPath : public TestGraph<GraphType> {
protected:
    using typename TestGraph<GraphType>::TVertex;
    using typename TestGraph<GraphType>::TVertexProperties;
    using typename TestGraph<GraphType>::TEdge;
    using typename TestGraph<GraphType>::TEdgeProperties;

    TestGraphBidirectedPath() : TestGraph<GraphType>("P_3") {}

    void SetUp() override 
    {
        for ( Types::count i = 0; i < 3; ++i ) 
        {
            vertexIds_.push_back(this->graph_.AddVertex( TVertexProperties{i} ));
            TVertex vertex = this->graph_.VertexAt( vertexIds_.back() );
            mapIdToVertex_.emplace(vertexIds_.back(), vertex );
        }

        for ( Types::count i = 0; i < 2; ++i ) 
        {
            Types::index    privatId = 2 * i;
            Types::vertexId source   = i;
            Types::vertexId target   = i + 1;

            edgeIds_.push_back(this->graph_.AddEdge(source, target, TVertexProperties(privatId) ));
            Types::edgeId edgeId = edgeIds_.back();
            TEdge edge = this->graph_.EdgeAt(edgeId);
            mapIdToEdge_.emplace(edgeIds_.back(), edge);

            // Reverse edge
            privatId = 2 * i + 1;
            source   = i + 1;
            target   = i;

            edgeIds_.push_back(this->graph_.AddEdge(source, target, TVertexProperties(privatId) ));
            edgeId = edgeIds_.back();
            edge   = this->graph_.EdgeAt(edgeId);
            mapIdToEdge_.emplace(edgeIds_.back(), edge);
        }
    }

    std::vector<Types::vertexId>                 vertexIds_;
    std::unordered_map<Types::vertexId, TVertex> mapIdToVertex_;
    std::vector<Types::edgeId>                   edgeIds_;
    std::unordered_map<Types::edgeId, TEdge>     mapIdToEdge_;
};

template<typename GraphType>
class TestGraphStar : public TestGraph<GraphType> {
protected:
    using TVertex           = typename TestGraph<GraphType>::TVertex;
    using TVertexProperties = typename TestGraph<GraphType>::TVertexProperties;
    using TEdge             = typename TestGraph<GraphType>::TEdge;
    using TEdgeProperties   = typename TestGraph<GraphType>::TEdgeProperties;

    TestGraphStar() : TestGraph<GraphType>("K_1_3") {}

    void SetUp() override 
    {
        centerId_ = this->graph_.AddVertex(TVertexProperties(0));
        vertexIds_.push_back(centerId_);
        TVertex vertex = this->graph_.VertexAt(vertexIds_.back());
        mapIdToVertex_.emplace(centerId_, vertex ); // TVertex(0));
        for ( Types::count i = 0; i < 3; ++i ) 
        {
            leafIds_.push_back(this->graph_.AddVertex(TVertexProperties(i + 1)));
            vertexIds_.push_back(leafIds_.back());
            vertex = this->graph_.VertexAt(vertexIds_.back());
            mapIdToVertex_.emplace(leafIds_.back(), vertex );
        }
        for ( Types::count i = 0; i < 3; ++i ) 
        {
            edgeIds_.push_back(this->graph_.AddEdge(centerId_, leafIds_[i], TEdgeProperties(i) ));
            mapIdToEdge_.emplace(edgeIds_.back(), this->graph_.EdgeAt(edgeIds_.back()) );
        }
    }

    Types::vertexId centerId_;
    std::vector<Types::vertexId> leafIds_;
    std::vector<Types::vertexId> vertexIds_;
    std::unordered_map<Types::vertexId, TVertex> mapIdToVertex_;
    std::vector<Types::edgeId> edgeIds_;
    std::unordered_map<Types::edgeId, TEdge> mapIdToEdge_;
};

/**
 * @brief      A fixture for DynamicGraph that contains a star with three leaves.
 * @details    The graph was constructed by first adding and then deleting some
 *             edges and vertices.
 *
 * @tparam     VertexPropertiesType  The types of the vertices
 * @tparam     EdgePropertiesType    The types of the edges
 */
template<typename VertexPropertiesType, typename EdgePropertiesType>
class TestGraphStar<egoa::DynamicGraph<VertexPropertiesType, EdgePropertiesType>>
    : public TestGraph<egoa::DynamicGraph<VertexPropertiesType, EdgePropertiesType>> {
protected:
    using TVertexProperties = VertexPropertiesType;
    using TEdgeProperties   = EdgePropertiesType;
    using TGraph            = egoa::DynamicGraph<TVertexProperties, TEdgeProperties>;
    using TVertex           = typename TGraph::TVertex;
    using TEdge             = typename TGraph::TEdge;

    TestGraphStar() : TestGraph<TGraph>("K_1_3") {}

    void SetUp() override {
        // add vertices
        centerId_ = this->graph_.AddVertex(TVertexProperties(0));
        vertexIds_.push_back(centerId_);
        TVertex vertex = this->graph_.VertexAt( vertexIds_.back() );
        mapIdToVertex_.emplace(centerId_, vertex);
        Types::vertexId vertexToRemove = this->graph_.AddVertex(TVertexProperties(234));
        for ( Types::count i = 0; i < 3; ++i ) 
        {
            leafIds_.push_back(this->graph_.AddVertex( TVertexProperties{i + 1} ));
            vertexIds_.push_back(leafIds_.back());
            vertex = this->graph_.VertexAt( vertexIds_.back() );
            mapIdToVertex_.emplace(leafIds_.back(), vertex );
        }

        // add edges
        std::vector<Types::edgeId> edgesToRemove;
        edgesToRemove.push_back(this->graph_.AddEdge(centerId_, vertexToRemove, TEdgeProperties{8} ));
        edgesToRemove.push_back(this->graph_.AddEdge(leafIds_[0], leafIds_[2], TEdgeProperties(5) ));
        this->graph_.AddEdge(leafIds_[1], vertexToRemove, TEdgeProperties{234});
        this->graph_.AddEdge(vertexToRemove, leafIds_[2], TEdgeProperties{123});
        for (Types::count i = 0; i < 3; ++i) 
        {
            TEdgeProperties edgeProperties{i};
            edgeIds_.push_back(this->graph_.AddEdge(centerId_, leafIds_[i], edgeProperties));
            TEdge edge = this->graph_.Edge(centerId_, leafIds_[i]);
            mapIdToEdge_.emplace(edgeIds_.back(), edge);
        }

        // remove edges
        for (auto e : edgesToRemove) 
        {
            this->graph_.RemoveEdgeAt(e);
        }

        // remove vertex
        this->graph_.RemoveVertexAt(vertexToRemove);
    }

    Types::vertexId centerId_;
    std::vector<Types::vertexId> leafIds_;
    std::vector<Types::vertexId> vertexIds_;
    std::unordered_map<Types::vertexId, TVertex> mapIdToVertex_;
    std::vector<Types::edgeId> edgeIds_;
    std::unordered_map<Types::edgeId, TEdge> mapIdToEdge_;
};

using GraphTypes = ::testing::Types<
                      egoa::StaticGraph<MinimalProperties, MinimalProperties>,
                      egoa::DynamicGraph<MinimalProperties, MinimalProperties>
                    >;

template<>
struct FileName<egoa::StaticGraph<MinimalProperties, MinimalProperties>> 
{
    static Types::string Name() 
    {
        return "StaticGraph.hpp";
    }
};

template<>
struct FileName<egoa::DynamicGraph<MinimalProperties, MinimalProperties>> {
    static Types::string Name() {
        return "DynamicGraph.hpp";
    }
};

TYPED_TEST_SUITE(TestGraphEmpty, GraphTypes);
TYPED_TEST_SUITE(TestGraphEmptyDeathTest, GraphTypes);
TYPED_TEST_SUITE(TestGraphSingleVertex, GraphTypes);
TYPED_TEST_SUITE(TestGraphSingleVertexDeathTest, GraphTypes);
TYPED_TEST_SUITE(TestGraphFourVertices, GraphTypes);
TYPED_TEST_SUITE(TestGraphFourVerticesDeathTest, GraphTypes);
TYPED_TEST_SUITE(TestGraphBidirectedPath, GraphTypes);
TYPED_TEST_SUITE(TestGraphStar, GraphTypes);


} // namespace egoa::test

#endif // EGOA___TESTS___DATA_STRUCTURES___GRAPHS__TEST_GRAPH_HPP

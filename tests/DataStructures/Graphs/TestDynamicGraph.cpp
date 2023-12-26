/*
 * TestDynamicGraph.cpp
 *
  *  Created on: Mar 7, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */

#include "TestDynamicGraph.hpp"

namespace egoa::test {

#pragma mark DeleteVertex

#ifdef EGOA_ENABLE_ASSERTION
    TEST_F(TestDynamicGraphEmptyDeathTest, DeleteVertex) {
        auto assertionMessage =
            this->assertionString("RemoveVertexAt", "VertexExists\\(id\\)");
        Types::vertexId id = 0;
        EXPECT_DEATH( { this->graph_.RemoveVertexAt(id); }, assertionMessage);
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestDynamicGraphEmpty
            , DeleteVertexExceptionHandling ) 
    {
        auto assertionString = this->assertionString("RemoveVertexAt", "VertexExists\\(id\\)");
        Types::vertexId id = 0;
        try {
            this->graph_.RemoveVertexAt(id);
        } catch ( std::runtime_error const & error ) 
        {
            EXPECT_THAT ( error.what(), MatchesRegex(assertionString.c_str()) );
        } catch ( ... ) 
        {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

TEST_F(TestDynamicGraphSingleVertex, DeleteVertex) {
    this->graph_.RemoveVertexAt(this->id_);

    EXPECT_FALSE(this->graphConst_.VertexExists(this->id_));
    EXPECT_EQ(0, this->graphConst_.NumberOfVertices());
}

TEST_F(TestDynamicGraphFourVertices, DeleteVertex) {
    Types::vertexId vertexToRemove = this->vertexIds_[2];

    this->graph_.RemoveVertexAt(vertexToRemove);

    EXPECT_EQ(3, this->graphConst_.NumberOfVertices());
    EXPECT_EQ(0, this->graphConst_.NumberOfEdges());

    for (Types::vertexId id : this->vertexIds_) {
        if (id == vertexToRemove) {
            EXPECT_FALSE(this->graphConst_.VertexExists(id));
        } else {
            EXPECT_TRUE(this->graphConst_.VertexExists(id));
            EXPECT_EQ(id, this->graphConst_.VertexAt(id).Properties().PrivateId());
        }
    }
}

TEST_F(TestDynamicGraphBidirectedPath, DeleteVertexMiddle) {
    Types::vertexId middleVertex = this->vertexIds_[1];

    this->graph_.RemoveVertexAt(middleVertex);

    EXPECT_EQ(2, this->graphConst_.NumberOfVertices());
    EXPECT_EQ(0, this->graphConst_.NumberOfEdges());

    for (Types::vertexId id : this->vertexIds_) {
        if (id == middleVertex) {
            EXPECT_FALSE(this->graphConst_.VertexExists(id));
        } else {
            EXPECT_TRUE(this->graphConst_.VertexExists(id));
            EXPECT_EQ(id, this->graphConst_.VertexAt(id).Properties().PrivateId());
            EXPECT_EQ(0, this->graphConst_.DegreeAt(id));
            EXPECT_EQ(0, this->graphConst_.InEdgeIdsAt(id).size());
            EXPECT_EQ(0, this->graphConst_.OutEdgeIdsAt(id).size());
        }
    }
}

TEST_F(TestDynamicGraphBidirectedPath, DeleteVertexFirst) {
    Types::vertexId firstVertex = this->vertexIds_[0];

    this->graph_.RemoveVertexAt(firstVertex);

    EXPECT_EQ(2, this->graphConst_.NumberOfVertices());
    EXPECT_EQ(2, this->graphConst_.NumberOfEdges());

    for (Types::vertexId id : this->vertexIds_) {
        if (id == firstVertex) {
            EXPECT_FALSE(this->graphConst_.VertexExists(id));
        } else {
            EXPECT_TRUE(this->graphConst_.VertexExists(id));
            EXPECT_EQ(id, this->graphConst_.VertexAt(id).Properties().PrivateId());
            EXPECT_EQ(2, this->graphConst_.DegreeAt(id));
            EXPECT_EQ(1, this->graphConst_.InEdgeIdsAt(id).size());
            EXPECT_EQ(1, this->graphConst_.OutEdgeIdsAt(id).size());
        }
    }
}

#pragma mark UpdateVertices

TEST_F(TestDynamicGraphFourVertices, UpdateVertices) 
{
    Types::vertexId vertexToRemove = this->vertexIds_[2];
    ASSERT_EQ(2, this->graphConst_.VertexAt(vertexToRemove).Properties().PrivateId());

    this->graph_.RemoveVertexAt(vertexToRemove);
    this->graph_.UpdateVertices();

    EXPECT_EQ(3, this->graphConst_.NumberOfVertices());
    EXPECT_EQ(0, this->graphConst_.NumberOfEdges());

    std::vector<Types::vertexId> ids;
    std::vector<Types::vertexId> privateIds;

    this->graphConst_.template for_all_vertex_tuples<egoa::ExecutionPolicy::sequential>(
        [&ids, &privateIds, this](Types::vertexId id, TVertex const & vertex) 
        {
            ids.push_back(id);
            privateIds.push_back(vertex.Properties().PrivateId());

            ASSERT_TRUE(this->graphConst_.VertexExists(id));
            EXPECT_EQ(id, vertex.Identifier());
            EXPECT_EQ(vertex, this->graphConst_.VertexAt(id));
        });
    ExpectSameContent({0, 1, 2}, ids);
    ExpectSameContent({0, 1, 3}, privateIds);
}

TEST_F(TestDynamicGraphBidirectedPath, UpdateVerticesMiddle) 
{
    Types::vertexId middleVertex = this->vertexIds_[1];

    this->graph_.RemoveVertexAt(middleVertex);
    this->graph_.UpdateVertices();

    EXPECT_EQ(2, this->graphConst_.NumberOfVertices());
    EXPECT_EQ(0, this->graphConst_.NumberOfEdges());

    std::vector<Types::vertexId> ids;
    std::vector<Types::vertexId> privateIds;

    this->graphConst_.template for_all_vertex_tuples<egoa::ExecutionPolicy::sequential>(
        [&ids, &privateIds, this](Types::vertexId id, TVertex const & vertex) 
        {
            ids.push_back(id);
            privateIds.push_back(vertex.Properties().PrivateId());

            ASSERT_TRUE(this->graphConst_.VertexExists(id));
            EXPECT_EQ(id, vertex.Identifier());
            EXPECT_EQ(vertex, this->graphConst_.VertexAt(id));
            EXPECT_EQ(0, this->graphConst_.DegreeAt(id));
            EXPECT_EQ(0, this->graphConst_.InEdgeIdsAt(id).size());
            EXPECT_EQ(0, this->graphConst_.OutEdgeIdsAt(id).size());
        });
    ExpectSameContent({0, 1}, ids);
    ExpectSameContent({0, 2}, privateIds);
}

TEST_F(TestDynamicGraphBidirectedPath, UpdateVerticesFirst) 
{
    Types::vertexId firstVertex = this->vertexIds_[0];

    this->graph_.RemoveVertexAt(firstVertex);
    this->graph_.UpdateVertices();

    EXPECT_EQ(2, this->graphConst_.NumberOfVertices());
    EXPECT_EQ(2, this->graphConst_.NumberOfEdges());

    std::vector<Types::vertexId> ids;
    std::vector<Types::vertexId> privateIds;

    this->graphConst_.template for_all_vertex_tuples<egoa::ExecutionPolicy::sequential>(
        [&ids, &privateIds, this](Types::vertexId id, TVertex const & vertex) 
        {
            ids.push_back(id);
            privateIds.push_back(vertex.Properties().PrivateId());

            ASSERT_TRUE(this->graphConst_.VertexExists(id));
            EXPECT_EQ(id, vertex.Identifier());
            EXPECT_EQ(vertex, this->graphConst_.VertexAt(id));
            EXPECT_EQ(2, this->graphConst_.DegreeAt(id));
            EXPECT_EQ(1, this->graphConst_.InEdgeIdsAt(id).size());
            EXPECT_EQ(1, this->graphConst_.OutEdgeIdsAt(id).size());
        });
    ExpectSameContent({0, 1}, ids);
    ExpectSameContent({1, 2}, privateIds);

    auto privateEdgeIds = this->graphConst_.MapEdges(
        [](Types::edgeId, TEdge const & edge) {
            return edge.Properties().PrivateId();
        });
    ExpectSameContent({2, 3}, privateEdgeIds);
}

} // namespace egoa::test

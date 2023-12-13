/*
 * TestGraph.cpp
 *
 *  Created on: Feb 12, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */

#include "TestGraph.hpp"

#include <algorithm>
#include <functional>

namespace egoa::test {

#pragma mark Name
TYPED_TEST( TestGraphEmpty, Name ) {
    EXPECT_EQ("Empty Graph", this->graph_.Name());
    EXPECT_EQ("Empty Graph", this->graphConst_.Name());
}

TYPED_TEST( TestGraphSingleVertex, Name ) {
    EXPECT_EQ("Single Vertex Graph", this->graph_.Name());
    EXPECT_EQ("Single Vertex Graph", this->graphConst_.Name());
}

TYPED_TEST( TestGraphFourVertices, Name ) {
    EXPECT_EQ("4K_1", this->graph_.Name());
    EXPECT_EQ("4K_1", this->graphConst_.Name());
}

TYPED_TEST( TestGraphBidirectedPath, Name ) {
    EXPECT_EQ("P_3", this->graph_.Name());
    EXPECT_EQ("P_3", this->graphConst_.Name());
}

TYPED_TEST( TestGraphStar, Name ) {
    EXPECT_EQ("K_1_3", this->graph_.Name());
    EXPECT_EQ("K_1_3", this->graphConst_.Name());
}

#pragma mark NumberOfVertices
TYPED_TEST( TestGraphEmpty, NumberOfVertices ) {
    EXPECT_EQ(0, this->graph_.NumberOfVertices());
    EXPECT_EQ(0, this->graphConst_.NumberOfVertices());
}

TYPED_TEST( TestGraphSingleVertex, NumberOfVertices ) {
    EXPECT_EQ(1, this->graph_.NumberOfVertices());
    EXPECT_EQ(1, this->graphConst_.NumberOfVertices());
}

TYPED_TEST( TestGraphFourVertices, NumberOfVertices ) {
    EXPECT_EQ(4, this->graph_.NumberOfVertices());
    EXPECT_EQ(4, this->graphConst_.NumberOfVertices());
}

TYPED_TEST( TestGraphBidirectedPath, NumberOfVertices ) {
    EXPECT_EQ(3, this->graph_.NumberOfVertices());
    EXPECT_EQ(3, this->graphConst_.NumberOfVertices());
}

TYPED_TEST( TestGraphStar, NumberOfVertices ) {
    EXPECT_EQ(4, this->graph_.NumberOfVertices());
    EXPECT_EQ(4, this->graphConst_.NumberOfVertices());
}

#pragma mark NumberOfEdges
TYPED_TEST( TestGraphEmpty, NumberOfEdges ) {
    EXPECT_EQ(0, this->graph_.NumberOfEdges());
    EXPECT_EQ(0, this->graphConst_.NumberOfEdges());
}

TYPED_TEST( TestGraphSingleVertex, NumberOfEdges ) {
    EXPECT_EQ(0, this->graph_.NumberOfEdges());
    EXPECT_EQ(0, this->graphConst_.NumberOfEdges());
}

TYPED_TEST( TestGraphFourVertices, NumberOfEdges ) {
    EXPECT_EQ(0, this->graph_.NumberOfEdges());
    EXPECT_EQ(0, this->graphConst_.NumberOfEdges());
}

TYPED_TEST( TestGraphBidirectedPath, NumberOfEdges ) {
    EXPECT_EQ(4, this->graph_.NumberOfEdges());
    EXPECT_EQ(4, this->graphConst_.NumberOfEdges());
}

TYPED_TEST( TestGraphStar, NumberOfEdges ) {
    EXPECT_EQ(3, this->graph_.NumberOfEdges());
    EXPECT_EQ(3, this->graphConst_.NumberOfEdges());
}

#pragma mark VertexExists
TYPED_TEST( TestGraphEmpty, VertexExists ) {
    EXPECT_FALSE(this->graphConst_.VertexExists(0));
    EXPECT_FALSE(this->graphConst_.VertexExists(10));
    EXPECT_FALSE(this->graphConst_.VertexExists(Const::NONE));
}

TYPED_TEST( TestGraphSingleVertex, VertexExists ) {
    EXPECT_TRUE(this->graphConst_.VertexExists(this->id_));
    EXPECT_FALSE(this->graphConst_.VertexExists(this->id_ + 1));
    EXPECT_FALSE(this->graphConst_.VertexExists(Const::NONE));
}

TYPED_TEST( TestGraphFourVertices, VertexExists ) {
    for (auto id : this->vertexIds_) {
        EXPECT_TRUE(this->graphConst_.VertexExists(id));
    }
    using std::begin, std::end;
    Types::vertexId nonexistent = *std::max_element(begin(this->vertexIds_),
                                                   end(this->vertexIds_))
                                  + 1;
    EXPECT_FALSE(this->graphConst_.VertexExists(nonexistent));
    EXPECT_FALSE(this->graphConst_.VertexExists(Const::NONE));
}

TYPED_TEST( TestGraphBidirectedPath, VertexExists ) {
    for (auto id : this->vertexIds_) {
        EXPECT_TRUE(this->graphConst_.VertexExists(id));
    }
    using std::begin, std::end;
    Types::vertexId nonexistent = *std::max_element(begin(this->vertexIds_),
                                                   end(this->vertexIds_))
                                  + 1;
    EXPECT_FALSE(this->graphConst_.VertexExists(nonexistent));
    EXPECT_FALSE(this->graphConst_.VertexExists(Const::NONE));
}

TYPED_TEST( TestGraphStar, VertexExists ) {
    for (auto id : this->leafIds_) {
        EXPECT_TRUE(this->graphConst_.VertexExists(id));
    }
    using std::begin, std::end;
    Types::vertexId nonexistent = *std::max_element(begin(this->leafIds_),
                                                   end(this->leafIds_));
    nonexistent = std::max(nonexistent, this->centerId_) + 1;
    EXPECT_FALSE(this->graphConst_.VertexExists(nonexistent));
    EXPECT_FALSE(this->graphConst_.VertexExists(Const::NONE));
}

#pragma mark EdgeExists
TYPED_TEST( TestGraphEmpty, EdgeExists ) {
    EXPECT_FALSE(this->graphConst_.EdgeExists(0));
    EXPECT_FALSE(this->graphConst_.EdgeExists(10));
    EXPECT_FALSE(this->graphConst_.EdgeExists(Const::NONE));
}

TYPED_TEST( TestGraphSingleVertex, EdgeExists ) 
{
    EXPECT_FALSE(this->graphConst_.EdgeExists(0));
    EXPECT_FALSE(this->graphConst_.EdgeExists(10));
    EXPECT_FALSE(this->graphConst_.EdgeExists(Const::NONE));
}

TYPED_TEST( TestGraphFourVertices, EdgeExists ) 
{
    EXPECT_FALSE(this->graphConst_.EdgeExists(0));
    EXPECT_FALSE(this->graphConst_.EdgeExists(10));
    EXPECT_FALSE(this->graphConst_.EdgeExists(Const::NONE));
}

TYPED_TEST( TestGraphBidirectedPath, EdgeExists ) 
{
    for (auto id : this->edgeIds_) {
        EXPECT_TRUE(this->graphConst_.EdgeExists(id));
    }
    using std::begin, std::end;
    Types::vertexId nonexistent = *std::max_element(begin(this->edgeIds_),
                                                   end(this->edgeIds_))
                                  + 1;
    EXPECT_FALSE(this->graphConst_.EdgeExists(nonexistent));
    EXPECT_FALSE(this->graphConst_.EdgeExists(Const::NONE));
}

TYPED_TEST( TestGraphStar, EdgeExists ) 
{
    for (auto id : this->edgeIds_) 
    {
        EXPECT_TRUE(this->graphConst_.EdgeExists(id));
    }

    for (Types::index i = 0; i < 20; ++i) 
    {
        using std::begin, std::end;
        bool expected = std::find(begin(this->edgeIds_),
                                  end(this->edgeIds_),
                                  i)
                        != end(this->edgeIds_);
        EXPECT_EQ(expected, this->graphConst_.EdgeExists(i));
    }
}

#pragma mark Vertices
/// @name Tests for Vertices().size()
/// @{
#pragma mark VerticesSize
TYPED_TEST( TestGraphEmpty, VerticesSize ) 
{
    EXPECT_EQ(0, this->graph_.Vertices().size());
    EXPECT_EQ(0, this->graphConst_.Vertices().size());
}

TYPED_TEST( TestGraphSingleVertex, VerticesSize ) 
{
    EXPECT_EQ(1, this->graph_.Vertices().size());
    EXPECT_EQ(1, this->graphConst_.Vertices().size());
}

TYPED_TEST( TestGraphFourVertices, VerticesSize ) 
{
    EXPECT_EQ(4, this->graph_.Vertices().size());
    EXPECT_EQ(4, this->graphConst_.Vertices().size());
}

TYPED_TEST( TestGraphBidirectedPath, VerticesSize ) 
{
    EXPECT_EQ(3, this->graph_.Vertices().size());
    EXPECT_EQ(3, this->graphConst_.Vertices().size());
}

TYPED_TEST( TestGraphStar, VerticesSize ) 
{
    EXPECT_EQ(4, this->graph_.Vertices().size());
    EXPECT_EQ(4, this->graphConst_.Vertices().size());
}
/// @}

/// @name Tests for Vertices().empty()
/// @{
#pragma mark VerticesEmpty
TYPED_TEST( TestGraphEmpty, VerticesEmpty ) 
{
    EXPECT_TRUE(this->graph_.Vertices().empty());
    EXPECT_TRUE(this->graphConst_.Vertices().empty());
}

TYPED_TEST( TestGraphSingleVertex, VerticesEmpty ) 
{
    EXPECT_FALSE(this->graph_.Vertices().empty());
    EXPECT_FALSE(this->graphConst_.Vertices().empty());
}

TYPED_TEST( TestGraphFourVertices, VerticesEmpty ) 
{
    EXPECT_FALSE(this->graph_.Vertices().empty());
    EXPECT_FALSE(this->graphConst_.Vertices().empty());
}

TYPED_TEST( TestGraphBidirectedPath, VerticesEmpty ) 
{
    EXPECT_FALSE(this->graph_.Vertices().empty());
    EXPECT_FALSE(this->graphConst_.Vertices().empty());
}

TYPED_TEST( TestGraphStar, VerticesEmpty ) 
{
    EXPECT_FALSE(this->graph_.Vertices().empty());
    EXPECT_FALSE(this->graphConst_.Vertices().empty());
}
/// @}

/// @name Tests for Vertices().begin() and Vertices().end()
/// @{
#pragma mark VerticesIterate
TYPED_TEST( TestGraphEmpty, VerticesIterate) 
{
    Types::count counter = 0;
    for (auto & v : this->graph_.Vertices()) 
    {
        ++counter;
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphSingleVertex, VerticesIterate) 
{
    Types::count counter = 0;
    for (auto & v : this->graph_.Vertices()) {
        ++counter;
        auto id = v.Identifier();
        v.Properties().NonConstMemberFunction();
        EXPECT_TRUE(this->graphConst_.VertexExists(id));
        EXPECT_EQ(this->graphConst_.VertexAt(id), v);
        EXPECT_EQ(this->graphConst_.Vertices()[id], v);
    }
    EXPECT_EQ(1, counter);
}

TYPED_TEST( TestGraphFourVertices, VerticesIterate) 
{
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    for (auto & v : this->graph_.Vertices()) {
        ++counter;
        auto id = v.Identifier();
        v.Properties().NonConstMemberFunction();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.VertexExists(id));
        EXPECT_EQ(this->graphConst_.VertexAt(id), v);
        EXPECT_EQ(this->graphConst_.Vertices()[id], v);
    }

    EXPECT_EQ(4, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end()));
}

TYPED_TEST( TestGraphStar, VerticesIterate) 
{
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    for (auto & v : this->graph_.Vertices()) 
    {
        ++counter;
        auto id = v.Identifier();
        v.Properties().NonConstMemberFunction();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.VertexExists(id));
        EXPECT_EQ(this->graphConst_.VertexAt(id), v);
        EXPECT_EQ(this->mapIdToVertex_.at(id), v);
        EXPECT_EQ(this->graphConst_.Vertices()[id], v);
    }

    EXPECT_EQ(4, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end()));
}

#pragma mark VerticesIterateConst
TYPED_TEST( TestGraphEmpty, VerticesIterateConst) 
{
    Types::count counter = 0;
    for (auto& v : this->graphConst_.Vertices()) 
    {
        ++counter;
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphSingleVertex, VerticesIterateConst) 
{
    Types::count counter = 0;
    for (auto& v : this->graphConst_.Vertices()) 
    {
        ++counter;
        auto id = v.Identifier();
        EXPECT_TRUE(this->graphConst_.VertexExists(id));
        EXPECT_EQ(this->graphConst_.VertexAt(id), v);
        EXPECT_EQ(this->graphConst_.Vertices()[id], v);
    }
    EXPECT_EQ(1, counter);
}

TYPED_TEST( TestGraphFourVertices, VerticesIterateConst) 
{
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    for (auto& v : this->graphConst_.Vertices()) 
    {
        ++counter;
        auto id = v.Identifier();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.VertexExists(id));
        EXPECT_EQ(this->graphConst_.VertexAt(id), v);
        EXPECT_EQ(this->graphConst_.Vertices()[id], v);
    }

    EXPECT_EQ(4, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end()));
}

TYPED_TEST( TestGraphStar, VerticesIterateConst) 
{
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    for (auto& v : this->graphConst_.Vertices()) {
        ++counter;
        auto id = v.Identifier();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.VertexExists(id));
        EXPECT_EQ(this->graphConst_.VertexAt(id), v);
        EXPECT_EQ(this->mapIdToVertex_.at(id), v);
        EXPECT_EQ(this->graphConst_.Vertices()[id], v);
    }

    EXPECT_EQ(4, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end()));
}
/// @}

/// @name Tests for Vertices().rbegin() and Vertices().rend()
/// @{
#pragma mark VerticesIterateBackwards
TYPED_TEST( TestGraphEmpty, VerticesIterateBackwards) 
{
    Types::count counter = 0;
    for (auto it = this->graph_.Vertices().rbegin();
            it != this->graph_.Vertices().rend();
            ++it) {
        it->Properties().NonConstMemberFunction();
        ++counter;
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphSingleVertex, VerticesIterateBackwards) 
{
    EXPECT_NE(this->graph_.Vertices().rbegin(),
              this->graph_.Vertices().rend());

    Types::count counter = 0;
    for (auto it = this->graph_.Vertices().rbegin();
            it != this->graph_.Vertices().rend();
            ++it) {
        ++counter;
        it->Properties().NonConstMemberFunction();
        auto id = it->Identifier();
        EXPECT_TRUE(this->graphConst_.VertexExists(id));
        EXPECT_EQ(this->graphConst_.VertexAt(id), *it);
        EXPECT_EQ(this->graphConst_.Vertices()[id], *it);
    }
    EXPECT_EQ(1, counter);
}

TYPED_TEST( TestGraphFourVertices, VerticesIterateBackwards) 
{
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    EXPECT_NE(this->graph_.Vertices().rbegin(),
              this->graph_.Vertices().rend());


    for (auto it = this->graph_.Vertices().rbegin();
            it != this->graph_.Vertices().rend();
            ++it) {
        ++counter;
        it->Properties().NonConstMemberFunction();
        auto id = it->Identifier();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.VertexExists(id));
        EXPECT_EQ(this->graphConst_.VertexAt(id), *it);
        EXPECT_EQ(this->graphConst_.Vertices()[id], *it);
    }

    EXPECT_EQ(4, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end(), std::greater<Types::vertexId>()));
}

TYPED_TEST( TestGraphStar, VerticesIterateBackwards) 
{
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    EXPECT_NE(this->graph_.Vertices().rbegin(),
              this->graph_.Vertices().rend());


    for (auto it = this->graph_.Vertices().rbegin();
            it != this->graph_.Vertices().rend();
            ++it) 
    {
        ++counter;
        it->Properties().NonConstMemberFunction();
        auto id = it->Identifier();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.VertexExists(id));
        EXPECT_EQ(this->graphConst_.VertexAt(id), *it);
        EXPECT_EQ(this->graphConst_.Vertices()[id], *it);
        EXPECT_EQ(this->mapIdToVertex_.at(id), *it);
    }

    EXPECT_EQ(4, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end(), std::greater<Types::vertexId>()));
}

#pragma mark VerticesIterateBackwardsConst
TYPED_TEST( TestGraphEmpty, VerticesIterateBackwardsConst) {
    Types::count counter = 0;
    for (auto it = this->graphConst_.Vertices().rbegin();
            it != this->graphConst_.Vertices().rend();
            ++it) {
        ++counter;
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphSingleVertex, VerticesIterateBackwardsConst) {
    EXPECT_NE(this->graphConst_.Vertices().rbegin(),
              this->graphConst_.Vertices().rend());

    Types::count counter = 0;
    for (auto it = this->graphConst_.Vertices().rbegin();
            it != this->graphConst_.Vertices().rend();
            ++it) {
        ++counter;
        auto id = it->Identifier();
        EXPECT_TRUE(this->graphConst_.VertexExists(id));
        EXPECT_EQ(this->graphConst_.VertexAt(id), *it);
        EXPECT_EQ(this->graphConst_.Vertices()[id], *it);
    }
    EXPECT_EQ(1, counter);
}

TYPED_TEST( TestGraphFourVertices, VerticesIterateBackwardsConst) {
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    EXPECT_NE(this->graphConst_.Vertices().rbegin(),
              this->graphConst_.Vertices().rend());


    for (auto it = this->graphConst_.Vertices().rbegin();
            it != this->graphConst_.Vertices().rend();
            ++it) {
        ++counter;
        auto id = it->Identifier();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.VertexExists(id));
        EXPECT_EQ(this->graphConst_.VertexAt(id), *it);
        EXPECT_EQ(this->graphConst_.Vertices()[id], *it);
    }

    EXPECT_EQ(4, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end(), std::greater<Types::vertexId>()));
}

TYPED_TEST( TestGraphStar, VerticesIterateBackwardsConst) {
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    EXPECT_NE(this->graphConst_.Vertices().rbegin(),
              this->graphConst_.Vertices().rend());


    for (auto it = this->graphConst_.Vertices().rbegin();
            it != this->graphConst_.Vertices().rend();
            ++it) {
        ++counter;
        auto id = it->Identifier();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.VertexExists(id));
        EXPECT_EQ(this->graphConst_.VertexAt(id), *it);
        EXPECT_EQ(this->graphConst_.Vertices()[id], *it);
        EXPECT_EQ(this->mapIdToVertex_.at(id), *it);
    }

    EXPECT_EQ(4, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end(), std::greater<Types::vertexId>()));
}
/// @}

#pragma mark Edges
/// @name Tests for Edges()
/// @{
#pragma mark EdgesSize
TYPED_TEST( TestGraphEmpty, EdgesSize ) {
    EXPECT_EQ(0, this->graph_.Edges().size());
    EXPECT_EQ(0, this->graphConst_.Edges().size());
}

TYPED_TEST( TestGraphSingleVertex, EdgesSize ) {
    EXPECT_EQ(0, this->graph_.Edges().size());
    EXPECT_EQ(0, this->graphConst_.Edges().size());
}

TYPED_TEST( TestGraphFourVertices, EdgesSize ) {
    EXPECT_EQ(0, this->graph_.Edges().size());
    EXPECT_EQ(0, this->graphConst_.Edges().size());
}

TYPED_TEST( TestGraphBidirectedPath, EdgesSize ) {
    EXPECT_EQ(4, this->graph_.Edges().size());
    EXPECT_EQ(4, this->graphConst_.Edges().size());
}

TYPED_TEST( TestGraphStar, EdgesSize ) {
    EXPECT_EQ(3, this->graph_.Edges().size());
    EXPECT_EQ(3, this->graphConst_.Edges().size());
}

#pragma mark EdgesEmpty
TYPED_TEST( TestGraphEmpty, EdgesEmpty ) {
    EXPECT_TRUE(this->graph_.Edges().empty());
    EXPECT_TRUE(this->graphConst_.Edges().empty());
}

TYPED_TEST( TestGraphSingleVertex, EdgesEmpty ) {
    EXPECT_TRUE(this->graph_.Edges().empty());
    EXPECT_TRUE(this->graphConst_.Edges().empty());
}

TYPED_TEST( TestGraphFourVertices, EdgesEmpty ) {
    EXPECT_TRUE(this->graph_.Edges().empty());
    EXPECT_TRUE(this->graphConst_.Edges().empty());
}

TYPED_TEST( TestGraphBidirectedPath, EdgesEmpty ) 
{
    EXPECT_FALSE(this->graph_.Edges().empty());
    EXPECT_FALSE(this->graphConst_.Edges().empty());
}

TYPED_TEST( TestGraphStar, EdgesEmpty ) 
{
    EXPECT_FALSE(this->graph_.Edges().empty());
    EXPECT_FALSE(this->graphConst_.Edges().empty());
}

#pragma mark EdgesIterate
TYPED_TEST( TestGraphEmpty, EdgesIterate ) 
{
    Types::count counter = 0;
    for (auto& edge : this->graph_.Edges()) 
    {
        ++counter;
        edge.Properties().NonConstMemberFunction();
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphSingleVertex, EdgesIterate ) 
{
    Types::count counter = 0;
    for ( auto & edge : this->graph_.Edges() ) {
        ++counter;
        edge.Properties().NonConstMemberFunction();
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphFourVertices, EdgesIterate ) 
{
    Types::count counter = 0;
    for (auto& edge : this->graph_.Edges()) {
        ++counter;
        edge.Properties().NonConstMemberFunction();
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphBidirectedPath, EdgesIterate ) 
{
    Types::count counter = 0;
    std::vector<Types::edgeId> ids;

    for (auto& edge : this->graph_.Edges()) 
    {
        ++counter;
        edge.Properties().NonConstMemberFunction();
        auto id = edge.Identifier();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.EdgeExists(id));
        EXPECT_EQ(this->graphConst_.EdgeAt(id), edge);
        EXPECT_EQ(this->mapIdToEdge_.at(id), edge);
        EXPECT_EQ(this->graphConst_.Edges()[id], edge);
    }

    EXPECT_EQ(4, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end()));
}

TYPED_TEST( TestGraphStar, EdgesIterate) 
{
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    for ( auto & edge : this->graph_.Edges() ) 
    {
        ++counter;
        edge.Properties().NonConstMemberFunction();
        auto id = edge.Identifier();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.EdgeExists(id));
        EXPECT_EQ(this->graphConst_.EdgeAt(id), edge);
        EXPECT_EQ(this->mapIdToEdge_.at(id), edge);
        EXPECT_EQ(this->graphConst_.Edges()[id], edge);
    }

    EXPECT_EQ(3, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end()));
}

#pragma mark EdgesIterateConst
TYPED_TEST( TestGraphEmpty, EdgesIterateConst ) 
{
    Types::count counter = 0;
    for (auto & v : this->graphConst_.Edges()) 
    {
        ++counter;
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphSingleVertex, EdgesIterateConst ) 
{
    Types::count counter = 0;
    for (auto & v : this->graphConst_.Edges()) 
    {
        ++counter;
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphFourVertices, EdgesIterateConst ) 
{
    Types::count counter = 0;
    for (auto & v : this->graphConst_.Edges()) 
    {
        ++counter;
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphBidirectedPath, EdgesIterateConst ) 
{
    Types::count counter = 0;
    std::vector<Types::edgeId> ids;

    for (auto& edge : this->graphConst_.Edges()) 
    {
        ++counter;
        auto id = edge.Identifier();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.EdgeExists(id));
        EXPECT_EQ(this->graphConst_.EdgeAt(id), edge);
        EXPECT_EQ(this->mapIdToEdge_.at(id), edge);
        EXPECT_EQ(this->graphConst_.Edges()[id], edge);
    }

    EXPECT_EQ(4, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end()));
}

TYPED_TEST( TestGraphStar, EdgesIterateConst) 
{
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    for ( auto & edge : this->graphConst_.Edges() ) 
    {
        ++counter;
        auto id = edge.Identifier();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.EdgeExists(id));
        EXPECT_EQ(this->graphConst_.EdgeAt(id), edge);
        EXPECT_EQ(this->mapIdToEdge_.at(id), edge);
        EXPECT_EQ(this->graphConst_.Edges()[id], edge);
    }

    EXPECT_EQ(3, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end()));
}

#pragma mark EdgesIterateBackwards
TYPED_TEST( TestGraphEmpty, EdgesIterateBackwards ) 
{
    Types::count counter = 0;
    for (auto it = this->graph_.Edges().rbegin();
         it != this->graph_.Edges().rend();
         ++it)
    {
        ++counter;
        it->Properties().NonConstMemberFunction();
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphSingleVertex, EdgesIterateBackwards ) 
{
    Types::count counter = 0;
    for (auto it = this->graph_.Edges().rbegin();
         it != this->graph_.Edges().rend();
         ++it)
    {
        ++counter;
        it->Properties().NonConstMemberFunction();
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphFourVertices, EdgesIterateBackwards ) 
{
    Types::count counter = 0;
    for (auto it = this->graph_.Edges().rbegin();
         it != this->graph_.Edges().rend();
         ++it)
    {
        ++counter;
        it->Properties().NonConstMemberFunction();
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphBidirectedPath, EdgesIterateBackwards ) 
{
    Types::count counter = 0;
    std::vector<Types::edgeId> ids;

    for (auto it = this->graph_.Edges().rbegin();
         it != this->graph_.Edges().rend();
         ++it)
    {
        ++counter;
        it->Properties().NonConstMemberFunction();
        auto & edge = *it;
        auto id = edge.Identifier();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.EdgeExists(id));
        EXPECT_EQ(this->graphConst_.EdgeAt(id), edge);
        EXPECT_EQ(this->mapIdToEdge_.at(id), edge);
        EXPECT_EQ(this->graphConst_.Edges()[id], edge);
    }

    EXPECT_EQ(4, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end(), std::greater<Types::edgeId>()));
}

TYPED_TEST( TestGraphStar, EdgesIterateBackwards) 
{
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    for (auto it = this->graph_.Edges().rbegin();
         it != this->graph_.Edges().rend();
         ++it)
    {
        ++counter;
        it->Properties().NonConstMemberFunction();
        auto & edge = *it;
        auto id = edge.Identifier();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.EdgeExists(id));
        EXPECT_EQ(this->graphConst_.EdgeAt(id), edge);
        EXPECT_EQ(this->mapIdToEdge_.at(id), edge);
        EXPECT_EQ(this->graphConst_.Edges()[id], edge);
    }

    EXPECT_EQ(3, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end(), std::greater<Types::edgeId>()));
}

#pragma mark EdgesIterateBackwardsConst
TYPED_TEST( TestGraphEmpty, EdgesIterateBackwardsConst ) 
{
    Types::count counter = 0;
    for (auto it = this->graphConst_.Edges().rbegin();
         it != this->graphConst_.Edges().rend();
         ++it)
    {
        ++counter;
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphSingleVertex, EdgesIterateBackwardsConst ) {
    Types::count counter = 0;
    for (auto it = this->graphConst_.Edges().rbegin();
         it != this->graphConst_.Edges().rend();
         ++it)
    {
        ++counter;
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphFourVertices, EdgesIterateBackwardsConst ) {
    Types::count counter = 0;
    for (auto it = this->graphConst_.Edges().rbegin();
         it != this->graphConst_.Edges().rend();
         ++it)
    {
        ++counter;
        FAIL();
    }
    EXPECT_EQ(0, counter);
}

TYPED_TEST( TestGraphBidirectedPath, EdgesIterateBackwardsConst ) {
    Types::count counter = 0;
    std::vector<Types::edgeId> ids;

    for (auto it = this->graphConst_.Edges().rbegin();
         it != this->graphConst_.Edges().rend();
         ++it)
    {
        ++counter;
        auto & edge = *it;
        auto id = edge.Identifier();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.EdgeExists(id));
        EXPECT_EQ(this->graphConst_.EdgeAt(id), edge);
        EXPECT_EQ(this->mapIdToEdge_.at(id), edge);
        EXPECT_EQ(this->graphConst_.Edges()[id], edge);
    }

    EXPECT_EQ(4, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end(), std::greater<Types::edgeId>()));
}

TYPED_TEST( TestGraphStar, EdgesIterateBackwardsConst) {
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    for (auto it = this->graphConst_.Edges().rbegin();
         it != this->graphConst_.Edges().rend();
         ++it)
    {
        ++counter;
        auto & edge = *it;
        auto id = edge.Identifier();
        ids.push_back(id);
        EXPECT_TRUE(this->graphConst_.EdgeExists(id));
        EXPECT_EQ(this->graphConst_.EdgeAt(id), edge);
        EXPECT_EQ(this->mapIdToEdge_.at(id), edge);
        EXPECT_EQ(this->graphConst_.Edges()[id], edge);
    }

    EXPECT_EQ(3, counter);
    EXPECT_TRUE(std::is_sorted(ids.begin(), ids.end(), std::greater<Types::edgeId>()));
}
/// @}

#pragma mark VertexAt
TYPED_TEST(TestGraphEmptyDeathTest, VertexAt) {
    auto assertionString = this->assertionString("VertexAt", "VertexExists\\(id\\)");
    Types::vertexId id = 0;
    EXPECT_DEATH( {this->graph_.VertexAt(id);}, assertionString);
    EXPECT_DEATH( {this->graphConst_.VertexAt(id);}, assertionString);
}

TYPED_TEST(TestGraphSingleVertexDeathTest, VertexAt) {
    auto assertionString = this->assertionString("VertexAt", "VertexExists\\(id\\)");
    Types::vertexId id = this->id_ + 1;
    EXPECT_DEATH( {this->graph_.VertexAt(id);}, assertionString);
    EXPECT_DEATH( {this->graphConst_.VertexAt(id);}, assertionString);
}

TYPED_TEST(TestGraphFourVerticesDeathTest, VertexAt) {
    auto assertionString = this->assertionString("VertexAt", "VertexExists\\(id\\)");
    Types::vertexId id = Const::NONE;
    EXPECT_DEATH( {this->graph_.VertexAt(id);}, assertionString);
    EXPECT_DEATH( {this->graphConst_.VertexAt(id);}, assertionString);
}


TYPED_TEST(TestGraphStar, VertexAt) {
    ASSERT_TRUE(this->graph_.VertexExists(this->centerId_));
    EXPECT_EQ(this->centerId_, this->graph_.VertexAt(this->centerId_).Identifier());
    EXPECT_EQ(this->centerId_, this->graphConst_.VertexAt(this->centerId_).Identifier());

    for (auto id : this->leafIds_) {
        ASSERT_TRUE(this->graph_.VertexExists(id));
        EXPECT_EQ(id, this->graph_.VertexAt(id).Identifier());
        EXPECT_EQ(id, this->graphConst_.VertexAt(id).Identifier());
    }
}

/// @name Tests for neighbors
/// @{
#pragma mark NeighborsOf
/// @todo death tests for neighbors of non-existent vertices
TYPED_TEST(TestGraphEmptyDeathTest, NeighborsOf) {
    auto assertionString = this->assertionString("NeighborsOf", "VertexExists\\(id\\)");
    Types::vertexId id = 0;
    EXPECT_DEATH( {this->graph_.NeighborsOf(id);}, assertionString);
    EXPECT_DEATH( {this->graphConst_.NeighborsOf(id);}, assertionString);
}

TYPED_TEST(TestGraphSingleVertexDeathTest, NeighborsOf) {
    auto assertionString = this->assertionString("NeighborsOf", "VertexExists\\(id\\)");
    Types::vertexId id = this->id_ + 1;
    EXPECT_DEATH( {this->graph_.NeighborsOf(id);}, assertionString);
    EXPECT_DEATH( {this->graphConst_.NeighborsOf(id);}, assertionString);
}

TYPED_TEST(TestGraphFourVerticesDeathTest, NeighborsOf) {
    auto assertionString = this->assertionString("NeighborsOf", "VertexExists\\(id\\)");
    Types::vertexId id = Const::NONE;
    EXPECT_DEATH( {this->graph_.NeighborsOf(id);}, assertionString);
    EXPECT_DEATH( {this->graphConst_.NeighborsOf(id);}, assertionString);
}

TYPED_TEST(TestGraphSingleVertex, NeighborsOfWithoutEdges) {
    std::vector<Types::vertexId> neighbors;

    EXPECT_EQ(0, this->graphConst_.NeighborsOf(0).size());
    this->graphConst_.NeighborsOf(0, neighbors);
    EXPECT_EQ(0, neighbors.size());
}

TYPED_TEST(TestGraphFourVertices, NeighborsOfWithoutEdges) {
    std::vector<Types::vertexId> neighbors;

    for (Types::index i = 0; i < 4; ++i) {
        EXPECT_EQ(0, this->graphConst_.NeighborsOf(i).size());
        this->graphConst_.NeighborsOf(i, neighbors);
        EXPECT_EQ(0, neighbors.size());
        neighbors.clear();
    }
}

TYPED_TEST(TestGraphBidirectedPath, NeighborsOf) {
    std::vector<Types::vertexId> expectedNeighbors = {this->vertexIds_[1]};
    auto neighbors = this->graphConst_.NeighborsOf(this->vertexIds_[0]);
    EXPECT_EQ(expectedNeighbors, neighbors);

    neighbors = this->graphConst_.NeighborsOf(this->vertexIds_[2]);
    EXPECT_EQ(expectedNeighbors, neighbors);

    expectedNeighbors = {this->vertexIds_[0], this->vertexIds_[2]};
    neighbors = this->graphConst_.NeighborsOf(this->vertexIds_[1]);
    ExpectSameContent(expectedNeighbors, neighbors);
}

TYPED_TEST(TestGraphStar, NeighborsOf) {
    // Center
    Types::vertexId centerId = this->centerId_;
    std::vector<Types::vertexId> expectedNeighbors(this->leafIds_.begin(),
        this->leafIds_.end());

    std::vector<Types::vertexId> neighbors = this->graphConst_.NeighborsOf(centerId);
    EXPECT_EQ(3, neighbors.size());
    ExpectSameContent(expectedNeighbors, neighbors);
    neighbors.clear();

    this->graphConst_.NeighborsOf(centerId, neighbors);
    EXPECT_EQ(3, neighbors.size());
    ExpectSameContent(expectedNeighbors, neighbors);
    neighbors.clear();
    
    // Leaves
    for (size_t i = 0; i < 3; ++i) {
        Types::vertexId id = this->leafIds_[i];
        neighbors = this->graphConst_.NeighborsOf(id);
        ASSERT_EQ(1, neighbors.size());
        EXPECT_EQ(centerId, neighbors.front());
        neighbors.clear();

        this->graphConst_.NeighborsOf(id, neighbors);
        ASSERT_EQ(1, neighbors.size());
        EXPECT_EQ(centerId, neighbors.front());
        neighbors.clear();
    }
}

#pragma mark NeighborsOfPassedVectorNonEmpty
TYPED_TEST(TestGraphSingleVertex, NeighborsOfPassedVectorNonEmpty) {
    std::vector<Types::vertexId> expectedOutput = {42, 24, 12, 123};

    auto input = expectedOutput;
    this->graphConst_.NeighborsOf(0, input);
    EXPECT_EQ(expectedOutput, input);
}

TYPED_TEST(TestGraphFourVertices, NeighborsOfPassedVectorNonEmpty) {
    std::vector<Types::vertexId> expectedOutput = {42, 24, 12, 123};

    for (Types::vertexId i = 0; i < 4; ++i) {
        auto input = expectedOutput;
        this->graphConst_.NeighborsOf(i, input);
        EXPECT_EQ(expectedOutput, input);
    }
}

TYPED_TEST(TestGraphStar, NeighborsOfPassedVectorNonEmpty) {
    std::vector<Types::vertexId> neighbors = {42, 24, 12, 123};
    auto initialSize = neighbors.size();
    std::vector<Types::vertexId> expectedNeighbors(neighbors);
    expectedNeighbors.insert(expectedNeighbors.end(), this->leafIds_.begin(), this->leafIds_.end());
    std::sort(expectedNeighbors.begin() + initialSize, expectedNeighbors.end());
    Types::vertexId centerId = this->centerId_;

    this->graphConst_.NeighborsOf(centerId, neighbors);
    ASSERT_EQ(initialSize + 3, neighbors.size());
    std::sort(neighbors.begin() + initialSize, neighbors.end());
    EXPECT_EQ(expectedNeighbors, neighbors);
}
/// @}

/// @name Tests for methods related to the degree
/// @{

// TODO: Death test for InDegreeAt() and OutDegreeAt() for non-existing vertices
/**
 * Tests InDegreeAt()
 */
#pragma mark InDegreeAt
TYPED_TEST(TestGraphSingleVertex, InDegreeAtWithoutEdges) {
    ASSERT_TRUE(this->graph_.VertexExists(0));
    EXPECT_EQ(0, this->graph_.InDegreeAt(0));
    EXPECT_EQ(0, this->graphConst_.InDegreeAt(0));
}

TYPED_TEST(TestGraphFourVertices, InDegreeAtWithoutEdges) {
    for (Types::index i = 0; i < 4; ++i) {
        ASSERT_TRUE(this->graph_.VertexExists(i));
        EXPECT_EQ(0, this->graph_.InDegreeAt(i));
        EXPECT_EQ(0, this->graphConst_.InDegreeAt(i));
    }
}

TYPED_TEST(TestGraphBidirectedPath, InDegreeAt) {
    std::vector<Types::count> expectedInDegrees{1, 2, 1};
    for (Types::index i = 0; i < this->vertexIds_.size(); ++i) {
        ASSERT_TRUE(this->graph_.VertexExists(i));
        EXPECT_EQ(expectedInDegrees[i], this->graph_.InDegreeAt(i));
        EXPECT_EQ(expectedInDegrees[i], this->graphConst_.InDegreeAt(i));
    }
}

TYPED_TEST(TestGraphStar, InDegreeAt) {
    auto centerId = this->centerId_;
    EXPECT_EQ(0, this->graph_.InDegreeAt(centerId));
    EXPECT_EQ(0, this->graphConst_.InDegreeAt(centerId));
    for (auto index : this->leafIds_) {
        EXPECT_EQ(1, this->graph_.InDegreeAt(index));
        EXPECT_EQ(1, this->graphConst_.InDegreeAt(index));
    }
}

/**
 * Tests OutDegreeAt()
 */
#pragma mark OutDegreeAt
TYPED_TEST(TestGraphSingleVertex, OutDegreeAtWithoutEdges ) {
    ASSERT_TRUE(this->graph_.VertexExists(0));
    EXPECT_EQ(0, this->graph_.OutDegreeAt(0));
    EXPECT_EQ(0, this->graphConst_.OutDegreeAt(0));
}

TYPED_TEST(TestGraphFourVertices, OutDegreeAtWithoutEdges ) {
    for (Types::index i = 0; i < 4; ++i) {
        ASSERT_TRUE(this->graph_.VertexExists(i));
        EXPECT_EQ(0, this->graph_.OutDegreeAt(i));
        EXPECT_EQ(0, this->graphConst_.OutDegreeAt(i));
    }
}

TYPED_TEST(TestGraphBidirectedPath, OutDegreeAt) {
    std::vector<Types::count> expectedOutDegrees{1, 2, 1};
    for (Types::index i = 0; i < this->vertexIds_.size(); ++i) {
        ASSERT_TRUE(this->graph_.VertexExists(i));
        EXPECT_EQ(expectedOutDegrees[i], this->graph_.OutDegreeAt(i));
        EXPECT_EQ(expectedOutDegrees[i], this->graphConst_.OutDegreeAt(i));
    }
}

TYPED_TEST(TestGraphStar, OutDegreeAt) {
    auto index = this->centerId_;
    EXPECT_EQ(3, this->graph_.OutDegreeAt(index));
    EXPECT_EQ(3, this->graphConst_.OutDegreeAt(index));
    for (int i = 0; i < 3; ++i) {
        index = this->leafIds_[i];
        EXPECT_EQ(0, this->graph_.OutDegreeAt(index));
        EXPECT_EQ(0, this->graphConst_.OutDegreeAt(index));
    }
}

/**
 * Tests DegreeAt()
 */
// @todo death test for degrees of non-existent vertices
#pragma mark DegreeAt
TYPED_TEST(TestGraphSingleVertex, DegreeAtWithoutEdges) {
    ASSERT_TRUE(this->graph_.VertexExists(0));
    EXPECT_EQ(0, this->graph_.DegreeAt(0));
    EXPECT_EQ(0, this->graphConst_.DegreeAt(0));
}

TYPED_TEST(TestGraphFourVertices, DegreeAtWithoutEdges) {
    for (Types::index i = 0; i < 4; ++i) {
        ASSERT_TRUE(this->graph_.VertexExists(i));
        EXPECT_EQ(0, this->graph_.DegreeAt(i));
        EXPECT_EQ(0, this->graphConst_.DegreeAt(i));
    }
}

TYPED_TEST(TestGraphBidirectedPath, DegreeAt) {
    std::vector<Types::count> expectedDegrees{2, 4, 2};
    for (Types::index i = 0; i < this->vertexIds_.size(); ++i) {
        ASSERT_TRUE(this->graph_.VertexExists(i));
        EXPECT_EQ(expectedDegrees[i], this->graph_.DegreeAt(i));
        EXPECT_EQ(expectedDegrees[i], this->graphConst_.DegreeAt(i));
    }
}

TYPED_TEST(TestGraphStar, DegreeAt) {
    auto centerId = this->centerId_;
    EXPECT_EQ(3, this->graph_.DegreeAt(centerId));
    EXPECT_EQ(3, this->graphConst_.DegreeAt(centerId));
    for (auto index : this->leafIds_) {
        EXPECT_EQ(1, this->graph_.DegreeAt(index));
        EXPECT_EQ(1, this->graphConst_.DegreeAt(index));
    }
}


// #pragma mark MinDegree
// TYPED_TEST(TestGraphEmpty, MinDegree) {
//     Types::index index = 0;
//     EXPECT_EQ(0, this->graphConst_.MinDegree());
//     EXPECT_EQ(0, this->graphConst_.MinDegree(index));
//     EXPECT_EQ(Const::NONE, index);
// }

// TYPED_TEST(TestGraphSingleVertex, MinDegree) {
//     Types::index index = 0;
//     EXPECT_EQ(0, this->graphConst_.MinDegree());
//     EXPECT_EQ(0, this->graphConst_.MinDegree(index));
//     EXPECT_EQ(0, index);
// }

// TYPED_TEST(TestGraphFourVertices, MinDegree) {
//     Types::index index = 0;
//     EXPECT_EQ(0, this->graphConst_.MinDegree());
//     EXPECT_EQ(0, this->graphConst_.MinDegree(index));
//     EXPECT_EQ(0, index);
// }

// TYPED_TEST(TestGraphStar, MinDegree) {
//     Types::index index = 0;
//     EXPECT_EQ(1, this->graphConst_.MinDegree());
//     EXPECT_EQ(1, this->graphConst_.MinDegree(index));
//     EXPECT_EQ(1, this->graphConst_.DegreeAt(index));
// }

// #pragma mark MaxDegree
// TYPED_TEST(TestGraphEmpty, MaxDegree) {
//     Types::index index = 0;
//     EXPECT_EQ(0, this->graphConst_.MaxDegree());
//     EXPECT_EQ(0, this->graphConst_.MaxDegree(index));
//     EXPECT_EQ(Const::NONE, index);
// }

// TYPED_TEST(TestGraphSingleVertex, MaxDegree) {
//     Types::index index = 0;
//     EXPECT_EQ(0, this->graphConst_.MaxDegree());
//     EXPECT_EQ(0, this->graphConst_.MaxDegree(index));
//     EXPECT_EQ(0, this->graphConst_.DegreeAt(index));
// }

// TYPED_TEST(TestGraphFourVertices, MaxDegree) {
//     Types::index index = 0;
//     EXPECT_EQ(0, this->graphConst_.MaxDegree());
//     EXPECT_EQ(0, this->graphConst_.MaxDegree(index));
//     EXPECT_EQ(0, this->graphConst_.DegreeAt(index));
// }

// TYPED_TEST(TestGraphStar, MaxDegree) {
//     Types::index index = 0;
//     EXPECT_EQ(3, this->graphConst_.MaxDegree());
//     EXPECT_EQ(3, this->graphConst_.MaxDegree(index));
//     EXPECT_EQ(3, this->graphConst_.DegreeAt(index));
// }
// /// @}

// // TODO: Tests for InEdgeIdsAt
// // TODO: Tests for OutEdgeIdsAt
// // TODO: Tests for EdgeIdsAt

/// @name Tests for mapping functions
/// @{
#pragma mark MapEdges
TYPED_TEST(TestGraphEmpty, MapEdges) {
    int called = 0;
    auto function = [&called](Types::edgeId, const typename TestFixture::TEdge &) {
            ++called;
            return 0;
        };
    auto result = this->graphConst_.MapEdges(function);

    EXPECT_EQ(0, called);
    EXPECT_EQ(0, result.size());
}

TYPED_TEST(TestGraphSingleVertex, MapEdges) {
    int called = 0;
    auto function = [&called](Types::edgeId, const typename TestFixture::TEdge &) {
            ++called;
            return 0;
        };
    auto result = this->graphConst_.MapEdges(function);

    EXPECT_EQ(0, called);
    EXPECT_EQ(0, result.size());
}

TYPED_TEST(TestGraphFourVertices, MapEdges) {
    int called = 0;
    auto function = [&called](Types::edgeId, const typename TestFixture::TEdge &) {
            ++called;
            return 0;
        };
    auto result = this->graphConst_.MapEdges(function);

    EXPECT_EQ(0, called);
    EXPECT_EQ(0, result.size());
}

TYPED_TEST(TestGraphStar, MapEdges) {
    const unsigned OFFSET = 1234;
    auto result = this->graphConst_.MapEdges([](
        Types::edgeId id, const typename TestFixture::TEdge & edge) 
        {
            return std::make_pair(id, edge.Properties().PrivateId() + OFFSET);
        }
    );

    ASSERT_EQ(3, result.size());
    for (Types::index i = 0; i < result.size(); ++i) {
        EXPECT_EQ(this->edgeIds_[i], result[i].first);
        EXPECT_EQ(i + OFFSET, result[i].second);
    }
}

#pragma mark MapVertices
TYPED_TEST(TestGraphEmpty, MapVertices) {
    int called = 0;
    auto function = [&called](Types::vertexId, const typename TestFixture::TVertex &) 
        {
            ++called;
            return 42;
        };
    auto result = this->graphConst_.MapVertices(function);

    EXPECT_EQ(0, called);
    EXPECT_EQ(0, result.size());
}

TYPED_TEST(TestGraphStar, MapVertices) {
    const unsigned OFFSET = 1234;
    auto privateIds = this->graphConst_.MapVertices([](Types::vertexId id, const typename TestFixture::TVertex & vertex) {
        return std::make_pair<>(id, vertex.Properties().PrivateId() + OFFSET);
    });

    ASSERT_EQ(4, privateIds.size());
    EXPECT_EQ(this->centerId_, privateIds[0].first);
    EXPECT_EQ(0 + OFFSET, privateIds[0].second);

    for (Types::index i = 1; i < privateIds.size(); ++i) {
        EXPECT_EQ(this->leafIds_[i - 1], privateIds[i].first);
        EXPECT_EQ(i + OFFSET, privateIds[i].second);
    }
}
/// @}

/// @name Tests for adding vertices
/// @{
#pragma mark AddVertex
TYPED_TEST( TestGraphEmpty, AddVertex) 
{   
    using TVertex           = typename TestFixture::TVertex;
    using TVertexProperties = typename TestFixture::TVertexProperties;

    const unsigned NUMBER_OF_VERTICES = 4;
    
    std::vector<Types::index> indices;

    for (size_t i = 0; i < NUMBER_OF_VERTICES; ++i) 
    {
        TVertexProperties vertexProperties(i);
        auto id = this->graph_.AddVertex(vertexProperties);
        indices.push_back(id);
        TVertex vertex = this->graph_.VertexAt(id);

        EXPECT_EQ(id, vertex.Identifier());
        EXPECT_EQ(i + 1, this->graph_.NumberOfVertices());
        
        // Check if all previously inserted vertices are still correct
        for (size_t j = 0; j <= i; ++j) 
        {
            ASSERT_TRUE(this->graph_.VertexExists(indices[j]));
            EXPECT_EQ(j, this->graph_.VertexAt(indices[j]).Properties().PrivateId() )
            << "After adding vertex " << i << ": Vertex " << j << "is incorrect";
        }
        
    }
}

#pragma mark AddVertexFromTemporary
TYPED_TEST(TestGraphEmpty, AddVertexFromTemporary) 
{
    using TVertex           = typename TestFixture::TVertex;
    using TVertexProperties = typename TestFixture::TVertexProperties;

    auto id = this->graph_.AddVertex(TVertexProperties(0));

    ASSERT_EQ(1, this->graph_.NumberOfVertices());
    ASSERT_TRUE(this->graph_.VertexExists(id));
    TVertex const & vertex = this->graph_.VertexAt(id);
    EXPECT_EQ(0, vertex.Properties().PrivateId() );
    EXPECT_EQ(id, vertex.Identifier());
}

#pragma mark AddVertexFromConstReference
TYPED_TEST(TestGraphEmpty, AddVertexFromConstReference) 
{
    using TVertex           = typename TestFixture::TVertex;
    using TVertexProperties = typename TestFixture::TVertexProperties;

    const TVertexProperties vertexProperties(0);
    auto id = this->graph_.AddVertex(vertexProperties);

    ASSERT_EQ(1, this->graph_.NumberOfVertices());
    ASSERT_TRUE(this->graph_.VertexExists(id));
    const TVertex& vertexInGraph = this->graph_.VertexAt(id);
    EXPECT_EQ(id, vertexInGraph.Identifier());
}

/// @}

/// @name Tests for adding edges
/// @{
#pragma mark AddEdge
TYPED_TEST( TestGraphFourVertices, AddEdge) {
    using TEdge             = typename TestFixture::TEdge;
    using TEdgeProperties   = typename TestFixture::TEdgeProperties;

    for (Types::vertexId i = 0; i < 4; ++i) 
    {
        ASSERT_TRUE(this->graph_.VertexExists(0));
    }

    // Add edge (0,1)
    TEdgeProperties edgeProperties01 = TEdgeProperties(0);
    Types::edgeId source = 0;
    Types::edgeId target = 1;
    Types::edgeId id01   = this->graph_.AddEdge(source, target, edgeProperties01);
    TEdge         edge01 = this->graph_.EdgeAt(id01);

    EXPECT_EQ(1, this->graph_.NumberOfEdges());

    EXPECT_EQ(id01, edge01.Identifier());
    EXPECT_EQ(id01, this->graph_.EdgeAt(id01).Identifier());
    EXPECT_EQ(edge01, this->graph_.EdgeAt(id01));
    EXPECT_EQ(source, this->graph_.EdgeAt(id01).Source());
    EXPECT_EQ(target, this->graph_.EdgeAt(id01).Target());

    ASSERT_EQ(1, this->graph_.OutEdgeIdsAt(0).size());
    EXPECT_EQ(id01, this->graph_.OutEdgeIdsAt(0).front());
    ASSERT_EQ(1, this->graph_.InEdgeIdsAt(1).size());
    EXPECT_EQ(id01, this->graph_.InEdgeIdsAt(1).front());
    ExpectInDegrees(this->graph_, {0, 1, 0, 0});
    ExpectOutDegrees(this->graph_, {1, 0, 0, 0});


    // Add edge (1,2)
    TEdgeProperties edgeProperties12 = TEdgeProperties(1);
    source = 1;
    target = 2;
    Types::edgeId id12 = this->graph_.AddEdge(source, target, edgeProperties12);
    TEdge edge12 = this->graph_.EdgeAt(id12);

    EXPECT_EQ(2, this->graph_.NumberOfEdges());

    EXPECT_EQ(id12, edge12.Identifier());
    EXPECT_EQ(id12, this->graph_.EdgeAt(id12).Identifier());
    EXPECT_NE(id01, id12);
    EXPECT_EQ(edge12, this->graph_.EdgeAt(id12));

    ASSERT_EQ(1, this->graph_.OutEdgeIdsAt(1).size());
    EXPECT_EQ(id12, this->graph_.OutEdgeIdsAt(1).front());
    ASSERT_EQ(1, this->graph_.InEdgeIdsAt(2).size());
    EXPECT_EQ(id12, this->graph_.InEdgeIdsAt(2).front());
    ExpectInDegrees(this->graph_, {0, 1, 1, 0});
    ExpectOutDegrees(this->graph_, {1, 1, 0, 0});
    //Check that the edge (0,1) has not changed
    EXPECT_EQ(edge01, this->graph_.EdgeAt(id01));


    // Add edge (0,3)
    TEdgeProperties edgeProperties03 = TEdgeProperties(2);
    source = 0;
    target = 3;
    Types::edgeId id03 = this->graph_.AddEdge(source, target, edgeProperties03);
    TEdge edge03 = this->graph_.EdgeAt(id03);

    EXPECT_EQ(3, this->graph_.NumberOfEdges());

    EXPECT_EQ(id03, edge03.Identifier());
    EXPECT_NE(id01, id03);
    EXPECT_NE(id12, id03);
    EXPECT_EQ(id03, this->graph_.EdgeAt(id03).Identifier());
    EXPECT_EQ(edge03, this->graph_.EdgeAt(id03));

    ExpectSameContent({id01, id03}, this->graph_.OutEdgeIdsAt(0));
    ASSERT_EQ(1, this->graph_.InEdgeIdsAt(3).size());
    EXPECT_EQ(id03, this->graph_.InEdgeIdsAt(3).front());
    ExpectInDegrees(this->graph_, {0, 1, 1, 1});
    ExpectOutDegrees(this->graph_, {2, 1, 0, 0});
    //Check that the edges (0,1) and (1,2) have not changed
    EXPECT_EQ(edge01, this->graph_.EdgeAt(id01));
    EXPECT_EQ(edge12, this->graph_.EdgeAt(id12));
}
/// @}

/// @name Tests for EdgeId(source, target)
#pragma mark EdgeIdSourceTarget
TYPED_TEST(TestGraphSingleVertex, EdgeIdSourceTarget) {
    ASSERT_EQ(Const::NONE, this->graphConst_.EdgeId(this->id_, this->id_));
}

TYPED_TEST(TestGraphFourVertices, EdgeIdSourceTarget) {
    for (Types::vertexId source : this->vertexIds_) {
        for (Types::vertexId target : this->vertexIds_) {
            ASSERT_EQ(Const::NONE, this->graphConst_.EdgeId(source, target));
        }
    }
}

TYPED_TEST(TestGraphStar, EdgeIdSourceTarget) {
    for (size_t i = 0; i < this->leafIds_.size(); ++i) {
        ASSERT_EQ(this->edgeIds_[i],
            this->graphConst_.EdgeId(this->centerId_, this->leafIds_[i]));
        ASSERT_EQ(Const::NONE,
            this->graphConst_.EdgeId(this->leafIds_[i], this->centerId_));
    }
    for (Types::vertexId source : this->leafIds_) {
        for (Types::vertexId target : this->leafIds_) {
            ASSERT_EQ(Const::NONE, this->graphConst_.EdgeId(source, target));
        }
    }
}

#pragma mark ForAllVertexIdentifiers
TYPED_TEST(TestGraphEmpty, ForAllVertexIdentifiers) {
    this->graphConst_.template for_all_vertex_identifiers<egoa::ExecutionPolicy::sequential>(
        [](Types::vertexId id) {
            FAIL();
        });
}

TYPED_TEST(TestGraphSingleVertex, ForAllVertexIdentifiers) {
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    this->graphConst_.template for_all_vertex_identifiers<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids](Types::vertexId & id) {
            ++counter;
            ids.push_back(id);
            ++id;   // Try to mess with the loop counter
        });
    EXPECT_EQ(1, counter);
    EXPECT_EQ(this->id_, ids.front());
}

TYPED_TEST(TestGraphFourVertices, ForAllVertexIdentifiersModifyCounter) {
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    this->graphConst_.template for_all_vertex_identifiers<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids, this](Types::vertexId & id) {
            ++counter;
            ids.push_back(id);

            ASSERT_TRUE(this->graphConst_.VertexExists(id));
            auto copyOfId = id;
            auto idBeforeModification = this->graphConst_.VertexAt(copyOfId).Identifier();
            ++id;   // Try to mess with the loop counter
            auto idAfterModification = this->graphConst_.VertexAt(copyOfId).Identifier();
            EXPECT_EQ(idBeforeModification, idAfterModification);
        });
    EXPECT_EQ(4, counter);
    ExpectSameContent(this->vertexIds_, ids);
}

TYPED_TEST(TestGraphStar, ForAllVertexIdentifiers) {
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    this->graphConst_.template for_all_vertex_identifiers<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids](Types::vertexId & id) {
            ++counter;
            ids.push_back(id);
        });
    EXPECT_EQ(4, counter);
    ExpectSameContent(this->vertexIds_, ids);
}

#pragma mark ForAllVertices
TYPED_TEST(TestGraphEmpty, ForAllVertices) {
    this->graph_.template for_all_vertices<egoa::ExecutionPolicy::sequential>(
        [](typename TestFixture::TVertex) {
            FAIL();
        });
}

TYPED_TEST(TestGraphEmpty, ForAllVerticesConst) {
    this->graphConst_.template for_all_vertices<egoa::ExecutionPolicy::sequential>(
        [](typename TestFixture::TVertex) {
            FAIL();
        });
}

TYPED_TEST(TestGraphFourVertices, ForAllVertices) {
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    this->graph_.template for_all_vertices<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids](typename TestFixture::TVertex & vertex){
            ++counter;
            ids.push_back(vertex.Identifier());
        });
    EXPECT_EQ(4, counter);
    ExpectSameContent(this->vertexIds_, ids);
}

TYPED_TEST(TestGraphFourVertices, ForAllVerticesConst) {
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;
    this->graphConst_.template for_all_vertices<ExecutionPolicy::sequential>(
        [&counter, &ids](typename TestFixture::TVertex const & vertex){
            ++counter;
            ids.push_back(vertex.Identifier());
        });
    EXPECT_EQ(4, counter);
    ExpectSameContent(this->vertexIds_, ids);
}

TYPED_TEST(TestGraphStar, ForAllVertices) {
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    this->graph_.template for_all_vertices<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids](typename TestFixture::TVertex & vertex){
            ++counter;
            ids.push_back(vertex.Identifier());
        });
    EXPECT_EQ(4, counter);
    ExpectSameContent(this->vertexIds_, ids);
}

TYPED_TEST(TestGraphStar, ForAllVerticesConst) {
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;
    this->graphConst_.template for_all_vertices<ExecutionPolicy::sequential>(
        [&counter, &ids](typename TestFixture::TVertex const & vertex){
            ++counter;
            ids.push_back(vertex.Identifier());
        });
    EXPECT_EQ(4, counter);
    ExpectSameContent(this->vertexIds_, ids);
}

#pragma mark ForAllVertexTuples
TYPED_TEST(TestGraphEmpty, ForAllVertexTuples) {
    this->graph_.template for_all_vertex_tuples<egoa::ExecutionPolicy::sequential>(
        [](Types::vertexId, typename TestFixture::TVertex) {
            FAIL();
        });
}

TYPED_TEST(TestGraphEmpty, ForAllVertexTuplesConst) {
    this->graphConst_.template for_all_vertex_tuples<egoa::ExecutionPolicy::sequential>(
        [](Types::vertexId, typename TestFixture::TVertex) {
            FAIL();
        });
}

TYPED_TEST(TestGraphFourVertices, ForAllVertexTuplesModifyCounter) {
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    this->graph_.template for_all_vertex_tuples<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids](Types::vertexId & id, typename TestFixture::TVertex & vertex){
            ++counter;
            EXPECT_EQ(id, vertex.Identifier());
            ids.push_back(vertex.Identifier());
            ++id;   // Try to change the loop variable.
        });
    EXPECT_EQ(4, counter);
    ExpectSameContent(this->vertexIds_, ids);
}

TYPED_TEST(TestGraphFourVertices, ForAllVertexTuplesConstModifyCounter) {
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;
    this->graphConst_.template for_all_vertex_tuples<ExecutionPolicy::sequential>(
        [&counter, &ids](Types::vertexId & id, typename TestFixture::TVertex const & vertex){
            ++counter;
            EXPECT_EQ(id, vertex.Identifier());
            ids.push_back(vertex.Identifier());
            ++id;   // Try to change the loop variable.
        });
    EXPECT_EQ(4, counter);
    ExpectSameContent(this->vertexIds_, ids);
}

TYPED_TEST(TestGraphStar, ForAllVertexTuples) {
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;

    this->graph_.template for_all_vertex_tuples<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids](Types::vertexId id, typename TestFixture::TVertex & vertex){
            ++counter;
            EXPECT_EQ(id, vertex.Identifier());
            ids.push_back(vertex.Identifier());
        });
    EXPECT_EQ(4, counter);
    ExpectSameContent(this->vertexIds_, ids);
}

TYPED_TEST(TestGraphStar, ForAllVertexTuplesConst) {
    Types::count counter = 0;
    std::vector<Types::vertexId> ids;
    this->graphConst_.template for_all_vertex_tuples<ExecutionPolicy::sequential>(
        [&counter, &ids](Types::vertexId id, typename TestFixture::TVertex const & vertex){
            ++counter;
            EXPECT_EQ(id, vertex.Identifier());
            ids.push_back(vertex.Identifier());
        });
    EXPECT_EQ(4, counter);
    ExpectSameContent(this->vertexIds_, ids);
}

#pragma mark ForAllEdgeIdentifiers
TYPED_TEST(TestGraphEmpty, ForAllEdgeIdentifiers) {
    this->graphConst_.template for_all_edge_identifiers<egoa::ExecutionPolicy::sequential>(
        [](Types::edgeId id) {
            FAIL();
        });
}

TYPED_TEST(TestGraphSingleVertex, ForAllEdgeIdentifiers) {
    this->graphConst_.template for_all_edge_identifiers<egoa::ExecutionPolicy::sequential>(
        [](Types::edgeId id) {
            FAIL();
        });
}

TYPED_TEST(TestGraphFourVertices, ForAllEdgeIdentifiers) {
    this->graphConst_.template for_all_edge_identifiers<egoa::ExecutionPolicy::sequential>(
        [](Types::edgeId id) {
            FAIL();
        });
}

TYPED_TEST(TestGraphBidirectedPath, ForAllEdgeIdentifiersModifyCounter) {
    Types::count counter = 0;
    std::vector<Types::edgeId> ids;

    this->graphConst_.template for_all_edge_identifiers<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids, this](Types::edgeId & id) {
            ++counter;
            ids.push_back(id);

            ASSERT_TRUE(this->graphConst_.EdgeExists(id));
            auto copyOfId = id;
            auto idBeforeModification = this->graphConst_.EdgeAt(copyOfId).Identifier();
            ++id;
            auto idAfterModification = this->graphConst_.EdgeAt(copyOfId).Identifier();
            EXPECT_EQ(idBeforeModification, idAfterModification);
        });
    EXPECT_EQ(4, counter);
    ExpectSameContent(this->edgeIds_, ids);
}

TYPED_TEST(TestGraphStar, ForAllEdgeIdentifiers) {
    Types::count counter = 0;
    std::vector<Types::edgeId> ids;

    this->graphConst_.template for_all_edge_identifiers<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids](Types::edgeId & id) {
            ++counter;
            ids.push_back(id);
        });
    EXPECT_EQ(3, counter);
    ExpectSameContent(this->edgeIds_, ids);
}

#pragma mark ForAllEdges
TYPED_TEST(TestGraphEmpty, ForAllEdges) {
    this->graph_.template for_all_edges<egoa::ExecutionPolicy::sequential>(
        [](typename TestFixture::TEdge &) {
            FAIL();
        });
}

TYPED_TEST(TestGraphEmpty, ForAllEdgesConst) {
    this->graphConst_.template for_all_edges<egoa::ExecutionPolicy::sequential>(
        [](typename TestFixture::TEdge const &) {
            FAIL();
        });
}

TYPED_TEST(TestGraphFourVertices, ForAllEdges) {
    this->graph_.template for_all_edges<egoa::ExecutionPolicy::sequential>(
        [](typename TestFixture::TEdge &) {
            FAIL();
        });
}

TYPED_TEST(TestGraphFourVertices, ForAllEdgesConst) {
    this->graphConst_.template for_all_edges<egoa::ExecutionPolicy::sequential>(
        [](typename TestFixture::TEdge const &) {
            FAIL();
        });
}

TYPED_TEST(TestGraphBidirectedPath, ForAllEdges) {
    Types::count counter = 0;
    std::vector<Types::edgeId> ids;

    this->graph_.template for_all_edges<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids](typename TestFixture::TEdge & edge) {
            ++counter;
            ids.push_back(edge.Identifier());
        });
    EXPECT_EQ(4, counter);
    ExpectSameContent(this->edgeIds_, ids);
}

TYPED_TEST(TestGraphBidirectedPath, ForAllEdgesConst) {
    Types::count counter = 0;
    std::vector<Types::edgeId> ids;

    this->graphConst_.template for_all_edges<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids](typename TestFixture::TEdge const & edge) {
            ++counter;
            ids.push_back(edge.Identifier());
        });
    EXPECT_EQ(4, counter);
    ExpectSameContent(this->edgeIds_, ids);
}

TYPED_TEST(TestGraphStar, ForAllEdges) {
    Types::count counter = 0;
    std::vector<Types::edgeId> ids;

    this->graph_.template for_all_edges<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids](typename TestFixture::TEdge & edge) {
            ++counter;
            ids.push_back(edge.Identifier());
        });
    EXPECT_EQ(3, counter);
    ExpectSameContent(this->edgeIds_, ids);
}

TYPED_TEST(TestGraphStar, ForAllEdgesConst) {
    Types::count counter = 0;
    std::vector<Types::edgeId> ids;

    this->graphConst_.template for_all_edges<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids](typename TestFixture::TEdge const & edge) {
            ++counter;
            ids.push_back(edge.Identifier());
        });
    EXPECT_EQ(3, counter);
    ExpectSameContent(this->edgeIds_, ids);
}

#pragma mark ForAllEdgeTuples
TYPED_TEST(TestGraphEmpty, ForAllEdgeTuples) {
    this->graph_.template for_all_edge_tuples<egoa::ExecutionPolicy::sequential>(
        [](Types::edgeId, typename TestFixture::TEdge &) {
            FAIL();
        });
}

TYPED_TEST(TestGraphEmpty, ForAllEdgeTuplesConst) {
    this->graphConst_.template for_all_edge_tuples<egoa::ExecutionPolicy::sequential>(
        [](Types::edgeId, typename TestFixture::TEdge const &) {
            FAIL();
        });
}

TYPED_TEST(TestGraphFourVertices, ForAllEdgeTuples) {
    this->graph_.template for_all_edge_tuples<egoa::ExecutionPolicy::sequential>(
        [](Types::edgeId, typename TestFixture::TEdge &) {
            FAIL();
        });
}

TYPED_TEST(TestGraphFourVertices, ForAllEdgeTuplesConst) {
    this->graphConst_.template for_all_edge_tuples<egoa::ExecutionPolicy::sequential>(
        [](Types::edgeId, typename TestFixture::TEdge const &) {
            FAIL();
        });
}

TYPED_TEST(TestGraphBidirectedPath, ForAllEdgeTuplesModifyingCounter) {
    Types::count counter = 0;
    std::vector<Types::edgeId> ids;

    this->graph_.template for_all_edge_tuples<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids, this](Types::edgeId & id, typename TestFixture::TEdge & edge) {
            ++counter;
            ids.push_back(id);

            EXPECT_EQ(id, edge.Identifier());
            auto copyOfId = id;
            auto idBeforeModification = this->graphConst_.EdgeAt(copyOfId).Identifier();
            EXPECT_EQ(id, idBeforeModification);

            ++id;
            auto idAfterModification = this->graphConst_.EdgeAt(copyOfId).Identifier();
            EXPECT_EQ(idBeforeModification, idAfterModification);
            EXPECT_EQ(idBeforeModification, edge.Identifier());
        });

    EXPECT_EQ(4, counter);
    ExpectSameContent(this->edgeIds_, ids);
}

TYPED_TEST(TestGraphBidirectedPath, ForAllEdgeTuplesModifyingCounterConst) {
    Types::count counter = 0;
    std::vector<Types::edgeId> ids;

    this->graphConst_.template for_all_edge_tuples<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids, this](Types::edgeId & id, typename TestFixture::TEdge const & edge) {
            ++counter;
            ids.push_back(id);

            EXPECT_EQ(id, edge.Identifier());
            auto copyOfId = id;
            auto idBeforeModification = this->graphConst_.EdgeAt(copyOfId).Identifier();
            EXPECT_EQ(id, idBeforeModification);

            ++id;
            auto idAfterModification = this->graphConst_.EdgeAt(copyOfId).Identifier();
            EXPECT_EQ(idBeforeModification, idAfterModification);
            EXPECT_EQ(idBeforeModification, edge.Identifier());
        });

    EXPECT_EQ(4, counter);
    ExpectSameContent(this->edgeIds_, ids);
}

TYPED_TEST(TestGraphStar, ForAllEdgeTuples) {
    Types::count counter = 0;
    std::vector<Types::edgeId> ids;

    this->graph_.template for_all_edge_tuples<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids](Types::edgeId id, typename TestFixture::TEdge & edge) {
            ++counter;
            ids.push_back(edge.Identifier());

            EXPECT_EQ(id, edge.Identifier());
        });
    EXPECT_EQ(3, counter);
    ExpectSameContent(this->edgeIds_, ids);
}

TYPED_TEST(TestGraphStar, ForAllEdgeTuplesConst) {
    Types::count counter = 0;
    std::vector<Types::edgeId> ids;

    this->graphConst_.template for_all_edge_tuples<egoa::ExecutionPolicy::sequential>(
        [&counter, &ids](Types::edgeId id, typename TestFixture::TEdge const & edge) {
            ++counter;
            ids.push_back(edge.Identifier());

            EXPECT_EQ(id, edge.Identifier());
        });
    EXPECT_EQ(3, counter);
    ExpectSameContent(this->edgeIds_, ids);
}

#pragma mark ForAllEdgesAt
TYPED_TEST(TestGraphEmptyDeathTest, ForAllEdgesAt) {
    auto assertionString = this->assertionString("for_all_edges_at", "VertexExists\\(vertexId\\)");
    Types::vertexId nonexistentId = 3;
    EXPECT_DEATH(
        { this->graph_.template for_all_edges_at<egoa::ExecutionPolicy::sequential>(
            nonexistentId,
            [](typename TestFixture::TEdge &) {
                FAIL();
            });
        },
        assertionString);
}

TYPED_TEST(TestGraphEmptyDeathTest, ForAllEdgesAtConst) {
    auto assertionString = this->assertionString("for_all_edges_at", "VertexExists\\(vertexId\\)");
    Types::vertexId nonexistentId = 3;
    EXPECT_DEATH(
        { this->graphConst_.template for_all_edges_at<egoa::ExecutionPolicy::sequential>(
            nonexistentId,
            [](typename TestFixture::TEdge const &) {
                FAIL();
            });
        },
        assertionString);
}

TYPED_TEST(TestGraphFourVertices, ForAllEdgesAt) {
    for (auto id : this->vertexIds_) {
        this->graph_.template for_all_edges_at<egoa::ExecutionPolicy::sequential>(
            id,
            [](typename TestFixture::TEdge &) {
                FAIL();
            });
    }
}

TYPED_TEST(TestGraphFourVertices, ForAllEdgesAtConst) {
    for (auto id : this->vertexIds_) {
        this->graphConst_.template for_all_edges_at<egoa::ExecutionPolicy::sequential>(
            id,
            [](typename TestFixture::TEdge const &) {
                FAIL();
            });
    }
}

/// @todo Death tests
/// @todo Test for loops
/// @todo Test adding an edge if the graph is empty
/// @todo Test adding an edge to a vertex that does not exist
/// @todo Test adding an edge from a vertex that does not exist
/// @todo Test adding an edge parallel to an existing one
/// @todo Test for IncidentEdgesAt

} // namespace egoa::test

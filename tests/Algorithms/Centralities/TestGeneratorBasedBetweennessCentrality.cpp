/*
 * TestGeneratorBasedBetweennessCentrality.cpp
 *
 *  Created on: Feb 27, 2019
 *      Author: Franziska Wegner
 */

#include "TestGeneratorBasedBetweennessCentrality.hpp"

#ifdef OPENMP_AVAILABLE
    #include <omp.h>
#endif

using ::testing::Eq;
using ::testing::MatchesRegex;

namespace egoa::test {

#pragma mark TEST_BETWEENNESS_CENTRALITY_WITH_GRAPH_ACM_FIGURE_4A_B_NORM

TEST_F ( TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4aEdgeCounter
       , CheckCollection )
{
    betweennessAlgorithm_.Run();

    EXPECT_EQ ( betweennessAlgorithm_.Collection().Collection().size(), 1 );

    for ( TMeasurementRow const & row : betweennessAlgorithm_.Collection().Collection() ) 
    {
        EXPECT_EQ ( row.SourceId, 0 );
        TestCollectionValues ( row, "DTP", "", 4, 1, 4, 5, 10, 7, 3, 4 );
    }
}

TEST_F ( TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4aEdgeCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerEdge = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    EXPECT_EQ ( totalRelativeNumberOfPathsPerEdge.size(), network_.Graph().NumberOfEdges() );

    std::vector<Types::real> check = { 0.25, 0.25, 0.25, 0, 0 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerEdge, check );
}

TEST_F ( TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4aVertexCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerVertex = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    EXPECT_EQ ( totalRelativeNumberOfPathsPerVertex.size(), network_.Graph().NumberOfVertices() );

    std::vector<Types::real> check = { 1, 0.25, 0.25, 0.25 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerVertex, check );
}

TEST_F ( TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4aEdgeCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerEdge = betweennessAlgorithm_.TotalNumberOfPaths();
    EXPECT_EQ ( totalNumberOfPathsPerEdge.size(), network_.Graph().NumberOfEdges() );

    std::vector<Types::count> check = { 1, 1, 1, 0, 0 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerEdge, check );
}

TEST_F ( TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4aVertexCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerVertex = betweennessAlgorithm_.TotalNumberOfPaths();
    EXPECT_EQ ( totalNumberOfPathsPerVertex.size(), network_.Graph().NumberOfVertices() );

    std::vector<Types::count> check = { 4, 1, 1, 1 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerVertex, check );
}

#pragma mark TEST_BETWEENNESS_CENTRALITY_WITH_GRAPH_ACM_FIGURE_4B_B_NORM

TEST_F ( TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4bEdgeCounter
       , CheckCollection )
{
    betweennessAlgorithm_.Run();

    EXPECT_EQ ( betweennessAlgorithm_.Collection().Collection().size(), 1 );

    for ( TMeasurementRow const & row : betweennessAlgorithm_.Collection().Collection() ) 
    {
        EXPECT_EQ ( row.SourceId, 0 );
        TestCollectionValues ( row, "DTP", "", 4, 1, 4, 5, 10, 7, 3, 4 );
    }
}

TEST_F ( TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4bEdgeCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerEdge = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    EXPECT_EQ ( totalRelativeNumberOfPathsPerEdge.size(), network_.Graph().NumberOfEdges() );

    std::vector<Types::real> check = { 0.25, 0.25, 0.25, 0, 0 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerEdge, check );
}

TEST_F ( TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4bVertexCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerVertex = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    EXPECT_EQ ( totalRelativeNumberOfPathsPerVertex.size(), network_.Graph().NumberOfVertices() );

    std::vector<Types::real> check = { 1, 0.25, 0.25, 0.25 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerVertex, check );
}

TEST_F ( TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4bEdgeCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerEdge = betweennessAlgorithm_.TotalNumberOfPaths();
    EXPECT_EQ ( totalNumberOfPathsPerEdge.size(), network_.Graph().NumberOfEdges() );

    std::vector<Types::count> check = { 1, 1, 1, 0, 0 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerEdge, check );
}

TEST_F ( TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4bVertexCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerVertex = betweennessAlgorithm_.TotalNumberOfPaths();
    EXPECT_EQ ( totalNumberOfPathsPerVertex.size(), network_.Graph().NumberOfVertices() );

    std::vector<Types::count> check = { 4, 1, 1, 1 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerVertex, check );
}


#pragma mark TEST_BETWEENNESS_CENTRALITY_WITH_GRAPH_ACM_FIGURE_4A_VOLTAGE_ANGLE

TEST_F ( TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4aEdgeCounter
       , CheckCollection )
{
    betweennessAlgorithm_.Run();

    EXPECT_EQ ( betweennessAlgorithm_.Collection().Collection().size(), 1 );

    for ( TMeasurementRow const & row : betweennessAlgorithm_.Collection().Collection() ) 
    {
        EXPECT_EQ ( row.SourceId, 0 );
        TestCollectionValues ( row, "DTP", "", 4, 1, 4, 5, 18, 9, 6, 7 );
    }
}

TEST_F ( TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4aEdgeCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerEdge = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    EXPECT_EQ ( totalRelativeNumberOfPathsPerEdge.size(), network_.Graph().NumberOfEdges() );

    std::vector<Types::real> check = { 0.375, 0.25, 0.125, 0.125, 0.375 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerEdge, check );
}

TEST_F ( TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4aVertexCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerVertex = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    EXPECT_EQ ( totalRelativeNumberOfPathsPerVertex.size(), network_.Graph().NumberOfVertices() );

    std::vector<Types::real> check = { 1, 0.375, 0.5, 0.375 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerVertex, check );
}

TEST_F ( TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4aEdgeCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerEdge = betweennessAlgorithm_.TotalNumberOfPaths();
    EXPECT_EQ ( totalNumberOfPathsPerEdge.size(), network_.Graph().NumberOfEdges() );

    std::vector<Types::count> check = { 2, 1, 1, 1, 2 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerEdge, check );
}

TEST_F ( TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4aVertexCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerVertex = betweennessAlgorithm_.TotalNumberOfPaths();
    EXPECT_EQ ( totalNumberOfPathsPerVertex.size(), network_.Graph().NumberOfVertices() );

    std::vector<Types::count> check = { 5, 2, 3, 2 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerVertex, check );
}

#pragma mark TEST_BETWEENNESS_CENTRALITY_WITH_GRAPH_ACM_FIGURE_4B_VOLTAGE_ANGLE

TEST_F ( TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4bEdgeCounter
       , CheckCollection )
{
    betweennessAlgorithm_.Run();

    EXPECT_EQ ( betweennessAlgorithm_.Collection().Collection().size(), 1 );

    for ( TMeasurementRow const & row : betweennessAlgorithm_.Collection().Collection() ) 
    {
        EXPECT_EQ ( row.SourceId, 0 );
        TestCollectionValues ( row, "DTP", "", 4, 1, 4, 5, 12, 7, 4, 5 );
    }
}

TEST_F ( TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4bEdgeCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerEdge = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    EXPECT_EQ ( totalRelativeNumberOfPathsPerEdge.size(), network_.Graph().NumberOfEdges() );

    std::vector<Types::real> check = { 0.25, 0.375, 0.125, 0, 0.125 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerEdge, check );
}

TEST_F ( TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4bVertexCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerVertex = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    EXPECT_EQ ( totalRelativeNumberOfPathsPerVertex.size(), network_.Graph().NumberOfVertices() );

    std::vector<Types::real> check = { 1, 0.25, 0.375, 0.25 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerVertex, check );
}

TEST_F ( TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4bEdgeCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerEdge = betweennessAlgorithm_.TotalNumberOfPaths();
    EXPECT_EQ ( totalNumberOfPathsPerEdge.size(), network_.Graph().NumberOfEdges() );

    std::vector<Types::count> check = { 1, 2, 1, 0, 1 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerEdge, check );
}

TEST_F ( TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4bVertexCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerVertex = betweennessAlgorithm_.TotalNumberOfPaths();
    EXPECT_EQ ( totalNumberOfPathsPerVertex.size(), network_.Graph().NumberOfVertices() );

    std::vector<Types::count> check = { 5, 2, 3, 2 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerVertex, check );
}

} // namespace egoa::test
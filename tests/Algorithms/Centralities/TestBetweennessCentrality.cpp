/*
 * TestBetweennessCentrality.cpp
 *
 *  Created on: Feb 26, 2019
 *      Author: Franziska Wegner
 */

#include "TestBetweennessCentrality.hpp"

#ifdef OPENMP_AVAILABLE
    #include <omp.h>
#endif

using ::testing::Eq;
using ::testing::MatchesRegex;

namespace egoa::test {

#pragma mark TEST_BETWEENNESS_CENTRALITY_USING_SUSCEPTANCE_NORM_WITH_GRAPH_ACM_FIGURE_4A

TEST_F ( TestBcDtpBnormUsingAcm2018MtsfFigure4aEdgeCounter
       , Collection )
{
    betweennessAlgorithm_.Run();
    EXPECT_EQ ( betweennessAlgorithm_.Collection().Collection().size(), graph_.NumberOfVertices() );

    for ( TMeasurementRow const & row : betweennessAlgorithm_.Collection().Collection() )
    {
        if ( 0 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 10, 7, 3, 4 );
        } else if ( 1 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 12, 8, 4, 5 );
        } else if ( 2 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 10, 7, 3, 4 );
        } else if ( 3 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 12, 8, 4, 5 );
        }
    }
}

TEST_F ( TestBcDtpBnormUsingAcm2018MtsfFigure4aEdgeCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerEdge = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    EXPECT_EQ ( totalRelativeNumberOfPathsPerEdge.size(), graph_.NumberOfEdges() );

    std::vector<Types::real> check = { 0.25, 0.166667, 0.25, 0.25, 0.25 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerEdge, check );
}

TEST_F ( TestBcDtpBnormUsingAcm2018MtsfFigure4aVertexCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerVertex = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    EXPECT_EQ ( totalRelativeNumberOfPathsPerVertex.size(), graph_.NumberOfVertices() );

    std::vector<Types::real> check = { 0.66667, 0.58333, 0.66667, 0.58333 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerVertex, check );
}

TEST_F ( TestBcDtpBnormUsingAcm2018MtsfFigure4aEdgeCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerEdge = betweennessAlgorithm_.TotalNumberOfPaths();
    EXPECT_EQ ( totalNumberOfPathsPerEdge.size(), graph_.NumberOfEdges() );

    std::vector<Types::count> check = { 4, 2, 4, 4, 4 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerEdge, check );
}

TEST_F ( TestBcDtpBnormUsingAcm2018MtsfFigure4aVertexCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerVertex = betweennessAlgorithm_.TotalNumberOfPaths();
    EXPECT_EQ ( totalNumberOfPathsPerVertex.size(), graph_.NumberOfVertices() );

    std::vector<Types::count> check = { 9, 9, 9, 9 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerVertex, check );
}

#pragma mark TEST_BETWEENNESS_CENTRALITY_USING_SUSCEPTANCE_NORM_WITH_GRAPH_ACM_FIGURE_4B

TEST_F ( TestBcDtpBnormUsingAcm2018MtsfFigure4bEdgeCounter
       , CheckCollection )
{
    betweennessAlgorithm_.Run();
    EXPECT_EQ ( betweennessAlgorithm_.Collection().Collection().size(), graph_.NumberOfVertices() );
    // betweennessAlgorithm_.WriteCollection ( std::cout );

    for ( TMeasurementRow const & row : betweennessAlgorithm_.Collection().Collection() )
    {
        if ( 0 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 10, 7, 3, 4 );
        } else if ( 1 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 12, 8, 4, 5 );
        } else if ( 2 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 10, 7, 3, 4 );
        } else if ( 3 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 12, 8, 4, 5 );
        }
    }
}

TEST_F ( TestBcDtpBnormUsingAcm2018MtsfFigure4bEdgeCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerEdge = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    EXPECT_EQ ( totalRelativeNumberOfPathsPerEdge.size(), graph_.NumberOfEdges() );

    std::vector<Types::real> check = { 0.25, 0.166667, 0.25, 0.25, 0.25 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerEdge, check );
}

TEST_F ( TestBcDtpBnormUsingAcm2018MtsfFigure4bVertexCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerVertex = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    EXPECT_EQ ( totalRelativeNumberOfPathsPerVertex.size(), graph_.NumberOfVertices() );

    std::vector<Types::real> check = { 0.66667, 0.58333, 0.66667, 0.58333 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerVertex, check );
}

TEST_F ( TestBcDtpBnormUsingAcm2018MtsfFigure4bEdgeCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerEdge = betweennessAlgorithm_.TotalNumberOfPaths();
    EXPECT_EQ ( totalNumberOfPathsPerEdge.size(), graph_.NumberOfEdges() );

    std::vector<Types::count> check = { 4, 2, 4, 4, 4 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerEdge, check );
}

TEST_F ( TestBcDtpBnormUsingAcm2018MtsfFigure4bVertexCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerVertex = betweennessAlgorithm_.TotalNumberOfPaths();
    EXPECT_EQ ( totalNumberOfPathsPerVertex.size(), graph_.NumberOfVertices() );

    std::vector<Types::count> check = { 9, 9, 9, 9 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerVertex, check );
}


#pragma mark TEST_BETWEENNESS_CENTRALITY_USING_VOLTAGE_ANGLE_DIFFERENCE_WITH_GRAPH_ACM_FIGURE_4A

TEST_F ( TestBcDtpVangleUsingAcm2018MtsfFigure4aEdgeCounter
       , CheckCollection )
{
    betweennessAlgorithm_.Run();
    EXPECT_EQ ( betweennessAlgorithm_.Collection().Collection().size(), graph_.NumberOfVertices() );

    for ( TMeasurementRow const & row : betweennessAlgorithm_.Collection().Collection() )
    {
        if ( 0 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 18, 9, 6, 7 );
        } else if ( 1 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 12, 8, 4, 5 );
        } else if ( 2 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 16, 9, 5, 6 );
        } else if ( 3 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 15, 9, 5, 6 );
        }
    }
}

TEST_F ( TestBcDtpVangleUsingAcm2018MtsfFigure4aEdgeCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerEdge = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    ASSERT_EQ ( totalRelativeNumberOfPathsPerEdge.size(), graph_.NumberOfEdges() );

    std::vector<Types::real> check = { 0.333333, 0.16667, 0.166667, 0.333333, 0.5 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerEdge, check );
}

TEST_F ( TestBcDtpVangleUsingAcm2018MtsfFigure4aVertexCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerVertex = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    ASSERT_EQ ( totalRelativeNumberOfPathsPerVertex.size(), graph_.NumberOfVertices() );

    std::vector<Types::real> check = { 0.66667, 0.66667, 0.83333, 0.66667 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerVertex, check );
}

TEST_F ( TestBcDtpVangleUsingAcm2018MtsfFigure4aEdgeCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerEdge = betweennessAlgorithm_.TotalNumberOfPaths();
    ASSERT_EQ ( totalNumberOfPathsPerEdge.size(), graph_.NumberOfEdges() );

    std::vector<Types::count> check = { 6, 2, 4, 6, 8 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerEdge, check );
}

TEST_F ( TestBcDtpVangleUsingAcm2018MtsfFigure4aVertexCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerVertex = betweennessAlgorithm_.TotalNumberOfPaths();
    ASSERT_EQ ( totalNumberOfPathsPerVertex.size(), graph_.NumberOfVertices() );

    std::vector<Types::count> check = { 11, 11, 13, 11 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerVertex, check );
}

#pragma mark TEST_BETWEENNESS_CENTRALITY_USING_VOLTAGE_ANGLE_DIFFERENCE_WITH_GRAPH_ACM_FIGURE_4B

TEST_F ( TestBcDtpVangleUsingAcm2018MtsfFigure4bEdgeCounter
       , CheckCollection )
{
    betweennessAlgorithm_.Run();
    EXPECT_EQ ( betweennessAlgorithm_.Collection().Collection().size(), graph_.NumberOfVertices() );

    for ( TMeasurementRow const & row : betweennessAlgorithm_.Collection().Collection() )
    {
        if ( 0 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 12, 7, 4, 5 );
        } else if ( 1 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 12, 8, 4, 5 );
        } else if ( 2 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 10, 7, 3, 4 );
        } else if ( 3 == row.SourceId ) {
            TestCollectionValues ( row, "DTP", "", 4, 0, 0, 5, 15, 9, 5, 6 );
        }
    }
}

TEST_F ( TestBcDtpVangleUsingAcm2018MtsfFigure4bEdgeCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerEdge = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    EXPECT_EQ ( totalRelativeNumberOfPathsPerEdge.size(), graph_.NumberOfEdges() );

    std::vector<Types::real> const check = { 0.25, 0.25, 0.166667, 0.25, 0.333333 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerEdge, check );
}

TEST_F ( TestBcDtpVangleUsingAcm2018MtsfFigure4bVertexCounter
       , NumberOfRelativePaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::real>  totalRelativeNumberOfPathsPerVertex = betweennessAlgorithm_.TotalRelativeNumberOfPaths();
    EXPECT_EQ ( totalRelativeNumberOfPathsPerVertex.size(), graph_.NumberOfVertices() );

    std::vector<Types::real> const check = { 0.66667, 0.58333, 0.75, 0.58333 };
    TestTotalRelativeNumberOfPaths ( totalRelativeNumberOfPathsPerVertex, check );
}

TEST_F ( TestBcDtpVangleUsingAcm2018MtsfFigure4bEdgeCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerEdge = betweennessAlgorithm_.TotalNumberOfPaths();
    EXPECT_EQ ( totalNumberOfPathsPerEdge.size(), graph_.NumberOfEdges() );

    std::vector<Types::count> check = { 4, 4, 4, 4, 6 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerEdge, check );
}

TEST_F ( TestBcDtpVangleUsingAcm2018MtsfFigure4bVertexCounter
       , NumberOfPaths )
{
    betweennessAlgorithm_.Run();
    std::vector<Types::count> totalNumberOfPathsPerVertex = betweennessAlgorithm_.TotalNumberOfPaths();
    EXPECT_EQ ( totalNumberOfPathsPerVertex.size(), graph_.NumberOfVertices() );

    std::vector<Types::count> check = { 11, 9, 11, 11 };
    TestTotalNumberOfPaths ( totalNumberOfPathsPerVertex, check );
}


#pragma mark TEST_MULTIPLE_CASES
// ---------

TEST_F ( TestBcDtpVangleUsingMultipleCases
       , Test1 )
{
    Types::string TestCaseExample = "../../framework/data/PowerGrids/IEEE/00-Matpower-Data/case9.m";
    TPowerGrid network;
    if (!TPowerGridIO::read ( network_
                            , TestCaseExample
                            , TPowerGridIO::readIeeeCdfMatlab ) )
    {
        std::cerr   << "Expected file "
                    << TestCaseExample
                    << " does not exist!";
        exit(1);
    }
    graph_ = network.Graph();
    TGraph & graph = network.Graph();

    TBcDtpVangle betweennessAlgorithm ( graph );
    betweennessAlgorithm.Run();
}

} // namespace egoa::test

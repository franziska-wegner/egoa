/*
 * TestDominatingThetaPath.cpp
 *
 *  Created on: Feb 14, 2019
 *      Author: Franziska Wegner
 */

#include "TestDominatingThetaPath.hpp"
#include "Helper/TestHelper.hpp"

#ifdef OPENMP_AVAILABLE
    #include <omp.h>
#endif

using ::testing::Eq;
using ::testing::MatchesRegex;

namespace egoa::test {

#pragma mark TEST_DOMINATING_THETA_PATH_PRIMITIVES

TEST_F ( TestDTPEmptyGraph
       , QueueEmpty )
{
    EXPECT_EQ ( dtp_.NumberOfLabels(), 0 );
}

TEST_F ( TestDTPEmptyGraph
       , Reset )
{
    EXPECT_EQ ( dtp_.NumberOfLabels(), 0 );
    dtp_.Clear();
    EXPECT_EQ ( dtp_.NumberOfLabels(), 0 );
}

TEST_F ( TestDTPEmptyGraph
       , Run )
{
    dtp_.Run();
    EXPECT_EQ ( dtp_.NumberOfLabels(), 0 );
}

#ifdef EGOA_ENABLE_ASSERTION
    TEST_F ( TestDTPEmptyGraphDeathTest
           , SetSource )
    {
        auto assertionString = buildAssertionString ( "DominatingThetaPath.hpp"
                                                    , "DominatingThetaPath"
                                                    , "Source"
                                                    , "source < labelSets_.size\\(\\)");

        ASSERT_DEATH ( {dtp_.Source(0);}, assertionString );
    }
#else // EGOA_ENABLE_ASSERTION
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F ( TestDTPEmptyGraphExceptionHandling
           , SetSource )
    {
        auto assertionString = buildAssertionString ( "DominatingThetaPath.hpp"
                                                    , "DominatingThetaPath"
                                                    , "Source"
                                                    , "source < labelSets_.size\\(\\)");

        try {
            dtp_.Source(0);
        } catch ( std::runtime_error const & error ) {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) {
            FAIL()  << "Expected std::runtime_error with message: "
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

#pragma mark TEST_DOMINATING_THETA_PATH_WITH_GRAPH_ACM_FIGURE_4A

TEST_F  ( TestDTPUsingAcm2018MtsfFigure4a
        , NumberOfLabels )
{
    EXPECT_EQ ( dtp_.NumberOfLabels(), 0 );
}

TEST_F  ( TestDTPUsingAcm2018MtsfFigure4a
        , Initialization )
{
    EXPECT_EQ ( graph_.NumberOfVertices(), 4 );
    EXPECT_EQ ( graph_.NumberOfEdges(),    5 );
    EXPECT_EQ ( graph_.NumberOfEdges(),    5 );
    EXPECT_EQ ( graph_.MinDegree(),        2 );
    EXPECT_EQ ( graph_.MaxDegree(),        3 );

    Types::edgeId edgeId = graph_.EdgeId ( static_cast<Types::vertexId>(0)
                                         , static_cast<Types::vertexId>(1) );
    TestEdgeValues ( edgeId, 0, 1.00, -1.00, -1.00, 0.00, 0.00 );

    edgeId = graph_.EdgeId ( static_cast<Types::vertexId>(0)
                           , static_cast<Types::vertexId>(2) );
    TestEdgeValues ( edgeId, 1, 4.00, -1.00, -1.00, 0.00, 0.00 );

    edgeId = graph_.EdgeId ( static_cast<Types::vertexId>(0)
                           , static_cast<Types::vertexId>(3) );
    TestEdgeValues ( edgeId, 2, 3.00, -1.00, -1.00, 0.00, 0.00 );

    edgeId = graph_.EdgeId ( static_cast<Types::vertexId>(1)
                           , static_cast<Types::vertexId>(2) );
    TestEdgeValues ( edgeId, 3, 1.00, -1.00, -1.00, 0.00, 0.00 );

    edgeId = graph_.EdgeId ( static_cast<Types::vertexId>(2)
                           , static_cast<Types::vertexId>(3) );
    TestEdgeValues ( edgeId, 4, 1.00, -1.00, -1.00, 0.00, 0.00 );
}

TEST_F  ( TestDTPUsingAcm2018MtsfFigure4a
        , RunDTPwithEmptySource )
{
    dtp_.Run();
    EXPECT_EQ ( 0, dtp_.NumberOfLabels() );
}

TEST_F  ( TestDTPUsingAcm2018MtsfFigure4a
        , RunDTPwithSource )
{
    dtp_.Source ( source_ );
    dtp_.Run();
    EXPECT_EQ ( 4, dtp_.NumberOfLabels() );
}

TEST_F  ( TestDTPUsingAcm2018MtsfFigure4a
        , RunDTPthetaWithSource )
{
    dtpTheta_.Source ( source_ );
    dtpTheta_.Run();
    EXPECT_EQ ( 7, dtpTheta_.NumberOfLabels() );
}

TEST_F  ( TestDTPUsingAcm2018MtsfFigure4a
        , RunDTPthetaWithSourceResultGraph )
{
    dtpTheta_.Source ( source_ );
    dtpTheta_.Run();
    EXPECT_EQ ( 7, dtpTheta_.NumberOfLabels() );

    // Sink at 0
    Subgraph<TGraph const> expectedGraphWithSink0{&graph_, {0}, {}};
    Subgraph<TGraph const> resultGraphWithSink0{nullptr, {}, {}};
    Types::real result = dtpTheta_.Result( resultGraphWithSink0, 0 );

    EXPECT_EQ ( expectedGraphWithSink0, resultGraphWithSink0 );
    EXPECT_EQ ( 0, result );

    // Sink at 1
    Subgraph<TGraph const> expectedGraphWithSink1{&graph_, {0, 1}, {0}};
    Subgraph<TGraph const> resultGraphWithSink1{nullptr, {}, {}};
    result = dtpTheta_.Result( resultGraphWithSink1, 1 );
    EXPECT_EQ ( expectedGraphWithSink1, resultGraphWithSink1 );
    EXPECT_EQ ( 1, result );

    // Sink at 2
    Subgraph<TGraph const> expectedGraphWithSink2{&graph_, {0, 1, 2, 3}, {0, 3, 2, 4}};
    Subgraph<TGraph const> resultGraphWithSink2{nullptr, {}, {}};
    result = dtpTheta_.Result( resultGraphWithSink2, 2 );
    EXPECT_EQ(expectedGraphWithSink2, resultGraphWithSink2);
    EXPECT_EQ ( 2, result );

    // Sink at 3
    Subgraph<TGraph const> expectedGraphWithSink3{&graph_, {0, 2, 3}, {1, 4}};
    Subgraph<TGraph const> resultGraphWithSink3{nullptr, {}, {}};
    result = dtpTheta_.Result( resultGraphWithSink3, 3 );
    EXPECT_EQ(expectedGraphWithSink3, resultGraphWithSink3);
    EXPECT_EQ ( 2, result );
}

TEST_F  ( TestDTPUsingAcm2018MtsfFigure4a
        , RunDTPthetaWithSourceResultVector )
{
    dtpTheta_.Source ( source_ );
    dtpTheta_.Run();
    EXPECT_EQ ( 7, dtpTheta_.NumberOfLabels() );

    std::vector<std::vector<Types::vertexId>> resultVectorWithSink;

    Types::real result = dtpTheta_.Result( resultVectorWithSink, 0 );
    EXPECT_EQ( resultVectorWithSink.size(), 1 );
    EXPECT_EQ( resultVectorWithSink[0].size(), 1 );
    EXPECT_EQ( resultVectorWithSink[0][0], 0 );
    EXPECT_EQ ( result, 0 );

    resultVectorWithSink.clear();
    result = dtpTheta_.Result( resultVectorWithSink, 1 );
    EXPECT_EQ( resultVectorWithSink.size(), 1 );
    EXPECT_EQ( resultVectorWithSink[0].size(), 2 );
    EXPECT_EQ( resultVectorWithSink[0][0], 0 );
    EXPECT_EQ( resultVectorWithSink[0][1], 1 );
    EXPECT_EQ ( result, 1 );

    resultVectorWithSink.clear();
    result = dtpTheta_.Result( resultVectorWithSink, 2 );
    EXPECT_EQ( resultVectorWithSink.size(), 2 );
    EXPECT_EQ( resultVectorWithSink[0].size(), 3 );
    EXPECT_EQ( resultVectorWithSink[0][0], 0 );
    EXPECT_EQ( resultVectorWithSink[0][1], 3 );
    EXPECT_EQ( resultVectorWithSink[0][2], 2 );
    EXPECT_EQ( resultVectorWithSink[1].size(), 3 );
    EXPECT_EQ( resultVectorWithSink[1][0], 0 );
    EXPECT_EQ( resultVectorWithSink[1][1], 1 );
    EXPECT_EQ( resultVectorWithSink[1][2], 2 );
    EXPECT_EQ ( result, 2 );

    resultVectorWithSink.clear();
    result = dtpTheta_.Result( resultVectorWithSink, 3 );
    EXPECT_EQ( resultVectorWithSink.size(), 1 );
    EXPECT_EQ( resultVectorWithSink[0].size(), 3 );
    EXPECT_EQ( resultVectorWithSink[0][0], 0 );
    EXPECT_EQ( resultVectorWithSink[0][1], 2 );
    EXPECT_EQ( resultVectorWithSink[0][2], 3 );
    EXPECT_EQ ( result, 2 );
}

#pragma mark TEST_DOMINATING_THETA_PATH_WITH_GRAPH_ACM_FIGURE_4B

TEST_F  ( TestDTPUsingAcm2018MtsfFigure4b
        , NumberOfLabels )
{
    EXPECT_EQ ( dtp_.NumberOfLabels(), 0 );
}

TEST_F  ( TestDTPUsingAcm2018MtsfFigure4b
        , Initialization )
{
    EXPECT_EQ ( graph_.NumberOfVertices(), 4 );
    EXPECT_EQ ( graph_.NumberOfEdges(),    5 );
    EXPECT_EQ ( graph_.NumberOfEdges(),    5 );
    EXPECT_EQ ( graph_.MinDegree(),        2 );
    EXPECT_EQ ( graph_.MaxDegree(),        3 );

    Types::edgeId edgeId = graph_.EdgeId ( static_cast<Types::vertexId>(0)
                                         , static_cast<Types::vertexId>(1) );
    TestEdgeValues ( edgeId, 0, 1.00, -1.00, -1.00, 0.00, 0.00 );

    edgeId = graph_.EdgeId ( static_cast<Types::vertexId>(0)
                           , static_cast<Types::vertexId>(2) );
    TestEdgeValues ( edgeId, 1, 1.00, -1.00, -1.00, 0.00, 0.00 );

    edgeId = graph_.EdgeId ( static_cast<Types::vertexId>(0)
                           , static_cast<Types::vertexId>(3) );
    TestEdgeValues ( edgeId, 2, 2.00, -1.00, -1.00, 0.00, 0.00 );

    edgeId = graph_.EdgeId ( static_cast<Types::vertexId>(1)
                           , static_cast<Types::vertexId>(2) );
    TestEdgeValues ( edgeId, 3, 1.00, -1.00, -1.00, 0.00, 0.00 );

    edgeId = graph_.EdgeId ( static_cast<Types::vertexId>(2)
                           , static_cast<Types::vertexId>(3) );
    TestEdgeValues ( edgeId, 4, 1.00, -1.00, -1.00, 0.00, 0.00 );
}

TEST_F  ( TestDTPUsingAcm2018MtsfFigure4b
        , RunDTPwithEmptySource )
{
    dtp_.Run();
    EXPECT_EQ ( dtp_.NumberOfLabels(), 0 );
}

TEST_F  ( TestDTPUsingAcm2018MtsfFigure4b
        , RunDTPwithSource )
{
    dtp_.Source ( source_ );
    dtp_.Run();
    EXPECT_EQ ( dtp_.NumberOfLabels(), 4 );
}

TEST_F  ( TestDTPUsingAcm2018MtsfFigure4b
        , RunDTPthetaWithSource )
{
    dtpTheta_.Source ( source_ );
    dtpTheta_.Run();
    EXPECT_EQ ( dtpTheta_.NumberOfLabels(), 5 );
}

TEST_F  ( TestDTPUsingAcm2018MtsfFigure4b
        , RunDTPthetaWithSourceResultGraph )
{
    dtpTheta_.Source ( source_ );
    dtpTheta_.Run();
    EXPECT_EQ ( dtpTheta_.NumberOfLabels(), 5 );

    // Sink at 0
    Subgraph<TGraph const> expectedGraphWithSink0{&graph_, {0}, {}};
    Subgraph<TGraph const> resultGraphWithSink0{nullptr, {}, {}};
    Types::real result = dtpTheta_.Result( resultGraphWithSink0, 0 );
    EXPECT_EQ(expectedGraphWithSink0, resultGraphWithSink0);
    EXPECT_EQ ( result, 0 );

    // Sink at 1
    Subgraph<TGraph const> expectedGraphWithSink1{&graph_, {0, 1}, {0}};
    Subgraph<TGraph const> resultGraphWithSink1{nullptr, {}, {}};
    result = dtpTheta_.Result( resultGraphWithSink1, 1 );
    EXPECT_EQ(expectedGraphWithSink1, resultGraphWithSink1);
    EXPECT_EQ ( result, 1 );

    // Sink at 2
    Subgraph<TGraph const> expectedGraphWithSink2{&graph_, {0, 2}, {1}};
    Subgraph<TGraph const> resultGraphWithSink2{nullptr, {}, {}};
    result = dtpTheta_.Result( resultGraphWithSink2, 2 );
    EXPECT_EQ(expectedGraphWithSink2, resultGraphWithSink2);
    EXPECT_EQ ( result, 1 );

    // Sink at 3
    Subgraph<TGraph const> expectedGraphWithSink3{&graph_, {0, 2, 3}, {1, 2, 4}};
    Subgraph<TGraph const> resultGraphWithSink3{nullptr, {}, {}};
    result = dtpTheta_.Result( resultGraphWithSink3, 3 );
    EXPECT_EQ(expectedGraphWithSink3, resultGraphWithSink3);
    EXPECT_EQ ( result, 2 );
}

TEST_F  ( TestDTPUsingAcm2018MtsfFigure4b
        , RunDTPthetaWithSourceResultVector )
{
    dtpTheta_.Source ( source_ );
    dtpTheta_.Run();
    EXPECT_EQ ( dtpTheta_.NumberOfLabels(), 5 );

    std::vector<std::vector<Types::vertexId>> resultVectorWithSink;

    Types::real result = dtpTheta_.Result( resultVectorWithSink, 0 );
    EXPECT_EQ( resultVectorWithSink.size(), 1 );
    EXPECT_EQ( resultVectorWithSink[0].size(), 1 );
    EXPECT_EQ( resultVectorWithSink[0][0], 0 );
    EXPECT_EQ ( result, 0 );

    resultVectorWithSink.clear();
    result = dtpTheta_.Result( resultVectorWithSink, 1 );
    EXPECT_EQ( resultVectorWithSink.size(), 1 );
    EXPECT_EQ( resultVectorWithSink[0].size(), 2 );
    EXPECT_EQ( resultVectorWithSink[0][0], 0 );
    EXPECT_EQ( resultVectorWithSink[0][1], 1 );
    EXPECT_EQ ( result, 1 );

    resultVectorWithSink.clear();
    result = dtpTheta_.Result( resultVectorWithSink, 2 );
    EXPECT_EQ( resultVectorWithSink.size(), 1 );
    EXPECT_EQ( resultVectorWithSink[0].size(), 2 );
    EXPECT_EQ( resultVectorWithSink[0][0], 0 );
    EXPECT_EQ( resultVectorWithSink[0][1], 2 );
    EXPECT_EQ ( result, 1 );

    resultVectorWithSink.clear();
    result = dtpTheta_.Result( resultVectorWithSink, 3 );
    EXPECT_EQ( resultVectorWithSink.size(), 2 );
    EXPECT_EQ( resultVectorWithSink[0].size(), 2 );
    EXPECT_EQ( resultVectorWithSink[0][0], 0 );
    EXPECT_EQ( resultVectorWithSink[0][1], 3 );
    EXPECT_EQ( resultVectorWithSink[1].size(), 3 );
    EXPECT_EQ( resultVectorWithSink[1][0], 0 );
    EXPECT_EQ( resultVectorWithSink[1][1], 2 );
    EXPECT_EQ( resultVectorWithSink[1][2], 3 );
    EXPECT_EQ ( result, 2 );
}

} // namespace egoa::test

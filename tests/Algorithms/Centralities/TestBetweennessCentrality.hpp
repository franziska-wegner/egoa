/*
 * TestBetweennessCentrality.hpp
 *
 *  Created on: Feb 26, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__TESTS__ALGORITHMS__TEST_BETWEENNESS_CENTRALITY_HPP
#define EGOA__TESTS__ALGORITHMS__TEST_BETWEENNESS_CENTRALITY_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Algorithms/PathFinding/DominatingThetaPath.hpp"

#include "IO/PowerGridIO.hpp"

#include "DataStructures/Networks/PowerGrid.hpp"

#include "DataStructures/Graphs/StaticGraph.hpp"

#include "DataStructures/Labels/SusceptanceNormLabel.hpp"
#include "DataStructures/Labels/VoltageAngleDifferenceLabel.hpp"

#include "DataStructures/Container/Queues/Bucket.hpp"
#include "DataStructures/Container/Queues/BinaryHeap.hpp"
#include "DataStructures/Container/Queues/MappingBinaryHeap.hpp"

#include "DataStructures/Container/DominationCriterion.hpp"

#include "Algorithms/Centralities/BetweennessCentrality.hpp"
#include "IO/Statistics/DtpRuntimeCollection.hpp"

namespace egoa::test {

/**
 * @brief      Fixture that provides the basic network and measurement setup 
 */
class TestBetweennessCentralityGraph : public ::testing::Test {
    protected:
        ///@name Type aliasing
        ///@{
#pragma mark BC_GRAPH_TYPE_ALIASING
            
            // Graph and network data structures
            using TVertex           = Vertices::Vertex<Vertices::ElectricalProperties<>>;
            using TVertexProperties = TVertex::TProperties;
            using TEdge             = Edges::Edge<Edges::ElectricalProperties>;
            using TEdgeProperties   = TEdge::TProperties;
            using TGraph            = StaticGraph<TVertexProperties, TEdgeProperties>;
            // Graph and network data structures
            using TPowerGrid        = PowerGrid<TGraph>;
            // IO
            using TPowerGridIO      = PowerGridIO<TGraph>;
            // Measurement 
            using TMeasurementCollection = IO::DtpRuntimeCollection;
            using TMeasurementRow        = typename TMeasurementCollection::TRow;
        ///@}

        ///@name Constructors and destructor
        ///@{
#pragma mark BC_GRAPH_CONSTRUCTORS_AND_DESTRUCTOR

            TestBetweennessCentralityGraph ()
            : graph_()
            , graphConst_( graph_ )
            {}

            TestBetweennessCentralityGraph ( TGraph && graph )
            : graph_( graph )
            , graphConst_( graph_ )
            {}

            TestBetweennessCentralityGraph ( TGraph const & graph )
            : graph_( graph )
            , graphConst_( graph_ )
            {}

            virtual ~TestBetweennessCentralityGraph () {}
        ///@}

#pragma mark BC_GRAPH_TEST_METHODS
        /**
         * @brief      Test the  collection values.
         *
         * @param      row                            The row
         * @param[in]  nameOfProblem                  The name of problem.
         * @param[in]  name                           The name.
         * @param[in]  numberOfVertices               The number of vertices.
         * @param[in]  numberOfGenerators             The number of generators.
         * @param[in]  numberOfLoads                  The number of loads.
         * @param[in]  numberOfEdges                  The number of edges.
         * @param[in]  numberOfScannedEdges           The number of scanned edges.
         * @param[in]  numberOfEdgesProducingNoCycle  The number of edges producing no cycle.
         * @param[in]  numberOfRelaxedEdges           The number of relaxed edges.
         * @param[in]  numberOfLabels                 The number of labels.
         */
        inline void TestCollectionValues ( TMeasurementRow const & row
                                         , Types::string    nameOfProblem
                                         , Types::name      name
                                         , Types::count     numberOfVertices
                                         , Types::count     numberOfGenerators
                                         , Types::count     numberOfLoads
                                         , Types::count     numberOfEdges
                                         , Types::count     numberOfScannedEdges
                                         , Types::count     numberOfEdgesProducingNoCycle
                                         , Types::count     numberOfRelaxedEdges
                                         , Types::count     numberOfLabels)
        {
            EXPECT_EQ ( row.NameOfProblem,                  nameOfProblem                   );
            EXPECT_EQ ( row.Name,                           name                            );
            EXPECT_EQ ( row.NumberOfVertices,               numberOfVertices                );
            EXPECT_EQ ( row.NumberOfGenerators,             numberOfGenerators              );
            EXPECT_EQ ( row.NumberOfLoads,                  numberOfLoads                   );
            EXPECT_EQ ( row.NumberOfEdges,                  numberOfEdges                   );
            EXPECT_EQ ( row.NumberOfScannedEdges,           numberOfScannedEdges            );
            EXPECT_EQ ( row.NumberOfEdgesProducingNoCycle,  numberOfEdgesProducingNoCycle   );
            EXPECT_EQ ( row.NumberOfRelaxedEdges,           numberOfRelaxedEdges            );
            EXPECT_EQ ( row.NumberOfLabels,                 numberOfLabels                  );
        }

        /**
         * @brief      Test the total number of paths.
         *
         * @param      original  The original representing the algorithm output.
         * @param      check     The check representing the vector of expected values.
         */
        inline void TestTotalNumberOfPaths ( std::vector<Types::count> const & original
                                           , std::vector<Types::count> const & check    ) const
        {
            ASSERT_EQ ( original.size(), check.size() );

            for (Types::count counter = 0
                ; counter < original.size()
                ; ++counter )
            {
                EXPECT_EQ ( original[counter], check[counter] );
            }
        }

        /**
         * @brief      Test the total relative number of paths.
         *
         * @param      original  The original representing the algorithm output.
         * @param      check     The check representing the vector of expected values.
         */
        inline void TestTotalRelativeNumberOfPaths ( std::vector<Types::real> const & original
                                                   , std::vector<Types::real> const & check    ) const
        {
            ASSERT_EQ ( original.size(), check.size() );
            
            for (Types::count counter = 0
                ; counter < original.size()
                ; ++counter )
            {
                EXPECT_EQ ( round ( original[counter] * 100000.0 ) / 100000.0
                          , round ( check[counter]    * 100000.0 ) / 100000.0 );
            }
        }

#pragma mark BC_GRAPH_MEMBERS
        TGraph                  graph_;
        TGraph          const & graphConst_;

        TPowerGrid              network_;
        TPowerGrid      const & constNetwork_ = network_;

        Types::string   const   TestCaseAcm2018MtsfFigure4a_ = "../../framework/tests/Data/PowerGrids/ieee_2018_acm_eEnergy_MTSF_Figure4a.m";
        Types::string   const   TestCaseAcm2018MtsfFigure4b_ = "../../framework/tests/Data/PowerGrids/ieee_2018_acm_eEnergy_MTSF_Figure4b.m";
};

// ***********************************************************************
// ***********************************************************************
#pragma mark BC_DTP_VANGLE
// ***********************************************************************
// ***********************************************************************

/**
 * @brief      Class for testing the betweenness centrality with DTP and
 *     voltage angle difference label.
 */
class TestBetweennessCentralityDtpVoltageAngleDifference 
        : public TestBetweennessCentralityGraph 
{
    protected:

#pragma mark BC_DTP_VANGLE_TYPE_ALIASING
        // Power Grid DTP specific data structures including voltage angles
        using TLabel         = VoltageAngleDifferenceLabel<TGraph::TEdge>;
        // Queues
        using TQueue         = BinaryHeap<TLabel>;
        using TMQueue        = MappingBinaryHeap<typename TGraph::TVertexId, TLabel >;
        // Bucket
        using TLabelSet      = Bucket< TQueue >;
        
        // Dominating theta path using susceptance norm only
        using TFindPathAlgo  = DominatingThetaPath < TGraph
                                                   , TLabel
                                                   , TMQueue
                                                   , TLabelSet
                                                   , DominationCriterion::strict >;

#pragma mark BC_DTP_VANGLE_CONSTRUCTORS_AND_DESTRUCTOR
       TestBetweennessCentralityDtpVoltageAngleDifference ()
       : TestBetweennessCentralityGraph( std::move( TGraph( "Empty Test Graph" ) ) )
       {}

       TestBetweennessCentralityDtpVoltageAngleDifference ( TGraph && graph )
       : TestBetweennessCentralityGraph( graph )
       {}

       TestBetweennessCentralityDtpVoltageAngleDifference ( TGraph const & graph )
       : TestBetweennessCentralityGraph( graph )
       {}

       ~TestBetweennessCentralityDtpVoltageAngleDifference () {}
}; 

// ***********************************************************************
// ***********************************************************************
#pragma mark BC_DTP_VANGLE_EDGE_COUNTER
// ***********************************************************************
// ***********************************************************************

/**
 * @brief      Class for testing the betweenness centrality with DTP and
 *     voltage angle difference label using @c edge counter @c.
 */
class TestBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter 
        : public TestBetweennessCentralityDtpVoltageAngleDifference 
{
    protected:
#pragma mark BC_DTP_VANGLE_EDGE_COUNTER_TYPE_ALIASING
        using TBcDtpVangle   = BetweennessCentrality < TGraph
                                                     , TFindPathAlgo
                                                     , TMeasurementCollection
                                                     , CentralityCounter::counterAtEdges >;
 
 #pragma mark BC_DTP_VANGLE_EDGE_COUNTER_CONSTRUCTORS_AND_DESTRUCTOR
       TestBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter ()
       : TestBetweennessCentralityDtpVoltageAngleDifference()
       , betweennessAlgorithm_( graphConst_ )
       {}

       TestBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter ( TGraph && graph )
       : TestBetweennessCentralityDtpVoltageAngleDifference( graph )
       , betweennessAlgorithm_( graphConst_ )
       {}

       TestBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter ( TGraph const & graph )
       : TestBetweennessCentralityDtpVoltageAngleDifference( graph )
       , betweennessAlgorithm_( graphConst_ )
       {}

       ~TestBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter () {}

#pragma mark BC_DTP_VANGLE_EDGE_COUNTER_MEMBER
        TBcDtpVangle betweennessAlgorithm_;
}; 

// ***********************************************************************
// ***********************************************************************
#pragma mark BC_DTP_VANGLE_VERTEX_COUNTER
// ***********************************************************************
// ***********************************************************************

/**
 * @brief      Class for test betweenness centrality with DTP and voltage
 *     angle difference labels using vertex counter.
 */
class TestBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter 
        : public TestBetweennessCentralityDtpVoltageAngleDifference 
{
    protected:
#pragma mark BC_DTP_VANGLE_VERTEX_COUNTER_TYPE_ALIASING
        using TBcDtpVangle   = BetweennessCentrality < TGraph
                                                     , TFindPathAlgo
                                                     , TMeasurementCollection
                                                     , CentralityCounter::counterAtVertices >;

#pragma mark BC_DTP_VANGLE_VERTEX_COUNTER_CONSTRUCTORS_AND_DESTRUCTOR
       TestBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter ()
       : TestBetweennessCentralityDtpVoltageAngleDifference()
       , betweennessAlgorithm_( graphConst_ )
       {}

       TestBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter ( TGraph && graph )
       : TestBetweennessCentralityDtpVoltageAngleDifference( graph )
       , betweennessAlgorithm_( graphConst_ )
       {}

       TestBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter ( TGraph const & graph )
       : TestBetweennessCentralityDtpVoltageAngleDifference( graph )
       , betweennessAlgorithm_( graphConst_ )
       {}

       ~TestBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter () {}

#pragma mark BC_DTP_VANGLE_VERTEX_COUNTER_MEMBERS
        TBcDtpVangle betweennessAlgorithm_;
}; 

#pragma mark BC_DTP_SUSCEPTANCE_NORM

/**
 * @brief      Class for test betweenness centrality with DTP and susceptance
 *     norm labels.
 */
class TestBetweennessCentralityDtpSusceptanceNorm 
        : public TestBetweennessCentralityGraph 
{
    protected:

#pragma mark BC_DTP_SUSCEPTANCE_NORM_TYPE_ALIASING
        // Label specific data structures
        using TLabel         = SusceptanceNormLabel<TGraph::TEdge>;
        // Queues
        using TQueue         = BinaryHeap< TLabel >;
        using TMQueue        = MappingBinaryHeap< typename TGraph::TVertexId, TLabel >;
        // Bucket
        using TLabelSet      = Bucket<TQueue>;
        // Dominating theta path using susceptance norm only
        using TFindPathAlgo  = DominatingThetaPath < TGraph
                                                   , TLabel
                                                   , TMQueue
                                                   , TLabelSet
                                                   , DominationCriterion::strict >;

#pragma mark BC_DTP_SUSCEPTANCE_NORM_CONSTRUCTORS_AND_DESTRUCTOR
        TestBetweennessCentralityDtpSusceptanceNorm ()
        : TestBetweennessCentralityGraph( std::move( TGraph( "Empty Test Graph" ) ) )
        {}

        TestBetweennessCentralityDtpSusceptanceNorm ( TGraph && graph )
        : TestBetweennessCentralityGraph( graph )
        {}

        TestBetweennessCentralityDtpSusceptanceNorm ( TGraph const & graph )
        : TestBetweennessCentralityGraph( graph )
        {}

        ~TestBetweennessCentralityDtpSusceptanceNorm () {}
};

#pragma mark BC_DTP_SUSCEPTANCE_NORM_EDGE_COUNTER

/**
 * @brief      Class for testing the betweenness centrality with DTP and
 *     susceptance norm labels using @c edge counter @c.
 */
class TestBetweennessCentralityDtpSusceptanceNormEdgeCounter 
        : public TestBetweennessCentralityDtpSusceptanceNorm 
{
    protected:

#pragma mark BC_DTP_SUSCEPTANCE_NORM_EDGE_COUNTER_TYPE_ALIASING
        using TBcDtpBnorm    = BetweennessCentrality < TGraph
                                                     , TFindPathAlgo
                                                     , TMeasurementCollection
                                                     , CentralityCounter::counterAtEdges >;

#pragma mark BC_DTP_SUSCEPTANCE_NORM_EDGE_COUNTER_CONSTRUCTORS_AND_DESTRUCTOR
        TestBetweennessCentralityDtpSusceptanceNormEdgeCounter ()
        : TestBetweennessCentralityDtpSusceptanceNorm( )
        , betweennessAlgorithm_( graphConst_ )
        {}

        TestBetweennessCentralityDtpSusceptanceNormEdgeCounter ( TGraph && graph )
        : TestBetweennessCentralityDtpSusceptanceNorm( graph )
        , betweennessAlgorithm_( graphConst_ )
        {}

        TestBetweennessCentralityDtpSusceptanceNormEdgeCounter ( TGraph const & graph )
        : TestBetweennessCentralityDtpSusceptanceNorm( graph )
        , betweennessAlgorithm_( graphConst_ )
        {}

        ~TestBetweennessCentralityDtpSusceptanceNormEdgeCounter () {}
    
#pragma mark BC_DTP_SUSCEPTANCE_NORM_EDGE_COUNTER_MEMBERS
        TBcDtpBnorm betweennessAlgorithm_;
};

/**
 * @brief      Class for testing the betweenness centrality with DTP and
 *     susceptance norm labels using @c vertex counter @c.
 */
class TestBetweennessCentralityDtpSusceptanceNormVertexCounter 
        : public TestBetweennessCentralityDtpSusceptanceNorm 
{
    protected:
        using TBcDtpBnorm    = BetweennessCentrality < TGraph
                                                     , TFindPathAlgo
                                                     , TMeasurementCollection
                                                     , CentralityCounter::counterAtVertices >;

        TestBetweennessCentralityDtpSusceptanceNormVertexCounter ()
        : TestBetweennessCentralityDtpSusceptanceNorm( )
        , betweennessAlgorithm_( graphConst_ )
        {}

        TestBetweennessCentralityDtpSusceptanceNormVertexCounter ( TGraph && graph )
        : TestBetweennessCentralityDtpSusceptanceNorm( graph )
        , betweennessAlgorithm_( graphConst_ )
        {}

        TestBetweennessCentralityDtpSusceptanceNormVertexCounter ( TGraph const & graph )
        : TestBetweennessCentralityDtpSusceptanceNorm( graph )
        , betweennessAlgorithm_( graphConst_ )
        {}

        virtual ~TestBetweennessCentralityDtpSusceptanceNormVertexCounter () {}
    
    protected:
        TBcDtpBnorm betweennessAlgorithm_;
};

/**
 * @brief      Class for testing the betweenness centrality with DTP and
 *     susceptance norm labels using @c edge counter @c and the @c
 *     Acm2018MtsfFigure4a @c.
 */
class TestBcDtpBnormUsingAcm2018MtsfFigure4aEdgeCounter 
        : public TestBetweennessCentralityDtpSusceptanceNormEdgeCounter 
{
    protected:
        TestBcDtpBnormUsingAcm2018MtsfFigure4aEdgeCounter ()
        : TestBetweennessCentralityDtpSusceptanceNormEdgeCounter( std::move( TGraph( "Acm2018MtsfFigure4a" ) ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4a_
                                    , TPowerGridIO::readIeeeCdfMatlab ) ) 
            {
                std::cerr   << "Expected file " 
                            << TestCaseAcm2018MtsfFigure4a_ 
                            << " does not exist!";
                exit(1);
            }
            graph_ = network_.Graph();
        }

        virtual ~TestBcDtpBnormUsingAcm2018MtsfFigure4aEdgeCounter(){}

        virtual void SetUp() override 
        {
            betweennessAlgorithm_.Clear();
        }
};

/**
 * @brief      Class for testing the betweenness centrality with DTP and
 *     susceptance norm labels using @c vertex counter @c and the @c
 *     Acm2018MtsfFigure4a @c.
 */
class TestBcDtpBnormUsingAcm2018MtsfFigure4aVertexCounter 
        : public TestBetweennessCentralityDtpSusceptanceNormVertexCounter 
{
    protected:
        TestBcDtpBnormUsingAcm2018MtsfFigure4aVertexCounter ()
        : TestBetweennessCentralityDtpSusceptanceNormVertexCounter( std::move( TGraph( "Acm2018MtsfFigure4a" ) ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4a_
                                    , TPowerGridIO::readIeeeCdfMatlab ) ) 
            {
                std::cerr   << "Expected file " 
                            << TestCaseAcm2018MtsfFigure4a_ 
                            << " does not exist!";
                exit(1);
            }
            graph_ = network_.Graph();
        }

        virtual ~TestBcDtpBnormUsingAcm2018MtsfFigure4aVertexCounter(){}

        virtual void SetUp() override 
        {
            betweennessAlgorithm_.Clear();
        }
};

/**
 * @brief      Class for testing the betweenness centrality with DTP and
 *     susceptance norm labels using @c edge counter @c and the @c
 *     Acm2018MtsfFigure4b @c.
 */
class TestBcDtpBnormUsingAcm2018MtsfFigure4bEdgeCounter 
        : public TestBetweennessCentralityDtpSusceptanceNormEdgeCounter 
{
    protected:
        TestBcDtpBnormUsingAcm2018MtsfFigure4bEdgeCounter ()
        : TestBetweennessCentralityDtpSusceptanceNormEdgeCounter( std::move( TGraph( "Acm2018MtsfFigure4b" ) ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4b_
                                    , TPowerGridIO::readIeeeCdfMatlab ) ) 
            {
                std::cerr   << "Expected file " 
                            << TestCaseAcm2018MtsfFigure4b_ 
                            << " does not exist!";
                exit(1);
            }
            graph_ = network_.Graph();
        }

        virtual ~TestBcDtpBnormUsingAcm2018MtsfFigure4bEdgeCounter(){}

        virtual void SetUp() override 
        {
            betweennessAlgorithm_.Clear();
        }
};

/**
 * @brief      Class for testing the betweenness centrality with DTP and
 *     susceptance norm labels using @c vertex counter @c and the @c
 *     Acm2018MtsfFigure4b @c.
 */
class TestBcDtpBnormUsingAcm2018MtsfFigure4bVertexCounter 
        : public TestBetweennessCentralityDtpSusceptanceNormVertexCounter 
{
    protected:
        TestBcDtpBnormUsingAcm2018MtsfFigure4bVertexCounter ()
        : TestBetweennessCentralityDtpSusceptanceNormVertexCounter( std::move( TGraph( "Acm2018MtsfFigure4b" ) ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4b_
                                    , TPowerGridIO::readIeeeCdfMatlab ) ) 
            {
                std::cerr   << "Expected file " 
                            << TestCaseAcm2018MtsfFigure4b_ 
                            << " does not exist!";
                exit(1);
            }
            graph_ = network_.Graph();
        }

        virtual ~TestBcDtpBnormUsingAcm2018MtsfFigure4bVertexCounter(){}

        virtual void SetUp() override 
        {
            betweennessAlgorithm_.Clear();
        }
};

/**
 * @brief      Class for testing the betweenness centrality with DTP and
 *     voltage angle difference labels using @c edge counter @c and the @c
 *     Acm2018MtsfFigure4a @c.
 */
class TestBcDtpVangleUsingAcm2018MtsfFigure4aEdgeCounter 
        : public TestBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter 
{
    protected:
        TestBcDtpVangleUsingAcm2018MtsfFigure4aEdgeCounter ()
        : TestBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter( std::move( TGraph( "Acm2018MtsfFigure4a" ) ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4a_
                                    , TPowerGridIO::readIeeeCdfMatlab ) ) 
            {
                std::cerr   << "Expected file " 
                            << TestCaseAcm2018MtsfFigure4a_ 
                            << " does not exist!";
                exit(1);
            }
            graph_ = network_.Graph();
        }

        virtual ~TestBcDtpVangleUsingAcm2018MtsfFigure4aEdgeCounter(){}

        virtual void SetUp() override 
        {
            betweennessAlgorithm_.Clear();
        }
};

/**
 * @brief      Class for testing the betweenness centrality with DTP and
 *     voltage angle difference labels using @c vertex counter @c and the @c
 *     Acm2018MtsfFigure4a @c.
 */
class TestBcDtpVangleUsingAcm2018MtsfFigure4aVertexCounter 
        : public TestBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter 
{
    protected:
        TestBcDtpVangleUsingAcm2018MtsfFigure4aVertexCounter ()
        : TestBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter( std::move( TGraph( "Acm2018MtsfFigure4a" ) ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4a_
                                    , TPowerGridIO::readIeeeCdfMatlab ) ) 
            {
                std::cerr   << "Expected file " 
                            << TestCaseAcm2018MtsfFigure4a_ 
                            << " does not exist!";
                exit(1);
            }
            graph_ = network_.Graph();
        }

        virtual ~TestBcDtpVangleUsingAcm2018MtsfFigure4aVertexCounter(){}

        virtual void SetUp() override 
        {
            betweennessAlgorithm_.Clear();
        }
};

/**
 * @brief      Class for testing the betweenness centrality with DTP and
 *     voltage angle difference labels using @c edge counter @c and the @c
 *     Acm2018MtsfFigure4b @c.
 */
class TestBcDtpVangleUsingAcm2018MtsfFigure4bEdgeCounter 
        : public TestBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter 
{
    protected:
        TestBcDtpVangleUsingAcm2018MtsfFigure4bEdgeCounter ()
        : TestBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter( std::move( TGraph( "Acm2018MtsfFigure4b" ) ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4b_
                                    , TPowerGridIO::readIeeeCdfMatlab ) ) 
            {
                std::cerr   << "Expected file " 
                            << TestCaseAcm2018MtsfFigure4b_ 
                            << " does not exist!";
                exit(1);
            }
            graph_ = network_.Graph();
        }

        virtual ~TestBcDtpVangleUsingAcm2018MtsfFigure4bEdgeCounter(){}

        virtual void SetUp() override 
        {
            betweennessAlgorithm_.Clear();
        }
};

/**
 * @brief      Class for testing the betweenness centrality with DTP and
 *     voltage angle difference labels using @c vertex counter @c and the @c
 *     Acm2018MtsfFigure4b @c.
 */
class TestBcDtpVangleUsingAcm2018MtsfFigure4bVertexCounter 
        : public TestBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter 
{
    protected:
        TestBcDtpVangleUsingAcm2018MtsfFigure4bVertexCounter ()
        : TestBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter( std::move( TGraph( "Acm2018MtsfFigure4b" ) ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4b_
                                    , TPowerGridIO::readIeeeCdfMatlab ) ) 
            {
                std::cerr   << "Expected file " 
                            << TestCaseAcm2018MtsfFigure4b_ 
                            << " does not exist!";
                exit(1);
            }
            graph_ = network_.Graph();
        }

        virtual ~TestBcDtpVangleUsingAcm2018MtsfFigure4bVertexCounter(){}

        virtual void SetUp() override 
        {
            betweennessAlgorithm_.Clear();
        }
};

/**
 * @brief      Class for testing the betweenness centrality with DTP and
 *     voltage angle difference labels using @c vertex counter @c and the @c
 *     Acm2018MtsfFigure4b @c.
 */
class TestBcDtpVangleUsingMultipleCases
        : public TestBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter 
{
    protected:
        TestBcDtpVangleUsingMultipleCases ()
        : TestBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter( std::move( TGraph( "MultipleCases" ) ) )
        {            
            // Types::string TestCaseExample = "../../framework/data/PowerGrids/IEEE/00-Matpower-Data/case9.m";
            // if (!TPowerGridIO::read ( network_
            //                         , TestCaseExample
            //                         , TPowerGridIO::readIeeeCdfMatlab ) ) 
            // {
            //     std::cerr   << "Expected file " 
            //                 << TestCaseExample 
            //                 << " does not exist!";
            //     exit(1);
            // }
            // graph_ = network_.Graph();
        }

        virtual ~TestBcDtpVangleUsingMultipleCases () {}

        virtual void SetUp () override 
        {
            // betweennessAlgorithm_.Clear();
        }
};

} // namespace egoa::test

#endif // EGOA__TESTS__ALGORITHMS__TEST_BETWEENNESS_CENTRALITY_HPP
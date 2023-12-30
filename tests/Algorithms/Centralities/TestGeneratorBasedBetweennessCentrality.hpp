/*
 * TestGeneratorBasedBetweennessCentrality.cpp
 *
 *  Created on: Feb 27, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__TESTS__ALGORITHMS__TEST_GENERATOR_BASED_BETWEENNESS_CENTRALITY_HPP
#define EGOA__TESTS__ALGORITHMS__TEST_GENERATOR_BASED_BETWEENNESS_CENTRALITY_HPP

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

#include "Algorithms/Centralities/GeneratorBasedBetweennessCentrality.hpp"
#include "IO/Statistics/DtpRuntimeCollection.hpp"

namespace egoa::test {

/**
 * @brief      Class creating the initial simple set up
 */
class TestGeneratorBasedBetweennessCentralityGraph
        : public ::testing::Test
{
    protected:
        // Graph and network data structures
        using TVertex           = Vertices::Vertex< Vertices::ElectricalProperties<Vertices::IeeeBusType> >;
        using TVertexProperties = TVertex::TProperties;
        // Edges
        using TEdge             = Edges::Edge< Edges::ElectricalProperties >;
        using TEdgeProperties   = TEdge::TProperties;

        using TGraph            = StaticGraph<TVertexProperties, TEdgeProperties>;
        // Graph and network data structures
        using TNetwork          = PowerGrid<TGraph>;
        // IO
        using TPowerGridIO      = PowerGridIO<TGraph>;
        // Measurement
        using TMeasurementCollection = IO::DtpRuntimeCollection;
        using TMeasurementRow        = typename TMeasurementCollection::TRow;
    protected:
        TestGeneratorBasedBetweennessCentralityGraph ()
        : network_()
        , networkConst_( network_ )
        {}

        TestGeneratorBasedBetweennessCentralityGraph ( TNetwork && network )
        : network_( network )
        , networkConst_( network_ )
        {}

        TestGeneratorBasedBetweennessCentralityGraph ( TNetwork const & network )
        : network_( network )
        , networkConst_( network_ )
        {}

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
            EXPECT_EQ ( row.NameOfProblem, nameOfProblem );
            EXPECT_EQ ( row.Name, name );
            EXPECT_EQ ( row.NumberOfVertices, numberOfVertices );
            EXPECT_EQ ( row.NumberOfGenerators, numberOfGenerators );
            EXPECT_EQ ( row.NumberOfLoads, numberOfLoads );
            EXPECT_EQ ( row.NumberOfEdges, numberOfEdges );
            EXPECT_EQ ( row.NumberOfScannedEdges, numberOfScannedEdges );
            EXPECT_EQ ( row.NumberOfEdgesProducingNoCycle, numberOfEdgesProducingNoCycle );
            EXPECT_EQ ( row.NumberOfRelaxedEdges, numberOfRelaxedEdges );
            EXPECT_EQ ( row.NumberOfLabels, numberOfLabels );
        }

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

    protected:
        TNetwork                network_;
        TNetwork        const & networkConst_ = network_;

        Types::string   const   TestCaseAcm2018MtsfFigure4a_ = "../../framework/tests/Data/PowerGrids/ieee_2018_acm_eEnergy_MTSF_Figure4a.m";
        Types::string   const   TestCaseAcm2018MtsfFigure4b_ = "../../framework/tests/Data/PowerGrids/ieee_2018_acm_eEnergy_MTSF_Figure4b.m";
};

class TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifference
        : public TestGeneratorBasedBetweennessCentralityGraph
{
    protected:
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
    protected:
       TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifference ()
       : TestGeneratorBasedBetweennessCentralityGraph( std::move( TNetwork() ) )
       {}

       TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifference ( TNetwork && network )
       : TestGeneratorBasedBetweennessCentralityGraph( network )
       {}

       TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifference ( TNetwork const & network )
       : TestGeneratorBasedBetweennessCentralityGraph( network )
       {}
};


class TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter
        : public TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifference
{
    protected:
        using TGeneratorBasedBcDtpVangle = GeneratorBasedBetweennessCentrality < TNetwork
                                                                               , TFindPathAlgo
                                                                               , TMeasurementCollection
                                                                               , CentralityCounter::counterAtEdges >;
    protected:
       TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter ()
       : TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifference( std::move( TNetwork() ) )
       , betweennessAlgorithm_( networkConst_ )
       {}

       TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter ( TNetwork && network )
       : TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifference( network )
       , betweennessAlgorithm_( networkConst_ )
       {}

       TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter ( TNetwork const & network )
       : TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifference( network )
       , betweennessAlgorithm_( networkConst_ )
       {}

    protected:
        TGeneratorBasedBcDtpVangle betweennessAlgorithm_;
};

class TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter
        : public TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifference
{
    protected:
        using TGeneratorBasedBcDtpVangle = GeneratorBasedBetweennessCentrality < TNetwork
                                                                               , TFindPathAlgo
                                                                               , TMeasurementCollection
                                                                               , CentralityCounter::counterAtVertices >;
    protected:
       TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter ()
       : TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifference( std::move( TNetwork() ) )
       , betweennessAlgorithm_( networkConst_ )
       {}

       TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter ( TNetwork && network )
       : TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifference( network )
       , betweennessAlgorithm_( networkConst_ )
       {}

       TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter ( TNetwork const & network )
       : TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifference( network )
       , betweennessAlgorithm_( networkConst_ )
       {}

    protected:
        TGeneratorBasedBcDtpVangle betweennessAlgorithm_;
};

class TestGeneratorBasedBetweennessCentralityDtpSusceptanceNorm
        : public TestGeneratorBasedBetweennessCentralityGraph
{
    protected:
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

        TestGeneratorBasedBetweennessCentralityDtpSusceptanceNorm ()
        : TestGeneratorBasedBetweennessCentralityGraph( std::move( TNetwork() ) )
        {}

        TestGeneratorBasedBetweennessCentralityDtpSusceptanceNorm ( TNetwork && network )
        : TestGeneratorBasedBetweennessCentralityGraph( network )
        {}

        TestGeneratorBasedBetweennessCentralityDtpSusceptanceNorm ( TNetwork const & network )
        : TestGeneratorBasedBetweennessCentralityGraph( network )
        {}
};

class TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormEdgeCounter
        : public TestGeneratorBasedBetweennessCentralityDtpSusceptanceNorm
{
    protected:
        using TGeneratorBasedBcDtpBnorm = GeneratorBasedBetweennessCentrality < TNetwork
                                                                              , TFindPathAlgo
                                                                              , TMeasurementCollection
                                                                              , CentralityCounter::counterAtEdges >;

        TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormEdgeCounter ()
        : TestGeneratorBasedBetweennessCentralityDtpSusceptanceNorm( std::move( TNetwork() ) )
        , betweennessAlgorithm_( networkConst_ )
        {}

        TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormEdgeCounter ( TNetwork && network )
        : TestGeneratorBasedBetweennessCentralityDtpSusceptanceNorm( network )
        , betweennessAlgorithm_( networkConst_ )
        {}

        TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormEdgeCounter ( TNetwork const & network )
        : TestGeneratorBasedBetweennessCentralityDtpSusceptanceNorm( network )
        , betweennessAlgorithm_( networkConst_ )
        {}

    protected:
        TGeneratorBasedBcDtpBnorm betweennessAlgorithm_;
};

class TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormVertexCounter
        : public TestGeneratorBasedBetweennessCentralityDtpSusceptanceNorm
{
    protected:
        using TGeneratorBasedBcDtpBnorm = GeneratorBasedBetweennessCentrality < TNetwork
                                                                              , TFindPathAlgo
                                                                              , TMeasurementCollection
                                                                              , CentralityCounter::counterAtVertices >;

        TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormVertexCounter ()
        : TestGeneratorBasedBetweennessCentralityDtpSusceptanceNorm( std::move( TNetwork() ) )
        , betweennessAlgorithm_( networkConst_ )
        {}

        TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormVertexCounter ( TNetwork && network )
        : TestGeneratorBasedBetweennessCentralityDtpSusceptanceNorm( network )
        , betweennessAlgorithm_( networkConst_ )
        {}

        TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormVertexCounter ( TNetwork const & network )
        : TestGeneratorBasedBetweennessCentralityDtpSusceptanceNorm( network )
        , betweennessAlgorithm_( networkConst_ )
        {}

    protected:
        TGeneratorBasedBcDtpBnorm betweennessAlgorithm_;
};

class TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4aEdgeCounter
        : public TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormEdgeCounter
{
    protected:
        TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4aEdgeCounter ()
        : TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormEdgeCounter( std::move( TNetwork() ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4a_
                                    , TPowerGridIO::readIeeeCdfMatlab ) )
            {
                std::cerr << "Expected file " << TestCaseAcm2018MtsfFigure4a_ << " does not exist!";
                exit(1);
            }
        }

        virtual ~TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4aEdgeCounter(){}

        virtual void SetUp() override
        {
            betweennessAlgorithm_.Clear();
        }
};

class TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4aVertexCounter
        : public TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormVertexCounter
{
    protected:
        TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4aVertexCounter ()
        : TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormVertexCounter( std::move( TNetwork() ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4a_
                                    , TPowerGridIO::readIeeeCdfMatlab ) )
            {
                std::cerr << "Expected file " << TestCaseAcm2018MtsfFigure4a_ << " does not exist!";
                exit(1);
            }
        }

        virtual ~TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4aVertexCounter(){}

        virtual void SetUp() override
        {
            betweennessAlgorithm_.Clear();
        }
};

class TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4bEdgeCounter
        : public TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormEdgeCounter
{
    protected:
        TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4bEdgeCounter ()
        : TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormEdgeCounter( std::move( TNetwork() ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4b_
                                    , TPowerGridIO::readIeeeCdfMatlab ) )
            {
                std::cerr << "Expected file " << TestCaseAcm2018MtsfFigure4b_ << " does not exist!";
                exit(1);
            }
        }

        virtual ~TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4bEdgeCounter(){}

        virtual void SetUp() override
        {
            betweennessAlgorithm_.Clear();
        }
};

class TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4bVertexCounter
        : public TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormVertexCounter
{
    protected:
        TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4bVertexCounter ()
        : TestGeneratorBasedBetweennessCentralityDtpSusceptanceNormVertexCounter( std::move( TNetwork() ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4b_
                                    , TPowerGridIO::readIeeeCdfMatlab ) )
            {
                std::cerr << "Expected file " << TestCaseAcm2018MtsfFigure4b_ << " does not exist!";
                exit(1);
            }
        }

        virtual ~TestGeneratorBasedBcDtpBnormUsingAcm2018MtsfFigure4bVertexCounter(){}

        virtual void SetUp() override
        {
            betweennessAlgorithm_.Clear();
        }
};

class TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4aEdgeCounter
        : public TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter
{
    protected:
        TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4aEdgeCounter ()
        : TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter( std::move( TNetwork() ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4a_
                                    , TPowerGridIO::readIeeeCdfMatlab ) )
            {
                std::cerr << "Expected file " << TestCaseAcm2018MtsfFigure4a_ << " does not exist!";
                exit(1);
            }
        }

        virtual ~TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4aEdgeCounter(){}

        virtual void SetUp() override
        {
            betweennessAlgorithm_.Clear();
        }
};

class TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4aVertexCounter
        : public TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter
{
    protected:
        TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4aVertexCounter ()
        : TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter( std::move( TNetwork() ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4a_
                                    , TPowerGridIO::readIeeeCdfMatlab ) )
            {
                std::cerr << "Expected file " << TestCaseAcm2018MtsfFigure4a_ << " does not exist!";
                exit(1);
            }
        }

        virtual ~TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4aVertexCounter(){}

        virtual void SetUp() override
        {
            betweennessAlgorithm_.Clear();
        }
};

class TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4bEdgeCounter
        : public TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter
{
    protected:
        TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4bEdgeCounter ()
        : TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceEdgeCounter( std::move( TNetwork() ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4b_
                                    , TPowerGridIO::readIeeeCdfMatlab ) )
            {
                std::cerr << "Expected file " << TestCaseAcm2018MtsfFigure4b_ << " does not exist!";
                exit(1);
            }
        }

        virtual ~TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4bEdgeCounter(){}

        virtual void SetUp() override
        {
            betweennessAlgorithm_.Clear();
        }
};

class TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4bVertexCounter
        : public TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter
{
    protected:
        TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4bVertexCounter ()
        : TestGeneratorBasedBetweennessCentralityDtpVoltageAngleDifferenceVertexCounter( std::move( TNetwork() ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4b_
                                    , TPowerGridIO::readIeeeCdfMatlab ) )
            {
                std::cerr << "Expected file " << TestCaseAcm2018MtsfFigure4b_ << " does not exist!";
                exit(1);
            }
        }

        virtual ~TestGeneratorBasedBcDtpVangleUsingAcm2018MtsfFigure4bVertexCounter(){}

        virtual void SetUp() override
        {
            betweennessAlgorithm_.Clear();
        }
};

} // namespace egoa::test

#endif // EGOA__TESTS__ALGORITHMS__TEST_GENERATOR_BASED_BETWEENNESS_CENTRALITY_HPP

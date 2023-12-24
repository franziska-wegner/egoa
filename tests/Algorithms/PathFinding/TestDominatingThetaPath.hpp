/*
 * TestDominatingThetaPath.hpp
 *
 *  Created on: Feb 14, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__TESTS__ALGORITHMS__PATH_FINDING__TEST_DOMINATING_THETA_PATH_HPP
#define EGOA__TESTS__ALGORITHMS__PATH_FINDING__TEST_DOMINATING_THETA_PATH_HPP

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

namespace egoa::test {

/**
 * @brief      Class creating the initial simple set up
 */
class TestDominatingThetaPath : public ::testing::Test {
    protected:
        // Graph and network data structures
        using TVertexProperties = Vertices::ElectricalProperties<>;
        using TEdgeProperties   = Edges::ElectricalProperties;
        using TGraph            = StaticGraph<TVertexProperties, TEdgeProperties>;

        using TVertex        = TGraph::TVertex;
        using TEdge          = TGraph::TEdge;
        // Label specific data structures
        using TLabel         = SusceptanceNormLabel<TEdge>;
        // Queues
        using TQueue         = BinaryHeap< TLabel >;
        using TMQTheta       = MappingBinaryHeap< typename TGraph::TVertexId, TLabel >;
        // Bucket
        using TLabelSet      = Bucket<TQueue>;

        // Dominating theta path using susceptance norm only
        using TDtp           = DominatingThetaPath < TGraph
                                                   , TLabel
                                                   , TMQTheta
                                                   , TLabelSet
                                                   , DominationCriterion::strict >;
    protected:
        TestDominatingThetaPath ()
        : graph_()
        , graphConst_( graph_ )
        , dtp_( graphConst_ )
        {}

        TestDominatingThetaPath ( TGraph && graph )
        : graph_()
        , graphConst_( graph_ )
        , dtp_( graphConst_ )
        {}

        TestDominatingThetaPath ( TGraph const & graph )
        : graph_()
        , graphConst_( graph_ )
        , dtp_( graphConst_ )
        {}

    protected:
        TGraph          graph_;
        TGraph const &  graphConst_;
        TDtp            dtp_;
};

/**
 * @brief      Fixture for testing the DTP on an empty graph
 */
class TestDTPPowerGridSpecific : public TestDominatingThetaPath {
    protected:
        // Graph and network data structures
        using TPowerGrid     = PowerGrid<TGraph>;
        // IO
        using TPowerGridIO   = PowerGridIO<TGraph>;
        // Power Grid DTP specific data structures including voltage angles
        using TLabelTheta    = VoltageAngleDifferenceLabel<TGraph::TEdge>;
        // Queues
        using TQueueTheta    = BinaryHeap<TLabelTheta>;
        using TMQTheta       = MappingBinaryHeap<typename TGraph::TVertexId, TLabelTheta >;
        // Bucket
        using TLabelSetTheta = Bucket< TQueueTheta >;
        
        // Dominating theta path using susceptance norm only
        using TDtpTheta      = DominatingThetaPath < TGraph
                                                   , TLabelTheta
                                                   , TMQTheta
                                                   , TLabelSetTheta
                                                   , DominationCriterion::strict >;
    protected:
        TestDTPPowerGridSpecific ()
        : TestDominatingThetaPath()
        , dtpTheta_( graphConst_ )
        {}

        TestDTPPowerGridSpecific ( TGraph && graph )
        : TestDominatingThetaPath ( graph )
        , dtpTheta_( graphConst_ )
        {}

        TestDTPPowerGridSpecific ( TGraph const & graph )
        : TestDominatingThetaPath ( graph )
        , dtpTheta_( graphConst_ )
        {}

        inline void TestEdgeValues ( Types::edgeId edgeId
                                   , Types::edgeId identifier
                                   , Types::real   thermalLineLimit
                                   , Types::real   dcSusceptance
                                   , Types::real   acSusceptance
                                   , Types::real   dcConductance
                                   , Types::real   acConductance )
        {
            EXPECT_NE ( edgeId, Const::NONE );
            EXPECT_EQ ( edgeId, identifier );
            EXPECT_EQ ( graph_.EdgeAt( edgeId ).Properties().ThermalLimit(), thermalLineLimit );
            EXPECT_EQ ( graph_.EdgeAt( edgeId ).Properties().Susceptance<Edges::CarrierDifferentiationType::DC>(), dcSusceptance );
            EXPECT_EQ ( graph_.EdgeAt( edgeId ).Properties().Susceptance<Edges::CarrierDifferentiationType::AC>(), acSusceptance );
            EXPECT_EQ ( graph_.EdgeAt( edgeId ).Properties().Conductance<Edges::CarrierDifferentiationType::DC>(), dcConductance );
            EXPECT_EQ ( graph_.EdgeAt( edgeId ).Properties().Conductance<Edges::CarrierDifferentiationType::AC>(), acConductance );   
        }
    protected:
        TPowerGrid            network_;
        TPowerGrid    const & constNetwork_ = network_;

        Types::string   const TestCaseAcm2018MtsfFigure4a_ = "../../framework/tests/Data/PowerGrids/ieee_2018_acm_eEnergy_MTSF_Figure4a.m";
        Types::string   const TestCaseAcm2018MtsfFigure4b_ = "../../framework/tests/Data/PowerGrids/ieee_2018_acm_eEnergy_MTSF_Figure4b.m";
        Types::vertexId const source_ = 0;
        TDtpTheta             dtpTheta_;
};

/**
 * @brief      Fixture for testing the DTP after initialization without a source
 */
class TestDTPEmptyGraph : public TestDominatingThetaPath {
    protected:
        TestDTPEmptyGraph () 
        : TestDominatingThetaPath ( std::move( TGraph( "Empty Test Graph" ) ) )
        {}

        virtual ~TestDTPEmptyGraph(){}

        virtual void SetUp() override {
        }
};

using TestDTPEmptyGraphDeathTest          = TestDTPEmptyGraph;
using TestDTPEmptyGraphExceptionHandling  = TestDTPEmptyGraph;

/**
 * @brief      Fixtures to test DTP using Figure 4a
 */
class TestDTPUsingAcm2018MtsfFigure4a : public TestDTPPowerGridSpecific {
    protected:
        TestDTPUsingAcm2018MtsfFigure4a ()
        : TestDTPPowerGridSpecific ( std::move( TGraph( "Acm2018MtsfFigure4a" ) ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4a_
                                    , TPowerGridIO::readIeeeCdfMatlab ) ) 
            {
                std::cerr << "Expected file " << TestCaseAcm2018MtsfFigure4a_ << " does not exist!";
                exit(1);
            }
            graph_ = network_.Graph();
            // std::cout << network_ << std::endl;
        }

        virtual ~TestDTPUsingAcm2018MtsfFigure4a(){}

        virtual void SetUp() override {
            dtp_.Clear();
            dtpTheta_.Clear();
        }
};

using TestDTPUsingAcm2018MtsfFigure4aDeathTest         = TestDTPUsingAcm2018MtsfFigure4a;
using TestDTPUsingAcm2018MtsfFigure4aExceptionHandling = TestDTPUsingAcm2018MtsfFigure4a;

/**
 * @brief      Fixtures to test DTP using Figure 4b
 */
class TestDTPUsingAcm2018MtsfFigure4b : public TestDTPPowerGridSpecific {
    protected:
        TestDTPUsingAcm2018MtsfFigure4b ()
        : TestDTPPowerGridSpecific ( std::move( TGraph( "Empty Test Graph" ) ) )
        {
            if (!TPowerGridIO::read ( network_
                                    , TestCaseAcm2018MtsfFigure4b_
                                    , TPowerGridIO::readIeeeCdfMatlab ) ) 
            {
                std::cerr << "Expected file " << TestCaseAcm2018MtsfFigure4b_ << " does not exist!";
                exit(1);
            }
            graph_ = network_.Graph();
            // std::cout << network_ << std::endl;
        }

        virtual ~TestDTPUsingAcm2018MtsfFigure4b(){}

        virtual void SetUp() override {
            dtp_.Clear();
            dtpTheta_.Clear();
        }
};

using TestDTPUsingAcm2018MtsfFigure4bDeathTest          = TestDTPUsingAcm2018MtsfFigure4b;
using TestDTPUsingAcm2018MtsfFigure4bExceptionHandling  = TestDTPUsingAcm2018MtsfFigure4b;

} // namespace egoa::test

#endif // EGOA__TESTS__ALGORITHMS__PATH_FINDING__TEST_DOMINATING_THETA_PATH_HPP

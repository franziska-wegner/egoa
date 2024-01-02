/*
 * TestPowerGrid.hpp
 *
 *  Created on: Mar 02, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__TESTS__DATA_STRUCTURES__GRAPHS__TEST_POWER_GRID_HPP
#define EGOA__TESTS__DATA_STRUCTURES__GRAPHS__TEST_POWER_GRID_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Exceptions/Assertions.hpp"

#include "Helper/TestHelper.hpp"

#include "IO/PowerGridIO.hpp"
#include "IO/Parser/IeeeCdfMatlabParser.hpp"

#include "DataStructures/Networks/PowerGrid.hpp"

#include "DataStructures/Graphs/StaticGraph.hpp"
#include "DataStructures/Graphs/DynamicGraph.hpp"

#include "DataStructures/Graphs/Edges/Edge.hpp"
#include "DataStructures/Graphs/Edges/ElectricalProperties.hpp"

#include "DataStructures/Graphs/Vertices/Vertex.hpp"
#include "DataStructures/Graphs/Vertices/ElectricalProperties.hpp"
#include "DataStructures/Graphs/Vertices/LoadProperties.hpp"

#include "DataStructures/Iterators/PowerGridIterators.hpp"

namespace egoa::test {

/**
 * @brief Fixture for testing power grids
 */
class TestPowerGrid : public ::testing::Test {
    protected:
        // Graph specific types
        // Vertices
        using TVertex           = Vertices::Vertex<Vertices::ElectricalProperties<>>;
        using TVertexProperties = typename TVertex::TProperties;
        // Edges
        using TEdge             = Edges::Edge<Edges::ElectricalProperties>;
        using TEdgeProperties   = typename TEdge::TProperties;
        using TGraph            = StaticGraph < TVertexProperties
                                              , TEdgeProperties >;
        // Network specific types
        using TGeneratorProperties  = Vertices::GeneratorProperties<>;
        using TLoadProperties       = Vertices::LoadProperties<Vertices::IeeeBusType>;
        using TNetwork              = PowerGrid<TGraph>;

        // IO
        using TPowerGridIO          = PowerGridIO<TGraph>;
        using TIeeeCdfMatlabParser  = IeeeCdfMatlabParser<TGraph>;

        using TBound    = Bound<>;

    protected:
        TestPowerGrid ()
        : network_(){}

        TestPowerGrid ( TNetwork & network )
        : network_( network ){}

        ~TestPowerGrid () {}

        static void CreateExampleGeneratorProperties ( TGeneratorProperties & generatorProperties )
        {
            generatorProperties.Name()                           = "Test Generator Properties 0";
            generatorProperties.Type()                           = Vertices::IeeeBusType::generator;
            generatorProperties.RealPower()                      = 9.9;
            generatorProperties.ReactivePower()                  = 9.9;

            generatorProperties.ReactivePowerBound().Maximum()   = 9.9;
            generatorProperties.ReactivePowerBound().Minimum()   = 0.1;

            generatorProperties.VoltageMagnitude()               = 42;
            generatorProperties.NominalPower()                   = 1;
            generatorProperties.Status()                         = Vertices::BusStatus::active;

            generatorProperties.RealPowerBound().Maximum()       = 9.9;
            generatorProperties.RealPowerBound().Minimum()       = 0.1;

            generatorProperties.Pc1()                            = 23;
            generatorProperties.Pc2()                            = 27;

            generatorProperties.Qc1Bound().Maximum()             = 11;
            generatorProperties.Qc1Bound().Minimum()             = 10;

            generatorProperties.Qc2Bound().Maximum()             = 25;
            generatorProperties.Qc2Bound().Minimum()             = 21;

            generatorProperties.RampAgc()                        = 3;
            generatorProperties.Ramp10()                         = 10;
            generatorProperties.Ramp30()                         = 30;
            generatorProperties.RampQ()                          = 89;
            generatorProperties.Apf()                            = 69;
        }

        static void CreateExampleLoadProperties ( TLoadProperties & loadProperties )
        {
            loadProperties.Name()                           = "Test Load Properties 0";
            loadProperties.Type()                           = Vertices::IeeeBusType::load;
            loadProperties.RealPowerLoad()                  = 8.8;
            loadProperties.RealPowerLoadBound().Maximum()   = 8.9;
            loadProperties.RealPowerLoadBound().Minimum()   = 4.2;

            loadProperties.ReactivePowerLoad()                  = 7.7;
            loadProperties.ReactivePowerLoadBound().Maximum()   = 8.1;
            loadProperties.ReactivePowerLoadBound().Minimum()   = 0.1;
        }

        static void CheckExampleGeneratorProperties ( TGeneratorProperties const & generatorProperties )
        {
            EXPECT_EQ ( "Test Generator Properties 0", generatorProperties.Name() );
            EXPECT_EQ ( Vertices::IeeeBusType::generator, generatorProperties.Type() );
            EXPECT_EQ ( 9.9, generatorProperties.RealPower() );
            EXPECT_EQ ( 9.9, generatorProperties.ReactivePower() );
            EXPECT_EQ ( 9.9, generatorProperties.ReactivePowerBound().Maximum() );
            EXPECT_EQ ( 0.1, generatorProperties.ReactivePowerBound().Minimum() );
            EXPECT_EQ ( 42,  generatorProperties.VoltageMagnitude() );
            EXPECT_EQ ( 1,   generatorProperties.NominalPower() );
            EXPECT_EQ ( Vertices::BusStatus::active, generatorProperties.Status() );
            EXPECT_EQ ( 9.9, generatorProperties.RealPowerBound().Maximum() );
            EXPECT_EQ ( 0.1, generatorProperties.RealPowerBound().Minimum() );
            EXPECT_EQ ( 23,  generatorProperties.Pc1() );
            EXPECT_EQ ( 27,  generatorProperties.Pc2() );
            EXPECT_EQ ( 10,  generatorProperties.Qc1Bound().Minimum() );
            EXPECT_EQ ( 11,  generatorProperties.Qc1Bound().Maximum() );
            EXPECT_EQ ( 21,  generatorProperties.Qc2Bound().Minimum() );
            EXPECT_EQ ( 25,  generatorProperties.Qc2Bound().Maximum() );
            EXPECT_EQ ( 3,   generatorProperties.RampAgc() );
            EXPECT_EQ ( 10,  generatorProperties.Ramp10() );
            EXPECT_EQ ( 30,  generatorProperties.Ramp30() );
            EXPECT_EQ ( 89,  generatorProperties.RampQ() );
            EXPECT_EQ ( 69,  generatorProperties.Apf() );
        }

        static void CheckExampleLoadProperties ( TLoadProperties const & loadProperties )
        {
            EXPECT_EQ ( "Test Load Properties 0",    loadProperties.Name() );
            EXPECT_EQ ( Vertices::IeeeBusType::load, loadProperties.Type() );

            EXPECT_EQ ( 8.8, loadProperties.RealPowerLoad() );
            EXPECT_EQ ( 8.9, loadProperties.RealPowerLoadBound().Maximum() );
            EXPECT_EQ ( 4.2, loadProperties.RealPowerLoadBound().Minimum() );

            EXPECT_EQ ( 7.7, loadProperties.ReactivePowerLoad() );
            EXPECT_EQ ( 8.1, loadProperties.ReactivePowerLoadBound().Maximum() );
            EXPECT_EQ ( 0.1, loadProperties.ReactivePowerLoadBound().Minimum() );
        }

    protected:
        TNetwork         network_;
        TNetwork const & networkConst_ = network_;
};

/**
 * Fixture for testing a network without vertices and edges.
 */
using TestNetworkEmpty          = TestPowerGrid;

/**
 * Fixture for death tests on an empty graph.
 */
using TestNetworkEmptyDeathTest = TestNetworkEmpty;

/**
 * @brief Fixture for testing the power grids using the Acm2018MtsfFigure4a
 */
class TestPowerGridAcm2018MtsfFigure4a : public TestPowerGrid {
    protected:
        TestPowerGridAcm2018MtsfFigure4a ()
        : TestPowerGrid ()
        {}

        virtual ~TestPowerGridAcm2018MtsfFigure4a () {}

        inline void GeneratorComplyInitialValues ( TGeneratorProperties const & generatorProperties ) const
        {
            EXPECT_EQ ( true, generatorProperties.IsActive()      );
            EXPECT_EQ ( Vertices::BusStatus::active, generatorProperties.Status()  );

            EXPECT_EQ ( 1.234, generatorProperties.RealPower()    );
            EXPECT_EQ ( 1.111, generatorProperties.ReactivePower()  );

            EXPECT_EQ ( 0.0, generatorProperties.RealPowerBound().Minimum()      );
            EXPECT_EQ ( 8.0, generatorProperties.RealPowerBound().Maximum()      );

            EXPECT_EQ ( 0.0, generatorProperties.ReactivePowerBound().Minimum()  );
            EXPECT_EQ ( 2.0, generatorProperties.ReactivePowerBound().Maximum()  );

            EXPECT_EQ ( 1.10, generatorProperties.VoltageMagnitude() );
        }

        virtual void SetUp () override
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
        }

        Types::string   const   TestCaseAcm2018MtsfFigure4a_ = "../../tests/Data/PowerGrids/ieee_2018_acm_eEnergy_MTSF_Figure4a.m";
};

/**
 * Fixture for death tests on an Acm2018MtsfFigure4a power grid.
 */
using TestPowerGridAcm2018MtsfFigure4aDeathTest = TestPowerGridAcm2018MtsfFigure4a;

/**
 * @brief Fixture for testing the power grids using the Acm2018MtsfFigure4b
 */
class TestPowerGridAcm2018MtsfFigure4b : public TestPowerGrid {
    protected:
        TestPowerGridAcm2018MtsfFigure4b ()
        : TestPowerGrid ()
        {}

        virtual ~TestPowerGridAcm2018MtsfFigure4b () {}

        inline void GeneratorComplyInitialValues ( TGeneratorProperties const & generatorProperties ) const
        {
            EXPECT_EQ ( true, generatorProperties.IsActive()      );
            EXPECT_EQ ( Vertices::BusStatus::active, generatorProperties.Status()  );

            EXPECT_EQ ( 0.0, generatorProperties.RealPower()      );
            EXPECT_EQ ( 0.0, generatorProperties.ReactivePower()  );

            EXPECT_EQ ( 0.0, generatorProperties.RealPowerBound().Minimum()      );
            EXPECT_EQ ( 5.0, generatorProperties.RealPowerBound().Maximum()      );

            EXPECT_EQ ( 0.0, generatorProperties.ReactivePowerBound().Minimum()  );
            EXPECT_EQ ( 0.0, generatorProperties.ReactivePowerBound().Maximum()  );

            EXPECT_EQ ( 1.10, generatorProperties.VoltageMagnitude() );
        }

        virtual void SetUp () override
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
        }

        Types::string   const   TestCaseAcm2018MtsfFigure4b_ = "../../tests/Data/PowerGrids/ieee_2018_acm_eEnergy_MTSF_Figure4b.m";
};

/**
 * Fixture for death tests on an Acm2018MtsfFigure4b power grid.
 */
using TestPowerGridAcm2018MtsfFigure4bDeathTest = TestPowerGridAcm2018MtsfFigure4b;

/**
 * @brief Fixture for testing the power grids using the test PyPSA example.
 */
class TestPowerGridPyPsaExample : public TestPowerGrid {
    protected:
        TestPowerGridPyPsaExample ()
        : TestPowerGrid ()
        {}

        virtual ~TestPowerGridPyPsaExample () {}

        inline void GeneratorComplyInitialValues ( TGeneratorProperties const & generatorProperties ) const
        {
            EXPECT_EQ ( true, generatorProperties.IsActive()      );
            EXPECT_EQ ( Vertices::BusStatus::active, generatorProperties.Status()  );

            EXPECT_EQ ( 0.0, generatorProperties.RealPower()      );
            EXPECT_EQ ( 0.0, generatorProperties.ReactivePower()  );

            EXPECT_EQ ( 0, generatorProperties.RealPowerBound().Minimum()                      );
            EXPECT_EQ ( Const::REAL_INFTY, generatorProperties.RealPowerBound().Maximum()      );

            EXPECT_EQ ( 0.0, generatorProperties.ReactivePowerBound().Minimum()  );
            EXPECT_EQ ( Const::REAL_INFTY, generatorProperties.ReactivePowerBound().Maximum()  );

            EXPECT_EQ ( 1, generatorProperties.VoltageMagnitude() );
        }

        virtual void SetUp () override
        {
            if ( ! egoa::PowerGridIO<TGraph>::read( network_
                                                  , graph_
                                                  , TestCaseSmallExample_
                                                  , TPowerGridIO::ReadPyPsa ) )
            {
                std::cerr   << "Expected file "
                            << TestCaseSmallExample_
                            << " does not exist!";
                exit(1);
            }
        }

        Types::string const TestCaseSmallExample_ = "../../tests/Data/PowerGrids/PyPSAExample";

    protected:
        TGraph         graph_;
        TGraph const & graphConst_ = graph_;
};

/**
 * Fixture for death tests on an Power Grid PyPsa Example.
 */
using TestPowerGridPyPsaExampleDeathTest = TestPowerGridPyPsaExample;


} // namespace egoa::test

#endif // EGOA___TESTS___DATA_STRUCTURES___GRAPHS__TEST_POWER_GRID_HPP

/*
 * TestPyPsaParser.hpp
 *
 *  Created on: Jan 29, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA___TESTS___IO___TEST_PY_PSA_PARSER_HPP
#define EGOA___TESTS___IO___TEST_PY_PSA_PARSER_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "IO/PowerGridIO.hpp"

#include "DataStructures/Networks/PowerGrid.hpp"

#include "DataStructures/Graphs/StaticGraph.hpp"
#include "DataStructures/Graphs/DynamicGraph.hpp"

namespace egoa::test {
/**
* @brief Fixture for testing class PyPsaParser
*/
class TestPyPsaParser : public ::testing::Test {
    protected:
        // Vertices
        using TVertex           = Vertices::Vertex<Vertices::ElectricalProperties<>>;
        using TVertexType       = typename TVertex::TProperties::TVertexType;
        using TVertexProperties = typename TVertex::TProperties;
        // Edges
        using TEdge             = Edges::Edge<Edges::ElectricalProperties>;
        using TEdgeProperties   = typename TEdge::TProperties;
        // Network specific types
        using TGraph            = StaticGraph< Vertices::ElectricalProperties<>
                                             , Edges::ElectricalProperties>;
        // Network specific types
        using TGeneratorProperties  = Vertices::GeneratorProperties<>;
        using TLoadProperties   = Vertices::LoadProperties<Vertices::IeeeBusType>;
        using TNetwork          = PowerGrid<TGraph>;
        // IO
        using TPowerGridIO      = PowerGridIO<TGraph>;

    protected:
        // You can do set-up work for each test here.
        TestPyPsaParser()
        : network_(){}

        TestPyPsaParser ( TNetwork & network )
        : network_( network ){}

        // You can do clean-up work that doesn't throw exceptions here.
        virtual ~TestPyPsaParser(){}

    protected:
        TGraph           graph_;
        TGraph   const & graphConst_   = graph_;
        TNetwork         network_;
        TNetwork const & networkConst_ = network_;
};

/**
 * @brief Fixture for testing the PyPsa parser for a simple example
 */
class TestPyPsaExample : public TestPyPsaParser {
    protected:
        TestPyPsaExample ()
        : TestPyPsaParser () 
        {}

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

        Types::string   const   TestCaseSmallExample_ = "../../framework/tests/Data/PowerGrids/PyPsaExample";
};

/**
 * @brief Fixture for testing the PyPsa parser for inconsistency in generators
 */
class PyPSAExampleInconsistencyGeneratorsDeathTest : public TestPyPsaParser {
    protected:
        PyPSAExampleInconsistencyGeneratorsDeathTest ()
        : TestPyPsaParser () 
        {}

        Types::string   const   TestCaseSmallExample_ = "../../framework/tests/Data/PowerGrids/PyPSAExampleDeathTestInconsistencyGenerators";
};

/**
 * @brief Fixture for testing the PyPsa parser for inconsistency in the number of timestamps
 */
class PyPSAExampleInconsistencyInTimestampLengthDeathTest : public TestPyPsaParser {
    protected:
        PyPSAExampleInconsistencyInTimestampLengthDeathTest ()
        : TestPyPsaParser () 
        {}

        Types::string   const   TestCaseSmallExample_ = "../../framework/tests/Data/PowerGrids/PyPSAExampleDeathTestInconsistencyInTimestampLength";
};

/**
 * @brief Fixture for testing the PyPsa parser for duplicated generator assert
 */
class PyPSAExampleDuplicatedGeneratorsDeathTest : public TestPyPsaParser {
    protected:
        PyPSAExampleDuplicatedGeneratorsDeathTest ()
        : TestPyPsaParser () 
        {}

        Types::string   const   TestCaseSmallExample_ = "../../framework/tests/Data/PowerGrids/PyPSAExampleDeathTestDuplicatedGeneratorNames";
};

/**
 * @brief Fixture for testing the power grids using the PyPSA_PyPSA_data_2018_11_20__elec_s1024_AT
 */
class PyPSA_PyPSA_data_2018_11_20__elec_s1024_AT : public TestPyPsaParser {
    protected:
        PyPSA_PyPSA_data_2018_11_20__elec_s1024_AT ()
        : TestPyPsaParser () 
        {}

        Types::string   const   TestCaseSmallExample_ = "../../framework/data/PowerGrids/PyPSA/pypsa-iti-collaboration/elec_s1024_AT";;
};

} // namespace egoa::test

#endif // EGOA___TESTS___IO___TEST_PY_PSA_PARSER_HPP

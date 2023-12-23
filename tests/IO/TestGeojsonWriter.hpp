/*
 * TestGeojsonWriter.hpp
 *
 *  Created on: Nov 04, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA___TESTS___IO___TEST_GEO_JSON_WRITER_HPP
#define EGOA___TESTS___IO___TEST_GEO_JSON_WRITER_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "IO/PowerGridIO.hpp"

#include "DataStructures/Networks/PowerGrid.hpp"

#include "DataStructures/Graphs/StaticGraph.hpp"
#include "DataStructures/Graphs/DynamicGraph.hpp"

namespace egoa::test {

class TestGeojsonWriter : public ::testing::Test {
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
        TestGeojsonWriter()
        : network_(){}

        TestGeojsonWriter( TNetwork & network )
        : network_(){}

        // You can do clean-up work that doesn't throw exceptions here.
        virtual ~TestGeojsonWriter(){}

    protected:
        TGraph           graph_;
        TGraph   const & graphConst_   = graph_;
        TNetwork         network_;
        TNetwork const & networkConst_ = network_;
};

class TestGeojsonExample : public TestGeojsonWriter {
    protected:
        TestGeojsonExample ()
        : TestGeojsonWriter ()
        {}

        virtual void SetUp () override
        {
            if ( ! egoa::PowerGridIO<TGraph>::read( network_
                                                  , graph_
                                                  , TestCaseSmallExampleInput_
                                                  , TPowerGridIO::ReadPyPsa ) )
            {
                std::cerr   << "Expected file " 
                            << TestCaseSmallExampleInput_ 
                            << " does not exist!";
                ASSERT_TRUE(false);
            }
        }

        Types::string const TestCaseSmallExampleInput_          = "../../framework/tests/Data/PowerGrids/PyPsaExampleGeoJsonWriter";
        Types::string const TestCaseSmallExampleExpectedOutput_ = "../../framework/tests/Data/Output/PyPsaExampleJsonWriterExpectedOutput.json";
        Types::string const TestCaseSmallExampleOutputFile_     = "../../framework/tests/Data/Output/PyPsaExampleJsonWriter.json";
};


} // namespace egoa::test

#endif // EGOA___TESTS___IO___TEST_GEO_JSON_WRITER_HPP

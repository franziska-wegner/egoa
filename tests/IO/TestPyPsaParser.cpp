/*
 * TestPyPsaParser.cpp
 *
 *  Created on: Jan 29, 2019
 *      Author: Franziska Wegner
 */

#include "TestPyPsaParser.hpp"
#include "IO/Parser/PyPsaParser.hpp"

#include "Auxiliary/Types.hpp"
#include "Helper/TestHelper.hpp"

namespace egoa::test {

TEST_F ( TestPyPsaExample, CompareNetworkGlobalProperties )
{
    EXPECT_EQ(0  , network_.Graph().MinDegree() );
    EXPECT_EQ(3  , network_.Graph().MaxDegree() );
    EXPECT_EQ(5  , network_.Graph().NumberOfEdges() );
    EXPECT_EQ(10 , network_.Graph().NumberOfVertices() );
    // std::cout << network_ << std::endl;
    // std::cout << graph_   << std::endl << std::endl;
    // network_.OutputGeneratorSnaps();
    // network_.OutputLoadSnaps();
}

TEST_F ( TestPyPsaExample, CompareVerticesPropertiesWithBusesData )
{
    Types::index x =  1;
    Types::index y = 11;

    network_.Graph().template for_all_vertices<ExecutionPolicy::sequential>(
        [&x,&y]( TVertex const & vertex )
    {
        EXPECT_EQ(380.0         , vertex.Properties().NominalVoltage() );
        EXPECT_EQ(x             , vertex.Properties().X() );
        EXPECT_EQ(y             , vertex.Properties().Y() );
        EXPECT_EQ("TEST EXAMPLE", vertex.Properties().Country() );
        ++x;
        ++y;

        // default
        EXPECT_EQ(0                          , vertex.Properties().ShuntSusceptance() );
        EXPECT_EQ(0                          , vertex.Properties().ShuntConductance() );
        EXPECT_EQ(1                          , vertex.Properties().VoltageMagnitude() );
        EXPECT_EQ(0                          , vertex.Properties().VoltageAngle() );
        EXPECT_EQ(0                          , vertex.Properties().MinimumVoltage() );
        EXPECT_EQ(Const::REAL_INFTY          , vertex.Properties().MaximumVoltage() );
        EXPECT_EQ(0                          , vertex.Properties().Area() );
        EXPECT_EQ(0                          , vertex.Properties().Zone() );
        EXPECT_EQ(Vertices::ControlType::PQ  , vertex.Properties().Control() );
        EXPECT_EQ(Vertices::EnergyCarrier::AC, vertex.Properties().Carrier() );
        EXPECT_EQ(true                       , vertex.Properties().IsActive() );
        EXPECT_EQ(Vertices::BusStatus::active, vertex.Properties().Status() );

    });
}

TEST_F ( TestPyPsaExample, CompareVerticesPropertiesWithLinesData )
{
    Types::index x =  1;

    network_.Graph().template for_all_edges<ExecutionPolicy::sequential>(
        [&x]( TEdge const & edge )
    {
        EXPECT_EQ(x                 , Types::String2integer(edge.Properties().Name()) );

        // default
        EXPECT_EQ(true              , edge.Properties().Status() );

        EXPECT_EQ(20                , edge.Properties().Resistance() );
        EXPECT_EQ(10                , edge.Properties().Reactance() );

        // default
        EXPECT_EQ( 0                , edge.Properties().Conductance<Edges::CarrierDifferentiationType::DC>() );
        EXPECT_EQ( 0.04             , edge.Properties().Conductance<Edges::CarrierDifferentiationType::AC>() );
        EXPECT_EQ(-0.1              , edge.Properties().Susceptance<Edges::CarrierDifferentiationType::DC>() );
        EXPECT_EQ(-0.02             , edge.Properties().Susceptance<Edges::CarrierDifferentiationType::AC>() );
        EXPECT_EQ(0.7               , edge.Properties().Weight() );
        EXPECT_EQ(0                 , edge.Properties().Charge() );
        EXPECT_EQ(0                 , edge.Properties().ThermalLimitB() );
        EXPECT_EQ(0                 , edge.Properties().ThermalLimitC() );
        EXPECT_EQ(1                 , edge.Properties().TapRatio() );
        EXPECT_EQ(0                 , edge.Properties().AngleShift() );
        EXPECT_EQ(0                 , edge.Properties().TapRatioCosThetaShift() );
        EXPECT_EQ(0                 , edge.Properties().TapRatioSinThetaShift() );
        EXPECT_EQ(-Const::REAL_INFTY, edge.Properties().ThetaBound().Minimum() );
        EXPECT_EQ( Const::REAL_INFTY, edge.Properties().ThetaBound().Maximum() );
        EXPECT_EQ(0                 , edge.Properties().NominalApparentPowerExtendable() );
        EXPECT_EQ(0                 , edge.Properties().TerrainFactor() );


        EXPECT_EQ(Edges::ElectricalEdgeType::standard, edge.Properties().Type() );
        EXPECT_EQ((x+1)*1000     , edge.Properties().CapitalCost() );
        EXPECT_EQ(100            , edge.Properties().Length() );
        EXPECT_EQ(x              , edge.Properties().NumberOfParallelLines() );
        EXPECT_EQ(0.7            , edge.Properties().ThermalLimit() );
        EXPECT_EQ ( ceil ( (   ( x*1.0 + 2 ) * 1000 / ( x * 1.0 ) ) * 1000 / 1000 )
                  , ceil ( edge.Properties().NominalApparentPower() * 1000 / 1000 ) );
        EXPECT_EQ(380            , edge.Properties().NominalVoltage() );
        EXPECT_EQ(4000           , edge.Properties().NominalApparentPowerBound().Minimum() );
        EXPECT_EQ(8000           , edge.Properties().NominalApparentPowerBound().Maximum() );
        ++x;
    });
}

TEST_F ( TestPyPsaExample, CompareGeneratorsPropertiesWithGeneratorsData )
{
    std::vector<Vertices::GeneratorType> generatorTypes { Vertices::GeneratorType::onwind
                                                        , Vertices::GeneratorType::solar };
    Types::count counter = 0;

    network_.template for_all_generators<ExecutionPolicy::sequential>(
        [&counter,&generatorTypes]( TGeneratorProperties const & generator )
    {
        // EXPECT_EQ(0                        , generator.Name() );
        EXPECT_EQ( (counter+2)*100000                , generator.CapitalCost() );
        EXPECT_EQ(generatorTypes[counter%2]         , generator.GeneratorType() );
        EXPECT_EQ(1.0                               , generator.Efficiency() );
        EXPECT_EQ(15.0                              , generator.MarginalCost() );
        EXPECT_EQ(100.0                             , generator.NominalPower() );
        EXPECT_EQ(true                              , generator.IsExtendable() );
        if ( counter != 0)
            EXPECT_EQ(1000.0                            , generator.NominalRealPowerBound().Maximum() );
        else
            EXPECT_EQ(Const::REAL_INFTY                 , generator.NominalRealPowerBound().Maximum() );

        EXPECT_EQ(TVertexType::generator            , generator.Type() );
        EXPECT_EQ(0                                 , generator.X() );
        EXPECT_EQ(0                                 , generator.Y() );
        EXPECT_EQ(1                                 , generator.VoltageMagnitude() );
        EXPECT_EQ(0                                 , generator.NominalRealPowerBound().Minimum() );
        EXPECT_EQ(Vertices::PowerSign::positive     , generator.PowerSign() );
        EXPECT_EQ(0                                 , generator.RealPower() );
        EXPECT_EQ(0                                 , generator.RealPowerBound().Minimum() );
        EXPECT_EQ(0                                 , generator.Pc1() );
        EXPECT_EQ(0                                 , generator.Pc2() );
        EXPECT_EQ(0                                 , generator.ReactivePower() );
        EXPECT_EQ(0                                 , generator.ReactivePowerBound().Minimum() );
        EXPECT_EQ(Const::REAL_INFTY                 , generator.ReactivePowerBound().Maximum() );
        EXPECT_EQ(0                                 , generator.Qc1Bound().Minimum() );
        EXPECT_EQ(0                                 , generator.Qc1Bound().Maximum() );
        EXPECT_EQ(Vertices::BusStatus::active       , generator.Status() );
        EXPECT_EQ(false                             , generator.Committable() );
        EXPECT_EQ(Vertices::ControlType::PQ         , generator.Control() );
        EXPECT_EQ(0.0                               , generator.StartUpCost() );
        EXPECT_EQ(0.0                               , generator.ShutDownCost() );
        EXPECT_EQ(0.0                               , generator.MinimumUpTime() );
        EXPECT_EQ(0.0                               , generator.MinimumDownTime() );
        EXPECT_EQ(0.0                               , generator.RampAgc() );
        EXPECT_EQ(0.0                               , generator.Ramp10() );
        EXPECT_EQ(0.0                               , generator.Ramp30() );
        EXPECT_EQ(0.0                               , generator.Apf() );
        EXPECT_EQ(Const::REAL_INFTY                 , generator.RampLimitUp() );
        EXPECT_EQ(Const::REAL_INFTY                 , generator.RampLimitDown() );
        EXPECT_EQ(1.0                               , generator.RampLimitStartUp() );
        EXPECT_EQ(1.0                               , generator.RampLimitShutDown() );
        ++counter;
    });
}

TEST_F ( TestPyPsaExample, CheckGeneratorRealPowerSnapshots )
{
    Types::index generatorId = 1;
    Types::index snapId      = 0;
    network_.template for_all_real_power_generator_snapshots<ExecutionPolicy::sequential>(
        [&generatorId, &snapId](Types::index snapshotId, Types::generatorSnapshot snapshot)
        {
            EXPECT_EQ ( generatorId*100 + (snapId%10)*10, snapshot);
            EXPECT_EQ ( (snapId%10),                      snapshotId);
            ++snapId;
            if ( 0 == (snapId%10) ) ++generatorId;
        }
    );

    generatorId = 1;
    snapId      = 0;
    network_.template for_all_generators<ExecutionPolicy::sequential>(
        [this,&generatorId, &snapId](TGeneratorProperties const & generatorProperties)
        {
            this->network_.template for_all_real_power_generator_snapshots_of<ExecutionPolicy::sequential>( generatorId-1,
                [&generatorId, &snapId](Types::index snapshotId, Types::generatorSnapshot snapshot) {
                    EXPECT_EQ ( generatorId*100 + (snapId%10)*10, snapshot);
                    EXPECT_EQ ( (snapId%10),                      snapshotId);
                    ++snapId;
                }
            );
            ++generatorId;
        }
    );

    generatorId = 1;
    snapId      = 0;
    std::vector<Types::index> numberOfColumsPerVertex = {2,2,2,2,2,3,2,3,3,2};
    Types::count counter = 0;
    network_.Graph().template for_all_vertex_identifiers<ExecutionPolicy::sequential>(
        [&generatorId,
         &snapId,
         &numberOfColumsPerVertex,
         &counter,
         this](Types::vertexId vertexId)
        {
            network_.template for_all_real_power_generator_snapshots_at<ExecutionPolicy::sequential>(
                vertexId
                , [&generatorId,
                   &snapId,
                   &numberOfColumsPerVertex,
                   &counter](Types::index snapshotId, Types::generatorSnapshot snapshot)
                {
                    EXPECT_EQ ( generatorId*100 + (snapId%10)*10, snapshot);
                    EXPECT_EQ ( (snapId%10),                      snapshotId);
                    ++snapId;
                    if ( 0 == (snapId%10) ) ++generatorId;
                    ++counter;
                }
            );
            EXPECT_EQ ( numberOfColumsPerVertex[vertexId], counter/10);
            counter = 0;
        }
    );
}

TEST_F ( TestPyPsaExample, CheckLoadRealPowerSnapshots )
{
    Types::loadId loadId = 0;
    Types::index  snapId = 0;
    network_.template for_all_real_power_load_snapshots<ExecutionPolicy::sequential>(
        [&loadId, &snapId]
        ( Types::index snapshotId
        , Types::loadSnapshot snapshot )
        {
            // std::cout << "snapshotId: " << snapshotId << " ; snapshots: " << snapshot << std::endl;
            EXPECT_EQ ( 100 + (snapId%10)*10 + loadId, snapshot);
            EXPECT_EQ ( (snapId%10),                   snapshotId);
            ++snapId;
            if ( 0 == (snapId%10) ) ++loadId;
        }
    );

    loadId = 0;
    snapId = 0;
    network_.template for_all_loads<ExecutionPolicy::sequential>(
        [this,&loadId, &snapId](TLoadProperties const & loadProperties)
        {
            this->network_.template for_all_real_power_load_snapshots_of<ExecutionPolicy::sequential>(
                loadId,
                [&loadId, &snapId](Types::index snapshotId, Types::generatorSnapshot snapshot) {
                    EXPECT_EQ ( 100 + (snapId%10)*10 + loadId, snapshot);
                    EXPECT_EQ ( (snapId%10),                   snapshotId);
                    ++snapId;
                }
            );
            ++loadId;
        }
    );

    loadId = 0;
    snapId = 0;
    std::vector<Types::index> numberOfColumsPerVertex = {1,1,1,1,1,1,1,1,1,1};
    Types::count counter = 0;
    network_.Graph().template for_all_vertex_identifiers<ExecutionPolicy::sequential>(
        [&loadId,
         &snapId,
         &numberOfColumsPerVertex,
         &counter,
         this](Types::vertexId vertexId)
        {
            network_.template for_all_real_power_load_snapshots_at<ExecutionPolicy::sequential>(
                vertexId
                , [&loadId,
                   &snapId,
                   &numberOfColumsPerVertex,
                   &counter](Types::index snapshotId, Types::generatorSnapshot snapshot)
                {
                    EXPECT_EQ ( 100 + (snapId%10)*10 + loadId, snapshot);
                    EXPECT_EQ ( (snapId%10),                   snapshotId);
                    ++snapId;
                    if ( 0 == (snapId%10) ) ++loadId;
                    ++counter;
                }
            );
            EXPECT_EQ ( numberOfColumsPerVertex[vertexId], counter/10);
            counter = 0;
        }
    );
}

TEST_F ( PyPSAExampleInconsistencyGeneratorsDeathTest
       , DeathTestInconsistency )
{
    auto assertionString = buildAssertionString ( "PyPsaParser.hpp"
                                                , "PyPsaParser"
                                                , "ExtractGeneratorMaximumRealPowerPuHeader"
                                                , R"(false && "Generator name does not exist")");
    EXPECT_DEATH({egoa::PowerGridIO<TGraph>::read( network_
                                                 , graph_
                                                 , TestCaseSmallExample_
                                                 , TPowerGridIO::ReadPyPsa );}, assertionString );
}

TEST_F ( PyPSAExampleInconsistencyInTimestampLengthDeathTest
       , DeathTestInconsistency )
{
    auto assertionString = buildAssertionString ( "PyPsaParser.hpp"
                                                , "PyPsaParser"
                                                , "HasCorrectSnapshotSizes"
                                                , "generatorSnapshotsSize == loadSnapshotsSize");
    EXPECT_DEATH({egoa::PowerGridIO<TGraph>::read( network_
                                                 , graph_
                                                 , TestCaseSmallExample_
                                                 , TPowerGridIO::ReadPyPsa );}, assertionString );
}

TEST_F ( PyPSAExampleDuplicatedGeneratorsDeathTest
       , DeathTestGeneratorDuplicates )
{
    auto assertionString = buildAssertionString ( "PyPsaParser.hpp"
                                                , "PyPsaParser"
                                                , "AddNameToGenerator"
                                                , R"(false && "Generator duplicates")");
    EXPECT_DEATH({egoa::PowerGridIO<TGraph>::read( network_
                                                 , graph_
                                                 , TestCaseSmallExample_
                                                 , TPowerGridIO::ReadPyPsa );}, assertionString );
}

TEST_F ( PyPSA_PyPSA_data_2018_11_20__elec_s1024_AT
       , SimpleReadTest )
{
    if ( ! egoa::PowerGridIO<TGraph>::read( network_
                                          , graph_
                                          , TestCaseSmallExample_
                                          , TPowerGridIO::ReadPyPsa ) )
    {
        std::cout   << "Expected file "
                    << TestCaseSmallExample_
                    << " does not exist!";
    }
}

} // namespace egoa::test

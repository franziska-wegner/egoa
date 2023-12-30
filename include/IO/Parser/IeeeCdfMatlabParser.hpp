/*
 * IeeeCdfMatlabParser.hpp
 *
 *  Created on: Sep 07, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA___IO___PARSER___IEEE_CDF_MATLAB_PARSER_HPP
#define EGOA___IO___PARSER___IEEE_CDF_MATLAB_PARSER_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "DataStructures//Networks/PowerGrid.hpp"

#include "DataStructures/Graphs/StaticGraph.hpp"

#include "DataStructures/Graphs/Edges/Edge.hpp"
#include "DataStructures/Graphs/Edges/ElectricalProperties.hpp"

#include "DataStructures/Graphs/Vertices/Type.hpp"
#include "DataStructures/Graphs/Vertices/Vertex.hpp"
#include "DataStructures/Graphs/Vertices/ElectricalProperties.hpp"
#include "DataStructures/Graphs/Vertices/GeneratorProperties.hpp"
#include "DataStructures/Graphs/Vertices/LoadProperties.hpp"

#include "Auxiliary/Auxiliary.hpp"

namespace egoa {

template<typename GraphType = StaticGraph< Vertices::ElectricalProperties<Vertices::IeeeBusType >
                                         , Edges::ElectricalProperties > >
class IeeeCdfMatlabParser final {

    using TElectricalVertex     = typename GraphType::TVertex;
    using TVertexProperties     = typename TElectricalVertex::TProperties;
    using TVertex               = typename GraphType::TVertex;

    using TVertexType           = typename TVertexProperties::TVertexType;

    using TGeneratorProperties  = Vertices::GeneratorProperties<TVertexType>;
    using TLoadProperties       = Vertices::LoadProperties<TVertexType>;
    using TElectricalEdge       = typename GraphType::TEdge;
    using TEdgeProperties       = typename TElectricalEdge::TProperties;
    using TBound                = Bound<>;
    using TNetwork              = PowerGrid<GraphType>;

    private:
        static inline void toUpper ( std::string &str ) {
            std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        }

        static inline void toLower(std::string &str) {
            std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        }

        inline void init () {
            initialized_ = false;
        }

        /**
         * @brief Read base MVA from an m-file in IEEE Common Data Format
         * @details This value is necessary for the per Unit system.
         *
         * @param[in,out] network The parameter base MVA is changed in this method.
         */
        void readBaseMva ( TNetwork & network ) {
            Types::string str;
            while ( str.compare("mpc.baseMVA") )
            {
                input_stream_ >> str;
            }
            input_stream_.ignore(3);
            getline ( input_stream_, str, ';' );
            network.BaseMva() = atoi(str.c_str());
        }

        /**
         * @brief Read the name of the case
         * @details The name of the power grid, e.g. case14 for the 14 bus system.
         *
         * @param[in,out] network The parameter changes the name of the network
         */
        inline void readCaseName( TNetwork & network ) {
            Types::string str;
            while ( str.compare("function") )
            {
                input_stream_ >> str;
            }
            input_stream_.ignore(6);
            input_stream_  >> str;
            network.Graph().Name() =  str;
        }

        /**
         * @brief Read the bus matrix
         * @details While reading each line of the matrix a vertex is created and
         *      added to the network with
         *      vertex.Name()                   = bus_i,
         *      vertex.Type()                   = type,
         *      vertex.RealPowerLoad()          = Pd / base_mva,
         *      vertex.ReactivePowerLoad()      = Qd / base_mva,
         *      vertex.ShuntConductance()       = Gs / base_mva,
         *      vertex.ShuntSusceptance()       = Bs / base_mva,
         *      vertex.Area()                   = area,
         *      vertex.VoltageMagnitude()       = Vm,
         *      vertex.VoltageAngleSnapshot()   = Va,
         *      vertex.BaseKV                   = baseKV,
         *      vertex.Zone()                   = zone,
         *      vertex.MaximumVoltage()         = Vmax,
         *      vertex.MinimumVoltage()         = Vmin.
         *
         *
         * @param[in,out] network Add all buses to the network
         */
        void readBusMatrix( TNetwork & network ) {
            Types::string str;

            // Nodes
            while ( str.compare("mpc.bus") )
            {
                input_stream_ >> str;
            }

            getline(input_stream_, str);

            TVertexProperties   bus;
            TLoadProperties     load;
            Types::vertexId     identifier;

            network.AddSnapshotTimestamp( genericTimestamp_ );
            network.AddSnapshotWeighting( genericWeighting_ );

            input_stream_ >> str;

            while ( str.compare("];") )
            {
                bus.Name()                    = str.c_str();

                input_stream_ >> std::ws >> str;
                bus.Type()                    = Vertices::to_enum<TVertexType>( atoi( str.c_str() ) );

                input_stream_ >> std::ws >> str; //bus
                load.RealPowerLoad()          = Types::String2double(str) / network.BaseMva();

                input_stream_ >> str; //bus
                load.ReactivePowerLoad()      = Types::String2double(str) / network.BaseMva();

                input_stream_ >> str;
                bus.ShuntConductance()       = Types::String2double(str) / network.BaseMva();

                input_stream_ >> str;
                bus.ShuntSusceptance()       = Types::String2double(str) / network.BaseMva();

                input_stream_ >> std::ws >> str;
                bus.Area()                   = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                bus.VoltageMagnitude()       = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                bus.VoltageAngle()           = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                bus.NominalVoltage()         = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                bus.Zone()                   = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                bus.MaximumVoltage()         = Types::String2double(str);

                getline(input_stream_, str,';');
                bus.MinimumVoltage()         = Types::String2double(str);

                bus.Status()                 = Vertices::BusStatus::active;
                identifier                   = network.Graph().AddVertex( bus );
                mapVertexName2Id_[bus.Name()]= identifier;

                //bus
                if ( load.RealPowerLoad() >= 0 )
                {
                    load.RealPowerLoadBound().Minimum() = 0;
                    load.RealPowerLoadBound().Maximum() = load.RealPowerLoad();
                } else {
                    load.RealPowerLoadBound().Minimum() = load.RealPowerLoad(); // TODO
                    load.RealPowerLoadBound().Maximum() = 0;
                }

                if ( load.ReactivePowerLoad() >= 0 )
                {
                    load.ReactivePowerLoadBound().Minimum() = 0;
                    load.ReactivePowerLoadBound().Maximum() = load.ReactivePowerLoad();
                } else {
                    load.ReactivePowerLoadBound().Minimum() = load.ReactivePowerLoad();
                    load.ReactivePowerLoadBound().Maximum() = 0;
                }

                if ( load.RealPowerLoad() > 0 || load.ReactivePowerLoad() > 0 )
                {
                    load.Name()          = bus.Name();
                    load.Type()          = Vertices::IeeeBusType::load;
                    Types::loadId loadId = network.AddLoadAt( identifier, load );
                    if ( load.RealPowerLoad () > 0 )
                    { // Add a snapshot only when necessary
                        network.AddLoadSnapshotAt(loadId, load.RealPowerLoad() ); // Maximum real power p.u.
                    } //@todo Else add load snapshot that has reactive power
                }
                if ( load.RealPowerLoad () < 0 )
                { // real power generator if real power demand is negative
                    TGeneratorProperties generator;
                    generator.Name ()       = bus.Name();
                    generator.RealPower ()  = std::fabs ( load.RealPowerLoad() );
                    // Add real power bounds using the absolute value of the demand
                    generator.RealPowerBound().Minimum() = 0;
                    generator.RealPowerBound().Maximum() = generator.RealPower ();

                    if ( load.ReactivePowerLoad () < 0 )
                    {
                        generator.ReactivePower ()               = std::fabs ( load.ReactivePowerLoad () );
                        // Add reactive power bounds using the absolute value of the demand
                        generator.ReactivePowerBound().Minimum() = 0;
                        generator.ReactivePowerBound().Maximum() = generator.ReactivePower ();
                    } // else is already done before by adding a load vertex
                } else if ( load.ReactivePowerLoad () < 0 )
                { // reactive power generator if reactive power demand is negative
                    TGeneratorProperties generator;
                    generator.Name ()                        = bus.Name();
                    generator.ReactivePower ()               = std::fabs ( load.ReactivePowerLoad () );
                    // Add reactive power bounds using the absolute value of the demand
                    generator.ReactivePowerBound().Minimum() = 0;
                    generator.ReactivePowerBound().Maximum() = generator.ReactivePower ();
                } // else is already done before by adding a load vertex

                input_stream_ >> str;
            }

            input_stream_.seekg (0, input_stream_.beg); //move the position to the begin of the file
        }


        /**
         * @brief Read the branch matrix
         * @details While reading each row of the matrix a arc is created and added
         *     to the network with
         *     edge.Conductance()           = G not in data (\f$ \frac{R}{|Z|} \f$, with \f$ |Z| = R^2 + X^2 \f$)
         *     edge.Susceptance()           = B not in data (\f$ \frac{X}{|Z|} \f$, with \f$ |Z| = R^2 + X^2 \f$)
         *     edge.Resistance()            = r             (or R for resistance)
         *     edge.Reactance()             = x             (or X for reactance)
         *     edge.Charge()                = b             (for charge)
         *     edge.ThermalLimit()          = rateA         (Standard line capacity/thermal line limit)
         *     edge.ThermalLimitB()         = rateB         (Emergency line capacity/thermal line limit)
         *     edge.ThermalLimitC()         = rateC         (Emergency line capacity/thermal line limit)
         *     edge.TapRatio()              = ratio         (tap ratio)
         *     edge.AngleShift()            = angle.pi/180  (angle is transformed into radian \f$ \frac{angle^\circ\cdot\pi}{180^\circ} \f$ rad, since \f$ \pi = 180^\circ \f$)
         *     edge.cc                      = not in data   (\f$ ratio\cdot\cos\left( \frac{angle^\circ\cdot\pi}{180^\circ} \right) \f$)
         *     edge.dd                      = not in data   (\f$ ratio\cdot\sin\left( \frac{angle^\circ\cdot\pi}{180^\circ} \right) \f$)
         *     edge.Status()                = status
         *     edge.ThetaBound().Minimum()  = angmin.pi/180  (angle is transformed into radian \f$ \frac{angmin^\circ\cdot\pi}{180^\circ} \f$ rad, since \f$ \pi = 180^\circ \f$)
         *     edge.ThetaBound().Maximum()  = angmax.pi/180  (angle is transformed into radian \f$ \frac{angmax^\circ\cdot\pi}{180^\circ} \f$ rad, since \f$ \pi = 180^\circ \f$)
         *
         *     IGNORE: rateB, rateC
         *
         * @param[in,out] network Netowork with all arcs
         */
        void readBranchMatrix( TNetwork & network ) {
            Types::string str;

            network.ThetaBound().Minimum() = 0.0;
            network.ThetaBound().Maximum() = 0.0;

            // TODO this can be done smarter, currently whole file scanned again
            while ( str.compare("mpc.branch") )
            {
                input_stream_ >> str;
            }

            getline(input_stream_, str);
            Types::string src, dest;

            input_stream_ >> str;

            while(str.compare("];"))
            {
                TEdgeProperties edge;
                src = str;

                input_stream_ >> dest;

                // edge.Source()  = mapVertexName2Id_[src];
                // edge.Target()  = mapVertexName2Id_[dest];

                // r in the data
                input_stream_ >> str;
                edge.Resistance()    = Types::String2double(str);

                // x in the data
                input_stream_ >> str;
                edge.Reactance()     = Types::String2double(str);

                // b in the data
                input_stream_ >> str;
                edge.Charge()        = Types::String2double(str);

                // Rate A in the data
                input_stream_ >> str;
                edge.ThermalLimit()  = Types::String2double(str) / network.BaseMva();

                // Rate B in the data
                input_stream_ >> std::ws >> str;
                edge.ThermalLimitB() = Types::String2double(str) / network.BaseMva();

                // Rate C in the data
                input_stream_ >> std::ws >> str;
                edge.ThermalLimitC() = Types::String2double(str) / network.BaseMva();

                // Tap ratio tau in the data
                input_stream_ >> std::ws >> str;
                if(atof(str.c_str()) == 0)
                { //
                    edge.TapRatio() = 1.0;
                } else
                    edge.TapRatio() = Types::String2double(str);

                // theta shift in the data
                input_stream_ >> str;
                edge.AngleShift()            = Types::String2double(str)    * Const::PI / 180;
                edge.TapRatioCosThetaShift() = edge.TapRatio() * cos( edge.AngleShift() );
                edge.TapRatioSinThetaShift() = edge.TapRatio() * sin( edge.AngleShift() );

                // Status in the data
                input_stream_ >> str;
                edge.Status()                = Types::String2integer(str);

                // angmin in the data
                input_stream_ >> str;
                edge.ThetaBound().Minimum()     = Types::String2double(str) * Const::PI / 180 ;
                network.ThetaBound().Minimum() += edge.ThetaBound().Minimum(); //m_theta_lb

                // angmax in the data
                input_stream_ >> str;
                edge.ThetaBound().Maximum()     = Types::String2double(str) * Const::PI / 180;
                network.ThetaBound().Maximum() += edge.ThetaBound().Maximum();

                network.Graph().AddEdge(mapVertexName2Id_[src], mapVertexName2Id_[dest], edge);

                getline(input_stream_, str,'\n');
                input_stream_ >> str;
            } // while
        }

        /**
         * @brief Read generator matrix
         * @details While reading each row of the matrix a generator is created and
         *     added to the network
         *     vertex.Name()                            = bus
         *     vertex.RealPower()                       = Pg   / base_mva,
         *     vertex.ReactivePower()                   = Qg   / base_mva,
         *     vertex.ReactivePowerBound().Maximum()    = Qmax / base_mva,
         *     vertex.ReactivePowerBound().Minimum()    = Qmin / base_mva,
         *     vertex.VoltageMagnitude()                = Vg
         *     vertex.Mbase()                           = mBase
         *     vertex.Status()                          = status
         *     vertex.RealPowerBound().Maximum()        = Pmax / base_mva,
         *     vertex.RealPowerBound().Minimum()        = Pmin / base_mva,
         *     vertex.Pc1()                             = Pc1
         *     vertex.Pc2()                             = Pc2
         *     vertex.Qc1Bound().Minimum()              = Qc1min
         *     vertex.Qc1Bound().Maximum()              = Qc1max
         *     vertex.Qc2Bound().Minimum()              = Qc2min
         *     vertex.Qc2Bound().Maximum()              = Qc2max
         *     vertex.RampAgc()                         = ramp_agc
         *     vertex.Ramp10()                          = ramp_10
         *     vertex.Ramp30()                          = ramp_30
         *     vertex.RampQ()                           = ramp_q
         *     vertex.Apf()                             = apf
         *
         *
         *
         * @param[in,out] network Network with all generator
         */
        void readGeneratorMatrix( TNetwork & network ) {
            Types::string   str;

            while ( str.compare("mpc.gen") ) {
                input_stream_ >> str;
            }

            getline(input_stream_, str);
            input_stream_ >> str;

            while ( str.compare("];") ) {
                TGeneratorProperties generator;

                generator.Name()                           = str.c_str();

                input_stream_ >> str;
                generator.RealPower()                      = Types::String2double(str) / network.BaseMva();

                input_stream_ >> str;
                generator.ReactivePower()                  = Types::String2double(str) / network.BaseMva();

                input_stream_ >> str;
                generator.ReactivePowerBound().Maximum()   = Types::String2double(str) / network.BaseMva();

                input_stream_ >> str;
                generator.ReactivePowerBound().Minimum()   = Types::String2double(str) / network.BaseMva();

                input_stream_ >> std::ws >> str;
                generator.VoltageMagnitude()               = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                generator.NominalPower()                   = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                Types::index status                        = Types::String2integer(str);
                if ( status )
                    generator.Status()                     = Vertices::BusStatus::active;
                else
                    generator.Status()                     = Vertices::BusStatus::inactive;

                input_stream_ >> str;
                generator.RealPowerBound().Maximum()       = Types::String2double(str) / network.BaseMva();

                input_stream_ >> str;
                generator.RealPowerBound().Minimum()       = Types::String2double(str) / network.BaseMva();

                input_stream_ >> std::ws >> str;
                generator.Pc1()                            = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                generator.Pc2()                            = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                generator.Qc1Bound().Minimum()             = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                generator.Qc1Bound().Maximum()             = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                generator.Qc2Bound().Minimum()             = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                generator.Qc2Bound().Maximum()             = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                generator.RampAgc()                        = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                generator.Ramp10()                         = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                generator.Ramp30()                         = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                generator.RampQ()                          = Types::String2double(str);

                input_stream_ >> std::ws >> str;
                generator.Apf()                            = Types::String2double(str);

                getline(input_stream_, str,'\n');

                Types::generatorId generatorId             = network.AddGeneratorAt(mapVertexName2Id_[generator.Name()], generator);
                network.AddGeneratorRealPowerSnapshotAt( generatorId, generator.RealPower() );

                // Get first item in the new line
                input_stream_ >> str;
            }
            input_stream_.seekg (0, input_stream_.beg);
        }

        /**
         * @brief Gammelig
         * @todo add both possible function types
         * @details Gammelig
         *
         * @param network Gammelig
         */
        // void readGeneratorCostFunctionMatrix( TNetwork & network );


        bool readNetwork( TNetwork & network ) {
            readCaseName( network );
            readBaseMva( network );
            readBusMatrix( network );
            readGeneratorMatrix( network );
            // readGeneratorCostFunctionMatrix( network );
            readBranchMatrix( network );

            return true;
        }

    public:
        explicit IeeeCdfMatlabParser ( std::istream & input_stream )
        : input_stream_(input_stream)
        {
            init();
        }

        bool read ( TNetwork & network ) {
            return readNetwork( network );
        }

    private:
        std::istream &                                  input_stream_;
        bool                                            initialized_;
        std::unordered_map<Types::name, Types::index>   mapVertexName2Id_;

        const Types::string                             genericTimestamp_ = "0000-00-00 00:00:00";
        const Types::real                               genericWeighting_ = 1.0;
};

} // namespace egoa

#endif // EGOA__IO__PARSER___IEEE_CDF_MATLAB_PARSER_HPP

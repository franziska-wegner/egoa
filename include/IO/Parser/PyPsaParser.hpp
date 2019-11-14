/*
 * PyPsaParser.hpp
 * https://pypsa.org/doc/components.html
 * https://pypsa.org
 * https://wiki.openmod-initiative.org/wiki/Transmission_network_datasets
 *
 *  Created on: Nov 20, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__IO__PARSER___PY_PSA_PARSER_HPP
#define EGOA__IO__PARSER___PY_PSA_PARSER_HPP

#include <typeinfo>

#include <QFile>
#include <QStringList>

#include "IO/Wrapper/Edge.hpp"
#include "IO/Helper/DataValidation.hpp"

#include "DataStructures/Graphs/PowerGrid.hpp"
#include "DataStructures/Graphs/Edges/ElectricalProperties.hpp"
#include "DataStructures/Graphs/Vertices/ElectricalProperties.hpp"
#include "DataStructures/Graphs/Vertices/GeneratorProperties.hpp"
#include "DataStructures/Graphs/Vertices/LoadProperties.hpp"

#include "Auxiliary/Auxiliary.hpp"

namespace egoa {

namespace internal {
template<typename VertexTypeProperties, typename EdgeTypeProperties, typename GraphType>
class NetworkDifferentiation;
} // namespace internal

template<typename GraphType = StaticGraph< Vertices::ElectricalProperties<Vertices::IeeeBusType>, Edges::ElectricalProperties > >
class PyPsaParser {

#pragma mark TEMPLATE_TYPE_ALIASING
    // Template type aliasing
    using TGraph            = GraphType;
    using TNetwork          = PowerGrid<GraphType>;
    // Vertices
    using TVertex               = typename TGraph::TVertex;
    using TVertexProperties     = typename TGraph::TVertexProperties;
    using TVertexType           = typename TVertexProperties::TVertexType;
    using TGeneratorProperties  = typename TNetwork::TGeneratorProperties;
    using TLoadProperties       = typename TNetwork::TLoadProperties;
    // Edges
    using TEdge                 = typename TGraph::TEdge;
    using TEdgeProperties       = typename TGraph::TEdgeProperties;
    using TIoEdge               = io::Edge<TEdgeProperties>;
    // Bounds
    using TBound                = Bound<>;
    
    public:

        ///@name Constructors and destructor
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTOR

            explicit PyPsaParser ( std::string const & filename )
            : path2FileDirectory_( filename )
            , filenameBuses_("buses.csv")
            , filenameCarriers_("carriers.csv")
            , filenameGenerators_("generators.csv")
            , filenameGeneratorsPMaxPu_("generators-p_max_pu.csv")
            , filenameGlobalConstraints_("global_constraints.csv")
            , filenameLines_("lines.csv")
            , filenameLinesNew_("lines_new.csv")
            , filenameLoads_("loads.csv")
            , filenameLoadsPSet_("loads-p_set.csv")
            , filenameNetwork_("network.csv")
            , filenameSnapshots_("snapshots.csv")
            , filenameStorageUnits_("storage_units.csv")
            , filenameStorageUnitsInflow_("storage_units-inflow.csv")
            , generatorSnapshotsSize(0)
            , loadSnapshotsSize(0)
            {}

            PyPsaParser ( std::string filenameBuses 
                        , std::string filenameCarriers
                        , std::string filenameGenerators
                        , std::string filenameGeneratorsPMaxPu
                        , std::string filenameGlobalConstraints
                        , std::string filenameLines
                        , std::string filenameLinesNew
                        , std::string filenameLoads
                        , std::string filenameLoadsPSet
                        , std::string filenameNetwork 
                        , std::string filenameSnapshots
                        , std::string filenameStorageUnits
                        , std::string filenameStorageUnitsInflow )
            : filenameBuses_(filenameBuses)
            , filenameCarriers_(filenameCarriers)
            , filenameGenerators_(filenameGenerators)
            , filenameGeneratorsPMaxPu_(filenameGeneratorsPMaxPu)
            , filenameGlobalConstraints_(filenameGlobalConstraints)
            , filenameLines_(filenameLines)
            , filenameLinesNew_(filenameLinesNew)
            , filenameLoads_(filenameLoads)
            , filenameLoadsPSet_(filenameLoadsPSet)
            , filenameNetwork_(filenameNetwork)
            , filenameSnapshots_(filenameSnapshots)
            , filenameStorageUnits_(filenameStorageUnits)
            , filenameStorageUnitsInflow_(filenameStorageUnitsInflow)
            , generatorSnapshotsSize(0)
            , loadSnapshotsSize(0)
            {}

            ~PyPsaParser()
            {
                mapBusName2VertexId_.clear();           
                mapGeneratorName2Generator_.clear();
                mapGeneratorName2Identifier_.clear();
                mapGeneratorName2BusName_.clear();
                mapLoadName2Identifier_.clear();
            }
        ///@}

        ///@name Reader Methods
        ///@{
#pragma mark READERS

            /**
             * @brief      Read storage units in flow.
             * @details    For more information see the storage unit section under
             *     <a href="https://pypsa.org/doc/components.html">https://pypsa.org/doc/components.html</a>.
             *     
             * @I{  An example input is given by:
             *     
             *      name         -   Timestamp
             *      AT0 1 hydro  -   Represents a storage unit name with its production snapshot
             *  }
             *  
             * @return     Returns @p true if the parsing was successful, @p
             *     false otherwise.
             */
            inline bool ReadStorageUnitsInflows () 
            {
                throw std::runtime_error ( "Not implemented yet! Storage units are currently unsupported." );
                return true;
            }

            /**
             * @brief      Reads storage units.
             * @details    For more information see the storage unit section under
             *     <a href="https://pypsa.org/doc/components.html">https://pypsa.org/doc/components.html</a>.
             * 
             * @I{  The setting is as following:
             *      name                    - Name 
             *      
             *      bus                     - Name of the bus (required)
             *      capital_cost            - in currency/MWh (default 0, optional)
             *      carrier                 - (default n/a, optional)
             *      control                 - 
             *      cyclic_state_of_charge  - 
             *      type                    - 
             *      efficiency_store        - 
             *      efficiency_dispatch     - in p.u. (default 1, optional)
             *      inflow                  - 
             *      marginal_cost           - in currency/MWh (default 0, optional)
             *      max_hours               - (default NaN, optional)
             *      p                       - 
             *      p_min_pu                - in p.u., minimum output (default -1, optional)
             *      p_max_pu                - in p.u., maximum output (default 1, optional)
             *      p_nom                   - in MW, nominal power (default 0, optional)
             *      p_nom_extendable        -  
             *      p_nom_opt               - 
             *      p_set                   - in MW, real power set point (default 0, optional)
             *      q                       - 
             *      q_set                   - in MVar, reactive power set point (default 0, optional)
             *      sign                    - power sign (default 1, optional)
             *      standing_loss           - 
             *      state_of_charge         - 
             *      state_of_charge_initial - 
             *      state_of_charge_set     - 
             *      spill                   - 
             *  }
             *
             * @return     @p True if the parsing was successful, @p False otherwise.
             */
            inline bool ReadStorageUnits() 
            {
                throw std::runtime_error ( "Not implemented yet! Storage units are currently unsupported." );
                return true;
            }

            /**
             * @brief      Read the bus matrix.
             * @details    While reading each line of the matrix a vertex is
             *      created and added to the network (see the bus section of
             *      <a href="https://pypsa.org/doc/components.html">https://pypsa.org/doc/components.html</a>
             *      for more information).
             *      
             * @I{  The setting is as following:
             * 
             *      Name in EGOA        Name in PyPSA       Description                           
             *      
             *      - vertex.Name()     - name          - unique name of the bus
             *      
             *      -                   - carrier       - AC, DC  (default AC, optional)
             *      - vertex.Des        - country       - country
             *      - vertex.Type()     - type          - Not specified. We use the IEEE TYPES here.
             *      -                   - v_mag_pu_set  - in p.u. (default 1, optional)
             *      -                   - v_mag_pu_min  - in p.u. (default 0, optional)
             *      -                   - v_mag_pu_max  - in p.u. (default INF, optional)
             *      - vertex.VoltageNom - v_nom         - in kV, Nominal voltage (default 1, optional)
             *      - vertex.X()        - x             - X-Coordinate (longitude)
             *      - vertex.Y()        - y             - Y-Coordinate (latitude)
             *                          
             *      Output parameter are:
             *          - control         - (default PQ) P,Q,V control strategy for the power flow, must be @p PQ, @p PV or @p Slack.
             *          - marginal_price  - in currency/MWh (default 0). Locational marginal price from LOPF from power balance constraint.
             *          - p               - in MW (default 0). The real power at a vertex.
             *          - q               - in MVar (default 0). The reactive power at a vertex.
             *          - sub_network     - Name of connected sub-network to which the vertex belongs.
             *          - vertex.Theta()  - in RAD (default: 0). The Voltage angle.
             *          - v_ang           - in radians (default 0)
             *          - v_mag_pu        - in p.u. (default 1). Voltage magnitude, per unit of v_nom. 
             *   }   
             *
             * @param      network   The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * @param      filename  The filename.
             *
             * @return     @p True if the parsing was successful, @p False otherwise.
             */
            inline bool ReadBuses ( TNetwork          & network
                                  , std::string const & filename ) 
            {
                QFile file( QString::fromStdString(filename + "/" + filenameBuses_) );
                OpenFile(file);
                QList<QByteArray> splitted = ReadLine( file );

                dataMapperBuses_.clear();
                ExtractBusHeader( splitted );
                while( !file.atEnd() ) 
                {
                    TVertexProperties vertexProperties;
                    std::string temp;

                    splitted = ReadLine( file, false );
                    
                    USAGE_ASSERT ( static_cast<Types::count>( splitted.size() ) == dataMapperBuses_.size() );

                    for ( Types::count counter = 0
                        ; counter < static_cast<Types::count>( splitted.size() )
                        ; ++counter ) 
                    {
                        temp = splitted[counter].toStdString();
                        (this->*dataMapperBuses_[counter])( temp , vertexProperties);
                    } // for
                    Types::vertexId index                            = AddVertex<TNetwork>( network, vertexProperties );
                    mapBusName2VertexId_[ vertexProperties.Name() ]  = index;
                } // while
                return true;
            }

            /**
             * @brief      Reads carriers.
             * @details    For more information see the carrier section under 
             *     <a href="https://pypsa.org/doc/components.html">https://pypsa.org/doc/components.html</a>.
             *     
             * @I{  The setting is as following:
             *          - name              - Name of the carrier, see ReadGeneratorMatrix for mapping.
             *          - co2_emissions     - in tonnes/MWh (CO2 emissions of this carrier) 
             *  }
             *
             * @return     @p True if the parsing was successful, @p False otherwise.
             */
            inline bool ReadCarriers() 
            {
                throw std::runtime_error ( "Not implemented yet! Storage units are currently unsupported." );
                return true;
            }

            /**
             * @brief      Read generators maximum real power production
             *     snapshot in p.u.
             * @details    For more information see the generator section under 
             *     <a href="https://pypsa.org/doc/components.html">https://pypsa.org/doc/components.html</a>.
             *
             * @param      network   The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * @param      filename  The filename
             * 
             * @I{
             *     - name 
             *     - AT0 0 onwind    - Represents a generator name with its production snapshot in p.u.
             *     - AT0 0 ror       - Represents a generator name with its production snapshot in p.u.
             *   }
             *
             * @return     @p True if the parsing was successful, @p False otherwise.
             */
            inline bool ReadGeneratorsRealPowerMaxPu ( TNetwork          & network
                                                     , std::string const & filename ) 
            {
                QFile file( QString::fromStdString(filename + "/" + filenameGeneratorsPMaxPu_) );
                OpenFile(file);
                QList<QByteArray> splitted = ReadLine( file, false );

                dataMapperGeneratorsRealPowerMaxPu_.clear();
                ExtractGeneratorMaximumRealPowerPuHeader( splitted );
                
                while( !file.atEnd() ) 
                {
                    splitted = ReadLine( file, false );
                    std::string generationValue;
                    
                    USAGE_ASSERT ( static_cast<Types::count>( splitted.size() ) == dataMapperGeneratorsRealPowerMaxPu_.size() );
                    
                    if ( !splitted[0].isEmpty() )
                    {
                        ++ generatorSnapshotsSize;
                    }
                    for ( Types::count counter = 0
                        ; counter < static_cast<Types::count>( splitted.size() )
                        ; ++counter ) 
                    {
                        generationValue = splitted[counter].toStdString();
                        dataMapperGeneratorsRealPowerMaxPu_[counter]( generationValue, network );
                    } // for
                } // while
                return true;
            }

            /**
             * @brief      Read the generator matrix.
             * @details    While reading each row of the matrix a generator is
             *     created and added to the network. The description of the
             *     elements is as in 
             *     <a href="https://pypsa.org/doc/components.html">https://pypsa.org/doc/components.html</a>.
             *
             * @param      network   The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * @param      filename  The filename.
             *
             * @I{
             *      Name in EGOA                          Name in PyPSA             Description
             *      
             *     - vertex.Name()                         - name                   - unique generator name (required)
             *     - vertex.Name()                         - bus                    - bus at which the generator is connected (required)
             *     - vertex.Control()                      - control                - P, Q, V control strategy usually PQ, PV or Slack (default PQ, optional)
             *     - vertex.Type                           - type                   - generator type (default n/a, optional)
             *     - vertex.CapitalCost()                  - capital_cost           - (default n/a, optional) 
             *     - vertex.Type                           - carrier                - carrier (default n/a, optional)
             *     - vertex.efficiency                     - efficiency             - (default n/a, optional) 
             *     - vertex.marginal_cost                  - marginal_cost          - (default n/a, optional) 
             *     - vertex.Mbase()                        - p_nom                  - in MW, nominal power for limits (default 0, optional)
             *     - vertex.IsExtendable()                 - p_nom_extendable       - to allow capacity (default 0, optional)
             *     - vertex.NominalRealPower().Minimum()   - p_nom_min              - in p.u., if p_nom extendable, i.e., set p_nom_min (default 0, optional)
             *     - vertex.NominalRealPower().Maximum()   - p_nom_max              - in p.u., if p_nom extendable, i.e., set p_nom_max (default INF, optional)
             *     - vertex.RealPowerBound().Minimum()     - p_min_pu               - in p.u., the minimum output for each snapshot (default 0, optional)
             *     - vertex.RealPowerBound().Maximum()     - p_max_pu               - in p.u., the maximum output for each snapshot (default 1, optional)
             *     - vertex.ReactivePowerBound().Minimum() - 
             *     - vertex.ReactivePowerBound().Maximum() - 
             *     - vertex.RealPowerSetPoint()            - p_set                  - in MW, real power set point (default 0, optional)
             *     - vertex.ReactivePowerSetPoint()        - q_set                  - in MVar, reactive power set point (default 0, optional)
             *     - vertex.PowerSign()                    - sign                   - (default 1, optional)
             *     - vertex.MarginalCost()                 - marginal_cost          - in currency per MWh, (default 0, optional)
             *     - vertex.CapitalCost()                  - capital_cost           - in currency per MW, (default 0, optional)
             *     - vertex.Efficiency()                   - efficiency             - in p.u., (default 1, optional)
             *     - vertex.Committable()                  - committable            -  (default 0, optional)
             *     - vertex.StartUpCost()                  - start_up_cost          - in currency, (default 0, optional)
             *     - vertex.ShutDownCost()                 - shut_down_cost         - in currency, (default 0, optional)
             *     - vertex.MinimumUpTime()                - min_up_time            - in p.u., (default 0, optional)
             *     - vertex.MinimumDownTime()              - min_down_time          - in p.u., (default 0, optional)
             *     - vertex.Status()                       - initial_status         - in p.u., (default 1, optional)
             *     - vertex.RampLimitUp()                  - ramp_limit_up          - in p.u., (default NaN, optional)
             *     - vertex.RampLimitDown()                - ramp_limit_down        - in p.u., (default NaN, optional)
             *     - vertex.RampLimitStartUp()             - ramp_limit_start_up    - in p.u., (default 1, optional)
             *     - vertex.RampLimitShutDown()            - ramp_limit_shut_down   - in p.u., (default 1, optional)
             *     
             *     The Output Parameter:
             *     
             *     - vertex.RealPower()                     - p                     - in MW, real power at bus (positive if generation)
             *     - vertex.ReactivePower                   - q                     - in MVar, reactive power at bus (positive if generation)
             *     -                                        - p_nom_opt             - in MW, optimized nominal power (default, 0)
             *     - vertex.Status()                        - status                - Status on or off (default, 1)
             *     
             *     - vertex.Weight()                        - weight
             *  }
             *
             * @return     @p True if the parsing was successful, @p False otherwise.
             */
            inline bool ReadGenerators ( TNetwork          & network
                                       , std::string const & filename ) 
            {
                QFile file( QString::fromStdString(filename + "/" + filenameGenerators_) );
                OpenFile(file);
                QList<QByteArray> splitted = ReadLine( file );

                dataMapperGenerators_.clear();
                ExtractGeneratorHeader( splitted );

                while( !file.atEnd() ) 
                {
                    splitted = ReadLine( file, false );
                    TGeneratorProperties * generator = new TGeneratorProperties();
                    std::string temp;
                    
                    USAGE_ASSERT ( static_cast<Types::count>( splitted.size() ) == dataMapperGenerators_.size() );
                    
                    for ( Types::count counter = 0; 
                          counter < static_cast<Types::count>( splitted.size() ); 
                          ++counter 
                        ) 
                    {
                        temp = splitted[counter].toStdString();
                        (this->*dataMapperGenerators_[counter])( temp , generator);
                    } // for
                    Types::vertexId generatorId = Const::NONE;
                    if ( mapGeneratorName2BusName_.find(generator->Name()) != mapGeneratorName2BusName_.end() ) 
                    {
                        if ( mapBusName2VertexId_.find(mapGeneratorName2BusName_[generator->Name()]) != mapBusName2VertexId_.end() ) 
                        {
                            generatorId = network.AddGeneratorAt(mapBusName2VertexId_[mapGeneratorName2BusName_[generator->Name()]], *generator);
                        } else {
                            ESSENTIAL_ASSERT( false && "Bus name does not exist" );
                        }
                    } else {
                        ESSENTIAL_ASSERT( false && "Generator name does not exist" );
                    }
                    if ( mapGeneratorName2Identifier_.find(generator->Name()) == mapGeneratorName2Identifier_.end() ) 
                    {                        
                        mapGeneratorName2Identifier_[generator->Name()] = generatorId;
                    } else {
                        ESSENTIAL_ASSERT( false && "Generator name to identifier, Generator name duplicates" );   
                    }
                } // while
                network.UpdateGeneratorSnapshotSize();
                return true;
            }

            /**
             * @brief      Sets the generator default values.
             * @details    The description of the elements is as in 
             *     <a href="https://pypsa.org/doc/components.html">https://pypsa.org/doc/components.html</a>.
             *     
             * @I{
             *     - name 
             *     - constant
             *     - type               - Type of constraint (only "primary energy", i.e., limits on the usage of primary energy before generator conversion)
             *     - carrier_attribute
             *     - sense              - Constraints sense, meaning <=, >=, ==
             *     - constant           - Constant for the rhs
             *     - mu                 - Shadow price of global constraint
             *  }
             *     
             * @return     @p True if the parsing was successful, @p False otherwise.
             */
            inline bool ReadGlobalConstraints() 
            {
                throw std::runtime_error ( "Not implemented yet! Storage units are currently unsupported." );
                return true;
            }

            /**
             * @brief      Reads branch (lines) matrix.
             * @details    While reading each row of the matrix an arc is created and added
             *     to the network.
             *
             * @param      network   The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * @param[in]  filename  The filename.
             *
             * @tparam     Graph     A graph type such as PowerGrid or StaticGraph.
             * 
             * @I{
             *     edge.Name()                  = name                      -> in -, branch name (default -, required)
             *     edge.Source()                = bus0                      -> in -, source bus ID (default -, required)
             *     edge.Target()                = bus1                      -> in -, target bus ID (default -, required)
             *     edge.CapitalCost()           = capital_cost              -> in Dollar, capital cost (default 0, optional).
             *                                                                            Capital cost of extending s_nom by 1 MVA.
             *     edge.Length()                = length                    -> in ?, length of this track (default 0, optional).
             *                                                                       Length of line used when "type" is set, also useful for calculating the capital cost.
             *     edge.NumberOfParallelLines() = num_parallel              -> in -, number of parallel lines at this branch (default 1, optional).
             *                                                                       When “type” is set, this is the number of parallel lines (can also be fractional). 
             *                                                                       If “type” is empty “” this value is ignored.
             *     edge.ThermalLimit()          = s_max_pu                  -> in p.u., thermal limit (default 1, optional).
             *                                                                          The maximum allowed absolute flow per unit of s_nom for the OPF (e.g. can be set <1 
             *                                                                          to approximate n-1 factor, or can be time-varying to represent weather-dependent dynamic 
             *                                                                          line rating for overhead lines).
             *     edge.NominalApparentPower()  = s_nom                     -> in MW or MVAR, nominal apparent power (default 0, optional). 
             *                                                                              Limit of apparent power which can pass through branch.
             *     edge.Type()                  = type                      -> in -, name of branch standard type (default ?, ?). 
             *                                                                       If this is not an empty string “”, then the line standard type impedance parameters 
             *                                                                       are multiplied with the line length and divided/multiplied by num_parallel to compute 
             *                                                                       x, r, etc. This will override any values set in r, x, and b. If the string is empty, 
             *                                                                       PyPSA will simply read r, x, etc.
             *     edge.NominalVoltage()        = v_nom                     -> in V, nominal voltage, basekv (default ?, ?)
             *     edge.NominalApparentPowerBound().Minimum() = s_nom_min   -> in MW or MVAr, minimum nominal apparent power (default 0, optional).
             *                                                                              If s_nom is extendable in OPF, set its minimum value.
             *     edge.NominalApparentPowerBound().Maximum() = s_nom_max   -> in MW or MVAr, maximum nominal apparent power (default inf, optional).
             *                                                                              If s_nom is extendable in OPF, set its maximum value (e.g. limited by potential).
             *     edge.Reactance()             = x                         -> in Ohm,  series reactance (default 0, optional), 
             *                                                                          must be non-zero for AC branch in linear power flow. 
             *                                                                          If the line has series inductance L in Henries then x = 2\pi f L where f is the frequency in 
             *                                                                          Hertz. Series impedance z = r + jx must be non-zero for the non-linear power flow. Ignored if 
             *                                                                          type defined.
             *     edge.Resistance()            = r                         -> in Ohm, series resistance (default 0, optional), 
             *                                                                         must be non-zero for DC branch in linear power flow. Series impedance z = r + jx must be non-zero 
             *                                                                         for the non-linear power flow. Ignored if type defined. 
             *     edge.Conductance()           = g                         -> in Siemens, shunt conductance (default 0, optional), 
             *                                                                             calculated by resistance and reactance dependent on the model (DC or AC), shunt admittance is 
             *                                                                             y = g + jb and g = r / (x^2 + r^2).
             *     edge.Susceptance()           = b                         -> in Siemens, shunt susceptance (default 0, optional), 
             *                                                                             calculated by resistance and reactance dependent on the model (DC or AC), if the 
             *                                                                             line has shunt capacitance C in Farads then b = 2\pi f C, where f is the frequency 
             *                                                                             in Hertz. Shunt admittance is y = g + jb and b = X / (r^2 + x^2). Ignored if type defined.
             *     edge.NominalApparentPowerExtendable() = s_nom_extendable -> in MW or VAR, nominal apparent power (default false, optional).
             *                                                                              Switch to allow capacity s_nom to be extended in OPF.
             *     edge.TerrainFactor           = terrain_factor            -> in -, terrain factor (default 0, ?).
             *                                                                       Terrain factor for increasing capital cost.
             *     edge.ThetaBound().Minimum()  = v_ang_min                 -> in Rad, minimum voltage angle (default -inf, optional).
             *                                                                         Minimum voltage angle difference across the line. This is a placeholder attribute and is not currently 
             *                                                                         used by any PyPSA functions.
             *     edge.ThetaBound().Maximum()  = v_ang_max                 -> in Rad, maximum voltage angle (default  inf, optional).
             *                                                                         Maximum voltage angle difference across the line. This is a placeholder attribute and is not currently 
             *                                                                         used by any PyPSA functions.
             *                                                                         
             *     [Out]                = sub_network           -> Subnetwork. Name of connected sub-network to which lines belongs. This attribute is set by PyPSA in the function 
             *                                                                 network.determine_network_topology(); do not set it directly by hand.
             *     [Out]                = p0                    -> in MW (default 0).
             *                                                     Active power at bus0 (positive if branch is withdrawing power from bus0).
             *     [Out]                = q0                    -> in MVar (default 0).
             *                                                     Reactive power at bus0 (positive if branch is withdrawing power from bus0).
             *     [Out]                = p1                    -> in MW (default 0).
             *                                                     Active power at bus1 (positive if branch is withdrawing power from bus1).
             *     [Out]                = q1                    -> in MVar (default 0).
             *                                                     Reactive power at bus1 (positive if branch is withdrawing power from bus1).
             *     [Out]                = x_pu                  -> in p.u. (default 0).
             *                                                     Per unit series reactance calculated by PyPSA from x and bus.v_nom.
             *     [Out]                = r_pu                  -> in p.u. (default 0).
             *                                                     Per unit series resistance calculated by PyPSA from r and bus.v_nom.
             *     [Out]                = g_pu                  -> in p.u. (default 0).
             *                                                     Per unit shunt conductivity calculated by PyPSA from g and bus.v_nom.
             *     [Out]                = b_pu                  -> in p.u. (default 0).
             *                                                     Per unit shunt susceptance calculated by PyPSA from b and bus.v_nom.
             *     [Out]                = x_pu_eff              -> in p.u. (default 0).
             *                                                     Effective per unit series reactance for linear power flow, calculated by PyPSA from x, tap_ratio for transformers and bus.v_nom.
             *     [Out]                = r_pu_eff              -> in p.u. (default 0).
             *                                                     Effective per unit series resistance for linear power flow, calculated by PyPSA from x, tap_ratio for transformers and bus.v_nom.
             *     [Out]                = s_nom_opt             -> in MVA (default 0).
             *                                                     Optimized capacity for apparent power.
             *     [Out]                = mu_lower              -> in currency/MVA (default 0).
             *                                                     Shadow price of lower s_nom limit -F leq f. Always non-negative.
             *     [Out]                = mu_upper              -> in currency/MVA (default 0).
             *                                                     Shadow price of upper s_nom limit f leq F. Always non-negative.
             *  }
             *
             * @return     @p True if the parsing was successful, @p False otherwise.
             */
            template<typename Graph = TNetwork>
            inline bool ReadLines ( Graph             & network
                                  , const std::string & filename ) 
            {
                QFile file( QString::fromStdString ( filename + "/" + filenameLines_ ) );
                OpenFile(file);
                QList<QByteArray> splitted = ReadLine( file );

                dataMapperLines_.clear();
                ExtractLineHeader( splitted );

                while( !file.atEnd() ) 
                {
                    splitted = ReadLine( file, false );
                    TIoEdge edge;
                    SetLineDefaultValues ( edge );
                    std::string temp;

                    USAGE_ASSERT ( static_cast<Types::count>( splitted.size() ) == dataMapperLines_.size() );

                    for ( Types::count counter = 0
                        ; counter < static_cast<Types::count>( splitted.size() )
                        ; ++counter ) 
                    {
                        temp = splitted[counter].toStdString();
                        (this->*dataMapperLines_[counter])( temp , edge );
                    } // for
                    AddEdge<Graph>( network, edge );
                } // while
                return true;
            }

            /**
             * @brief      Sets the branch default values.
             * @details    The description of the elements is as in 
             *     <a href="https://pypsa.org/doc/components.html">https://pypsa.org/doc/components.html</a>.
             *
             * @I{  The setting is as following:
             * 
             *      Name in EGOA                            Default                 Name in PyPSA   Description
             *      
             *      - Status()                              - true
             *      - Type()                                - Edge::ElectricalEdgeType::standard        type (default: -). Name of line standard type. If this is not an empty string “”, then the line standard type impedance parameters are multiplied with the line length and divided/multiplied by num_parallel to compute x, r, etc. This will override any values set in r, x, and b. If the string is empty, PyPSA will simply read r, x, etc. 
             *      - Reactance()                           - 0                     x                   Series reactance; must be non-zero for AC branch in linear power flow. If the line has series inductance L in Henries then x = 2\pi f L where f is the frequency in Hertz. Series impedance z = r + jx must be non-zero for the non-linear power flow. Ignored if type defined. 
             *      - Resistance()                          - 0                     r                   Series resistance; must be non-zero for DC branch in linear power flow. Series impedance z = r + jx must be non-zero for the non-linear power flow. Ignored if type defined. 
             *      // calculated by r and x
             *      - Conductance(0.0)                      - 0                     g                   Shunt conductivity. Shunt admittance is y = g + jb. 
             *      - Susceptance(0.0)                      - 0                     b                   Shunt susceptance. If the line has shunt capacitance C in Farads then b = 2\pi f C where f is the frequency in Hertz. Shunt admittance is y = g + jb. Ignored if type defined. 
             *      - NominalApparentPower()                - 0.0                   s_nom               Limit of apparent power which can pass through branch. 
             *      - NominalApparentPowerExtendable()      - false                 s_nom_extendable    Switch to allow capacity s_nom to be extended in OPF. 
             *      - NominalApparentPowerBound().Minimum() - 0.0                   s_nom_min           If s_nom is extendable in OPF, set its minimum value. 
             *      - NominalApparentPowerBound().Maximum() - Const::REAL_INFTY     s_nom_max           If s_nom is extendable in OPF, set its maximum value (e.g. limited by potential).
             *      - ThermalLimit()                        - 1.0                   s_max_pu            The maximum allowed absolute flow per unit of s_nom for the OPF (e.g. can be set <1 to approximate n-1 factor, or can be time-varying to represent weather-dependent dynamic line rating for overhead lines).
             *      - CapitalCost()                         - 0.0                   capital_cost        Capital cost of extending s_nom by 1 MVA. 
             *      - Length()                              - 0.0                   length              Length of line used when “type” is set, also useful for calculating the capital cost. 
             *      - TerrainFactor()                       - 0.0                   terrain_factor      Terrain factor for increasing capital cost. 
             *      - NumberOfParallelLines()               - 1.0                   num_parallel        When “type” is set, this is the number of parallel lines (can also be fractional). If “type” is empty “” this value is ignored. 
             *      - ThetaBound().Minimum()                - -Const::REAL_INFTY    v_ang_min           Minimum voltage angle difference across the line. This is a placeholder attribute and is not currently used by any PyPSA functions. 
             *      - ThetaBound().Minimum()                -  Const::REAL_INFTY    v_ang_max           Maximum voltage angle difference across the line. This is a placeholder attribute and is not currently used by any PyPSA functions.
             *      
             *      - sub_network      -       Name of connected sub-network to which lines belongs. This attribute is set by PyPSA in the function network.determine_network_topology(); do not set it directly by hand.
             *      - p0               0       Active power at bus0 (positive if branch is withdrawing power from bus0). 
             *      - q0               0       Reactive power at bus0 (positive if branch is withdrawing power from bus0). 
             *      - p1               0       Active power at bus1 (positive if branch is withdrawing power from bus1). 
             *      - q1               0       Reactive power at bus1 (positive if branch is withdrawing power from bus1). 
             *      - x_pu             0       Per unit series reactance calculated by PyPSA from x and bus.v_nom. 
             *      - r_pu             0       Per unit series resistance calculated by PyPSA from r and bus.v_nom 
             *      - g_pu             0       Per unit shunt conductivity calculated by PyPSA from g and bus.v_nom 
             *      - b_pu             0       Per unit shunt susceptance calculated by PyPSA from b and bus.v_nom 
             *      - x_pu_eff         0       Effective per unit series reactance for linear power flow, calculated by PyPSA from x, tap_ratio for transformers and bus.v_nom. 
             *      - r_pu_eff         0       Effective per unit series resistance for linear power flow, calculated by PyPSA from x, tap_ratio for transformers and bus.v_nom. 
             *      - s_nom_opt        0       Optimised capacity for apparent power. 
             *      - mu_lower         0       Shadow price of lower s_nom limit -F leq f. Always non-negative.
             *      - mu_upper         0       Shadow price of upper s_nom limit f leq F. Always non-negative.
             *      
             *  }
             *  
             * @param      edge  The edge object.
             */
            inline void SetLineDefaultValues( TIoEdge & edge ) 
            {
                edge.Properties().Status()      = true;
                edge.Properties().Type()        = Edges::ElectricalEdgeType::standard;
                edge.Properties().Reactance()   = 0;       
                edge.Properties().Resistance()  = 0;
                
                // calculated by r and x
                edge.Properties().Conductance(0.0);
                edge.Properties().Susceptance(0.0);
                
                edge.Properties().TapRatio()                             = 1;
                edge.Properties().NominalApparentPower()                 = 0.0;
                edge.Properties().NominalApparentPowerExtendable()       = false;
                edge.Properties().NominalApparentPowerBound().Minimum()  = 0.0;
                edge.Properties().NominalApparentPowerBound().Maximum()  = Const::REAL_INFTY;
                edge.Properties().ThermalLimit()                         = 1.0;
                edge.Properties().CapitalCost()                          = 0.0;
                edge.Properties().Length()                               = 0.0;
                edge.Properties().TerrainFactor()                        = 0.0;
                edge.Properties().NumberOfParallelLines()                = 1.0;
                edge.Properties().ThetaBound().Minimum()                 = -Const::REAL_INFTY;
                edge.Properties().ThetaBound().Maximum()                 =  Const::REAL_INFTY;
            }

            /**
             * @brief      Read loads real power set.
             * @details    While reading each row of the matrix a real power
             *     load is added to the network.
             *
             * @I{
             *     ?? = name   (represents the time stamp of the load)
             *     ?? = AT0 0  (represents the real power load at load "AT0 0" for time stamp "name")
             *     ?? = AT0 1
             *     ?? = ...
             *     ?? = AT0 k
             *     
             *     where k is the number of loads specified in "loads.csv"
             *  }
             *
             * @param      network   The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * @param      filename  The filename.
             *
             * @return     @p True if the parsing was successful, @p False otherwise.
             */
            inline bool ReadLoadsPset ( TNetwork          & network
                                      , std::string const & filename ) 
            {
                QFile file( QString::fromStdString(filename + "/" + filenameLoadsPSet_) );
                OpenFile(file);
                QList<QByteArray> splitted = ReadLine( file, false );
                
                dataMapperLoadsRealPowerMaxPu_.clear();
                ExtractLoadMaximumRealPowerPuHeader( splitted );

                while( !file.atEnd() ) 
                {
                    splitted = ReadLine( file, false );
                    std::string loadValue;

                    USAGE_ASSERT ( static_cast<Types::count>( splitted.size() ) == dataMapperLoadsRealPowerMaxPu_.size() );
                    if ( !splitted[0].isEmpty() )
                    {
                        ++ loadSnapshotsSize;
                    }

                    for ( Types::count counter = 0
                        ; counter < static_cast<Types::count>( splitted.size() )
                        ; ++counter ) 
                    {
                        loadValue = splitted[counter].toStdString();
                        dataMapperLoadsRealPowerMaxPu_[counter]( loadValue, network );
                    } // for
                } // while
                return true;
            }

            /**
             * @brief      Read the load matrix that is a mapping of load to bus.
             * @details    While reading each row of the matrix a mapping between load and bus is made 
             *     and thus, the load is added to the network.
             *
             * @I{
             *     load.Name()  = name    (represents the name of the load)
             *                  = bus     (represents the name of the bus)
             *     load.Type()  = type
             *                  = p_set
             *                  = q_set
             *                  = sign
             *     
             *     [out]
             *                  = p
             *                  = q
             *  }
             *
             * @param      network   The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * @param      filename  The filename.
             *
             * @return     @p True if the parsing was successful, @p False otherwise.
             */
            inline bool ReadLoads ( TNetwork          & network
                                  , std::string const & filename ) 
            {
                QFile file( QString::fromStdString(filename + "/" + filenameLoads_) );
                OpenFile(file);
                QList<QByteArray> splitted = ReadLine( file );
                Types::index busColumn(0);
                
                dataMapperLoads_.clear();
                ExtractLoadHeader( splitted, busColumn );
                
                while( !file.atEnd() ) 
                {
                    splitted = ReadLine( file, false );
                    TLoadProperties vertex;
                    SetLoadDefaultValues(vertex);
                    Types::string temp;

                    USAGE_ASSERT ( static_cast<Types::count>( splitted.size() ) == dataMapperLoads_.size() );
                    
                    // Read a row
                    for ( Types::count counter = 0
                        ; counter < static_cast<Types::count>( splitted.size() )
                        ; ++counter ) 
                    {
                        temp = splitted[counter].toStdString();
                        (this->*dataMapperLoads_[counter])( temp , vertex);
                    } // for each column in a row

                    Types::loadId loadId = Const::NONE;
                    if (mapBusName2VertexId_.find( splitted[ busColumn ].toStdString() ) != mapBusName2VertexId_.end() ) 
                    {
                        loadId = network.AddLoadAt( mapBusName2VertexId_[ splitted[ busColumn ].toStdString() ], vertex );
                    } else {
                        ESSENTIAL_ASSERT( false && "Bus name does not exist" );
                    }
                    
                    if ( mapLoadName2Identifier_.find( vertex.Name() ) == mapLoadName2Identifier_.end() ) {
                        mapLoadName2Identifier_[vertex.Name()]  = loadId;    
                    } else {
                        ESSENTIAL_ASSERT( false && "Load name duplicates" );
                    }
                    
                } // while
                return true;
            }

            /**
             * @brief      Sets the load default values.
             * @details    The description of the elements is as in 
             *     <a href="https://pypsa.org/doc/components.html">https://pypsa.org/doc/components.html</a>.
             *     
             * @I{
             *     vertex.Type()    Vertices::IeeeBusType::load
             *     p_set            0       real power consumption
             *     q_set            0       reactive power consumption
             *     sign             -1      power sign
             *     
             *     Output Parameter:
             *     p                0       real power
             *     q                0       reactive power
             *  }
             *
             * @param      vertex  The load vertex object.
             */
            inline void SetLoadDefaultValues ( TLoadProperties & vertex ) 
            {
                vertex.Type()   = Vertices::IeeeBusType::load;
            }

            /**
             * @brief      Reads a network.
             * @details    The description of the elements is as in 
             *     <a href="https://pypsa.org/doc/components.html">https://pypsa.org/doc/components.html</a>.
             *     
             * @I{
             *     - name
             *     - pypsa_version
             *     - srid 
             *  }
             *
             * @param      network  The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             *
             * @return     @p True if the parsing was successful, @p False otherwise.
             */
            inline bool ReadNetwork( TNetwork & network ) 
            {
                throw std::runtime_error ( "Not implemented yet! Storage units are currently unsupported." );
                return true;
            }

            /**
             * @brief      Reads snapshots.
             * @details    The description of the elements is as in 
             *     <a href="https://pypsa.org/doc/components.html">https://pypsa.org/doc/components.html</a>.
             * 
             * @I{
             *     name        - Time stamp
             *     weightings  - Weighting of the time stamp
             *  }
             *
             * @param      network  The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             *
             * @return     @p True if the parsing was successful, @p False otherwise.
             */
            inline bool ReadSnapshots( TNetwork & network ) 
            {
                throw std::runtime_error ( "Not implemented yet! Snapshots weightings are currently unsupported." );
                // if ( !splitted[0].empty() )
                // {
                //     ++ snapshotsSize;
                // }
                return true;
            }

            /**
             * @brief      Reads a complete network.
             *
             * @param      network   The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * @param[in]  filename  The filename.
             *
             * @return     @p true if the parsing was successful, @p false otherwise.
             */
            inline bool ReadCompleteNetwork ( TNetwork          & network
                                            , std::string const & filename ) 
            {
                network.BaseMva() = 1.0;
                return ReadBuses ( network, filename )
                    && ReadGenerators ( network, filename )
                    && ReadGeneratorsRealPowerMaxPu ( network, filename )
                    && ReadLines ( network.Graph(), filename )
                    && ReadLoads ( network, filename )
                    && ReadLoadsPset ( network, filename )
                    && HasCorrectSnapshotSizes()
                    && IO::Helper::HasNetworkCorrectBounds<TNetwork> ( network );
            }

            /**
             * @brief      Reads a complete network and a candidate network.
             *
             * @param      network           The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * @param      candidateNetwork  The candidate network @f$\graph = (\vertices, \edges_{\mathrm{cand}})@f$.
             * @param[in]  filename          The filename.
             *
             * @return     @p true if the parsing was successful, @p false otherwise.
             */
            inline bool ReadCompleteNetwork ( TNetwork          & network
                                            , TGraph            & candidateNetwork
                                            , std::string const & filename ) 
            {
                network.BaseMva() = 1.0;
                bool booleanBuses = ReadBuses ( network, filename );
                candidateNetwork  = network.Graph();
                
                return booleanBuses
                    && ReadGenerators ( network, filename ) 
                    && ReadGeneratorsRealPowerMaxPu ( network, filename )
                    && ReadLines ( network, filename )
                    && ReadLines<TGraph> ( candidateNetwork, filename )
                    && ReadLoads ( network, filename )
                    && ReadLoadsPset ( network, filename )
                    && HasCorrectSnapshotSizes()
                    && IO::Helper::HasNetworkCorrectBounds<TNetwork> ( network )
                    && IO::Helper::HasGraphCorrectBounds<TGraph> ( candidateNetwork );
            }
        ///@}
 
    public: 
        ///@name Reader
        ///@{
#pragma mark READER

            /**
             * @brief      Read network @f$ \network @f$ from file.
             *
             * @param      network   The network network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * @param      filename  The filename @f$\graph = (\vertices, \edges_{\mathrm{cand}})@f$.
             *
             * @return     @p true if the parsing was successful, @p false otherwise.
             */
            bool read ( TNetwork          & network
                      , std::string const & filename ) 
            {
                return ReadCompleteNetwork ( network, filename );
            }

            /**
             * @brief      Read network and candidate network from file 
             *
             * @param      network           The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * @param      candidateNetwork  The candidate network
             * @param      filename          The filename.
             *
             * @return     @p true if the parsing was successful, @p false otherwise.
             */
            bool read   ( TNetwork          & network
                        , TGraph            & candidateNetwork
                        , std::string const & filename ) 
            {
                return ReadCompleteNetwork ( network, candidateNetwork, filename );
            }
        ///@}

    private: 
        ///@name Auxiliary
        ///@{
#pragma mark AUXILIARY

            /**
             * @brief      Wrapper for adding a vertex.
             *
             * @param      network           The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * @param      vertexProperties  The vertex properties.
             *
             * @tparam     Graph             The graph type, e.g., PowerGrid.
             *
             * @return     The vertex identifier of a vertex.
             */
            template<typename Graph = TNetwork>
            inline Types::vertexId AddVertex ( Graph                   & network
                                             , TVertexProperties const & vertexProperties  )
            {
                return internal::NetworkDifferentiation<TVertexProperties, TEdgeProperties, Graph>::AddVertex ( network
                                                                                                              , vertexProperties );
            }

            /**
             * @brief      Wrapper for adding an edge.
             *
             * @param      network  The network  @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * @param      ioEdge   The i/o edge
             *
             * @tparam     Graph    The graph type, e.g., PowerGrid.
             *
             * @return     The edge identifier of a edge.
             */
            template<typename Graph = TNetwork>
            inline Types::edgeId AddEdge ( Graph         & network
                                         , TIoEdge const & ioEdge )
            {
                return internal::NetworkDifferentiation<TVertexProperties, TEdgeProperties, Graph>::AddEdge ( network
                                                                                                            , ioEdge );
            }

            /**
             * @brief      Reads a line.
             *
             * @param      file      The file.
             * @param[in]  compress  The compress.
             *
             * @return     The line as array, where each field represents a
             *     column entry.
             */
            inline QList<QByteArray> ReadLine ( QFile & file
                                              , bool    compress = true ) 
            {
                QByteArray  line = file.readLine();
                if ( compress ) CompressString( line);
                line = line.trimmed();
                return line.split(',');            
            }

            /**
             * @brief      Compress the string by removing spaces.
             *
             * @param      list  The list.
             */
            inline void CompressString ( QByteArray & list ) 
            {
                list = list.replace(" ","");
            }

            /**
             * @brief      Opens a file.
             *
             * @param      file  The file.
             *
             * @return     @p true file could be opened, @p false otherwise.
             */
            inline bool OpenFile ( QFile & file ) 
            {
                if (!file.open(QIODevice::ReadOnly)) 
                {
                    qDebug() << file.errorString();
                    return false; // TODO throw exception
                }
                return true;
            }

            /**
             * @brief      Check if the snapshot size maps.
             *
             * @return     @p true the snapshot size maps, @p false otherwise.
             */
            inline bool HasCorrectSnapshotSizes()
            {
                USAGE_ASSERT ( generatorSnapshotsSize == loadSnapshotsSize );
                return (generatorSnapshotsSize == loadSnapshotsSize);
            }
        ///@}

        ///@name Header extraction
        ///@{
#pragma mark EXTRACT_HEADER

            /**
             * @brief      Extract the bus header.
             * @details    Dependent on the data some columns exist and some
             *     are missing. This method dynamically extracts the existing
             *     data.
             *
             * @param      splitted  The splitted line.
             *
             * @return     @p true if the extraction was successful, @p false otherwise.
             */
            inline bool ExtractBusHeader( QList<QByteArray> const & splitted ) 
            {
                for ( Types::count counter = 0
                    ; counter < static_cast<Types::count>( splitted.size() )
                    ; ++counter ) 
                {
                    if ( splitted[counter] == "name" )
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddBusName );
                    } else if ( splitted[counter] == "v_nom" ) 
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddNominalVoltageToVertexProperty );
                    } else if ( splitted[counter] == "x" ) 
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddXcoordinateToVertexProperty );
                    } else if ( splitted[counter] == "y" ) 
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddYcoordinateToVertexProperty );
                    } else if ( splitted[counter] == "carrier" ) 
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddCarrierToVertexProperty );
                    } else if ( splitted[counter] == "country" ) 
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddCountryToVertexProperty );
                    } else if ( splitted[counter] == "v_mag_pu_set" ) 
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddVoltageMagnitudePuSetPointToVertexProperty );
                    } else if ( splitted[counter] == "v_mag_pu_min" ) 
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddMinimumVoltageMagnitudePuToVertexProperty );
                    } else if ( splitted[counter] == "v_mag_pu_max" ) 
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddMaximumVoltageMagnitudePuToVertexProperty );
                    } else if ( splitted[counter] == "control" ) 
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddControlTypeToVertexProperty );
                    } else if ( splitted[counter] == "sub_network" ) 
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddSubnetworkToVertexProperty );
                    } else if ( splitted[counter] == "p" ) 
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddRealPowerToVertexProperty );
                    } else if ( splitted[counter] == "q" ) 
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddReactivePowerToVertexProperty );
                    } else if ( splitted[counter] == "v_mag_pu" ) 
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddVoltageMagnitudePuToVertexProperty );
                    } else if ( splitted[counter] == "v_ang" ) 
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddVoltageAngleToVertexProperty );
                    } else if ( splitted[counter] == "marginal_price" ) 
                    {
                        dataMapperBuses_.emplace_back( &PyPsaParser::AddMarginalPriceToVertexProperty );
                    } // if
                } // for

            return true;
            }

            /**
             * @brief      Extract the line (branch) header.
             * @details    Dependent on the data some columns exist and some
             *     are missing. This method dynamically extracts the existing
             *     data.
             *     
             * @param      splitted  The splitted line.
             *
             * @return     @p true if the extraction was successful, @p false otherwise.
             */
            inline bool ExtractLineHeader( QList<QByteArray> const & splitted ) 
            {
                for ( Types::count counter = 0
                    ; counter < static_cast<Types::count>( splitted.size() )
                    ; ++counter ) 
                {
                    if ( splitted[counter] == "name" )
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddNameToEdge );
                    } else if ( splitted[counter] == "bus0" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddSourceVertexToEdge );
                    } else if ( splitted[counter] == "bus1" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddTargetVertexToEdge );
                    } else if ( splitted[counter] == "capital_cost" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddCapitalCostToEdge );
                    } else if ( splitted[counter] == "length" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddLengthToEdge );
                    } else if ( splitted[counter] == "num_parallel" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddNumberOfParallelLinesToEdge );
                    } else if ( splitted[counter] == "s_max_pu" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddMaximumApparentPowerPuToEdge );
                    } else if ( splitted[counter] == "s_nom" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddNominalApparentPowerToEdge );
                    } else if ( splitted[counter] == "type" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddLineTypeToEdge );
                    } else if ( splitted[counter] == "v_nom" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddNominalVoltageToEdge );
                    } else if ( splitted[counter] == "s_nom_min" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddMinimumNominalApparentPowerToEdge );
                    } else if ( splitted[counter] == "s_nom_max" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddMaximalNominalApparentPowerToEdge );
                    } else if ( splitted[counter] == "x" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddReactanceToEdge );
                    } else if ( splitted[counter] == "r" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddResistanceToEdge );
                    } else if ( splitted[counter] == "g" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddConductanceToEdge );
                    } else if ( splitted[counter] == "b" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddSusceptanceToEdge );
                    } else if ( splitted[counter] == "s_nom_extendable" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddNominalExtendableApparentPowerToEdge );
                    } else if ( splitted[counter] == "terrain_factor" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddTerrainFactorToEdge );
                    } else if ( splitted[counter] == "v_ang_min" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddMinimumVoltageAngleToEdge );
                    } else if ( splitted[counter] == "v_ang_max" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddMaximumVoltageAngleToEdge );
                    } 
                    // [out]
                    else if ( splitted[counter] == "sub_network" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddSubnetworkToEdge );
                    } else if ( splitted[counter] == "p0" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddP0ToEdge );
                    } else if ( splitted[counter] == "q0" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddQ0ToEdge );
                    } else if ( splitted[counter] == "p1" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddP1ToEdge );
                    } else if ( splitted[counter] == "q1" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddQ1ToEdge );
                    } else if ( splitted[counter] == "x_pu" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddReactancePuToEdge );
                    } else if ( splitted[counter] == "r_pu" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddResistancePuToEdge );
                    } else if ( splitted[counter] == "g_pu" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddConductancePuToEdge );
                    } else if ( splitted[counter] == "b_pu" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddSusceptancePuToEdge );
                    } else if ( splitted[counter] == "x_pu_eff" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddEffectiveReactancePuToEdge );
                    } else if ( splitted[counter] == "r_pu_eff" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddEffectiveResistancePuToEdge );
                    } else if ( splitted[counter] == "s_nom_opt" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddOptimalNominalApparentPowerToEdge );
                    } else if ( splitted[counter] == "mu_lower" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddMuLowerToEdge );
                    } else if ( splitted[counter] == "mu_upper" ) 
                    {
                        dataMapperLines_.emplace_back( &PyPsaParser::AddMuUpperToEdge );
                    } // if
                } // for
                return true;
            }

            /**
             * @brief      Extract the generator header.
             * @details    Dependent on the data some columns exist and some
             *     are missing. This method dynamically extracts the existing
             *     data.
             *
             * @param      splitted  The splitted line.
             *
             * @return     @p true if the extraction was successful, @p false otherwise.
             */
            inline bool ExtractGeneratorHeader( QList<QByteArray> const & splitted ) 
            {
                for ( Types::count counter = 0
                    ; counter < static_cast<Types::count>( splitted.size() )
                    ; ++counter ) 
                {
                    if ( splitted[counter] == "name" )
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddNameToGenerator ); 
                    } else if ( splitted[counter] == "bus" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AssociateGeneratorWithBus );
                    } else if ( splitted[counter] == "control" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddControlTypeToGenerator );
                    } else if ( splitted[counter] == "type" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddTypeToGenerator );
                    } else if ( splitted[counter] == "efficiency" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddGeneratorEfficiencyToGenerator );
                    } else if ( splitted[counter] == "p_nom" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddNominalRealPowerToGenerator );
                    } else if ( splitted[counter] == "p_nom_extendable" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddNominalRealPowerToGeneratorExtendable );
                    } else if ( splitted[counter] == "p_nom_min" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddNominalRealPowerToGeneratorMin );
                    } else if ( splitted[counter] == "p_nom_max" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddNominalRealPowerToGeneratorMax );
                    } else if ( splitted[counter] == "p_min_pu" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddMinimumRealPowerPuToGenerator );
                    } else if ( splitted[counter] == "p_max_pu" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddMaximumRealPowerPuToGenerator );
                    } else if ( splitted[counter] == "p_set" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddRealPowerSetPointToGenerator );
                    } else if ( splitted[counter] == "q_set" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddReactivePowerSetPointToGenerator );
                    } else if ( splitted[counter] == "sign" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddGeneratorSignToGenerator );
                    } else if ( splitted[counter] == "carrier" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddCarrierToGenerator );
                    } else if ( splitted[counter] == "marginal_cost" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddMarginalCostToGenerator );
                    } else if ( splitted[counter] == "capital_cost" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddCapitalCostToGenerator );
                    } else if ( splitted[counter] == "committable" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddCommittabilityToGenerator );
                    } else if ( splitted[counter] == "start_up_cost" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddStartUpCostToGenerator );
                    } else if ( splitted[counter] == "shut_down_cost" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddShutDownCostToGenerator );
                    } else if ( splitted[counter] == "min_up_time" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddMinimumUpTimeToGenerator );
                    } else if ( splitted[counter] == "min_down_time" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddMinimumDownTimeToGenerator );
                    } else if ( splitted[counter] == "initial_status" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddInitialStatusToGenerator );
                    } else if ( splitted[counter] == "ramp_limit_up" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddRampLimitUpToGenerator );
                    } else if ( splitted[counter] == "ramp_limit_down" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddRampLimitDownToGenerator );
                    } else if ( splitted[counter] == "ramp_limit_start_up" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddRampLimitStartUpToGenerator );
                    } else if ( splitted[counter] == "ramp_limit_shut_down" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddRampLimitShutDownToGenerator );
                    } 
                    // [out]
                    else if ( splitted[counter] == "p" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddRealPowerToGenerator );
                    } else if ( splitted[counter] == "q" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddReactivePowerToGenerator );
                    } else if ( splitted[counter] == "p_nom_opt" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddNominalRealPowerToGeneratorOpt );
                    } else if ( splitted[counter] == "status" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddStatusToGenerator );
                    } else if ( splitted[counter] == "weight" ) 
                    {
                        dataMapperGenerators_.emplace_back( &PyPsaParser::AddWeightToGenerator );
                    } // if
                } // for
                return true;
            }

            /**
             * @brief      Extract the existing generator maximum real power p.u. header.
             *
             * @param      splitted  The splitted string of one row/line.
             *
             * @return     @p true if the header could be extracted, @p false
             *     otherwise.
             */
            inline bool ExtractGeneratorMaximumRealPowerPuHeader( QList<QByteArray> const & splitted ) 
            {
                for ( Types::count counter = 0
                    ; counter < static_cast<Types::count>( splitted.size() )
                    ; ++counter ) 
                {
                    if ( splitted[counter] == "name" )
                    {
                        dataMapperGeneratorsRealPowerMaxPu_.emplace_back ( 
                            std::bind ( & PyPsaParser::AddTimestampOfGenerator
                                      , this 
                                      , std::placeholders::_1 // input string
                                      , std::placeholders::_2 // network
                                      )
                        );
                    } else 
                    {
                        std::string generatorName = splitted[counter].trimmed().toStdString();
                        // dataMapperGeneratorsRealPowerMaxPu_.emplace_back( std::bind(&PyPsaParser::AddMaximumRealPowerSnapshotPuToGenerator, std::placeholders::_1, mapGeneratorName2Generator_[generatorName]) );

                        if ( mapGeneratorName2Identifier_.find(generatorName) == mapGeneratorName2Identifier_.end() ) 
                        {
                            ESSENTIAL_ASSERT( false && "Generator name does not exist" );
                        }

                        dataMapperGeneratorsRealPowerMaxPu_.emplace_back ( 
                            std::bind ( & PyPsaParser::AddMaximumRealPowerSnapshotPuToGenerator
                                      , this
                                      , std::placeholders::_1 // input string
                                      , std::placeholders::_2 // network
                                      , mapGeneratorName2Identifier_[generatorName] ) ); // identifier
                    }
                } // for
                return true;
            }

            /**
             * @brief      Extract the existing load header data.
             *
             * @param      splitted  The splitted string of one row/line.
             * @param      column    The column
             *
             * @return     @p true if the header could be extracted, @p false
             *     otherwise.
             */
            inline bool ExtractLoadHeader ( QList<QByteArray> const & splitted
                                          , Types::index            & column ) 
            {
                for ( Types::count counter = 0
                    ; counter < static_cast<Types::count>( splitted.size() )
                    ; ++counter ) 
                {
                    if ( splitted[counter] == "name" )
                    {
                        dataMapperLoads_.emplace_back( &PyPsaParser::AddNameToLoad );
                    } else if ( splitted[counter] == "bus" )
                    {
                        dataMapperLoads_.emplace_back( &PyPsaParser::AssociateLoadWithVertex );
                        column = counter;
                    } else if ( splitted[counter] == "type" )
                    {
                        dataMapperLoads_.emplace_back( &PyPsaParser::AddTypeToLoad );
                    } else if ( splitted[counter] == "p_set" )
                    {
                        dataMapperLoads_.emplace_back( &PyPsaParser::AddRealPowerSetPointToLoad );
                    } else if ( splitted[counter] == "q_set" )
                    {
                        dataMapperLoads_.emplace_back( &PyPsaParser::AddReactivePowerSetPointToLoad );
                    } else if ( splitted[counter] == "sign" )
                    {
                        dataMapperLoads_.emplace_back( &PyPsaParser::AddSignToLoad );
                    } else if ( splitted[counter] == "p" )
                    {
                        dataMapperLoads_.emplace_back( &PyPsaParser::AddRealPowerToLoad );
                    } else if ( splitted[counter] == "q" )
                    {
                        dataMapperLoads_.emplace_back( &PyPsaParser::AddReactivePowerToLoad );
                    }
                } // for
                return true;
            }

            /**
             * @brief      Extract load maximum real power p.u.
             *
             * @param      splitted  The splitted string of one row/line.
             *
             * @return     @p true if the header could be extracted, @p false otherwise.
             */
            inline bool ExtractLoadMaximumRealPowerPuHeader( QList<QByteArray> const & splitted ) 
            {
                for ( Types::count counter = 0
                    ; counter < static_cast<Types::count>( splitted.size() )
                    ; ++counter ) 
                {
                    if ( splitted[counter] == "name" )
                    {
                        dataMapperLoadsRealPowerMaxPu_.emplace_back( 
                            std::bind ( &PyPsaParser::AddLoadTimestampName 
                                      , this
                                      , std::placeholders::_1 // input string
                                      , std::placeholders::_2 // network
                                      )
                        );
                    } else 
                    {
                        std::string loadName = splitted[counter].toStdString();
                        
                        if ( mapLoadName2Identifier_.find(loadName) == mapLoadName2Identifier_.end() ) 
                        {
                            ESSENTIAL_ASSERT( false && "Load name does not exist" );
                        }

                        dataMapperLoadsRealPowerMaxPu_.emplace_back( 
                            std::bind ( &PyPsaParser::AddMaximumRealPowerSnapshotPuToLoad
                                      , this
                                      , std::placeholders::_1 // input string
                                      , std::placeholders::_2 // network
                                      , mapLoadName2Identifier_[loadName] ) ); // identifier
                    }
                } // for
                return true;
            }
        ///@}

#pragma mark FUNCTION_POINTER_VECTOR_WITH_FUNCTION_POINTER

        std::vector<TGeneratorProperties*> headerGeneratorMaximumRealPowerPu_;   /**< */
        
        ///@name Function pointer types
        ///@{
            using ElectricalVertexFunc               = void (PyPsaParser::*)( Types::name const & , TVertexProperties& );

            using GeneratorVertexFunc                = void (PyPsaParser::*)(Types::name const & , TGeneratorProperties*);
            using GeneratorMaximumRealPowerPuFunc    = std::function<void(Types::string const &, TNetwork&)>;

            using LoadVertexFunc                     = void (PyPsaParser::*)(Types::name const & , TLoadProperties&);
            using LoadMaximumRealPowerPuFunc         = std::function<void(Types::string const &, TNetwork&)>;

            using ElectricalEdgeFunc                 = void (PyPsaParser::*)(Types::name const & , TIoEdge&);
        ///@}

        ///@name Mappers for Reading Data
        ///@{
            // std::vector<void *(*)(void *)>               dataMapperStorageUnitsInflows_;
            // std::vector<void *(*)(void *)>               dataMapperStorageUnits_;
            std::vector<ElectricalVertexFunc>               dataMapperBuses_;
            // std::vector<ElectricalEdgeFunc>              dataMapperCarrier_;
            std::vector<GeneratorMaximumRealPowerPuFunc>    dataMapperGeneratorsRealPowerMaxPu_;
            std::vector<GeneratorVertexFunc>                dataMapperGenerators_;
            // std::vector<void *(*)(void *)>               dataMapperGlobalConstraints_;

            std::vector<ElectricalEdgeFunc>                 dataMapperCandidateNetwork_; // dataMapperLinesNew_;
            std::vector<ElectricalEdgeFunc>                 dataMapperLines_;

            std::vector<LoadVertexFunc>                     dataMapperLoads_;
            std::vector<LoadMaximumRealPowerPuFunc>         dataMapperLoadsRealPowerMaxPu_;
            // std::vector<void *(*)(void *)>               dataMapperNetwork_;
            // std::vector<void *(*)(void *)>               dataMapperSnapshots_; //void *(*)(void *)
        ///@}

        ///@name Bus (also known as vertex) data
        ///@{
#pragma mark BUS_DATA_EXTRACTION

            /**
             * @brief      Add bus name to the vertex property.
             *
             * @param      name    The name.
             * @param      vertex  The vertex property.
             */
            void AddBusName ( Types::name  const & name
                                    , TVertexProperties & vertexProperty ) 
            { 
                vertexProperty.Name()   = name;                                   
            }

            /**
             * @brief      Add the nominal voltage to the vertex property.
             *
             * @param      voltageNominal  The nominal voltage.
             * @param      vertexProperty  The vertex property.
             */
            void AddNominalVoltageToVertexProperty ( Types::name const & voltageNominal
                                    , TVertexProperties & vertexProperty ) 
            {   
                if ( !voltageNominal.empty() ) 
                {
                    if ( voltageNominal.compare("inf") != 0 ) 
                    { // not inf
                        vertexProperty.NominalVoltage() = Types::String2double( voltageNominal );
                    } else { //inf
                        vertexProperty.NominalVoltage() = Const::REAL_INFTY;
                    }
                } 
            }

            /**
             * @brief      Add the bus type to the vertex property.
             * 
             * @pre        Assume IEEE type.
             *
             * @param      type            The type.
             * @param      vertexProperty  The vertex property.
             * 
             * @note       Placeholder in PyPsa data, i.e., not used yet.
             */
            inline void AddBusTypeToVertexProperty ( Types::name const & type
                                    , TVertexProperties & vertexProperty ) 
            { 
                if ( !type.empty() ) 
                { 
                    vertexProperty.Type() = Vertices::StringToIeeeBusType ( type );
                }
            }

            /**
             * @brief      Add x-coordinate to the vertex property.
             *
             * @param      xCoordinate     The x-coordinate or the bus.
             * @param      vertexProperty  The vertex property.
             */
            inline void AddXcoordinateToVertexProperty ( Types::name const & xCoordinate
                                                       , TVertexProperties & vertexProperty ) 
            { 
                if ( !xCoordinate.empty() ) 
                {
                    vertexProperty.X()      = Types::String2double( xCoordinate );    
                } 
            }

            /**
             * @brief      Add y-coordinate to the vertex property.
             *
             * @param      yCoordinate     The y-coordinate or the bus.
             * @param      vertexProperty  The vertex property.
             */
            inline void AddYcoordinateToVertexProperty ( Types::name const & yCoordinate
                                 , TVertexProperties & vertexProperty ) 
            { 
                if ( !yCoordinate.empty() ) 
                {
                    vertexProperty.Y()      = Types::String2double( yCoordinate );
                } 
            }

            /**
             * @brief      Add carrier to the vertex property.
             *
             * @param      carrier         The carrier.
             * @param      vertexProperty  The vertex property.
             */
            inline void AddCarrierToVertexProperty ( Types::name const & carrier
                                                   , TVertexProperties & vertexProperty ) 
            {  
                if ( !carrier.empty() ) 
                {
                    vertexProperty.Carrier() = Vertices::StringToEnergyCarrier ( carrier );
                } 
            }

            /**
             * @brief      Add data country to the vertex property.
             *
             * @param      country         The country.
             * @param      vertexProperty  The vertex property.
             */
            inline void AddCountryToVertexProperty ( Types::name const & country
                                                   , TVertexProperties & vertexProperty ) 
            { // used in data but not specified
                if ( !country.empty() ) 
                {
                    vertexProperty.Country() = country;
                } 
            } 

            /**
             * @brief      Add voltage magnitude set point to the vertex property.
             *
             * @param      voltageMagnitudePuSetpoint  The voltage magnitude set point in p.u.
             * @param      vertexProperty              The vertex property.
             */
            inline void AddVoltageMagnitudePuSetPointToVertexProperty ( Types::name const & voltageMagnitudePuSetpoint
                                                                      , TVertexProperties & vertexProperty ) 
            { 
                if ( !voltageMagnitudePuSetpoint.empty() ) 
                {
                    if ( voltageMagnitudePuSetpoint.compare("inf") != 0 ) 
                    { // not inf
                        vertexProperty.VoltageMagnitude() = Types::String2double( voltageMagnitudePuSetpoint ); 
                    } else { //inf
                        vertexProperty.VoltageMagnitude() = Const::REAL_INFTY; 
                    }
                }
            }

            /**
             * @brief      Add minimum voltage magnitude to the vertex property.
             *
             * @param      voltageMagnitudePuMinimum  The minimum voltage magnitude in p.u.
             * @param      vertexProperty             The vertex property.
             */
            inline void AddMinimumVoltageMagnitudePuToVertexProperty ( Types::name const & voltageMagnitudePuMinimum
                                                                     , TVertexProperties & vertexProperty ) 
            {  
                if ( !voltageMagnitudePuMinimum.empty() ) 
                { /* vertex voltageMagnitudePuMinimum */
                    if ( voltageMagnitudePuMinimum.compare("inf") != 0 ) 
                    { // not inf
                        vertexProperty.MinimumVoltage() = Types::String2double( voltageMagnitudePuMinimum );
                    } else { //inf
                        vertexProperty.MinimumVoltage() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add maximum voltage to the vertex property.
             *
             * @param      voltageMagnitudePuMaximum  The maximum voltage magnitude in p.u.
             * @param      vertexProperty             The vertex property.
             */
            inline void AddMaximumVoltageMagnitudePuToVertexProperty ( Types::name const & voltageMagnitudePuMaximum
                                                                     , TVertexProperties & vertexProperty ) 
            {  
                if ( !voltageMagnitudePuMaximum.empty() ) 
                { /* vertex voltageMagnitudePuMaximum */
                    if ( voltageMagnitudePuMaximum.compare("inf") != 0 ) 
                    { // not inf
                        vertexProperty.MaximumVoltage() = Types::String2double( voltageMagnitudePuMaximum );
                    } else { //inf
                        vertexProperty.MaximumVoltage() = Const::REAL_INFTY;
                    }
                }
            }
        ///@}

        ///@name Vertex data output
        ///@{
#pragma mark BUS_DATA_OUTPUT

            /**
             * @brief      Add the control type to the vertex property.
             *
             * @param      control         The control type of the bus.
             * @param      vertexProperty  The vertex property.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddControlTypeToVertexProperty ( Types::string const & control
                                                       , TVertexProperties   & vertexProperty ) 
            {  
                if ( !control.empty() ) 
                { /* vertex control */
                    vertexProperty.Control() = Vertices::StringToControlType ( control );
                }
            }

            /**
             * @brief      Add the subnetwork to the vertex property.
             *
             * @param      subnetwork      The subnetwork.
             * @param      vertexProperty  The vertex property.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddSubnetworkToVertexProperty ( Types::name const & subnetwork
                                                      , TVertexProperties & vertexProperty ) 
            {  
                if ( !subnetwork.empty() ) 
                {
                    if ( subnetwork.compare("inf") != 0 ) 
                    { // not inf
                        /* vertex subnetwork */
                    } else { //inf
                        /* vertex subnetwork */
                    }
                }
            }

            /**
             * @brief      Add the real power to the vertex property.
             *
             * @param      realPower       The real power.
             * @param      vertexProperty  The vertex property.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddRealPowerToVertexProperty ( Types::name const & realPower
                                                     , TVertexProperties & vertexProperty ) 
            { 
                if ( !realPower.empty() ) 
                {
                    if ( realPower.compare("inf") != 0 ) 
                    { // not inf
                        /* vertex.RealPowerLoad()        = Types::String2double( realPower ); */
                    } else { //inf
                        /* vertex.RealPowerLoad()        = Types::String2double( realPower ); */
                    }
                }
            }

            /**
             * @brief      Add reactive power to the vertex property.
             *
             * @param      reactivePower   The reactive power
             * @param      vertexProperty  The vertex property
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddReactivePowerToVertexProperty ( Types::name const & reactivePower
                                                         , TVertexProperties & vertexProperty ) 
            { 
                if ( !reactivePower.empty() ) 
                {
                    if ( reactivePower.compare("inf") != 0 ) 
                    { // not inf
                        /*vertex.ReactivePowerLoad()    = Types::String2double( reactivePower ); */
                    } else { //inf
                        /*vertex.ReactivePowerLoad()    = Types::String2double( reactivePower ); */
                    }
                }
            }

            /**
             * @brief      Add the voltage magnitude in p.u. to the vertex property.
             *
             * @param      voltageMagnitudePu  The voltage magnitude in p.u.
             * @param      vertexProperty      The vertex property.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddVoltageMagnitudePuToVertexProperty ( Types::name const & voltageMagnitudePu
                                                              , TVertexProperties & vertexProperty ) 
            {
                if ( !voltageMagnitudePu.empty() ) 
                {
                    if ( voltageMagnitudePu.compare("inf") != 0 ) 
                    { // not inf
                        /* vertex.VoltageMagnitude() = voltageMagnitudePu; */ 
                    } else { //inf
                        /* vertex.VoltageMagnitude() = voltageMagnitudePu; */ 
                    }
                } 
            }

            /**
             * @brief      Add voltage angle to the vertex property.
             *
             * @param      voltageAngle    The voltage angle.
             * @param      vertexProperty  The vertex property.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddVoltageAngleToVertexProperty ( Types::name const & voltageAngle
                                                        , TVertexProperties & vertexProperty ) 
            { 
                if ( !voltageAngle.empty() ) 
                {
                    if ( voltageAngle.compare("inf") != 0 ) 
                    { // not inf
                        vertexProperty.VoltageAngle()         = Types::String2double( voltageAngle ); 
                    } else { //inf
                        vertexProperty.VoltageAngle()         = Const::REAL_INFTY; 
                    }
                }
            }

            /**
             * @brief      Add the marginal price to the vertex property.
             *
             * @param      marginalPrice  The marginal price.
             * @param      vertex         The vertex property.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddMarginalPriceToVertexProperty ( Types::name const & marginalPrice
                                                         , TVertexProperties & vertex ) 
            {  
                if ( !marginalPrice.empty() ) 
                {
                    if ( marginalPrice.compare("inf") != 0 ) 
                    { // not inf
                        /* marginalPrice */
                    } else { //inf
                        /* marginalPrice */
                    }
                }
            }
        ///@}
        
        ///@name Generator (also known as source) data
        ///@{
#pragma mark GENERATOR_DATA_EXTRACTION

            /**
             * @brief      Add the control type to the generator.
             *
             * @param      control    The control type.
             * @param      generator  The generator.
             */
            inline void AddControlTypeToGenerator ( Types::string  const & control
                                                  , TGeneratorProperties * generator ) 
            { 
                generator->Control() = Vertices::StringToControlType ( control );
                if ( Vertices::ControlType::unknown == generator->Control()  ) 
                {
                    generator->Control() = Vertices::ControlType::PQ; 
                } 
            }

            /**
             * @brief      Add the nominal real power.
             *
             * @param      pNom       The nominal real power.
             * @param      generator  The generator.
             */
            inline void AddNominalRealPowerToGenerator ( Types::string  const & pNom
                                                       , TGeneratorProperties * generator ) 
            { 
                if ( Types::String2double( pNom ) != 0 ) 
                {
                    generator->NominalPower()  = Types::String2double( pNom ); 
                } else {
                    generator->NominalPower()  = 1; 
                }
            }

            /**
             * @brief      Add if the generator is nominal extendable.
             *
             * @param      pNomExtendable  The nominal extendable.
             * @param      generator       The generator.
             */
            inline void AddNominalRealPowerToGeneratorExtendable ( Types::string  const & pNomExtendable
                                                                 , TGeneratorProperties * generator ) 
            { 
                if ( pNomExtendable == "TRUE" ) 
                { 
                    generator->IsExtendable() = true; 
                } else { 
                    generator->IsExtendable() = false; 
                } 
            }

            /**
             * @brief      Add the name to the generator.
             *
             * @param      name       The name.
             * @param      generator  The generator.
             */
            inline void AddNameToGenerator ( Types::name    const & name
                                           , TGeneratorProperties * generator ) 
            { 
                generator->Name()                 = name; 
                if ( mapGeneratorName2Generator_.find( generator->Name() ) == mapGeneratorName2Generator_.end() ) 
                {
                    mapGeneratorName2Generator_[generator->Name()] = generator; 
                } else {
                    ESSENTIAL_ASSERT( false && "Generator duplicates" );
                }
            } 

            /**
             * @brief      Associate the generator with a bus.
             *
             * @param      bus        The bus.
             * @param      generator  The generator.
             */
            inline void AssociateGeneratorWithBus ( Types::name    const & bus
                                                  , TGeneratorProperties * generator ) 
            { 
                if ( !bus.empty() ) 
                {
                    if ( mapGeneratorName2BusName_.find( generator->Name() ) == mapGeneratorName2BusName_.end() ) 
                    {
                        mapGeneratorName2BusName_[generator->Name()] = bus; 
                    } else {
                        ESSENTIAL_ASSERT( false && "Generator duplicates" );
                    }
                } else {
                    USAGE_ASSERT ( false && "Generator bus is empty!" );
                }
            }

            /**
             * @brief      Add the type to the generator.
             *
             * @param      type       The type.
             * @param      generator  The generator.
             */
            inline void AddTypeToGenerator ( Types::string  const & type
                                           , TGeneratorProperties * generator ) 
            { 
                if ( !type.empty() ) 
                {
                    /* generator type */
                }
            }

            /**
             * @brief      Add the generator's efficiency to the generator.
             *
             * @param      efficiency  The generator's efficiency.
             * @param      generator   The generator.
             */
            inline void AddGeneratorEfficiencyToGenerator ( Types::string  const & efficiency
                                                          , TGeneratorProperties * generator ) 
            { 
                if ( !efficiency.empty() ) 
                {
                    if ( efficiency.compare("inf") != 0 ) 
                    { // not inf
                        generator->Efficiency() = Types::String2double( efficiency );
                    } else { //inf
                        generator->Efficiency() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the minimum nominal real power.
             *
             * @param      pNomMin    The minimum nominal real power.
             * @param      generator  The generator.
             */
            inline void AddNominalRealPowerToGeneratorMin ( Types::string  const & pNomMin
                                                          , TGeneratorProperties * generator ) 
            { 
                if ( !pNomMin.empty() ) 
                {
                    if ( pNomMin.compare("inf") != 0 ) 
                    { // not inf
                        generator->NominalRealPowerBound().Minimum() = Types::String2double( pNomMin );
                    } else { //inf
                        generator->NominalRealPowerBound().Minimum() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the maximum nominal real power to the generator.
             *
             * @param      pNomMax    The maximum nominal real power.
             * @param      generator  The generator.
             */
            inline void AddNominalRealPowerToGeneratorMax ( Types::string  const & pNomMax
                                                          , TGeneratorProperties * generator ) 
            { 
                if ( !pNomMax.empty() ) 
                {
                    if ( pNomMax.compare("inf") != 0 ) 
                    { // not inf
                        generator->NominalRealPowerBound().Maximum() = Types::String2double( pNomMax );      
                    } else { //inf
                        generator->NominalRealPowerBound().Maximum() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the minimum real power in p.u. to the generator.
             *
             * @param      pMinPu     The minimum real power in p.u.
             * @param      generator  The generator.
             */
            inline void AddMinimumRealPowerPuToGenerator ( Types::string  const & pMinPu
                                                         , TGeneratorProperties * generator ) 
            { 
                if ( !pMinPu.empty() ) 
                {
                    if ( pMinPu.compare("inf") != 0 ) 
                    { // not inf
                        generator->RealPowerBound().Minimum()   = Types::String2double( pMinPu  );
                    } else { //inf
                        generator->RealPowerBound().Minimum()   = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the maximum real power in p.u.
             *
             * @param      pMaxPu     The maximum real power in p.u.
             * @param      generator  The generator.
             */
            inline void AddMaximumRealPowerPuToGenerator ( Types::string  const & pMaxPu
                                                         , TGeneratorProperties * generator ) 
            { 
                if ( !pMaxPu.empty() ) 
                {
                    if ( pMaxPu.compare("inf") != 0 ) 
                    { // not inf
                        generator->RealPowerBound().Maximum()   = Types::String2double( pMaxPu  );
                    } else { //inf
                        generator->RealPowerBound().Maximum()   = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the real power set point to the generator.
             *
             * @param      pSet       The real power set point.
             * @param      generator  The generator.
             */
            inline void AddRealPowerSetPointToGenerator ( Types::string  const & pSet
                                                        , TGeneratorProperties * generator ) 
            { 
                if ( !pSet.empty() ) 
                {
                    if ( pSet.compare("inf") != 0 ) 
                    { // not inf
                        generator->RealPower() = Types::String2double( pSet );
                    } else { //inf
                        generator->RealPower() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the reactive set point to the generator.
             *
             * @param      qSet       The reactive power set point.
             * @param      generator  The generator.
             */
            inline void AddReactivePowerSetPointToGenerator ( Types::string  const & qSet
                                                            , TGeneratorProperties * generator ) 
            { 
                if ( !qSet.empty() ) 
                {
                    if ( qSet.compare("inf") != 0 ) 
                    { // not inf
                        generator->ReactivePower() = Types::String2double( qSet );
                    } else { //inf
                        generator->ReactivePower() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the generator's sign to the generator.
             *
             * @param      sign       The sign.
             * @param      generator  The generator.
             */
            inline void AddGeneratorSignToGenerator ( Types::string  const & sign
                                                    , TGeneratorProperties * generator ) 
            { 
                if ( !sign.empty() ) 
                {
                    Types::integer powerSign    = Types::String2integer( sign );
                    if ( powerSign >= 0 )
                        generator->PowerSign()  = Vertices::PowerSign::positive;
                    else
                        generator->PowerSign()  = Vertices::PowerSign::negative;
                }
            }

            /**
             * @brief      Add the carrier to the generator.
             *
             * @param      carrier    The carrier.
             * @param      generator  The generator.
             */
            inline void AddCarrierToGenerator ( Types::string  const & carrier
                                              , TGeneratorProperties * generator ) 
            { 
                if ( !carrier.empty() ) 
                {
                    generator->GeneratorType() = Vertices::StringToGeneratorType( carrier );
                }
            }

            /**
             * @brief      Add the marginal cost to the generator.
             *
             * @param      marginalCost  The marginal cost.
             * @param      generator     The generator.
             */
            inline void AddMarginalCostToGenerator ( Types::string  const & marginalCost
                                                   , TGeneratorProperties * generator ) 
            { 
                if ( !marginalCost.empty() ) 
                {
                    if ( marginalCost.compare("inf") != 0 ) 
                    { // not inf
                        generator->MarginalCost() = Types::String2double( marginalCost ); 
                    } else { //inf
                        generator->MarginalCost() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the capital cost to the generator.
             *
             * @param      capitalCost  The capital cost.
             * @param      generator    The generator.
             */
            inline void AddCapitalCostToGenerator ( Types::string  const & capitalCost
                                                  , TGeneratorProperties * generator ) 
            { 
                if ( !capitalCost.empty() ) 
                {
                    if ( capitalCost.compare("inf") != 0 ) 
                    { // not inf
                        generator->CapitalCost() = Types::String2double( capitalCost );
                    } else { //inf
                        generator->CapitalCost() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add if the generator is committable or not.
             *
             * @param      committable  The committable.
             * @param      generator    The generator.
             */
            inline void AddCommittabilityToGenerator ( Types::string  const & committable
                                                     , TGeneratorProperties * generator ) 
            { 
                if ( committable == "True" ) 
                { 
                    generator->Committable() = true; 
                } else { 
                    generator->Committable() = false; 
                } 
            }

            /**
             * @brief      Add the start up cost to the generator.
             *
             * @param      startUpCost  The start up cost.
             * @param      generator    The generator.
             */
            inline void AddStartUpCostToGenerator ( Types::string  const & startUpCost
                                                  , TGeneratorProperties * generator ) 
            { 
                if ( !startUpCost.empty() ) 
                {
                    if ( startUpCost.compare("inf") != 0 ) 
                    { // not inf
                        generator->StartUpCost() = Types::String2double( startUpCost );
                    } else { //inf
                        generator->StartUpCost() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the shutdown cost to the generator.
             *
             * @param      shutDownCost  The shut down cost.
             * @param      generator     The generator.
             */
            inline void AddShutDownCostToGenerator ( Types::string  const & shutDownCost
                                                   , TGeneratorProperties * generator ) 
            { 
                if ( !shutDownCost.empty() ) 
                {
                    if ( shutDownCost.compare("inf") != 0 ) 
                    { // not inf
                        generator->ShutDownCost() = Types::String2double( shutDownCost );
                    } else { //inf
                        generator->ShutDownCost() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the minimum up time to the generator.
             *
             * @param      minUpTime  The minimum up time.
             * @param      generator  The generator.
             */
            inline void AddMinimumUpTimeToGenerator ( Types::string  const & minUpTime
                                                    , TGeneratorProperties * generator ) 
            { 
                if ( !minUpTime.empty() ) 
                {
                    if ( minUpTime.compare("inf") != 0 ) 
                    { // not inf
                        generator->MinimumUpTime() = Types::String2double( minUpTime );        
                    } else { //inf
                        generator->MinimumUpTime() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the minimum down time to the generator.
             *
             * @param      minDownTime  The minimum down time.
             * @param      generator    The generator.
             */
            inline void AddMinimumDownTimeToGenerator ( Types::string  const & minDownTime
                                                      , TGeneratorProperties * generator ) 
            { 
                if ( !minDownTime.empty() ) 
                {
                    if ( minDownTime.compare("inf") != 0 ) 
                    { // not inf
                        generator->MinimumDownTime() = Types::String2double( minDownTime );
                    } else { //inf
                        generator->MinimumDownTime() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the initial status to the generator.
             *
             * @param      initialStatus  The initial status.
             * @param      generator      The generator.
             */
            inline void AddInitialStatusToGenerator ( Types::string  const & initialStatus
                                                    , TGeneratorProperties * generator ) 
            { 
                if ( !initialStatus.empty() ) 
                {
                    Types::index status     = Types::String2integer( initialStatus );
                    if ( status )
                        generator->Status() = Vertices::BusStatus::active;
                    else
                        generator->Status() = Vertices::BusStatus::inactive;
                }
            }

            /**
             * @brief      Add the ramp limit up to the generator.
             *
             * @param      rampLimitUp  The ramp limit up.
             * @param      generator    The generator.
             */
            inline void AddRampLimitUpToGenerator ( Types::string  const & rampLimitUp
                                                  , TGeneratorProperties * generator ) 
            { 
                if ( !rampLimitUp.empty() ) 
                {
                    if ( rampLimitUp.compare("inf") != 0 ) 
                    { // not inf
                        generator->RampLimitUp() = Types::String2double( rampLimitUp );      
                    } else { //inf
                        generator->RampLimitUp() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the ramp limit down to the generator.
             *
             * @param      rampLimitDown  The ramp limit down.
             * @param      generator      The generator.
             */
            inline void AddRampLimitDownToGenerator ( Types::string  const & rampLimitDown
                                                    , TGeneratorProperties * generator ) 
            { 
                if ( !rampLimitDown.empty() ) 
                {
                    if ( rampLimitDown.compare("inf") != 0 ) 
                    { // not inf
                        generator->RampLimitDown() = Types::String2double( rampLimitDown );    
                    } else { //inf
                        generator->RampLimitDown() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the ramp limit start up to the generator.
             *
             * @param      rampLimitStartUp  The ramp limit start up.
             * @param      generator         The generator.
             */
            inline void AddRampLimitStartUpToGenerator ( Types::string  const & rampLimitStartUp
                                                       , TGeneratorProperties * generator ) 
            { 
                if ( !rampLimitStartUp.empty() ) 
                {
                    if ( rampLimitStartUp.compare("inf") != 0 ) 
                    { // not inf
                        generator->RampLimitStartUp()  = Types::String2double( rampLimitStartUp);  
                    } else { //inf
                        generator->RampLimitStartUp()  = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the ramp limit shutdown to the generator.
             *
             * @param      rampLimitShutDown  The ramp limit shut down.
             * @param      generator          The generator.
             */
            inline void AddRampLimitShutDownToGenerator ( Types::string  const & rampLimitShutDown
                                                        , TGeneratorProperties * generator ) 
            { 
                if ( !rampLimitShutDown.empty() ) 
                {
                    if ( rampLimitShutDown.compare("inf") != 0 ) 
                    { // not inf
                        generator->RampLimitShutDown() = Types::String2double( rampLimitShutDown );
                    } else { //inf
                        generator->RampLimitShutDown() = Const::REAL_INFTY;
                    }
                }
            }
        ///@}

        ///@name Generator data output
        ///@{    
#pragma mark GENERATOR_DATA_OUTPUT

            /**
             * @brief      Add the real power to a generator.
             *
             * @param      realPower  The real power.
             * @param      generator  The generator.
             */
            inline void AddRealPowerToGenerator ( Types::name    const & realPower
                                                , TGeneratorProperties * generator ) 
            { 
                if ( !realPower.empty() ) 
                {
                    if ( realPower.compare("inf") != 0 ) 
                    { // not inf
                        /* realPower */
                    } else { //inf
                        /* realPower */
                    }
                }
            }

            /**
             * @brief      Add the reactive power to the generator.
             *
             * @param      reactivePower  The reactive power.
             * @param      generator      The generator.
             */
            inline void AddReactivePowerToGenerator ( Types::name    const & reactivePower
                                                    , TGeneratorProperties * generator ) 
            { 
                if ( !reactivePower.empty() ) 
                {
                    if ( reactivePower.compare("inf") != 0 ) 
                    { // not inf
                        /* reactivePower */
                    } else { //inf
                        /* reactivePower */
                    }
                }
            }

            /**
             * @brief      Add the optimal nominal real power to the generator.
             *
             * @param      pNomOpt    The optimal nominal real power.
             * @param      generator  The generator.
             */
            inline void AddNominalRealPowerToGeneratorOpt ( Types::name    const & pNomOpt
                                                          , TGeneratorProperties * generator ) 
            { 
                if ( !pNomOpt.empty() ) 
                {  
                    if ( pNomOpt.compare("inf") != 0 ) 
                    { // not inf
                        /* pNomOpt */
                    } else { //inf
                        /* pNomOpt */
                    }
                } 
            }

            /**
             * @brief      Add the status to the generator.
             *
             * @param      status     The status.
             * @param      generator  The generator.
             */
            inline void AddStatusToGenerator ( Types::name    const & status
                                             , TGeneratorProperties * generator ) 
            { 
                if ( !status.empty() ) 
                {
                    if ( status.compare("inf") != 0 ) 
                    { // not inf
                        /* status */
                    } else { //inf
                        /* status */
                    }
                }
            }

            /**
             * @brief      Add the weight to the generator.
             *
             * @param      weight     The weight.
             * @param      generator  The generator.
             */
            inline void AddWeightToGenerator ( Types::name    const & weight
                                             , TGeneratorProperties * generator ) 
            { 
                if ( !weight.empty() ) 
                {
                    if ( weight.compare("inf") != 0 ) 
                    { // not inf
                        /* weight */
                    } else { //inf
                        /* weight */
                    }
                }
            }
        ///@}

        ///@name Generator snapshot extraction
        ///@{
#pragma mark GENERATOR_SNAPSHOT_EXTRACTION

            /**
             * @brief      Add the time stamp of the maximum real power.
             *
             * @param      name     The name.
             * @param      network  The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * 
             * @todo       What happens if load timestamps does not exist?
             * 
             */
            void AddTimestampOfGenerator ( Types::name const & name
                                                , TNetwork   & network ) 
            { /*network.AddSnapshotTimestamp( name ); is already implemented at load equivalent*/ 
            }

            /**
             * @brief      Add the maximum real power generation snapshot in p.u. to a generator.
             *
             * @param      maximumRealPowerPu  The maximum real power in p.u.
             * @param      network             The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * @param[in]  generatorId         The generator identifier.
             * 
             * @todo Check if the number of timestamps are correct
             * 
             */
            inline void AddMaximumRealPowerSnapshotPuToGenerator ( Types::name const & maximumRealPowerPu
                                                                 , TNetwork          & network
                                                                 , Types::vertexId     generatorId ) 
            { 
                if ( !maximumRealPowerPu.empty() ) 
                {
                    if ( maximumRealPowerPu.compare("inf") != 0 ) 
                    { // not inf
                        network.AddGeneratorRealPowerSnapshotAt(generatorId, Types::String2double( maximumRealPowerPu ) );  
                    } else { //inf
                        network.AddGeneratorRealPowerSnapshotAt(generatorId, Const::REAL_INFTY );  
                    }
                } else {
                    USAGE_ASSERT ( false && "Generator real power snapshot at generatorId is empty!" );
                }
            } 
            // void AddMaximumRealPowerSnapshotPuToGenerator ( Types::name & maximumRealPowerPu, TGeneratorProperties * generator ) { generator->RealPower() = Types::String2double( maximumRealPowerPu );  } 
        ///@}

        ///@name Line (also known as Branch or Circuit) Data
        ///@{
#pragma mark LINE_DATA_EXTRACTION

            /**
             * @brief      Add the name to the line.
             *
             * @param      name  The name of the line.
             * @param      edge  The edge.
             */
            inline void AddNameToEdge ( Types::name const & name
                                      , TIoEdge           & edge ) 
            { 
                edge.Properties().Name() = name;
            }

            /**
             * @brief      Associate the line with the source vertex.
             *
             * @param      source  The source vertex.
             * @param      edge    The edge.
             */
            inline void AddSourceVertexToEdge ( Types::name const & source
                                              , TIoEdge           & edge ) 
            { 
                if ( !source.empty() ) 
                {
                    if ( mapBusName2VertexId_.find ( source ) != mapBusName2VertexId_.end() ) 
                    {
                        edge.Source() = mapBusName2VertexId_[source];
                    }
                }
            } 

            /**
             * @brief      Associate the line with the target bus.
             *
             * @param      target  The target bus.
             * @param      edge    The edge.
             */
            inline void AddTargetVertexToEdge ( Types::name const & target
                                              , TIoEdge           & edge ) 
            { 
                if ( !target.empty() ) 
                {
                    if ( mapBusName2VertexId_.find ( target ) != mapBusName2VertexId_.end() ) 
                    {
                        edge.Target() = mapBusName2VertexId_[target];
                    }
                }
            } 

            /**
             * @brief      Add the capital cost to the line.
             *
             * @param      capitalCost  The capital cost.
             * @param      edge         The edge.
             */
            inline void AddCapitalCostToEdge ( Types::name const & capitalCost
                                             , TIoEdge           & edge ) 
            { 
                if ( !capitalCost.empty() ) 
                {
                    if ( capitalCost.compare("inf") != 0 ) 
                    { // not inf
                        edge.Properties().CapitalCost() = Types::String2double( capitalCost );
                    } else { //inf
                        edge.Properties().CapitalCost() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the length to the line.
             *
             * @param      length  The length.
             * @param      edge    The edge.
             */
            inline void AddLengthToEdge ( Types::name const & length
                                        , TIoEdge           & edge ) 
            { 
                if ( !length.empty() ) 
                {
                    if ( length.compare("inf") != 0 ) 
                    { // not inf
                        edge.Properties().Length() = Types::String2double( length );
                    } else {
                        ESSENTIAL_ASSERT( false && "Infinity line length");
                    }
                }
            }

            /**
             * @brief      Add the number of parallel lines to the line.
             *
             * @param      numberParallelLines  The number parallel lines.
             * @param      edge                 The edge.
             */
            inline void AddNumberOfParallelLinesToEdge ( Types::name const & numberParallelLines
                                                       , TIoEdge           & edge ) 
            { 
                if ( !numberParallelLines.empty() ) 
                {
                    if ( numberParallelLines.compare("inf") != 0 ) 
                    { // not inf
                        edge.Properties().NumberOfParallelLines() = Types::String2integer( numberParallelLines ); 
                    } else {
                        ESSENTIAL_ASSERT( false && "Infinity parallel lines");
                    }
                }
            }

            /**
             * @brief      Add the maximum apparent power in p.u. to the line.
             *
             * @param      apparentPowerMaximumPu  The maximum apparent power in p.u.
             * @param      edge                    The edge.
             */
            inline void AddMaximumApparentPowerPuToEdge ( Types::name const & apparentPowerMaximumPu
                                                        , TIoEdge           & edge ) 
            { 
                if ( !apparentPowerMaximumPu.empty() ) 
                {
                    if ( apparentPowerMaximumPu.compare("inf") != 0 ) 
                    { // not inf
                        edge.Properties().ThermalLimit() = Types::String2double( apparentPowerMaximumPu );   
                    } else { //inf
                        edge.Properties().ThermalLimit() = Const::REAL_INFTY;
                    }
                }
            } 
            
            /**
             * @brief      Add the nominal apparent power to the line.
             *
             * @param      apparentPowerNominal  The nominal apparent power.
             * @param      edge                  The edge.
             */
            void AddNominalApparentPowerToEdge ( Types::name const & apparentPowerNominal
                                                      , TIoEdge           & edge ) 
            { 
                if ( !apparentPowerNominal.empty() ) 
                {
                    if ( apparentPowerNominal.compare("inf") != 0 ) 
                    { // not inf
                        edge.Properties().NominalApparentPower() = Types::String2double( apparentPowerNominal );     
                    } else { //inf
                        edge.Properties().NominalApparentPower() = Const::REAL_INFTY;
                    }
                }
            }
            
            /**
             * @brief      Add the line type to the line.
             *
             * @param      type  The line type.
             * @param      edge  The edge.
             */
            inline void AddLineTypeToEdge ( Types::name const & type
                                          , TIoEdge           & edge ) 
            { 
                if ( !type.empty() ) 
                {
                    edge.Properties().Type() = Edges::ElectricalEdgeType::standard; 
                }
            }

            /**
             * @brief      Add the nominal voltage to the line.
             *
             * @param      voltageNominal  The nominal voltage.
             * @param      edge            The edge.
             */
            void AddNominalVoltageToEdge ( Types::name const & voltageNominal
                                                , TIoEdge           & edge ) 
            { 
                if ( !voltageNominal.empty() ) 
                {
                    if ( voltageNominal.compare("inf") != 0 ) 
                    { // not inf
                        edge.Properties().NominalVoltage() = Types::String2double( voltageNominal );
                    } else { //inf
                        edge.Properties().NominalVoltage() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the minimum nominal apparent power.
             *
             * @param      apparentPowerNominalMinimum  The minimum nominal apparent power.
             * @param      edge                         The edge.
             */
            inline void AddMinimumNominalApparentPowerToEdge ( Types::name const & apparentPowerNominalMinimum
                                                             , TIoEdge           & edge ) 
            { /* difference to apparentPowerMaximumPu apart the pu */
                if ( !apparentPowerNominalMinimum.empty() ) 
                {
                    if ( apparentPowerNominalMinimum.compare("inf") != 0 ) 
                    { // not inf
                        edge.Properties().NominalApparentPowerBound().Minimum() = Types::String2double( apparentPowerNominalMinimum );
                    } else { //inf
                        edge.Properties().NominalApparentPowerBound().Minimum() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the maximum nominal apparent power to the line.
             *
             * @param      apparentPowerNominalMaximum  The maximum nominal apparent power.
             * @param      edge                         The edge.
             */
            inline void AddMaximalNominalApparentPowerToEdge ( Types::name const & apparentPowerNominalMaximum
                                                             , TIoEdge           & edge ) 
            { 
                if ( !apparentPowerNominalMaximum.empty() ) 
                {
                    if ( apparentPowerNominalMaximum.compare("inf") != 0 ) 
                    { // not inf
                        edge.Properties().NominalApparentPowerBound().Maximum() = Types::String2double( apparentPowerNominalMaximum ); 
                    } else { //inf
                        edge.Properties().NominalApparentPowerBound().Maximum() = Const::REAL_INFTY;
                    }
                }
            }

            /**
             * @brief      Add the resistance to the line.
             *
             * @param      resistance  The resistance.
             * @param      edge        The edge.
             */
            inline void AddResistanceToEdge ( Types::name const & resistance   
                                            , TIoEdge           & edge ) 
            { 
                if ( !resistance.empty() ) 
                {
                    if ( resistance.compare("inf") != 0 ) 
                    { // not inf
                        edge.Properties().Resistance() = Types::String2double( resistance );
                    } else { //inf
                        edge.Properties().Resistance() = Const::REAL_INFTY;
                    }  
                }
            }

            /**
             * @brief      Add the reactance to the line.
             *
             * @param      reactance  The reactance.
             * @param      edge       The edge.
             */
            inline void AddReactanceToEdge ( Types::name const & reactance
                                           , TIoEdge           & edge ) 
            { 
                if ( !reactance.empty() ) 
                {
                    if ( reactance.compare("inf") != 0 ) 
                    { // not inf
                        edge.Properties().Reactance() = Types::String2double( reactance );
                    } else { //inf
                        edge.Properties().Reactance() = Const::REAL_INFTY;
                    }  
                }
            }

            /**
             * @brief      Add the conductance to the line.
             *
             * @param      conductance  The conductance.
             * @param      edge         The edge.
             */
            inline void AddConductanceToEdge ( Types::name const & conductance
                                             , TIoEdge           & edge ) 
            { /* Can be calculated by r and x */
                if ( !conductance.empty() ) 
                {
                    if ( conductance.compare("inf") != 0 ) 
                    { // not inf
                        edge.Properties().Conductance( Types::String2double( conductance ) );
                    } else { //inf
                        edge.Properties().Conductance( Const::REAL_INFTY );
                    }  
                }
            } 

            /**
             * @brief      Add the susceptance to the line.
             *
             * @param      susceptance  The susceptance.
             * @param      edge         The edge.
             */
            inline void AddSusceptanceToEdge ( Types::name const & susceptance
                                             , TIoEdge           & edge ) 
            { /* Can be calculated by r and x */
                if ( !susceptance.empty() ) 
                {
                    if ( susceptance.compare("inf") != 0 ) 
                    { // not inf
                        edge.Properties().Susceptance( Types::String2double( susceptance ) );
                    } else { //inf
                        edge.Properties().Susceptance( Const::REAL_INFTY );
                    }   
                }
            } 
            
            /**
             * @brief      Add the nominal extendable apparent power to the line.
             *
             * @param      apparentPowerNominalExtendable  The nominal extendable apparent power.
             * @param      edge                            The edge.
             */
            void AddNominalExtendableApparentPowerToEdge ( Types::name const & apparentPowerNominalExtendable
                                                         , TIoEdge           & edge ) 
            { 
                if ( !apparentPowerNominalExtendable.empty() ) 
                {
                    edge.Properties().NominalApparentPowerExtendable() = Types::String2double( apparentPowerNominalExtendable ); 
                }
            }

            /**
             * @brief      Add the terrain factor to the line.
             *
             * @param      terrainFactor  The terrain factor.
             * @param      edge           The edge.
             */
            inline void AddTerrainFactorToEdge ( Types::name const & terrainFactor
                                               , TIoEdge           & edge ) 
            { 
                if ( !terrainFactor.empty() ) 
                {   
                    if ( terrainFactor.compare("inf") != 0 ) 
                    { // not inf
                        edge.Properties().TerrainFactor() = Types::String2double( terrainFactor );
                    } else { //inf
                        edge.Properties().TerrainFactor() = Const::REAL_INFTY;
                    }   
                }
            }

            /**
             * @brief      Add the minimum voltage angle to the line.
             *
             * @param      voltageAngleMin  The minimum voltage angle.
             * @param      edge             The edge.
             */
            inline void AddMinimumVoltageAngleToEdge ( Types::name const & voltageAngleMin
                                                     , TIoEdge           & edge ) 
            { 
                if ( !voltageAngleMin.empty() ) 
                {
                    if ( voltageAngleMin.compare("inf") != 0 ) 
                    { // not inf
                        edge.Properties().ThetaBound().Minimum() = Types::String2double( voltageAngleMin );
                    } else { //inf
                        edge.Properties().ThetaBound().Minimum()  = Const::REAL_INFTY;
                    }   
                }
            }

            /**
             * @brief      Add maximum voltage angle to the line.
             *
             * @param      voltageAngleMax  The maximum voltage angle.
             * @param      edge             The edge.
             */
            inline void AddMaximumVoltageAngleToEdge ( Types::name const & voltageAngleMax
                                                     , TIoEdge           & edge ) 
            { 
                if ( !voltageAngleMax.empty() ) 
                {
                    if ( voltageAngleMax.compare("inf") != 0 ) 
                    { // not inf
                        edge.Properties().ThetaBound().Maximum() = Types::String2double( voltageAngleMax );
                    } else { //inf
                        edge.Properties().ThetaBound().Maximum() = Const::REAL_INFTY;
                    }
                }
            }
        ///@}

        /**
         * @name       Line data output.
         * 
         * @brief      Each row in the line data creates an edge. 
         *
         * @note       Currently only used for output.
         */
        ///@{    
#pragma mark LINE_DATA_OUTPUT
            
            /**
             * @brief      Add the subnetwork.
             *
             * @param      subnetwork  The subnetwork.
             * @param      edge        The edge.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddSubnetworkToEdge ( Types::name const & subnetwork
                                            , TIoEdge           & edge ) 
            { 
                if ( !subnetwork.empty() ) 
                {
                    if ( subnetwork.compare("inf") != 0 ) 
                    { // not inf
                        /* edge subnetwork */
                    } else { //inf
                        /* edge subnetwork */
                    }
                }
            }

            /**
             * @brief      Add the real power P0.
             *
             * @param      p0    The real power P0.
             * @param      edge  The edge.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddP0ToEdge ( Types::name const & p0
                                    , TIoEdge           & edge ) 
            { 
                if ( !p0.empty() ) 
                {
                    if ( p0.compare("inf") != 0 ) 
                    { // not inf
                        /* edge p0 */
                    } else { //inf
                        /* edge p0 */
                    }
                }
            }

            /**
             * @brief      Add the reactive power Q0.
             *
             * @param      q0    The reactive power Q0.
             * @param      edge  The edge.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddQ0ToEdge ( Types::name const & q0
                                    , TIoEdge           & edge ) 
            { 
                if ( !q0.empty() ) 
                {
                    if ( q0.compare("inf") != 0 ) 
                    { // not inf
                        /* edge q0 */
                    } else { //inf
                        /* edge q0 */
                    }
                }
            }

            /**
             * @brief      Add the real power P1.
             *
             * @param      p1    The real power P1.
             * @param      edge  The edge.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddP1ToEdge ( Types::name const & p1
                                    , TIoEdge           & edge ) 
            { 
                if ( !p1.empty() ) 
                {
                    if ( p1.compare("inf") != 0 ) 
                    { // not inf
                        /* edge p1 */
                    } else { //inf
                        /* edge p1 */
                    }
                }
            }

            /**
             * @brief      Add the reactive power Q1
             *
             * @param      q1    The reactive power Q1.
             * @param      edge  The edge.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddQ1ToEdge ( Types::name const & q1
                                    , TIoEdge           & edge ) 
            { 
                if ( !q1.empty() ) 
                {
                    if ( q1.compare("inf") != 0 ) 
                    { // not inf
                        /* edge q1 */
                    } else { //inf
                        /* edge q1 */
                    }
                }
            }

            /**
             * @brief      Add the reactance in p.u.
             *
             * @param      reactancePu  The reactance in p.u.
             * @param      edge         The edge.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddReactancePuToEdge ( Types::name const & reactancePu
                                             , TIoEdge           & edge ) 
            { 
                if ( !reactancePu.empty() ) 
                {
                    if ( reactancePu.compare("inf") != 0 ) 
                    { // not inf
                        /* edge reactancePu */
                    } else { //inf
                        /* edge reactancePu */
                    }
                }
            }
            /**
             * @brief      Add the resistance in p.u.
             *
             * @param      resistancePu  The resistance in p.u.
             * @param      edge          The edge.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddResistancePuToEdge ( Types::name const & resistancePu
                                              , TIoEdge           & edge ) 
            { 
                if ( !resistancePu.empty() ) 
                {
                    if ( resistancePu.compare("inf") != 0 ) 
                    { // not inf
                        /* edge resistancePu */
                    } else { //inf
                        /* edge resistancePu */
                    }
                }
            }

            /**
             * @brief      Add the conductance G in p.u.
             *
             * @param      conductancePu  The conductance in p.u.
             * @param      edge           The edge.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddConductancePuToEdge ( Types::name const & conductancePu
                                               , TIoEdge           & edge ) 
            { 
                if ( !conductancePu.empty() ) 
                {
                    if ( conductancePu.compare("inf") != 0 ) 
                    { // not inf
                        /* edge conductancePu */
                    } else { //inf
                        /* edge conductancePu */
                    }
                }
            }

            /**
             * @brief      Add the susceptance in p.u.
             *
             * @param      susceptancePu  The susceptance in p.u.
             * @param      edge           The edge.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddSusceptancePuToEdge ( Types::name const & susceptancePu
                                               , TIoEdge           & edge ) 
            { 
                if ( !susceptancePu.empty() ) 
                {
                    if ( susceptancePu.compare("inf") != 0 ) 
                    { // not inf
                        /* edge susceptancePu */
                    } else { //inf
                        /* edge susceptancePu */
                    }
                }
            }
            
            /**
             * @brief      Add the effective reactance in p.u.
             *
             * @param      reactancePuEffective  The effective reactance in p.u.
             * @param      edge                  The edge
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddEffectiveReactancePuToEdge ( Types::name const & reactancePuEffective
                                                      , TIoEdge           & edge ) 
            { 
                if ( !reactancePuEffective.empty() ) 
                {
                    if ( reactancePuEffective.compare("inf") != 0 ) 
                    { // not inf
                        /* edge reactancePuEffective */
                    } else { //inf
                        /* edge reactancePuEffective */
                    }
                }
            }

            /**
             * @brief      Add the effective resistance in p.u.
             *
             * @param      resistancePuEffective  The effective resistance in p.u. 
             * @param      edge                   The edge.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddEffectiveResistancePuToEdge ( Types::name const & resistancePuEffective
                                                       , TIoEdge           & edge ) 
            { 
                if ( !resistancePuEffective.empty() ) 
                {
                    if ( resistancePuEffective.compare("inf") != 0 ) 
                    { // not inf
                        /* edge resistancePuEffective */
                    } else { //inf
                        /* edge resistancePuEffective */
                    }
                }
            }

            /**
             * @brief      Add the optimal nominal apparent power.
             *
             * @param      apparentPowerNominalOptimal  The optimal nominal apparent power.
             * @param      edge                         The edge.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddOptimalNominalApparentPowerToEdge ( Types::name const & apparentPowerNominalOptimal
                                                             , TIoEdge           & edge ) 
            { 
                if ( !apparentPowerNominalOptimal.empty() ) 
                {
                    if ( apparentPowerNominalOptimal.compare("inf") != 0 ) 
                    { // not inf
                        /* edge apparentPowerNominalOptimal */
                    } else { //inf
                        /* edge apparentPowerNominalOptimal */
                    }
                }
            }

            /**
             * @brief      Add mu lower of a line.
             *
             * @param      muLower  The mu lower.
             * @param      edge     The edge.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddMuLowerToEdge ( Types::name const & muLower
                                         , TIoEdge           & edge ) 
            { 
                if ( !muLower.empty() ) 
                {
                    if ( muLower.compare("inf") != 0 ) 
                    { // not inf
                        /* edge muLower */
                    } else { //inf
                        /* edge muLower */
                    }
                }
            }

            /**
             * @brief      Add mu upper of a line.
             *
             * @param      muUpper  The mu upper.
             * @param      edge     The edge.
             * 
             * @note       Currently only output and not used yet.
             */
            inline void AddMuUpperToEdge ( Types::name const & muUpper
                                        , TIoEdge           & edge ) 
            { 
                if ( !muUpper.empty() ) 
                {
                    if ( muUpper.compare("inf") != 0 ) 
                    { // not inf
                        /* edge muUpper */
                    } else { //inf
                        /* edge muUpper */
                    }
                }
            }
        ///@}

        /**
         * @name       Load Data.
         * 
         * @brief      Each row in the load data creates an load vertex. 
         *
         * @note       Currently only the name and type is set.
         */
        ///@{
#pragma mark LOAD_DATA_EXTRACTION

            /**
             * @brief      Add the name of the load.
             *
             * @param      name            The name.
             * @param      vertexProperty  The vertex property.
             */
            inline void AddNameToLoad ( Types::string const & name
                                      , TLoadProperties     & vertexProperty ) 
            { 
                vertexProperty.Name() = name; 
            }

            /**
             * @brief      Associating the load with a bus.
             *
             * @param      bus             The bus.
             * @param      vertexProperty  The vertex property.
             */
            inline void AssociateLoadWithVertex ( Types::string const & bus
                                                , TLoadProperties     & vertexProperty ) 
            {  
                if ( !bus.empty() ) 
                {
                    /* load bus */
                }
            }

            /**
             * @brief      Add the load type.
             *
             * @param      type            The load type.
             * @param      vertexProperty  The vertex property.
             */
            inline void AddTypeToLoad ( Types::string const & type
                                      , TLoadProperties     & vertexProperty ) 
            { 
                if ( !type.empty() ) 
                {
                    vertexProperty.Type() = Vertices::IeeeBusType::load; 

                } else {
                    vertexProperty.Type() = Vertices::IeeeBusType::load; 
                }
            }

            /**
             * @brief      Add the real power load set point.
             *
             * @param      pset            The real power set point.
             * @param      vertexProperty  The vertex property.
             */
            inline void AddRealPowerSetPointToLoad ( Types::string const & pset
                                                   , TLoadProperties     & vertexProperty ) 
            {
                if ( !pset.empty() ) 
                {
                    if ( pset.compare("inf") != 0 ) 
                    { // not inf
                        /* load pset */
                    } else { //inf
                        /* load pset */
                    }
                }
            }

            /**
             * @brief      Add the reactive power set point.
             *
             * @param      qset            The reactive power set point.
             * @param      vertexProperty  The vertex property.
             */
            inline void AddReactivePowerSetPointToLoad ( Types::string const & qset
                                                       , TLoadProperties     & vertexProperty ) 
            {
                if ( !qset.empty() ) 
                {
                    if ( qset.compare("inf") != 0 ) 
                    { // not inf
                        /* load qset */
                    } else { //inf
                        /* load qset */
                    }
                }
            }

            /**
             * @brief      Add the data sign of the load.
             *
             * @param      sign            The sign.
             * @param      vertexProperty  The vertex property.
             */
            inline void AddSignToLoad ( Types::string const & sign
                                      , TLoadProperties     & vertexProperty ) 
            {  
                if ( !sign.empty() ) 
                {
                    if ( sign.compare("inf") != 0 ) 
                    { // not inf
                        /* power sign */
                    } else { //inf
                        /* power sign */
                    }
                }
            }

            /**
             * @brief      Add the real power load to the vertex property.
             *
             * @param      realPower       The real power.
             * @param      vertexProperty  The vertex property.
             */
            inline void AddRealPowerToLoad ( Types::string const & realPower
                                           , TLoadProperties     & vertexProperty ) 
            { 
                if ( !realPower.empty() ) 
                {
                    if ( realPower.compare("inf") != 0 ) 
                    { // not inf
                        /* load realPower */
                    } else { //inf
                        /* load realPower */
                    }
                }
            }

            /**
             * @brief      Add the reactive power loads.
             *
             * @param      reactivePower   The reactive power.
             * @param      vertexProperty  The vertex property.
             */
            inline void AddReactivePowerToLoad ( Types::string const & reactivePower
                                               , TLoadProperties     & vertexProperty ) 
            { 
                if ( !reactivePower.empty() ) 
                {
                    if ( reactivePower.compare("inf") != 0 ) 
                    { // not inf
                        /* load reactivePower */
                    } else { //inf
                        /* load reactivePower */
                    }
                }
            }
        ///@}

        /**
         * @name       Load's Real Power Data Snapshot per Timestamp.
         * 
         * @brief      Each row in the load's real power set data creates an
         *     snapshot entry.
         *
         * @note       The snapshots are managed in the network @f$\network@f$
         *     and not in the load.
         */
        ///@{
#pragma mark LINE_SNAPSHOT_EXTRACTION

            /**
             * @brief      Add a maximum real power load time stamp in p.u.
             *
             * @param      name     The real power load time stamp in p.u.
             * @param      network  The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             */
            inline void AddLoadTimestampName ( Types::name const & name
                                             , TNetwork          & network ) 
            { 
                network.AddSnapshotTimestamp( name ); 
            }

            /**
             * @brief      Add a maximum real power load in p.u.
             *
             * @param      maximumRealPowerPu  The maximum real power load in p.u.
             * @param      network             The network @f$\network = ( \graph, \generators, \consumers, \capacity, \susceptance, \dots )@f$.
             * @param[in]  loadId              The load identifier.
             */
            inline void AddMaximumRealPowerSnapshotPuToLoad ( Types::name const & maximumRealPowerPu
                                                            , TNetwork          & network
                                                            , Types::vertexId     loadId ) 
            { 
                if ( !maximumRealPowerPu.empty() ) 
                {   
                    if ( maximumRealPowerPu.compare("inf") != 0 ) 
                    { // not inf
                        network.AddLoadSnapshotAt ( loadId, Types::String2double( maximumRealPowerPu ) );  
                    } else { //inf
                        network.AddLoadSnapshotAt ( loadId, Const::REAL_INFTY );  
                    }
                } else {
                    USAGE_ASSERT ( false && "Load real power snapshot at loadId is empty!" );
                }
            } 
        ///@}

        ///@name File and Directory Information
        ///@{
#pragma mark FILE_AND_DIRECTORY_INFORMATION

            Types::name path2FileDirectory_;                    /**< The path to the PyPsa file directory, e.g., elec_s1024_AT */
            Types::name const filenameBuses_;                   /**< Name of the bus file, e.g., buses.csv */
            Types::name const filenameCarriers_;                /**< Name of the carriers file, e.g., carriers.csv */
            Types::name const filenameGenerators_;              /**< Name of the generators file, e.g., generators.csv */
            Types::name const filenameGeneratorsPMaxPu_;        /**< Name of the generators real power (in p.u.) snapshot file, e.g., generators-p_max_pu.csv */
            Types::name const filenameGlobalConstraints_;       /**< Name of the global constraints file, e.g., global_constraints.csv */
            Types::name const filenameLines_;                   /**< Name of the branches file, e.g., lines.csv */
            Types::name const filenameLinesNew_;                /**< Name of the new branches file, e.g., lines_new.csv */
            Types::name const filenameLoads_;                   /**< Name of the loads file, e.g., loads.csv */
            Types::name const filenameLoadsPSet_;               /**< Name of the loads real power set point snapshot file, e.g., loads-p_set.csv */
            Types::name const filenameNetwork_;                 /**< Name of the network file, e.g., network.csv */
            Types::name const filenameSnapshots_;               /**< Name of the file with the weighting of a snapshot, e.g., snapshot.csv */
            Types::name const filenameStorageUnits_;            /**< Name of the file with the storage units, e.g., storage_units.csv */
            Types::name const filenameStorageUnitsInflow_;      /**< Name of the file with the storage units inflow, e.g., storage_units-inflow.csv */
        ///@}

        ///@name Mapping of Different Inputs
        ///@{
#pragma mark MAPPING_OF_DIFFERENT_INPUTS

            std::unordered_map<Types::name, Types::vertexId>     mapBusName2VertexId_;           /**< Mapping the bus name to the vertex identifier */
            std::unordered_map<Types::name, TGeneratorProperties*>   mapGeneratorName2Generator_;    /**< Mapping the generator name to the generator */
            std::unordered_map<Types::name, Types::vertexId>     mapGeneratorName2Identifier_;   /**< Mapping the generator name to the vertex identifier */
            std::unordered_map<Types::name, Types::name>         mapGeneratorName2BusName_;      /**< Mapping the generator name to the vertex name */
            std::unordered_map<Types::name, Types::vertexId>     mapLoadName2Identifier_;        /**< Mapping the load name to the vertex identifier */
        ///@}

        ///@name Counter
        ///@{
#pragma mark COUNTER
            Types::count generatorSnapshotsSize;
            Types::count loadSnapshotsSize;
            // Types::count snapshotsSize;
            // Types::count storageUnitsInflowSize;
        ///@}

        ///@name Friends
        ///@{
#pragma mark FRIENDS
            ///@todo Add dynamic graph wrapper
            friend internal::NetworkDifferentiation< TVertex, TIoEdge, PowerGrid< StaticGraph<TVertex,TIoEdge>, TGeneratorProperties, TLoadProperties > >;
            friend internal::NetworkDifferentiation< TVertex, TIoEdge, StaticGraph<TVertex,TIoEdge> >;
        ///@}
};

namespace internal {
template<>
class NetworkDifferentiation< egoa::Vertices::ElectricalProperties<egoa::Vertices::IeeeBusType>
                            , egoa::Edges::ElectricalProperties
                            , StaticGraph<egoa::Vertices::ElectricalProperties<egoa::Vertices::IeeeBusType>
                                        , egoa::Edges::ElectricalProperties> > 
{
    using TGraph            = StaticGraph<egoa::Vertices::ElectricalProperties<egoa::Vertices::IeeeBusType>
                                        , egoa::Edges::ElectricalProperties>;
    using TVertexProperties = egoa::Vertices::ElectricalProperties<egoa::Vertices::IeeeBusType>;
    using TEdgeProperties   = egoa::Edges::ElectricalProperties;
    
    using TIoEdge         = io::Edge<TEdgeProperties>;

    public:
        static Types::edgeId AddEdge ( TGraph        & network
                                     , TIoEdge const & ioEdge    ) 
        {
            return network.AddEdge( ioEdge.Source(), ioEdge.Target(), ioEdge.Properties() );
        }

        static Types::vertexId AddVertex ( TGraph                  & network
                                         , TVertexProperties const & vertexProperties  )
        {
            return network.AddVertex( vertexProperties );
        }
};

template<typename VertexTypeProperties, typename EdgeTypeProperties>
class NetworkDifferentiation< VertexTypeProperties
                            , EdgeTypeProperties
                            , StaticGraph<VertexTypeProperties
                                        , EdgeTypeProperties> > 
{
    using TVertexProperties = VertexTypeProperties;
    using TEdgeProperties   = EdgeTypeProperties;

    using TGraph            = StaticGraph<TVertexProperties
                                        , TEdgeProperties>;
    
    using TIoEdge         = io::Edge<TEdgeProperties>;
    public:
        static Types::edgeId AddEdge ( TGraph        & network
                                     , TIoEdge const & ioEdge  ) 
        {
            return network.AddEdge( ioEdge.Source(), ioEdge.Target(), ioEdge.Properties() );
        }

        static Types::vertexId AddVertex ( TGraph                  & network
                                         , TVertexProperties const & vertexProperties  )
        {
            return network.AddVertex( vertexProperties );
        }
};

template<typename VertexTypeProperties, typename EdgeTypeProperties>
class NetworkDifferentiation< VertexTypeProperties
                            , EdgeTypeProperties
                            , PowerGrid< StaticGraph< VertexTypeProperties
                                                    , EdgeTypeProperties >
                            , Vertices::GeneratorProperties<>
                            , Vertices::LoadProperties<Vertices::IeeeBusType> > > 
{
    using TVertexProperties = VertexTypeProperties;
    using TEdgeProperties   = EdgeTypeProperties;

    using TGraph  = PowerGrid<StaticGraph<TVertexProperties
                                        , TEdgeProperties>>;

    using TIoEdge         = io::Edge<TEdgeProperties>;

    public:
        static Types::edgeId AddEdge ( TGraph        & network
                                     , TIoEdge const & ioEdge  )
        {
            return network.Graph().AddEdge( ioEdge.Source(), ioEdge.Target(), ioEdge.Properties() );
        }

        static Types::vertexId AddVertex ( TGraph                  & network
                                         , TVertexProperties const & vertexProperties  )
        {
            return network.Graph().AddVertex( vertexProperties );
        }
};
} // namespace internal

} // namespace egoa

#endif // EGOA__IO__PARSER___PY_PSA_PARSER_HPP
 
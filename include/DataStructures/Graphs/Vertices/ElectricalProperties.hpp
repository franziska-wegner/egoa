/*
 * ElectricalProperties.hpp
 *
 *  Created on: Sep 07, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__VERTICES__ELECTRICAL_PROPERTIES_HPP
#define EGOA__DATA_STRUCTURES__VERTICES__ELECTRICAL_PROPERTIES_HPP

#include <iomanip>
#include <ostream>
#include <string>

#include "Auxiliary/Constants.hpp"

#include "DataStructures/Graphs/Vertices/Type.hpp"
#include "DataStructures/Bound.hpp"

namespace egoa::Vertices {

/**
 * @brief      Class for electrical properties.
 *
 * @tparam     VertexType  The vertex type, e.g., Vertices::IeeeBusType.
 */
template<class VertexType = Vertices::IeeeBusType>
class ElectricalProperties {
    public: // Template type aliasing
        // Vertex electrical type
        using TVertexType   = VertexType;
        using TProperties   = ElectricalProperties<TVertexType>;
    private:
        using TBound        = Bound<Types::real>;

    public:
        /**@name Constructors and Destructor */
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS

            /**
             * @brief      Default constructs the object.
             * @details    The values are set to the default values.
             */
            ElectricalProperties()
            : name_("")
            , type_(TVertexType::unknown)
            , xCoordinate_(0.0)
            , yCoordinate_(0.0)
            // admittance
            , shuntSusceptance_(0.0)
            , shuntConductance_(0.0)
            // voltage
            , nominalVoltage_(1.0)
            , voltageAngle_(0.0)
            , voltageMagnitude_(1.0)
            , voltageMagnitudeSq_(1.0)
            // , realVoltage_(0.0)
            // , imaginaryVoltage_(0.0)
            , voltageBound_( TBound(0.0, Const::REAL_INFTY) )
            // location
            , country_("")
            , area_(0)
            , zone_(0)
            , control_(Vertices::ControlType::PQ)
            , carrier_(EnergyCarrier::AC)
            // Status
            , status_(Vertices::BusStatus::active)
            {}

            /**
             * @brief      Reset values to default.
             */
            inline void Reset ()
            {
                // BasicVertex specifics
                Name ()           = "";
                Type ()           = TVertexType::unknown;
                X ()              = 0.0;
                Y ()              = 0.0;

                // Admittance specifics
                ShuntSusceptance ()     = 0.0;
                ShuntConductance ()     = 0.0;

                // Voltage specifics
                NominalVoltage()        = 1.0;
                VoltageAngle()          = 0.0;
                VoltageMagnitude ()     = 1.0;
                voltageMagnitudeSq_     = 1.0;
                // realVoltage_      = 0.0;
                // imaginaryVoltage_ = 0.0;
                voltageBound_           = TBound ( 0.0, Const::REAL_INFTY );

                // Location specifics
                Country ()              = "";
                Area ()                 = 0;
                Zone ()                 = 0;
                Control ()              = Vertices::ControlType::PQ;
                Carrier ()              = EnergyCarrier::AC;

                // Status specifics
                Status()                = Vertices::BusStatus::active;
            }
        ///@}

        ///@Name Comparators
        ///@{
#pragma mark COMPARATORS
            /**
             * @brief      Inequality comparator.
             *
             * @param      rhs   The right hand side GeneratorProperties.
             *
             * @return     @p True if both vertices are @p not equal, @p False
             *     otherwise.
             */
            inline bool operator!=( ElectricalProperties const & rhs ) const
            {
                return !(this == rhs);
            }

            /**
             * @brief      Equality comparator.
             *
             * @param      rhs   The right hand side GeneratorProperties.
             *
             * @return     @p True if both vertices are equal, @p False
             *     otherwise.
             */
            inline bool operator==( ElectricalProperties const & rhs ) const
            {
                if ( Name()                 != rhs.Name()               ) return false;
                if ( Type()                 != rhs.Type()               ) return false;
                if ( X()                    != rhs.X()                  ) return false;
                if ( Y()                    != rhs.Y()                  ) return false;
                if ( ShuntSusceptance()     != rhs.ShuntSusceptance()   ) return false;
                if ( ShuntConductance()     != rhs.ShuntConductance()   ) return false;
                if ( NominalVoltage()       != rhs.NominalVoltage()     ) return false;
                if ( VoltageAngle()         != rhs.VoltageAngle()       ) return false;
                if ( VoltageMagnitude()     != rhs.VoltageMagnitude()   ) return false;
                if ( voltageMagnitudeSq_    != rhs.voltageMagnitudeSq_  ) return false;
                if ( voltageBound_          != rhs.voltageBound_        ) return false;
                if ( Area()                 != rhs.Area()               ) return false;
                if ( Zone()                 != rhs.Zone()               ) return false;
                if ( Control()              != rhs.Control()            ) return false;
                if ( Carrier()              != rhs.Carrier()            ) return false;
                if ( Status()               != rhs.Status()             ) return false;
            }
        ///@}

        /**@name Copy and swap idiom */
        ///@{
#pragma mark COPY_AND_SWAP_IDIOM
            /**
             * @brief Swapping the members of two ElectricalVertices
             *
             * @param lhs Left ElectricalProperties
             * @param rhs Right ElectricalProperties
             */
            friend void swap ( ElectricalProperties & lhs
                             , ElectricalProperties & rhs )
            { // Necessary for the copy and swap idiom
                using std::swap; // enable ADL
                // Basic vertex
                swap(lhs.name_,                     rhs.name_                    );
                swap(lhs.type_,                     rhs.type_                    );
                swap(lhs.xCoordinate_,              rhs.xCoordinate_             );
                swap(lhs.yCoordinate_,              rhs.yCoordinate_             );
                // Admittance
                swap(lhs.shuntSusceptance_,         rhs.shuntSusceptance_        );
                swap(lhs.shuntConductance_,         rhs.shuntConductance_        );
                // Voltage
                swap(lhs.nominalVoltage_,           rhs.nominalVoltage_          );
                swap(lhs.voltageAngle_,             rhs.voltageAngle_            );
                swap(lhs.voltageMagnitude_,         rhs.voltageMagnitude_        );
                swap(lhs.voltageMagnitudeSq_,       rhs.voltageMagnitudeSq_      );
                // swap(lhs.realVoltage_,              rhs.realVoltage_             );
                // swap(lhs.imaginaryVoltage_,         rhs.imaginaryVoltage_        );
                swap(lhs.voltageBound_,             rhs.voltageBound_            );
                // Location
                swap(lhs.area_,                     rhs.area_                    );
                swap(lhs.zone_,                     rhs.zone_                    );
                swap(lhs.control_,                  rhs.control_                 );
                swap(lhs.carrier_,                  rhs.carrier_                 );
                // Status
                swap(lhs.status_,                   rhs.status_                  );
            }
        ///@}

        /// @name Basic Properties
        ///@{
#pragma mark BASIC_PROPERTIES

            inline Types::name       Name()        const { return name_; }
            inline Types::name     & Name()              { return name_; }

            inline TVertexType       Type()        const { return type_; }
            inline TVertexType     & Type()              { return type_; }

            inline Types::real       X()           const { return xCoordinate_; }
            inline Types::real     & X()                 { return xCoordinate_; }

            inline Types::real       Y()           const { return yCoordinate_; }
            inline Types::real     & Y()                 { return yCoordinate_; }
        ///@}

        /**@name Admittance */
        ///@{
#pragma mark ADMITTANCE

            /**
             * @brief      Getter for the shunt susceptance
             *     @f$\shuntsusceptance(\vertex)@f$.
             * @details    The shunt susceptance is a function
             *     @f$\shuntsusceptance\colon\vertices\to\reals@f$. It is measured
             *     in MVAr injected at a voltage of 1.0 p.u.
             *
             * @return     The shunt susceptance @f$\shuntsusceptance(\vertex)@f$
             *     of @f$\vertex\in\vertices@f$.
             */
            inline Types::real ShuntSusceptance() const
            {
                return shuntSusceptance_;
            }

            /**
             * @brief      Getter and setter for the shunt susceptance
             *     @f$\shuntsusceptance(\vertex)@f$.
             * @details    The shunt susceptance is a function
             *     @f$\shuntsusceptance\colon\vertices\to\reals@f$. It is
             *     measured in MVAr injected at a voltage of 1.0 p.u.
             *
             * @code{.cpp}
             *      ElectricalProperties vertex;
             *      vertex.ShuntSusceptance() = 0.11;
             * @endcode
             *
             * @return     The shunt susceptance
             *     @f$\shuntsusceptance(\vertex)@f$ of
             *     @f$\vertex\in\vertices@f$.
             */
            inline Types::real & ShuntSusceptance()
            {
                return shuntSusceptance_;
            }

            /**
             * @brief      Getter for the shunt conductance
             *     @f$\shuntconductance(\vertex)@f$.
             * @details    The shunt conductance is a function
             *     @f$\shuntconductance\colon\vertices\to\reals@f$. It is
             *     measured in MW demanded at a voltage of 1.0 p.u.
             *
             * @return     The shunt conductance @f$\shuntconductance(\vertex)@f$
             *     of @f$\vertex\in\vertices@f$.
             */
            inline Types::real ShuntConductance() const
            {
                return shuntConductance_;
            }

            /**
             * @brief      Getter and setter for the shunt conductance
             *     @f$\shuntconductance(\vertex)@f$.
             * @details    The shunt conductance is a function
             *     @f$\shuntconductance\colon\vertices\to\reals@f$. It is measured
             *     in MW demanded at a voltage of 1.0 p.u.
             *
             * @code{.cpp}
             *      ElectricalProperties vertex;
             *      vertex.ShuntConductance() = 0.11;
             * @endcode
             *
             * @return     The shunt conductance @f$\shuntconductance(\vertex)@f$
             *     of @f$\vertex\in\vertices@f$.
             */
            inline Types::real & ShuntConductance ()
            {
                return shuntConductance_;
            }
        ///@}

        /**@name Voltage */
        ///@{
#pragma mark VOLTAGE
            /**
             * @brief      Getter for the nominal voltage
             *     @f$\voltagenominal@f$ (also known as base voltage; in kV).
             *
             * @return     The nominal voltage @f$\voltagenominal@f$ in kV.
             */
            inline Types::real NominalVoltage () const
            {
                return nominalVoltage_;
            }

            /**
             * @brief      Getter and setter for the nominal voltage
             *     @f$\voltagenominal@f$ (also known as base voltage; in kV).
             *
             * @return     The nominal voltage @f$\voltagenominal@f$ in kV.
             */
            inline Types::real & NominalVoltage ()
            {
                return nominalVoltage_;
            }

            /**
             * @brief      Getter for the voltage magnitude @f$\vmagnitude@f$.
             * @details    The voltage magnitude @f$\voltagenominal@f$ is in per
             *     unit (p.u.) of the nominal voltage @f$\voltagenominal@f$. It
             *     represents a set point.
             *
             * @return     The voltage magnitude @f$\voltagenominal@f$.
             */
            inline Types::real VoltageMagnitude () const
            {
                return voltageMagnitude_;
            }

            /**
             * @brief      Getter and setter for the voltage magnitude
             *     @f$\vmagnitude@f$.
             * @details    The voltage magnitude @f$\vmagnitude@f$ is in per
             *     unit (p.u.) of the nominal voltage @f$\voltagenominal@f$. It
             *     represents a set point.
             *
             * @return     The voltage magnitude @f$\vmagnitude@f$.
             */
            inline Types::real & VoltageMagnitude ()
            {
                return voltageMagnitude_;
            }

            /**
             * @brief      Getter for the voltage angle @f$\vangle(\vertex)@f$.
             * @details    The voltage angle is a function
             *     @f$\vangle\colon\vertices\to\reals@f$. It is measured in
             *     degree.
             *
             * @note       It is used for the data's snapshot and/or
             *     optimization's result.
             *
             * @return     The voltage angle @f$\vangle(\vertex)@f$ at vertex
             *     @f$\vertex\in\vertices@f$.
             */
            inline Types::real VoltageAngle () const
            {
                return voltageAngle_;
            }

            /**
             * @brief      Getter for the voltage angle @f$\vangle(\vertex)@f$.
             * @details    The voltage angle is a function
             *     @f$\vangle\colon\vertices\to\reals@f$. It is measured in
             *     degree.
             *
             * @code{.cpp}
             *      ElectricalProperties vertex;
             *      vertex.ShuntConductance() = 0.11;
             * @endcode
             *
             * @note       It is used for the data's snapshot and/or
             *     optimization's result.
             *
             * @return     The voltage angle @f$\vangle(\vertex)@f$ at vertex
             *     @f$\vertex\in\vertices@f$.
             */
            inline Types::real & VoltageAngle ()
            {
                return voltageAngle_;
            }

            /**
             * @brief      Getter for the minimum voltage magnitude
             *     @f$\voltagemin@f$.
             * @details    The voltage magnitude is in per unit (p.u.) of the
             *     nominal voltage @f$\voltagenominal@f$.
             *
             * @return     The minimum voltage magnitude @f$\voltagemin@f$.
             */
            inline Types::real MinimumVoltage () const
            {
                return voltageBound_.Minimum();
            }

            /**
             * @brief      Getter and setter for the minimum voltage
             *     magnitude @f$\voltagemin@f$.
             * @details    The voltage magnitude is in per unit (p.u.) of the
             *     nominal voltage @f$\voltagenominal@f$.
             *
             * @code{.cpp}
             *      ElectricalProperties vertex;
             *      vertex.MinimumVoltage() = 0;
             * @endcode
             *
             * @return     The minimum voltage magnitude @f$\voltagemin@f$.
             */
            inline Types::real & MinimumVoltage ()
            {
                return voltageBound_.Minimum();
            }

            /**
             * @brief      Getter for the maximum voltage magnitude
             *     @f$\voltagemax@f$.
             * @details    The voltage magnitude is in per unit (p.u.) of the
             *     nominal voltage @f$\voltagenominal@f$.
             *
             * @return     The maximum voltage magnitude @f$\voltagemax@f$.
             */
            inline Types::real MaximumVoltage () const
            {
                return voltageBound_.Maximum();
            }

            /**
             * @brief      Getter and setter for the maximum voltage
             *     magnitude @f$\voltagemax@f$.
             * @details    The voltage magnitude is in p.u.
             *
             * @code{.cpp}
             *      ElectricalProperties vertex;
             *      vertex.MaximumVoltage() = 111;
             * @endcode
             *
             * @return     The maximum voltage magnitude @f$\voltagemax@f$.
             */
            inline Types::real & MaximumVoltage ()
            {
                return voltageBound_.Maximum();
            }
        ///@}

        /**@name Type specific information */
        ///@{
#pragma mark TYPE_SPECIFIC_INFORMATION

            /**
             * @brief      Getter for the country
             * @details    Used in PyPSA for example to specify the location
             *     of the vertex.
             *
             * @return     The country of the vertex.
             */
            inline Types::name Country () const
            {
                return country_;
            }

            /**
             * @brief      Getter and setter for the country
             * @details    Used in PyPSA for example to specify the location
             *     of the vertex.
             *
             * @return     The country of the vertex.
             */
            inline Types::name & Country ()
            {
                return country_;
            }

            /**
             * @brief      Getter for the bus area number.
             * @details    Bus area (1 - 99) indicates in which company/region
             *     the station is located. A two digit integer from 0 to 99
             *     indicating the company or region in which the line is
             *     located. This area number should be the same as the area of
             *     one of the two terminal vertices. Tie line it indicates the
             *     ownership or area to which the losses should be assigned.
             *     This area is not related to the meter bus location.
             *
             * @note       If the value is 0 this means that there is no data
             *     available or there is no area.
             *
             * @return     The bus area number.
             */
            inline Types::index Area () const
            {
                return area_;
            }

            /**
             * @brief      Getter and setter for the bus area number.
             * @details    Bus area (1 - 99) indicates in which company/region
             *     the station is located. A two digit integer from 0 to 99
             *     indicating the company or region in which the line is
             *     located. This area number should be the same as the area of
             *     one of the two terminal vertices. Tie line it indicates the
             *     ownership or area to which the losses should be assigned.
             *     This area is not related to the meter bus location.
             *
             * @note       If the value is 0 this means that there is no data
             *     available or there is no area.
             *
             * @code{.cpp}
             *      ElectricalProperties vertex;
             *      vertex.Area() = 11;
             * @endcode
             *
             * @return     The bus area number.
             */
            inline Types::index & Area ()
            {
                return area_;
            }

            /**
             * @brief      Getter for the loss zone.
             * @details    A three digit integer from 0 to 999 for defining
             *     zones of loss calculation.
             *
             * @note       If the value is 0 this means that there is no zone.
             *
             * @return     The loss zone.
             */
            inline Types::index Zone () const
            {
                return zone_;
            }

            /**
             * @brief      Getter and setter for the loss zone.
             * @details    A three digit integer from 0 to 999 for defining
             *     zones of loss calculation.
             *
             * @note       If the value is 0 this means that there is no zone.
             *
             * @code{.cpp}
             *      ElectricalProperties vertex;
             *      vertex.Zone() = 11;
             * @endcode
             *
             * @return     The loss zone.
             */
            inline Types::index & Zone ()
            {
                return zone_;
            }

            /**
             * @brief      Getter for the bus control type strategy.
             * @details    The bus control type strategy can be either PQ, PV,
             *     or slack. The latter represents the reference bus. The
             *     voltage angle of the reference bus is usually set to 0.
             *
             * @see Type#Vertices#ControlType
             *
             * @return     The bus control type strategy.
             */
            inline Vertices::ControlType Control () const
            {
                return control_;
            }

            /**
             * @brief      Getter and setter for the bus control type
             *     strategy.
             * @details    The bus control type strategy can be either PQ, PV,
             *     or slack. The latter represents the reference bus. The
             *     voltage angle of the reference bus is usually set to 0.
             *
             * @code{.cpp}
             *      ElectricalProperties vertex;
             *      vertex.Control() = Vertices::ControlType::PQ;
             * @endcode
             *
             * @see Type#Vertices#ControlType
             *
             * @return     The bus control type strategy.
             */
            inline Vertices::ControlType & Control ()
            {
                return control_;
            }

            /**
             * @brief      Getter for the energy carrier type.
             * @details    The energy carrier type describes the vertex is for
             *     example connected to @f$\ac@f$ or @f$\dc@f$.
             *
             * @see Type#Vertices#EnergyCarrier
             *
             * @return     The energy carrier type.
             */
            inline Vertices::EnergyCarrier Carrier () const
            {
                return carrier_;
            }

            /**
             * @brief      Getter and setter for the energy carrier type.
             * @details    The energy carrier type describes if the electrical
             *     vertex is connected to @f$\ac@f$ or @f$\dc@f$. If the
             *     vertex is not an electrical bus it might be @p heat or @p
             *     gas.
             *
             * @code{.cpp}
             *      ElectricalProperties vertex;
             *      vertex.Carrier() = Vertices::EnergyCarrier::DC;
             * @endcode
             *
             * @see Type#Vertices#EnergyCarrier
             *
             * @return     The energy carrier type.
             */
            inline Vertices::EnergyCarrier & Carrier ()
            {
                return carrier_;
            }
        ///@}

        /**@name Status */
        ///@{
#pragma mark STATUS

            /**
             * @brief      Determines if the electrical vertex is active.
             *
             * @see Status
             *
             * @return     @p True if active (on), @p False otherwise (unknown).
             */
            inline bool IsActive () const
            {
                return Vertices::BusStatus::active == Status();
            }

            /**
             * @brief      Status of the electrical vertex.
             *
             * @see Type#Vertices#BusStatus
             *
             * @return     The status can have a different status.
             */
            inline Vertices::BusStatus & Status ()
            {
                return status_;
            }

            /**
             * @brief      Status of the electrical vertex.
             *
             * @see Type#Vertices#BusStatus
             *
             * @return     The status can have a different status.
             */
            inline Vertices::BusStatus const & Status () const
            {
                return status_;
            }
        ///@}

        /**@name Output */
        ///@{
#pragma mark OUTPUT_METHODS
            /**
             * @brief      Header out stream.
             * @details    List all IEEE standard input data.
             *
             * @param      outputStream  The stream to write data to, e.g., std::cout.
             */
            static void HeaderLong ( std::ostream & outputStream )
            {
                outputStream
                    << std::setw(6)     << "ID"
                    << std::setw(6)     << "Type"
                    // << std::setw(10)    << "RealPowerLoad"
                    // << std::setw(20)    << "ReactivePowerLoad"
                    << std::setw(20)    << "ShuntSusceptance"
                    << std::setw(20)    << "ShuntConductance"
                    << std::setw(6)     << "Area"
                    << std::setw(10)    << "VoltageMagnitude"
                    << std::setw(10)    << "VoltageAngle"
                    << std::setw(10)    << "BaseKV"
                    << std::setw(6)     << "Zone"
                    << std::setw(20)    << "MaximumVoltage"
                    << std::setw(20)    << "MinimumVoltage"
                    << std::endl;
            }

            /**
             * @brief      Header out stream.
             * @details    List all IEEE standard input data.
             *
             * @param      outputStream  The stream to write data to, e.g., std::cout.
             */
            static inline void Header ( std::ostream & outputStream )
            {
                outputStream
                    << std::setw(6)     << "bus_i"
                    << std::setw(6)     << "type"
                    // << std::setw(10)    << "Pd"
                    // << std::setw(10)    << "Qd"
                    << std::setw(10)    << "Gs"
                    << std::setw(10)    << "Bs"
                    << std::setw(6)     << "area"
                    << std::setw(10)    << "Vm"
                    << std::setw(10)    << "Va"
                    << std::setw(10)    << "baseKV"
                    << std::setw(6)     << "zone"
                    << std::setw(10)    << "Vmax"
                    << std::setw(10)    << "Vmin"
                    << std::endl;
            }

            /**
             * @brief      Line out stream.
             * @details    List all IEEE standard input data.
             *
             * @param      outputStream  The stream to write data to, e.g., std::cout.
             * @param[in]  baseMva       The base MVA.
             */
            inline void Line ( std::ostream & outputStream
                             , Types::real    baseMva = 1 ) const
            {
                outputStream
                    << std::setprecision(2)
                    << std::fixed
                    << std::setw(6)     << Name()
                    << std::setw(6)     << Vertices::to_underlying( Type() )
                    << std::setw(10)    << ShuntConductance()  * baseMva
                    << std::setw(10)    << ShuntSusceptance()  * baseMva
                    << std::setw(6)     << Area()
                    << std::setw(10)    << VoltageMagnitude()
                    << std::setw(10)    << VoltageAngle()
                    << std::setw(10)    << NominalVoltage()
                    << std::setw(6)     << Zone()
                    << std::setw(10)    << MaximumVoltage()
                    << std::setw(10)    << MinimumVoltage()
                    << std::endl;
            }

            /**
             * @brief      Writes the electrical property as a line.
             * @details    List all IEEE standard input data.
             *
             * @param      outputStream  The stream to write data to, e.g., std::cout.
             * @param[in]  identifier    The identifier.
             * @param[in]  baseMva       The base MVA.
             */
            inline void Line ( std::ostream  & outputStream
                             , Types::vertexId identifier
                             , Types::real     baseMva = 1 ) const
            {
                outputStream
                    << std::setprecision(2)
                    << std::fixed
                    << std::setw(6)     << identifier
                    << std::setw(15)    << Name()
                    << std::setw(6)     << Vertices::to_underlying( Type() )
                    // << std::setw(10)    << RealPowerLoad()     * baseMva
                    // << std::setw(10)    << ReactivePowerLoad() * baseMva
                    << std::setw(10)    << ShuntConductance()  * baseMva
                    << std::setw(10)    << ShuntSusceptance()  * baseMva
                    << std::setw(6)     << Area()
                    << std::setw(10)    << VoltageMagnitude()
                    << std::setw(10)    << VoltageAngle()
                    << std::setw(10)    << NominalVoltage()
                    << std::setw(6)     << Zone()
                    << std::setw(10)    << MaximumVoltage()
                    << std::setw(10)    << MinimumVoltage()
                    << std::endl;
            }

            /**
             * @brief      Write the electrical property to an output stream.
             *
             * @param      outputStream  The stream to write data to, e.g., std::cout.
             * @param      rhs           The right hand side electrical property.
             *
             * @return     The output stream.
             */
            friend std::ostream & operator<< ( std::ostream       & outputStream
                                             , TProperties const  & rhs )
            {
                outputStream
                    << std::setprecision(2)
                    << std::fixed
                    << std::endl
                    << "Bus " << rhs.Name()     << std::endl
                    << std::string(20, '-')     << std::endl
                    << std::setw(30) << "ID: "                  << std::setw(10) << rhs.Name()
                    // << std::setw(20) << "load: "                << std::setw(10) << rhs.RealPowerLoad()         << std::setw(25) << " p.u.       (real, MW), "
                    //                                             << std::setw(10) << rhs.ReactivePowerLoad()     << std::setw(25) << " p.u. (reactive, MVar), "  << std::endl
                    << std::setw(20) << "shunt: "               << std::setw(10) << rhs.ShuntSusceptance()      << std::setw(25) << " p.u.    (susceptance), "
                                                                << std::setw(10) << rhs.ShuntConductance()      << std::setw(25) << " p.u.    (conductance), "  << std::endl
                    << std::setw(20) << "voltage bounds: "      << std::setw(10) << rhs.MinimumVoltage()        << std::setw(25) << " p.u.        (vmin, V), "
                                                                << std::setw(10) << rhs.MaximumVoltage()        << std::setw(25) << " p.u.        (vmax, V), "  << std::endl
                    << std::setw(20) << "voltage snapshot: "    << std::setw(10) << rhs.VoltageMagnitude()      << std::setw(25) << "               (Vm, V), "
                    << std::setw(20) << "area: "                << std::setw(10) << rhs.Area()                  << std::setw(25) << ""                          << std::endl
                    << std::setw(20) << "zone: "                << std::setw(10) << rhs.Zone()                  << std::setw(25) << ""                          << std::endl
                    << std::setw(20) << "type: "                << std::setw(10) << rhs.Type()                  << std::setw(25) << ""                          << std::endl;
                return outputStream;
            }
        ///@}

    private:

#pragma mark MEMBERS
        ///@name Basic Property Members
        ///@{
            Types::name     name_;                  /**< name of the vertex */
            TVertexType     type_;                  /**< vertex type representing either source, sink or intermediate */
            Types::real     xCoordinate_;           /**< x-coordinate of the point if available */
            Types::real     yCoordinate_;           /**< y-coordinate of the point if available */
        ///@}

        /**@name Admittance Related Members */
        ///@{
            Types::real     shuntSusceptance_;      /**< The shunt susceptance @f$\shuntsusceptance(\vertex)@f$. */
            Types::real     shuntConductance_;      /**< The shunt conductance @f$\shuntconductance(\vertex)@f$. */
        ///@}

        /**@name Voltage Related Members */
        ///@{
            Types::real     nominalVoltage_;        /**< The nominal voltage also known as base voltage measured
                                                     *      in kV.
                                                     */
            Types::real     voltageAngle_;          /**< The voltage angle @f$\vangle(\vertex)@f$ that represents
                                                     *      a snapshot of the voltage angle, i.e., final voltage
                                                     *      angle from data.
                                                     */
            Types::real     voltageMagnitude_;      /**< Voltage magnitude @f$\vmagnitude(\vertex)@f$ including
                                                     *      a snapshot (p.u. set point), i.e., final voltage
                                                     *      from data.
                                                     */
            Types::real     voltageMagnitudeSq_;    /**< Voltage magnitude squared variable */
            // Types::real     realVoltage_;        /**< Real voltage */
            // Types::real     imaginaryVoltage_;   /**< Imaginary voltage */
            TBound          voltageBound_;          /**< The voltage limits @f$\voltage := [\voltagemin,\voltagemax]@f$
                                                     *      in per unit (p.u.) of the nominal voltage @f$\voltagenominal@f$.
                                                     */
        ///@}

        /**@name Location Specific Members */
        ///@{
            Types::name     country_;               /** Country */
            Types::index    area_;                  /**< Bus area (1 - 99) indicates in which company/region
                                                     *      the station is located, 0 means data unavailable.
                                                     *      A two digit integer from 0 to 99 indicating the
                                                     *      company or region in which the line is located.
                                                     *      This area number should be the same as the area of
                                                     *      one of the two terminal vertices.
                                                     *      Tie line it indicates the ownership or area to
                                                     *      which the losses should be assigned.
                                                     *      This area is not related to the meter bus location.
                                                     */
            Types::index    zone_;                  /**< Three digit integer from 0 to 999 for defining
                                                     *   zones of loss calculation.  A 0 means no zone.
                                                     */
            Vertices::ControlType     control_;     /**< The control type such as PV. */
            Vertices::EnergyCarrier   carrier_;     /**< The energy carrier used at this bus such as AC. */
        ///@}

        /**@name Status Members */
        ///@{
            Vertices::BusStatus status_;            /**< Station status: active - true, inactive - false */
        ///@}
};

} // namespace egoa::Vertices

#endif // EGOA__DATA_STRUCTURES__VERTICES__ELECTRICAL_PROPERTIES_HPP

/*
 * Type.hpp
 *
 *  Created on: Sep 07, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__VERTICES__TYPE_HPP
#define EGOA__DATA_STRUCTURES__VERTICES__TYPE_HPP

#include "Auxiliary/Types.hpp"

namespace egoa::Vertices {

#pragma mark VERTEX_TYPES
/**
 * @brief      Class for basic vertex types.
 */
enum class BasicVertexType {
    sink         = 0,
    source       = 1,
    intermediate = 4,
    unknown      = 99
};

/**
 * @brief      Class for CDF bus types.
 */
enum class CdfBusType {
    load    = 0,            /**< 0 - unregulated bus also called load bus */
    mvar    = 1,            /**< 1 - bus holding Mvar generation within voltage limits */
    voltage = 2,            /**< 2 - bus holding bus voltage within Mvar limits, i.e., regulated generator bus */
    slack   = 3,            /**< 3 - bus holding bus voltage and angle, i.e., swing/reference/slack bus */
    unknown = 99
};

/**
 * @brief      Class for IEEE bus types.
 */
enum class IeeeBusType {
    load        = 1,        /**< 1 - PQ, unregulated bus also called load bus */
    generator   = 2,        /**< 2 - PV, ? */
    slack       = 3,        /**< 3 - ref, bus holding bus voltage and angle, i.e., swing/reference/slack bus */
    isolated    = 4,        /**< 4 - isolated */
    unknown     = 99
};

/**
 * @brief      Class for energy carrier.
 */
enum class EnergyCarrier {
    AC             = 0,     /**< AC carrier */
    DC             = 1,     /**< DC carrier */
    heat           = 2,
    gas            = 3,
    unknown        = 99     /**< unknown    */
};

/**
 * @brief      Generator/Vertex control strategy
 * @detail     P, Q and V are control strategies for the power flow (PF).
 *     Either PQ, PV or Slack.
 */
enum class ControlType {
    PQ          = 0,      /**< PQ control */
    PV          = 1,      /**< PV control */
    slack       = 2,      /**< Slack */
    unknown     = 99      /**< unknown */
};


#pragma mark BOUND_TYPES
/**
 * @brief      Class for bound types.
 */
enum class BoundType {
    unbounded     = 0,      /**< Generation and load minimum and maximum are set to 0 to infinity, respectively */
    bounded       = 1,      /**< Bounded uses the minimum and maximum generation and load from the data */
    exact         = 2,      /**< Exact load and generation bounds from the available snapshot */
    pureunbounded = 3,      /**< Generation and load minimum and maximum are set to 0 to infinity,
                                 respectively, with exception of buses having
                                 both generator and load. Then the load is
                                 bounded from 0 to its maximum.*/
    unknown       = 99      /**< unknown */
};

#pragma mark GENERATOR_TYPES
/**
 * @brief      Class for generator types.
 */
enum class GeneratorType {
    coal          = 0,      /**< Coal */
    browncoal     = 1,      /**< Brown coal power producer */
    hardcoal      = 2,      /**< Hard coal power producer */
    nuclear       = 3,      /**< Nuclear power plants */
    oil           = 4,      /**< Oil */
    // renewables
    solar         = 10,     /**< Solar generator */
    onwind        = 11,     /**< Onshore wind producer */
    offwind       = 12,     /**< Offshore wind producer */
    ror           = 13,     /**< Run of river power */
    ccgt          = 14,     /**< Combined Cycle Gas Turbines (CCGT) */
    ocgt          = 15,     /**< Open Cycle Gas Turbines (OCGT) */
    biomass       = 16,     /**< Biomass */ 
    battery       = 17,     /**< Battery */
    // ...
    unknown       = 99      /**< unknown */
};

#pragma mark VERTEX_STATUS

/**
 * @brief      Class for bus status used in the Electrical Vertex.
 */
enum class BusStatus {
    inactive        = 0
    , active        = 1
    , unknown       = 99
};

enum class PowerSign {
    positive        = 0
    , negative      = 1
    , unknown       = 99
};

///@name Conversion methods
///@{
#pragma mark CONVERSION_METHODS

    /**
     * @brief      Converts a string to a basic vertex type.
     *
     * @param      type  The string having the basic vertex type information.
     *
     * @return     The corresponding BasicVertexType type.
     */
    inline BasicVertexType StringToBasicVertexType ( Types::string const & type )
    {
        if ( "sink" == type ) {
            return Vertices::BasicVertexType::sink;
        } else if ( "source" == type ) {
            return Vertices::BasicVertexType::source;
        } else if ( "intermediate" == type ) {
            return Vertices::BasicVertexType::intermediate;
        } else {
            return Vertices::BasicVertexType::unknown;
        }
    }

    /**
     * @brief      Converts a string to a CDF bus type.
     *
     * @param      type  The string having the CDF bus type information.
     *
     * @return     The corresponding CdfBusType type.
     */
    inline CdfBusType StringToCdfBusType ( Types::string const & type )
    {
        if ( "load" == type ) {
            return Vertices::CdfBusType::load;
        } else if ( "mvar" == type ) {
            return Vertices::CdfBusType::mvar;
        } else if ( "voltage" == type ) {
            return Vertices::CdfBusType::voltage;
        } else if ( "slack" == type ) {
            return Vertices::CdfBusType::slack;
        } else {
            return Vertices::CdfBusType::unknown;
        }
    }

    /**
     * @brief      Converts a string to a IEEE bus type.
     *
     * @param      type  The string having the IEEE bus type information.
     *
     * @return     The corresponding IeeeBusType type.
     */
    inline IeeeBusType StringToIeeeBusType ( Types::string const & type )
    {
        if ( "load" == type ) {
            return Vertices::IeeeBusType::load;
        } else if ( "generator" == type ) {
            return Vertices::IeeeBusType::generator;
        } else if ( "slack" == type ) {
            return Vertices::IeeeBusType::slack;
        } else if ( "isolated" == type ) {
            return Vertices::IeeeBusType::isolated;
        } else {
            return Vertices::IeeeBusType::unknown;
        }
    }

    /**
     * @brief      Converts a string to a bound type.
     *
     * @param      type  The string having the bound type information.
     *
     * @return     The corresponding BoundType type.
     */
    inline BoundType StringToBoundType ( Types::string const & type )
    {
        if ( "unbounded" == type ) {
            return Vertices::BoundType::unbounded;
        } else if ( "bounded" == type ) {
            return Vertices::BoundType::bounded;
        } else if ( "exact" == type ) {
            return Vertices::BoundType::exact;
        } else if ( "pureunbounded" == type ) {
            return Vertices::BoundType::pureunbounded;
        } else {
            return Vertices::BoundType::unknown;
        }
    }

    /**
     * @brief      Converts a string to a generator type.
     *
     * @param      type  The string having the generator type information.
     *
     * @return     The corresponding GeneratorType type.
     */
    inline GeneratorType StringToGeneratorType ( Types::string const & type )
    {
        if ( "coal" == type ) {
            return GeneratorType::coal;
        } else if ( "browncoal" == type ) {
            return GeneratorType::browncoal;
        } else if ( "hardcoal" == type ) {
            return GeneratorType::hardcoal;
        } else if ( "nuclear" == type ) {
            return GeneratorType::nuclear;
        } else if ( "oil" == type ) {
            return GeneratorType::oil;
        } else if ( "solar" == type ) {
            return GeneratorType::solar;
        } else if ( "onwind" == type ) {
            return GeneratorType::onwind;
        } else if ( "offwind" == type ) {
            return GeneratorType::offwind;
        } else if ( "ror" == type ) {
            return GeneratorType::ror;
        } else if ( "ccgt" == type ) {
            return GeneratorType::ccgt;
        } else if ( "ocgt" == type ) {
            return GeneratorType::ocgt;
        } else if ( "biomass" == type ) {
            return GeneratorType::biomass;
        } else if ( "battery" == type ) {
            return GeneratorType::battery;
        } else {
            return GeneratorType::unknown;
        }
    }

    /**
     * @brief      Converts a string to a bus status.
     *
     * @param      type  The string having the bus status information.
     *
     * @return     The corresponding BusStatus type.
     */
    inline BusStatus StringToBusStatus ( Types::string const & type )
    {
        if ( "inactive" == type ) {
            return Vertices::BusStatus::inactive;
        } else if ( "active" == type ) {
            return Vertices::BusStatus::active;
        } else {
            return Vertices::BusStatus::unknown;
        }
    }

    /**
     * @brief      Converts a BusStatus to a boolean.
     *
     * @param      type  The bus status.
     *
     * @return     The corresponding boolean.
     */
    inline bool BusStatusToBoolean ( BusStatus const & type )
    {
        if ( Vertices::BusStatus::inactive == type ) {
            return false;
        } else if ( Vertices::BusStatus::active == type ) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief      Converts a string to a power sign.
     *
     * @param      type  The string having the power sign information.
     *
     * @return     The corresponding PowerSign type.
     */
    inline PowerSign StringToPowerSign ( Types::string const & type )
    {
        if ( "positive" == type ) {
            return Vertices::PowerSign::positive;
        } else if ( "negative" == type ) {
            return Vertices::PowerSign::negative;
        } else {
            return Vertices::PowerSign::unknown;
        }
    }

    /**
     * @brief      Converts the power sign to an integer.
     *
     * @param      type  The power sign.
     *
     * @return     @p 1 if positive, @p -1 if negative, and @p 1 if unknown.
     */
    inline Types::integer PowerSignToInteger ( PowerSign const & type )
    {
        if ( Vertices::PowerSign::positive == type ) {
            return 1;
        } else if ( Vertices::PowerSign::negative == type ) {
            return -1;
        } else {
            return 1;
        }
    }

    /**
     * @brief      Converts a string to a energy carrier sign.
     *
     * @param      type  The string having the energy carrier information.
     *
     * @return     The corresponding EnergyCarrier type.
     */
    inline EnergyCarrier StringToEnergyCarrier ( Types::string const & type )
    {
        if ( "AC" == type ) {
            return Vertices::EnergyCarrier::AC;
        } else if ( "DC" == type ) {
            return Vertices::EnergyCarrier::DC;
        } else if ( "heat" == type ) {
            return Vertices::EnergyCarrier::heat;
        } else if ( "gas" == type ) {
            return Vertices::EnergyCarrier::gas;
        } else {
            return Vertices::EnergyCarrier::unknown;
        }
    }

    /**
     * @brief      Converts a string to a control type.
     *
     * @param      type  The string having the control type information.
     *
     * @return     The corresponding ControlType type.
     */
    inline ControlType StringToControlType ( Types::string const & type )
    {
        if ( "PQ" == type ) {
            return Vertices::ControlType::PQ;
        } else if ( "PV" == type ) {
            return Vertices::ControlType::PV;
        } else if ( "slack" == type ) {
            return Vertices::ControlType::slack;
        } else {
            return Vertices::ControlType::unknown;
        }
    }
///@}

///@name Output operator
///@{
#pragma mark OUTPUT_OPERATOR

    inline std::ostream & operator<< ( std::ostream          & os
                                     , BasicVertexType const & rhs ) 
    {
        if      ( rhs == BasicVertexType::sink         ){ os << "sink";         } 
        else if ( rhs == BasicVertexType::source       ){ os << "source";       } 
        else if ( rhs == BasicVertexType::intermediate ){ os << "intermediate"; } 
        else                                            { os << "unknown";      }
        return os;
    }

    inline std::ostream & operator<< ( std::ostream     & os
                                     , CdfBusType const & rhs ) 
    {
        if      ( rhs == CdfBusType::load    ){ os <<       "load bus (Type 0)"; } /** unregulated bus also called load bus */
        else if ( rhs == CdfBusType::mvar    ){ os << "Mvar generator (Type 1)"; } /** bus holding Mvar generation within voltage limits */        
        else if ( rhs == CdfBusType::voltage ){ os <<    "voltage bus (Type 2)"; } /** bus holding bus voltage within Mvar limits, i.e., regulated generator bus */
        else if ( rhs == CdfBusType::slack   ){ os <<      "slack bus (Type 3)"; } /** bus holding bus voltage and angle, i.e., swing/reference/slack bus */
        else                                  { os <<                 "unknown"; }
        return os;
    }

    inline std::ostream & operator<< ( std::ostream      & os
                                     , IeeeBusType const & rhs ) 
    {
        if      ( rhs == IeeeBusType::load      ){ os <<    "load bus (Type 1)"; } /** bus with load only */
        else if ( rhs == IeeeBusType::generator ){ os <<   "generator (Type 2)"; } /**@todo Generator, but definition is missing */
        else if ( rhs == IeeeBusType::slack     ){ os <<   "slack bus (Type 3)"; } /** Slack */
        else                                     { os <<              "unknown"; }
        return os;
    }

    inline std::ostream & operator<< ( std::ostream    & os
                                     , BoundType const & rhs ) 
    {
        if      ( rhs == BoundType::unbounded       ){ os << "unbounded";   } 
        else if ( rhs == BoundType::bounded         ){ os << "bounded";     } 
        else if ( rhs == BoundType::exact           ){ os << "exact";       } 
        else if ( rhs == BoundType::pureunbounded   ){ os << "pure_unbounded";} 
        else                                         { os << "unknown";     }
        return os;
    }

    inline std::ostream & operator<< ( std::ostream    & os
                                     , BusStatus const & rhs ) 
    {
        if      ( rhs == Vertices::BusStatus::inactive ){ os << "inactive"; } 
        else if ( rhs == Vertices::BusStatus::active   ){ os << "active";   } 
        else                                            { os << "unknown";  }
        return os;
    }

    inline std::ostream & operator<< ( std::ostream        & os
                                     , EnergyCarrier const & rhs ) 
    {
        if      ( rhs == Vertices::EnergyCarrier::AC   ){ os << "AC";       } 
        else if ( rhs == Vertices::EnergyCarrier::DC   ){ os << "DC";       } 
        else if ( rhs == Vertices::EnergyCarrier::heat ){ os << "heat";     } 
        else if ( rhs == Vertices::EnergyCarrier::gas  ){ os << "gas";      } 
        else                                            { os << "unknown";  }
        return os;
    }

    inline std::ostream & operator<< ( std::ostream      & os
                                     , ControlType const & rhs ) 
    {
        if      ( rhs == Vertices::ControlType::PQ    ){ os << "PQ";       } 
        else if ( rhs == Vertices::ControlType::PV    ){ os << "PV";       } 
        else if ( rhs == Vertices::ControlType::slack ){ os << "slack";    } 
        else                                           { os << "unknown";  }
        return os;
    }

    inline std::ostream & operator<< ( std::ostream        & os
                                     , GeneratorType const & rhs ) 
    {
        if ( GeneratorType::coal == rhs ) {
            os << "coal" ;
        } else if ( GeneratorType::browncoal == rhs ) {
            os << "browncoal" ;
        } else if ( GeneratorType::hardcoal == rhs ) {
            os << "hardcoal" ;
        } else if ( GeneratorType::nuclear == rhs ) {
            os << "nuclear" ;
        } else if ( GeneratorType::oil == rhs ) {
            os << "oil" ;
        } else if ( GeneratorType::solar == rhs ) {
            os << "solar" ;
        } else if ( GeneratorType::onwind == rhs ) {
            os << "onwind" ;
        } else if ( GeneratorType::offwind == rhs ) {
            os << "offwind" ;
        } else if ( GeneratorType::ror == rhs ) {
            os << "ror" ;
        } else if ( GeneratorType::ccgt == rhs ) {
            os << "ccgt" ;
        } else if ( GeneratorType::ocgt == rhs ) {
            os << "ocgt" ;
        } else if ( GeneratorType::biomass == rhs ) {
            os << "biomass" ;
        } else if ( GeneratorType::battery == rhs ) {
            os << "battery" ;
        } else {
            os << "unknown" ;
        }
        return os;
    }
///@}

/**@name Enum conversion */ 
///@{
#pragma mark ENUM_CONVERSION

/**
 * https://stackoverflow.com/questions/8357240/how-to-automatically-convert-strongly-typed-enum-into-int
 */
    template <typename E>
    constexpr auto to_underlying(E e) noexcept
    {
        return static_cast<std::underlying_type_t<E>>(e);
    }

    template< typename E , typename T>
    constexpr 
    inline 
    typename 
    std::enable_if< std::is_enum<E>::value && std::is_integral<T>::value, 
                    E 
                  >::type 
    to_enum( T value ) noexcept {
        return static_cast<E>( value );
    }
///@}

} // namespace egoa::Vertices

#endif // EGOA__DATA_STRUCTURES__VERTICES__TYPE_HPP
/*
 * LoadProperties.hpp
 *
 *  Created on: Sep 07, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__GRAPHS__VERTICES__LOAD_PROPERTIES_HPP
#define EGOA__DATA_STRUCTURES__GRAPHS__VERTICES__LOAD_PROPERTIES_HPP

#include "Type.hpp"
#include "DataStructures/Bound.hpp"

namespace egoa::Vertices {

/**
 * @brief      Class having all load properties.
 *
 * @tparam     VertexType  Represents the type specification, e.g., IeeeBusType.
 * 
 * @pre        The vertex type should provide the option @p load.
 */
template<class VertexType = Vertices::IeeeBusType>
class LoadProperties {

    // Template type aliasing
    using TVertexType   = VertexType;
    using TBound        = Bound<Types::real>;

    public:
        /**@name Constructors and Destructor */
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS
            
            /**
             * @brief      Constructs the object.
             */
            LoadProperties ( )
            : name_("") 
            , type_(TVertexType::load) 
            , realPowerLoad_(0.0)
            , realPowerLoadBound_( TBound( 0.0, 0.0 ) )
            , reactivePowerLoad_(0.0)
            , reactivePowerLoadBound_( TBound( 0.0, 0.0 ) )
            {}

            /**
             * @brief      Constructs the object.
             *
             * @param[in]  name  The name of the vertex.
             */
            LoadProperties ( Types::name name )
            : name_(name)
            , type_(TVertexType::load) 
            , realPowerLoad_(0.0)
            , realPowerLoadBound_( TBound( 0.0, 0.0 ) )
            , reactivePowerLoad_(0.0)
            , reactivePowerLoadBound_( TBound( 0.0, 0.0 ) )
            {}
        ///@}

        /**@name Real power */
        ///@{
#pragma mark GENERAL_INFORMATION

            /**
             * @brief      Getter for the name of the vertex.
             *
             * @return     The name of the vertex.
             */
            inline Types::name & Name ()
            { 
                return name_; 
            }

            /**
             * @brief      Getter and setter for the name of the vertex.
             *
             * @return     The name of the vertex.
             */
            inline Types::name Name () const 
            { 
                return name_; 
            }

            /**
             * @brief      Getter for the type of the vertex.
             *
             * @return     The type of the vertex.
             */
            inline TVertexType & Type ()
            { 
                return type_; 
            }

            /**
             * @brief      Getter and setter for the type of the vertex.
             *
             * @return     The type of the vertex.
             */
            inline TVertexType const & Type () const 
            { 
                return type_; 
            }
        ///@}
        
        /**@name Real power */
        ///@{
#pragma mark REAL_POWER_LOAD

            /**
             * @brief      Getter for the real power demand
             *     @f$\realpowerdemand@f$ set point in per unit (p.u.) nominal
             *     power (MW).
             *
             * @return     The real power demand @f$\realpowerdemand@f$ set
             *     point in per unit (p.u.) nominal power (MW).
             */
            inline Types::real RealPowerLoad () const 
            { 
                return realPowerLoad_; 
            }

            /**
             * @brief      Getter and setter for the real power demand
             *     @f$\realpowerdemand@f$ set point in per unit (p.u.) nominal
             *     power (MW).
             *
             * @return     The real power demand @f$\realpowerdemand@f$ set
             *     point in per unit (p.u.) nominal power (MW).
             */
            inline Types::real & RealPowerLoad ()
            { 
                return realPowerLoad_; 
            }

            /**
             * @brief      Getter for the real power demand bound
             *     @f$[\realpowerdemandmin, \realpowerdemandmax]@f$ in per
             *     unit (p.u.) nominal power (MW).
             *
             * @return     The real power demand bound
             *     @f$[\realpowerdemandmin, \realpowerdemandmax]@f$ in per
             *     unit (p.u.) nominal power (MW).
             */
            inline TBound RealPowerLoadBound () const 
            { 
                return realPowerLoadBound_; 
            }

            /**
             * @brief      Getter and setter for the real power demand bound
             *     @f$[\realpowerdemandmin, \realpowerdemandmax]@f$ in per
             *     unit (p.u.) nominal power (MW).
             *
             * @return     The real power demand bound
             *     @f$[\realpowerdemandmin, \realpowerdemandmax]@f$ in per
             *     unit (p.u.) nominal power (MW).
             */
            inline TBound & RealPowerLoadBound ()
            { 
                return realPowerLoadBound_; 
            }
        ///@}

        /**@name Reactive Power Demand */
        ///@{
#pragma mark REACTIVE_POWER_LOAD

            /**
             * @brief      Getter for the reactive power demand
             *     @f$\reactivepowerdemand@f$ in per unit (p.u.) nominal power
             *     (MVAr).
             *
             * @return     The reactive power demand
             *     @f$\reactivepowerdemand@f$ in per unit (p.u.) nominal power
             *     (MVAr).
             */
            inline Types::real ReactivePowerLoad () const 
            { 
                return reactivePowerLoad_; 
            }

            /**
             * @brief      Getter for the reactive power demand
             *     @f$\reactivepowerdemand@f$ in per unit (p.u.) nominal power
             *     (MVAr).
             *
             * @return     The reactive power demand
             *     @f$\reactivepowerdemand@f$ in per unit (p.u.) nominal power
             *     (MVAr).
             */
            inline Types::real & ReactivePowerLoad ()
            { 
                return reactivePowerLoad_; 
            }

            /**
             * @brief      Getter for the reactive power demand bound
             *     @f$[\reactivepowerdemandmin, \reactivepowerdemandmax]@f$ in
             *     per unit (p.u.) nominal power (MVAr).
             *
             * @return     The reactive power demand bound
             *     @f$[\reactivepowerdemandmin, \reactivepowerdemandmax]@f$ in
             *     per unit (p.u.) nominal power (MVAr).
             */
            inline TBound ReactivePowerLoadBound () const 
            { 
                return reactivePowerLoadBound_; 
            }

            /**
             * @brief      Getter and setter for the reactive power demand
             *     bound @f$[\reactivepowerdemandmin,
             *     \reactivepowerdemandmax]@f$ in per unit (p.u.) nominal
             *     power (MVAr).
             *
             * @return     The reactive power demand demand bound
             *     @f$[\reactivepowerdemandmin, \reactivepowerdemandmax]@f$ in
             *     per unit (p.u.) nominal power (MVAr).
             */
            inline TBound & ReactivePowerLoadBound ()
            { 
                return reactivePowerLoadBound_; 
            }
        ///@}

        ///@name Comparators
        ///@{
#pragma mark COMPARATORS
            
            /**
             * @brief      Inequality comparator.
             *
             * @param      rhs   The right hand side LoadProperties.
             *
             * @return     @p true if both vertices are @p not equal, @p false
             *     otherwise.
             */
            inline bool operator!= ( LoadProperties const & rhs ) const 
            { 
                return !( this == rhs ); 
            }

            /**
             * @brief      Equality comparator.
             *
             * @param      rhs   The right hand side LoadProperties.
             *
             * @return     @p true if both vertices are equal, @p false
             *     otherwise.
             */
            inline bool operator== ( LoadProperties const & rhs ) const 
            {
                if ( Name() != rhs.Name() ) return false;
                if ( Type() != rhs.Type() ) return false;
                
                if ( RealPowerLoad()                != rhs.RealPowerLoad()                ) return false;
                if ( RealPowerLoadBound().Minimum() != rhs.RealPowerLoadBound().Minimum() ) return false;
                if ( RealPowerLoadBound().Maximum() != rhs.RealPowerLoadBound().Maximum() ) return false;

                if ( ReactivePowerLoad()                != rhs.ReactivePowerLoad()                ) return false;
                if ( ReactivePowerLoadBound().Minimum() != rhs.ReactivePowerLoadBound().Minimum() ) return false;
                if ( ReactivePowerLoadBound().Maximum() != rhs.ReactivePowerLoadBound().Maximum() ) return false;
                
                return true;
            }
        ///@}

    private:
#pragma mark MEMBER
        ///@name General Information Members
        ///@{
            Types::name name_;                      /**< The name of the vertex. */
            TVertexType type_;                      /**< The type of the vertex. */
        ///@}

        ///@name Real Power Members
        ///@{
            Types::real realPowerLoad_;             /**< The real power demand @f$\realpowerdemand@f$. */
            TBound      realPowerLoadBound_;        /**< The real power demand bound 
                                                     *      @f$[\realpowerdemandmin, \realpowerdemandmax]@f$. 
                                                     */
        ///@}

        ///@name Reactive Power Members
        ///@{
            Types::real reactivePowerLoad_;         /**< The reactive power demand 
                                                     *      @f$\reactivepowerdemand@f$. 
                                                     */
            TBound      reactivePowerLoadBound_;    /**< The real power demand bound 
                                                     *      @f$[\reactivepowerdemandmin, \reactivepowerdemandmax]@f$. 
                                                     */
        ///@}
};

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__GRAPHS__VERTICES__LOAD_PROPERTIES_HPP

/*
 * GeneratorProperties.hpp
 *
 *  Created on: Sep 07, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__VERTICES__GENERATOR_PROPERTIES_HPP
#define EGOA__DATA_STRUCTURES__VERTICES__GENERATOR_PROPERTIES_HPP

#include <iostream>
#include <iomanip>

#include "Type.hpp"
#include "Auxiliary/Auxiliary.hpp"
#include "Auxiliary/Constants.hpp"
#include "DataStructures/Bound.hpp"

namespace egoa::Vertices {

/**
 * @brief      Class having all generator properties.
 *
 * @tparam     VertexType  The vertex type is used to categorize the vertex,
 *     e.g., as slack bus.
 */
template<class VertexType = Vertices::IeeeBusType>
class GeneratorProperties {
    public:
        ///@name Bound Specific Types
        ///@{
            using TBound         = Bound<Types::real>;
        ///@}
        
        ///@name Type Specific Types
        ///@{
            using TVertexType    = VertexType;
            using TControlType   = Vertices::ControlType;
            using TGeneratorType = Vertices::GeneratorType;
            using TBusStatus     = Vertices::BusStatus;
            using TPowerSign     = Vertices::PowerSign;
        ///@}

    public:
        /**@name Constructors and Destructor */
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS

            GeneratorProperties ()
            : name_("")
            , type_(TVertexType::generator)
            , xCoordinate_(0.0)
            , yCoordinate_(0.0)
            // voltage
            , voltageMagnitudeSnapshot_(1.0)
            // nominal power
            , nominalPower_(1.0)
            , pNomExtendable_(false)
            , nominalRealPowerBound_( TBound(0.0, Const::REAL_INFTY ) )
            , sign_(TPowerSign::positive)
            // real power
            , realPower_(0.0)
            , realPowerBound_( TBound(0.0, Const::REAL_INFTY) ) 
            , pc1_(0.0)
            , pc2_(0.0)
            // reactive power
            , reactivePower_(0.0)
            , reactivePowerBound_( TBound(0.0, Const::REAL_INFTY) ) 
            , qc1Bound_( TBound(0.0, 0.0) )
            , qc2Bound_( TBound(0.0, 0.0) )
            // status
            , status_(TBusStatus::active)
            , committable_(false)
            // types
            , control_( TControlType::PQ )
            , generatorType_(TGeneratorType::unknown)
            , efficiency_(1.0)
            // cost specific information
            , marginalCost_(0.0)
            , capitalCost_(0.0)
            , startUpCost_(0.0)
            , shutDownCost_(0.0)
            // ramp information
            , minUpTime_(0.0)
            , minDownTime_(0.0)
            , rampAgc_(0.0)
            , ramp10_(0.0)
            , ramp30_(0.0)
            , rampQ_(0.0)
            , apf_(0.0)
            , rampLimitUp_(Const::REAL_INFTY)
            , rampLimitDown_(Const::REAL_INFTY)
            , rampLimitStartUp_(1.0)
            , rampLimitShutDown_(1.0)
            {}

            /**
             * @brief      Reset to default values.
             */
            inline void Reset () 
            {
                // BasicVertex specifics
                Name ()           = "";
                Type ()           = TVertexType::unknown;
                X ()              = 0.0;
                Y ()              = 0.0;
                // voltage
                VoltageMagnitude()            = 1.0;
                // nominal power
                NominalPower()                = 1.0;
                IsExtendable()                = false;
                NominalRealPowerBound()       = TBound(0.0, Const::REAL_INFTY );
                PowerSign()                   = TPowerSign::positive;
                // real power
                RealPower()                   = 0.0;
                RealPowerBound()              = TBound(0.0, Const::REAL_INFTY); //1.o?
                Pc1()                         = 0.0;
                Pc2()                         = 0.0;
                // reactive power
                ReactivePower()               = 0.0;
                ReactivePowerBound()          = TBound(0.0, Const::REAL_INFTY);
                Qc1Bound()                    = TBound(0.0, 0.0);
                Qc2Bound()                    = TBound(0.0, 0.0);
                // status
                Status()                      = TBusStatus::active;
                Committable()                 = false;
                // types
                Control()                     = TControlType::PQ;
                GeneratorType()               = TGeneratorType::unknown;
                Efficiency()                  = 1.0;
                // cost specific information
                MarginalCost()                = 0.0;
                CapitalCost()                 = 0.0;
                StartUpCost()                 = 0.0;
                ShutDownCost()                = 0.0;
                // ramp information
                MinimumUpTime()               = 0.0;
                MinimumDownTime()             = 0.0;
                RampAgc()                     = 0.0;
                Ramp10()                      = 0.0;
                Ramp30()                      = 0.0;
                RampQ()                       = 0.0;
                Apf()                         = 0.0;
                RampLimitUp()                 = Const::REAL_INFTY;
                RampLimitDown()               = Const::REAL_INFTY;
                RampLimitStartUp()            = 1.0;
                RampLimitShutDown()           = 1.0;
            }
        ///@}

        ///@Name Comparators
        ///@{
#pragma mark COMPARATORS

            /**
             * @brief      Inequality comparator of two generator properties.
             *
             * @param      rhs   The right hand side generator properties.
             *
             * @return     @p true if both vertices are @p not equal, @p false
             *     otherwise.
             */
            inline bool operator!=( GeneratorProperties const & rhs ) const 
            { 
                return !(this == rhs); 
            }

            /**
             * @brief      Comparison of two generator properties.
             *
             * @param      rhs   The right hand side generator properties.
             *
             * @return     @p true if both vertices are equal, @p false
             *     otherwise.
             */
            inline bool operator==( GeneratorProperties const & rhs ) const 
            {
                // Basic Vertex
                if ( Name()   != rhs.Name()   ) return false;
                if ( X()      != rhs.X()      ) return false;
                if ( Y()      != rhs.Y()      ) return false;
                if ( Type()   != rhs.Type()   ) return false;
                
                // Voltage specific information
                if ( !Auxiliary::EQ ( VoltageMagnitude(), rhs.VoltageMagnitude()                ) ) return false;

                // Nominal power specific information
                if ( NominalPower()                      != rhs.NominalPower()                    ) return false;
                if ( IsExtendable()                      != rhs.IsExtendable()                    ) return false;
                if ( NominalRealPowerBound().Minimum()   != rhs.NominalRealPowerBound().Minimum() ) return false;
                if ( NominalRealPowerBound().Maximum()   != rhs.NominalRealPowerBound().Maximum() ) return false;
                if ( PowerSign()                         != rhs.PowerSign()                       ) return false;

                // Real power specific information
                if ( !Auxiliary::EQ ( RealPower(),                rhs.RealPower()               ) ) return false;
                if ( !Auxiliary::EQ ( RealPowerBound().Maximum(), rhs.RealPowerBound().Maximum()) ) return false;
                if ( !Auxiliary::EQ ( RealPowerBound().Minimum(), rhs.RealPowerBound().Minimum()) ) return false;
                if ( !Auxiliary::EQ ( Pc1(),                      rhs.Pc1()                     ) ) return false;
                if ( !Auxiliary::EQ ( Pc2(),                      rhs.Pc2()                     ) ) return false;

                // Reactive power specific information
                if ( !Auxiliary::EQ( ReactivePower(),               rhs.ReactivePower()         ) ) return false;
                if ( !Auxiliary::EQ( ReactivePowerBound().Minimum(),rhs.ReactivePowerBound().Minimum() ) ) return false;
                if ( !Auxiliary::EQ( ReactivePowerBound().Maximum(),rhs.ReactivePowerBound().Maximum() ) ) return false;
                if ( !Auxiliary::EQ( Qc1Bound().Minimum(),          rhs.Qc1Bound().Minimum()    ) ) return false;
                if ( !Auxiliary::EQ( Qc1Bound().Maximum(),          rhs.Qc1Bound().Maximum()    ) ) return false;
                if ( !Auxiliary::EQ( Qc2Bound().Minimum(),          rhs.Qc2Bound().Minimum()    ) ) return false;
                if ( !Auxiliary::EQ( Qc2Bound().Maximum(),          rhs.Qc2Bound().Maximum()    ) ) return false;

                // Status specific information
                if ( Status()                            != rhs.Status()                          ) return false;
                if ( Committable()                       != rhs.Committable()                     ) return false;

                // Type specific information
                if ( Control()                           != rhs.Control()                         ) return false;
                if ( GeneratorType()                     != rhs.GeneratorType()                   ) return false;
                if ( !Auxiliary::EQ ( Efficiency(),               rhs.Efficiency()              ) ) return false;

                // Cost specific information
                if ( !Auxiliary::EQ( MarginalCost(),              rhs.MarginalCost()            ) ) return false;
                if ( !Auxiliary::EQ( CapitalCost(),               rhs.CapitalCost()             ) ) return false;
                if ( !Auxiliary::EQ( StartUpCost(),               rhs.StartUpCost()             ) ) return false;
                if ( !Auxiliary::EQ( ShutDownCost(),              rhs.ShutDownCost()            ) ) return false;

                // Ramp specific information
                if ( !Auxiliary::EQ( MinimumUpTime(),             rhs.MinimumUpTime()           ) ) return false;
                if ( !Auxiliary::EQ( MinimumDownTime(),           rhs.MinimumDownTime()         ) ) return false;
                if ( !Auxiliary::EQ( RampAgc(),                   rhs.RampAgc()                 ) ) return false;
                if ( !Auxiliary::EQ( Ramp10(),                    rhs.Ramp10()                  ) ) return false;
                if ( !Auxiliary::EQ( Ramp30(),                    rhs.Ramp30()                  ) ) return false;
                if ( !Auxiliary::EQ( RampQ(),                     rhs.RampQ()                   ) ) return false;
                if ( !Auxiliary::EQ( Apf(),                       rhs.Apf()                     ) ) return false;
                if ( !Auxiliary::EQ( RampLimitUp(),               rhs.RampLimitUp()             ) ) return false;
                if ( !Auxiliary::EQ( RampLimitDown(),             rhs.RampLimitDown()           ) ) return false;
                if ( !Auxiliary::EQ( RampLimitStartUp(),          rhs.RampLimitStartUp()        ) ) return false;
                if ( !Auxiliary::EQ( RampLimitShutDown(),         rhs.RampLimitShutDown()       ) ) return false;

                return true;
            }
        ///@}

        /**
         * @brief      Swapping the members of two generator properties.
         *
         * @param      lhs   The left hand side generator property.
         * @param      rhs   The right hand side generator property.
         */
        friend void swap ( GeneratorProperties & lhs
                         , GeneratorProperties & rhs ) 
        { // Necessary for the copy and swap idiom
            using std::swap; // enable ADL
            // Basic vertex
            swap( lhs.name_,                    rhs.name_       );
            swap( lhs.type_,                    rhs.type_       );
            swap( lhs.xCoordinate_,             rhs.xCoordinate_);
            swap( lhs.yCoordinate_,             rhs.yCoordinate_);

            // Voltage specific information
            swap( lhs.voltageMagnitudeSnapshot_,rhs.voltageMagnitudeSnapshot_);

            // Nominal power specific information
            swap( lhs.nominalPower_,            rhs.nominalPower_);
            swap( lhs.pNomExtendable_,          rhs.pNomExtendable_);
            swap( lhs.nominalRealPowerBound_,   rhs.nominalRealPowerBound_);
            swap( lhs.sign_,                    rhs.sign_);

            // Real power specific information
            swap( lhs.realPower_,               rhs.realPower_);
            swap( lhs.realPowerBound_,          rhs.realPowerBound_);
            swap( lhs.pc1_,                     rhs.pc1_);
            swap( lhs.pc2_,                     rhs.pc2_);

            // Reactive power specific information
            swap( lhs.reactivePower_,           rhs.reactivePower_);
            swap( lhs.reactivePowerBound_,      rhs.reactivePowerBound_);
            swap( lhs.qc1Bound_,                rhs.qc1Bound_);
            swap( lhs.qc2Bound_,                rhs.qc2Bound_);

            // Status specific information
            swap( lhs.status_,                  rhs.status_);
            swap( lhs.committable_,             rhs.committable_);
            
            // Type specific information
            swap( lhs.control_,                 rhs.control_);
            swap( lhs.type_,                    rhs.type_);
            swap( lhs.efficiency_,              rhs.efficiency_);

            // Cost specific information
            swap( lhs.marginalCost_,            rhs.marginalCost_);
            swap( lhs.capitalCost_,             rhs.capitalCost_);
            swap( lhs.startUpCost_,             rhs.startUpCost_);
            swap( lhs.shutDownCost_,            rhs.shutDownCost_);

            // Ramp specific information
            swap( lhs.minUpTime_,               rhs.minUpTime_);
            swap( lhs.minDownTime_,             rhs.minDownTime_);
            swap( lhs.rampAgc_,                 rhs.rampAgc_);
            swap( lhs.ramp10_,                  rhs.ramp10_);
            swap( lhs.ramp30_,                  rhs.ramp30_);
            swap( lhs.rampQ_,                   rhs.rampQ_);
            swap( lhs.apf_,                     rhs.apf_);
            swap( lhs.rampLimitUp_,             rhs.rampLimitUp_);
            swap( lhs.rampLimitDown_,           rhs.rampLimitDown_);
            swap( lhs.rampLimitStartUp_,        rhs.rampLimitStartUp_);
            swap( lhs.rampLimitShutDown_,       rhs.rampLimitShutDown_);
        }

        ///@name Basic Properties
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

        /**@name Voltage */
        ///@{
#pragma mark VOLTAGE

            /**
             * @brief      Getter for the voltage magnitude setpoint
             *     @f$\vmagnitude@f$ in per unit (p.u.) of the nominal
             *     voltage.
             *
             * @return     The voltage magnitude @f$\vmagnitude@f$.
             */
            inline Types::real VoltageMagnitude () const 
            { 
                return voltageMagnitudeSnapshot_; 
            }

            /**
             * @brief      Getter and setter for the voltage magnitude
             *     setpoint @f$\vmagnitude@f$ in per unit (p.u.) of the
             *     nominal voltage.
             *
             * @return     The voltage magnitude @f$\vmagnitude@f$.
             */
            inline Types::real & VoltageMagnitude ()
            { 
                return voltageMagnitudeSnapshot_; 
            }
        ///@}

        /**@name Nominal Power Information */ 
        ///@{
#pragma mark NOMINAL_POWER

            /**
             * @brief      Determines if the generator is extendable (used for
             *     production expansion).
             * @details    This is mainly used for renewable energy sources to
             *     determine how much the new energy source is expanded. For
             *     already existing energy sources this is usually set to @p
             *     False. However, in some cases it makes sense to extend
             *     already existing energy sources, too, and the flag might be
             *     @p True, too.
             * 
             * @pre        Default is @p false.
             * 
             * @note       If it is true the extendable generator then the
             *     generator's nominal real power @f$\realpowernominal@f$ lies
             *     between @f$\realpowernominalmin@f$ and
             *     @f$\realpowernominalmax@f$ meaning
             *     @f[
             *     \realpowernominal := [\realpowernominalmin,\realpowernominalmax].
             *     @f] 
             *     Otherwise, the generator's nominal real power
             *     @f$\realpowernominal@f$ is defined by a fixed value. Thus, use
             *     @f$\realpowernominal@f$ by using @p Mbase when @p
             *     IsExtendable is @p false, and @f$\realpowernominalmin@f$ and
             *     @f$\realpowernominalmax@f$ by using @p NominalRealPower if
             *     @p IsExtendable is @p true.
             *     
             * @see NominalPower
             * @see NominalRealPowerBound
             *
             * @return     @p True if the generator
             *     @f$\vertex\in\generators@f$ is extendable, @p false
             *     otherwise.
             */
            inline bool IsExtendable() const 
            { 
                return pNomExtendable_; 
            }

            /**
             * @brief      Setter and determines if the generator is
             *     extendable (used for production expansion).
             * @details    This is mainly used for renewable energy sources to
             *     determine how much the new energy source is expanded. For
             *     already existing energy sources this is usually set to @p
             *     False. However, in some cases it makes sense to extend
             *     already existing energy sources, too, and the flag might be
             *     @p True, too.
             *
             * @code{.cpp}
             *      generator.IsExtendable() = true;
             * @endcode
             * 
             * @pre        Default is @p false.
             * 
             * @note       If it is true the extendable generator then the
             *     generator's nominal real power @f$\realpowernominal@f$ lies between
             *     @f$\realpowernominalmin@f$ and @f$\realpowernominalmax@f$ meaning
             *     @f[
             *     \realpowernominal := [\realpowernominalmin,\realpowernominalmax].
             *     @f] 
             *     Otherwise, the generator's nominal real power
             *     @f$\realpowernominal@f$ is defined by a fixed value. Thus, use
             *     @f$\realpowernominal@f$ by using @p Mbase when @p
             *     IsExtendable is @p false, and @f$\realpowernominalmin@f$
             *     and @f$\realpowernominalmax@f$ by using @p NominalRealPower
             *     if @p IsExtendable is @p true.
             *
             * @see NominalPower
             * @see IsExtendable
             * @see NominalRealPowerBound
             *
             * @return     @p true if the generator
             *     @f$\vertex\in\generators@f$ is extendable, @p false
             *     otherwise.
             */
            inline bool & IsExtendable ()
            { 
                return pNomExtendable_; 
            }

            /**
             * @brief      Getter for the nominal power base. 
             * @details    If the generator @f$\vertex\in\generators@f$ is
             *     @p NOT extendable---meaning IsExtendable is @p false---and
             *         thus, fixed the nominal power is used to normalize or
             *         to denormalize into/from the p.u. units.
             *
             * @code{.cpp}
             *     GeneratorProperties const & generator;
             *     ...
             *     if ( !generator.IsExtendable() )  
             *     { // nominal real power is a value and thus, is fixed.
             *         std::cout << "p_nom = " << generator.Mbase() << std::endl;
             *     }
             * @endcode
             *
             * @see NominalPower
             * @see IsExtendable
             * @see NominalRealPowerBound
             *
             * @return     The nominal power base.
             */
            inline Types::real NominalPower () const 
            { 
                return nominalPower_;
            }

            /**
             * @brief      Getter and setter for the nominal power base. 
             * @details    If the generator @f$\vertex\in\generators@f$ is
             *     @p NOT extendable---meaning IsExtendable is @p False---and
             *         thus, fixed the nominal power is used to normalize or
             *         to denormalize into/from the p.u. units.
             *
             * @code{.cpp}
             *     if ( !generator.IsExtendable() )  
             *     { // nominal real power is a value and thus, is fixed.
             *         generator.Mbase() = 11.11;
             *     }
             * @endcode
             *
             * @see NominalPower
             * @see IsExtendable
             * @see NominalRealPowerBound
             *
             * @return     The nominal power base.
             */
            inline Types::real & NominalPower ()
            { 
                return nominalPower_; 
            }

            /**
             * @brief      Getter for the nominal real power bound with
             *     @f$\realpowernominal:=[\realpowernominalmin,\realpowernominalmax]@f$
             *     while the generator
             *     @f$\vertex\in\generators@f$ is extendable.
             *     
             * @pre        Check if the @f$\vertex\in\generators@f$ is
             *     extendable meaning IsExtendable is true.
             *     
             * @code{.cpp}
             *     if ( generator.IsExtendable() ) 
             *     { // nominal real power lies in between a bound and thus, is flexible.
             *         std::cout << "p_nom_min = " << generator.NominalRealPower().Minimum()
             *                   << "p_nom_max = " << generator.NominalRealPower().Maximum() << std::endl;
             *     } else 
             *     { // nominal real power is a value and thus, is fixed.
             *         std::cout << "p_nom = " << generator.Mbase() << std::endl;
             *     }
             * @endcode
             * 
             * @see NominalPower
             * @see IsExtendable
             * @see NominalRealPowerBound
             * 
             * @return     The nominal real power bound
             *     @f$\realpowernominal:=[\realpowernominalmin,\realpowernominalmax]@f$.
             */
            inline TBound NominalRealPowerBound () const 
            { 
                return nominalRealPowerBound_; 
            }

            /**
             * @brief      Getter and setter for the nominal real power bound
             *     with
             *     @f$\realpowernominal:=[\realpowernominalmin,\realpowernominalmax]@f$
             *     while the generator
             *     @f$\vertex\in\generators@f$ is extendable.
             *     
             * @pre        Check if the @f$\vertex\in\generators@f$ is
             *     extendable meaning IsExtendable is true.
             *     
             * @code{.cpp}
             *     if ( generator.IsExtendable() ) 
             *     { // nominal real power lies in between a bound and thus, is flexible.
             *         generator.NominalRealPower().Minimum() = 0.0;
             *         generator.NominalRealPower().Maximum() = 11.11;
             *     }
             * @endcode
             * 
             * @see NominalPower
             * @see IsExtendable
             * @see NominalRealPowerBound
             * 
             * @return     The nominal real power bound
             *     @f$\realpowernominal:=[\realpowernominalmin,\realpowernominalmax]@f$.
             */
            inline TBound & NominalRealPowerBound ()
            { 
                return nominalRealPowerBound_; 
            }

            /**
             * @brief      Getter for the power sign.
             *
             * @return     The power sign, if 1 the generator produces energy,
             *     otherwise if -1 it consumes energy.
             *     
             * @todo make enum
             */
            inline TPowerSign PowerSign () const 
            { 
                return sign_;
            }

            /**
             * @brief      Getter for the power sign.
             *
             * @return     The power sign, if 1 the generator produces energy,
             *     otherwise if -1 it consumes energy.
             *     
             * @todo make enum
             */
            inline TPowerSign & PowerSign () 
            { 
                return sign_; 
            }
        ///@}

        /**@name Real Power Information */ 
        ///@{
#pragma mark REAL_POWER_INFORMATION

            /**
             * @brief      Getter for the real power @f$\realpowergeneration@f$.
             *
             * @return     The real power @f$\realpowergeneration@f$.
             */
            inline Types::real RealPower () const 
            { 
                return realPower_; 
            }

            /**
             * @brief      Getter and setter for the real power set point
             *     @f$\realpowergeneration@f$.
             *
             * @return     The real power set point @f$\realpowergeneration@f$.
             */
            inline Types::real & RealPower ()
            { 
                return realPower_; 
            }

            /**
             * @brief      Getter for the real power bound
             *     @f$[\realpowergenerationmin, \realpowergenerationmax]@f$.
             *
             * @return     The real power bound @f$[\realpowergenerationmin,
             *     \realpowergenerationmax]@f$.
             */
            inline TBound RealPowerBound () const
            { 
                return realPowerBound_; 
            }

            /**
             * @brief      Getter and setter for the real power bound
             *     @f$[\realpowergenerationmin, \realpowergenerationmax]@f$.
             *
             * @return     The real power bound @f$[\realpowergenerationmin,
             *     \realpowergenerationmax]@f$.
             */
            inline TBound & RealPowerBound ()
            { 
                return realPowerBound_; 
            }

            /**
             * @brief      Getter for the lower real power output of @p PQ
             *     capability curve (MW) at @p PC1.
             *
             * @return     The lower real power output of @p PQ capability
             *     curve (MW).
             */
            inline Types::real Pc1 () const 
            { 
                return pc1_; 
            }

            /**
             * @brief      Getter and setter for the lower real power output
             *     of @p PQ capability curve (MW) at @p PC1.
             *
             * @return     The lower real power output of @p PQ capability
             *     curve (MW).
             */
            inline Types::real & Pc1 ()
            { 
                return pc1_; 
            }

            /**
             * @brief      Getter for the upper real power output of @p PQ
             *     capability curve (MW) at @p PC2.
             *
             * @return     The upper real power output of @p PQ capability
             *     curve (MW).
             */
            inline Types::real Pc2 () const 
            { 
                return pc2_; 
            }

            /**
             * @brief      Getter and setter for the upper real power output
             *     of @p PQ capability curve (MW) at @p PC2.
             *
             * @return     The upper real power output of @p PQ capability
             *     curve (MW).
             */
            inline Types::real & Pc2 ()
            { 
                return pc2_; 
            }
        ///@}

        /**@name Reactive Power Information */ 
        ///@{
#pragma mark REACTIVE_POWER_INFORMATION

            /**
             * @brief      Getter for the reactive power
             *     @f$\reactivepowergeneration@f$.
             *
             * @return     The real power @f$\reactivepowergeneration@f$.
             */
            inline Types::real ReactivePower () const
            { 
                return reactivePower_; 
            }

            /**
             * @brief      Getter and setter for the reactive power
             *     @f$\reactivepowergeneration@f$.
             *
             * @return     The real power @f$\reactivepowergeneration@f$.
             */
            inline Types::real & ReactivePower ()
            { 
                return reactivePower_; 
            }

            /**
             * @brief      Getter for the reactive power bound
             *     @f$[\reactivepowergenerationmin, \reactivepowergenerationmax]@f$.
             *
             * @return     The reactive power bound
             *     @f$[\reactivepowergenerationmin,\reactivepowergenerationmax]@f$.
             */
            inline TBound ReactivePowerBound () const
            { 
                return reactivePowerBound_; 
            }
            
            /**
             * @brief      Getter and setter for the reactive power bound
             *     @f$[\reactivepowergenerationmin, \reactivepowergenerationmax]@f$.
             *
             * @return     The reactive power bound
             *     @f$[\reactivepowergenerationmin,\reactivepowergenerationmax]@f$.
             */
            inline TBound & ReactivePowerBound ()
            { 
                return reactivePowerBound_; 
            }

            /**
             * @brief      Getter for the reactive power output bound at @p
             *     PC1.
             * @details    This is measured in MVAr.
             *
             * @return     The reactive power output bound at @p PC1.
             */
            inline TBound Qc1Bound () const 
            { 
                return qc1Bound_; 
            }

            /**
             * @brief      Getter and setter for the reactive power output
             *     bound at @p PC1.
             * @details    This is measured in MVAr.
             *
             * @return     The reactive power output bound at @p PC1.
             */
            inline TBound & Qc1Bound ()
            { 
                return qc1Bound_; 
            }

            /**
             * @brief      Getter for the reactive power output bound at @p
             *     PC2.
             * @details    This is measured in MVAr.
             *
             * @return     The reactive power output bound at @p PC2.
             */
            inline TBound Qc2Bound () const 
            { 
                return qc2Bound_; 
            }

            /**
             * @brief      Getter and setter for the reactive power output
             *     bound at @p PC2.
             * @details    This is measured in MVAr.
             *
             * @return     The reactive power output bound at @p PC2.
             */
            inline TBound & Qc2Bound ()
            { 
                return qc2Bound_; 
            }
        ///@}

        /**@name Status Specific Information */
        ///@{
#pragma mark STATUS_INFORMATION

            /**
             * @brief      Determines if the electrical vertex is active.
             *
             * @see Status
             *
             * @return     @p true if active (on), @p false otherwise (unknown).
             */
            inline bool IsActive () const  
            { 
                if ( TBusStatus::active == Status() )
                    return true;
                else 
                    return false; 
            }
            
            /**
             * @brief      Status of the electrical vertex.
             * @details    The status of the generator/machine is described by
             *     @p active (in-service) or @p inactive (out-of-service).
             *
             * @see Type#Vertex#BusStatus
             *
             * @return     The status can have a different status.
             */
            ///@todo USE DIFFERENT TYPE see bus
            inline TBusStatus Status () const 
            { 
                return status_; 
            }

            /**
             * @brief      Status of the electrical vertex.
             * @details    The status of the generator/machine is described by
             *     @p active (in-service) or @p inactive (out-of-service).
             *
             * @see Type#Vertex#BusStatus
             *
             * @return     The status can have a different status.
             */
            ///@todo USE DIFFERENT TYPE see bus
            inline TBusStatus & Status ()
            { 
                return status_; 
            }

            /**
             * @brief      Getter for the unit commitment.
             * 
             * @pre        This can only be @p true if the generator is not
             *     extendable.
             *
             * @return     @p true if unit commitment, @p false otherwise.
             */
            inline bool Committable () const 
            { 
                return committable_; 
            }

            /**
             * @brief      Getter and setter for the unit commitment.
             * 
             * @pre        This can only be @p true if the generator is not
             *     extendable.
             *
             * @return     @p true if unit commitment, @p false otherwise.
             */
            inline bool & Committable () 
            { 
                return committable_; 
            }
        ///@}

        /**@name Type Specific Information*/ 
        ///@{
#pragma mark TYPE_INFORMATION

            /**
             * @brief      Getter for the control strategy.
             * @details    The control strategy must be either PQ, PV, or
             *     Slack. The slack vertex represents a reference vertex used
             *     to set a voltage angle for example to 0 and thus, determine
             *     the other voltage angle.
             *
             * @see Vertices#ControlType
             *
             * @return     The control strategy.
             */
            inline Vertices::ControlType Control () const
            { 
                return control_; 
            }

            /**
             * @brief      Getter and setter for the control strategy.
             * @details    The control strategy must be either PQ, PV, or
             *     Slack. The slack vertex represents a reference vertex used
             *     to set a voltage angle for example to 0 and thus, determine
             *     the other voltage angle.
             *     
             * @see Vertices#ControlType
             *
             * @return     The control strategy.
             */
            inline Vertices::ControlType & Control ()
            { 
                return control_; 
            }
            
            /**
             * @brief      Getter for the generator type.
             * @details    The generator type determines if it is a
             *     conventional or renewable generator.
             *
             * @see Vertices#GeneratorType
             *
             * @return     The generator type.
             */
            inline Vertices::GeneratorType GeneratorType () const
            { 
                return generatorType_; 
            }

            /**
             * @brief      Getter and setter for the generator type.
             * @details    The generator type determines if it is a
             *     conventional or renewable generator.
             *
             * @see Vertices#GeneratorType
             *
             * @return     The generator type.
             */
            inline Vertices::GeneratorType & GeneratorType ()
            { 
                return generatorType_; 
            }
            
            /**
             * @brief      Getter for the efficiency of the generator.
             * @details    The efficiency of a generator is calculated by the
             *     ratio between primary and electrical energy.
             *
             * @return     The efficiency of the generator.
             */
            inline Types::real Efficiency () const 
            { 
                return efficiency_; 
            }

            /**
             * @brief      Getter and setter for the efficiency of the
             *     generator.
             * @details    The efficiency of a generator is calculated by the
             *     ratio between primary and electrical energy.
             *
             * @return     The efficiency of the generator.
             */
            inline Types::real & Efficiency ()
            { 
                return efficiency_; 
            }
        ///@}

        /**@name Cost Specific Information */ 
        ///@{
#pragma mark COST_SPECIFIC_INFOMRATION

            /**
             * @brief      Getter for the marginal cost.
             * @details    The marginal cost for the production of 1 MW.
             *
             * @return     The marginal cost.
             */
            inline Types::real MarginalCost () const 
            { 
                return marginalCost_; 
            }

            /**
             * @brief      Getter and setter for the marginal cost.
             * @details    The marginal cost for the production of 1 MW.
             *
             * @return     The marginal cost.
             */
            inline Types::real & MarginalCost ()
            { 
                return marginalCost_; 
            }

            /**
             * @brief      Getter for the capital cost.
             * @details    The capital cost by extending the generator's
             *     nominal power @f$\realpowernominal@f$ by 1 MW.
             *
             * @return     The capital cost.
             */
            inline Types::real CapitalCost () const
            { 
                return capitalCost_; 
            }

            /**
             * @brief      Getter and setter for the capital cost.
             * @details    The capital cost by extending the generator's
             *     nominal power @f$\realpowernominal@f$ by 1 MW.
             *
             * @return     The capital cost.
             */
            inline Types::real & CapitalCost ()
            { 
                return capitalCost_; 
            }

            /**
             * @brief      Getter for the startup costs for the generator.
             *
             * @pre        Only if Committable() is @p true.
             *
             * @return     The startup cost for the generator.
             */
            inline Types::real StartUpCost () const 
            { 
                return startUpCost_; 
            }

            /**
             * @brief      Getter and setter for the startup costs for the
             *     generator.
             *
             * @pre        Only if Committable() is @p true.
             *
             * @return     The startup cost for the generator.
             */
            inline Types::real & StartUpCost ()
            { 
                return startUpCost_; 
            }

            /**
             * @brief      Getter for the shutdown costs for the generator.
             *
             * @pre        Only if Committable() is @p true.
             *
             * @return     The shut-down cost for the generator.
             */
            inline Types::real ShutDownCost () const
            { 
                return shutDownCost_; 
            }

            /**
             * @brief      Getter and setter for the shutdown costs for the
             *     generator.
             *
             * @pre        Only if Committable() is @p true.
             *
             * @return     The shut-down cost for the generator.
             */
            inline Types::real & ShutDownCost ()
            { 
                return shutDownCost_; 
            }
        ///@}

        /**
         * @name    Ramp Specific Information
         * 
         * @brief   Ramp Limits: The inner dynamic of generators does not
         *     always allow to change the production level, i.e., a maximum
         *     possible change is set by ramp limits.
         * 
         *     Ramp rate: Describes how fast generator outputs can be changed.
         *     There are usually ramping up (increasing) and down
         *     (decreasing), i.e., the unit is in units of power over time
         *     (here MW/min).
         */
        ///@{
#pragma mark RAMP_SPECIFIC_INFORMATION

            /**
             * @brief      Getter for the minimum availability (active) time. 
             * @details    This is measured in number of snapshots. This
             *     represents the minimum number of snapshots to be in @p
             *     active status until a shutdown is possible, i.e., being in
             *     @p inactive status.
             *     
             * @pre        Only if Committable() is @p true.
             *
             * @return     The minimum @p active time of the generator.
             */
            inline Types::real MinimumUpTime () const
            { 
                return minUpTime_; 
            }

            /**
             * @brief      Getter and setter for the minimum availability
             *     (active) time.
             * @details    This is measured in number of snapshots. This
             *     represents the minimum number of snapshots to be in @p
             *     active status until a shutdown is possible, i.e., being in
             *     @p inactive status.
             *     
             * @pre        Only if Committable() is @p true.
             *
             * @return     The minimum @p active time of the generator.
             */
            inline Types::real & MinimumUpTime ()
            { 
                return minUpTime_; 
            }

            /**
             * @brief      Getter for the minimum time to be @p inactive. 
             * @details    This is measured in number of snapshots. This
             *     represents the minimum number of snapshots to be in @p
             *     inactive status until a startup is possible again, i.e.,
             *     being in @p active status.
             *     
             * @pre        Only if Committable() is @p true.
             *
             * @return     The minimum time to be @p inactive of the generator.
             */
            inline Types::real MinimumDownTime () const
            { 
                return minDownTime_; 
            }

            /**
             * @brief      Getter and setter for the minimum time to be @p
             *     inactive.
             * @details    This is measured in number of snapshots. This
             *     represents the minimum number of snapshots to be in @p
             *     inactive status until a startup is possible again, i.e.,
             *     being in @p active status.
             *
             * @pre        Only if Committable() is @p true.
             *
             * @return     The minimum time to be @p inactive of the generator.
             */
            inline Types::real & MinimumDownTime ()
            { 
                return minDownTime_; 
            }

            /**
             * @brief      Getter for the ramp rate for load following AGC.
             * @details    The ramp rate is measured in MW/min and is part of
             *     the IEEE data.
             * 
             * @note       AGC stands for Automatic Generation Control.
             *
             * @return     The ramp rate for load following AGC.
             */
            inline Types::real RampAgc () const 
            { 
                return rampAgc_; 
            }

            /**
             * @brief      Getter and setter for the ramp rate for load
             *     following AGC.
             * @details    The ramp rate is measured in MW/min and is part of
             *     the IEEE data.
             * 
             * @note       AGC stands for Automatic Generation Control.
             *
             * @return     The ramp rate for load following AGC.
             */
            inline Types::real & RampAgc ()
            { 
                return rampAgc_; 
            }

            /**
             * @brief      Getter for the ramp rate for a 10 minute reserve.
             * @details    The ramp rate is measured in MW and is part of the
             *     IEEE data.
             *
             * @return     The ramp rate for a 10 minute reserve.
             */
            inline Types::real Ramp10 () const 
            { 
                return ramp10_; 
            }

            /**
             * @brief      Getter and setter for the ramp rate for a 10 minute
             *     reserve.
             * @details    The ramp rate is measured in MW and is part of the
             *     IEEE data.
             *
             * @return     The ramp rate for a 10 minute reserve.
             */
            inline Types::real & Ramp10 ()
            { 
                return ramp10_; 
            }

            /**
             * @brief      Getter for the ramp rate for a 30 minute reserve.
             * @details    The ramp rate is measured in MW and is part of the
             *     IEEE data.
             *
             * @return     The ramp rate for a 30 minute reserve.
             */
            inline Types::real Ramp30 () const 
            { 
                return ramp30_; 
            }

            /**
             * @brief      Getter and setter for the ramp rate for a 30 minute
             *     reserve.
             * @details    The ramp rate is measured in MW and is part of the
             *     IEEE data.
             *
             * @return     The ramp rate for a 30 minute reserve.
             */
            inline Types::real & Ramp30 ()
            { 
                return ramp30_; 
            }

            /**
             * @brief      Getter for the ramp rate for the reactive power (2
             *     sec timescale).
             * @details    The ramp rate is measured in MVAr/min and is part of the
             *     IEEE data.
             *
             * @return     The ramp rate for the reactive power.
             */
            inline Types::real RampQ () const 
            { 
                return rampQ_; 
            }

            /**
             * @brief      Getter and setter for the ramp rate for the
             *     reactive power (2 sec timescale).
             * @details    The ramp rate is measured in MVAr/min and is part
             *     of the IEEE data.
             *
             * @return     The ramp rate for the reactive power.
             */
            inline Types::real & RampQ ()
            { 
                return rampQ_; 
            }

            /**
             * @brief      Getter for the area participation factor (APF).
             *
             * @return     The area participation factor (APF).
             */
            inline Types::real Apf () const 
            { 
                return apf_; 
            }

            /**
             * @brief      Getter and setter for the area participation factor
             *     (APF).
             *
             * @return     The area participation factor (APF).
             */
            inline Types::real & Apf ()
            { 
                return apf_; 
            }

            /**
             * @brief      Getter for the maximum increase in power.
             * @details    The maximum increase in power is measured in per
             *     snapshot.
             *
             * @note       Ignore if infinity.
             *
             * @return     The maximum increase in power.
             */
            inline Types::real RampLimitUp () const
            { 
                return rampLimitUp_; 
            }
            
            /**
             * @brief      Getter and setter for the maximum increase in power.
             * @details    The maximum increase in power is measured in per
             *     snapshot.
             *
             * @note       Ignore if infinity.
             *
             * @return     The maximum increase in power.
             */
            inline Types::real & RampLimitUp ()
            { 
                return rampLimitUp_; 
            }

            /**
             * @brief      Getter for the maximum decrease in power.
             * @details    The maximum decrease in power is measured in per
             *     snapshot.
             *
             * @note       Ignore if infinity.
             *
             * @return     The maximum decrease in power.
             */
            inline Types::real RampLimitDown () const
            { 
                return rampLimitDown_; 
            }
            
            /**
             * @brief      Getter and setter for the maximum decrease in power.
             * @details    The maximum decrease in power is measured in per
             *     snapshot.
             *
             * @note       Ignore if infinity.
             *
             * @return     The maximum decrease in power.
             */
            inline Types::real & RampLimitDown ()
            { 
                return rampLimitDown_; 
            }

            /**
             * @brief      Getter for the maximum increase in power at startup.
             * @details    The maximum increase in power at startup is
             *     measured in per unit of nominal power @f$\realpowernominal@f$.
             *
             * @pre        Only if Committable() is @p true.
             *
             * @return     The maximum increase in power at startup.
             */
            inline Types::real RampLimitStartUp () const
            { 
                return rampLimitStartUp_; 
            }
            
            /**
             * @brief      Getter and setter for the maximum increase in power
             *     at start-up.
             * @details    The maximum increase in power at startup is
             *     measured in per unit of nominal power @f$\realpowernominal@f$.
             *
             * @pre        Only if Committable() is @p true.
             *
             * @return     The maximum increase in power at startup.
             */
            inline Types::real & RampLimitStartUp ()
            { 
                return rampLimitStartUp_; 
            }

            /**
             * @brief      Getter for the maximum decrease in power at shut-down.
             * @details    The maximum decrease in power at shutdown is
             *     measured in per unit of nominal power @f$\realpowernominal@f$.
             *
             * @pre        Only if Committable() is @p true.
             *
             * @return     The maximum decrease in power at shutdown.
             */
            inline Types::real RampLimitShutDown () const
            { 
                return rampLimitShutDown_; 
            }
            
            /**
             * @brief      Getter and setter for the maximum decrease in power
             *     at shut-down.
             * @details    The maximum decrease in power at shutdown is
             *     measured in per unit of nominal power @f$\realpowernominal@f$.
             *
             * @pre        Only if Committable() is @p true.
             *
             * @return     The maximum decrease in power at shutdown.
             */
            inline Types::real & RampLimitShutDown ()
            { 
                return rampLimitShutDown_; 
            }
        ///@}       

        /**@name Output */ 
        ///@{
#pragma mark OUTPUT_METHODS
            /**
             * @brief      Writes the generator property to an output stream.
             *
             * @param      outputStream  The stream to write data to, e.g., std::cout.
             * @param[in]  rhs           The right hand side of the generator property.
             *
             * @return     The output stream.
             */
            friend std::ostream & operator<< ( std::ostream              & outputStream
                                             , GeneratorProperties const & rhs ) 
            {
                outputStream  << std::setprecision(2)
                    << std::fixed
                    << std::endl
                    << "Generator at Bus "      << rhs.Name()   << std::endl
                    << "-------------------"    << std::endl
                    << std::setw(30) << "bus: "                 << std::setw(10) << rhs.Name() 
                    << std::setw(20) << "generation: "          << std::setw(10) << rhs.RealPower()                   << std::setw(25) << " p.u.       (real, MW), "
                                                                << std::setw(10) << rhs.ReactivePower()               << std::setw(25) << " p.u. (reactive, MVar), "  << std::endl
                    << std::setw(20) << "real power bound: "    << std::setw(10) << rhs.RealPowerBound().Minimum()    << std::setw(25) << " p.u.       (pmin, MW), "
                                                                << std::setw(10) << rhs.RealPowerBound().Maximum()    << std::setw(25) << " p.u.       (pmax, MW), "  << std::endl
                    << std::setw(20) << "reactive power bound: "<< std::setw(10) << rhs.ReactivePowerBound().Minimum()<< std::setw(25) << " p.u.     (qmin, MVar), "
                                                                << std::setw(10) << rhs.ReactivePowerBound().Maximum()<< std::setw(25) << " p.u.     (qmax, MVar), "  << std::endl
                    << std::setw(20) << "voltage magnitude: "   << std::setw(10) << rhs.VoltageMagnitude()            << std::setw(25) << "               (Vm, V), "  << std::endl
                    << std::setw(20) << "status: "              << std::setw(10) << rhs.IsActive()                      << std::setw(25) << ""                          << std::endl;
                return outputStream;
            }

            /**
             * @brief      Write the header to the output stream.
             * @details    List all IEEE standard input data.
             *
             * @param      outputStream  The stream to write data to, e.g., std::cout.
             */
            static inline void Header ( std::ostream & outputStream) 
            {
                outputStream  << std::setw(20)    << "bus"
                    << std::setw(10)    << "Pg"
                    << std::setw(10)    << "Qg"
                    << std::setw(10)    << "Qmax"
                    << std::setw(10)    << "Qmin" 
                    << std::setw(10)    << "Vg"
                    << std::setw(10)    << "mBase"
                    << std::setw(10)    << "status"
                    << std::setw(10)    << "Pmax"
                    << std::setw(10)    << "Pmin"
                    << std::setw(6)     << "Pc1"
                    << std::setw(6)     << "Pc2"
                    << std::setw(8)     << "Qc1min"
                    << std::setw(8)     << "Qc1max"
                    << std::setw(8)     << "Qc2min"
                    << std::setw(8)     << "Qc2max"
                    << std::setw(9)     << "ramp_agc"
                    << std::setw(8)     << "ramp_10"
                    << std::setw(8)     << "ramp_30"
                    << std::setw(8)     << "ramp_q"
                    << std::setw(6)     << "apf"
                    << std::endl;
            }

            static inline void HeaderBusGeneratorName ( std::ostream & outputStream) 
            {
                outputStream  << std::setw(20)    << "bus"
                    << std::setw(20)    << "name"
                    << std::setw(10)    << "Pg"
                    << std::setw(10)    << "Qg"
                    << std::setw(10)    << "Qmax"
                    << std::setw(10)    << "Qmin" 
                    << std::setw(10)    << "Vg"
                    << std::setw(10)    << "mBase"
                    << std::setw(10)    << "status"
                    << std::setw(10)    << "Pmax"
                    << std::setw(10)    << "Pmin"
                    << std::setw(6)     << "Pc1"
                    << std::setw(6)     << "Pc2"
                    << std::setw(8)     << "Qc1min"
                    << std::setw(8)     << "Qc1max"
                    << std::setw(8)     << "Qc2min"
                    << std::setw(8)     << "Qc2max"
                    << std::setw(9)     << "ramp_agc"
                    << std::setw(8)     << "ramp_10"
                    << std::setw(8)     << "ramp_30"
                    << std::setw(8)     << "ramp_q"
                    << std::setw(6)     << "apf"
                    << std::endl;
            }

            /**
             * @brief      Write the values of the generator property.
             * @details    List all IEEE standard input data.
             *
             * @param      outputStream  The stream to write data to, e.g., std::cout.
             * @param[in]  baseMva       The base MVA.
             */
            inline void Line ( std::ostream & outputStream
                             , Types::real    baseMva = 1 ) const
            {
                outputStream  << std::setprecision(2)
                    << std::fixed
                    << std::setw(20)    << Name()
                    << std::setw(10)    << RealPower()     * baseMva
                    << std::setw(10)    << ReactivePower() * baseMva
                    << std::setw(10)    << ReactivePowerBound().Maximum() * baseMva
                    << std::setw(10)    << ReactivePowerBound().Minimum() * baseMva
                    << std::setw(10)    << VoltageMagnitude()
                    << std::setw(10)    << NominalPower()
                    << std::setw(10)    << IsActive()
                    << std::setw(10)    << RealPowerBound().Maximum() * baseMva
                    << std::setw(10)    << RealPowerBound().Minimum() * baseMva
                    << std::setw(6)     << Pc1()
                    << std::setw(6)     << Pc2()
                    << std::setw(8)     << Qc1Bound().Minimum()
                    << std::setw(8)     << Qc1Bound().Maximum()
                    << std::setw(8)     << Qc2Bound().Minimum()
                    << std::setw(8)     << Qc2Bound().Maximum()
                    << std::setw(9)     << RampAgc()
                    << std::setw(8)     << Ramp10()
                    << std::setw(8)     << Ramp30()
                    << std::setw(8)     << RampQ()
                    << std::setw(6)     << Apf()
                    << std::endl;
            }

            /**
             * @brief      Writes the values including the identifier of the generator property.
             * @details    List all IEEE standard input data.
             *
             * @param      outputStream  The stream to write data to, e.g., std::cout.
             * @param[in]  identifier    The identifier.
             * @param[in]  baseMva       The base MVA.
             */
            inline void Line ( std::ostream &   outputStream
                             , Types::vertexId  identifier
                             , Types::real      baseMva = 1 ) const
            {
                outputStream  << std::setprecision(2)
                    << std::fixed
                    << std::setw(6)     << identifier
                    << std::setw(10)    << RealPower()     * baseMva
                    << std::setw(10)    << ReactivePower() * baseMva
                    << std::setw(10)    << ReactivePowerBound().Maximum() * baseMva
                    << std::setw(10)    << ReactivePowerBound().Minimum() * baseMva
                    << std::setw(10)    << VoltageMagnitude()
                    << std::setw(10)    << NominalPower()
                    << std::setw(10)    << IsActive()
                    << std::setw(10)    << RealPowerBound().Maximum() * baseMva
                    << std::setw(10)    << RealPowerBound().Minimum() * baseMva
                    << std::setw(6)     << Pc1()
                    << std::setw(6)     << Pc2()
                    << std::setw(8)     << Qc1Bound().Minimum()
                    << std::setw(8)     << Qc1Bound().Maximum()
                    << std::setw(8)     << Qc2Bound().Minimum()
                    << std::setw(8)     << Qc2Bound().Maximum()
                    << std::setw(9)     << RampAgc()
                    << std::setw(8)     << Ramp10()
                    << std::setw(8)     << Ramp30()
                    << std::setw(8)     << RampQ()
                    << std::setw(6)     << Apf()
                    << std::endl;
            }

            /**
             * @brief      Writes the values including the name of the generator property.
             * @details    List all IEEE standard input data.
             *
             * @param      outputStream  The stream to write data to
             * @param[in]  busName       The bus name
             * @param[in]  baseMva       The base mva
             */
            inline void Line ( std::ostream &   outputStream
                             , Types::name      busName
                             , Types::real      baseMva = 1 ) const
            {
                outputStream  << std::setprecision(2)
                    << std::fixed
                    << std::setw(20)    << busName
                    << std::setw(20)    << Name()
                    << std::setw(10)    << RealPower()     * baseMva
                    << std::setw(10)    << ReactivePower() * baseMva
                    << std::setw(10)    << ReactivePowerBound().Maximum() * baseMva
                    << std::setw(10)    << ReactivePowerBound().Minimum() * baseMva
                    << std::setw(10)    << VoltageMagnitude()
                    << std::setw(10)    << NominalPower()
                    << std::setw(10)    << IsActive()
                    << std::setw(10)    << RealPowerBound().Maximum() * baseMva
                    << std::setw(10)    << RealPowerBound().Minimum() * baseMva
                    << std::setw(6)     << Pc1()
                    << std::setw(6)     << Pc2()
                    << std::setw(8)     << Qc1Bound().Minimum()
                    << std::setw(8)     << Qc1Bound().Maximum()
                    << std::setw(8)     << Qc2Bound().Minimum()
                    << std::setw(8)     << Qc2Bound().Maximum()
                    << std::setw(9)     << RampAgc()
                    << std::setw(8)     << Ramp10()
                    << std::setw(8)     << Ramp30()
                    << std::setw(8)     << RampQ()
                    << std::setw(6)     << Apf()
                    << std::endl;
            }
        ///@}

    private:
#pragma mark MEMBERS
        ///@name Basic Property Members
        ///@{
            Types::name             name_;          /**< name of the vertex */
            TVertexType             type_;          /**< vertex type representing either source, sink or intermediate */
            Types::real             xCoordinate_;   /**< x-coordinate of the point if available */
            Types::real             yCoordinate_;   /**< y-coordinate of the point if available */
        ///@}

        /**@name Voltage Related Members */
        ///@{
            Types::real     voltageMagnitudeSnapshot_;  /**< The voltage magnitude set point in per unit (p.u.) 
                                                         *      of the nominal voltage @f$\voltagenominal@f$.
                                                         */
        ///@}

        /**@name Nominal Power Members */ 
        ///@{
            Types::real     nominalPower_;              /**< The total nominal power of machine (also known as 
                                                         *      MVA base or mBase), defaults set to baseMVA.
                                                         */
            bool            pNomExtendable_;            /**< Determines if the generator is extendable and thus, 
                                                         *      uses @p nominalRealPowerBound_ bounds. If the  
                                                         *      generator is not extendable @p mBase_ is used. 
                                                         *      Thus, the extension/upgrade level is unknown and 
                                                         *      can be decided by, e.g., a MILP. However, generators 
                                                         *      that are not build are not interesting for standard 
                                                         *      problems such as MTSF or MFF. Note that for PyPsa 
                                                         *      this are often renewable energies.
                                                         */
            TBound          nominalRealPowerBound_;     /**< If the generator is extendable the nominal real power 
                                                         *      @f$\realpowernominal@f$ can be in the interval 
                                                         *      @f$\realpowernominal\coloneqq[\realpowernominalmin,
                                                         *      \realpowernominalmax]@f$. 
                                                         */
            TPowerSign      sign_;                      /**< The power sign (1 means generation, -1 means load) */
        ///@}

        /**@name Real Power Members */
        ///@{
            Types::real     realPower_;                 /**< The real power generation @f$\realpowergeneration@f$
                                                         *      in @p MW. 
                                                         */
            TBound          realPowerBound_;            /**< The real power output bound @f$[\realpowergenerationmin, 
                                                         *      \realpowergenerationmax]@f$ in @p MW. 
                                                         */            
            Types::real     pc1_;                       /**< The lower real power output of PQ capability curve at 
                                                         *      PC1 in @p MW. 
                                                         */
            Types::real     pc2_;                       /**< The upper real power output of PQ capability curve at 
                                                         *      PC2 in @p MW. 
                                                         */
        ///@}

        /**@name Real Power Members */
        ///@{
            Types::real     reactivePower_;             /**< The reactive power generation @f$\reactivepowergeneration@f$ 
                                                         *      in @p MVAr. 
                                                         */
            TBound          reactivePowerBound_;        /**< The reactive power output bound @f$[\reactivepowergenerationmin, 
                                                         *      \reactivepowergenerationmax]@f$ in @p MVAr. 
                                                         */
            TBound          qc1Bound_;                  /**< The reactive power output bound at @p PC1 in @p MVAr. */
            TBound          qc2Bound_;                  /**< The reactive power output bound at @p PC2 in @p MVAr. */
        ///@}
        
        /**@name Status Members */
        ///@{
            TBusStatus      status_;                    /**< Describes the status of the generator. */
            bool            committable_;               /**< Decides whether unit commitment is @p active (while 
                                                         *      not being extendable) or @p inactive. 
                                                         */
        ///@}

        /**@name Type Members */
        ///@{
            TControlType    control_;                   /**< The control strategy, must be either @p PQ, @p PV 
                                                         *      or @p Slack. 
                                                         */
            TGeneratorType  generatorType_;             /**< The generator type, i.e., solar. */
            Types::real     efficiency_;                /**< The efficiency representing the ratio between primary 
                                                         *      and electrical energy. 
                                                         */
        ///@}
        
        /**@name Cost Specific Members */
        ///@{
            Types::real     marginalCost_;              /**< The marginal cost for production of 1 MW. */
            Types::real     capitalCost_;               /**< The Capital cost of extending p_nom by 1 MW. */
            
            Types::real     startUpCost_;               /**< The startup cost of the generator. */
            Types::real     shutDownCost_;              /**< The shutdown cost of the generator. */
        ///@}

        /**
         * @name    Ramp Members
         * @brief   Ramp Limits: The inner dynamic of generators does not
         *     always allow to change the production level, i.e., a maximum
         *     possible change is set by ramp limits.
         * 
         *     Ramp rate: Describes how fast generator outputs can be changed.
         *     There are usually ramping up (increasing) and down
         *     (decreasing), i.e., the unit is in units of power over time
         *     (here MW/min).
         */
        ///@{
            Types::real     minUpTime_;         /**< The minimum number of snapshots to be @p active. */
            Types::real     minDownTime_;       /**< The minimum number of snapshots to be @p inactive. */

            Types::real     rampAgc_;           /**< The ramp rate for load following AGC, where AGC stands for automatic generation control (in MW/min). */
            Types::real     ramp10_;            /**< The ramp rate for 10 minute reserves (in MW). */
            Types::real     ramp30_;            /**< The ramp rate for 30 minute reserves (in MW). */
            Types::real     rampQ_;             /**< The ramp rate for reactive power (2 sec timescale) (in MVAr/min). */
            Types::real     apf_;               /**< The area participation factor (APF). */

            Types::real     rampLimitUp_;       /**< The maximum increase in power per snapshot. */
            Types::real     rampLimitDown_;     /**< The maximum decrease in power per snapshot. */
            Types::real     rampLimitStartUp_;  /**< The maximum increase at startup in per unit of nominal power. */
            Types::real     rampLimitShutDown_; /**< The maximum decrease at shutdown in per unit of nominal power. */
        ///@}
        

        // Types::real MU_P_BOUND  /**< in u/MW, Kuhn-Tucker multiplier on lower/upper P_g limit (MU_PMIN / MU_PMAX) */
        // Types::real MU_QMAX  /**< in u/MVAr, Kuhn-Tucker multiplier on lower/upper Q_g limit (MU_QMIN / MU_QMAX) */
};

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__VERTICES__GENERATOR_PROPERTIES_HPP

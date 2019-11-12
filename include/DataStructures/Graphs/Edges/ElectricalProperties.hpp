/* 
 * ElectricalProperties.hpp
 *
 *  Created on: Sep 16, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__EDGES__ELECTRICAL_PROPERTIES_HPP
#define EGOA__DATA_STRUCTURES__EDGES__ELECTRICAL_PROPERTIES_HPP

#include <iostream>
#include <iomanip>

#include "Auxiliary/Constants.hpp"
#include "DataStructures/Bound.hpp"
#include "DataStructures/Graphs/Edges/Type.hpp"

namespace egoa::Edges {

template<Edges::CarrierDifferentiationType CarrierType> 
class CarrierDifferentiation;

/**
 * @brief      Class having all edge electrical properties (branch properties).
 * @details    @b DOI: <a href="https://doi.org/10.1109/TPAS.1973.293571">10.1109/TPAS.1973.293571</a>
 */
class ElectricalProperties {
    // Template type aliasing
    using TBound         = Bound<>;

    public:
        /**@name Constructors and Destructor */
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS
        
            ElectricalProperties()
            :   name_("Branch 0")
              , status_(true)
              , type_(Edges::ElectricalEdgeType::standard)
              , thetaBound_( TBound(0.0, 0.0) )
              , resistance_(0.0)
              , reactance_(0.0)
              , conductance_(0.0)
              , susceptance_(0.0)
              , charge_(0.0)
              , thermalLimitA_(0.0)
              , thermalLimitB_(0.0)
              , thermalLimitC_(0.0)
              , tapRatio_(1.0)
              , angleShift_(0.0)
              , tapRatioCosThetaShift_(0.0)
              , tapRatioSinThetaShift_(0.0)
              // 
              , capitalCost_(0.0)
              , length_(0.0)
              , numberOfParallelLines_(0)
              , nominalApparentPower_(1.0)
              , nominalVoltage_(0.0)
              , nominalApparentPowerBound_( TBound(0.0, 0.0) )
              , nominalApparentPowerExtendable_(false)
              , terrainFactor_(0.0)
            {}

            ElectricalProperties ( Types::name name )
            : ElectricalProperties()
            {
                Name() = name;
            }
        ///@}

        /**
         * @brief Swapping the members of two ElectricalProperties
         * 
         * @param lhs Left ElectricalProperties
         * @param rhs Right ElectricalProperties
         */
        friend void swap ( ElectricalProperties & lhs, ElectricalProperties & rhs ) 
        { // Necessary for the copy and swap idiom
            using std::swap; // enable ADL
            swap( lhs.name_,                    rhs.name_ );
            swap( lhs.status_,                  rhs.status_);
            swap( lhs.type_,                    rhs.type_);
            swap( lhs.thetaBound_,              rhs.thetaBound_);
            swap( lhs.resistance_,              rhs.resistance_);
            swap( lhs.reactance_,               rhs.reactance_);
            swap( lhs.conductance_,             rhs.conductance_);
            swap( lhs.susceptance_,             rhs.susceptance_);
            swap( lhs.charge_,                  rhs.charge_);
            swap( lhs.thermalLimitA_,           rhs.thermalLimitA_);
            swap( lhs.thermalLimitB_,           rhs.thermalLimitB_);
            swap( lhs.thermalLimitC_,           rhs.thermalLimitC_);
            swap( lhs.tapRatio_,                rhs.tapRatio_);
            swap( lhs.angleShift_,              rhs.angleShift_);
            swap( lhs.tapRatioCosThetaShift_,   rhs.tapRatioCosThetaShift_);
            swap( lhs.tapRatioSinThetaShift_,   rhs.tapRatioSinThetaShift_);

            swap( lhs.capitalCost_,             rhs.capitalCost_);
            swap( lhs.length_,                  rhs.length_);
            swap( lhs.numberOfParallelLines_,   rhs.numberOfParallelLines_);
            swap( lhs.nominalApparentPower_,    rhs.nominalApparentPower_);
            swap( lhs.nominalVoltage_,          rhs.nominalVoltage_);
            swap( lhs.nominalApparentPowerBound_,       rhs.nominalApparentPowerBound_);
            swap( lhs.nominalApparentPowerExtendable_,  rhs.nominalApparentPowerExtendable_);
            swap( lhs.terrainFactor_,           rhs.terrainFactor_);
        }

        ///@name Comparators
        ///@{
#pragma mark COMPARATORS
            /**
             * @brief      Comparator
             *
             * @param      lhs   The left edge.
             * @param      rhs   The right edge.
             *
             * @return     @p true if the edges are the same, @p false otherwise.
             */
            friend bool operator== ( ElectricalProperties const & lhs
                                   , ElectricalProperties const & rhs) 
            {
                return ( lhs.Name()                             == rhs.Name()       ) 
                    && ( lhs.Status()                           == rhs.Status()     )
                    && ( lhs.Type()                             == rhs.Type()       )
                    && ( lhs.Resistance()                       == rhs.Resistance() )
                    && ( lhs.Reactance()                        == rhs.Reactance()  )
                    && ( lhs.conductance_                       == rhs.conductance_ )
                    && ( lhs.susceptance_                       == rhs.susceptance_ )
                    && ( lhs.Weight()                           == rhs.Weight() )
                    && ( lhs.Charge()                           == rhs.Charge() )
                    && ( lhs.ThermalLimit()                     == rhs.ThermalLimit()  ) 
                    && ( lhs.ThermalLimitB()                    == rhs.ThermalLimitB() )
                    && ( lhs.ThermalLimitC()                    == rhs.ThermalLimitC() )
                    && ( lhs.TapRatio()                         == rhs.TapRatio()      )
                    && ( lhs.AngleShift()                       == rhs.AngleShift()    )
                    && ( lhs.TapRatioCosThetaShift()            == rhs.TapRatioCosThetaShift() )
                    && ( lhs.TapRatioSinThetaShift()            == rhs.TapRatioSinThetaShift() )
                    && ( lhs.ThetaBound()                       == rhs.ThetaBound()  )
                    && ( lhs.CapitalCost()                      == rhs.CapitalCost() )
                    && ( lhs.Length()                           == rhs.Length()      )
                    && ( lhs.NumberOfParallelLines()            == rhs.NumberOfParallelLines() )
                    && ( lhs.NominalApparentPower()             == rhs.NominalApparentPower()  )
                    && ( lhs.NominalVoltage()                   == rhs.NominalVoltage()        )
                    && ( lhs.NominalApparentPowerBound()        == rhs.NominalApparentPowerBound()      )
                    && ( lhs.NominalApparentPowerExtendable()   == rhs.NominalApparentPowerExtendable() )
                    && ( lhs.TerrainFactor()                    == rhs.TerrainFactor() );
            }

            /**
             * @brief      Comparator
             *
             * @param      lhs   The left edge.
             * @param      rhs   The right edge.
             *
             * @return     @p false if the edges are the same, @p true otherwise.
             */
            friend bool operator!=( ElectricalProperties const & lhs
                                  , ElectricalProperties const & rhs) 
            {
                return !(lhs == rhs);
            }
        ///@}        

        /**@name Getter and setter */
        ///@{
#pragma mark GETTER_AND_SETTER
            inline Types::string     Name()                  const { return name_; }
            inline Types::string   & Name()                        { return name_; }

            inline bool              Status()                const { return status_; }
            inline bool            & Status()                      { return status_; }

            inline Edges::ElectricalEdgeType      Type()     const { return type_; }
            inline Edges::ElectricalEdgeType    & Type()           { return type_; }

            inline Types::real       Resistance()            const { return resistance_; }
            inline Types::real     & Resistance()                  { return resistance_; }

            inline Types::real       Reactance()             const { return reactance_; }
            inline Types::real     & Reactance()                   { return reactance_; }

            template<Edges::CarrierDifferentiationType CarrierType>
            inline Types::real       Conductance()                    const { return CarrierDifferentiation<CarrierType>::Conductance(*this); }
            inline void              Conductance(Types::real conductance)   { conductance_ = conductance; }

            template<Edges::CarrierDifferentiationType CarrierType>
            inline Types::real       Susceptance()                    const { return CarrierDifferentiation<CarrierType>::Susceptance(*this); }
            inline void              Susceptance(Types::real susceptance)   { susceptance_ = susceptance; }

            inline Types::real       Weight()                const { return thermalLimitA_; }
            inline Types::real     & Weight()                      { return thermalLimitA_; }

            inline Types::real       Charge()                const { return charge_; }
            inline Types::real     & Charge()                      { return charge_; }

            inline Types::real       ThermalLimit()          const { return thermalLimitA_; }
            inline Types::real     & ThermalLimit()                { return thermalLimitA_; }

            inline Types::real       ThermalLimitB()         const { return thermalLimitB_; }
            inline Types::real     & ThermalLimitB()               { return thermalLimitB_; }

            inline Types::real       ThermalLimitC()         const { return thermalLimitC_; }
            inline Types::real     & ThermalLimitC()               { return thermalLimitC_; }

            inline Types::real       TapRatio()              const { return tapRatio_; }
            inline Types::real     & TapRatio()                    { return tapRatio_; }

            inline Types::real       AngleShift()            const { return angleShift_; }
            inline Types::real     & AngleShift()                  { return angleShift_; }

            inline Types::real       TapRatioCosThetaShift() const { return tapRatioCosThetaShift_; }
            inline Types::real     & TapRatioCosThetaShift()       { return tapRatioCosThetaShift_; }

            inline Types::real       TapRatioSinThetaShift() const { return tapRatioSinThetaShift_; }
            inline Types::real     & TapRatioSinThetaShift()       { return tapRatioSinThetaShift_; }
            
            // used to be Bound type
            inline TBound            ThetaBound()            const { return thetaBound_; }
            inline TBound          & ThetaBound()                  { return thetaBound_; }
        ///@}
            
            // PyPsa
            inline Types::real       CapitalCost()           const { return capitalCost_; }
            inline Types::real     & CapitalCost()                 { return capitalCost_; }

            inline Types::real       Length()                const { return length_; }
            inline Types::real     & Length()                      { return length_; }

            inline Types::count      NumberOfParallelLines() const { return numberOfParallelLines_; }
            inline Types::count    & NumberOfParallelLines()       { return numberOfParallelLines_; }

            inline Types::real       NominalApparentPower()  const { return nominalApparentPower_; }
            inline Types::real     & NominalApparentPower()        { return nominalApparentPower_; }

            inline Types::real       NominalVoltage()        const { return nominalVoltage_; }
            inline Types::real     & NominalVoltage()              { return nominalVoltage_; }

            inline TBound            NominalApparentPowerBound() const { return nominalApparentPowerBound_; }
            inline TBound          & NominalApparentPowerBound()   { return nominalApparentPowerBound_; }

            inline bool              NominalApparentPowerExtendable() const { return nominalApparentPowerExtendable_; }
            inline bool            & NominalApparentPowerExtendable()       { return nominalApparentPowerExtendable_; }

            inline Types::real       TerrainFactor()                  const { return terrainFactor_; }
            inline Types::real     & TerrainFactor()                        { return terrainFactor_; }
            
            
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
                    << std::setw(15)    << "Name"
                    << std::setw(6)     << "Source"
                    << std::setw(6)     << "Target"
                    << std::setw(10)    << "Resistance"
                    << std::setw(10)    << "Reactance"
                    << std::setw(10)    << "Susceptance" 
                    << std::setw(10)    << "ThermalLineLimitA" 
                    << std::setw(10)    << "ThermalLineLimitB"
                    << std::setw(10)    << "ThermalLineLimitC"
                    << std::setw(10)    << "Ratio"
                    << std::setw(10)    << "Angle"
                    << std::setw(6)     << "Status"
                    << std::setw(10)    << "AngleMinimum"
                    << std::setw(10)    << "AngleMaximum"
                    << std::endl;
            }

            /**
             * @brief      Header out stream.
             * @details    List all IEEE standard input data.
             *
             * @param      outputStream  The stream to write data to, e.g., std::cout.
             */
            static inline void Header ( std::ostream & outputStream) 
            {
                outputStream  
                    << std::setw(15)    << "name"
                    << std::setw(6)     << "fbus"
                    << std::setw(6)     << "tbus"
                    << std::setw(10)    << "r"
                    << std::setw(10)    << "x"
                    << std::setw(10)    << "b" 
                    << std::setw(10)    << "rateA"
                    << std::setw(10)    << "rateB"
                    << std::setw(10)    << "rateC"
                    << std::setw(10)    << "ratio"
                    << std::setw(10)    << "angle"
                    << std::setw(6)     << "status"
                    << std::setw(10)    << "angmin"
                    << std::setw(10)    << "angmax"
                    << std::endl;
            }

            /**
             * @brief      Line out stream.
             * @details    List all IEEE standard input data.
             *
             * @param      outputStream  The stream to write data to, e.g., std::cout.
             * @param[in]  sourceName    The source name
             * @param[in]  targetName    The target name
             * @param[in]  baseMva       The base mva
             */
            inline void Line ( std::ostream & outputStream
                             , Types::name    sourceName
                             , Types::name    targetName
                             , Types::real    baseMva = 1 ) const 
            {
                outputStream  
                    << std::setprecision(2)
                    << std::fixed
                    << std::setw(15)    << Name()
                    << std::setw(6)     << sourceName
                    << std::setw(6)     << targetName
                    << std::setw(10)    << Resistance()
                    << std::setw(10)    << Reactance()
                    << std::setw(10)    << Charge()
                    << std::setw(10)    << ThermalLimit()  * baseMva * NominalApparentPower()
                    << std::setw(10)    << ThermalLimitB() * baseMva * NominalApparentPower()
                    << std::setw(10)    << ThermalLimitC() * baseMva * NominalApparentPower()
                    << std::setw(10)    << TapRatio()
                    << std::setw(10)    << AngleShift()  / Const::PI * 180
                    << std::setw(6)     << Status()
                    << std::setw(10)    << ThetaBound().Minimum() / Const::PI * 180
                    << std::setw(10)    << ThetaBound().Maximum() / Const::PI * 180
                    << std::endl;
            }

            /**
             * @brief      Writes the electrical property to an output stream.
             *
             * @param      outputStream  The stream to write data to, e.g., std::cout.
             * @param[in]  rhs           The electrical property.
             *
             * @return     The output stream.
             */
            friend std::ostream & operator<< ( std::ostream               & outputStream
                                             , ElectricalProperties const & rhs ) 
            {
                outputStream  << std::setprecision(2)
                    << std::fixed
                    << std::endl
                    << "Branch " << rhs.Name()  << std::endl
                    << "-------------------"    << std::endl
                    << std::setw(30) << "\tthermal line limit: "<< std::setw(10) << rhs.ThermalLimit()   << std::setw(10) << " MW, "
                                                                << std::setw(10) << rhs.ThermalLimitB()  << std::setw(10) << " MW, "
                                                                << std::setw(10) << rhs.ThermalLimitC()  << std::setw(10) << " MW, "                      << std::endl
                    << std::setw(30) << "\timpedance Z: "       << std::setw(10) << rhs.Resistance()     << std::setw(10) << " p.u. (R), "
                                                                << std::setw(10) << rhs.Reactance()      << std::setw(10) << " p.u. (X), "                << std::endl
                    << std::setw(30) << "\tcharge: "            << std::setw(10) << rhs.Charge()         << std::setw(10) << ", "                         << std::endl
                    << std::setw(30) << "\ttap ratio: "         << std::setw(10) << rhs.TapRatio()       << std::setw(10) << " (tau),"                    << std::endl
                    << std::setw(30) << "\tangle shift: "       << std::setw(10) << rhs.AngleShift()     << std::setw(10) << " theta shift/final angle,"  << std::endl;
                return outputStream;                    
            }
        ///@}


    private:
        Types::string   name_;                  /**< Name of the branch */

        bool            status_;                /**< in {0,1}, on/off status of a branch, i.e. closed or open circuit */

        Edges::ElectricalEdgeType type_;

        // used to be type Bound
        TBound          thetaBound_;            /**< in rad, minimum/maximum angle difference, theta(source) - theta(target) =
                                                             delta theta; Thermal limit bound */

        /**@name Branch impedance @f$ Z = R + j X @f$ in p.u. 
         * @note A line with impedance 0 can be removed unless it is a jumper line. 
         */
        //@{
            Types::real resistance_;            /**< in p.u., resistance r */
            Types::real reactance_;             /**< in p.u., reactance  x */
        ///@}
        Types::real     conductance_;           /**< in p.u., conductance g, not included in IEEE data */
        Types::real     susceptance_;           /**< in p.u., susceptance b, not included in IEEE data */ 
        Types::real     charge_;                /**< in p.u., total line charging susceptance (b) 
                                                              0 unless the transmission line has been combined
                                                              with a transformer then add a line charging */

        /**@name Line MVA ratings 
         * @brief Three MVA ratings with Rate A being the lowest one.
         */
        ///@{
            Types::real thermalLimitA_;         /**< in MVA, standard thermal line limit (long term rating) */
            Types::real thermalLimitB_;         /**< in MVA, first emergency thermal line limit (short term rating) */
            Types::real thermalLimitC_;         /**< in MVA, second emergency thermal line limit (emergency rating) */
        ///@}

        /**@name Transformer */
        //@{
            Types::real tapRatio_;              /**< in -, tap ratio representing final ratio, transformer off nominal turns
                                                     ratio, i non-zero (taps at source and impedance at target meaning 
                                                     @f$ r = x = b = 0 @f$, @f$ tap = |V(source)|/|V(target)|) @f$, tap = 0 
                                                     indicates transmission line rather than transformer, i.e., tap = 1 */
            Types::real angleShift_;            /**< in rad, transformer phase shift angle, known as theta shift (angle shift)
                                                     representing final angle, if it is positive it represents a delay. */
            Types::real tapRatioCosThetaShift_; /**< Tap ratio . cos(theta shift) */
            Types::real tapRatioSinThetaShift_; /**< Tap ratio . sin(theta shift) */
        ///@}        

        // PyPsa
        Types::real     capitalCost_;           /**< in Dollar, capital cost */
        Types::real     length_;                /**< in ?, length of a branch */
        Types::count    numberOfParallelLines_; /**< in -, number of parallel lines */
        Types::real     nominalApparentPower_;  /**< in MW or MVAr, nominal apparent power */
        Types::real     nominalVoltage_;        /**< in V, nominal voltage, basekv */
        TBound          nominalApparentPowerBound_;         /**< in MW or MVAr, minimum/maximum nominal apparent power */
        bool            nominalApparentPowerExtendable_;    /**< in MW or VAr, nominal apparent power */
        Types::real     terrainFactor_;                     /**< in -, terrain factor */

        friend CarrierDifferentiation<Edges::CarrierDifferentiationType::AC>;
        friend CarrierDifferentiation<Edges::CarrierDifferentiationType::DC>;
        friend CarrierDifferentiation<Edges::CarrierDifferentiationType::unknown>;

};

template<> 
class CarrierDifferentiation<Edges::CarrierDifferentiationType::AC> {
    typedef ElectricalProperties TEdge;
    public:
        /**
         * @brief      Conductance for the AC network
         * @details    This represents the "standard" conductance calculated
         *     by @f$r / (r^2 + x^2)@f$.
         *
         * @param      edge  The edge
         *
         * @return     The AC conductance g(u, v)
         */
        static inline Types::real Conductance ( TEdge const & edge ) {
            Types::real squareImpedanceMagnitude = ( pow( edge.Resistance(), 2 ) + pow( edge.Reactance(), 2 ) ); 
            if ( squareImpedanceMagnitude != 0 )
                return ( edge.Resistance() / squareImpedanceMagnitude );
            else {
                std::cerr << "AcConductance: Electrical edge has values r = x = 0";
                exit(-1);
            }
        }

        /**
         * @brief      Susceptance for the AC network
         * @details    This represents the "standard" susceptance calculated
         *     by @f$x / (r^2 + x^2)@f$.
         *     
         *     For more details see 
         *      Zimmerman, R. D., & Murillo-s, C. E. (2011). 
         *      Matpower 4.1 User’s Manual. 
         *      Power Systems Engineering Research Center (Pserc). 
         *      http://doi.org/http://www.pserc.cornell.edu/matpower/manual.pdf
         *
         * @param      edge  The edge
         *
         * @return     The AC susceptance b(u, v)
         */
        static inline Types::real Susceptance ( TEdge const & edge ) 
        {
            Types::real squareImpedanceMagnitude = ( pow( edge.Resistance(), 2 ) + pow( edge.Reactance(), 2 ) ); 
            if ( squareImpedanceMagnitude != 0 ) {
                return ( -edge.Reactance() / squareImpedanceMagnitude );
            } else {
                std::cerr << "AcSusceptance: Electrical edge has values r = x = 0";
                exit(-1);
            }
        }
};

/**
 * @brief      Class for carrier differentiation.
 * @details    For the carrier differentiation we distinguish between DC and
 *     AC carrier. Dependent on the carrier the computation for the
 *     susceptance and conductance changes.
 */
template<> 
class CarrierDifferentiation<Edges::CarrierDifferentiationType::DC> {
    typedef ElectricalProperties TEdge;
    public:
        /**
         * @brief      Conductance for the DC approximation of an AC network.
         * @details    For the DC-Approximation the resistance becomes r = 0.
         *     Thus, the conductance term @f$r / (r^2 + x^2)@f$ becomes 0.
         *     Note that this is often overseen in other tools.
         *
         * @param      edge  The edge.
         *
         * @return     Conductance g(u, v) of the DC approximation.
         */
        static inline Types::real Conductance ( TEdge const & edge ) 
        {
            return 0.0;
        }

        /**
         * @brief      Susceptance for the DC approximation of an AC network
         * @details    For the DC-Approximation r = 0. Thus, the term @f$x /(r^2
         *     + x^2)@f$ becomes @f$1 / x@f$. Note that this is often overseen
         *       in other tools.
         * 
         *     For more details see 
         *      Zimmerman, R. D., & Murillo-s, C. E. (2011).  
         *      Matpower 4.1 User’s Manual. 
         *      Power Systems Engineering Research Center (Pserc). 
         *      http://doi.org/http://www.pserc.cornell.edu/matpower/manual.pdf
         *
         * @param      edge  The edge.
         *
         * @return     Susceptance b(u, v) of the DC approximation.
         */
        static inline Types::real Susceptance ( TEdge const & edge ) {
            if ( edge.Reactance() != 0 )
                return ( -1 / edge.Reactance() );
            else {
                std::cerr << "DcSusceptance: Electrical edge has values r = x = 0";
                exit(-1);
            }
        }
};

/**
 * @brief      Class for carrier differentiation.
 * @details    Detailed information of the susceptance b and conductance g can
 *     be extracted from the data itself.
 */
template<> 
class CarrierDifferentiation<Edges::CarrierDifferentiationType::unknown> {
    typedef ElectricalProperties TEdge;
    public:
        static inline Types::real Conductance ( TEdge const & edge ) {
            return edge.conductance_;
        }

        static inline Types::real Susceptance ( TEdge const & edge ) {
            return edge.susceptance_;
        }    
};

} // namespace egoa::Edge

#endif // EGOA__DATA_STRUCTURES__EDGES__ELECTRICAL_PROPERTIES_HPP

/*
 * VoltageAngleDifferenceLabel.hpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Franziska Wegner
 */
 
#ifndef EGOA__DATA_STRUCTURES__LABELS__DOMINATING_THETA_PATH_LABEL_HPP
#define EGOA__DATA_STRUCTURES__LABELS__DOMINATING_THETA_PATH_LABEL_HPP

#include "SusceptanceNormLabel.hpp"

namespace egoa {

/**
 * @brief      Class for Voltage Angle Difference label.
 * @details    The voltage angle difference label consists of the susceptance
 *     norm and the minimum capacity of a path. The value is defined by 
 *     @f[
 *          \deltavangle(\vertexa,\vertexb) = \bnorm{\fpath{}{\vertexa}{\vertexb}} \cdot \fmincapacity{}{\fpath{}{\vertexa}{\vertexb}},
 *     @f] 
 *     where @f$\bnorm{\fpath{}{\vertexa}{\vertexb}} := \sum_{\edge\in\fpath{}{\vertexa}{\vertexb}}\susceptance(\edge)^{-1}@f$
 *     is the susceptance norm with
 *     @f$\susceptance(\vertexa,\vertexb)\in\reals@f$, 
 *     and 
 *     @f$\fmincapacity{}{ \fpath{}{\vertexa}{\vertexb} }:= \min_{ (\vertexa,\vertexb)\in\pathu}\fcapacity{}{\vertexa}{\vertexb}@f$ 
 *     with the thermal limit @f$\capacity\colon\edges\to\reals@f$. For more information see Section 3 in the paper 
 *     <a href="https://doi.org/10.1145/3208903.3208910">The Maximum Transmission Switching Flow Problem</a>.
 *     
 * @I{The formula in readable format:  delta = b(path(s,u)) . mincapacity(path(s,u))    }
 *
 * @tparam     ElementType  An edge providing access to the susceptance, e.g., an electrical edge.
 * 
 * @see        Edge::ElectricalEdge representing an ElementType interface.
 * @see        BucketElement representing an minimum interface requirement for a bucket.
 * @see        Label representing the base's base class.
 * @see        SusceptanceNormLabel representing the base class.
 */
template< typename ElementType          = Edges::Edge<Edges::ElectricalProperties>
        , typename VertexSetContainer   = std::unordered_set<Types::vertexId>
        , typename PointerType          = Types::vertexId >
class VoltageAngleDifferenceLabel : public SusceptanceNormLabel<ElementType, VertexSetContainer, PointerType> {
    public:
        // Type aliasing
        using TLabel   = SusceptanceNormLabel<ElementType, VertexSetContainer, PointerType>;
        using typename TLabel::TVertexId;
        using typename TLabel::TElement;
        using typename TLabel::TVertexSet;

    public:
        ///@name Constructors and Destructor
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS

            /**
             * @brief      Constructs the voltage angle difference label object.
             * @details    The label and vertex identifier and previous label
             *     and vertex identifiers are set to @p Const::NONE. The valid
             *     flag is set to @p true. Note that the susceptance norm is
             *     set to
             *     @f$\bnorm{\fpath{}{\vertexa}{\vertexb}} = 0.0@f$ and the
             *     minimum capacity to infinity representing the initial label
             *     @f$(0,\infty)@f$.
             *
             * @param[in]  vertexId  The vertex identifier.
             */
            VoltageAngleDifferenceLabel () 
            : VoltageAngleDifferenceLabel ( Const::NONE )
            {}

            /**
             * @brief      Constructs the voltage angle difference label object.
             * @details    The label identifier and previous label/vertex
             *     identifiers are set to @p Const::NONE. The valid flag is set
             *     to @p true. Note that the susceptance norm is set to
             *     @f$\bnorm{\fpath{}{\vertexa}{\vertexb}} = 0.0@f$ and the
             *     minimum capacity to infinity representing the initial label
             *     @f$(0,\infty)@f$.
             *
             * @param[in]  vertexId  The vertex identifier.
             */
            VoltageAngleDifferenceLabel ( Types::vertexId vertexId ) 
            : VoltageAngleDifferenceLabel ( vertexId, 0.0, Const::REAL_INFTY )
            {}

            /**
             * @brief      Constructs the voltage angle difference label object.
             * @details    The label identifier and previous label/vertex
             *     identifiers are set to @p Const::NONE. The valid flag is set
             *     to @p true.
             *
             * @param[in]  vertexId         The vertex identifier.
             * @param[in]  susceptanceNorm  The susceptance norm @f$\bnorm{\fpath{}{\vertexa}{\vertexb}}@f$. 
             * @param[in]  minimumCapacity  The minimum capacity @f$\fmincapacity{}{ \fpath{}{\vertexa}{\vertexb} }@f$.
             */
            VoltageAngleDifferenceLabel ( Types::vertexId   vertexId
                                        , Types::real       susceptanceNorm
                                        , Types::real       minimumCapacity ) 
            : TLabel ( vertexId, susceptanceNorm )
            , minimumCapacity_ ( minimumCapacity ) 
            {}

            /**
             * @brief      Constructs the voltage angle difference label object.
             * @details    The label identifier and previous label/vertex
             *     identifiers are set to @p Const::NONE. The valid flag is set
             *     to @p true.
             *
             * @param[in]  vertexId         The vertex identifier.
             * @param[in]  susceptanceNorm  The susceptance norm @f$\bnorm{\fpath{}{\vertexa}{\vertexb}}@f$. 
             * @param[in]  minimumCapacity  The minimum capacity @f$\fmincapacity{}{ \fpath{}{\vertexa}{\vertexb} }@f$.
             * @param[in]  vertexSet        The vertex set of visited vertices.
             */
            VoltageAngleDifferenceLabel ( Types::vertexId   vertexId
                                        , Types::real       susceptanceNorm
                                        , Types::real       minimumCapacity
                                        , TVertexSet        vertexSet ) 
            : TLabel ( vertexId, susceptanceNorm, vertexSet )
            , minimumCapacity_ ( minimumCapacity ) 
            {}

            /**
             * @brief      Copy constructor.
             *
             * @param      label  The voltage angle difference label.
             */
            VoltageAngleDifferenceLabel( VoltageAngleDifferenceLabel const & label ) = default;

            /**
             * @brief      Destroys the object.
             */
            ~VoltageAngleDifferenceLabel() {}
        ///@}

        /**
         * @brief      Generate source label.
         *
         * @param[in]  vertexId  The vertex identifier.
         *
         * @return     The voltage angle difference source label.
         */
        inline static VoltageAngleDifferenceLabel SourceLabel ( Types::vertexId  vertexId )
        {
            return VoltageAngleDifferenceLabel ( vertexId
                                               , 0.0
                                               , Const::REAL_INFTY
                                               , TVertexSet ( {{vertexId}} ) );
        }

        ///@name Domination Operators
        ///@{
#pragma mark DOMINATION_OPERATORS
            
            /**
             * @brief      Strict domination using less than.
             *
             * @param      rhs   The right hand side.
             *
             * @return     @p true if lhs < rhs, @p false otherwise.
             */
            inline bool operator<( VoltageAngleDifferenceLabel const & rhs ) const 
            {
                USAGE_ASSERT ( TLabel::SusceptanceNorm() != Const::NONE );
                USAGE_ASSERT ( MinimumCapacity()         != Const::NONE );
                
                return   ( *this <= rhs )   // Weak domination w.r.t. <=
                      && ( *this != rhs );  // Only false if both elements are equal 
            }

            /**
             * @brief      Weak domination using less or equal than.
             *
             * @param      rhs   The right hand side.
             *
             * @return     @p true if lhs <= rhs, @p false otherwise.
             */
            inline bool operator<=( VoltageAngleDifferenceLabel const & rhs ) const 
            { 
                USAGE_ASSERT ( TLabel::SusceptanceNorm() != Const::NONE );
                USAGE_ASSERT ( MinimumCapacity()         != Const::NONE );

                return ( TLabel::SusceptanceNorm() <= rhs.TLabel::SusceptanceNorm() ) 
                    && ( MinimumCapacity()         <= rhs.MinimumCapacity()         );
            }

            /**
             * @brief      Strict domination using greater than.
             *
             * @param      rhs   The right hand side.
             *
             * @return     @p true if lhs > rhs, @p false otherwise.
             */
            inline bool operator> ( VoltageAngleDifferenceLabel const & rhs ) const 
            { 
                USAGE_ASSERT ( TLabel::SusceptanceNorm() != Const::NONE );
                USAGE_ASSERT ( MinimumCapacity()         != Const::NONE );

                return   ( *this >= rhs )   // Weak domination w.r.t. >=
                      && ( *this != rhs );  // Only false if both elements are equal 
            }
            
            /**
             * @brief      Weak domination using greater or equal than.
             *
             * @param      rhs   The right hand side.
             *
             * @return     @p true if lhs >= rhs, @p false otherwise.
             */
            inline bool operator>=( VoltageAngleDifferenceLabel const & rhs ) const 
            { 
                USAGE_ASSERT ( TLabel::SusceptanceNorm() != Const::NONE );
                USAGE_ASSERT ( MinimumCapacity()         != Const::NONE );

                return ( TLabel::SusceptanceNorm() >= rhs.TLabel::SusceptanceNorm() ) 
                    && ( MinimumCapacity()         >= rhs.MinimumCapacity()         );
            }
        ///@}

        ///@name Comparison Operators
        ///@{
#pragma mark COMPARISON_OPERATORS

            /**
             * @brief      Equality check.
             *
             * @param      rhs   The right hand side.
             *
             * @return     @p true if lhs == rhs, @p false otherwise.
             */
            inline bool operator==( VoltageAngleDifferenceLabel const & rhs ) const 
            {
                USAGE_ASSERT ( TLabel::SusceptanceNorm() != Const::NONE );
                USAGE_ASSERT ( MinimumCapacity()         != Const::NONE );

                return ( Auxiliary::EQ ( TLabel::SusceptanceNorm(), rhs.TLabel::SusceptanceNorm() ) ) 
                    && ( Auxiliary::EQ ( MinimumCapacity(),         rhs.MinimumCapacity() ) );
            }

            /**
             * @brief      Inequality check.
             *
             * @param      rhs   The right hand side.
             *
             * @return     @p true if lhs != rhs, @p false otherwise.
             */
            inline bool operator!=( VoltageAngleDifferenceLabel const & rhs ) const 
            {
                USAGE_ASSERT ( TLabel::SusceptanceNorm() != Const::NONE );
                USAGE_ASSERT ( MinimumCapacity()         != Const::NONE );

                return !( *this == rhs );
            }
        ///@}

        ///@name Concatenation Operators 
        ///@{
#pragma mark CONCATENATION_OPERATORS

            /**
             * @brief      Addition operators testing for cycles.
             * @details    A cycle is created if and only if the vertex is already in
             *     the set of visited vertices @p vertexSet.
             *
             * @param      lhs        The left hand side representing a VoltageAngleDifferenceLabel.
             * @param      vertexId   The vertex identifier.
             *
             * @return     @p true if the element could be added without creating
             *     a cycle, @p false otherwise.
             */
            friend inline bool operator+( VoltageAngleDifferenceLabel const & lhs
                                        , TVertexId                   const & vertexId ) 
            {
                USAGE_ASSERT ( lhs.SusceptanceNorm()    != Const::NONE );
                USAGE_ASSERT ( lhs.MinimumCapacity()    != Const::NONE );
                USAGE_ASSERT ( vertexId                 != Const::NONE );

                bool isInsert = false;
                std::tie( std::ignore, isInsert ) = lhs.VertexSet().emplace( vertexId );
                return isInsert;
            }

            /**
             * @brief      Addition operators testing for cycles.
             *
             * @param      vertexId     The vertex identifier.
             * @param      rhs          The right hand side representing a VoltageAngleDifferenceLabel.
             *
             * @return     A pair of a hash map and boolean. The boolean is @p
             *     true if the element could be added without creating a
             *     cycle, @p false otherwise.
             */
            friend inline std::pair<TVertexSet, bool> operator+( TVertexId                   const & vertexId
                                                               , VoltageAngleDifferenceLabel const & rhs     ) 
            {
                USAGE_ASSERT ( rhs.SusceptanceNorm()    != Const::NONE );
                USAGE_ASSERT ( rhs.MinimumCapacity()    != Const::NONE );
                USAGE_ASSERT ( vertexId                 != Const::NONE );

                bool isInsert       = false;
                TVertexSet newSet   = rhs.VertexSet();
                
                std::tie( std::ignore, isInsert ) = newSet.emplace( vertexId );
                
                return std::make_pair ( newSet, isInsert );
            }

            /**
             * @brief      Addition operators testing for cycles.
             *
             * @param      edge  The edge.
             * @param      rhs   The susceptance norm label VoltageAngleDifferenceLabel.
             *
             * @return     A pair of a VoltageAngleDifferenceLabel and boolean. The boolean is
             *     @p true if the element could be added without creating a cycle,
             *     @p false otherwise.
             */
            friend inline std::pair<VoltageAngleDifferenceLabel, bool> operator+( TElement                    const & edge
                                                                                , VoltageAngleDifferenceLabel const & rhs ) 
            {
                USAGE_ASSERT ( rhs.SusceptanceNorm()    != Const::NONE );
                USAGE_ASSERT ( rhs.MinimumCapacity()    != Const::NONE );
                USAGE_ASSERT ( edge.Properties().template Susceptance<Edges::CarrierDifferentiationType::DC>()  != 0 );

                bool                        isInsert  = false;
                VoltageAngleDifferenceLabel newLabel  = rhs;

                newLabel           += edge;
                TVertexId vertexId  = edge.Other( rhs.Vertex() );
                
                ESSENTIAL_ASSERT ( vertexId == newLabel.Vertex() );

                std::tie( newLabel.VertexSet(), isInsert )  = vertexId + newLabel;

                return std::make_pair( newLabel, isInsert );
            }

            /**
             * @brief      Addition operators testing for cycles.
             *
             * @param      lhs   The susceptance norm label VoltageAngleDifferenceLabel.
             * @param      edge  The edge.
             *
             * @return     A pair of a LabelStruct and boolean. The boolean is
             *     @p true if the element could be added without creating a cycle,
             *     @p false otherwise.
             */
            friend inline std::pair<VoltageAngleDifferenceLabel, bool> operator+( VoltageAngleDifferenceLabel const & lhs
                                                                                , TElement                    const & edge ) 
            {
                USAGE_ASSERT ( lhs.SusceptanceNorm()    != Const::NONE );
                USAGE_ASSERT ( lhs.MinimumCapacity()    != Const::NONE );
                USAGE_ASSERT ( edge.Properties().template Susceptance<Edges::CarrierDifferentiationType::DC>()  != 0 );

                return edge + lhs;
            }

            /**
             * @brief      In place addition.
             *
             * @param      rhs   The right hand side representing a TElement.
             *
             * @return     The voltage angle difference label with added TElement.
             */
            inline VoltageAngleDifferenceLabel & operator+=( TElement const & rhs )
            {
                USAGE_ASSERT ( TLabel::SusceptanceNorm()    != Const::NONE );
                USAGE_ASSERT (         MinimumCapacity()    != Const::NONE );
                USAGE_ASSERT ( rhs.Properties().template Susceptance<Edges::CarrierDifferentiationType::DC>()  != 0);
                
                TLabel::SusceptanceNorm() += fabs( 1 / rhs.Properties().template Susceptance<Edges::CarrierDifferentiationType::DC>() );
                MinimumCapacity()          = std::min( MinimumCapacity(), rhs.Properties().ThermalLimit() );
                TLabel::Vertex()           = rhs.Other( TLabel::Vertex() );
                return *this;
            }
        ///@}

        ///@name Getter and Setter
        ///@{
#pragma mark GETTER_AND_SETTER

            /**
             * @brief      Getter for the minimum capacity.
             *
             * @return     The minimum capacity @f$\fmincapacity{}{\fpath{}{\vertexa}{\vertexb}}@f$.
             */
            inline Types::real   MinimumCapacity() const 
            { 
                return minimumCapacity_; 
            }

            /**
             * @brief      Setter for the minimum capacity.
             *
             * @return     The minimum capacity @f$\fmincapacity{}{\fpath{}{\vertexa}{\vertexb}}@f$.
             */
            inline Types::real & MinimumCapacity()       
            { 
                return minimumCapacity_; 
            }

            /**
             * @brief      Voltage angle difference value.
             * @details    Represents the total voltage angle difference (also
             *     known as delta theta or theta difference)
             *     @f$\bnorm{\fpath{}{\vertexa}{\vertexb}}@f$ on a path
             *     @f$\fpath{}{\vertexa}{\vertexb}@f$. It is calculated by
             *     @f[
             *          \deltavangle(\vertexa,\vertexb) = \bnorm{\fpath{}{\vertexa}{\vertexb}} \cdot \fmincapacity{}{\fpath{}{\vertexa}{\vertexb}},
             *     @f]
             *     where @f$\vertexa\in\vertices@f$ is the label's vertex.
             *     
             *     @I{ Code readable formula: delta = b(path(s,u)) . mincapacity(path(s,u))  where u is the label's vertex }
             *
             * @return     The voltage angle difference value @f$\deltavangle(\vertexa,\vertexb)@f$.
             */
            inline Types::real Value() const
            { 
                return ( TLabel::SusceptanceNorm() * MinimumCapacity() ); 
            }
        ///@}

#pragma mark OUTPUT
        /**
         * @brief      Output stream.
         *
         * @param      os    The output stream such as std::cout.
         * @param      rhs   The right hand side voltage angle difference label.
         *
         * @return     The output stream.
         */
        friend std::ostream& operator<< ( std::ostream                      & os
                                        , VoltageAngleDifferenceLabel const & rhs ) 
        {
            return os << "(" << rhs.SusceptanceNorm() << "," << rhs.MinimumCapacity() << ")";
        }

#pragma mark MEMBERS
    private:
        Types::real minimumCapacity_;   /**< The minimum capacity @f$\fmincapacity{}{\fpath{}{\vertexa}{\vertexb}}@f$ on a path @f$\fpath{}{\vertexa}{\vertexb}@f$. */
};

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__LABELS__DOMINATING_THETA_PATH_LABEL_HPP
 
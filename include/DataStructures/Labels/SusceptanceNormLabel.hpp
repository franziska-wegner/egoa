/*
 * SusceptanceNormLabel.hpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__LABELS__SUSCEPTANCE_NORM_LABEL_HPP
#define EGOA__DATA_STRUCTURES__LABELS__SUSCEPTANCE_NORM_LABEL_HPP

#include "Label.hpp"

namespace egoa {

/**
 * @brief      Class for Susceptance norm label.
 * @details    The susceptance norm is defined by 
 *             @f[ 
 *                  \bnorm{\fpath{}{\vertexa}{\vertexb}} := \sum_{\edge\in\fpath{}{\vertexa}{\vertexb}}\susceptance(\edge)^{-1},
 *             @f] 
 *             where @f$\susceptance(\vertexa,\vertexb)\in\reals@f$ is the
 *             susceptance defined for all @f$(\vertexa,\vertexb)\in\edges@f$.
 *             For more information see Section 3 in the paper <a
 *             href="https://doi.org/10.1145/3208903.3208910">The Maximum
 *             Transmission Switching Flow Problem</a>.
 *
 * @tparam     ElementType  An edge providing access to the susceptance, e.g., an electrical edge.
 * @todo       What are the formal requirements for @p ElementType? From what I can see below,
 *             the following expressions must be valid:
 *             @code
 *             Types::real b = element.template Susceptance<Edge::CarrierDifferentiationType::DC>();
 *             Types::vertexId id = ...;
 *             element.Other(id);
 *             @endcode
 * 
 * @see        Edge::ElectricalEdge representing an ElementType interface.
 * @see        BucketElement representing an minimum interface requirement for a bucket.
 * @see        Label representing the base class.
 * @see        VoltageAngleDifferenceLabel representing an extension of this label.
 */
template< typename ElementType          = Edges::Edge<Edges::ElectricalProperties>
        , typename VertexSetContainer   = std::unordered_set<Types::vertexId>
        , typename PointerType          = Types::vertexId >
class SusceptanceNormLabel : public Label<ElementType, VertexSetContainer, PointerType> {
    public:
        // Type aliasing
        using typename Label<ElementType,VertexSetContainer, PointerType>::TLabel;
        using typename TLabel::TVertexId;
        using typename TLabel::TElement;
        using typename TLabel::TVertexSet;

    public:
        ///@name Constructors and Destructor
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS

            /**
             * @brief      Constructs the Susceptance Norm label object.
             * @details    The label and vertex identifier and previous label
             *     and vertex identifiers are set to @p Const::NONE. The @p
             *     valid flag is set to @p true. Note that the susceptance
             *     norm is set to infinity.
             *
             * @param[in]  vertexId  The vertex identifier.
             */
            SusceptanceNormLabel () 
            : SusceptanceNormLabel ( Const::NONE, Const::REAL_INFTY )
            {}

            /**
             * @brief      Constructs the Susceptance Norm label object.
             * @details    The label identifier and previous label/vertex
             *     identifiers are set to @p Const::NONE. The @p valid flag is
             *     set to @p true. Note that the susceptance norm is set to
             *     infinity.
             *
             * @param[in]  vertexId  The vertex identifier.
             */
            SusceptanceNormLabel ( Types::vertexId vertexId ) 
            : SusceptanceNormLabel ( vertexId, Const::REAL_INFTY )
            {}

            /**
             * @brief      Constructs the Susceptance Norm label object.
             * @details    The label identifier and previous label and vertex
             *     identifiers are set to @p Const::NONE. The @p valid flag is
             *     set to @p true.
             *
             * @param[in]  vertexId         The vertex identifier.
             * @param[in]  susceptanceNorm  The susceptance norm @f$\bnorm{\fpath{}{\vertexa}{\vertexb}}@f$.
             */
            SusceptanceNormLabel ( Types::vertexId  vertexId
                                 , Types::real      susceptanceNorm ) 
            : SusceptanceNormLabel ( vertexId, susceptanceNorm, TVertexSet() )
            {}

            /**
             * @brief      Constructs the Susceptance Norm label object.
             * @details    The label identifier and previous label and vertex
             *     identifiers are set to @p Const::NONE. The @p valid flag is
             *     set to @p true.
             *
             * @param[in]  vertexId         The vertex identifier.
             * @param[in]  susceptanceNorm  The susceptance norm @f$\bnorm{\fpath{}{\vertexa}{\vertexb}}@f$.
             * @param[in]  vertexSet        The vertex set of visited vertices.
             */
            SusceptanceNormLabel ( Types::vertexId  vertexId
                                 , Types::real      susceptanceNorm
                                 , TVertexSet       vertexSet ) 
            : TLabel ( vertexId )
            , susceptanceNorm_ ( susceptanceNorm )
            , vertexSet_ ( vertexSet )
            {}

            /**
             * @brief      Copy constructor.
             * @details    Constructs the susceptance norm label object.
             *
             * @param      label  The susceptance norm label.
             */
            SusceptanceNormLabel ( SusceptanceNormLabel const & label ) = default;

            /**
             * @brief      Destroys the susceptance norm label object.
             */
            ~SusceptanceNormLabel () {}
        ///@}

        /**
         * @brief      Generate source label.
         *
         * @param[in]  vertexId  The vertex identifier.
         *
         * @return     The susceptance norm source label.
         */
        inline static SusceptanceNormLabel SourceLabel ( Types::vertexId  vertexId )
        {
            return SusceptanceNormLabel ( vertexId, 0.0, TVertexSet ( {{vertexId}} ) );
        }

        ///@name Getter and Setter
        ///@{
#pragma mark GETTER_AND_SETTER
            
            /**
             * @brief      Getter of the set of all visited vertices from the source.
             *
             * @return     Set of all visited vertices.
             */
            inline TVertexSet const & VertexSet() const 
            {
                return vertexSet_;
            }

            /**
             * @brief      Getter of the set of all visited vertices from the source.
             *
             * @return     Set of all visited vertices.
             */
            inline TVertexSet & VertexSet() 
            {
                return vertexSet_;
            }
        ///@}

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
            inline bool operator< ( SusceptanceNormLabel const & rhs ) const 
            {
                return this->SusceptanceNorm() < rhs.SusceptanceNorm();
            }

            /**
             * @brief      Weak domination using less or equal than.
             *
             * @param      rhs   The right hand side.
             *
             * @return     @p true if lhs <= rhs, @p false otherwise.
             */
            inline bool operator<= ( SusceptanceNormLabel const & rhs )  const 
            { 
                return !(*this > rhs); 
            }

            /**
             * @brief      Strict domination using greater than.
             *
             * @param      rhs   The right hand side.
             *
             * @return     @p true if lhs > rhs, @p false otherwise.
             */
            inline bool operator> ( SusceptanceNormLabel const & rhs )   const 
            { 
                return rhs < *this; 
            }
            
            /**
             * @brief      Weak domination using greater or equal than.
             *
             * @param      rhs   The right hand side.
             *
             * @return     @p true if lhs >= rhs, @p false otherwise.
             */
            inline bool operator>= ( SusceptanceNormLabel const & rhs )  const 
            { 
                return !(rhs > *this); 
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
            inline bool operator== ( SusceptanceNormLabel const & rhs ) const 
            {
                return this->SusceptanceNorm() == rhs.SusceptanceNorm();
            }

            /**
             * @brief      Inequality check.
             *
             * @param      rhs   The right hand side.
             *
             * @return     @p true if lhs != rhs, @p false otherwise.
             */
            inline bool operator!= ( SusceptanceNormLabel const & rhs ) const 
            {
                return !(*this==rhs);
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
             * @param      lhs        The left hand side representing a SusceptanceNormLabel.
             * @param      vertexId   The vertex identifier.
             *
             * @return     @p true if the element could be added without creating
             *     a cycle, @p false otherwise.
             */
            friend inline bool operator+( SusceptanceNormLabel const & lhs
                                        , TVertexId            const & vertexId ) 
            {
                USAGE_ASSERT ( lhs.SusceptanceNorm()    != Const::NONE );
                USAGE_ASSERT ( vertexId                 != Const::NONE );

                bool isInsert = false;
                std::tie( std::ignore, isInsert ) = lhs.VertexSet().emplace( vertexId );
                return isInsert;
            }

            /**
             * @brief      Addition operators testing for cycles.
             *
             * @param      vertexId     The vertex identifier.
             * @param      rhs          The right hand side representing a SusceptanceNormLabel.
             *
             * @return     A pair of a hash map and boolean. The boolean is True if
             *     the element could be added without creating a cycle, False
             *     otherwise.
             */
            friend inline std::pair<TVertexSet, bool> operator+( TVertexId            const & vertexId
                                                               , SusceptanceNormLabel const & rhs     ) 
            {
                USAGE_ASSERT ( rhs.SusceptanceNorm()    != Const::NONE );
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
             * @param      rhs   The susceptance norm label SusceptanceNormLabel.
             *
             * @return     A pair of a SusceptanceNormLabel and boolean. The boolean is
             *     @p true if the element could be added without creating a cycle,
             *     @p false otherwise.
             */
            friend inline std::pair<SusceptanceNormLabel, bool> operator+( TElement             const & edge
                                                                         , SusceptanceNormLabel const & rhs ) 
            {
                USAGE_ASSERT ( rhs.SusceptanceNorm()    != Const::NONE );
                USAGE_ASSERT ( edge.Properties().template Susceptance<Edges::CarrierDifferentiationType::DC>()  != 0 );

                bool                 isInsert  = false;
                SusceptanceNormLabel newLabel  = rhs;

                newLabel           += edge;
                TVertexId vertexId  = edge.Other( rhs.Vertex() );
                
                ESSENTIAL_ASSERT ( vertexId == newLabel.Vertex() );

                std::tie( newLabel.VertexSet(), isInsert )  = vertexId + rhs;

                return std::make_pair( newLabel, isInsert );
            }

            /**
             * @brief      Addition operators testing for cycles.
             *
             * @param      lhs   The susceptance norm label SusceptanceNormLabel.
             * @param      edge  The edge.
             *
             * @return     A pair of a LabelStruct and boolean. The boolean is
             *     @p true if the element could be added without creating a cycle,
             *     @p false otherwise.
             */
            friend inline std::pair<SusceptanceNormLabel, bool> operator+( SusceptanceNormLabel const & lhs
                                                                         , TElement             const & edge ) 
            {
                USAGE_ASSERT ( lhs.SusceptanceNorm()    != Const::NONE );
                USAGE_ASSERT ( edge.Properties().template Susceptance<Edges::CarrierDifferentiationType::DC>()  != 0 );

                return edge + lhs;
            }

            /**
             * @brief      In place addition.
             *
             * @param      rhs   The right hand side.
             *
             * @return     The susceptance norm label with added TElement.
             */
            inline SusceptanceNormLabel & operator+= ( TElement const & rhs )
            {
                USAGE_ASSERT ( SusceptanceNorm()    != Const::NONE );
                USAGE_ASSERT ( rhs.Properties().template Susceptance<Edges::CarrierDifferentiationType::DC>()  != 0 ); // TODO: Check for >0?

                SusceptanceNorm()         += fabs( 1 / rhs.Properties().template Susceptance<Edges::CarrierDifferentiationType::DC>() );
                TLabel::Vertex()           = rhs.Other( TLabel::Vertex() );

                return *this;
            }
        ///@}

        ///@name Getter and Setter
        ///@{
#pragma mark GETTER_AND_SETTER

            /**
             * @brief      Getter and setter for the susceptance norm.
             *
             * @return     The susceptance norm value
             *     @f$\bnorm{\fpath{}{\vertexa}{\vertexb}}@f$ on a path
             *     @f$\fpath{}{\vertexa}{\vertexb}@f$ of the label.
             */
            inline Types::real   SusceptanceNorm() const  
            { 
                return susceptanceNorm_; 
            }

            /**
             * @brief      Getter and setter for the susceptance norm.
             *
             * @return     The susceptance norm value
             *     @f$\bnorm{\fpath{}{\vertexa}{\vertexb}}@f$ on a path
             *     @f$\fpath{}{\vertexa}{\vertexb}@f$ of the label.
             */
            inline Types::real & SusceptanceNorm()        
            { 
                return susceptanceNorm_; 
            }

            /**
             * @brief      Susceptance norm label value.
             * @details    Represents the objective of this label that is the
             *     total susceptance norm of the path.
             *
             * @return     The susceptance norm label value
             *     @f$\bnorm{\fpath{}{\vertexa}{\vertexb}}@f$.
             */
            inline Types::real Value() const
            { 
                return SusceptanceNorm(); 
            }
        ///@}

#pragma mark OUTPUT
        /**
         * @brief      Output stream.
         *
         * @param      os    The output stream such as std::cout.
         * @param      rhs   The right hand side susceptance norm label.
         *
         * @return     The output stream.
         */
        friend std::ostream & operator<< ( std::ostream               & os
                                         , SusceptanceNormLabel const & rhs ) 
        {
            return os << rhs.SusceptanceNorm();
        }

#pragma mark MEMBERS
    private:
        Types::real     susceptanceNorm_;   /**< The susceptance norm value @f$\bnorm{\fpath{}{\vertexa}{\vertexb}}@f$ on a path @f$\fpath{}{\vertexa}{\vertexb}@f$. */
        TVertexSet      vertexSet_;         /**< The vertex set representing the set of visited vertices. */
};

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__LABELS__SUSCEPTANCE_NORM_LABEL_HPP
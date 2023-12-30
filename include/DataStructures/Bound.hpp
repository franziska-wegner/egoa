/*
 * Bound.hpp
 *
 *  Created on: Sep 06, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURE__BOUND_HPP
#define EGOA__DATA_STRUCTURE__BOUND_HPP

#include "Exceptions/Exceptions.hpp"
#include "Exceptions/Assertions.hpp"

namespace egoa {

/**
 * @brief      Class for bounds.
 *
 * @tparam     BoundType  The type of the lower and upper bounds.
 */
template<typename BoundType = double>
class Bound {
    private:
#pragma mark TYPE_ALIASING
    using TBound = BoundType;   /**< The bound type, e.g., int. */

    public:
        /**@name Constructors and Destructor */
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS

            Bound() = delete;

            /**
             * @brief      Constructs the object.
             *
             * @param[in]  minimum  The minimum representing the lower bound.
             * @param[in]  maximum  The maximum representing the upper bound.
             */
            Bound ( TBound const & minimum
                  , TBound const & maximum )
            : minimum_(minimum)
            , maximum_(maximum)
            {
#ifdef PGT_EXCEPTION_HANDLING
                BoundMismatch::template Check<TBound>(minimum, maximum);
#endif
                USAGE_ASSERT ( minimum_ <= maximum_ );
            }
        ///@}

        ///@name Getter and Setter
        ///@{
#pragma mark GETTER_AND_SETTER

            /**
             * @brief      Getter of the minimum of the bound.
             *
             * @return     The minimum of the bound, i.e., lower bound.
             */
            inline TBound   Minimum () const
            {
                return minimum_;
            }

            /**
             * @brief      Setter of the minimum of the bound.
             *
             * @code{.cpp}
             *      someBound.Minimum() = 9;
             * @endcode
             *
             * @return     The minimum of the bound, i.e., lower bound.
             */
            inline TBound & Minimum ()
            {
                return minimum_;
            }

            /**
             * @brief      Getter of the maximum of the bound.
             *
             * @return     The maximum of the bound, i.e., upper bound.
             */
            inline TBound   Maximum() const
            {
                return maximum_;
            }

            /**
             * @brief      Setter of the maximum of the bound.
             *
             * @code{.cpp}
             *      someBound.Maximum() = 99;
             * @endcode
             *
             * @return     The maximum of the bound, i.e., upper bound.
             */
            inline TBound & Maximum()
            {
                return maximum_;
            }
        ///@}

        ///@name Modifier
        ///@{
#pragma mark MODIFIER

            /**
             * @brief      Set the range of the bound.
             *
             * @param[in]  minimum  The minimum of the bound, i.e., lower bound.
             * @param[in]  maximum  The maximum of the bound, i.e., upper bound.
             */
            inline void Range ( TBound const & minimum
                              , TBound const & maximum )
            {
#ifdef PGT_EXCEPTION_HANDLING
                BoundMismatch::template Check<TBound>(minimum, maximum);
#endif
                USAGE_ASSERT ( minimum <= maximum );
                minimum_ = minimum;
                maximum_ = maximum;

                USAGE_ASSERT ( minimum_ <= maximum_ );
            }
        ///@}

        ///@name Comparators
        ///@{
#pragma mark COMPARATORS

            /**
             * @brief      Comparison operator.
             *
             * @param[in]  rhs   The right hand side Bound.
             *
             * @code{.cpp}
             *      if ( Bound<int>(0,0) == Bound<int>(1,0) ) {  }
             * @endcode
             *
             * @return     @p True if both bounds are equal, @p False otherwise.
             */
            inline bool operator== ( Bound<TBound> const & rhs ) const
            {
                return ( this->Minimum() == rhs.Minimum() )
                    && ( this->Maximum() == rhs.Maximum() );
            }

            inline bool operator!= ( Bound<TBound> const & rhs ) const
            {
                return !(*this == rhs);
            }
        ///@}

    private:
        ///@name Members
        ///@{
#pragma mark MEMBERS

            TBound minimum_;    /**< The minimum of the bound representing the lower bound. */
            TBound maximum_;    /**< The maximum of the bound representing the upper bound. */
        ///@}
};

} // gpgt

#endif // EGOA__DATA_STRUCTURE__BOUND_HPP

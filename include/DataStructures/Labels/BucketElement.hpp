/*
 * BucketElement.hpp
 *
 *  Created on: Feb 04, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__LABELS__BUCKET_ELEMENT_HPP
#define EGOA__DATA_STRUCTURES__LABELS__BUCKET_ELEMENT_HPP

namespace egoa {

/**
 * @brief      Class representing the minimal bucket element.
 * @details    This is a wrapper that can be used to atomic elements to the
 *     bucket container. If you want to use more complex elements make sure
 *     the elements implement all comparison operators such as <, >, <=, >=,
 *     ==, and !=.
 *
 * @tparam     ElementType  Atomic or complex element implementing comparison
 *     operators.
 *     
 * @see        Label representing a label interface.
 * @see        Bucket representing a bucket.
 */
template<typename ElementType>
class BucketElement {
    public:
        // Type aliasing
        using TElement       = ElementType;
        using TBucketElement = BucketElement<TElement>;
    public:
        ///@name Constructors and destructor
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS

            BucketElement () 
            : BucketElement(TElement(),true)
            {}

            /**
             * @brief      Constructs the BucketElement object.
             *
             * @param[in]  value  The value.
             * @param[in]  valid  The information about the validity of this
             *      element.
             */
            BucketElement ( TElement    value
                          , bool        valid ) 
            : index_(Const::NONE)
            , valid_(valid)
            , value_(value)
            {}

            /**
             * @brief      Constructs the object.
             *
             * @param[in]  element  The element.
             */
            BucketElement( TElement element ) 
            : BucketElement( element, true )
            {}

            /**
             * @brief      Destroys the BucketElement object.
             */
            ~BucketElement() {}
        ///@}
        
        ///@name Domination Operators
        ///@{
#pragma mark DOMINATION_OPERATORS
            /**
             * @brief      Strict domination using less than.
             *
             * @param      rhs   The right hand side.
             *
             * @return     True if lhs < rhs, False otherwise.
             */
            inline bool operator<( BucketElement const & rhs ) const 
            {
                return value_ < rhs.value_;
            }

            /**
             * @brief      Weak domination using less or equal than.
             *
             * @param      rhs   The right hand side
             *
             * @return     True if lhs <= rhs, False otherwise.
             */
            inline bool operator<=( BucketElement const & rhs )  const 
            { 
                return !(*this > rhs); 
            }

            /**
             * @brief      Strict domination using greater than.
             *
             * @param      rhs   The right hand side.
             *
             * @return     True if lhs > rhs, False otherwise.
             */
            inline bool operator> ( BucketElement const & rhs )  const 
            { 
                return rhs < *this; 
            }

            /**
             * @brief      Weak domination using greater or equal than.
             *
             * @param      rhs   The right hand side.
             *
             * @return     True if lhs >= rhs, False otherwise.
             */
            inline bool operator>=( BucketElement const & rhs )  const 
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
             * @return     True if lhs == rhs, False otherwise.
             */
            inline bool operator==( BucketElement const & rhs ) const 
            {
                return value_ == rhs.value_;
            }

            /**
             * @brief      Inequality check.
             *
             * @param      rhs   The right hand side.
             *
             * @return     True if lhs != rhs, False otherwise.
             */
            inline bool operator!=( BucketElement const & rhs ) const 
            {
                return !(*this==rhs);
            }
        ///@}

        ///@name Concatenation Operators 
        ///@{
#pragma mark CONCATENATION_OPERATORS
            /**
             * @brief      In place addition.
             *
             * @param      rhs   The right hand side.
             *
             * @return     The BucketElement with added TElement.
             */
            inline BucketElement & operator+=( TElement const & rhs ) 
            {
                this->Value() += rhs.Value();
                return *this;
            }

            /**
             * @brief      Adding an element to the BucketElement.
             *
             * @param      rhs   The right hand side.
             *
             * @return     The BucketElement with added TElement.
             */
            inline BucketElement   operator+ ( TElement const & rhs ) const 
            {
                BucketElement temp ( *this );
                return temp += rhs;
            }
        ///@}

        ///@name Getter and Setter
        ///@{
#pragma mark GETTER_AND_SETTER

            /**
             * @brief      Getter for the identifier.
             * @details    This identifier represents the label's position,
             *     e.g., within the buckets processed elements.
             *
             * @return     The BucketElement's identifier.
             */
            inline Types::labelId    Index() const 
            { 
                return index_; 
            }

            /**
             * @brief      Setter for the identifier.
             * @details    This identifier is set while the element is moved
             *     to the processed elements in the bucket. Thus, the element
             *     will be fixed to this position.
             *
             * @code
             *      this->Index() = 9;
             * @endcode
             *
             * @return     The BucketElement's identifier.
             */
            inline Types::labelId  & Index()
            { 
                return index_; 
            }

            /**
             * @brief      Getter for the valid flag.
             *
             * @return     @p True if the BucketElement is valid, @p false otherwise.
             */
            inline bool   Valid() const 
            { 
                return valid_; 
            }

            /**
             * @brief      Setter for the valid flag.
             *
             * @code
             *      this->Valid() = false;
             * @endcode
             *
             * @return     @p True if the BucketElement is valid, @p false otherwise.
             */
            inline bool & Valid()
            { 
                return valid_; 
            }

            /**
             * @brief      Getter for the value of the BucketElement.
             *
             * @return     The value of the BucketElement.
             */
            inline TElement   Value() const 
            { 
                return value_; 
            }

            /**
             * @brief      Setter for the value of the BucketElement.
             *
             * @code
             *      this->Value() = TElement();
             * @endcode
             *
             * @return     The value of the BucketElement.
             */
            inline TElement & Value()
            { 
                return value_; 
            }
        ///@}

#pragma mark OUTPUT
        /**
         * @brief      Output stream.
         *
         * @param      os    The output stream such as std::cout.
         * @param      rhs   The right hand side BucketElement.
         *
         * @return     The output stream.
         */
        friend std::ostream & operator<< ( std::ostream         & os
                                         , BucketElement const  & rhs ) 
        {
            return os << "(" << rhs.Value() << "," << rhs.Valid() << ")";
        }

#pragma mark MEMBERS
    private:
        Types::index    index_;     /**< The BucketElement identifier. */
        bool            valid_;     /**< The valid flag that is @p true if the bucket element is valid, @p false otherwise. */
        TElement        value_;     /**< The value of the BucketElement. */
};

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__LABELS__BUCKET_ELEMENT_HPP

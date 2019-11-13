/*
 * Bucket.hpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__CONTAINER__QUEUES__BUCKET_HPP
#define EGOA__DATA_STRUCTURES__CONTAINER__QUEUES__BUCKET_HPP

#include "Auxiliary/ExecutionPolicy.hpp"

#include "Exceptions/PgtExceptions.hpp"
#include "Exceptions/Assertions.hpp"

#include "DataStructures/Container/DominationCriterion.hpp"

#include "DataStructures/Container/Queues/PriorityQueue.hpp"
#include "DataStructures/Container/Queues/BinaryHeap.hpp"

#include "DataStructures/Labels/VoltageAngleDifferenceLabel.hpp"

namespace egoa {

namespace internal {
/**
 * @brief      Class for bucket loop differentiation.
 *
 * @tparam     BucketType  Type of the bucket.
 * @tparam     Policy      The execution policy.
 */
template<typename BucketType, ExecutionPolicy Policy>
class BucketLoopDifferentiation;
} // namespace internal

/**
 * @brief      Class for bucket data structure.
 * 
 * @code{.cpp}
 *      egoa::Bucket<egoa::BinaryHeap<int>, int> bucket;
 * @endcode
 *
 * @tparam     PriorityQueue  Type of the priority queue used within the
 *     bucket, e.g., BinaryHeap. The PriorityQueue has to provide the
 *     following interface.
 *     
 *     Function                      | Description
 *     ------------------------------|---------------------
 *     Top                           | Returns the top element.
 *     Search                        | Search for the first match.
 *     Insert, operator+=, Emplace   | Inserts one or more elements.
 *     BuildWith                     | Builds a heap.
 *     DeleteTop, Pop                | Deletes the top element.
 *     Clear                         | Clears the heap.
 *     ChangeKey                     | Changes the key of one element.
 *     DecreaseKey                   | Decreases the key of an element.
 *     Empty, Size                   | Capacity operations.
 *     Comparator, Maximize, Minimize| Comparators.
 *     operator==, operator!=,       | Equality operators.
 *     IsEqualTo                     |
 *     swap                          | Swap two heaps.
 *     operator<<                    | Writes the heap into an output stream.
 */
template< typename PriorityQueue = BinaryHeap<VoltageAngleDifferenceLabel<Edges::Edge<Edges::ElectricalProperties> > > >
class Bucket {
    public:
        // Type aliasing
        using TPriorityQueue = PriorityQueue;
        using TElement       = typename TPriorityQueue::TElement;
        using TBucket        = Bucket< TPriorityQueue >;
        using TIterator      = std::iterator< std::input_iterator_tag
                                            , TElement
                                            , Types::largeNumber
                                            , Types::largeNumber const *
                                            , Types::largeNumber>;
    public:
        ///@name Constructors and Destructor
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS

            /**
             * @brief      Constructs the object.
             */
            Bucket ()
            : processedElements_()
            , unprocessedElements_()
            , numberOfValidUnprocessedElements_(0)
            {
                Comparator( std::less<TElement>() );
            }
        ///@}
        
        /**
         * @name      Comparators for Unprocessed Bucket Elements
         * 
         * @param      rhs   The right hand side bucket.
         * 
         * @pre        Neither of the bucket queues is allowed to be empty.
         *     Check status of the queue by using #EmptyQueue().
         *     
         * @return     @p true if the element with an optimal key is <, >, <=, >= than
         *     the rhs bucket, @p false otherwise.
         *     
         * @see        EmptyQueue()
         */
        ///@{
#pragma mark OPERATORS

            inline bool operator< ( TBucket const & rhs ) const 
            {
                USAGE_ASSERT ( !EmptyQueue()     );
                USAGE_ASSERT ( !rhs.EmptyQueue() );
                return ( Top() < rhs.Top() );
            }

            inline bool operator>  ( TBucket const & rhs ) const 
            {
                USAGE_ASSERT ( !EmptyQueue()     );
                USAGE_ASSERT ( !rhs.EmptyQueue() );
                return rhs < *this;
            }

            inline bool operator<= ( TBucket const & rhs ) const 
            {
                USAGE_ASSERT ( !EmptyQueue()     );
                USAGE_ASSERT ( !rhs.EmptyQueue() );
                return !(*this > rhs);
            }

            inline bool operator>= ( TBucket const & rhs ) const 
            {
                USAGE_ASSERT ( !EmptyQueue()     );
                USAGE_ASSERT ( !rhs.EmptyQueue() );
                return !(*this < rhs);
            }
        ///@}

        /**
         * @name       Merge an Element into the Bucket
         * @details    Note that the valid flag for the processed labels might
         *     change in some special cases. However, this flag is ignored for
         *     processed labels.
         *
         * @param      newElement  The new element to merge into the bucket.
         *
         * @pre        Note that the element will be moved if the return type is true.
         *
         * @tparam     Domination  The domination sense such as weak, strict, or none.
         * 
         * @return     @p true if the @p newElement is added into the bucket,
         *     @p false otherwise (meaning it was dominated in some sense defined
         *     by @p Domination).
         */
        ///@{
#pragma mark MERGE_ELEMENTS
            
            template<DominationCriterion Domination = DominationCriterion::weak>
            inline bool Merge ( TElement && newElement ) 
            {
                newElement.Valid() = true;
                for_all_elements<ExecutionPolicy::breakable>(
                    [&](TElement & element) -> bool 
                    {
                        if ( internal::DominationDifferentiation<TElement, Domination>
                            ::Dominates( element, newElement, Comparator() ) ) {
                            newElement.Valid() = false;
                            return false; // break loop
                        } else if ( internal::DominationDifferentiation<TElement, Domination>
                            ::Dominates( newElement, element, Comparator() ) ) {
                            // Note that this can only be a label from the unprocessed range
                            element.Valid() = false;
                            --numberOfValidUnprocessedElements_;
                        }
                        // also covers DominationCriterion::none
                        return true; 
                    }
                );

                if ( !newElement.Valid() ) 
                {
                    PopInvalidUnprocessedElements();
                    return false;
                }

                // Add new element to the bucket
                Insert( std::move(newElement) );
                ++numberOfValidUnprocessedElements_;
                PopInvalidUnprocessedElements();
                return true;
            }

            template<DominationCriterion Domination = DominationCriterion::weak>
            inline bool Merge ( TElement & newElement ) 
            {
                bool valid = Merge<Domination>( TElement(newElement) );
                newElement.Valid() = valid;
                return valid;
            }

            template<DominationCriterion Domination = DominationCriterion::weak>
            inline bool Merge( TElement const & newElement ) 
            {
                return Merge<Domination>( TElement(newElement) );
            }
        ///@}

        ///@todo Think about it
        inline bool HasElement ( TElement const & newElement
                               , TElement       & existingElement ) 
        {
            bool hasElement = false;
            for_all_elements<ExecutionPolicy::breakable>( 
                [ & newElement
                , & existingElement
                , & hasElement](TElement & element) -> bool 
                {
                    if ( newElement == element ) 
                    {
                        existingElement = element;
                        hasElement = true;
                        return false;
                    }
                    return true;
                }
            );
            return hasElement;
        }

        ///@name Element Accessors
        ///@{
#pragma mark ELEMENT_ACCESS

            /**
             * @brief      Determines if it has a processed element at
             *     position @a index.
             *
             * @param[in]  index  The position of an element
             *
             * @return     @p true if it has an element at that position, @p
             *     false otherwise.
             */
            inline bool HasElementAt ( Types::index index ) 
            {
                USAGE_ASSERT ( index >= 0 );
                return ( index < NumberOfProcessedElements() );
            }

            /**
             * @brief      Processed element at a certain position @a index.
             *
             * @param[in]  index  The position of a processed element.
             * 
             * @pre        There are processed elements and #HasElementAt( index )
             *     is true.
             *
             * @return     The processed element at the position @a index.
             */
            inline TElement & ElementAt ( Types::index index ) 
            {
#ifdef PGT_EXCEPTION_HANDLING
                throw_out_of_bound( index, NumberOfProcessedElements() );
#endif
                USAGE_ASSERT ( HasElementAt(index) );
                return processedElements_.at( index );
            }

            /**
             * @brief      Processed element at a certain position @a index.
             *
             * @param[in]  index  The position of a processed element.
             * 
             * @pre        There are processed elements and #HasElementAt( index )
             *     is true.
             *
             * @return     The processed element at the position @a index.
             */
            inline TElement & operator[] ( Types::index index ) 
            {
#ifdef PGT_EXCEPTION_HANDLING
                throw_out_of_bound( index, NumberOfProcessedElements() );
#endif
                USAGE_ASSERT ( HasElementAt(index) );
                return processedElements_.at(index);
            }

            /**
             * @brief      Processed element at a certain position @a index.
             *
             * @param[in]  index  The position of a processed element.
             * 
             * @pre        There are processed elements and #HasElementAt( index )
             *     is true.
             *
             * @return     The processed element at the position @a index.
             */
            inline TElement & operator[] ( Types::index index ) const 
            {
#ifdef PGT_EXCEPTION_HANDLING
                throw_out_of_bound( index, NumberOfProcessedElements() );
#endif
                USAGE_ASSERT ( HasElementAt(index) );
                return processedElements_.at( index );
            }

            /**
             * @brief      Returns the first valid and unprocessed element.
             * @details    Top returns an unprocessed element that has an optimal
             *     key (e.g. for VoltageAngleDifferenceLabel the key would be the
             *     susceptance norm).
             *     
             * @pre        The queue is not empty meaning #EmptyQueue() is false.
             *
             * @return     The element with an optimal key.
             */
            inline TElement const & Top () const 
            {
                USAGE_ASSERT ( !EmptyQueue() );
                ESSENTIAL_ASSERT( unprocessedElements_.Top().Valid() );
                return unprocessedElements_.Top();
            }

            /**
             * @brief      All elements with an optimum value.
             * @details    Get all elements that have an optimum value, e.g. for the
             *     VoltageAngleDifferenceLabel an optimum corresponds to the minimum
             *     delta theta value of the path.
             *     
             * @note       This function does not change the bucket. All elements
             *     stay in the queue. The equality check depends on the element
             *     equality check.
             *     
             * @todo       Is this loop sufficient for unprocessed labels only?
             *
             * @return     Vector of elements with optimum value
             */
            inline std::vector<TElement> Optima () const 
            {   //@todo This is a very bad implementation. Think about it again.
                auto result  = std::min_element( processedElements_.begin(), processedElements_.end(), [](TElement a, TElement b) { return a.Value() < b.Value(); } );
                auto result2 = std::min_element( unprocessedElements_.begin(), unprocessedElements_.end(), [](TElement a, TElement b) { return a.Value() < b.Value(); } );
                TElement minElement;
                if ( result != processedElements_.end() )
                {
                    if ( result2 != unprocessedElements_.end() ) 
                    {
                        ((*result)<(*result2))?(minElement = *result):(minElement = *result2);
                    } else {
                        minElement = *result;
                    }
                } else if ( result2 != unprocessedElements_.end() ) {
                    minElement = *result2;
                }

                // Extract elements with the same optimum value
                std::vector<TElement> optima;
                for_all_elements<ExecutionPolicy::sequential> ( 
                    [ & minElement
                    , & optima ]( TElement const & element )
                    {
                        if ( element.Value() == minElement.Value() ) 
                        { 
                            optima.emplace_back( element );
                        }
                    }
                );
                return optima;
            }
        ///@}

        ///@name Modifiers
        ///@{
#pragma mark MODIFIERS
            /**
             * @brief      Pop the first valid element.
             * @details    Returns the first unprocessed valid label and removes
             *     it from the set of unprocessed labels. The first unprocessed
             *     label is the one with the smallest key (e.g. for
             *     VoltageAngleDifferenceLabel the key would be the susceptance
             *     norm).
             *
             * @pre        The queue---meaning the unprocessed items---is not
             *     allowed to be empty.
             *     
             * @return     The element with a optimal key.
             */
            inline Types::index Pop () 
            {
                USAGE_ASSERT ( !EmptyQueue() );

                TElement element = unprocessedElements_.DeleteTop();
                --numberOfValidUnprocessedElements_;
                ESSENTIAL_ASSERT( element.Valid() );
                PopInvalidUnprocessedElements();

                return MoveToProcessed ( std::move(element) );
            }

            /**
             * @brief      Delete and return the first valid element
             * @details    Returns the first unprocessed valid label and removes
             *     it from the set of unprocessed labels. The first unprocessed
             *     label is the one with the smallest key (e.g. for
             *     VoltageAngleDifferenceLabel the key would be the susceptance
             *     norm times the minimum capacity).
             *     
             * @pre        The queue---meaning the unprocessed items---is not
             *     allowed to be empty.
             *
             * @return     The element with a optimal key.
             */
            inline std::pair<TElement, Types::index> DeleteTop () 
            {
                USAGE_ASSERT ( !EmptyQueue() );
                Types::index index = Pop();
                return std::make_pair( processedElements_.back(), index );
            }
        ///@}


#pragma mark CAPACITY
        /**
         * @brief      Clear the bucket.
         */
        inline void Clear () noexcept 
        {
            processedElements_.clear();
            unprocessedElements_.Clear();
            numberOfValidUnprocessedElements_ = 0;
        }

        /**
         * @name      Comparator Accessors.
         *
         * @code{.cpp}
         *      ...
         *      bucket_.Comparator( []( int a, int b ) { return a < b; } );
         *      ...
         * @endcode
         *
         * @pre        If the comparator is changed to a non standard
         *     comparator you have to make sure that the elements comply
         *     these conditions, e.g., changing the comparator to "<"
         *     implicitly requires that no duplicates are allowed.
         *
         * @return     Comparator function pointer.
         */
        ///@{
#pragma mark COMPARATOR

            inline std::function<bool ( TElement const &
                                      , TElement const & ) > 
            const & Comparator () const 
            { 
                return unprocessedElements_.Comparator(); 
            }

            inline void Comparator( std::function<bool  ( TElement const &
                                                        , TElement const & )> comparator ) 
            { 
                unprocessedElements_.Comparator ( comparator ); 
            }
        ///@}

#pragma mark OTHERS
        /**
         * @brief      Determines if the bucket is empty.
         *
         * @return     @p true if empty, @p false otherwise.
         */
        inline bool Empty () const 
        {
            return ( processedElements_.empty() && unprocessedElements_.Empty() );
        }

        /**
         * @brief      Determines if there are no unprocessed elements in the bucket.
         *
         * @return     @p true if empty, @p false otherwise.
         */
        inline bool EmptyQueue () const 
        {
            return unprocessedElements_.Empty();
        }

        inline Types::count Size () const 
        {
            return NumberOfProcessedElements() + NumberOfUnprocessedElements();
        }

        ///@name Element Loops
        ///@{
#pragma mark LOOPS
        
            /**
             * @brief      The @c for loop @c over all elements in the bucket.
             * @details    Loop over all processed and unprocessed elements.
             *
             * @param[in]  function    The function, e.g., lambda function.
             *
             * @code{.cpp}
             *      []( TElement & element ) 
             *      { 
             *          // Do something with the element object. 
             *      }
             * @endcode
             * 
             * @tparam     Policy      @p true if the loop is run in parallel using
             *     OpenMP, @p false otherwise.
             * @tparam     FUNCTION    The function pointer.
             */
            template<ExecutionPolicy Policy, typename FUNCTION>
            inline
            void for_all_elements ( FUNCTION function ) 
            {
                internal::BucketLoopDifferentiation<Bucket, Policy>
                    ::for_all_elements ( *this, function );
                PopInvalidUnprocessedElements();
            }

            /**
             * @brief      The @c for loop @c over all elements in the bucket
             *     with @p const access.
             * @details    Loop over all processed and unprocessed elements.
             *
             * @param[in]  function    The function, e.g., lambda function.
             *
             * @code{.cpp}
             *      []( TElement const & element ) 
             *      { 
             *          // Do something with the element object. 
             *      }
             * @endcode
             *
             * @tparam     Policy  @p true if the loop is run in parallel using
             *     OpenMP, @p false otherwise.
             * @tparam     FUNCTION    The function pointer.
             */
            template<ExecutionPolicy Policy, typename FUNCTION>
            inline 
            void for_all_elements ( FUNCTION function ) const 
            {
                internal::BucketLoopDifferentiation<Bucket const, Policy>
                    ::for_all_elements ( *this, function );
            }

            /**
             * @brief      The @c for loop @c over all @p processed elements in the bucket.
             *
             * @param[in]  function    The function, e.g., lambda function
             *
             * @code{.cpp}
             *      []( TElement & element ) 
             *      { 
             *          // Do something with the element object. 
             *      }
             * @endcode
             *
             * @tparam     Policy  @p true if the loop is run in parallel using
             *     OpenMP, @p false otherwise.
             * @tparam     FUNCTION    The function pointer.
             */
            template<ExecutionPolicy Policy, typename FUNCTION>
            inline 
            void for_all_processed_elements ( FUNCTION function ) 
            {
                internal::BucketLoopDifferentiation<Bucket, Policy>
                    ::for_all_processed_elements ( *this, function );
            }

            /**
             * @brief      The @c for loop @c over all @p processed elements in the bucket.
             *
             * @param[in]  function    The function, e.g., lambda function
             *
             * @code{.cpp}
             *      []( TElement const & element ) 
             *      { 
             *          Do something with the element object. 
             *      }
             * @endcode
             *
             * @tparam     Policy  @p true if the loop is run in parallel using
             *     OpenMP, @p false otherwise.
             * @tparam     FUNCTION    The function pointer.
             */
            template<ExecutionPolicy Policy, typename FUNCTION>
            inline
            void for_all_processed_elements ( FUNCTION function ) const 
            {
                internal::BucketLoopDifferentiation<Bucket const, Policy>
                    ::for_all_processed_elements ( *this, function );
            }

            /**
             * @brief      The @c for loop @c over all @p unprocessed elements in
             *     the bucket.
             * @details    If the @p function returns @p true the loop will be
             *     continued, if @p false this emulates a break.
             *
             * @param[in]  function    The function, e.g., lambda function.
             *
             * @code{.cpp}
             *      []( TElement & element ) 
             *      { 
             *          // Do something with the element object. 
             *      }
             * @endcode
             * 
             * @tparam     Policy  @p true if the loop is run in parallel using
             *     OpenMP, @p false otherwise.
             * @tparam     FUNCTION    The function pointer.
             */
            template<ExecutionPolicy Policy, typename FUNCTION>
            inline
            void for_all_unprocessed_elements ( FUNCTION function ) 
            {
                internal::BucketLoopDifferentiation<Bucket, Policy>
                    ::for_all_unprocessed_elements ( *this, function );
                PopInvalidUnprocessedElements();
            }

            /**
             * @brief      The @c for loop @c over all @p unprocessed elements in
             *     the bucket.
             * @details    If the @p function returns @p true the loop will be
             *     continued, if @p false this emulates a break.
             *
             * @param[in]  function    The function, e.g., lambda function.
             *
             * @code{.cpp}
             *      []( TElement const & element ) 
             *      { 
             *          // Do something with the element object. 
             *      }
             * @endcode
             * 
             * @tparam     Policy  @p true if the loop is run in parallel using
             *     OpenMP, @p false otherwise.
             * @tparam     FUNCTION    The function pointer.
             */
            template<ExecutionPolicy Policy, typename FUNCTION>
            inline
            void for_all_unprocessed_elements ( FUNCTION function ) const 
            {
                internal::BucketLoopDifferentiation<Bucket const, Policy>
                    ::for_all_unprocessed_elements ( *this, function );
            }

            /**
             * @brief      The @c for loop @c over all @p elements with optimal value.
             * @details    Loop over all unprocessed elements having an optimal value.
             *
             * @param[in]  function    The function, e.g., lambda function.
             *
             * @code{.cpp}
             *      []( TElement & element ) 
             *      { 
             *          // Do something with the element object. 
             *      }
             * @endcode
             * 
             * @tparam     Policy      @p true if the loop is run in parallel
             *     using OpenMP, @p false otherwise.
             * @tparam     FUNCTION    The function pointer.
             */
            template<ExecutionPolicy Policy, typename FUNCTION>
            inline
            Types::real for_all_optima ( FUNCTION function ) 
            {
                return internal::BucketLoopDifferentiation<Bucket, Policy>
                    ::for_all_optima ( *this, function );
            }

            /**
             * @brief      The @c for loop @c over all @p elements with optimal
             *     value with @p const access.
             * @details    Loop over all unprocessed elements having an optimal value.
             *
             * @param[in]  function    The function, e.g., lambda function
             *
             * @code{.cpp}
             *      []( TElement const & element ) 
             *      { 
             *          // Do something with the element object. 
             *      }
             * @endcode
             * 
             * @tparam     Policy      @p true if the loop is run in parallel
             *     using OpenMP, @p false otherwise.
             * @tparam     FUNCTION    The function pointer.
             */
            template<ExecutionPolicy Policy, typename FUNCTION>
            inline
            Types::real for_all_optima ( FUNCTION function ) const 
            {
                return internal::BucketLoopDifferentiation<Bucket const, Policy>
                    ::for_all_optima ( *this, function );
            }
        ///@}

    private: 
        ///@name Add an Element
        ///@{
#pragma mark ADD_ELEMENTS

            /**
             * @brief      Move element to processed elements.
             * @details    After moving it to the list of processed elements its
             *     identifier corresponds to the index.
             *
             * @param      element  The element to move to unprocessed elements.
             *
             * @pre        Function @see Pop().
             */
            inline Types::index MoveToProcessed ( TElement && element ) 
            {
               processedElements_.push_back ( std::move(element) );
               processedElements_.back().Index() = processedElements_.size() - 1;
               return processedElements_.back().Index();
            }

            /**
             * @brief      Insert an element 
             *
             * @param      element  The element.
             */
            inline void Insert ( TElement && element ) {
                ESSENTIAL_ASSERT( element.Valid() );
                unprocessedElements_.Insert ( std::move(element) );
            }
        ///@}

        ///@name Number of Elements
        ///@{
#pragma mark NUMBER_OF_ELEMENTS
            /**
             * @brief      Number of processed elements.
             *
             * @return     The number of processed elements.
             */
            inline Types::count NumberOfProcessedElements() const noexcept 
            { 
                return   processedElements_.size(); 
            }

            /**
             * @brief      Number of valid unprocessed elements.
             *
             * @return     The number of valid unprocessed elements.
             */
            inline Types::count NumberOfUnprocessedElements() const noexcept
            {
                return numberOfValidUnprocessedElements_;
            }
        ///@}

        ///@name Domination
        ///@{
#pragma mark DOMINATION
            /**
             * @brief      Checks if @p lhs dominates @p rhs in a certain sense.
             *
             * @param      lhs         The left hand side element.
             * @param      rhs         The right hand side element.
             *
             * @tparam     Domination  The domination sense such as weak, strict, or none.
             *
             * @return     @p true if the @p lhs dominates the @p rhs, @p false otherwise.
             */
            template<DominationCriterion Domination>
            inline bool Dominates ( TElement const & lhs, TElement const & rhs ) const 
            {
                return internal::DominationDifferentiation<TElement, Domination>
                    ::Dominates( lhs, rhs, Comparator() );
            }
        ///@}

        /// @name Ensuring Invariants
        /// @{
#pragma mark INVARIANTS

            /**
             * @brief      Pops invalid unprocessed elements until @p unprocessedElements_
             *             is empty or the top element is valid.
             */
            inline void PopInvalidUnprocessedElements() 
            {
                while (!unprocessedElements_.Empty() 
                    && !unprocessedElements_.Top().Valid()) 
                {
                    unprocessedElements_.Pop();
                }
            }
        /// @}

#pragma mark FRIENDS
        friend internal::BucketLoopDifferentiation<Bucket, ExecutionPolicy::sequential>;
        friend internal::BucketLoopDifferentiation<Bucket, ExecutionPolicy::breakable>;
        friend internal::BucketLoopDifferentiation<Bucket, ExecutionPolicy::parallel>;
        friend internal::BucketLoopDifferentiation<Bucket const, ExecutionPolicy::sequential>;
        friend internal::BucketLoopDifferentiation<Bucket const, ExecutionPolicy::breakable>;
        friend internal::BucketLoopDifferentiation<Bucket const, ExecutionPolicy::parallel>;

#pragma mark MEMBERS
        std::vector<TElement>                     processedElements_;   /**< The processed elements that do not change their status and stay valid */ 
        TPriorityQueue                          unprocessedElements_;   /**< The unprocessed elements that might change their status, e.g., to invalid */
        Types::count               numberOfValidUnprocessedElements_;   /**< The number of valid unprocessed elements. */
};

namespace internal {

#pragma mark SEQUENTIAL_LOOPS

template<typename BucketType>
class BucketLoopDifferentiation<BucketType, ExecutionPolicy::sequential> {

    // Type aliasing
    using TBucket  = BucketType;
    using TElement = typename TBucket::TElement;

    public:
        /**
         * @brief      The @c for loop @c over all elements in the bucket.
         * @details    Loop over all processed and unprocessed elements.
         *
         * @param[in]  function    The function, e.g., lambda function
         *
         * @code{.cpp}
         *      []( TElement & element ) 
         *      { 
         *          // Do something with the element object. 
         *      }
         * @endcode
         * 
         * @tparam     FUNCTION    The function pointer.
         */
        template<typename FUNCTION>
        inline static
        void for_all_elements ( BucketType & bucket
                              , FUNCTION     function )
        {
            for_all_processed_elements   ( bucket, function );
            for_all_unprocessed_elements ( bucket, function );
        }

        /**
         * @brief      The @c for loop @c over all @p processed elements in the bucket.
         *
         * @param[in]  function    The function, e.g., lambda function.
         *
         * @code{.cpp}
         *      []( TElement & element ) 
         *      { 
         *          // Do something with the element object. 
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function pointer.
         */
        template<typename FUNCTION>
        inline static
        void for_all_processed_elements ( BucketType & bucket
                                        , FUNCTION     function )
        {
            for ( auto & element : bucket.processedElements_ ) 
            {
                function ( element );
            }
        }

        /**
         * @brief      The @c for loop @c over all @p unprocessed elements in the bucket.
         *
         * @param[in]  function    The function, e.g., lambda function
         *
         * @code{.cpp}
         *      []( TElement & element ) 
         *      { 
         *          // Do something with the element object. 
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function pointer.
         */
        template<typename FUNCTION>
        inline static
        void for_all_unprocessed_elements ( BucketType & bucket
                                          , FUNCTION     function )
        {
            bucket.unprocessedElements_.template for_all_elements<ExecutionPolicy::sequential>(
                [&function]( auto & element ) 
                {
                    if (!element.Valid()) return;
                    function(element);
                }
            );
        }


        /**
         * @brief      The @c for loop @c over all @p elements with optimal value.
         * @details    Loop over all unprocessed elements having an optimal value.
         *
         * @param[in]  function    The function, e.g., lambda function
         *
         * @code{.cpp}
         *      []( TElement & element ) 
         *      { 
         *          // Do something with the element object. 
         *      }
         * @endcode
         * 
         * @tparam     Policy      @p true if the loop is run in parallel
         *     using OpenMP, @p false otherwise.
         * @tparam     FUNCTION    The function pointer.
         */
        template<typename FUNCTION>
        static inline 
        Types::real for_all_optima ( BucketType & bucket
                                   , FUNCTION     function )
        {
            std::vector<TElement> optima = bucket.Optima();
            for ( TElement const & element : optima ) 
            {
                function ( element );
            }
            if ( !optima.empty() )
                return optima[0].Value();
            else
                return Const::REAL_INFTY;
        }
};

#pragma mark BREAKABLE_LOOPS
template<typename BucketType>
class BucketLoopDifferentiation<BucketType, ExecutionPolicy::breakable> {
    using TElement = typename BucketType::TElement;
    public:

        template<typename FUNCTION>
        static inline 
        void for_all_elements ( BucketType & bucket
                              , FUNCTION     function )
        {
            for ( auto & element : bucket.processedElements_ ) 
            {
                bool toContinue = function( element );
                if (!toContinue) return;
            }

            for_all_unprocessed_elements(bucket, function);
        }

        /**
         * @brief      The @c for loop @c over all @p processed elements in the bucket.
         *
         * @param[in]  function    The function, e.g., lambda function that
         *      return a boolean. If the boolean is @p true the loop will be
         *      continued, if @p false this emulates a break.
         *
         * @code{.cpp}
         *      []( TElement & element ) -> bool 
         *      { 
         *          // Do something with the element object. 
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function pointer.
         */
        template<typename FUNCTION>
        static inline 
        void for_all_processed_elements ( BucketType & bucket
                                        , FUNCTION     function )
        {
            bool toContinue = true;
            for ( auto & element : bucket.processedElements_ ) 
            {
                toContinue = function ( element );
                if ( !toContinue ) break;
            }
        }

        /**
         * @brief      The @c for loop @c over all @p unprocessed elements in the bucket.
         *
         * @param[in]  function    The function, e.g., lambda function that
         *      return a boolean. If the boolean is @p true the loop will be
         *      continued, if @p false this emulates a break.
         *
         * @code{.cpp}
         *      []( TElement & element ) -> bool 
         *      { 
         *          // Do something with the element object. 
         *      }
         * @endcode
         * 
         * @tparam     FUNCTION    The function pointer.
         */
        template<typename FUNCTION>
        static inline 
        void for_all_unprocessed_elements ( BucketType & bucket
                                          , FUNCTION     function )
        {
            bucket.unprocessedElements_.template for_all_elements<ExecutionPolicy::breakable>(
                [&function](auto & element) -> bool 
                {
                    if (!element.Valid()) return true;
                    return function(element);
                }
            );
        }

        template<typename FUNCTION>
        static inline 
        Types::real for_all_optima ( BucketType & bucket
                                   , FUNCTION     function )
        {
            std::vector<TElement> optima = bucket.Optima();
            for ( TElement const & element : optima ) 
            {
                bool toContinue = function ( element );
                if (!toContinue) break;
            }
            if ( !optima.empty() )
                return optima[0].Value();
            else
                return Const::REAL_INFTY;
        }
};

#pragma mark PARALLEL_LOOPS

#ifdef OPENMP_AVAILABLE


template<typename BucketType>
class BucketLoopDifferentiation<BucketType, ExecutionPolicy::parallel> {

    // Type aliasing
    using TBucket  = BucketType;
    using TElement = typename TBucket::TElement;

    public:
        /**
         * @brief      The @c for loop @c over all elements in the bucket.
         * @details    Loop over all processed and unprocessed elements.
         *
         * @param[in]  function    The function, e.g., lambda function
         *
         * @code{.cpp}
         *      []( TElement & element ) 
         *      { 
         *          // Do something with the element object. 
         *      }
         * @endcode
         * 
         * @tparam     FUNCTION    The function pointer.
         */
        template<typename FUNCTION>
        static inline 
        void for_all_elements ( BucketType & bucket
                              , FUNCTION     function )
        {
            for_all_processed_elements   ( bucket, function );
            for_all_unprocessed_elements ( bucket, function );
        }

        /**
         * @brief      The @c for loop @c over all @p processed elements in the bucket.
         *
         * @param[in]  function    The function, e.g., lambda function
         *
         * @code{.cpp}
         *      []( TElement & element ) 
         *      { 
         *          // Do something with the element object. 
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function pointer.
         */
        template<typename FUNCTION>
        static inline 
        void for_all_processed_elements ( BucketType & bucket
                                        , FUNCTION     function )
        {
            #pragma omp parallel for
                for ( Types::count counter = 0
                    ; counter < bucket.processedElements_.size()
                    ; ++counter )
                {
                    function( bucket.processedElements_[counter] );
                }
        }

        /**
         * @brief      The @c for loop @c over all @p unprocessed elements in the bucket.
         *
         * @param[in]  function    The function, e.g., lambda function
         *
         * @code{.cpp}
         *      []( TElement & element ) 
         *      { 
         *          // Do something with the element object. 
         *      }
         * @endcode
         * 
         * @tparam     FUNCTION    The function pointer.
         */
        template<typename FUNCTION>
        static inline 
        void for_all_unprocessed_elements ( BucketType & bucket
                                          , FUNCTION     function )
        {
            bucket.unprocessedElements_.template for_all_elements<ExecutionPolicy::parallel>(
                [&function](auto & element) 
                {
                    if (!element.Valid()) return;
                    function(element);
                }
            );
        }

        /**
         * @brief      The @c for loop @c over all @p elements with optimal value.
         * @details    Loop over all unprocessed elements having an optimal value.
         *
         * @param[in]  function    The function, e.g., lambda function
         *
         * @code{.cpp}
         *      []( TElement & element ) 
         *      { 
         *          // Do something with the element object. 
         *      }
         * @endcode
         * 
         * @tparam     Policy      @p true if the loop is run in parallel
         *     using OpenMP, @p false otherwise.
         * @tparam     FUNCTION    The function pointer.
         */
        template<typename FUNCTION>
        static inline 
        Types::real for_all_optima ( BucketType & bucket
                                   , FUNCTION     function )
        {
            std::vector<TElement> optima = bucket.Optima();
            #pragma omp parallel for
                for ( Types::count counter = 0
                    ; counter < optima.size()
                    ; ++counter )
                {
                    function( optima[counter] );
                }

            if ( !optima.empty() )
                return optima[0].Value();
            else
                return Const::REAL_INFTY;
        }
};

#else // OPENMP_AVAILABLE
/**
 * @brief      If OpenMP is not available, fall back to sequential execution of the loops.
 *
 * @tparam     BucketType  The type of the bucket.
 */
template<typename BucketType>
class BucketLoopDifferentiation<BucketType, ExecutionPolicy::parallel>
    : public BucketLoopDifferentiation<BucketType, ExecutionPolicy::sequential> {};

#endif // OPENMP_AVAILABLE

} // namespace internal

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__CONTAINER__QUEUES__BUCKET_HPP

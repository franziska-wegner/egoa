/*
 * BinaryHeap.hpp
 *
 *  Created on: Nov 25, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__CONTAINER__BINARY_HEAP_HPP
#define EGOA__DATA_STRUCTURES__CONTAINER__BINARY_HEAP_HPP

#include "Auxiliary/Auxiliary.hpp"
#include "Auxiliary/ExecutionPolicy.hpp"
#include "Exceptions/Assertions.hpp"

#include <iomanip>
#include <iterator>

namespace egoa {

namespace internal {
/**
 * @brief      Class for binary heap check.
 * @details    If inOrder is TRUE the heaps are checked for structural
 *     equality (meaning that they are identical), otherwise it checks if both
 *     heaps have the same elements.
 *
 * @code{.cpp}
 *      if ( BinaryHeapCheck<TElement, true>::IsEqualTo(lhs, rhs) ) {
 *          std::cout << "Both heaps are (structurally) identical" << std::endl;
 *      } else if ( BinaryHeapCheck<TElement, false>::IsEqualTo(lhs, rhs) ) {
 *          std::cout << "Both heaps have the same elements, but differ in the structure" << std::endl;
 *      } else {
 *          std::cout << "Both heaps are different." << std::endl;
 *      }
 * @endcode
 *
 * @tparam     Type     Type of the elements contained by the heap.
 * @tparam     inOrder  TRUE checks if identical (order-wise), FALSE checks
 *     for same elements.
 */
template<typename Type, bool inOrder>
class BinaryHeapCheck;

/**
 * @brief      The @p for loops for BinaryHeap.
 * @details    The usage of templates is faster instead of ordinary function
 *     pointers such as std::function ( see
 *     https://stackoverflow.com/questions/14677997/stdfunction-vs-template
 *     for more information). This is the reason why the following code is not
 *     used 
 *     inline void for_all_<SOME_FUNCTION>(std::function<void(TVertex & vertex)> function) {}
 *
 * @tparam     HeapType     The type of the heap. If the heap type is const, const
 *                          references to the elements are passed to the function objects.
 * @tparam     Policy       The execution policy.
 *
 * @see        BinaryHeap
 */
template<typename HeapType, ExecutionPolicy Policy>
class BinaryHeapLoopDifferentiation;
} // namespace internal

/**
 * @brief      Class for binary heap data structure.
 * @details    The methods have the following worst case time complexities:
 *     Function                      | Time Complexity
 *     ------------------------------|---------------------
 *     Top                           | @f$\Theta(1)@f$
 *     Insertion (Emplace, Push)     | @f$\Theta(\log n)@f$
 *     MakeHeap                      | @f$\Theta(1)@f$
 *     DeleteTop, Pop                | @f$\Theta(\log n)@f$
 *     Delete                        | @f$\Theta(\log n)@f$
 *     ChangeKey                     | @f$\Theta(\log n)@f$
 *     Union (not implemented yet)   | @f$\Theta(n)@f$
 *
 *     The comparator must implement a strict total order on the elements,
 *     e.g., @p std::less<TElement>.
 *
 * @code{.cpp}
 *      BinaryHeap<int> heap;
 *      heap.Maximize();
 *      heap += 1;
 *      heap.Insert(3);
 *      heap.Push(5);
 *      heap.Emplace(9);
 *      std::cout << heap << std::endl;
 * @endcode
 *
 * @tparam     ElementType  Type of the elements contained by the heap.
 */
template<typename ElementType>
class BinaryHeap {
    public:
        // Type aliasing
        /**
         * @brief      The type of the elements in the heap.
         */
        using TElement  = ElementType;

        /// @name Constructors and Destructor
        /// @{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS
            /**
             * @brief      Constructs an empty Min-heap.
             *
             * @param      elements  The elements
             */
            BinaryHeap()
            {
                Minimize();
            }

            /**
             * @brief      Constructs a Min-heap of an vector.
             *
             * @param      elements  The elements
             */
            explicit BinaryHeap ( std::vector<TElement> const & elements )
            {
                Minimize();
                BuildWith( elements );
            }
        /// @}

        /// @name Element Access
        /// @{
#pragma mark ELEMENT_ACCESS
            /**
             * @brief      The top element.
             *
             * @pre        The heap must not be empty.
             *
             * @return     The element with minimum key according to the comparator.
             */
            inline TElement const & Top() const 
            {
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );
                USAGE_ASSERT ( !Empty() );
                return heap_.front();
            }

            /**
             * @brief      Searches for the first match.
             *
             * @param[in]  element  The element to search for.
             *
             * @return     Index of the element, or if not available Const::none.
             */
            inline Types::index Search ( TElement const & element ) const 
            {
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );

                auto result = std::find( std::begin(heap_), std::end(heap_), element );
                if ( result != std::end( heap_ ) )
                {
                    return std::distance( std::begin(heap_), result );
                }
                return Const::none;
            }
        /// @}

        /// @name Element Insertion
        /// @{
#pragma mark ADD_ELEMENTS
            /**
             * @brief      Inserts an element into the heap.
             *
             * @param      element  The element.
             *
             * @return     @p *this.
             */
            inline BinaryHeap & operator+= ( TElement const & rhs ) 
            {
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );
                heap_.emplace_back(rhs);
                SiftUp();
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );
                return *this;
            }

            /**
             * @brief      Inserts an element into the heap.
             *
             * @param      element  The element.
             *
             * @return     @p *this.
             */
            inline BinaryHeap & operator+= ( TElement && rhs ) 
            {
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );
                heap_.emplace_back(std::move(rhs));
                SiftUp();
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );
                return *this;
            }

            /**
             * @brief      Inserts an element into the heap.
             *
             * @param      element  The element.
             */
            inline void Insert ( TElement const & element ) 
            {
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );
                *this += element;
            }

            /**
             * @brief      Inserts an element into the heap.
             *
             * @param      element  The element.
             */
            inline void Insert ( TElement && element ) 
            {
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );
                *this += std::move(element);
            }

            /**
             * @brief      Inserts the elements from the range [first, last).
             *
             * @param[in]  first    Iterator pointing to the first element to add.
             * @param[in]  last     Iterator pointing behind the last element to add.
             *
             * @tparam     InputIt  The type of the iterators. It must satisfy the requirements of
             *                      input iterators.
             */
            template<typename InputIt>
            inline void Insert ( InputIt first, InputIt last) 
            {
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );
                for ( InputIt it = first
                    ; it != last
                    ; ++it ) 
                {
                    *this += *it;
                }
            }

            /**
             * @brief      Inserts the elements from the vector.
             *
             * @param      elements  The elements to insert
             */
            inline void Insert ( std::vector<TElement> const & elements) 
            {
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );
                Insert(elements.begin(), elements.end());
            }

            /**
             * @brief      Emplaces an element to the heap.
             *
             * @param      args  The arguments of a constructor of @p TElement.
             */
            template <typename... Args>
            inline void Emplace ( Args&&... args ) 
            {
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );
                heap_.emplace_back ( std::forward<Args>(args)... );
                SiftUp();
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );
            }

            /**
             * @brief      Builds a heap.
             *
             * @note       This will overwrite the existing content.
             *
             * @param[in]  elements  The elements with which to build the heap
             */
            inline void BuildWith ( std::vector<TElement> const & elements ) 
            {
                heap_ = elements;
                MakeHeapProperty();
            }
        /// @}

        /// @name Modifiers
        /// @{
#pragma mark MODIFIERS
            /**
             * @brief      Deletes the top element.
             *
             * @pre        The heap is not empty.
             */
            inline void Pop() 
            {
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );
                USAGE_ASSERT ( Size() > 0           );
                DeleteTop();
            }

            /**
             * @brief      Deletes the top element.
             *
             * @pre        The heap is not empty.
             *
             * @return     The top element.
             */
            inline TElement DeleteTop() 
            {
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );
                USAGE_ASSERT ( Size() > 0           );

                TElement top = std::move( Front() );
                if ( Size() > 1 ) 
                {
                    using std::swap; // enable ADL
                    swap ( Front(), Back() );
                    heap_.pop_back();
                    SiftDown();
                } else {
                    heap_.pop_back();
                }
                return top;
            }

            /**
             * @brief      Clears the heap.
             */
            inline void Clear() 
            {
                heap_.clear();
            }

            /**
             * @brief      Changes the key of one element.
             * @details    The key of the element may be increased or decreased (or remain
             *             unchanged).
             *
             * @pre        @code index < Size() @endcode
             *
             * @param[in]  index    The index of which the key shall be changed.
             * @param[in]  element  The element with a new key.
             */
            inline void ChangeKey ( Types::index     index
                                  , TElement const & element )
            {
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );
                USAGE_ASSERT ( index < Size()       );
                
                ElementAt( index ) = element;
                SiftUp( index );
                SiftDown( index );
            }

            /**
             * @brief      Decreases the key of one element.
             * @details    This only supports decreasing the key (according to the comparator) but not
             *             increasing it.
             *             That is, `Comparator()(oldElement, element)` is @p false.
             *
             * @pre        `index < Size() && !Comparator()(oldElement, element)`,
             *             where @p oldElement denotes the element at position @p index, which is
             *             replaced.
             *
             * @param[in]  index    The index of which the key shall be decreased.
             * @param      element  The new element.
             */
            inline void DecreaseKey ( Types::index     index
                                    , TElement const & element ) 
            {
                ESSENTIAL_ASSERT ( ComplyHeapProperty() );
                USAGE_ASSERT ( index < Size()       );

                ElementAt( index ) = element;
                SiftUp( index );
            }
        /// @}

        /// @name Capacity
        /// @{
#pragma mark CAPACITY

            /**
             * @brief      Checks if BinaryHeap is empty.
             *
             * @return     TRUE if empty and FALSE otherwise.
             */
            inline bool Empty() const 
            {
                return heap_.empty();
            }

            /**
             * @brief      Number of elements in the heap
             *
             * @return     The size of the heap
             */
            inline Types::count Size() const 
            {
                return heap_.size();
            }
        /// @}

        /// @name Comparator
        /// @{
#pragma mark COMPARATORS

            /**
             * @brief      The comparator.
             *
             * @return     The comparator.
             */
            inline std::function< bool  ( TElement const &
                                        , TElement const & ) >
            const & Comparator() const 
            {
                return comparator_; 
            }

            /**
             * @brief      Changes the comparator.
             * @details    The comparator must represent a strict total order on the elements.
             *
             * @code{.cpp}
             *      ...
             *      heap_.Comparator( []( int a, int b ) { return a < b; } );
             *      ...
             * @endcode
             *
             * @see        TestBinaryHeapWithVectorOfInteger::TEST_F(TestBinaryHeapWithVectorOfInteger,ChangeComparatorToLess)
             *
             * @param[in]  comparator  The comparator
             */
            inline void Comparator( std::function<bool  ( TElement const &
                                                        , TElement const & )> comparator )
            {
                comparator_ = comparator;
                MakeHeapProperty();
            }

            /**
             * @brief      Changes the comparator to construct a max-heap.
             * @details    The comparator is set to `std::greater<TElement>()` and the heap
             *             is updated to respect the new comparator.
             */
            inline void Maximize() 
            {
                Comparator ( std::greater<TElement>() );
            }

            /**
             * @brief      Changes the comparator to construct a min-heap.
             * @details    The comparator is set to `std::less<TElement>()` and the heap
             *             is updated to respect the new comparator.
             */
            inline void Minimize() 
            {
                Comparator ( std::less<TElement>() );
            }
        ///@}

        /// @name Operators
        /// @{
#pragma mark OPERATORS
            /**
             * @brief      Check if two heaps are equivalent.
             * @details    Equivalent means that they contain the same elements
             *             when the order of the elements is ignored.
             *
             * @param      rhs   The right hand side heap.
             *
             * @return     @p true if the heaps are equivalent, @p false if they do not
             *             have the same element.
             */
            inline bool operator==( BinaryHeap const & rhs ) const 
            {
                return IsEqualTo<false>( rhs );
            }

            /**
             * @brief      Check if two heaps are not equivalent.
             * @details    Equivalent means that they contain the same elements
             *             when the order of the elements is ignored.
             *
             * @param      rhs   The right hand side heap.
             *
             * @return     @p true if the heaps do not contain the same elements,
             *             @p false if they contain the same elements where the order
             *             does not matter.
             */
            inline bool operator!=( BinaryHeap const & rhs) const 
            {
                return !(*this==rhs);
            }

            /**
             * @brief      Determines if equal to.
             *
             * @param      rhs          The right hand side binary heap object
             *
             * @tparam     IsIdentical  If @p true it determines if equal---in
             *     sense of order---to the @rhs binary heap, if @p false it checks
             *     if the heap has the same elements.
             *
             * @return     @p true if equal to @p rhs, @p false otherwise.
             */
            template<bool IsIdentical>
            inline bool IsEqualTo( BinaryHeap const & rhs ) const 
            {
                return internal::BinaryHeapCheck<TElement, IsIdentical>
                    ::IsEqualTo(*this, rhs);
            }

            /**
             * @brief      Swap two BinaryHeaps
             *
             * @param      lhs   The left hand side BinaryHeaps
             * @param      rhs   The right hand side BinaryHeaps
             */
            friend void swap ( BinaryHeap<TElement> & lhs, BinaryHeap<TElement> & rhs ) 
            { // Necessary for the copy and swap idiom
                using std::swap; // enable ADL
                swap( lhs.heap_,                    rhs.heap_ );
                swap( lhs.comparator_,              rhs.comparator_);
            }
        /// @}

        /// @name Output
        /// @{
#pragma mark OUTPUT
            /**
             * @brief      Writes the heap into an output stream.
             *
             * @param      outputStream  The stream to write data to, e.g., std::cout.
             * @param      heap          The heap.
             *
             * @return     The resulting output stream.
             */
            friend std::ostream & operator<<( std::ostream     & outputStream
                                            , BinaryHeap const & heap )
            {
                std::copy( heap.begin(), heap.end(), std::ostream_iterator<TElement>( outputStream , "|" ) );
                return outputStream;
            }
        /// @}

        /// @name Iterators
        /// @{
#pragma mark ITERATORS
    private:

            /**
             * @brief      Class for a heap iterator.
             * @details    Based on example code from https://en.cppreference.com/w/cpp/iterator/iterator.
             */
            class HeapIterator {
                Types::largeNumber counter_;            /**< Counter */
                Types::largeNumber begin_;              /**< Begin */
                Types::largeNumber end_;                /**< End */
                std::vector<TElement> const * vector_;  /**< Vector of elements */
            public:
                using iterator_category = std::input_iterator_tag;  /**< Iterator category type */
                using value_type        = TElement;                 /**< Value type */
                using difference_type   = Types::difference;        /**< Difference type */
                using pointer           = const TElement*;          /**< Element pointer type */
                using reference         = const TElement&;          /**< Element reference type */

                explicit HeapIterator ( std::vector<TElement> const * vector
                                      , Types::largeNumber counter = 0      )
                : counter_( counter )
                , begin_( 0 )
                , end_( vector->size() - 1 )
                , vector_(vector){ }

                explicit HeapIterator ( std::vector<TElement> const * vector
                                      , Types::largeNumber            counter
                                      , Types::largeNumber            begin
                                      , Types::largeNumber            end )
                : counter_( counter )
                , begin_( begin )
                , end_( end )
                , vector_(vector){ }

                HeapIterator   & operator++() { ( end_ >= begin_ ) ? ( ++counter_ ) : ( --counter_ ); return *this; }
                HeapIterator operator++(int) {
                    HeapIterator copy = *this;
                    ++*this;
                    return copy;
                }
                bool             operator==( HeapIterator const & rhs) const {
                    return counter_ == rhs.counter_ && vector_ == rhs.vector_;
                }
                bool             operator!=( HeapIterator const & rhs) const { return !( operator==(rhs) ); }
                TElement const & operator*() const { return (*vector_)[counter_]; }
                TElement const * operator->() const { return &((*vector_)[counter_]); }
            };

    public:
            /**
             * @brief      An iterator pointing to the top element of the heap.
             *
             * @return     An iterator pointing to the top element.
             */
            HeapIterator begin() const noexcept { return HeapIterator(&heap_, 0); }

            /**
             * @brief      An interator pointing behind the last element.
             *
             * @return     An interator pointing behind the last element.
             */
            HeapIterator end() const noexcept { return HeapIterator( &heap_, heap_.size() ); }
        /// @}

        /// @name Loops
        /// @{
#pragma mark LOOPS
            /**
             * @brief      Iterates over all elements in the heap.
             *
             * @param[in]  function  The function object that is called for all
             *                       elements in the heap. It must accept one
             *                       argument of type @p TElement, e.g.,
             * @code
             *     []( TElement & element ) { ... }
             * @endcode
             *
             * @tparam     Policy    The execution policy.
             * @tparam     FUNCTION  The type of the function object.
             */
            template<ExecutionPolicy Policy, typename FUNCTION>
            inline
            void for_all_elements ( FUNCTION function ) 
            {
                internal::BinaryHeapLoopDifferentiation<BinaryHeap, Policy>
                    ::for_all_elements ( *this, function);
            }

            /**
             * @brief      Iterates over all elements in the heap.
             *
             * @param[in]  function  The function object that is called for all
             *                       elements in the heap. It must accept one
             *                       argument of type @p TElement, e.g.,
             * @code
             *     []( TElement const & element ) { ... }
             * @endcode
             *
             * @tparam     Policy    The execution policy.
             * @tparam     FUNCTION  The type of the function object.
             */
            template<ExecutionPolicy Policy, typename FUNCTION>
            inline
            void for_all_elements ( FUNCTION function ) const 
            {
                internal::BinaryHeapLoopDifferentiation<BinaryHeap const, Policy>
                    ::for_all_elements ( *this, function);
            }
        /// @}

    private:
        /// @name Accessors
        /// @{
#pragma mark ACCESSORS
            inline TElement       & ElementAt ( Types::index index )       { ESSENTIAL_ASSERT( index < Size() ); return heap_[index]; }
            inline TElement const & ElementAt ( Types::index index ) const { ESSENTIAL_ASSERT( index < Size() ); return heap_[index]; }

            inline TElement       & ParentElementAt ( Types::index index )       { ESSENTIAL_ASSERT( HasParent() ); return ElementAt(ParentIdOf(index)); }
            inline TElement const & ParentElementAt ( Types::index index ) const { ESSENTIAL_ASSERT( HasParent() ); return ElementAt(ParentIdOf(index)); }

            inline TElement       & RightElementAt ( Types::index index )        { ESSENTIAL_ASSERT( HasRightChild(index) ); return ElementAt(RightChildIdOf(index)); }
            inline TElement const & RightElementAt ( Types::index index ) const  { ESSENTIAL_ASSERT( HasRightChild(index) ); return ElementAt(RightChildIdOf(index)); }

            inline TElement       & LeftElementAt ( Types::index index )         { ESSENTIAL_ASSERT( HasLeftChild(index) ); return ElementAt(LeftChildIdOf(index)); }
            inline TElement const & LeftElementAt ( Types::index index )  const  { ESSENTIAL_ASSERT( HasLeftChild(index) ); return ElementAt(LeftChildIdOf(index)); }

            inline Types::index  LeftChildIdOf ( Types::index index ) const { return ( 2 * index + 1 ); }
            inline Types::index RightChildIdOf ( Types::index index ) const { return ( 2 * index + 2 ); }
            inline bool            HasChildren ( Types::index index ) const { return LeftChildIdOf(index) < Size(); }
            inline bool           HasLeftChild ( Types::index index ) const { return LeftChildIdOf(index) < Size(); }
            inline bool          HasRightChild ( Types::index index ) const { return RightChildIdOf(index) < Size(); }
            inline Types::index     ParentIdOf ( Types::index index ) const { return floor( ( index - 1 ) / 2 ); }
            inline bool              HasParent ( Types::index index ) const { return index > 0; }

            /**
             * @brief      The top element.
             *
             * @return     The top element, which is at the front of @p heap_.
             */
            inline TElement & Front() 
            {
                ESSENTIAL_ASSERT( !Empty() );
                return heap_.front();
            }

            /**
             * @brief      The top element.
             *
             * @return     The top element, which is at the front of @p heap_.
             */
            inline TElement const & Front() const 
            {
                ESSENTIAL_ASSERT( !Empty() );
                return heap_.front();
            }

            /**
             * @brief      The last element.
             *
             * @return     The last element, which is at the back of @p heap_.
             */
            inline TElement & Back() 
            {
                ESSENTIAL_ASSERT( !Empty() );
                return heap_.back();
            }

            /**
             * @brief      The last element.
             *
             * @return     The last element, which is at the back of @p heap_.
             */
            inline TElement const & Back() const 
            {
                ESSENTIAL_ASSERT( !Empty() );
                return heap_.back();
            }

            /**
             * @brief      Maximum index of the heap.
             *
             * @return     The maximum index.
             */
            inline Types::index MaximumIndex() const 
            {
                ESSENTIAL_ASSERT( !Empty() );
                return heap_.size() - 1;
            }
        /// @}

        /// @name Heap Property Methods
        /// @{
#pragma mark HEAP_PROPERTY_METHODS
            /**
             * @brief      Makes a heap property.
             * @details    This works even if the heap is empty.
             *
             *             The counter starts at @f$ n / 2 - 1 @f$ since the
             *             leafs fulfill the heap property. Thus, starting at
             *             the second level is sufficient. Roughly speaking,
             *             each layer @p l contains twice as many elements
             *             than the previous layer meaning @f$2^l@f$ elements.
             *             Dividing by 2 brings us to the previous layer
             *             @f$2^{l-1}@f$. As we start at 0, the value has to
             *             be reduced by 1.
             */
            inline void MakeHeapProperty() 
            {
                for ( Types::rcount counter = heap_.size() / 2 - 1
                    ; counter >= 0
                    ; --counter )
                {
                    SiftDown( counter );
                }
                ESSENTIAL_ASSERT( ComplyHeapProperty() );
            }

            /**
             * @brief      Checks if the heap complies with the heap property
             *             at element @p index.
             *
             * @param[in]  index  The index of the element.
             *
             * @return     @p true if the heap complies with the heap property
             *             at element @p index and @p false otherwise.
             */
            inline bool ComplyHeapProperty( Types::index index ) const 
            {
                ESSENTIAL_ASSERT( index < Size() );
                if ( !HasChildren( index ) ) return true;
                if ( Comparator()( LeftElementAt(index), ElementAt(index) ) ) return false;
                if ( !HasRightChild( index ) ) return true;
                return !Comparator()(RightElementAt(index), ElementAt(index));
            }

            /**
             * @brief      Checks if the heap complies with the heap property.
             *
             * @return     @p true if the heap complies the heap property, @p
             *     false otherwise.
             */
            inline bool ComplyHeapProperty() const 
            {
                for ( Types::count counter = 0
                    ; counter < Size()
                    ; ++counter ) 
                {
                    if ( !ComplyHeapProperty( counter ) ) 
                    {
                        return false;
                    }
                }
                return true;
            }
        /// @}

        /// @name Sifts
        /// @{
#pragma mark SIFTS
            /**
             * @brief      Sift the last element up.
             */
            inline void SiftUp () 
            {
                ESSENTIAL_ASSERT( !Empty() );
                SiftUp( MaximumIndex() );
            }

            /**
             * @brief      Sift up
             * @details    The element will be shifted upwards the tree while the
             *
             * @param[in]  index  The index of the element tha shall be sifted up.
             */
            inline void SiftUp ( Types::index index ) 
            {
                ESSENTIAL_ASSERT( index < Size() );

                if ( !HasParent(index) ) return;
                Types::index parentIndex  = ParentIdOf( index );
                while ( Comparator()( ElementAt( index ), ElementAt( parentIndex ) ) 
                    && index != 0 ) 
                {
                    using std::swap; // enable ADL
                    swap( ElementAt( index ), ElementAt( parentIndex ) );
                    index          = parentIndex;
                    if ( !HasParent(index) || index == 0 ) return;
                    parentIndex    = ParentIdOf( index );
                }
            }

            /**
             * @brief      Sift down the element at the root.
             */
            inline void SiftDown() 
            {
                ESSENTIAL_ASSERT( !Empty() );
                SiftDown( 0 );
            }

            /**
             * @brief      Sift down the element at @p index.
             * @details    Moves an element down the tree until the heap property holds
             *
             * @param[in]  index  The index of the element that shall be sifted down.
             */
            inline void SiftDown( Types::index index ) 
            {
                ESSENTIAL_ASSERT( index < Size() );

                Types::index childIndex = 0;
                if ( !HasChildren( index ) ) return;
                childIndex      = SelectSwappableChildAt ( index );

                while ( Comparator()( ElementAt(childIndex), ElementAt(index) ) 
                    && childIndex < Size() ) 
                {
                    using std::swap;
                    swap( ElementAt(index), ElementAt(childIndex) );
                    index      = childIndex;
                    if ( !HasChildren( index ) ) return;
                    childIndex = SelectSwappableChildAt ( index );
                }
            }
        /// @}

        /// @name Swappability
        /// @{
#pragma mark SWAPPABILITY
            /**
             * @brief      Selects the smallest child, where smallest is measured according to
             *             the comparator.
             * @details    If the elements needs to be swapped with a child, then it is the
             *             child at the position returned by this method.
             *
             * @param[in]  index  The current index.
             *
             * @return     The index of the child that has the best key.
             */
            inline Types::index SelectSwappableChildAt ( Types::index index ) const 
            {
                ESSENTIAL_ASSERT( HasChildren(index) );
                if ( !HasRightChild(index) ) 
                {
                    return LeftChildIdOf( index );
                }

                ESSENTIAL_ASSERT( HasRightChild(index) );
                if ( Comparator()( LeftElementAt( index ), RightElementAt( index )) ) 
                {
                    return LeftChildIdOf( index );
                }
                return RightChildIdOf( index );
            }
        /// @}

#pragma mark FRIENDS
        friend internal::BinaryHeapCheck<TElement, true>;
        friend internal::BinaryHeapCheck<TElement, false>;
        friend internal::BinaryHeapLoopDifferentiation<BinaryHeap, ExecutionPolicy::sequential>;
        friend internal::BinaryHeapLoopDifferentiation<BinaryHeap, ExecutionPolicy::breakable>;
        friend internal::BinaryHeapLoopDifferentiation<BinaryHeap, ExecutionPolicy::parallel>;
        friend internal::BinaryHeapLoopDifferentiation<BinaryHeap const, ExecutionPolicy::sequential>;
        friend internal::BinaryHeapLoopDifferentiation<BinaryHeap const, ExecutionPolicy::breakable>;
        friend internal::BinaryHeapLoopDifferentiation<BinaryHeap const, ExecutionPolicy::parallel>;

#pragma mark MEMBERS
    private:
        std::vector<TElement> heap_;
        std::function<bool(TElement const & a, TElement const & b)> comparator_;
};

namespace internal {
#pragma mark HEAPS_ARE_IDENTICAL_CHECK
template<typename Type>
class BinaryHeapCheck<Type, true> {
    
    // Type aliasing
    using TElement = Type;
    using THeap    = BinaryHeap<TElement>;
    
    public:
        /**
         * @brief      Determines if equal---in sense of order---to the \rhs binary heap.
         *
         * @param      rhs   The right hand side binary heap object.
         *
         * @return     TRUE if the order of the elements are the same to the \p rhs, FALSE otherwise.
         */
        static inline bool IsEqualTo ( THeap const & lhs
                                     , THeap const & rhs ) 
        {
            if ( lhs.Size() != rhs.Size() ) return false;
            for ( Types::count counter = 0
                ; counter < lhs.Size()
                ; ++counter ) 
            { 
                if ( lhs.ElementAt( counter ) != rhs.ElementAt( counter ) ) return false;
            }
            return true;
        }
};

#pragma mark HEAPS_HAVE_SAME_ELEMENTS_CHECK
template<typename Type>
class BinaryHeapCheck<Type, false> {

    // Template aliasing
    using TElement = Type;
    using THeap    = BinaryHeap<TElement>;

    public:
        /**
         * @brief      Determines if it has same elements as the other binary heap.
         *
         * @param      rhs   The right hand side binary heap object.
         *
         * @return     TRUE if it has the same elements as \p rhs, FALSE otherwise.
         */
        static inline bool IsEqualTo ( THeap const & lhs
                                     , THeap const & rhs ) 
        {
            if ( lhs.Size() != rhs.Size() ) return false;
            THeap tempRhs = rhs; std::sort( tempRhs.heap_.begin(), tempRhs.heap_.end() );
            THeap tempLhs = lhs; std::sort( tempLhs.heap_.begin(), tempLhs.heap_.end() );
            for ( Types::count counter = 0
                ; counter < tempLhs.Size()
                ; ++counter ) 
            { 
                if ( tempLhs.ElementAt( counter ) != tempRhs.ElementAt( counter ) ) return false;
            }
            return true;
        }
};

#pragma mark SEQUENTIAL_LOOPS
/**
 * @brief      Sequential loops for BinaryHeap.
 *
 * @tparam     HeapType  The type of the heap.
 */
template<typename HeapType>
class BinaryHeapLoopDifferentiation<HeapType, ExecutionPolicy::sequential> {

    using THeap = HeapType;

    public:
        /**
         * @brief      Iterates over all elements in the heap.
         *
         * @param[in]  function  The function pointer, e.g., lambda function
         * that has a TElement object as input
         *
         * @code{.cpp}
         *      [](TElement element) { Do something with the element object }
         * @endcode
         * 
         * @tparam     FUNCTION  Function
         */
        template<typename FUNCTION>
        inline static
        void for_all_elements ( THeap &  heap
                              , FUNCTION function )
        {
            for (auto & element : heap.heap_) 
            {
                function(element);
            }
            if ( !heap.ComplyHeapProperty() ) 
            {
                heap.MakeHeapProperty();
            }
        }
};

/**
 * @brief      Sequential loops for const BinaryHeap.
 *
 * @tparam     HeapType  The type of the heap.
 */
template<typename HeapType>
class BinaryHeapLoopDifferentiation<HeapType const, ExecutionPolicy::sequential> {

    using THeap = HeapType const;

    public:
        /**
         * @brief      Iterates over all elements in the heap.
         *
         * @param[in]  function  The function pointer, e.g., lambda function
         * that has a TElement object as input
         *
         * @code{.cpp}
         *      [](TElement element) { Do something with the element object }
         * @endcode
         *
         * @tparam     FUNCTION  Function
         */
        template<typename FUNCTION>
        inline static
        void for_all_elements ( THeap &  heap
                              , FUNCTION function )
        {
            for (auto & element : heap.heap_) 
            {
                function(element);
            }
            ESSENTIAL_ASSERT( heap.ComplyHeapProperty() );
        }
};

#pragma mark BREAKABLE_LOOPS
template<typename HeapType>
class BinaryHeapLoopDifferentiation<HeapType, ExecutionPolicy::breakable> {

    using THeap = HeapType;

    public:
        /**
         * @brief      Iterate over all elements in the heap
         *
         * @param[in]  function  The function pointer, e.g., lambda function
         *      that has a TElement object as input and a boolean as return
         *      type. If the boolean is @p true the loop will be continued, if
         *      @p false this emulates a break.
         *
         * @code{.cpp}
         *      [](TElement element) -> bool { Do something with the element object }
         * @endcode
         * 
         * @note       Heap property might be violated in the none const variant
         * 
         * @tparam     FUNCTION  Function
         */
        template<typename FUNCTION>
        inline static
        void for_all_elements ( THeap &  heap
                              , FUNCTION function )
        {
            for ( auto & element : heap.heap_ ) 
            {
                bool toContinue = function(element);
                if ( !toContinue ) break;
            }
            if ( !heap.ComplyHeapProperty() ) 
            {
                heap.MakeHeapProperty();
            }
        }
};

template<typename HeapType>
class BinaryHeapLoopDifferentiation<HeapType const, ExecutionPolicy::breakable> {

    using THeap = HeapType const;

    public:
        /**
         * @brief      Iterate over all elements in the heap
         *
         * @param[in]  function  The function pointer, e.g., lambda function
         *      that has a TElement object as input and a boolean as return
         *      type. If the boolean is @p true the loop will be continued, if
         *      @p false this emulates a break.
         *
         * @code{.cpp}
         *      [](TElement element) -> bool { Do something with the element object }
         * @endcode
         *
         * @note       Heap property might be violated in the none const variant
         *
         * @tparam     FUNCTION  Function
         */
        template<typename FUNCTION>
        inline static
        void for_all_elements ( THeap &  heap
                              , FUNCTION function )
        {
            for ( auto & element : heap.heap_ ) 
            {
                bool toContinue = function(element);
                if ( !toContinue ) break;
            }
            ESSENTIAL_ASSERT( heap.ComplyHeapProperty() );
        }
};

#pragma mark PARALLEL_LOOPS

#ifdef OPENMP_AVAILABLE

template<typename HeapType>
class BinaryHeapLoopDifferentiation<HeapType, ExecutionPolicy::parallel> {

    // Type aliasing
    using THeap = HeapType;

    public:
        /**
         * @brief      Iterate over all elements in the heap
         *
         * @param[in]  function  The function pointer, e.g., lambda function
         * that has a TElement object as input
         *
         * @code{.cpp}
         *      [](TElement element) { Do something with the element object }
         * @endcode
         * 
         * @tparam     FUNCTION  Function
         */
        template<typename FUNCTION>
        inline static
        void for_all_elements ( THeap &  heap
                              , FUNCTION function )
        {
            #pragma omp parallel for
                for ( Types::count counter = 0
                    ; counter < heap.heap_.size()
                    ; ++counter ) 
                {
                    function ( heap.heap_[counter] );
                }
            if ( !heap.ComplyHeapProperty() ) 
            {
                heap.MakeHeapProperty();
            }
        }
};

template<typename HeapType>
class BinaryHeapLoopDifferentiation<HeapType const, ExecutionPolicy::parallel> {

    // Type aliasing
    using THeap = HeapType const;

    public:
        /**
         * @brief      Iterate over all elements in the heap
         *
         * @param[in]  function  The function pointer, e.g., lambda function
         * that has a TElement object as input
         *
         * @code{.cpp}
         *      [](TElement element) { Do something with the element object }
         * @endcode
         *
         * @tparam     FUNCTION  Function
         */
        template<typename FUNCTION>
        inline static
        void for_all_elements ( THeap &  heap
                              , FUNCTION function )
        {
            #pragma omp parallel for
                for ( Types::count counter = 0
                    ; counter < heap.heap_.size()
                    ; ++counter ) 
                {
                    function ( heap.heap_[counter] );
                }
            ESSENTIAL_ASSERT( heap.ComplyHeapProperty() );
        }
};


#else // OPENMP_AVAILABLE

namespace internal {
template<typename HeapType>
class BinaryHeapLoopDifferentiation<HeapType, ExecutionPolicy::parallel>
    : public BinaryHeapLoopDifferentiation<HeapType, ExecutionPolicy::sequential> {
};

#endif

} // namespace internal
} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__CONTAINER__BINARY_HEAP_HPP

/*
 * MappingBinaryHeap.hpp
 *
 *  Created on: Feb 19, 2019
 *      Author: Matthias Wolf
 */

#ifndef EGOA__DATA_STRUCTURES__CONTAINER__MAPPING_BINARY_HEAP_HPP
#define EGOA__DATA_STRUCTURES__CONTAINER__MAPPING_BINARY_HEAP_HPP

#include "Auxiliary/Auxiliary.hpp"
#include "Auxiliary/ContainerLoop.hpp"
#include "Auxiliary/ExecutionPolicy.hpp"

#include "Exceptions/Assertions.hpp"

#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>

namespace egoa {

/**
 * @brief      Class for binary heap data structure, in which elements are
 *             sorted by keys.
 * @details    The elements and the keys are represented as separate objects.
 *             The heap supports changing the key of an element.
 *             The heap does not support having multiple keys for the same element.
 *
 *             Both the elements and the keys are stored in the heap.
 *
 *             A possible application is to store labels at the vertices of a
 *             graph. In this use case the elements are the vertices (or vertex
 *             identifiers) and the keys are the labels.
 *
 *             The map must support the following operations, where @p element
 *             is of type @p ElementType and @p i is of type @p Types::index.
 *
 *             Operation                                              | Effect
 *             -------------------------------------------------------|----------------------------------------------------------
 *             @code{.cpp} map[element] = i;                 @endcode | @p map maps @p element to @p i.
 *             @code{.cpp} Types::index i = map.at(element); @endcode | @p i is set to the index of the element stored in the map.
 *             @code{.cpp} map.erase(element);               @endcode | The mapping for @p element is removed from @p map.
 *             @code{.cpp} map.clear();                      @endcode | @p map does not contain any elements.
 *             The methods have the following worst case time complexities:
 *             Function                      | Time Complexity
 *             ------------------------------|---------------------
 *             Top                           | @f$\Theta(1)@f$
 *             Insert, Emplace, operator+=   | @f$\Theta(\log n)@f$
 *             DeleteTop, Pop                | @f$\Theta(\log n)@f$
 *             Delete                        | @f$\Theta(\log n)@f$
 *             Clear                         | @f$\Theta(1)@f$ + 1 call to `map.clear()`
 *             ChangeKey                     | @f$\Theta(\log n)@f$ + 1 call to `map.at()`
 *
 *             The comparator must implement a strict order on the keys. The smallest
 *             element according to the comparator is the top element of the heap.
 *             For example, if the comparator is `std::less<TKey>()`, the smallest element
 *             is at the top, and if the comparator is `std::greater<TKey>`, the largest
 *             element is at the top.
 *
 * @tparam     ElementType  The type of the elements
 * @tparam     KeyType      The type of the keys
 * @tparam     MapType      A mapping from elements to indices.
 *                          The default is <tt>std::unordered_map\<KeyType, Types::index\></tt>.
 *                          To use the default @p KeyType must satisfy all
 *                          requirements to be used as the key of a @p std::unordered_map.
 */
template<typename ElementType,
         typename KeyType,
         typename MapType = std::unordered_map<ElementType, Types::index>>
class MappingBinaryHeap {
public:
    /**
     * @brief      The type of the elements in the heap.
     */
    using TElement  = ElementType;
    /**
     * @brief      The type of the keys.
     */
    using TKey      = KeyType;
    /**
     * @brief      The type of the mapping from elements to indices.
     */
    using TMap      = MapType;
    /**
     * @brief      The type of the iterators.
     */
    using TIterator = typename std::vector<std::pair<TElement, TKey>>::const_iterator;
    /**
     * @brief      The type of the comparator.
     */
    using TComparator = std::function<bool(TKey const &, TKey const &)>;

    /// @name Constructors
    /// @{
        /**
         * @brief      Constructs an empty heap, in which the elements are sorted
         *             by their keys in increasing order.
         *
         * @param[in]  comparator   The comparator used to compare the elements.
         * @param[in]  map   The mapping from elements to positions in the heap.
         */
        MappingBinaryHeap(TComparator comparator = std::less<TKey>(),
                          TMap map = TMap())
        : elementKeyPairs_(),
          map_(std::move(map)),
          comparator_(std::move(comparator))
        {}

        /**
         * @brief      Constructs an heap containing the given elements.
         *
         * @param[in]  elementsKeyPairs  The element-key-pairs.
         * @param[in]  comparator   The comparator used to compare the elements.
         * @param[in]  map               The map.
         */
        MappingBinaryHeap(std::vector<std::pair<TElement, TKey>> elementsKeyPairs,
                          TComparator comparator = std::less<TKey>(),
                          TMap map = TMap())
        : elementKeyPairs_(std::move(elementsKeyPairs)),
          map_(std::move(map)),
          comparator_(std::move(comparator))
        {
            MakeHeapProperty();
        }

        /**
         * @brief      Constructs the heap filled with the element-key-pairs.
         *
         * @param[in]  first  The first An iterator pointing to the first element-key-pair.
         * @param[in]  last   The last An iterator pointing behind the last element-key-pair.
         * @param[in]  comparator   The comparator used to compare the elements.
         * @param[in]  map    The map.
         *
         * @tparam     It     An iterator pointing to @p std::pair<TElement, TKey>.
         */
        template<typename It>
        MappingBinaryHeap(It first,
                          It last,
                          TComparator comparator = std::less<TKey>(),
                          TMap map = TMap())
        : elementKeyPairs_(first, last),
          map_(std::move(map)),
          comparator_(std::move(comparator))
        {}
    /// @}

#pragma mark ELEMENT_ACCESS
    /// @name Element Access
    /// @{
        /**
         * @brief      The element and the key at the top of the heap.
         *
         * @pre        The heap is not empty.
         *
         * @return     A pair containing the element and the key at the top of the heap.
         */
        std::pair<TElement, TKey> const & Top() const {
            USAGE_ASSERT(!Empty());
            return elementKeyPairs_.front();
        }

        /**
         * @brief      The element at the top of the heap.
         *
         * @pre        The heap is not empty.
         *
         * @return     The element at the top of the heap.
         */
        TElement const & TopElement() const {
            USAGE_ASSERT(!Empty());
            return elementKeyPairs_.front().first;
        }

        /**
         * @brief      The key of the element at the top of the heap.
         *
         * @pre        The heap is not empty.
         *
         * @return     The key of the element at the top of the heap.
         */
        TKey const & TopKey() const {
            USAGE_ASSERT(!Empty());
            return elementKeyPairs_.front().second;
        }

        /**
         * @brief      The key of the element.
         *
         * @pre        The heap must contain the element.
         *
         * @param      element  The element.
         *
         * @return     The key of the element.
         */
        TKey const & KeyOf(TElement const & element) const {
            USAGE_ASSERT ( HasKeyOf( element ) );
            return KeyAt(IndexOf(element));
        }

        /**
         * @brief      Determines if the element exist in the heap.
         *
         * @param      element  The element.
         *
         * @return     @p True if the element exists, @p False otherwise.
         */
        bool HasKeyOf(TElement const & element) const {
            return map_.find(element) != map_.end();
        }
    /// @}

#pragma mark ADD_ELEMENTS
    /// @name Inserting Elements
    /// @{
        /**
         * @brief      Inserts the element with the given key.
         *
         * @pre        The heap does not contain the element.
         *
         * @param      element  The element.
         * @param      key      The key.
         */
        void Insert(TElement element, TKey key) {
            USAGE_ASSERT(!HasKeyOf(element));

            Insert(std::make_pair(std::move(element), std::move(key)));
        }

        /**
         * @brief      Inserts the element with the given key.
         *
         * @pre        The heap does not contain the element.
         *
         * @param[in]  pair  The pair containing the element (first position) and the key (second position).
         */
        void Insert(std::pair<TElement, TKey> pair) {
            USAGE_ASSERT(!HasKeyOf(pair.first));

            elementKeyPairs_.push_back(std::move(pair));
            Types::index index = MaximumIndex();
            map_[elementKeyPairs_.back().first] = index;

            SiftUp();
        }

        /**
         * @brief      Inserts the element with the given key.
         * @details    Equivalent to @p Insert(pair).
         *
         * @pre        The heap does not contain the element.
         *
         * @param[in]  pair  The pair containing the element (first position) and the key (second position).
         *
         * @return     The heap.
         */
        MappingBinaryHeap & operator+=(std::pair<TElement, TKey> pair) {
            Insert(std::move(pair));
            return *this;
        }

        /**
         * @brief      Constructs an element-key-pair inplace.
         * @details    Depending on the implementation of the map, inserting the mapping
         *             from the element to the index may create a copy of the element.
         *
         *             To construct both the element and the key in-place, one can use
         *             the constructor of @p std::pair that allows piecewise construction.
         */
        ///            @code
        ///            #include <tuple>
        ///            ...
        ///            Emplace(std::piecewise_construct,
        ///                    std::forward_as_tuple(/* constructor arguments of element */),
        ///                    std::forward_as_tuple(/* constructor arguments of key */));
        ///            @endcode
        /**
         * @param      args  The arguments of the constructor of @p std::pair.
         *
         * @tparam     Args  The types of the constructor arguments.
         */
        template<typename... Args>
        void Emplace(Args && ... args) {
            elementKeyPairs_.emplace_back(std::forward<Args>(args)...);
            Types::index index = MaximumIndex();
            map_[elementKeyPairs_.back().first] = index;

            SiftUp();
        }
    /// @}

    /// @name Removing Elements
    /// @{
#pragma mark REMOVE_ELEMENTS
        /**
         * @brief      Deletes the top element and returns it and its key.
         *
         * @pre        The heap is not empty.
         *
         * @return     A pair containing the former top element and its key.
         */
        std::pair<TElement, TKey> DeleteTop() {
            USAGE_ASSERT(!Empty());
            ESSENTIAL_ASSERT(ComplyHeapProperty());

            Swap(0, MaximumIndex());

            auto top = std::move(elementKeyPairs_.back());
            elementKeyPairs_.pop_back();
            map_.erase(top.first);

            if (!Empty()) SiftDown();

            return top;
        }

        /**
         * @brief      Deletes the top element.
         *
         * @pre        The heap is not empty.
         */
        void Pop() {
            USAGE_ASSERT(!Empty());
            ESSENTIAL_ASSERT(ComplyHeapProperty());

            Swap(0, MaximumIndex());

            map_.erase(elementKeyPairs_.back().first);
            elementKeyPairs_.pop_back();

            if (!Empty()) SiftDown();
        }

        /**
         * @brief      Deletes an element from the heap.
         *
         * @param      element  The element to delete.
         *
         * @return     A pair containing the deleted element and its key.
         */
        std::pair<TElement, TKey> Delete(TElement const & element) {
            USAGE_ASSERT(HasKeyOf(element));

            Types::index index = IndexOf(element);
            Swap(index, MaximumIndex());

            auto deleted = std::move(elementKeyPairs_.back());
            elementKeyPairs_.pop_back();
            map_.erase(element);

            if (!Empty() && index <= MaximumIndex()) {
                SiftDown(index);
                SiftUp(index);
            }

            return deleted;
        }

        /**
         * @brief      Removes all elements from the heap.
         */
        void Clear() {
            elementKeyPairs_.clear();
            map_.clear();
        }
    /// @}

    /// @name Updating Elements
    /// @{
#pragma mark CHANGE_ELEMENTS
        /**
         * @brief      Changes the key of the element.
         *
         * @pre        The heap contains the element.
         *
         * @param[in]  element  The element.
         * @param[in]  newKey   The new key.
         */
        void ChangeKey(const TElement & element, TKey newKey) {
            USAGE_ASSERT(HasKeyOf(element));
            ESSENTIAL_ASSERT(ComplyHeapProperty());

            Types::index index = IndexOf(element);
            KeyAt(index) = std::move(newKey);
            SiftUp(index);
            SiftDown(index);

            ESSENTIAL_ASSERT(ComplyHeapProperty());
        }
    /// @}

    /// @name Capacity
    /// @{
#pragma mark CAPACITY
        /**
         * @brief      Whether the heap is empty.
         *
         * @return     @p true if the heap is empty, @p false otherwise.
         */
        bool Empty() const {
            return elementKeyPairs_.empty();
        }

        /**
         * @brief      The number of elements in the heap.
         *
         * @return     The number of elements in the heap.
         */
        Types::count Size() const {
            return elementKeyPairs_.size();
        }
    /// @}

#pragma COMPARATOR

    /// @name Comparator
    /// @{
        /**
         * @brief      The comparator.
         *
         * @return     The comparator.
         */
        inline std::function<bool (TKey const &, TKey const &)>
        const & Comparator() const
        {
            return comparator_;
        }

        /**
         * @brief      Changes the comparator.
         * @details    The heap is updated to reflect the change of the comparator.
         *
         * @code{.cpp}
         *      ...
         *      heap_.Comparator( []( int a, int b ) { return a < b; } );
         *      ...
         * @endcode
         *
         * @param[in]  comparator  The comparator.
         */
        inline void Comparator( std::function<bool (TKey const &, TKey const &)> comparator )
        {
            comparator_ = comparator;
            MakeHeapProperty();
        }
    /// @}

    /// @name Iteration
    /// @{
#pragma mark ITERATORS
        TIterator begin() const { return elementKeyPairs_.cbegin(); }
        TIterator end()   const { return elementKeyPairs_.cend(); }
    /// @}


#pragma mark LOOPS
        /**
         * @brief      Iterates over all elements in the heap.
         *
         * @param[in]  function   The function object that is called for all
         *                    elements in the heap. It must accept one
         *                    argument of type `std::pair<TElement, TKey>`, e.g.,
         * @code
         *     []( std::pair<TElement, TKey> const & element ) { ... }
         * @endcode
         *
         * @tparam     Policy    The execution policy.
         * @tparam     FUNCTION  The type of the function object.
         */
        template<ExecutionPolicy Policy, typename FUNCTION>
        void for_all_elements( FUNCTION function ) const {
            internal::ContainerLoop<Policy>::for_each(elementKeyPairs_, function);
        }

#pragma mark SWAP
    /**
     * @brief      Swaps the contents of two heaps.
     *
     * @param      first   The first heap.
     * @param      second  The second heap.
     */
    inline friend void swap(MappingBinaryHeap & first, MappingBinaryHeap & second) {
        using std::swap;
        swap(first.elementKeyPairs_, second.elementKeyPairs_);
        swap(first.map_,             second.map_);
    }

private:
#pragma mark ACCESSORS
    inline TElement       & ElementAt( Types::index index )       { ESSENTIAL_ASSERT( index < Size() ); return elementKeyPairs_[index].first; }
    inline TElement const & ElementAt( Types::index index ) const { ESSENTIAL_ASSERT( index < Size() ); return elementKeyPairs_[index].first; }
    inline TKey           &     KeyAt( Types::index index )       { ESSENTIAL_ASSERT( index < Size() ); return elementKeyPairs_[index].second; }
    inline TKey     const &     KeyAt( Types::index index ) const { ESSENTIAL_ASSERT( index < Size() ); return elementKeyPairs_[index].second; }

    inline Types::index  LeftChildIdOf( Types::index index ) const { return ( 2 * index + 1 ); }
    inline Types::index RightChildIdOf( Types::index index ) const { return ( 2 * index + 2 ); }
    inline bool            HasChildren( Types::index index ) const { return LeftChildIdOf(index) < Size(); }
    inline bool           HasLeftChild( Types::index index ) const { return LeftChildIdOf(index) < Size(); }
    inline bool          HasRightChild( Types::index index ) const { return RightChildIdOf(index) < Size(); }
    inline Types::index     ParentIdOf( Types::index index ) const { return floor( ( index - 1 ) / 2 ); }
    inline bool              HasParent( Types::index index ) const { return index > 0; }

    Types::index IndexOf(TElement const & element) const {
        return map_.at(element);
    }

    /**
     * @brief      The largest index of elements in the heap.
     *
     * @return     The largest index of elements in the heap.
     */
    Types::index MaximumIndex() const { return elementKeyPairs_.size() - 1; }

#pragma mark SIFTS

    /**
     * @brief      Sifts the last element in the heap up.
     *
     * @pre        The heap is not empty.
     */
    void SiftUp() {
        ESSENTIAL_ASSERT(!Empty());
        SiftUp(MaximumIndex());
    }

    /**
     * @brief      Sifts the element at @p index up.
     *
     * @pre        The index is valid.
     *
     * @param[in]  index  The index.
     */
    void SiftUp(Types::index index) {
        ESSENTIAL_ASSERT(index < Size());
        while (HasParent(index) && Comparator()( KeyAt(index), KeyAt(ParentIdOf(index)) )) {
            Types::index parentIndex = ParentIdOf(index);
            Swap(index, parentIndex);
            index = parentIndex;
        }
    }

    /**
     * @brief      Sifts the first element in the heap down.
     *
     * @pre        The heap is not empty.
     */
    void SiftDown() {
        ESSENTIAL_ASSERT(!Empty());
        SiftDown(0);
    }

    /**
     * @brief      Sifts the element at @p index down.
     *
     * @pre        The index is valid.
     *
     * @param[in]  index  The index.
     */
    void SiftDown(Types::index index) {
        ESSENTIAL_ASSERT(index < Size());
        while(HasChildren(index)) {
            Types::index childIndex = SelectSwappableChildAt(index);
            if (!Comparator()( KeyAt(childIndex), KeyAt(index) )) return;
            Swap(index, childIndex);
            index = childIndex;
        }
    }

#pragma mark SWAP

    /**
     * @brief      Swaps the elements and keys at the indices @p first and
     *             @p second and updates the mapping.
     *
     * @param[in]  first   The first index.
     * @param[in]  second  The second index.
     */
    void Swap(Types::index first, Types::index second) {
        using std::swap;
        swap(ElementAt(first), ElementAt(second));
        swap(KeyAt(first), KeyAt(second));

        map_[ElementAt(first)] = first;
        map_[ElementAt(second)] = second;
    }

    /**
     * @brief      Selects the smallest child, where smallest is measured according
     *             to the comparator.
     *
     * @param[in]  index  The current index.
     *
     * @return     The index of the child that has the smallest key.
     */
    inline Types::index SelectSwappableChildAt ( Types::index index ) const {
        ESSENTIAL_ASSERT( HasChildren(index) );
        if ( !HasRightChild(index) ) {
            return LeftChildIdOf( index );
        }

        ESSENTIAL_ASSERT( HasRightChild(index) );
        Types::index leftChildId = LeftChildIdOf(index);
        Types::index rightChildId = RightChildIdOf(index);
        if ( Comparator()( KeyAt(leftChildId), KeyAt(rightChildId) ) ) {
            return LeftChildIdOf( index );
        }
        return RightChildIdOf( index );
    }

#pragma mark HEAP_PROPERTY_METHODS
    /**
     * @brief      Whether the heap property is fulfilled.
     *
     * @return     @p true if the heap property is fulfilled, @p false otherwise.
     */
    bool ComplyHeapProperty() const {
        // We only need to check the indices until Size() / 2 because all other elements do
        // not have children.
        for (Types::index index = 0; index < Size() / 2; ++index) {
            if (!ComplyHeapProperty(index)) return false;
        }
        return true;
    }

    /**
     * @brief      Whether the element at position @p index is smaller than
     *             its childred.
     *
     * @param[in]  index  The index.
     *
     * @return     @p true if the element is smaller than all of its children,
     *             @p false otherwise.
     */
    bool ComplyHeapProperty(Types::index index) const {
        if (!HasChildren(index)) return true;
        if (Comparator()( KeyAt(LeftChildIdOf(index)), KeyAt(index) )) return false;
        if (!HasRightChild(index)) return true;
        return !Comparator()(KeyAt(RightChildIdOf(index)), KeyAt(index));
    }

    /**
     * @brief      Ensures that the heap property is satisfied.
     */
    void MakeHeapProperty() {
        for ( Types::rcount counter = Size() / 2 - 1;
              counter >= 0;
              --counter )
        {
            SiftDown( counter );
        }
        ESSENTIAL_ASSERT( ComplyHeapProperty() );
    }

#pragma mark MEMBERS
    /**
     * @brief Pairs of elements and their keys; ordered such that
     * the heap property is satisfied.
     */
    std::vector<std::pair<TElement, TKey>> elementKeyPairs_;
    /**
     * @brief The mapping from elements to indices in @p elementKeyPairs_
     */
    TMap map_;
    /**
     * @brief The comparator used to compare the keys.
     */
    TComparator comparator_;
};

} // namespace egoa



#endif // EGOA__DATA_STRUCTURES__CONTAINER__MAPPING_BINARY_HEAP_HPP

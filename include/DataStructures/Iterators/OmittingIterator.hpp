/*
 * OmittingIterator.hpp
 *
 *  Created on: May 13, 2019
 *      Author: Matthias Wolf
 */

#ifndef EGOA__DATA_STRUCTURES__ITERATORS__OMITTING_ITERATOR_HPP
#define EGOA__DATA_STRUCTURES__ITERATORS__OMITTING_ITERATOR_HPP

#include <iterator>

namespace egoa {

/**
 * @brief      An iterator that omits elements of a range if another
 *             range of @p bool indicates that the element is invalid.
 *
 * @tparam     ElementVectorIt  The type of the underlying element iterator.
 * @tparam     BoolVectorIt     The type of the underlying bool iterator.
 */
template <typename ElementVectorIt,
          typename BoolVectorIt>
class OmittingIterator {
public:
    using iterator_category = std::input_iterator_tag;
    using value_type = typename ElementVectorIt::value_type;
    using difference_type = Types::difference;
    using pointer = ElementVectorIt;
    using reference = typename ElementVectorIt::reference;

    /**
     * @brief      Constructs an omitting iterator.
     *
     * @param[in]  elementIterator  The element the iterator points to. It does not
     *                              have to be valid.
     * @param[in]  elementEnd       The @p end iterator for the range of elements.
     * @param[in]  existsIterator   The iterator referencing the @p bool indicating
     *                              whether the element referenced by @p elementIterator
     *                              is valid.
     */
    OmittingIterator(ElementVectorIt elementIterator,
                     ElementVectorIt elementEnd,
                     BoolVectorIt existsIterator)
    : elementIterator_(elementIterator),
      elementEnd_(elementEnd),
      existsIterator_(existsIterator) {
        if (elementIterator_ != elementEnd_ && !*existsIterator_) {
            GoToNextExistingElement();
        }
    }

    OmittingIterator & operator++() {
        GoToNextExistingElement();
        return *this;
    }
    OmittingIterator operator++(int) {
        OmittingIterator copy = *this;
        ++*this;
        return copy;
    }
    OmittingIterator & operator--() {
        GoToPreviousExistingElement();
        return *this;
    }
    OmittingIterator operator--(int) {
        OmittingIterator copy = *this;
        --*this;
        return copy;
    }
    reference operator*() {
        return *elementIterator_;
    }
    pointer operator->() {
        return elementIterator_;
    }
    friend bool operator==(const OmittingIterator & left, const OmittingIterator & right) {
        return left.elementIterator_ == right.elementIterator_;
    }
    friend bool operator!=(const OmittingIterator & left, const OmittingIterator & right) {
        return !(left == right);
    }
private:
    /**
     * @brief      Goes to the next existing element
     * @details    If no such element exists, it points to @p elementEnd_.
     */
    void GoToNextExistingElement() {
        do {
            ++elementIterator_;
            ++existsIterator_;
        } while (elementIterator_ != elementEnd_ && !*existsIterator_);
    }

    /**
     * @brief      Goes to the previous existing element
     * @details    If no such element exists, the behavior is undefined.
     */
    void GoToPreviousExistingElement() {
        do {
            --elementIterator_;
            --existsIterator_;
        } while (!*existsIterator_);
    }

    /**
     * @brief      The current element.
     * @details    After the constructor has finished either @p elementIterator_
     *             points to a valid element or to @p elementEnd_.
     */
    ElementVectorIt elementIterator_;
    /**
     * @brief      The iterator pointing behind the range of elements.
     */
    ElementVectorIt elementEnd_;
    /**
     * @brief      The iterator pointing to the @p bool corresponding to the
     *             element pointed to by @p elementIterator_.
     */
    BoolVectorIt    existsIterator_;
};

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__ITERATORS__OMITTING_ITERATOR_HPP

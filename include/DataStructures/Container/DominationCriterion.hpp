/*
 * DominationCriterion.hpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__CONTAINER__DOMINATION_CRITERION_HPP
#define EGOA__DATA_STRUCTURES__CONTAINER__DOMINATION_CRITERION_HPP

namespace egoa {

/**
 * @brief      Domination criterion.
 * @details    Classification of different possible dominations for different
 *     kinds of bucket usages, where
 *
 *     weak means either <= or >=,
 *     strict means either < or >, and
 *     none means no domination criterion, and thus no element filter.
 *
 *     The sign depends on the comparator.
 */
enum class DominationCriterion {
      weak   = 0
    , strict = 1
    , none   = 2
};

namespace internal {

/**
 * @brief      Class for domination differentiation.
 *
 * @code{.cpp}
 *      int lhs = 3;
 *      int rhs = 3;
 *      if ( DominationDifferentiation<int, DominationCriterion::weak>::Dominates(lhs, rhs, [](TElement a, TElement b) { return a < b; }) ) {
 *          std::cout << "The variable lhs dominates rhs in a weak sense." << std::endl;
 *      } else {
 *          std::cout << "The variable lhs does not dominate rhs in any sense." << std::endl;
 *      }
 *      if ( DominationDifferentiation<int, DominationCriterion::strict>::Dominates(lhs, rhs, [](TElement a, TElement b) { return a < b; }) ) {
 *          std::cout << "The variable lhs dominates rhs in a strong sense." << std::endl;
 *      } else {
 *          std::cout << "The variable lhs might dominate rhs in a weak sense." << std::endl;
 *      }
 * @endcode
 *
 * @tparam     ElementType  Type of the elements contained in the bucket.
 * @tparam     Domination   Classification of domination, e.g., weak, strict, or none.
 */
template<typename ElementType, DominationCriterion Domination>
class DominationDifferentiation;

#pragma mark WEAK_DOMINATION
template<typename ElementType>
class DominationDifferentiation<ElementType, DominationCriterion::weak> {
    // Type aliasing
    using TElement = ElementType;

    public:
        static inline bool Dominates ( TElement const & lhs
                                     , TElement const & rhs
                                     , std::function<bool(TElement, TElement)> const & comparator )
        {
            return comparator(lhs, rhs) || (lhs == rhs);
        }
};

#pragma mark STRICT_DOMINATION
template<typename ElementType>
class DominationDifferentiation<ElementType, DominationCriterion::strict> {
    // Type aliasing
    using TElement = ElementType;

    public:
        static inline bool Dominates ( TElement const & lhs
                                     , TElement const & rhs
                                     , std::function<bool(TElement, TElement)> const & comparator )
        {
            return comparator(lhs, rhs);
        }
};

#pragma mark NO_DOMINATION
template<typename ElementType>
class DominationDifferentiation<ElementType, DominationCriterion::none> {
    // Type aliasing
    using TElement = ElementType;

    public:
        static inline bool Dominates ( TElement const & lhs
                                     , TElement const & rhs
                                     , std::function<bool(TElement, TElement)> const & comparator )
        {
            return false;
        }
};

} // namespace internal

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__CONTAINER__DOMINATION_CRITERION_HPP


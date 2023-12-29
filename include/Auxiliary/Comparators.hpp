/*
 * Comparators.hpp
 *
 *  Created on: May 09, 2019
 *      Author: Matthias Wolf
 */

#ifndef EGOA__AUXILIARY__COMPARATORS_HPP
#define EGOA__AUXILIARY__COMPARATORS_HPP

#include "Auxiliary/Types.hpp"

namespace egoa {

/**
 * @brief      A comparator that compares based on elements in the vector.
 *
 * @tparam     WeightType  The type of the vector elements.
 * @tparam     ComparatorType Tye type of the underlying comparator that is used to compare
 *             the vector elements.
 */
template<typename WeightType, typename ComparatorType = std::less<WeightType>>
class VectorBasedComparator {
public:
    /**
     * @brief      The constructor.
     *
     * @param      weights     The weights.
     * @param[in]  comparator  The comparator.
     */
    VectorBasedComparator(std::vector<WeightType> const & weights,
                          ComparatorType comparator = std::less<WeightType>())
        : weights_(weights),
          comparator_(std::move(comparator))
    {}

    bool operator()(Types::index lhs, Types::index rhs) const
    {
        return comparator_(weights_[lhs], weights_[rhs]);
    }

private:
    std::vector<WeightType> const & weights_;
    ComparatorType                  comparator_;
};

} // namespace egoa

#endif // EGOA__AUXILIARY__COMPARATORS_HPP

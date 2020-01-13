/**
 * VectorView.hpp
 *
 *  Created on: May 8, 2019
 *      Author: Matthias Wolf
 */

#ifndef EGOA__DATA_STRUCTURES__VIEWS__VECTOR_VIEW_HPP
#define EGOA__DATA_STRUCTURES__VIEWS__VECTOR_VIEW_HPP

#include <ostream>

#include "Auxiliary/Types.hpp"

namespace egoa {

/**
 * @brief      Provides a restricted view on a vector.
 *
 * @tparam     ElementType  The types of the vector's elements
 * @tparam     Const        Whether the vector shall be treated as const.
 */
template<typename ElementType, bool Const>
class VectorView {
        using TElement = ElementType;
        using TVector  = typename std::conditional<Const,
                             std::vector<TElement> const,
                             std::vector<TElement>
                         >::type;
    public:
        using TIterator        = typename std::conditional<Const,
                                     typename TVector::const_iterator,
                                     typename TVector::iterator
                                 >::type;
        using TReverseIterator = typename std::conditional<Const,
                                     typename TVector::const_reverse_iterator,
                                     typename TVector::reverse_iterator
                                 >::type;
        using TReference       = typename std::conditional<Const,
                                     TElement const &,
                                     TElement &
                                 >::type;

        explicit VectorView(TVector * vector) : vector_(vector) {}

        TIterator        begin()  const noexcept { return vector_->begin();  }
        TIterator        end()    const noexcept { return vector_->end();    }
        TReverseIterator rbegin() const noexcept { return vector_->rbegin(); }
        TReverseIterator rend()   const noexcept { return vector_->rend();   }
        bool             empty()  const noexcept { return vector_->empty();  }
        Types::count     size()   const noexcept { return vector_->size();   }
        TReference       operator[](Types::index index) const { return (*vector_)[index]; }

    private:
        TVector * vector_;
};

/**
 * @brief      Prints a VectorView.
 *
 * @param      os           The output stream.
 * @param      view         The view.
 *
 * @return     @c os
 */
template<typename ElementType, bool Const>
inline std::ostream & operator<<(std::ostream & os,
                                 VectorView<ElementType, Const> const & view) {
    os << "[";
    auto first = view.begin();
    for (auto it = first; it != view.end(); ++it) {
        if (it != first) {
            os << ", ";
        }
        os << *it;
    }
    os << "]";
    return os;
}

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__VIEWS__VECTOR_VIEW_HPP

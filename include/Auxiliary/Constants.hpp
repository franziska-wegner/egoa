/*
 * Constants.hpp
 *
 *  Created on: Sep 07, 2018
 *      Author: Franziska Wegner
 */
#ifndef EGOA__AUXILIARY__CONSTANTS_HPP
#define EGOA__AUXILIARY__CONSTANTS_HPP

#define _USE_MATH_DEFINES
#include <cmath>

#include "Auxiliary/Types.hpp"
#ifdef GUROBI_AVAILABLE
    #include "gurobi_c++.h"
#endif

namespace egoa::Const {
/**@name Constants */
///@{
    constexpr Types::count  SEC_PER_DAY       = 24 * 60 * 60;
    constexpr Types::count  SEC_PER_MIN       = 60 * 60;
    // 1 ns (for nanosecond) correspond to 1,000,000,000 s (for seconds)
    constexpr Types::count  NSEC_PER_SEC      = 1000000000; // pow(10,9)
    // 1 ns (for nanosecond) correspond to 1,000,000 ms (for milliseconds)
    constexpr Types::count  NSEC_PER_MILLISEC = 1000000;
    constexpr Types::count  MILLISEC_PER_SEC  = 1000;

    constexpr Types::real   EPSILON    = std::numeric_limits<Types::real>::epsilon();
    constexpr Types::index  NONE       = std::numeric_limits<Types::posInteger>::max();
    constexpr Types::count  INFTY      = std::numeric_limits<Types::posInteger>::max();
    constexpr Types::real   REAL_INFTY = std::numeric_limits<Types::real>::max();

    constexpr Types::real   PI         = M_PI;
///@}
} // namespace egoa::Const

#endif // EGOA__AUXILIARY__CONSTANTS_HPP

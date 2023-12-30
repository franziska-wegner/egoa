/*
 * ContainerLoop.hpp
 *
 *  Created on: Mar 8, 2019
 *      Author: Matthias Wolf
 */

#ifndef EGOA__DATA_STRUCTURES__AUXILIARY__CONTAINER_LOOP_HPP
#define EGOA__DATA_STRUCTURES__AUXILIARY__CONTAINER_LOOP_HPP

#ifdef OPENMP_AVAILABLE
    #include <omp.h>
#endif

#include <algorithm>

#include "Auxiliary/ExecutionPolicy.hpp"
#include "Auxiliary/Types.hpp"

namespace egoa::internal {

/**
 * @brief      Loops over containers.
 *
 * @tparam     Policy  The execution policy.
 */
template<ExecutionPolicy Policy>
struct ContainerLoop;

/**
 * @brief      Sequential loop over all elements in the container.
 */
template<>
struct ContainerLoop<ExecutionPolicy::sequential> {

    /**
     * @brief      Sequential loop over all elements in the container.
     * @details    Equivalent to `std::for_each`.
     *
     * @param      container  The container.
     * @param[in]  function   The function to call for all elements in @ container.
     *
     * @tparam     Container  The type of the container.
     * @tparam     FUNCTION   The type of the function object.
     */
    template<typename Container, typename FUNCTION>
    static void for_each ( Container const & container, FUNCTION function )
    {
        using std::begin, std::end;
        std::for_each(begin(container), end(container), function);
    }
};

/**
 * @brief      Breakable loop over all elements in the container.
 */
template<>
struct ContainerLoop<ExecutionPolicy::breakable> {

    /**
     * @brief      Breakable loop over all elements in the container.
     *
     * @param      container  The container.
     * @param[in]  function   The function to call for all elements in @ container.
     *
     * @tparam     Container  The type of the container.
     * @tparam     FUNCTION   The type of the function object.
     */
    template<typename Container, typename FUNCTION>
    static void for_each ( Container const & container, FUNCTION function )
    {
        using std::begin, std::end;

        bool toContinue = true;
        auto last = end(container);
        for ( auto it = begin(container)
            ; toContinue && it != last
            ; ++it )
        {
            toContinue = function(*it);
        }
    }
};

#ifdef OPENMP_AVAILABLE

/**
 * @brief      Parallel loop over all elements in the container.
 */
template<>
struct ContainerLoop<ExecutionPolicy::parallel> {

    /**
     * @brief      Parallel loop over all elements in the container.
     *
     * @param      container  The container.
     * @param[in]  function   The function to call for all elements in @ container.
     *
     * @tparam     Container  The type of the container.
     * @tparam     FUNCTION   The type of the function object.
     */
    template<typename Container, typename FUNCTION>
    static void for_each ( Container const & container, FUNCTION function )
    {
        #pragma omp parallel for
        for ( Types::index i = 0
            ; i < container.size()
            ; ++i )
        {
            function(container[i]);
        }
    }
};

#else // OPENMP_AVAILABLE
/**
 * @brief      If OpenMP is not available, the sequential loops are used.
 */
template<>
struct ContainerLoop<ExecutionPolicy::parallel>
    : public ContainerLoop<ExecutionPolicy::sequential> {};

#endif // OPENMP_AVAILABLE

} // namespace egoa::internal

#endif // EGOA__DATA_STRUCTURES__AUXILIARY__CONTAINER_LOOP_HPP

/*
 * ExecutionPolicy.hpp
 *
 *  Created on: Mar 1, 2019
 *      Author: Matthias Wolf
 */
#ifndef EGOA__AUXILIARY__EXECUTION_POLICY_HPP
#define EGOA__AUXILIARY__EXECUTION_POLICY_HPP

namespace egoa {

/**
 * @brief      Execution policies for @p for loops
 */
enum class ExecutionPolicy {
    /**
     * The loop is run sequentially.
     */
    sequential,
    /**
     * The loop is run in parallel using OpenMP.
     */
    parallel,
    /**
     * The loop is run sequentially until the function returns @p false.
     */
    breakable
};

}

#endif // EGOA__AUXILIARY__EXECUTION_POLICY_HPP

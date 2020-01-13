/*
 * EmptyCallback.hpp
 *
 *  Created on: May 21, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__MATHEMATICAL_MODEL__CALLBACKS__EMPTY_CALLBACK_HPP
#define EGOA__MATHEMATICAL_MODEL__CALLBACKS__EMPTY_CALLBACK_HPP

#include "gurobi_c++.h"
// #include "MathematicalModel/Solver/GurobiSolver.hpp"

namespace egoa {

template<typename CallbackType>
class GurobiSolver;

template<typename LoggingType>
class CallbackEmpty : public GRBCallback {
    public:
        using TLogging = LoggingType;
        using TSolver  = GurobiSolver<CallbackEmpty<TLogging>>;

        /**
         * @brief      Constructs the object.
         *
         * @param      solver  The solver
         */
        CallbackEmpty (TSolver *solver) // @todo not a perfect solution
        :   solver_(solver) {}
    private:
        /**
         * @brief      Do nothing
         */
        void callback() override {
            return;
        }
    private:
        TSolver * solver_;
};  

} // namespace egoa

#endif // EGOA__MATHEMATICAL_MODEL__CALLBACKS__EMPTY_CALLBACK_HPP
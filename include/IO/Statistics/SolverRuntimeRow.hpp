/*
 * SolverRuntimeRow.hpp
 *
 *  Created on: Jan 29, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__IO__STATISTICS__GUROBI_INFO_HPP
#define EGOA__IO__STATISTICS__GUROBI_INFO_HPP

#include "Auxiliary/Types.hpp"

#include <iostream>
#include <vector>

namespace egoa::IO {

    /**
     * @brief      A struct representing one row of the statistics for mathematical models.
     *
     * @see        GurobiRuntimeCollection A collection of @c SolverRuntimeRow objects
     */
    struct SolverRuntimeRow {

        Types::name     NameOfProblem;          /**< Problem solved */
        Types::name     Name;                   /**< Name of the instance */

        Types::count    NumberOfVertices;       /**< Number of vertices */
        Types::count    NumberOfEdges;          /**< Number of edges */

        Types::real     Solution;               /**< Current solution's cost */
        Types::real     OptimizationRuntimeSeconds; /**< Current time in the whole gurobi program */
        Types::real     BuildingRuntimeSeconds; /**< Current time in the whole gurobi program */

        Types::string   Status;                 /**< Gurobi solution status; see https://www.gurobi.com/documentation/8.0/refman/optimization_status_codes.html#sec:StatusCodes */
        Types::real     MipGap;                 /**< MIP gap in % */
        Types::real     UpperBound;             /**< Upper bound */
        Types::real     LowerBound;             /**< Lower bound */
        Types::count    NumberOfVariables;      /**< Number of variables */
        Types::count    NumberOfConstraints;    /**< Number of variables */
        Types::count    NumberOfSoS;            /**< Number of variables */
        Types::count    NumberOfQConstrains;    /**< Number of variables */
        Types::count    NumberOfGenConstrains;  /**< Number of variables */
        Types::count    NumberOfNZs;            /**< Number of variables */
        Types::count    NumberOfIntVars;        /**< Number of variables */
        Types::count    NumberOfBinaryVars;     /**< Number of variables */

        SolverRuntimeRow() :
            NameOfProblem(""),
            Name(""),

            NumberOfVertices(0),
            NumberOfEdges(0),

            Solution(0.0),
            OptimizationRuntimeSeconds(0.0),
            BuildingRuntimeSeconds(0.0),

            Status("unknown"),

            MipGap(0.0),
            UpperBound(0.0),
            LowerBound(0.0),
            NumberOfVariables(0),
            NumberOfConstraints(0),
            NumberOfSoS(0),
            NumberOfQConstrains(0),
            NumberOfGenConstrains(0),
            NumberOfNZs(0),
            NumberOfIntVars(0),
            NumberOfBinaryVars(0)
            {}

        inline static void Header ( std::ostream & os ) {
            os
                << "NameOfProblem"              << ",\t"
                << "Name"                       << ",\t"

                << "NumberOfVertices"           << ",\t"
                << "NumberOfEdges"              << ",\t"

                << "Solution"                   << ",\t"
                << "OptimizationRuntimeSeconds" << ",\t"
                << "BuildingRuntimeSeconds"     << ",\t"

                << "Status"                     << ",\t"
                << "MipGap"                     << ",\t"
                << "UpperBound"                 << ",\t"
                << "LowerBound"                 << ",\t"
                << "NumberOfVariables"          << ",\t"
                << "NumberOfConstraints"        << ",\t"
                << "NumberOfSoS"                << ",\t"
                << "NumberOfQConstrains"        << ",\t"
                << "NumberOfGenConstrains"      << ",\t"
                << "NumberOfNZs"                << ",\t"
                << "NumberOfIntVars"            << ",\t"
                << "NumberOfBinaryVars"         << ""

                << std::endl;
        }

        inline void Content ( std::ostream & os ) const {
            os
                << NameOfProblem                << ",\t"
                << Name                         << ",\t"

                << NumberOfVertices             << ",\t"
                << NumberOfEdges                << ",\t"

                << Solution                     << ",\t"
                << OptimizationRuntimeSeconds   << ",\t"
                << BuildingRuntimeSeconds       << ",\t"

                << Status                       << ",\t"
                << MipGap                       << ",\t"
                << UpperBound                   << ",\t"
                << LowerBound                   << ",\t"
                << NumberOfVariables            << ",\t"
                << NumberOfConstraints          << ",\t"
                << NumberOfSoS                  << ",\t"
                << NumberOfQConstrains          << ",\t"
                << NumberOfGenConstrains        << ",\t"
                << NumberOfNZs                  << ",\t"
                << NumberOfIntVars              << ",\t"
                << NumberOfBinaryVars           << ""

                << std::endl;
        }

        inline SolverRuntimeRow& operator+= ( const SolverRuntimeRow &rhs ) {
            Solution                    += rhs.Solution;
            OptimizationRuntimeSeconds  += rhs.OptimizationRuntimeSeconds;
            BuildingRuntimeSeconds      += rhs.BuildingRuntimeSeconds;

            MipGap                      += rhs.MipGap;
            UpperBound                  += rhs.UpperBound;
            LowerBound                  += rhs.LowerBound;
            NumberOfVariables           += rhs.NumberOfVariables;
            NumberOfConstraints         += rhs.NumberOfConstraints;
            NumberOfSoS                 += rhs.NumberOfSoS;
            NumberOfQConstrains         += rhs.NumberOfQConstrains;
            NumberOfGenConstrains       += rhs.NumberOfGenConstrains;
            NumberOfNZs                 += rhs.NumberOfNZs;
            NumberOfIntVars             += rhs.NumberOfIntVars;
            NumberOfBinaryVars          += rhs.NumberOfBinaryVars;

            return *this;
        }

        inline SolverRuntimeRow& operator/= ( int rhs ) {
            Solution                    /= rhs;
            OptimizationRuntimeSeconds  /= rhs;
            BuildingRuntimeSeconds      /= rhs;

            MipGap                      /= rhs;
            UpperBound                  /= rhs;
            LowerBound                  /= rhs;
            NumberOfVariables           /= rhs;
            NumberOfConstraints         /= rhs;
            NumberOfSoS                 /= rhs;
            NumberOfQConstrains         /= rhs;
            NumberOfGenConstrains       /= rhs;
            NumberOfNZs                 /= rhs;
            NumberOfIntVars             /= rhs;
            NumberOfBinaryVars          /= rhs;

            return *this;
        }

        inline void Min(const SolverRuntimeRow &rhs) {
            Solution                  = std::min( Solution,                    rhs.Solution            );
            OptimizationRuntimeSeconds= std::min( OptimizationRuntimeSeconds,  rhs.OptimizationRuntimeSeconds);

            MipGap                    = std::min( MipGap,                      rhs.MipGap              );
            UpperBound                = std::min( UpperBound,                  rhs.UpperBound          );
            LowerBound                = std::min( LowerBound,                  rhs.LowerBound          );
            NumberOfVariables         = std::min( NumberOfVariables,           rhs.NumberOfVariables   );
            NumberOfConstraints       = std::min( NumberOfConstraints,         rhs.NumberOfConstraints  );
            NumberOfSoS               = std::min( NumberOfSoS,                 rhs.NumberOfSoS          );
            NumberOfQConstrains       = std::min( NumberOfQConstrains,         rhs.NumberOfQConstrains  );
            NumberOfGenConstrains     = std::min( NumberOfGenConstrains,       rhs.NumberOfGenConstrains);
            NumberOfNZs               = std::min( NumberOfNZs,                 rhs.NumberOfNZs          );
            NumberOfIntVars           = std::min( NumberOfIntVars,             rhs.NumberOfIntVars      );
            NumberOfBinaryVars        = std::min( NumberOfBinaryVars,          rhs.NumberOfBinaryVars   );
        }

        inline void Max(const SolverRuntimeRow &rhs) {
            Solution                  = std::max( Solution,                    rhs.Solution            );
            OptimizationRuntimeSeconds= std::max( OptimizationRuntimeSeconds,  rhs.OptimizationRuntimeSeconds);

            MipGap                    = std::max( MipGap,                      rhs.MipGap              );
            UpperBound                = std::max( UpperBound,                  rhs.UpperBound          );
            LowerBound                = std::max( LowerBound,                  rhs.LowerBound          );
            NumberOfVariables         = std::max( NumberOfVariables,           rhs.NumberOfVariables   );
            NumberOfConstraints       = std::max( NumberOfConstraints,         rhs.NumberOfConstraints  );
            NumberOfSoS               = std::max( NumberOfSoS,                 rhs.NumberOfSoS          );
            NumberOfQConstrains       = std::max( NumberOfQConstrains,         rhs.NumberOfQConstrains  );
            NumberOfGenConstrains     = std::max( NumberOfGenConstrains,       rhs.NumberOfGenConstrains);
            NumberOfNZs               = std::max( NumberOfNZs,                 rhs.NumberOfNZs          );
            NumberOfIntVars           = std::max( NumberOfIntVars,             rhs.NumberOfIntVars      );
            NumberOfBinaryVars        = std::max( NumberOfBinaryVars,          rhs.NumberOfBinaryVars   );
        }
};

} // namespace egoa::IO

#endif // EGOA__IO__STATISTICS__GUROBI_INFO_HPP

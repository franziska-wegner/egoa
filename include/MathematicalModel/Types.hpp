/*
 * Types.hpp
 *
 *  Created on: May 14, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__MATHEMATICAL_MODEL__TYPE_HPP
#define EGOA__MATHEMATICAL_MODEL__TYPE_HPP

#include "Exceptions/Assertions.hpp"

// include only if cplex is available
#ifdef CPLEX_AVAILABLE
    #include <ilconcert/iloexpression.h>
    #include <ilcplex/ilocplexi.h>
#endif

// include only if Gurobi is available
#ifdef GUROBI_AVAILABLE
    #include "gurobi_c++.h"
#endif


namespace egoa::Solvers {

#pragma mark SOLVER_TYPES

/**
 * @brief      Class for solver status.
 */
enum class Status {
      loaded                = 0    /**<  */
    , feasible              = 1    /**<  */
    , optimal               = 2    /**<  */
    , infeasible            = 3    /**<  */
    , inf_or_unb            = 4    /**<  */
    , unbounded             = 5    /**<  */
    , cutoff                = 6    /**<  */
    , iteration_limit       = 7    /**<  */
    , node_limit            = 8    /**<  */
    , time_limit            = 9    /**<  */
    , solution_limit        = 10   /**<  */
    , interrupted           = 11   /**<  */
    , numeric               = 12   /**<  */
    , suboptimal            = 13   /**<  */
    , inprogress            = 14   /**<  */
    , user_obj_limit        = 15   /**<  */
    , error                 = 16   /**<  */
    , unknown               = 99   /**<  */
};

enum class VariableType {
      continuous        = 0    /**<  */
    , semicontinuous    = 1    /**<  */
    , binary            = 2    /**<  */
    , integer           = 3    /**<  */
    , semiinteger       = 4    /**<  */
    , unknown           = 99   /**<  */
};

enum class ObjectiveSense {
      minimize          = 0    /**< Minimize the objective, default */
    , maximize          = 1    /**< Maximize the objective */
    , unknown           = 99   /**< Unknown */
};


enum class Algorithm { 
    automatical     = 0
    , primal        = 1
    , dual          = 2
    , network       = 3
    , barrier       = 4
    , sifting       = 5
    , concurrent    = 6
    , feasOpt       = 7
    , mip           = 8
    , unknown       = 99
};

enum class NodeFileStrategy {
    standard             = 0
    , inMemoryCompressed = 1
    , onDisk             = 2
    , onDiskCompressed   = 3
    , unknown            = 99
};

#pragma mark OBJECTIVE_SENSE_CONVERSION

inline ObjectiveSense GurobiToObjectiveSense ( Types::integer const modelSense )
{
    if ( 1 == modelSense ) {
        return ObjectiveSense::minimize;
    } else if ( -1 == modelSense ) {
        return ObjectiveSense::maximize;
    } else {
        return ObjectiveSense::unknown;
    }
}

inline Types::integer ObjectiveSenseToGurobi ( ObjectiveSense const & modelSense )
{
    if ( ObjectiveSense::minimize == modelSense ) {
        return 1;
    } else if ( ObjectiveSense::maximize == modelSense ) {
        return -1;
    } else {
        return 1;
    }
}

#ifdef CPLEX_AVAILABLE
//https://www.ibm.com/support/knowledgecenter/SS9UKU_12.6.0/com.ibm.cplex.zos.help/refcppcplex/html/enumerations/IloObjective_Sense.html
inline ObjectiveSense CplexToObjectiveSense ( Types::integer const modelSense )
{
    if ( 1 == modelSense ) {
        return ObjectiveSense::minimize;
    } else if ( -1 == modelSense ) {
        return ObjectiveSense::maximize;
    } else {
        return ObjectiveSense::unknown;
    }
}

inline Types::integer ObjectiveSenseToCplex ( ObjectiveSense const & modelSense )
{
    if ( ObjectiveSense::minimize == modelSense ) {
        return 1;
    } else if ( ObjectiveSense::maximize == modelSense ) {
        return -1;
    } else {
        return 1;
    }
}
#endif // CPLEX_AVAILABLE

#pragma mark VARIABLE_TYPE_CONVERSION

#ifdef GUROBI_AVAILABLE

inline VariableType GurobiToVariableType ( char const variableType )
{
    if ( GRB_CONTINUOUS      == variableType ) { // "C"
        return VariableType::continuous;
    } else if ( GRB_SEMICONT == variableType ) {
        return VariableType::semicontinuous;
    } else if ( GRB_BINARY   == variableType ) { // "B"
        return VariableType::binary;
    } else if ( GRB_INTEGER  == variableType ) {
        return VariableType::integer;
    } else if ( GRB_SEMIINT  == variableType ) {
        return VariableType::semiinteger;
    } else {
        return VariableType::unknown;
    }
}

inline char VariableTypeToGurobi ( VariableType const & variableType )
{
    if ( VariableType::continuous       == variableType ) {
        return GRB_CONTINUOUS;
    } else if ( VariableType::semicontinuous == variableType ) {
        return GRB_SEMICONT;
    } else if ( VariableType::binary    == variableType ) {
        return GRB_BINARY;
    } else if ( VariableType::integer   == variableType ) {
        return GRB_INTEGER;
    } else if ( VariableType::semiinteger  == variableType ) {
        return GRB_SEMIINT;
    } else {
        USAGE_ASSERT(false && "Unknown Variable Type");
    }
}
#endif // GUROBI_AVAILABLE

#ifdef CPLEX_AVAILABLE

// https://www.ibm.com/support/knowledgecenter/SS9UKU_12.6.0/com.ibm.cplex.zos.help/refcppcplex/html/enumerations/IloNumVar_Type.html
inline VariableType CplexToVariableType ( IloNumVar::Type variableType )
{
    if ( ILOFLOAT       == variableType ) {
        return VariableType::continuous;
    } else if ( ILOBOOL == variableType ) {
        return VariableType::binary;
    } else if ( ILOINT  == variableType ) {
        return VariableType::integer;
    } else {
        return VariableType::unknown;
    }
}

// https://www.ibm.com/support/knowledgecenter/SS9UKU_12.6.0/com.ibm.cplex.zos.help/refcppcplex/html/enumerations/IloNumVar_Type.html
inline IloNumVar::Type VariableTypeToCplex ( VariableType const & variableType )
{
    if ( VariableType::continuous       == variableType ) {
        return ILOFLOAT;
    } else if ( VariableType::semicontinuous == variableType ) {
        USAGE_ASSERT(false && "Semi-continuous does not exist as cplex type");
    } else if ( VariableType::binary    == variableType ) {
        return ILOBOOL;
    } else if ( VariableType::integer   == variableType ) {
        return ILOINT;
    } else if ( VariableType::semiinteger  == variableType ) {
        USAGE_ASSERT(false && "Semi-integer does not exist as cplex type");
    } else {
        USAGE_ASSERT(false && "Unknown Variable Type");
    }
}

#endif // CPLEX_AVAILABLE

#pragma mark SOLVER_STATUS_CONVERSION

inline Types::string SolverStatusToString ( Status const & status )
{
    if ( Status::loaded                   == status ) {
        return "loaded";
    } else if ( Status::optimal           == status ) {
        return "optimal";
    } else if ( Status::infeasible        == status ) {
        return "infeasible";
    } else if ( Status::inf_or_unb        == status ) {
        return "inf_or_unb";
    } else if ( Status::unbounded == status ) {
        return "unbounded";
    } else if ( Status::cutoff            == status ) {
        return "cutoff";
    } else if ( Status::iteration_limit   == status ) {
        return "iteration_limit";
    } else if ( Status::node_limit        == status ) {
        return "node_limit";
    } else if ( Status::time_limit        == status ) {
        return "time_limit";
    } else if ( Status::solution_limit    == status ) {
        return "solution_limit";
    } else if ( Status::interrupted       == status ) {
        return "interrupted";
    } else if ( Status::numeric           == status ) {
        return "numeric";
    } else if ( Status::suboptimal        == status ) {
        return "suboptimal";
    } else if ( Status::inprogress        == status ) {
        return "inprogress";
    } else if ( Status::user_obj_limit    == status ) {
        return "user_obj_limit";
    } else {
        return "unknown";
    }
}

inline Status StringToSolverStatus ( Types::string const & status )
{
    if ( "loaded"                   == status ) {
        return Status::loaded;
    } else if ( "optimal"           == status ) {
        return Status::optimal;
    } else if ( "infeasible"        == status ) {
        return Status::infeasible;
    } else if ( "inf_or_unb"        == status ) {
        return Status::inf_or_unb;
    } else if ( "unbounded"         == status ) {
        return Status::unbounded;
    } else if ( "cutoff"            == status ) {
        return Status::cutoff;
    } else if ( "iteration_limit"   == status ) {
        return Status::iteration_limit;
    } else if ( "node_limit"        == status ) {
        return Status::node_limit;
    } else if ( "time_limit"        == status ) {
        return Status::time_limit;
    } else if ( "solution_limit"    == status ) {
        return Status::solution_limit;
    } else if ( "interrupted"       == status ) {
        return Status::interrupted;
    } else if ( "numeric"           == status ) {
        return Status::numeric;
    } else if ( "suboptimal"        == status ) {
        return Status::suboptimal;
    } else if ( "inprogress"        == status ) {
        return Status::inprogress;
    } else if ( "user_obj_limit"    == status ) {
        return Status::user_obj_limit;
    } else {
        return Status::unknown;
    }
}

#ifdef GUROBI_AVAILABLE

inline Status GurobiToSolverStatus ( Types::count const & status )
{
    if ( GRB_LOADED == status ) {
        return Status::loaded;
    } else if ( GRB_OPTIMAL         == status ) { // 2
        return Status::optimal;
    } else if ( GRB_INFEASIBLE      == status ) { // 3
        return Status::infeasible;
    } else if ( GRB_INF_OR_UNBD     == status ) { // 4
        return Status::inf_or_unb;
    } else if ( GRB_UNBOUNDED       == status ) { // 5
        return Status::unbounded;
    } else if ( GRB_CUTOFF          == status ) { // 6
        return Status::cutoff;
    } else if ( GRB_ITERATION_LIMIT == status ) { // 7
        return Status::iteration_limit;
    } else if ( GRB_NODE_LIMIT      == status ) { // 8
        return Status::node_limit;
    } else if ( GRB_TIME_LIMIT      == status ) { // 9
        return Status::time_limit;
    } else if ( GRB_SOLUTION_LIMIT  == status ) { // 10
        return Status::solution_limit;
    } else if ( GRB_INTERRUPTED     == status ) { // 11
        return Status::interrupted;
    } else if ( GRB_NUMERIC         == status ) { // 12
        return Status::numeric;
    } else if ( GRB_SUBOPTIMAL      == status ) { // 13
        return Status::suboptimal;
    } else if ( GRB_INPROGRESS      == status ) { // 14
        return Status::inprogress;
    } else if ( GRB_USER_OBJ_LIMIT  == status ) { // 15
        return Status::user_obj_limit;
    } else {
        return Status::unknown;
    }
}
#endif // GUROBI_AVAILABLE

#ifdef CPLEX_AVAILABLE
//https://www.ibm.com/support/knowledgecenter/SS9UKU_12.6.0/com.ibm.cplex.zos.help/refcppcplex/html/enumerations/IloAlgorithm_Status.html
inline Status CplexToSolverStatus ( IloAlgorithm::Status const & status )
{
    if ( IloAlgorithm::Status::Feasible                     == status ) {
        return Status::feasible;
    } else if ( IloAlgorithm::Status::Optimal               == status ) { 
        return Status::optimal;
    } else if ( IloAlgorithm::Status::Infeasible            == status ) { 
        return Status::infeasible;
    } else if ( IloAlgorithm::Status::InfeasibleOrUnbounded == status ) { 
        return Status::inf_or_unb;
    } else if ( IloAlgorithm::Status::Unbounded             == status ) { 
        return Status::unbounded;
    } else if ( IloAlgorithm::Status::Error                 == status ) { 
        return Status::error;
    } else if ( IloAlgorithm::Status::Unknown               == status ) { 
        return Status::unknown;
    } else {
        return Status::unknown;
    }
}
#endif // CPLEX_AVAILABLE

#pragma mark ALGORITHM_CONVERSION

#ifdef CPLEX_AVAILABLE
// https://www.ibm.com/support/knowledgecenter/SSSA5P_12.8.0/ilog.odms.cplex.help/refcppcplex/html/classes/IloCplex.html
inline Algorithm CplexToAlgorithm ( IloCplex::Algorithm const algorithm )
{
    if ( IloCplex::Auto                 == static_cast<IloCplex::WriteLevelType>( algorithm ) ) {
        return Algorithm::automatical;
    } else if ( IloCplex::Primal        == algorithm ) {
        return Algorithm::primal;
    } else if ( IloCplex::Dual          == algorithm ) {
        return Algorithm::dual;
    } else if ( IloCplex::Network       == algorithm ) {
        return Algorithm::network;
    } else if ( IloCplex::Barrier       == algorithm ) {
        return Algorithm::barrier;
    } else if ( IloCplex::Sifting       == algorithm ) {
        return Algorithm::sifting;
    } else if ( IloCplex::Concurrent    == algorithm ) {
        return Algorithm::concurrent;
    } else if ( IloCplex::FeasOpt       == algorithm ) {
        return Algorithm::feasOpt;
    } else if ( IloCplex::MIP           == algorithm ) {
        return Algorithm::mip;
    } else {
        return Algorithm::unknown;
    }
}

inline IloCplex::Algorithm AlgorithmToCplex ( Algorithm const & algorithm )
{
    if ( Algorithm::automatical         == algorithm ) {
        return static_cast<IloCplex::Algorithm>( IloCplex::Auto );
    } else if ( Algorithm::primal       == algorithm ) {
        return IloCplex::Primal;
    } else if ( Algorithm::dual         == algorithm ) {
        return IloCplex::Dual;
    } else if ( Algorithm::network      == algorithm ) {
        return IloCplex::Network;
    } else if ( Algorithm::barrier      == algorithm ) {
        return IloCplex::Barrier;
    } else if ( Algorithm::sifting      == algorithm ) {
        return IloCplex::Sifting;
    } else if ( Algorithm::concurrent   == algorithm ) {
        return IloCplex::Concurrent;
    } else if ( Algorithm::feasOpt      == algorithm ) {
        return IloCplex::FeasOpt;
    } else if ( Algorithm::mip          == algorithm ) {
        return IloCplex::MIP;
    } else {
        return static_cast<IloCplex::Algorithm>( IloCplex::Auto );
    }
}
#endif // CPLEX_AVAILABLE

#pragma mark NODE_FILE_STRATEGY_CONVERSION

inline Types::count NodeFileStrategyToInteger ( NodeFileStrategy const & strategy )
{
    if ( NodeFileStrategy::standard == strategy ) {
        return 0;
    } else if ( NodeFileStrategy::inMemoryCompressed == strategy ) {
        return 1;
    } else if ( NodeFileStrategy::onDisk             == strategy ) {
        return 2;
    } else if ( NodeFileStrategy::onDiskCompressed   == strategy ) {
        return 3;
    } else {
        USAGE_ASSERT(false && "Node File Strategy does not exist");
    }
}

#pragma mark ILO_BOOLEAN_CONVERSION

#ifdef CPLEX_AVAILABLE
/**
 * @brief      Conversion from IloBool to bool.
 *
 * @param      boolean  The IloBool boolean type.
 *
 * @see        https://www.ibm.com/support/knowledgecenter/SSSA5P_12.6.1/ilog.odms.ide.help/refcppopl/html/typedefs/IloBool.html
 * 
 * @return     Returns @p true for IloTrue, otherwise @p false.
 */
inline bool IloBoolToBoolean ( IloBool const & boolean )
{
    if ( IloTrue == boolean ) { return true; }
    else if ( IloFalse == boolean ) { return false; }
    else { USAGE_ASSERT ( false && "IloBool does not exist" ) }
}
#endif // CPLEX_AVAILABLE

#pragma mark OUTPUT_OPERATOR

inline std::ostream & operator<<( std::ostream & os, const Status & rhs ) 
{
    if      ( rhs == Status::loaded         ) { os << "loaded";    } 
    else if ( rhs == Status::optimal        ) { os << "optimal";   } 
    else if ( rhs == Status::infeasible     ) { os << "infeasible"; } 
    else if ( rhs == Status::inf_or_unb     ) { os << "inf_or_unb";} 
    else if ( rhs == Status::unbounded      ) { os << "unbounded";      } 
    else if ( rhs == Status::cutoff         ) { os << "cutoff"; } 
    else if ( rhs == Status::iteration_limit) { os << "iteration_limit"; } 
    else if ( rhs == Status::node_limit     ) { os << "node_limit"; } 
    else if ( rhs == Status::time_limit     ) { os << "time_limit"; } 
    else if ( rhs == Status::solution_limit ) { os << "solution_limit"; } 
    else if ( rhs == Status::interrupted    ) { os << "interrupted"; } 
    else if ( rhs == Status::numeric        ) { os << "numeric"; } 
    else if ( rhs == Status::suboptimal     ) { os << "suboptimal"; } 
    else if ( rhs == Status::inprogress     ) { os << "inprogress"; } 
    else if ( rhs == Status::user_obj_limit ) { os << "user_obj_limit"; } 
    else                                      { os << "unknown";    }
    return os;
}    

inline std::ostream & operator<<( std::ostream & os, VariableType const & rhs ) 
{
    if      ( rhs == VariableType::continuous       ) { os << "continuous";    } 
    else if ( rhs == VariableType::semicontinuous   ) { os << "semicontinuous";   } 
    else if ( rhs == VariableType::binary           ) { os << "binary"; } 
    else if ( rhs == VariableType::integer          ) { os << "integer";} 
    else if ( rhs == VariableType::semiinteger      ) { os << "semiinteger";      } 
    else                                              { os << "unknown";    }
    return os;
}    


inline std::ostream & operator<<( std::ostream & os, ObjectiveSense const & rhs ) 
{
    if      ( rhs == ObjectiveSense::minimize   ) { os << "minimize";   } 
    else if ( rhs == ObjectiveSense::maximize   ) { os << "maximize";   } 
    else                                          { os << "unknown";    }
    return os;
}

inline std::ostream & operator<<( std::ostream & os, Algorithm const & rhs ) 
{
    if      ( rhs == Algorithm::automatical   ) { os << "Auto";         } 
    else if ( rhs == Algorithm::primal        ) { os << "Primal";       } 
    else if ( rhs == Algorithm::dual          ) { os << "Dual";         } 
    else if ( rhs == Algorithm::network       ) { os << "Network";      } 
    else if ( rhs == Algorithm::barrier       ) { os << "Barrier";      } 
    else if ( rhs == Algorithm::sifting       ) { os << "Sifting";      } 
    else if ( rhs == Algorithm::concurrent    ) { os << "Concurrent";   } 
    else if ( rhs == Algorithm::feasOpt       ) { os << "FeasOpt";      } 
    else if ( rhs == Algorithm::mip           ) { os << "MIP";          } 
    else                                        { os << "None";         }
    return os;
}

} // namespace egoa::Solver

#endif // EGOA__MATHEMATICAL_MODEL__TYPE_HPP
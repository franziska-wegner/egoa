/*
 * Type.hpp
 *
 *  Created on: May 22, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__TYPE_HPP
#define EGOA__DATA_STRUCTURES__TYPE_HPP

#include "Auxiliary/Types.hpp"
#include "DataStructures/Graphs/Vertices/Type.hpp"

namespace egoa {

///@name Power grid conversion methods
///@{
#pragma mark POWER_GRID_CONVERSION_METHODS
    inline Types::string BoundTypeToString ( Vertices::BoundType const & boundType )
    { 
        if ( Vertices::BoundType::exact              == boundType ) return "exact"; 
        else if ( Vertices::BoundType::bounded       == boundType ) return "bounded"; 
        else if ( Vertices::BoundType::unbounded     == boundType ) return "unbounded";
        else if ( Vertices::BoundType::pureunbounded == boundType ) return "pureunbounded" ;
        return "unknown";
    }
///@}

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__TYPE_HPP
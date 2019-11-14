/* 
 * DataValidation.hpp
 *
 *  Created on: May 09, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__IO__HELPER__DATA_VALIDATION_HPP
#define EGOA__IO__HELPER__DATA_VALIDATION_HPP

#include "Auxiliary/ExecutionPolicy.hpp"

namespace egoa::IO::Helper {

    template<typename TGraph>
    inline bool HasGraphCorrectBounds ( TGraph const & graph )
    {
        using TVertex               = typename TGraph::TVertex;
        using TEdge                 = typename TGraph::TEdge;

        bool hasCorrectBound = true;
        // Check voltage bounds
        graph.template for_all_vertices<ExecutionPolicy::sequential>( 
            [&hasCorrectBound]( TVertex const & vertex ) 
        {
            USAGE_ASSERT ( vertex.Properties().MinimumVoltage() 
                        <= vertex.Properties().MaximumVoltage() );
            if ( vertex.Properties().MinimumVoltage() 
               > vertex.Properties().MaximumVoltage() ) 
            {
                hasCorrectBound = false;
            }
        });
        
        graph.template for_all_edges<ExecutionPolicy::sequential> ( 
            [&hasCorrectBound]( TEdge const & edge ) 
        {
            // thetaBound
            USAGE_ASSERT ( edge.Properties().ThetaBound().Minimum() 
                        <= edge.Properties().ThetaBound().Maximum() ); 
            if ( edge.Properties().ThetaBound().Minimum() 
               > edge.Properties().ThetaBound().Maximum() ) 
            {
                hasCorrectBound = false;
                return;
            }
            // nominalApparentPowerBound
            USAGE_ASSERT ( edge.Properties().NominalApparentPowerBound().Minimum() 
                        <= edge.Properties().NominalApparentPowerBound().Maximum() ); 
            if ( edge.Properties().NominalApparentPowerBound().Minimum() 
               > edge.Properties().NominalApparentPowerBound().Maximum() ) 
            {
                hasCorrectBound = false;
                return;
            }
        });
        return hasCorrectBound;
    }

    template<typename TNetwork>
    inline bool HasNetworkCorrectBounds ( TNetwork const & network )
    {
        using TGraph                = typename TNetwork::TGraph;
        using TGeneratorProperties  = typename TNetwork::TGeneratorProperties;

        bool hasCorrectBound = true;

        network.template for_all_generators<ExecutionPolicy::sequential> ( 
            [&hasCorrectBound]( TGeneratorProperties const & properties ) 
        {
            // nominalRealPowerBound
            USAGE_ASSERT ( properties.NominalRealPowerBound().Minimum() 
                        <= properties.NominalRealPowerBound().Maximum() ); 
            if ( properties.NominalRealPowerBound().Minimum() 
               > properties.NominalRealPowerBound().Maximum() ) 
            {
                hasCorrectBound = false;
            }
            // realPowerBound
            USAGE_ASSERT ( properties.RealPowerBound().Minimum() 
                        <= properties.RealPowerBound().Maximum() ); 
            if ( properties.RealPowerBound().Minimum() 
               > properties.RealPowerBound().Maximum() ) 
            {
                hasCorrectBound = false;
            }
            // reactivePowerBound
            USAGE_ASSERT ( properties.ReactivePowerBound().Minimum() 
                        <= properties.ReactivePowerBound().Maximum() ); 
            if ( properties.ReactivePowerBound().Minimum() 
               > properties.ReactivePowerBound().Maximum() ) 
            {
                hasCorrectBound = false;
                return;
            }
            // qc1Bound
            USAGE_ASSERT ( properties.Qc1Bound().Minimum() 
                        <= properties.Qc1Bound().Maximum() ); 
            if ( properties.Qc1Bound().Minimum() 
               > properties.Qc1Bound().Maximum() ) 
            {
                hasCorrectBound = false;
                return;
            }
            // qc2Bound
            USAGE_ASSERT ( properties.Qc2Bound().Minimum() 
                        <= properties.Qc2Bound().Maximum() ); 
            if ( properties.Qc2Bound().Minimum() 
               > properties.Qc2Bound().Maximum() ) 
            {
                hasCorrectBound = false;
                return;
            }
        });
        
        return hasCorrectBound
            && HasGraphCorrectBounds<TGraph>( network.Graph() );
    }

} // namespace egoa::IO::Helper

#endif // EGOA__IO__HELPER__DATA_VALIDATION_HPP
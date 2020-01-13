/*
 * GenerationStrategy.hpp
 *
 *  Created on: Jan 13, 2020
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATASTRUCTURES__NETWORKS__GENERATION_STRATEGY_HPP
#define EGOA__DATASTRUCTURES__NETWORKS__GENERATION_STRATEGY_HPP

#include "Auxiliary/Types.hpp"
#include "Exceptions/Assertions.hpp"

namespace egoa::internal {

/**
 * @brief      This base class to differentiate between different generation
 *             strategy.
 * @details    Implementations for the loops are defined in the template
 *             specializations for the different generation strategies.
 *
 * @tparam     NetworkType     The type of the network.
 * @tparam     GenerationType  The generation strategy.
 */
template<typename NetworkType, Vertices::GenerationStrategyDifferentiationType GenerationType>
class GenerationStrategyDifferentiation;

/**
 * @brief      This base class to differentiate between different generation
 *             strategy.
 * @details    This is the
 *     <tt> Vertices::GenerationStrategyDifferentiationType::totalVertexRealPowerGenerationPerSnapshot </tt>
 *     specialization.
 *     
 * @see        Vertices::GenerationStrategyDifferentiationType::totalVertexRealPowerGenerationPerSnapshot
 *
 * @tparam     NetworkType  The type of the network.
 */
template<typename NetworkType>
class GenerationStrategyDifferentiation<NetworkType, Vertices::GenerationStrategyDifferentiationType::totalVertexPowerGenerationPerSnapshot> {
    
    using TNetwork              = NetworkType;
    using TGeneratorProperties  = typename TNetwork::TGeneratorProperties;

    public:

    /// @name Total vertex real power generation per snapshot
    /// @{
#pragma mark TOTAL_VERTEX_REAL_POWER_GENERATION_PER_SNAPSHOT_STRATEGY
        /**
         * @brief      Total real power generation
         *     @f$\realpowergeneration(\vertex)@f$ at a vertex
         *     @f$\vertex\in\vertices@f$ with vertex identifier @p vertexId.
         *
         * @param      network            The network @f$\network@f$.
         * @param[in]  vertexId           The vertex identifier.
         * @param[in]  timestampPosition  The timestamp position.
         *
         * @return     A real power generation at a vertex
         *     @f$\vertex\in\vertices@f$.
         */
        inline static
        Types::real TotalRealPowerGenerationAt ( TNetwork        const & network
                                               , Types::vertexId         vertexId 
                                               , Types::index            timestampPosition = 0 )
        {
            USAGE_ASSERT ( network.Graph().VertexExists ( vertexId ) );

            Types::real pg ( 0.0 );
            if ( network.HasGeneratorAt ( vertexId ) ) 
            {
                network.template for_all_generators_at <ExecutionPolicy::sequential> ( vertexId, 
                    [ &network, &pg, &timestampPosition ]( TGeneratorProperties const & generator )
                    {
                        if ( generator.IsActive() ) 
                        {
                            pg += network.GeneratorRealPowerSnapshotAt ( generator, timestampPosition );
                        }
                    }
                );
            }
            return pg;
        }
    ///@}

    /// @name Total vertex reactive power generation per snapshot.
    /// @{
#pragma mark TOTAL_VERTEX_REACTIVE_POWER_GENERATION_PER_SNAPSHOT_STRATEGY

        /**
         * @brief      The total reactive power generation
         *     @f$\reactivepowergeneration@f$ of all generator snapshots for
         *     one timestamp at vertex @f$\vertex\in\vertices@f$ with
         *     identifier @p vertexId.
         *
         * @param[in]  vertexId  The vertex @f$\vertex\in\vertices@f$ with
         *     identifier @p vertexId.
         *
         * @note       The total reactive power generation
         *     @f$\reactivepowergeneration@f$ only includes the snapshots of
         *     @p active generators. In addition, if the vertex
         *     @f$\vertex\in\vertices@f$ has no generators the return value is 0.
         *
         * @return     The total reactive power generation
         *     @f$\reactivepowergeneration@f$ of all generator snapshots at a
         *     vertex @f$\vertex\in\vertices@f$ with identifier @p vertexId.
         */
        inline static
        Types::real TotalReactivePowerGenerationAt ( TNetwork const & network
                                                   , Types::vertexId  vertexId
                                                   , Types::index     timestampPosition = 0 )
        {
            USAGE_ASSERT ( network.Graph().VertexExists ( vertexId ) );

            Types::real qg( 0.0 );
            if ( network.HasGeneratorAt( vertexId ) ) 
            {
                network.template for_all_generators_at <ExecutionPolicy::sequential> ( vertexId, 
                    [&network, &qg, &timestampPosition ]( TGeneratorProperties const & generator )
                    {
                        if ( generator.IsActive() ) 
                        {
                            qg += network.GeneratorReactivePowerSnapshotAt ( generator
                                                                           , timestampPosition );
                        }
                    }
                );
            }
            return qg;
        }
    ///@}
};

} // namespace egoa::internal

#endif // EGOA__DATASTRUCTURES__NETWORKS__GENERATION_STRATEGY_HPP
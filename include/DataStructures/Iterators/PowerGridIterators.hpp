/*
 * PowerGridIterators.hpp
 *
 *  Created on: Dec 05, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATASTRUCTURES__GRAPHS__ITERATORS__POWER_GRID_ITERATORS_HPP
#define EGOA__DATASTRUCTURES__GRAPHS__ITERATORS__POWER_GRID_ITERATORS_HPP

#ifdef OPENMP_AVAILABLE
    #include <omp.h>
#endif

#include "Exceptions/Assertions.hpp"
#include "Auxiliary/ExecutionPolicy.hpp"

namespace egoa::internal {

#pragma mark SEQUENTIAL

/**
 * @brief      The base class for @p for loops for power grid.
 * @details    Implementations for the loops are defined in the
 *             template specializations for the different execution
 *             policies.
 *
 *
 * @tparam     PowerGridType    The type of a power grid, e.g., PowerGrid.
 * @tparam     Policy           The execution policy.
 */
template<typename PowerGridType, ExecutionPolicy Policy >
class PowerGridLoopDifferentiation;

template<typename PowerGridType >
class PowerGridLoopDifferentiation<PowerGridType, ExecutionPolicy::sequential> {

    using TNetwork              = PowerGridType;
    using TVertex               = typename TNetwork::TVertex;
    using TGeneratorProperties  = typename TNetwork::TGeneratorProperties;
    using TLoadProperties       = typename TNetwork::TLoadProperties;
    using TLoopDifferentiation  = PowerGridLoopDifferentiation<TNetwork, ExecutionPolicy::sequential>;

    public:

        ///@name Sequential Generator Loops
        ///@{
#pragma mark SEQUENTIAL_GENERATOR_LOOPS

            /**
             * @brief      The sequential @p for loop over all @p generators
             *     (vertex independent).
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a generator object as input.
             *
             * @code{.cpp}
             *      []( TGeneratorProperties & generatorProperties )
             *      {
             *          Do something with the generator properties.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator properties in the power grid.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generators ( TNetwork & network
                                    , FUNCTION   function )
            {
                for ( TGeneratorProperties & generator : network.generators_ )
                {
                    function( generator );
                }
            }

            /**
             * @brief      The sequential @p for loop over all @p generators (vertex
             *     independent).
             *
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a generator object as input.
             *
             * @code{.cpp}
             *      []( TGeneratorProperties const & generatorProperties )
             *      {
             *          Do something with the generator properties.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator properties in the power grid.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generators ( TNetwork const & network
                                    , FUNCTION         function )
            {
                for ( TGeneratorProperties const & generator : network.generators_ )
                {
                    function( generator );
                }
            }

            /**
             * @brief      The sequential @p for loop over all @p vertices that have
             *     a generator.
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda function
             *     that has a vertex identifier @p Types::vertexId as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId )
             *      {
             *          Do something with the vertex identifier that has generators.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all vertex identifiers that have a generator.
             */
            template<typename FUNCTION>
            inline static
            void for_all_vertex_identifiers_with_generator ( TNetwork const & network
                                                           , FUNCTION         function )
            {
                Types::vertexId vertexIdSafeguard = 0;
                for ( Types::vertexId vertexId = 0
                    ; vertexId < network.Graph().Vertices().size()
                    ; ++vertexId )
                {
                    if (   network.HasGeneratorAt(vertexId)
                        && network.Graph().VertexExists(vertexId) ) {
                        vertexIdSafeguard = vertexId;
                        function( vertexIdSafeguard );
                    }
                }
            }

            /**
             * @brief      The sequential @p for loop over all generator
             *     identifiers at a vertex identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param[in]  network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a generator identifier @p
             *      Types::generatorId as input.
             *
             * @code{.cpp}
             *      []( Types::generatorId generatorId )
             *      {
             *          Do something with the generator identifier at the @p vertexId.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator identifiers at @p vertexId.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generator_identifiers_at ( Types::vertexId vertexId
                                                 , TNetwork const & network
                                                 , FUNCTION         function )
            {
                Types::loadId generatorIdSafeguard = 0;
                if (   network.HasGeneratorAt ( vertexId )
                    && network.Graph().VertexExists ( vertexId ) )
                {
                    for ( Types::generatorId generatorId : network.generatorsAtVertex_[vertexId] )
                    {
                        generatorIdSafeguard = generatorId;
                        function ( generatorIdSafeguard );
                    }
                }
            }

            /**
             * @brief      The sequential @p for loop over all generator
             *     identifiers at a vertex.
             *
             * @param[in]  vertex    The vertex object.
             * @param[in]  network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a generator identifier @p generatorId as
             *      input.
             *
             * @code{.cpp}
             *      []( Types::generatorId generatorId )
             *      {
             *          Do something with the generator identifier at the @p vertex.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator identifiers at @p vertexId.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generator_identifiers_at ( TVertex const & vertex
                                                 , TNetwork const & network
                                                 , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );
                for_all_generator_identifiers_at ( vertexId, network, function );
            }


            /**
             * @brief      The sequential @p for loop over all generator objects
             *     at a @p vertex.
             *
             * @param      vertex    The vertex object.
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a generator object as input.
             *
             * @code{.cpp}
             *      []( TGeneratorProperties & generator )
             *      {
             *          Do something with the generator object at the @p vertex.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator properties at @p vertex.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generators_at ( TVertex  const & vertex
                                       , TNetwork       & network
                                       , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );
                for_all_generators_at ( vertexId, network, function );
            }

            /**
             * @brief      The sequential @p for loop over all generator objects
             *     at a @p vertex.
             *
             * @param      vertex    The vertex object.
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a generator object as input.
             *
             * @code{.cpp}
             *      []( TGeneratorProperties const & generator )
             *      {
             *          Do something with the generator object at the @p vertex.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator properties at @p vertex.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generators_at ( TVertex  const & vertex
                                       , TNetwork const & network
                                       , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );
                for_all_generators_at ( vertexId, network, function );
            }

            /**
             * @brief      The sequential @p for loop over all generator objects
             *     at a vertex identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a generator object as input.
             *
             * @code{.cpp}
             *      []( TGeneratorProperties & generator )
             *      {
             *          Do something with the generator object at the @p vertexId.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator properties at @p vertexId.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generators_at ( Types::vertexId const vertexId
                                       , TNetwork            & network
                                       , FUNCTION              function )
            {
                for_all_generator_identifiers_at ( vertexId, network,
                    [ &network, &function ]( Types::generatorId generatorId )
                    {
                        function ( network.generators_[generatorId] );
                    }
                );
            }

            /**
             * @brief      The sequential @p for loop over all generator objects
             *     at a vertex identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a generator object as input.
             *
             * @code{.cpp}
             *      []( TGeneratorProperties const & generator )
             *      {
             *          Do something with the generator object at the @p vertexId.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator properties at @p vertexId.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generators_at ( Types::vertexId const   vertexId
                                       , TNetwork        const & network
                                       , FUNCTION                function )
            {
                for_all_generator_identifiers_at ( vertexId, network,
                    [ &network, &function ]( Types::generatorId generatorId )
                    {
                        function ( network.generators_[generatorId] );
                    }
                );
            }

            /**
             * @brief      The sequential @p for loop over @c all vertices@c that
             *     have a generator and its @c generator objects@c.
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and a
             *      @c generator object@c as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId, TGeneratorProperties & generatorProperties )
             *      {
             *          Do something with the vertexId and the generator object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator tuple (vertexId, generatorProperties).
             */
            template<typename FUNCTION>
            inline static
            void for_all_generator_tuple ( TNetwork & network
                                         , FUNCTION   function )
            {
                Types::vertexId vertexIdSafeguard = 0;
                for ( Types::vertexId vertexId = 0
                    ; vertexId < network.Graph().Vertices().size()
                    ; ++vertexId )
                {
                    if ( network.HasGeneratorAt(vertexId) )
                    {
                        for ( Types::generatorId generatorId : network.generatorsAtVertex_[vertexId] )
                        {
                            vertexIdSafeguard = vertexId;
                            function( vertexIdSafeguard, network.generators_[generatorId]);
                        }
                    }
                }
            }

            /**
             * @brief      The sequential @p for loop over @c all vertices@c that
             *     have a generator and its @c generator objects@c.
             *
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and a
             *      @c generator object@c as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId, TGeneratorProperties const & generator )
             *      {
             *          Do something with the vertexId and the generator object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator tuple (vertexId, generatorProperties).
             */
            template<typename FUNCTION>
            inline static
            void for_all_generator_tuple ( TNetwork const & network
                                         , FUNCTION         function )
            {
                Types::vertexId vertexIdSafeguard = 0;
                for ( Types::vertexId vertexId = 0
                    ; vertexId < network.Graph().Vertices().size()
                    ; ++vertexId )
                {
                    if ( network.HasGeneratorAt(vertexId) )
                    {
                        for ( Types::generatorId generatorId : network.generatorsAtVertex_[vertexId] )
                        {
                            vertexIdSafeguard = vertexId;
                            function( vertexIdSafeguard, network.generators_[generatorId]);
                        }
                    }
                }
            }

            /**
             * @brief      The sequential @p for loop over @c all vertices@c that
             *     have a generator.
             *
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and its
             *      @c generator objects@c as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId, std::vector<TGeneratorProperties> const & generators )
             *      {
             *          Do something with the set of generators at the vertexId
             *          and identifier of the vertex that has generators.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator tuple (vertexId, vector of generatorProperties).
             */
            template<typename FUNCTION>
            inline static
            void for_all_generators_tuple ( TNetwork & network
                                          , FUNCTION   function )
            {
                Types::vertexId vertexIdSafeguard = 0;
                for ( Types::vertexId vertexId = 0
                    ; vertexId < network.Graph().Vertices().size()
                    ; ++vertexId )
                {
                    if ( network.HasGeneratorAt(vertexId) )
                    {
                        std::vector<TGeneratorProperties> generators;
                        network.GeneratorsAt(vertexId, generators);
                        vertexIdSafeguard = vertexId;
                        function( vertexIdSafeguard, generators);
                    }
                }
            }

            /**
             * @brief      The sequential @p for loop over @c all vertices@c that
             *     have a generator.
             *
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and its
             *      @c generator objects@c as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId, std::vector<TGeneratorProperties> const & generators )
             *      {
             *          // Do something with the set of generators at the vertexId
             *          // and identifier of the vertex that has generators.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator tuple (vertexId, vector of generatorProperties).
             */
            template<typename FUNCTION>
            inline static
            void for_all_generators_tuple ( TNetwork const & network
                                          , FUNCTION         function )
            {
                Types::vertexId vertexIdSafeguard = 0;
                for ( Types::vertexId vertexId = 0
                    ; vertexId < network.Graph().Vertices().size()
                    ; ++vertexId )
                {
                    if ( network.HasGeneratorAt ( vertexId ) )
                    {
                        std::vector<TGeneratorProperties> generators;
                        network.GeneratorsAt(vertexId, generators);
                        vertexIdSafeguard = vertexId;
                        function( vertexIdSafeguard, generators);
                    }
                }
            }
        ///@}

#pragma mark SEQUENTIAL_GENERATOR_SNAPSHOT_LOOP
        /**
         * @brief      The sequential @c for loop @c over all generator
         *  maximum real power p.u. snapshots.
         *
         * @param      network     The network @f$\network = ( \graph,
         *         \generators, \consumers, \capacity, \susceptance, \dots)@f$.
         * @param[in]  function    The function, e.g., lambda function.
         *
         * @code{.cpp}
         *      for_all_real_power_generator_snapshots<ExecutionPolicy::sequential>(
         *          network,
         *          []( Types::index             snapshotId
         *            , Types::generatorSnapshot snapshot )
         *          {
         *              // Do something with the snapshotId and generator snapshot object.
         *          }
         *      );
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power generator snapshots.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots ( TNetwork & network
                                                        , FUNCTION   function )
            {
                for ( Types::index generatorId = 0
                    ; generatorId < network.generatorRealPowerSnapshots_.size()
                    ; ++generatorId )
                {
                    for_all_real_power_generator_snapshots_of ( network, generatorId, function );
                }
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots ( TNetwork const & network
                                                        , FUNCTION         function )
            {
                for ( Types::index generatorId = 0
                    ; generatorId < network.generatorRealPowerSnapshots_.size()
                    ; ++generatorId )
                {
                    for_all_real_power_generator_snapshots_of ( network, generatorId, function );
                }
            }
        ///@}

        /**
         * @brief      The sequential @c for loop @c over all maximum real
         *     power p.u. snapshots of a generator with @p generatorId.
         *
         * @param      network     The network @f$\network = ( \graph,
         *         \generators, \consumers, \capacity, \susceptance, \dots)@f$.
         * @param      generatorId The identifier of the generator.
         * @param[in]  function    The function, e.g., lambda function.
         *
         * @pre        Check if the generator identifier @p generatorId of the
         *     generatorProperties exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.HasGenerator ( generatorId ) )
         *      {
         *          for_all_real_power_generator_snapshots_of<ExecutionPolicy::sequential> (
         *              network,
         *              generatorId,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  // Do something with the snapshotId and generator snapshot object.
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power generator snapshots at @p generatorId.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_of ( TNetwork         & network
                                                           , Types::generatorId generatorId
                                                           , FUNCTION           function )
            {
                USAGE_ASSERT ( network.HasGenerator ( generatorId ) );

                for ( Types::index snapshotId = 0
                    ; snapshotId < network.generatorRealPowerSnapshots_[generatorId].size()
                    ; ++snapshotId )
                {
                    function( snapshotId, network.generatorRealPowerSnapshots_[generatorId][snapshotId] );
                }
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_of ( TNetwork   const & network
                                                           , Types::generatorId generatorId
                                                           , FUNCTION           function )
            {
                USAGE_ASSERT ( network.HasGenerator ( generatorId ) );

                for ( Types::index snapshotId = 0
                    ; snapshotId < network.generatorRealPowerSnapshots_[generatorId].size()
                    ; ++snapshotId )
                {
                    function( snapshotId, network.generatorRealPowerSnapshots_[generatorId][snapshotId] );
                }
            }
        ///@}

        /**
         * @brief      The sequential @c for loop @c over all maximum real
         *     power p.u. snapshots of a @p generator.
         *
         * @param      network              The network @f$\network = ( \graph,
         *         \generators, \consumers, \capacity, \susceptance, \dots)@f$.
         * @param      generatorProperties  The generator properties.
         * @param[in]  function             The function, e.g. , lambda function.
         *
         * @pre        Check if the generator's properties @p
         *     generatorProperties exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.HasGenerator ( network.GeneratorId ( generatorProperties ) ) )
         *      {
         *          for_all_real_power_generator_snapshots_of<ExecutionPolicy::sequential> (
         *              network,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  // Do something with the snapshotId and generator snapshot object.
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power generator snapshots of @p generatorProperties.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_of ( TNetwork           & network
                                                           , TGeneratorProperties generatorProperties
                                                           , FUNCTION             function )
            {
                Types::generatorId generatorId = network.GeneratorId( generatorProperties );

                USAGE_ASSERT ( network.HasGenerator ( generatorId ) );

                for_all_real_power_generator_snapshots_of ( network, generatorId, function );
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_of ( TNetwork const &     network
                                                           , TGeneratorProperties generatorProperties
                                                           , FUNCTION             function )
            {
                Types::generatorId generatorId = network.GeneratorId( generatorProperties );

                USAGE_ASSERT ( network.HasGenerator ( generatorId ) );

                for_all_real_power_generator_snapshots_of ( network, generatorId, function );
            }
        ///@}

        /**
         * @brief      The sequential @c for loop @c over all generator
         *     maximum real power p.u. snapshots at a vertex with @p vertexId.
         *
         * @param      network     The network @f$\network = ( \graph,
         *         \generators, \consumers, \capacity, \susceptance, \dots)@f$.
         * @param      vertexId    The identifier of a vertex.
         * @param[in]  function    The function, e.g. , lambda function.
         *
         * @pre        Check if the vertex identifier @p vertexId of the
         *     vertex exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( vertexId ) )
         *      {
         *          for_all_real_power_generator_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertexId,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  // Do something with the snapshotId and generator snapshot object.
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power generator snapshots at @p vertexId.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork &      network
                                                           , Types::vertexId vertexId
                                                           , FUNCTION        function )
            {
                USAGE_ASSERT ( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::generatorId> generatorIds;
                network.GeneratorsAt( vertexId, generatorIds );

                for ( Types::generatorId generatorId : generatorIds )
                {
                    for_all_real_power_generator_snapshots_of ( network, generatorId, function );
                }
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork const & network
                                                           , Types::vertexId  vertexId
                                                           , FUNCTION         function )
            {
                USAGE_ASSERT ( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::generatorId> generatorIds;
                network.GeneratorsAt( vertexId, generatorIds );


                for ( Types::generatorId generatorId : generatorIds )
                {
                    for_all_real_power_generator_snapshots_of ( network, generatorId, function );
                }
            }
        ///@}

        /**
         * @brief      The sequential @c for loop @c over all generator
         *     maximum real power p.u. snapshots at a @p vertex.
         *
         * @param      network     The network @f$\network = ( \graph,
         *         \generators, \consumers, \capacity, \susceptance, \dots)@f$.
         * @param      vertex      The vertex.
         * @param[in]  function    The function, e.g., lambda function.
         *
         * @pre        Check if the vertex @p vertex exists before using
         *     this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( network.Graph().VertexId( vertex ) ) )
         *      {
         *          for_all_real_power_generator_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertex,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  // Do something with the snapshotId and generator snapshot object.
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power generator snapshots at @p vertex.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork         & network
                                                           , TVertex    const & vertex
                                                           , FUNCTION           function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::generatorId> generatorIds;
                network.GeneratorAt( vertexId, generatorIds );

                for_all_real_power_generator_snapshots_at ( network, vertexId, function );
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork   const & network
                                                           , TVertex    const & vertex
                                                           , FUNCTION           function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::generatorId> generatorIds;
                network.GeneratorAt( vertexId, generatorIds );

                for_all_real_power_generator_snapshots_at ( network, vertexId, function );
            }
        ///@}

        /**
         * @brief      The sequential @c for loop @c over snapshots with a
         *     certain @ timestampPosition for all @p generators.
         * @details    This loop basically extracts a row.
         *
         * @param      network              The network @f$\network = ( \graph,
         *         \generators, \consumers, \capacity, \susceptance, \dots)@f$.
         * @param      vertexId             The identifier of a vertex
         * @param      timestampPosition    The position of the snapshot
         *     (timestamp of the snapshot).
         * @param[in]  function             The function, e.g. , lambda function
         *
         * @pre        Check if the vertex identifier @p vertexId of the
         *     vertex exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( vertexId ) )
         *      {
         *          for_all_real_power_generator_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertexId,
         *              timestampPosition,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  Do something with the snapshotId and load snapshot object
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power generator at @p timestamp at @p vertex.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork &      network
                                                           , Types::vertexId vertexId
                                                           , Types::index    timestampPosition
                                                           , FUNCTION        function )
            {
                USAGE_ASSERT( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::generatorId> generatorIds;
                network.GeneratorIds ( vertexId, generatorIds );

                for ( Types::generatorId generatorId : generatorIds )
                {
                    function ( network.GeneratorSnapshotOf( generatorId, timestampPosition ) );
                }
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork   const & network
                                                           , Types::vertexId    vertexId
                                                           , Types::index       timestampPosition
                                                           , FUNCTION           function )
            {
                USAGE_ASSERT( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::generatorId> generatorIds;
                network.GeneratorIds ( vertexId, generatorIds );

                for ( Types::generatorId generatorId : generatorIds )
                {
                    function ( network.GeneratorSnapshotOf( generatorId, timestampPosition ) );
                }
            }
        ///@}

        /**
         * @brief      The @c for loop @c over all real power snapshots of a
         *     @p generator and a timestamp at @p timestampPosition.
         *
         * @param      network              The network @f$\network = ( \graph,
         *         \generators, \consumers, \capacity, \susceptance, \dots)@f$.
         * @param      vertex               The vertex
         * @param[in]  timestampPosition    The timestamp position
         * @param[in]  function             The function
         *
         * @pre        Check if the vertex @p vertex exists before using
         *     this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( vertexId ) )
         *      {
         *          for_all_real_power_generator_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertex,
         *              timestampPosition,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  // Do something with the snapshotId and load snapshot object
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load at @p timestamp at @p vertex.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork      & network
                                                           , TVertex const & vertex
                                                           , Types::index    timestampPosition
                                                           , FUNCTION        function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists ( vertexId ) );

                for_all_real_power_generator_snapshots_at ( network, vertexId, timestampPosition, function );
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork const & network
                                                           , TVertex  const & vertex
                                                           , Types::index     timestampPosition
                                                           , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists ( vertexId ) );

                for_all_real_power_generator_snapshots_at ( network, vertexId, timestampPosition, function );
            }
        ///@}


        ///@name Sequential Load Loops
        ///@{
#pragma mark SEQUENTIAL_LOAD_LOOPS

            /**
             * @brief      The sequential @p for loop over all @p loads
             *     (vertex independent).
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a load object as input.
             *
             * @code{.cpp}
             *      []( TLoadProperties & load )
             *      {
             *          Do something with the load object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all loads.
             */
            template<typename FUNCTION>
            inline static
            void for_all_loads ( TNetwork & network
                               , FUNCTION   function )
            {
                for ( TLoadProperties & load : network.loads_ )
                {
                    function ( load );
                }
            }

            /**
             * @brief      The sequential @p for loop over all @p loads
             *     (vertex independent).
             *
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a const load object as input.
             *
             * @code{.cpp}
             *      []( TLoadProperties const & load )
             *      {
             *          Do something with the load object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all loads.
             */
            template<typename FUNCTION>
            inline static
            void for_all_loads ( TNetwork const & network
                               , FUNCTION         function )
            {
                for ( TLoadProperties const & load : network.loads_ )
                {
                    function ( load );
                }
            }

            /**
             * @brief      The sequential @p for loop over all @p vertices
             *     that have a load.
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a vertex identifier @p Types::vertexId
             *      as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId )
             *      {
             *          Do something with the vertex identifier that has loads.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all vertex identifiers that have a load.
             */
            template<typename FUNCTION>
            inline static
            void for_all_vertex_identifiers_with_load ( TNetwork const & network
                                                      , FUNCTION         function )
            {
                Types::vertexId vertexIdSafeguard = 0;
                for ( Types::vertexId vertexId = 0
                    ; vertexId < network.Graph().Vertices().size()
                    ; ++vertexId )
                {
                    if (   network.HasLoadAt(vertexId)
                        && network.Graph().VertexExists(vertexId) )
                    {
                        vertexIdSafeguard = vertexId;
                        function ( vertexIdSafeguard );
                    }
                }
            }

            /**
             * @brief      The sequential @p for loop over all load identifiers
             *     at a vertex identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a load identifier @p Types::loadId as
             *      input.
             *
             * @code{.cpp}
             *      []( Types::loadId loadId )
             *      {
             *          Do something with the load identifier at the @p vertex.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all vertex identifiers at @p vertexId.
             */
            template<typename FUNCTION>
            inline static
            void for_all_load_identifiers_at ( Types::vertexId  vertexId
                                             , TNetwork const & network
                                             , FUNCTION         function )
            {
                Types::loadId loadIdSafeguard = 0;
                if (   network.HasLoadAt ( vertexId )
                    && network.Graph().VertexExists ( vertexId ) ) {
                    for ( Types::loadId loadId : network.loadsAtVertex_[vertexId] )
                    {
                        loadIdSafeguard = loadId;
                        function ( loadIdSafeguard );
                    }
                }
            }

            /**
             * @brief      The sequential @p for loop over all load identifiers
             *     at a vertex.
             *
             * @param      vertex    The vertex object.
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a load identifier as input.
             *
             * @code{.cpp}
             *      []( Types::loadId loadId )
             *      {
             *          Do something with the load identifier at the @p vertex.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all load identifiers at @p vertex.
             */
            template<typename FUNCTION>
            inline static
            void for_all_load_identifiers_at ( TVertex  const & vertex
                                             , TNetwork const & network
                                             , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );
                for_all_load_identifiers_at ( vertexId, network, function );
            }

            /**
             * @brief      The sequential @p for loop over all load objects at a
             *     @p vertex.
             *
             * @param      vertex    The vertex object.
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a load object as input.
             *
             * @code{.cpp}
             *      []( TLoadProperties & loadProperties )
             *      {
             *          Do something with the load object at the @p vertex.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all load properties at @p vertex.
             */
            template<typename FUNCTION>
            inline static
            void for_all_loads_at ( TVertex  const & vertex
                                  , TNetwork       & network
                                  , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );
                for_all_loads_at ( vertexId, network, function );
            }

            /**
             * @brief      The sequential @p for loop over all load objects at a
             *     @p vertex.
             *
             * @param      vertex    The vertex object.
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a load object as input.
             *
             * @code{.cpp}
             *      []( TLoadProperties const & load )
             *      {
             *          Do something with the load object at the @p vertex.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all load properties at @p vertex.
             */
            template<typename FUNCTION>
            inline static
            void for_all_loads_at ( TVertex  const & vertex
                                  , TNetwork const & network
                                  , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );
                for_all_loads_at ( vertexId, network, function );
            }

            /**
             * @brief      The sequential @p for loop over all load objects at a
             *     vertex identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a load object as input.
             *
             * @code{.cpp}
             *      []( TLoadProperties & load )
             *      {
             *          Do something with the load object at the @p vertexId.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all load properties at @p vertexId.
             */
            template<typename FUNCTION>
            inline static
            void for_all_loads_at ( Types::vertexId const vertexId
                                  , TNetwork            & network
                                  , FUNCTION              function )
            {
                for_all_load_identifiers_at ( vertexId, network,
                    [ &network, &function ]( Types::loadId loadId )
                    {
                        function ( network.loads_[loadId] );
                    }
                );
            }

            /**
             * @brief      The sequential @p for loop over all load objects at a
             *     vertex identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a load object as input.
             *
             * @code{.cpp}
             *      []( TLoadProperties const & load )
             *      {
             *          Do something with the load object at the @p vertexId.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all load properties at @p vertexId.
             */
            template<typename FUNCTION>
            inline static
            void for_all_loads_at ( Types::vertexId const   vertexId
                                  , TNetwork        const & network
                                  , FUNCTION                function )
            {
                for_all_load_identifiers_at ( vertexId, network,
                    [ &network, &function ]( Types::loadId loadId )
                    {
                        function ( network.loads_[loadId] );
                    }
                );
            }

            /**
             * @brief      The sequential @p for loop over @c all vertices@c
             *     that have a load and its @c load objects@c.
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and a
             *      @c load object@c as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId, TLoadProperties & loadProperties )
             *      {
             *          Do something with the vertexId and load object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all load tuples (vertexId, loadProperties).
             */
            template<typename FUNCTION>
            inline static
            void for_all_load_tuples ( TNetwork & network
                                     , FUNCTION   function )
            {
                Types::vertexId vertexIdSafeguard = 0;
                for ( Types::vertexId vertexId = 0
                    ; vertexId < network.Graph().Vertices().size()
                    ; ++vertexId )
                {
                    if ( network.HasLoadAt(vertexId) )
                    {
                        for ( Types::loadId loadId : network.loadsAtVertex_[vertexId] )
                        {
                            vertexIdSafeguard = vertexId;
                            function( vertexIdSafeguard, network.loads_[loadId] );
                        }
                    }
                }
            }

            /**
             * @brief      The sequential @p for loop over @c all vertices@c that
             *     have a load and its @c load objects@c.
             *
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and a
             *      @c load object@c as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId, TLoadProperties const & loadProperties )
             *      {
             *          Do something with the vertexId and load object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all load tuples (vertexId, loadProperties).
             */
            template<typename FUNCTION>
            inline static
            void for_all_load_tuples ( TNetwork const & network
                                     , FUNCTION         function )
            {
                Types::vertexId vertexIdSafeguard = 0;
                for ( Types::vertexId vertexId = 0
                    ; vertexId < network.Graph().Vertices().size()
                    ; ++vertexId )
                {
                    if ( network.HasLoadAt(vertexId) )
                    {
                        for ( Types::loadId loadId : network.loadsAtVertex_[vertexId] )
                        {
                            vertexIdSafeguard = vertexId;
                            function( vertexIdSafeguard, network.loads_[loadId] );
                        }
                    }
                }
            }

            /**
             * @brief      The sequential @p for loop over @c all vertices@c that
             *     have a load.
             *
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and its
             *      @c load objects@c as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId, std::vector<TLoadProperties> & loads )
             *      {
             *          Do something with the set of loads at the vertexId
             *          and identifier of the vertex that has loads.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all load tuples (vertexId, vector of loadProperties).
             */
            template<typename FUNCTION>
            inline static
            void for_all_loads_tuple ( TNetwork const & network
                                     , FUNCTION         function )
            {
                Types::vertexId vertexIdSafeguard = 0;
                for ( Types::vertexId vertexId = 0
                    ; vertexId < network.Graph().Vertices().size()
                    ; ++vertexId )
                {
                    if ( network.HasLoadAt(vertexId) )
                    {
                        std::vector<TLoadProperties> loads;
                        network.LoadsAt ( vertexId, loads );
                        vertexIdSafeguard = vertexId;
                        function( vertexIdSafeguard, loads );
                    }
                }
            }
        ///@}


#pragma mark SEQUENTIAL_LOAD_SNAPSHOT_LOOPS

        /**
         * @brief      The sequential @c for loop @c over all load real power
         *     snapshots.
         *
         * @param      network     The network
         * @param[in]  function    The function, e.g., lambda function.
         *
         * @code{.cpp}
         *      for_all_real_power_load_snapshots<ExecutionPolicy::sequential>(
         *          network,
         *          []( Types::index        snapshotId
         *            , Types::loadSnapshot snapshot )
         *          {
         *              Do something with the snapshotId and load snapshot object
         *          }
         *      );
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load snapshots.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots ( TNetwork & network
                                                   , FUNCTION   function )
            {
                for ( Types::loadId loadId = 0
                    ; loadId < network.loadSnapshots_.size()
                    ; ++loadId )
                {
                    for_all_real_power_load_snapshots_of ( network
                                                         , loadId
                                                         , function );
                }
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots ( TNetwork const & network
                                                   , FUNCTION         function )
            {
                for ( Types::loadId loadId = 0
                    ; loadId < network.loadSnapshots_.size()
                    ; ++loadId )
                {
                    for_all_real_power_load_snapshots_of ( network
                                                         , loadId
                                                         , function );
                }
            }
        ///@}

        /**
         * @brief      The sequential @c for loop @c over all real power
         *     snapshots of a load with @p loadId.
         *
         * @param      network     The network.
         * @param      loadId      The identifier of the load.
         * @param[in]  function    The function, e.g., lambda function.
         *
         * @pre        Check if the load identifier @p loadId of the
         *     loadProperties exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.HasLoad ( loadId ) )
         *      {
         *          for_all_real_power_load_snapshots_of<ExecutionPolicy::sequential> (
         *              network,
         *              loadId,
         *              []( Types::index snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  Do something with the snapshotId and load snapshot object
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load snapshots at @p loadId.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_of ( TNetwork &    network
                                                      , Types::loadId loadId
                                                      , FUNCTION      function )
            {
                USAGE_ASSERT ( network.HasLoad ( loadId ) );

                for ( Types::index timestampPosition = 0
                    ; timestampPosition < network.loadSnapshots_.size()
                    ; ++timestampPosition )
                {
                    function ( timestampPosition
                             , network.LoadSnapshotOf( loadId, timestampPosition ) );
                }
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_of ( TNetwork const & network
                                                      , Types::loadId    loadId
                                                      , FUNCTION         function )
            {
                USAGE_ASSERT ( network.HasLoad ( loadId ) );

                for ( Types::index timestampPosition = 0
                    ; timestampPosition < network.loadSnapshots_.size()
                    ; ++timestampPosition )
                {
                    function ( timestampPosition
                             , network.LoadSnapshotOf( loadId, timestampPosition ) );
                }
            }
        ///@}


        /**
         * @brief      The sequential @c for loop @c over all real power
         *     snapshots of a @p load.
         *
         * @param      network          The network.
         * @param      loadProperties   The load properties.
         * @param[in]  function         The function, e.g. , lambda function
         *
         * @pre        Check if the load's properties @p loadProperties exists
         *     before using this method.
         *
         * @code{.cpp}
         *      if ( network.HasLoad ( network.LoadId ( loadProperties ) ) )
         *      {
         *          for_all_real_power_load_snapshots_of<ExecutionPolicy::sequential> (
         *              network,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  Do something with the snapshotId and load snapshot object
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load snapshots at @p loadProperties.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_of ( TNetwork              & network
                                                      , TLoadProperties const & loadProperties
                                                      , FUNCTION                function )
            {
                Types::loadId loadId = network.LoadId ( loadProperties );

                USAGE_ASSERT ( network.HasLoad ( loadId ) );

                for_all_real_power_load_snapshots_of ( network, loadId, function );
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_of ( TNetwork        const & network
                                                      , TLoadProperties const & loadProperties
                                                      , FUNCTION                function )
            {
                Types::loadId loadId = network.LoadId ( loadProperties );

                USAGE_ASSERT ( network.HasLoad ( loadId ) );

                for_all_real_power_load_snapshots_of ( network, loadId, function );
            }
        ///@}

        /**
         * @brief      The sequential @c for loop @c over all real power
         *     snapshots of a @p load.
         *
         * @param      network     The network
         * @param      vertexId    The identifier of a vertex
         * @param[in]  function    The function, e.g. , lambda function
         *
         * @pre        Check if the vertex identifier @p vertexId of the
         *     vertex exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( vertexId ) )
         *      {
         *          for_all_real_power_load_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertexId,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  Do something with the snapshotId and load snapshot object }
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load snapshots at @p vertexId.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork &      network
                                                      , Types::vertexId vertexId
                                                      , FUNCTION        function )
            {
                USAGE_ASSERT( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::loadId> loadIds;
                network.LoadIds ( vertexId, loadIds );

                for ( Types::loadId loadId : loadIds )
                {
                    for_all_real_power_load_snapshots_of ( network, loadId, function );
                }
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork   const & network
                                                      , Types::vertexId    vertexId
                                                      , FUNCTION           function )
            {
                USAGE_ASSERT( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::loadId> loadIds;
                network.LoadIds ( vertexId, loadIds );

                for ( Types::loadId loadId : loadIds )
                {
                    for_all_real_power_load_snapshots_of ( network, loadId, function );
                }
            }
        ///@}

        /**
         * @brief      The @c for loop @c over all real power snapshots of a
         *     @p load.
         *
         * @param      network     The network
         * @param      vertex      The vertex
         * @param[in]  function    The function, e.g. , lambda function
         *
         * @pre        Check if the @p vertex exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( network.Graph().VertexId( vertex ) ) )
         *      {
         *          for_all_real_power_load_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertex,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  Do something with the snapshotId and load snapshot object
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load snapshots at @p vertex.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork      & network
                                                      , TVertex const & vertex
                                                      , FUNCTION        function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists ( vertexId ) );

                for_all_real_power_load_snapshots_at ( network, vertexId, function );
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork const & network
                                                      , TVertex  const & vertex
                                                      , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists ( vertexId ) );

                for_all_real_power_load_snapshots_at ( network, vertexId, function );
            }
        ///@}

        /**
         * @brief      The sequential @c for loop @c over snapshots with a
         *     certain @ timestampPosition for all @p load.
         * @details    This loop basically extracts a row.
         *
         * @param      network              The network
         * @param      vertexId             The identifier of a vertex
         * @param      timestampPosition    The position of the snapshot
         *     (timestamp of the snapshot).
         * @param[in]  function             The function, e.g. , lambda function
         *
         * @pre        Check if the vertex identifier @p vertexId of the
         *     vertex exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( vertexId ) )
         *      {
         *          for_all_real_power_load_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertexId,
         *              timestampPosition,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  Do something with the snapshotId and load snapshot object
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load at @p timestamp at @p vertex.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork &      network
                                                      , Types::vertexId vertexId
                                                      , Types::index    timestampPosition
                                                      , FUNCTION        function )
            {
                USAGE_ASSERT( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::loadId> loadIds;
                network.LoadIds ( vertexId, loadIds );

                for ( Types::loadId loadId : loadIds )
                {
                    function ( network.LoadSnapshotOf( loadId, timestampPosition ) );
                }
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork   const & network
                                                      , Types::vertexId    vertexId
                                                      , Types::index       timestampPosition
                                                      , FUNCTION           function )
            {
                USAGE_ASSERT( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::loadId> loadIds;
                network.LoadIds ( vertexId, loadIds );

                for ( Types::loadId loadId : loadIds )
                {
                    function ( network.LoadSnapshotOf( loadId, timestampPosition ) );
                }
            }
        ///@}

        /**
         * @brief      The @c for loop @c over all real power snapshots of a
         *     @p load and a timestamp at @p timestampPosition.
         *
         * @param      network              The network
         * @param      vertex               The vertex
         * @param[in]  timestampPosition    The timestamp position
         * @param[in]  function             The function
         *
         * @pre        Check if the @p vertex exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( vertexId ) )
         *      {
         *          for_all_real_power_load_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertex,
         *              timestampPosition,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  Do something with the snapshotId and load snapshot object
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load at @p timestamp at @p vertex.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork      & network
                                                      , TVertex const & vertex
                                                      , Types::index    timestampPosition
                                                      , FUNCTION        function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists ( vertexId ) );

                for_all_real_power_load_snapshots_at ( network, vertexId, timestampPosition, function );
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork const & network
                                                      , TVertex  const & vertex
                                                      , Types::index     timestampPosition
                                                      , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists ( vertexId ) );

                for_all_real_power_load_snapshots_at ( network, vertexId, timestampPosition, function );
            }
        ///@}
};

#pragma mark BREAKABLE

/**
 * @brief      Breakable @p for loops for @p PowerGrid.
 * @details    The loops are aborted if the function returns @p false.
 *
 * @tparam     PowerGridType  The type of the power grid.
 */
template<typename PowerGridType >
class PowerGridLoopDifferentiation<PowerGridType, ExecutionPolicy::breakable> {
    // Template type aliasing
    using TNetwork              = PowerGridType;
    using TVertex               = typename TNetwork::TVertex;
    using TGeneratorProperties  = typename TNetwork::TGeneratorProperties;
    using TLoadProperties       = typename TNetwork::TLoadProperties;
    using TLoopDifferentiation  = PowerGridLoopDifferentiation<TNetwork, ExecutionPolicy::sequential>;

    public:
        /// @name Breakable Generator Loops
        /// @{
#pragma mark BREAKABLE_GENERATOR_LOOPS
            //@todo       Implement
        ///@}

#pragma mark BREAKABLE_GENERATOR_SNAPSHOT_LOOP
        //@todo       Implement
#pragma mark BREAKABLE_LOAD_LOOPS

        template<typename FUNCTION>
        inline static
        void for_all_load_identifiers_at ( Types::vertexId  vertexId
                                         , TNetwork const & network
                                         , FUNCTION         function )
        {
            if ( !network.HasLoadAt( vertexId ) ) return;

            for ( Types::loadId loadId : network.loadsAtVertex_[vertexId] )
            {
                bool toContinue = function ( loadId );
                if (!toContinue) return;
            }
        }

        template<typename FUNCTION>
        inline static
        void for_all_load_identifiers_at ( TVertex  const & vertex
                                         , TNetwork const & network
                                         , FUNCTION         function )
        {
            Types::vertexId vertexId = vertex.Identifier();
            for_all_load_identifiers_at ( vertexId, network, function );
        }


        template<typename FUNCTION>
        inline static
        void for_all_loads_at( Types::vertexId vertexId,
                               TNetwork      & network,
                               FUNCTION        function )
        {
            USAGE_ASSERT( network.Graph().VertexExists(vertexId) );

            if ( !network.HasLoadAt(vertexId) ) return;

            for (Types::loadId loadId : network.loadsAtVertex_[vertexId] )
            {
                bool toContinue = function(network.loads_[loadId]);
                if (!toContinue) return;
            }

        }

        template<typename FUNCTION>
        inline static
        void for_all_loads_at( Types::vertexId  vertexId,
                               TNetwork const & network,
                               FUNCTION         function )
        {
            USAGE_ASSERT( network.Graph().VertexExists(vertexId) );

            if ( !network.HasLoadAt(vertexId) ) return;

            for (Types::loadId loadId : network.loadsAtVertex_[vertexId] )
            {
                bool toContinue = function(network.loads_[loadId]);
                if (!toContinue) return;
            }

        }
        //@todo       Implement
#pragma mark BREAKABLE_LOAD_SNAPSHOT_LOOPS
        //@todo       Implement
};

#pragma mark PARALLEL

#ifdef OPENMP_AVAILABLE

/**
 * @brief      The parallel @p for loops for @p PowerGrid.
 *
 * @tparam     PowerGridType  The type of the power grid.
 */
template<typename PowerGridType >
class PowerGridLoopDifferentiation<PowerGridType, ExecutionPolicy::parallel> {

    // Template type aliasing
    using TNetwork              = PowerGridType;
    using TVertex               = typename TNetwork::TVertex;
    using TGeneratorProperties  = typename TNetwork::TGeneratorProperties;
    using TLoadProperties       = typename TNetwork::TLoadProperties;
    using TLoopDifferentiation  = PowerGridLoopDifferentiation<TNetwork, ExecutionPolicy::parallel>;

    public:
        ///@name Parallel Generator Loops
        ///@{
#pragma mark PARALLEL_GENERATOR_LOOPS

            /**
             * @brief      The parallel @p for loop over all @p generators
             *     (vertex independent).
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a generator object as input.
             *
             * @code{.cpp}
             *      []( TGeneratorProperties & generator )
             *      {
             *          Do something with the generator object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator properties in the power grid.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generators ( TNetwork & network
                                    , FUNCTION   function )
            {
                #pragma omp parallel for
                    for ( Types::index generatorId = 0
                        ; generatorId < network.generators_.size()
                        ; ++generatorId )
                    {
                        function( network.generators_[generatorId] );
                    }
            }

            /**
             * @brief      The parallel @p for loop over all @p generators
             *     (vertex independent).
             *
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a generator object as input.
             *
             * @code{.cpp}
             *      []( TGeneratorProperties & generator )
             *      {
             *          Do something with the generator object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator properties in the power grid.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generators ( TNetwork const & network
                                    , FUNCTION         function )
            {
                #pragma omp parallel for
                    for ( Types::index generatorId = 0
                        ; generatorId < network.generators_.size()
                        ; ++generatorId )
                    {
                        function( network.generators_[generatorId] );
                    }
            }

            /**
             * @brief      The parallel @p for loop over all @p vertices that have
             *     a generator.
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda function
             *     that has a vertex identifier @p Types::vertexId as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId )
             *      {
             *          Do something with the vertex identifier that has generators.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_vertex_identifiers_with_generator ( TNetwork const & network
                                                           , FUNCTION         function )
            {
                #pragma omp parallel for
                    for ( Types::vertexId index = 0
                        ; index < network.Graph().Vertices().size()
                        ; ++index )
                    {
                        if (   network.HasGeneratorAt(index)
                            && network.Graph().VertexExists(index) )
                        {
                            function( index );
                        }
                    }
            }

            /**
             * @brief      The parallel @p for loop over all generator
             *     identifiers at a vertex identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param[in]  network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a generator identifier @p
             *      Types::generatorId as input.
             *
             * @code{.cpp}
             *      []( Types::generatorId generatorId )
             *      {
             *          Do something with the generator identifier at the @p vertexId.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator identifiers at @p vertexId.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generator_identifiers_at ( Types::vertexId  vertexId
                                                 , TNetwork  const & network
                                                 , FUNCTION          function )
            {
                if (   network.HasGeneratorAt ( vertexId )
                    && network.Graph().VertexExists ( vertexId ) ) {
                    #pragma omp parallel for
                        for ( Types::count counter = 0
                            ; counter < network.generatorsAtVertex_[vertexId].size()
                            ; ++counter )
                        {
                            function( network.generatorsAtVertex_[vertexId][counter] );
                        }
                }
            }

            /**
             * @brief      The parallel @p for loop over all generator
             *     identifiers at a vertex identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param[in]  network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a generator identifier @p
             *      Types::generatorId as input.
             *
             * @code{.cpp}
             *      []( Types::generatorId generatorId )
             *      {
             *          Do something with the generator identifier at the @p vertexId.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator identifiers at @p vertex.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generator_identifiers_at ( TVertex  const & vertex
                                                 , TNetwork  const & network
                                                 , FUNCTION          function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );
                for_all_generator_identifiers_at ( vertexId, network, function );
            }

            /**
             * @brief      The parallel @p for loop over all generator objects
             *     at a vertex identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a generator object as input.
             *
             * @code{.cpp}
             *      []( TGeneratorProperties & generator )
             *      {
             *          Do something with the generator object at the @p vertexId.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator properties at @p vertexId.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generators_at ( Types::vertexId const vertexId
                                       , TNetwork            & network
                                       , FUNCTION              function )
            {
                for_all_generator_identifiers_at ( vertexId,
                    [ &network, &function ]( Types::generatorId generatorId )
                    {
                        function ( network.generators_[generatorId] );
                    }
                );
            }

            /**
             * @brief      The parallel @p for loop over all generator objects
             *     at a vertex identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a generator object as input.
             *
             * @code{.cpp}
             *      []( TGeneratorProperties const & generator )
             *      {
             *          Do something with the generator object at the @p vertexId.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator properties at @p vertexId.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generators_at ( Types::vertexId const   vertexId
                                       , TNetwork        const & network
                                       , FUNCTION                function )
            {
                for_all_generator_identifiers_at ( vertexId,
                    [ &network, &function ]( Types::generatorId generatorId )
                    {
                        function ( network.generators_[generatorId] );
                    }
                );
            }

            /**
             * @brief      The parallel @p for loop over all generator objects
             *     at a @p vertex.
             *
             * @param      vertex    The vertex object.
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a generator object as input.
             *
             * @code{.cpp}
             *      []( TGeneratorProperties & generator )
             *      {
             *          Do something with the generator object at the @p vertex.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator properties at @p vertex.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generators_at ( TVertex  const & vertex
                                       , TNetwork       & network
                                       , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );
                for_all_generators_at ( vertexId, network, function );
            }

            /**
             * @brief      The parallel @p for loop over all generator objects
             *     at a @p vertex.
             *
             * @param      vertex    The vertex object.
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a generator object as input.
             *
             * @code{.cpp}
             *      []( TGeneratorProperties const & generator )
             *      {
             *          Do something with the generator object at the @p vertex.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION  The type of the function object.
             */
            template<typename FUNCTION>
            inline static
            void for_all_generators_at ( TVertex  const & vertex
                                       , TNetwork const & network
                                       , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );
                for_all_generators_at ( vertexId, network, function );
            }

            /**
             * @brief      The parallel @p for loop over @c all vertices@c
             *     that have a generator and its @c generator objects@c.
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and a
             *      @c generator object@c as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId
             *        , TGeneratorProperties & generatorProperties )
             *      {
             *          Do something with the vertexId and the generator object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator tuple (vertexId, generatorProperties).
             */
            template<typename FUNCTION>
            inline static
            void for_all_generator_tuple ( TNetwork & network
                                         , FUNCTION   function )
            {
                #pragma omp parallel for
                    for ( Types::vertexId index = 0
                        ; index < network.Graph().Vertices().size()
                        ; ++index )
                    {
                        if ( network.HasGeneratorAt(index) )
                        {
                            std::vector<TGeneratorProperties> generators;
                            network.GeneratorsAt(index, generators);
                            for ( TGeneratorProperties & generator : generators )
                            {
                                function( index, generator);
                            }
                        }
                    }
            }

            /**
             * @brief      The parallel @p for loop over @c all vertices@c
             *     that have a generator and its @c generator objects@c.
             *
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and a
             *      @c generator object@c as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId, TGeneratorProperties const & generator )
             *      {
             *          Do something with the vertexId and the generator object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator tuple (vertexId, generatorProperties).
             */
            template<typename FUNCTION>
            inline static
            void for_all_generator_tuple ( TNetwork const & network
                                         , FUNCTION         function )
            {
                #pragma omp parallel for
                    for ( Types::vertexId index = 0
                        ; index < network.Graph().Vertices().size()
                        ; ++index )
                    {
                        if ( network.HasGeneratorAt(index) )
                        {
                            std::vector<TGeneratorProperties> generators;
                            network.GeneratorsAt(index, generators);
                            for ( TGeneratorProperties & generator : generators ) {
                                function( index, generator);
                            }
                        }
                    }
            }

            /**
             * @brief      The parallel @p for loop over @c all vertices@c that
             *     have a generator.
             *
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and its
             *      @c generator objects@c as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId
             *        , std::vector<TGeneratorProperties> & generators )
             *      {
             *          Do something with the set of generators at the vertexId
             *          and identifier of the vertex that has generators.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all generator tuple (vertexId, vector of generatorProperties).
             */
            template<typename FUNCTION>
            inline static
            void for_all_generators_tuple ( TNetwork const & network
                                          , FUNCTION         function )
            {
                #pragma omp parallel for
                    for ( Types::vertexId index = 0
                        ; index < network.Graph().Vertices().size()
                        ; ++index )
                    {
                        if ( network.HasGeneratorAt(index) )
                        {
                            std::vector<TGeneratorProperties> generators;
                            network.GeneratorsAt(index, generators);
                            function( index, generators);
                        }
                    }
            }
        ///@}

#pragma mark PARALLEL_GENERATOR_SNAPSHOT_LOOP
        /**
         * @brief      The parallel @c for loop @c over all generator maximum real
         *     power p.u. snapshots.
         *
         * @param      network     The network @f$\network = ( \graph,
         *         \generators, \consumers, \capacity, \susceptance, \dots)@f$.
         * @param[in]  function    The function, e.g., lambda function.
         *
         * @code{.cpp}
         *      for_all_real_power_generator_snapshots<ExecutionPolicy::parallel>(
         *          network,
         *          []( Types::index             snapshotId
         *            , Types::generatorSnapshot snapshot )
         *          {
         *              // Do something with the snapshotId and generator snapshot object.
         *          }
         *      );
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power generator snapshots.
         */
        ///@{
            template<typename FUNCTION>
            inline
            void for_all_real_power_generator_snapshots ( TNetwork & network
                                                        , FUNCTION   function )
            {
                #pragma omp parallel for
                    for ( Types::index generatorId = 0
                        ; generatorId < network.generatorRealPowerSnapshots_.size()
                        ; ++generatorId )
                    {
                        for_all_real_power_generator_snapshots_of ( network, generatorId, function );
                    }
            }

            template<typename FUNCTION>
            inline
            void for_all_real_power_generator_snapshots ( TNetwork const & network
                                                        , FUNCTION         function ) const
            {
                #pragma omp parallel for
                    for ( Types::index generatorId = 0
                        ; generatorId < network.generatorRealPowerSnapshots_.size()
                        ; ++generatorId )
                    {
                        for_all_real_power_generator_snapshots_of ( network, generatorId, function );
                    }
            }
        ///@}

        /**
         * @brief      The parallel @c for loop @c over all maximum real power
         *     p.u. snapshots of a generator with @p generatorId.
         *
         * @param      network     The network @f$\network = ( \graph,
         *         \generators, \consumers, \capacity, \susceptance, \dots)@f$.
         * @param      generatorId The identifier of the generator.
         * @param[in]  function    The function, e.g., lambda function.
         *
         * @pre        Check if the generator identifier @p generatorId of the
         *     generatorProperties exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.HasGenerator ( generatorId ) )
         *      {
         *          for_all_real_power_generator_snapshots_of<ExecutionPolicy::parallel> (
         *              network,
         *              generatorId,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  // Do something with the snapshotId and generator snapshot object.
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power generator snapshots at @p generatorId.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_of ( TNetwork         & network
                                                           , Types::generatorId generatorId
                                                           , FUNCTION           function    )
            {
                USAGE_ASSERT ( network.HasGenerator ( generatorId ) );

                #pragma omp parallel for
                    for ( Types::index snapshotId = 0
                        ; snapshotId < network.generatorRealPowerSnapshots_[generatorId].size()
                        ; ++snapshotId )
                    { // snapshotId corresponds to row
                        function( snapshotId, network.generatorRealPowerSnapshots_[generatorId][snapshotId] );
                    }
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_of ( TNetwork   const & network
                                                           , Types::generatorId generatorId
                                                           , FUNCTION           function    )
            {
                USAGE_ASSERT ( network.HasGenerator ( generatorId ) );

                #pragma omp parallel for
                    for ( Types::index snapshotId = 0
                        ; snapshotId < network.generatorRealPowerSnapshots_[generatorId].size()
                        ; ++snapshotId )
                    { // snapshotId corresponds to row
                        function( snapshotId, network.generatorRealPowerSnapshots_[generatorId][snapshotId] );
                    }
            }
        ///@}

        /**
         * @brief      The parallel @c for loop @c over all maximum real power
         *     p.u. snapshots of a @p generatorProperties.
         *
         * @param      network              The network @f$\network = ( \graph,
         *         \generators, \consumers, \capacity, \susceptance, \dots)@f$.
         * @param      generatorProperties  The generator properties.
         * @param[in]  function             The function, e.g. , lambda function.
         *
         * @pre        Check if the generator identifier @p generatorId of the
         *     generatorProperties exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.HasGenerator ( network.GeneratorId ( generatorProperties ) ) )
         *      {
         *          for_all_real_power_generator_snapshots_of<ExecutionPolicy::parallel> (
         *              network,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  // Do something with the snapshotId and generator snapshot object.
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power generator snapshots of @p generatorProperties.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_of ( TNetwork                   & network
                                                           , TGeneratorProperties const & generatorProperties
                                                           , FUNCTION                     function )
            {
                Types::generatorId generatorId = network.GeneratorId( generatorProperties );

                USAGE_ASSERT ( network.HasGenerator ( generatorId ) );

                for_all_real_power_generator_snapshots_of ( network, generatorId, function );
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_of ( TNetwork             const & network
                                                           , TGeneratorProperties const & generatorProperties
                                                           , FUNCTION                     function  )
            {
                Types::generatorId generatorId = network.GeneratorId( generatorProperties );

                USAGE_ASSERT ( network.HasGenerator ( generatorId ) );

                for_all_real_power_generator_snapshots_of ( network, generatorId, function );
            }
        ///@}

        /**
         * @brief      The parallel @c for loop @c over all generator maximum
         *     real power p.u. snapshots at a vertex with @p vertexId.
         *
         * @param      network     The network @f$\network = ( \graph,
         *         \generators, \consumers, \capacity, \susceptance, \dots)@f$.
         * @param      vertexId    The identifier of a vertex.
         * @param[in]  function    The function, e.g. , lambda function.
         *
         * @pre        Check if the vertex identifier @p vertexId of the
         *     vertex exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( vertexId ) )
         *      {
         *          for_all_real_power_generator_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertexId,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  // Do something with the snapshotId and generator snapshot object.
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power generator snapshots at @p vertexId.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork       & network
                                                           , Types::vertexId  vertexId
                                                           , FUNCTION         function )
            {
                USAGE_ASSERT ( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::generatorId> generatorIds;
                network.GeneratorAt( vertexId, generatorIds );

                #pragma omp parallel for
                    for ( Types::index index = 0
                        ; index < generatorIds.size()
                        ; ++index )
                    {
                        for_all_real_power_generator_snapshots_of ( network, generatorIds[index], function );
                    }
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork const & network
                                                           , Types::vertexId  vertexId
                                                           , FUNCTION         function )
            {
                USAGE_ASSERT ( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::generatorId> generatorIds;
                network.GeneratorAt( vertexId, generatorIds );

                #pragma omp parallel for
                    for ( Types::index index = 0
                        ; index < generatorIds.size()
                        ; ++index )
                    {
                        for_all_real_power_generator_snapshots_of ( network, generatorIds[index], function );
                    }
            }
        ///@}

        /**
         * @brief      The parallel @c for loop @c over all generator maximum
         *     real power p.u. snapshots at a @p vertex.
         *
         * @param      network     The network @f$\network = ( \graph,
         *         \generators, \consumers, \capacity, \susceptance, \dots)@f$.
         * @param      vertex      The vertex.
         * @param[in]  function    The function, e.g., lambda function.
         *
         * @pre        Check if the vertex identifier @p vertexId of the
         *     vertex exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( network.Graph().VertexId( vertex ) ) )
         *      {
         *          for_all_real_power_generator_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertex,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  // Do something with the snapshotId and generator snapshot object.
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power generator snapshots at @p vertex.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork & network
                                                           , TVertex    vertex
                                                           , FUNCTION   function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::generatorId> generatorIds;
                network.GeneratorAt( vertexId, generatorIds );

                for_all_real_power_generator_snapshots_at ( network, vertexId, function );
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork const & network
                                                           , TVertex          vertex
                                                           , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::generatorId> generatorIds;
                network.GeneratorAt( vertexId, generatorIds );

                for_all_real_power_generator_snapshots_at ( network, vertexId, function );
            }
        ///@}

        /**
         * @brief      The sequential @c for loop @c over snapshots with a
         *     certain @ timestampPosition for all @p generators.
         * @details    This loop basically extracts a row.
         *
         * @param      network              The network @f$\network = ( \graph,
         *         \generators, \consumers, \capacity, \susceptance, \dots)@f$.
         * @param      vertexId             The identifier of a vertex
         * @param      timestampPosition    The position of the snapshot
         *     (timestamp of the snapshot).
         * @param[in]  function             The function, e.g. , lambda function
         *
         * @pre        Check if the vertex identifier @p vertexId of the
         *     vertex exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( vertexId ) )
         *      {
         *          for_all_real_power_generator_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertexId,
         *              timestampPosition,
         *              []( Types::loadSnapshot snapshot )
         *              {
         *                  Do something with the snapshotId and load snapshot object
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power generator at @p timestamp at @p vertex.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork &      network
                                                           , Types::vertexId vertexId
                                                           , Types::index    timestampPosition
                                                           , FUNCTION        function )
            {
                USAGE_ASSERT( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::generatorId> generatorIds;
                network.GeneratorIds ( vertexId, generatorIds );

                #pragma omp parallel for
                    for ( Types::index generatorId = 0
                        ; generatorId < generatorIds.size()
                        ; ++generatorId )
                    {
                        function ( network.GeneratorSnapshotOf( generatorIds[generatorId], timestampPosition ) );
                    }
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork   const & network
                                                           , Types::vertexId    vertexId
                                                           , Types::index       timestampPosition
                                                           , FUNCTION           function )
            {
                USAGE_ASSERT( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::generatorId> generatorIds;
                network.GeneratorIds ( vertexId, generatorIds );

                #pragma omp parallel for
                    for ( Types::index generatorId = 0
                        ; generatorId < generatorIds.size()
                        ; ++generatorId )
                    {
                        function ( network.GeneratorSnapshotOf( generatorIds[generatorId], timestampPosition ) );
                    }
            }
        ///@}

        /**
         * @brief      The @c for loop @c over all real power snapshots of a
         *     @p generator and a timestamp at @p timestampPosition.
         *
         * @param      network              The network @f$\network = ( \graph,
         *         \generators, \consumers, \capacity, \susceptance, \dots)@f$.
         * @param      vertex               The vertex
         * @param[in]  timestampPosition    The timestamp position
         * @param[in]  function             The function
         *
         * @pre        Check if the vertex identifier @p vertexId of the
         *     vertex exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( vertexId ) )
         *      {
         *          for_all_real_power_generator_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertex,
         *              timestampPosition,
         *              []( Types::loadSnapshot snapshot )
         *              {
         *                  Do something with the snapshotId and load snapshot object
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load at @p timestamp at @p vertex.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork      & network
                                                           , TVertex const & vertex
                                                           , Types::index    timestampPosition
                                                           , FUNCTION        function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists ( vertexId ) );

                for_all_real_power_generator_snapshots_at ( network, vertexId, timestampPosition, function );
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_generator_snapshots_at ( TNetwork const & network
                                                           , TVertex  const & vertex
                                                           , Types::index     timestampPosition
                                                           , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists ( vertexId ) );

                for_all_real_power_generator_snapshots_at ( network, vertexId, timestampPosition, function );
            }
        ///@}

        ///@name Parallel Load Loops
        ///@{
#pragma mark PARALLEL_LOAD_LOOPS

            /**
             * @brief      The parallel @p for loop over all @p loads (vertex
             *     independent).
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a load object as input.
             *
             * @code{.cpp}
             *      []( TLoadProperties & load )
             *      {
             *          Do something with the load object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all loads.
             */
            template<typename FUNCTION>
            inline static
            void for_all_loads ( TNetwork & network
                               , FUNCTION   function )
            {
                #pragma omp parallel for
                    for ( Types::loadId loadId = 0
                        ; loadId < network.loads_.size()
                        ; ++loadId )
                    {
                        function ( network.loads_[loadId] );
                    }
            }

            /**
             * @brief      The parallel @p for loop over all @p loads (vertex
             *     independent).
             *
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a const load object as input.
             *
             * @code{.cpp}
             *      []( TLoadProperties const & load )
             *      {
             *          Do something with the load object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all loads.
             */
            template<typename FUNCTION>
            inline static
            void for_all_loads ( TNetwork const & network
                               , FUNCTION         function )
            {
                #pragma omp parallel for
                    for ( Types::loadId loadId = 0
                        ; loadId < network.loads_.size()
                        ; ++loadId )
                    {
                        function ( network.loads_[loadId] );
                    }
            }

            /**
             * @brief      The parallel @p for loop over all @p vertices that
             *     have a load.
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a vertex identifier @p Types::vertexId
             *      as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId )
             *      {
             *          Do something with the vertex identifier that has loads.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all vertex identifiers that have a load.
             */
            template<typename FUNCTION>
            inline static
            void for_all_vertex_identifiers_with_load ( TNetwork const & network
                                                      , FUNCTION         function )
            {
                Types::vertexId vertexIdSafeguard = 0;
                #pragma omp parallel for
                    for ( Types::vertexId vertexId = 0
                        ; vertexId < network.Graph().Vertices().size()
                        ; ++vertexId )
                    {
                        if (   network.HasLoadAt(vertexId)
                            && network.Graph().VertexExists(vertexId) )
                        {
                            vertexIdSafeguard = vertexId;
                            function ( vertexIdSafeguard );
                        }
                    }
            }

            /**
             * @brief      The parallel @p for loop over all load identifiers
             *     at a vertex identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a load identifier @p Types::loadId as
             *      input.
             *
             * @code{.cpp}
             *      []( Types::loadId loadId )
             *      {
             *          Do something with the load identifier at the @p vertex.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all vertex identifiers that have a load.
             */
            template<typename FUNCTION>
            inline static
            void for_all_load_identifiers_at ( Types::vertexId  vertexId
                                             , TNetwork const & network
                                             , FUNCTION         function )
            {
                if (   network.HasLoadAt ( vertexId )
                    && network.Graph().VertexExists ( vertexId ) )
                {
                    #pragma omp parallel for
                        for ( Types::index index = 0
                            ; index < network.loadsAtVertex_[vertexId].size()
                            ; ++index )
                        {
                            function ( network.loadsAtVertex_[vertexId][index] );
                        }
                }
            }

            /**
             * @brief      The parallel @p for loop over all load identifiers
             *     at a vertex.
             *
             * @param      vertex    The vertex object.
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a load identifier as input.
             *
             * @code{.cpp}
             *      []( Types::loadId loadId )
             *      {
             *          Do something with the load identifier at the @p vertex.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all vertex identifiers at @p vertex.
             */
            template<typename FUNCTION>
            inline static
            void for_all_load_identifiers_at ( TVertex  const & vertex
                                             , TNetwork const & network
                                             , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );
                for_all_load_identifiers_at ( vertexId, network, function );
            }

            /**
             * @brief      The parallel @p for loop over all load objects at a
             *     @p vertex.
             *
             * @param      vertex    The vertex object.
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a load object as input.
             *
             * @code{.cpp}
             *      []( TLoadProperties & load )
             *      {
             *          Do something with the load object at the @p vertex.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all load properties at @p vertex.
             */
            template<typename FUNCTION>
            inline static
            void for_all_loads_at ( TVertex  const & vertex
                                  , TNetwork       & network
                                  , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );
                for_all_loads_at ( vertexId, network, function );
            }

            /**
             * @brief      The parallel @p for loop over all load objects at a
             *     @p vertex.
             *
             * @param      vertex    The vertex object.
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a load object as input.
             *
             * @code{.cpp}
             *      []( TLoadProperties const & load )
             *      {
             *          Do something with the load object at the @p vertex.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all load properties at @p vertex.
             */
            template<typename FUNCTION>
            inline static
            void for_all_loads_at ( TVertex  const & vertex
                                  , TNetwork const & network
                                  , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );
                for_all_loads_at ( vertexId, network, function );
            }

            /**
             * @brief      The parallel @p for loop over all load objects at a
             *     vertex identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a load object as input.
             *
             * @code{.cpp}
             *      []( TLoadProperties & load )
             *      {
             *          Do something with the load object at the @p vertexId.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all load properties at @p vertexId.
             */
            template<typename FUNCTION>
            inline static
            void for_all_loads_at ( Types::vertexId const vertexId
                                  , TNetwork            & network
                                  , FUNCTION              function )
            {
                for_all_load_identifiers_at ( vertexId, network,
                    [ &network, &function ]( Types::loadId loadId )
                    {
                        function ( network.loads_[loadId] );
                    }
                );
            }

            /**
             * @brief      The parallel @p for loop over all load objects at a
             *     vertex identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a load object as input.
             *
             * @code{.cpp}
             *      []( TLoadProperties const & load )
             *      {
             *          Do something with the load object at the @p vertexId.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all load properties at @p vertexId.
             */
            template<typename FUNCTION>
            inline static
            void for_all_loads_at ( Types::vertexId const   vertexId
                                  , TNetwork        const & network
                                  , FUNCTION                function )
            {
                for_all_load_identifiers_at ( vertexId, network,
                    [ &network, &function ]( Types::loadId loadId )
                    {
                        function ( network.loads_[loadId] );
                    }
                );
            }

            /**
             * @brief      The parallel @p for loop over @c all vertices@c that
             *     have a load and its @c load objects@c.
             *
             * @param      network   The network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and a
             *      @c load object@c as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId, TLoadProperties & load )
             *      {
             *          Do something with the vertexId and load object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all load tuples (vertexId, loadProperties).
             */
            template<typename FUNCTION>
            inline static
            void for_all_load_tuples ( TNetwork & network
                                     , FUNCTION   function )
            {
                Types::vertexId vertexIdSafeguard = 0;
                #pragma omp parallel for
                    for ( Types::vertexId vertexId = 0
                        ; vertexId < network.Graph().Vertices().size()
                        ; ++vertexId )
                    {
                        if ( network.HasLoadAt(vertexId) )
                        {
                            for ( Types::loadId loadId : network.loadsAtVertex_[vertexId] )
                            {
                                vertexIdSafeguard = vertexId;
                                function( vertexIdSafeguard, network.loads_[loadId] );
                            }
                        }
                    }
            }

            /**
             * @brief      The parallel @p for loop over @c all vertices@c that
             *     have a load and its @c load objects@c.
             *
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and a
             *      @c load object@c as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId, TLoadProperties const & load )
             *      {
             *          Do something with the vertexId and load object.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all load tuples (vertexId, loadProperties).
             */
            template<typename FUNCTION>
            inline static
            void for_all_load_tuples ( TNetwork const & network
                                     , FUNCTION         function )
            {
                Types::vertexId vertexIdSafeguard = 0;
                #pragma omp parallel for
                    for ( Types::vertexId vertexId = 0
                        ; vertexId < network.Graph().Vertices().size()
                        ; ++vertexId )
                    {
                        if ( network.HasLoadAt(vertexId) )
                        {
                            for ( Types::loadId loadId : network.loadsAtVertex_[vertexId] )
                            {
                                vertexIdSafeguard = vertexId;
                                function( vertexIdSafeguard, network.loads_[loadId] );
                            }
                        }
                    }
            }

            /**
             * @brief      The parallel @p for loop over @c all vertices@c that
             *     have a load.
             *
             * @param      network   The const network @f$\network = ( \graph,
             *     \generators, \consumers, \capacity, \susceptance, \dots
             *     )@f$.
             * @param[in]  function  The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and its
             *      @c load objects@c as input.
             *
             * @code{.cpp}
             *      []( Types::vertexId vertexId, std::vector<TLoadProperties> & loads )
             *      {
             *          Do something with the set of loads at the vertexId
             *          and identifier of the vertex that has loads.
             *      }
             * @endcode
             *
             * @tparam     FUNCTION    The function object that is called for
             *     all load tuples (vertexId, vector of loadProperties).
             */
            template<typename FUNCTION>
            inline static
            void for_all_loads_tuple ( TNetwork const & network
                                     , FUNCTION         function )
            {
                Types::vertexId vertexIdSafeguard = 0;
                #pragma omp parallel for
                    for ( Types::vertexId vertexId = 0
                        ; vertexId < network.Graph().Vertices().size()
                        ; ++vertexId )
                    {
                        if ( network.HasLoadAt(vertexId) )
                        {
                            std::vector<TLoadProperties> loads;
                            network.LoadsAt ( vertexId, loads );
                            vertexIdSafeguard = vertexId;
                            function( vertexIdSafeguard, loads );
                        }
                    }
            }
        ///@}

#pragma mark PARALLEL_LOAD_SNAPSHOT_LOOPS

        /**
         * @brief      The parallel @c for loop @c over all load real power
         *     snapshots.
         *
         * @param      network     The network
         * @param[in]  function    The function, e.g., lambda function.
         *
         * @code{.cpp}
         *      for_all_real_power_load_snapshots<ExecutionPolicy::parallel>(
         *          network,
         *          []( Types::index        snapshotId
         *            , Types::loadSnapshot snapshot )
         *          {
         *              Do something with the snapshotId and load snapshot object
         *          }
         *      );
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load snapshots.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots ( TNetwork & network
                                                   , FUNCTION   function )
            {
                #pragma omp parallel for
                    for ( Types::loadId loadId = 0
                        ; loadId < network.loadSnapshots_.size()
                        ; ++loadId )
                    {
                        for_all_real_power_load_snapshots_of ( network
                                                             , loadId
                                                             , function );
                    }
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots ( TNetwork const & network
                                                   , FUNCTION         function )
            {
                #pragma omp parallel for
                    for ( Types::loadId loadId = 0
                        ; loadId < network.loadSnapshots_.size()
                        ; ++loadId )
                    {
                        for_all_real_power_load_snapshots_of ( network
                                                             , loadId
                                                             , function );
                    }
            }
        ///@}

        /**
         * @brief      The parallel @c for loop @c over all real power
         *     snapshots of a load with @p loadId.
         *
         * @param      network     The network.
         * @param      loadId      The identifier of the load.
         * @param[in]  function    The function, e.g., lambda function.
         *
         * @pre        Check if the load identifier @p loadId of the
         *     loadProperties exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.HasLoad ( loadId ) )
         *      {
         *          for_all_real_power_load_snapshots_of<ExecutionPolicy::sequential> (
         *              network,
         *              loadId,
         *              []( Types::index snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  Do something with the snapshotId and load snapshot object
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load snapshots at @p loadId.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_of ( TNetwork &    network
                                                      , Types::loadId loadId
                                                      , FUNCTION      function )
            {
                USAGE_ASSERT ( network.HasLoad ( loadId ) );

                #pragma omp parallel for
                    for ( Types::index timestampPosition = 0
                        ; timestampPosition < network.loadSnapshots_.size()
                        ; ++timestampPosition )
                    {
                        function ( timestampPosition
                                 , network.LoadSnapshotOf( loadId, timestampPosition ) );
                    }
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_of ( TNetwork const & network
                                                      , Types::loadId    loadId
                                                      , FUNCTION         function )
            {
                #pragma omp parallel for
                    for ( Types::index timestampPosition = 0
                        ; timestampPosition < network.loadSnapshots_.size()
                        ; ++timestampPosition )
                    {
                        function ( timestampPosition
                                 , network.LoadSnapshotOf( loadId, timestampPosition ) );
                    }
            }
        ///@}


        /**
         * @brief      The parallel @c for loop @c over all real power
         *     snapshots of a @p load.
         *
         * @param      network          The network.
         * @param      loadProperties   The load properties.
         * @param[in]  function         The function, e.g. , lambda function.
         *
         * @pre        Check if the load identifier @p loadId of the
         *     loadProperties exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.HasLoad ( network.LoadId ( loadProperties ) ) )
         *      {
         *          for_all_real_power_load_snapshots_of<ExecutionPolicy::sequential> (
         *              network,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  Do something with the snapshotId and load snapshot object
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load snapshots at @p load.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_of ( TNetwork &      network
                                                      , TLoadProperties loadProperties
                                                      , FUNCTION        function )
            {
                Types::loadId loadId = network.LoadId ( loadProperties );

                USAGE_ASSERT ( network.HasLoad ( loadId ) );

                for_all_real_power_load_snapshots_of ( network, loadId, function );
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_of ( TNetwork const & network
                                                      , TLoadProperties  loadProperties
                                                      , FUNCTION         function )
            {
                Types::loadId loadId = network.LoadId ( loadProperties );

                USAGE_ASSERT ( network.HasLoad ( loadId ) );

                for_all_real_power_load_snapshots_of ( network, loadId, function );
            }
        ///@}

        /**
         * @brief      The parallel @c for loop @c over all real power
         *     snapshots of a @p load.
         *
         * @param      network     The network
         * @param      vertexId    The identifier of a vertex
         * @param[in]  function    The function, e.g. , lambda function
         *
         * @pre        Check if the vertex identifier @p vertexId of the
         *     vertex exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( vertexId ) )
         *      {
         *          for_all_real_power_load_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertexId,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  Do something with the snapshotId and load snapshot object }
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load snapshots at @p vertexId.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork &      network
                                                      , Types::vertexId vertexId
                                                      , FUNCTION        function )
            {
                USAGE_ASSERT( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::loadId> loadIds;
                network.LoadIds ( vertexId, loadIds );

                #pragma omp parallel for
                    for ( Types::index loadId = 0
                        ; loadId < loadIds.size()
                        ; ++loadId )
                    {
                        for_all_real_power_load_snapshots_of ( network, loadId, function );
                    }
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork const & network
                                                      , Types::vertexId  vertexId
                                                      , FUNCTION         function )
            {
                USAGE_ASSERT( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::loadId> loadIds;
                network.LoadIds ( vertexId, loadIds );

                #pragma omp parallel for
                    for ( Types::index loadId = 0
                        ; loadId < loadIds.size()
                        ; ++loadId )
                    {
                        for_all_real_power_load_snapshots_of ( network, loadId, function );
                    }
            }
        ///@}

        /**
         * @brief      The parallel @c for loop @c over all real power
         *     snapshots of a @p load.
         *
         * @param      network     The network
         * @param      vertex      The vertex
         * @param[in]  function    The function, e.g. , lambda function
         *
         * @pre        Check if the vertex identifier @p vertexId of the
         *     vertex exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( network.Graph().VertexId( vertex ) ) )
         *      {
         *          for_all_real_power_load_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertex,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  Do something with the snapshotId and load snapshot object
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load at @p timestamp at @p vertex.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork & network
                                                      , TVertex    vertex
                                                      , FUNCTION   function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists ( vertexId ) );

                for_all_real_power_load_snapshots_at ( network, vertexId, function );
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork const & network
                                                      , TVertex          vertex
                                                      , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists ( vertexId ) );

                for_all_real_power_load_snapshots_at ( network, vertexId, function );
            }
        ///@}

        /**
         * @brief      The sequential @c for loop @c over snapshots with a
         *     certain @ timestampPosition for all @p load.
         * @details    This loop basically extracts a row.
         *
         * @param      network              The network
         * @param      vertexId             The identifier of a vertex
         * @param      timestampPosition    The position of the snapshot
         *     (timestamp of the snapshot).
         * @param[in]  function             The function, e.g. , lambda function
         *
         * @pre        Check if the vertex identifier @p vertexId of the
         *     vertex exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( vertexId ) )
         *      {
         *          for_all_real_power_load_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertexId,
         *              timestampPosition,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  Do something with the snapshotId and load snapshot object
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load at @p timestamp at @p vertex.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork &      network
                                                      , Types::vertexId vertexId
                                                      , Types::index    timestampPosition
                                                      , FUNCTION        function )
            {
                USAGE_ASSERT( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::loadId> loadIds;
                network.LoadIds ( vertexId, loadIds );

                #pragma omp parallel for
                    for ( Types::index loadId = 0
                        ; loadId < loadIds.size()
                        ; ++loadId )
                    {
                        function ( network.LoadSnapshotOf( loadId, timestampPosition ) );
                    }
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork   const & network
                                                      , Types::vertexId    vertexId
                                                      , Types::index       timestampPosition
                                                      , FUNCTION           function )
            {
                USAGE_ASSERT( network.Graph().VertexExists( vertexId ) );

                std::vector<Types::loadId> loadIds;
                network.LoadIds ( vertexId, loadIds );

                #pragma omp parallel for
                    for ( Types::index loadId = 0
                        ; loadId < loadIds.size()
                        ; ++loadId )
                    {
                        function ( network.LoadSnapshotOf( loadId, timestampPosition ) );
                    }
            }
        ///@}

        /**
         * @brief      The @c for loop @c over all real power snapshots of a
         *     @p load and a timestamp at @p timestampPosition.
         *
         * @param      network              The network
         * @param      vertex               The vertex
         * @param[in]  timestampPosition    The timestamp position
         * @param[in]  function             The function
         *
         * @pre        Check if the vertex identifier @p vertexId of the
         *     vertex exists before using this method.
         *
         * @code{.cpp}
         *      if ( network.Graph().VertexExists( vertexId ) )
         *      {
         *          for_all_real_power_load_snapshots_at<ExecutionPolicy::sequential> (
         *              network,
         *              vertex,
         *              timestampPosition,
         *              []( Types::index        snapshotId
         *                , Types::loadSnapshot snapshot )
         *              {
         *                  Do something with the snapshotId and load snapshot object
         *              }
         *          );
         *      }
         * @endcode
         *
         * @tparam     FUNCTION    The function object that is called for
         *     all real power load at @p timestamp at @p vertex.
         */
        ///@{
            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork      & network
                                                      , TVertex const & vertex
                                                      , Types::index    timestampPosition
                                                      , FUNCTION        function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists ( vertexId ) );

                for_all_real_power_load_snapshots_at ( network, vertexId, timestampPosition, function );
            }

            template<typename FUNCTION>
            inline static
            void for_all_real_power_load_snapshots_at ( TNetwork const & network
                                                      , TVertex  const & vertex
                                                      , Types::index     timestampPosition
                                                      , FUNCTION         function )
            {
                Types::vertexId vertexId = network.Graph().VertexId( vertex );

                USAGE_ASSERT ( network.Graph().VertexExists ( vertexId ) );

                for_all_real_power_load_snapshots_at ( network, vertexId, timestampPosition, function );
            }
        ///@}
};

#else // OPENMP_AVAILABLE

/**
 * @brief      If OpenMP is not available, fall back to sequential execution
 *     of the loops.
 *
 * @tparam     PowerGridType  The type of the power grid.
 */
template<typename PowerGridType>
class PowerGridLoopDifferentiation<PowerGridType, ExecutionPolicy::parallel>
    : public PowerGridLoopDifferentiation<PowerGridType, ExecutionPolicy::sequential> {};

#endif // OPENMP_AVAILABLE

} // namespace egoa::internal

#endif // EGOA__DATASTRUCTURES__GRAPHS__ITERATORS__POWER_GRID_ITERATORS_HPP

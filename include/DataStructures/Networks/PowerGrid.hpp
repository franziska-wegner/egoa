/*
 * PowerGrid.hpp
 *
 *  Created on: Sep 16, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__GRAPHS__POWER_GRID_HPP
#define EGOA__DATA_STRUCTURES__GRAPHS__POWER_GRID_HPP

// for assert
#include "Exceptions/Assertions.hpp"

#include <algorithm>
#include <iterator>

#include <QDebug>

#include "Auxiliary/ExecutionPolicy.hpp"

#include "DataStructures/Graphs/DynamicGraph.hpp"
#include "DataStructures/Graphs/StaticGraph.hpp"
#include "DataStructures/Graphs/Subgraph.hpp"

#include "DataStructures/Graphs/Vertices/ElectricalProperties.hpp"
#include "DataStructures/Graphs/Vertices/LoadProperties.hpp"
#include "DataStructures/Graphs/Vertices/GeneratorProperties.hpp"
#include "DataStructures/Graphs/Vertices/Type.hpp"

#include "DataStructures/Graphs/Edges/ElectricalProperties.hpp"

#include "DataStructures/Iterators/PowerGridIterators.hpp"

#include "DataStructures/Networks/GenerationStrategy.hpp"

namespace egoa {

template <  typename GraphType           = StaticGraph < Vertices::ElectricalProperties<Vertices::IeeeBusType>,
                                                         Edges::ElectricalProperties>,
            typename GeneratorProperty   = Vertices::GeneratorProperties<Vertices::IeeeBusType>,
            typename LoadProperty        = Vertices::LoadProperties<Vertices::IeeeBusType> >
class PowerGrid {
    public:
        // Template type aliasing
        // Vertices
        using TVertex               = typename GraphType::TVertex;
        using TVertexProperties     = typename GraphType::TVertexProperties;
        using TGeneratorProperties  = GeneratorProperty; //GeneratorType;
        using TLoadProperties       = LoadProperty;  // LoadType;
        // Edges
        using TEdge                 = typename GraphType::TEdge;
        using TEdgeProperties       = typename GraphType::TEdgeProperties;
        // Graph structures
        using TGraph                = GraphType;
        using TNetwork              = PowerGrid;
        // Others
        using TBound                = Bound<>;

    public:
        ///@name Constructors and destructor
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTOR
            
            /**
             * @brief      Constructs the object.
             */
            PowerGrid()
            : baseMva_(1.0)
            , thetaBound_( -Const::REAL_INFTY, Const::REAL_INFTY )
            , verticesWithGeneratorCount_(0)
            , numberOfGenerators_(0)
            , numberOfLoads_(0)
            , generatorBoundType_(Vertices::BoundType::unknown)
            , loadBoundType_(Vertices::BoundType::unknown)
            , graph_()
            {}
        ///@}
    
    public:
        /**@name Getter and Setter */
        ///@{
#pragma mark GETTER_AND_SETTER

            /**
             * @brief      Getter for the underlying graph.
             *
             * @return     The underlying graph.
             */
            inline TGraph const & Graph() const 
            { 
                return graph_; 
            }

            /**
             * @brief      Setter for the underlying graph.
             *
             * @return     The underlying graph.
             */
            inline TGraph & Graph()
            { 
                return graph_; 
            }

            /**
             * @brief      Getter for the base MVA.
             *
             * @return     The power grid's base MVA.
             */
            inline Types::real BaseMva() const 
            { 
                return baseMva_;
            }

            /**
             * @brief      Setter for the base MVA.
             *
             * @return     The power grid's base MVA.
             */
            inline Types::real & BaseMva()
            { 
                return baseMva_;
            }

            /**
             * @brief      Getter for the voltage angle bound.
             *
             * @return     The voltage angle bound.
             */
            inline TBound ThetaBound () const 
            { 
                return thetaBound_;
            }

            /**
             * @brief      Setter for the voltage angle bound.
             *
             * @return     The voltage angle bound.
             */
            inline TBound & ThetaBound () 
            { 
                return thetaBound_;
            }
        ///@}

        ///@name Network Bound Accessors
        ///@{
#pragma mark BOUND_RELATED_METHODS

            /**
             * @brief      Getter for the generator bound type.
             * @pre        The default value is @p unknown.
             *
             * @return     The generator vertex bound type.
             */
            inline Vertices::BoundType const & GeneratorBoundType () const 
            { 
                return generatorBoundType_;
            }

            /**
             * @brief      Setter for the generator bound type.
             * @pre        The default value is @p unknown.
             *
             * @return     The generator vertex bound type.
             */
            inline Vertices::BoundType & GeneratorBoundType () 
            { 
                return generatorBoundType_;
            }

            /**
             * @brief      Getter for the load bound type.
             * @pre        The default value is @p unknown.
             *
             * @return     The load vertex bound type.
             */
            inline Vertices::BoundType const & LoadBoundType () const
            { 
                return loadBoundType_;
            }

            /**
             * @brief      Setter for the load bound type.
             * @pre        The default value is @p unknown.
             *
             * @return     The load vertex bound type.
             */
            inline Vertices::BoundType & LoadBoundType ()      
            { 
                return loadBoundType_;
            }

            /**
             * @brief      Makes the power grid bounded.
             * @details    A network is bounded if the demands/loads and the
             *     generators are bounded by their minimum and maximum
             *     possible generation. (see <a
             *     href="https://doi.org/10.1145/3208903.3208910">https://doi.org/10.1145/3208903.3208910</a>
             *     Page 343 Equations 11 and 12 for the definition)
             *     
             *     @f[
             *      -\maxdemand\leq\netflow(\vertexa)\leq-\mindemand\qquad\forall\vertexa\in\consumers 
             *     @f]
             *     @f[
             *       \maxexcess\leq\netflow(\vertexa)\leq \minexcess\qquad\forall\vertexa\in\generators
             *     @f]
             *     
             * @pre        All loads are set to @p bounded and all generators
             *     to @p bounded.
             *     
             * @I{ In short and easy to read formulation                            }
             * @I{  -dmax(u) <= fnet(u) <= -dmin(u)    for all u in Vc (Loads)      }
             * @I{   xmin(u) <= fnet(u) <=  xmax(u)    for all u in Vg (Generators) }
             *      
             * @note       Note that since the data does not provide a proper
             *      load lower bound we use @p maxbound and thus, set the lower
             *      bound to zero.
             */
            inline void MakeBounded () 
            {
                generatorBoundType_ = Vertices::BoundType::bounded;
                loadBoundType_      = Vertices::BoundType::bounded;
            }

            /**
             * @brief      Makes the power grid unbounded.
             * @details    A network is unbounded if the demands/loads and the
             *     generators are unbounded. This means that the minimum and
             *     maximum are 0 and infinity, respectively. (see <a
             *     href="https://doi.org/10.1145/3208903.3208910">https://doi.org/10.1145/3208903.3208910</a>
             *     Page 342 Equations 2 and 3 for the definition)
             *     
             *     @f[
             *      -\infty\leq\netflow(\vertexa)\leq 0\qquad\forall\vertexa\in\consumers 
             *     @f]
             *     @f[
             *      0\leq\netflow(\vertexa)\leq\infty\qquad\forall\vertexa\in\generators
             *     @f]
             * 
             * @pre        All loads are set to @p unbounded and all
             *     generators to @p unbounded.
             *     
             * @I{ In short and easy to read formulation                            }
             * @I{  -infty   <= fnet(u) <= 0         for all u in Vc (Loads)        }
             * @I{   0       <= fnet(u) <= infty     for all u in Vg (Generators)   }
             */
            inline void MakeUnbounded () 
            {
                generatorBoundType_ = Vertices::BoundType::unbounded;
                loadBoundType_      = Vertices::BoundType::unbounded;
            }

            /**
             * @brief      Makes the power grid pure unbounded.
             * @details    A network is pure unbounded if the demands/loads
             *     and the generators are unbounded. This means that the
             *     minimum and maximum are 0 and infinity, respectively (see
             *     <a href="https://doi.org/10.1145/3208903.3208910">
             *     https://doi.org/10.1145/3208903.3208910</a> Page 342
             *     Equations 2 and 3 for the definition).
             *     
             *     @f[
             *      -\infty\leq\netflow(\vertexa)\leq 0\qquad\forall\vertexa\in\consumers 
             *     @f]
             *     @f[
             *      0\leq\netflow(\vertexa)\leq\infty\qquad\forall\vertexa\in\generators
             *     @f]
             *     
             * @I{ In short and easy to read formulation                                }
             * @I{  -infty   <= fnet(u) <= 0         for all u in Vc (Loads)            }
             * @I{   0       <= fnet(u) <= infty     for all u in Vg (Generators)       }
             *      
             * @note       Note that unbounded generators get bounded demands
             *      as defined in <a
             *      href="https://doi.org/10.1145/3208903.3208910">
             *      https://doi.org/10.1145/3208903.3208910</a> Page 348
             *      Section 7. Note that pure unbounded focuses on the demands
             *      only.
             *      
             * @pre        All loads are set to @p pureunbounded and
             *     all generators to @p unbounded.
             *     
             * @see        Vertices#BoundType 
             */
            inline void MakePureUnbounded () 
            {
                generatorBoundType_ = Vertices::BoundType::unbounded;
                loadBoundType_      = Vertices::BoundType::pureunbounded;
            }

            /**
             * @brief      Makes the power grid exact bounded.
             * @details    This is especially useful when running the ordinary
             *     power flow (PF) program as PF just checks if the generator
             *     and load values produce feasible power flow.
             *     
             *     A network has exact bounds if the following holds
             *     @f[
             *      -\demand(\vertexa)\leq\netflow(\vertexa)\leq -\demand(\vertexa)\qquad\forall\vertexa\in\consumers,
             *     @f]
             *     @f[ 
             *       \excess(\vertexa)\leq\netflow(\vertexa)\leq\excess(\vertexa)\qquad\forall\vertexa\in\generators,
             *     @f] where the netflow is defined by 
             *     @f$\netflow:=\sum_{ \{ \vertexa,\vertexb \} \in \undirectededges } \flow ( \vertexa,\vertexb ) @f$,
             *     and the set of generators and and consumers is denoted by
             *     @f$\generators@f$ and @f$\consumers@f$, respectively.
             * 
             * @pre        All loads are set to @p exact and all generators to
             *     @p exact.
             * 
             * @I{ In short and easy to read formulation                            }
             * @I{   -d(u)   <= fnet(u) <= -d(u)     for all u in Vc (Loads)        }
             * @I{    x(u)   <= fnet(u) <=  x(u)     for all u in Vg (Generators)   }
             */
            inline void MakeExact () 
            {
                generatorBoundType_ = Vertices::BoundType::exact;
                loadBoundType_      = Vertices::BoundType::exact;
            }

            /**
             * @brief      Determines if bounded.
             *
             * @return     @p true if bounded, @p false otherwise.
             */
            inline bool IsBounded () const 
            {
                return ( (generatorBoundType_ == Vertices::BoundType::bounded) &&
                         (loadBoundType_      == Vertices::BoundType::bounded) );
            }
            
            /**
             * @brief      Determines if unbounded.
             *
             * @return     @p true if unbounded, @p false otherwise.
             */
            inline bool IsUnbounded () const
            {
                return ( (generatorBoundType_ == Vertices::BoundType::unbounded) &&
                         (loadBoundType_      == Vertices::BoundType::unbounded) );
            }

            /**
             * @brief      Determines if pure unbounded.
             *
             * @return     @p true if pure unbounded, @p false otherwise.
             */
            inline bool IsPureUnbounded () const
            {
                return  (   (   (generatorBoundType_ == Vertices::BoundType::unbounded) ||
                                (generatorBoundType_ == Vertices::BoundType::pureunbounded)
                            ) && 
                            ( loadBoundType_      == Vertices::BoundType::pureunbounded)
                        );
            }

            /**
             * @brief      Determines if exact.
             *
             * @return     @p true if exact, @p false otherwise.
             */
            inline bool IsExact () const
            {
                return ( ( generatorBoundType_ == Vertices::BoundType::exact ) 
                      && ( loadBoundType_      == Vertices::BoundType::exact ) );
            }

            /**
             * @brief      Get the current network bound type.
             *
             * @return     The network bound type.
             */
            inline Vertices::BoundType NetworkBoundType () const 
            { 
                if ( IsExact() )                return Vertices::BoundType::exact; 
                else if ( IsBounded() )         return Vertices::BoundType::bounded; 
                else if ( IsUnbounded() )       return Vertices::BoundType::unbounded;
                else if ( IsPureUnbounded() )   return Vertices::BoundType::pureunbounded;
                return Vertices::BoundType::unknown;
            }

            /**
             * @brief      Get the current network bound type.
             *
             * @return     The network bound type string.
             */
            inline Types::name NetworkType () const
            { 
                std::ostringstream temp;
                temp << NetworkBoundType();
                return temp.str();
            }
        ///@}

        /**@name Output Methods */
        ///@{
#pragma mark OUTPUT_METHODS

            /**
             * @brief      Output
             *
             * @param      os    The operating system
             * @param[in]  rhs   The right hand side
             *
             * @return     Output stream
             */
            friend std::ostream & operator<< ( std::ostream            & os
                                             , PowerGrid<TGraph> const & rhs ) 
            {
                os << std::string(20, '-');

                os << "\nBuses\n"       << std::string(7, '-')  << "\n";
                TVertexProperties::Header(os);
                rhs.Graph().template for_all_vertices<ExecutionPolicy::sequential>([&rhs, &os]( TVertex u )
                { 
                    u.Properties().Line( os, rhs.BaseMva() ); 
                });

                os << "\nGenerators\n"  << std::string(11, '-') << "\n";
                TGeneratorProperties::HeaderBusGeneratorName(os);
                rhs.template for_all_generator_tuple<ExecutionPolicy::sequential>( [&rhs, &os]( Types::vertexId vertexId, TGeneratorProperties u )
                { 
                    u.Line( os, rhs.Graph().VertexAt(vertexId).Properties().Name(), rhs.BaseMva() ); 
                });

                os << "\nBranches\n"    << std::string(9, '-')  << "\n";
                TEdgeProperties::Header(os);
                rhs.Graph().template for_all_edges<ExecutionPolicy::sequential>([&rhs, &os]( TEdge e )
                { 
                    e.Properties().Line( os, rhs.Graph().VertexAt(e.Source()).Properties().Name(), rhs.Graph().VertexAt(e.Target()).Properties().Name(), rhs.BaseMva() ); 
                });

                os << "\nMinDegree: " << rhs.Graph().MinDegree() << "\n";
                os << "MaxDegree: "   << rhs.Graph().MaxDegree() << "\n";

                return os;
            }
        ///@}

        /**@name Add and Remove Generators */
        ///@{
#pragma mark ADD_AND_REMOVE_GENERATOR_VERTICES

            /**
             * @brief      Adds a generator @f$g\in\generators@f$ at
             *     a vertex @f$\vertex\in\vertices@f$ with vertex identifier
             *     @p vertexId.
             *     
             * @I{  Using copy-and-swap idiom. }
             *
             * @param[in]       vertexId            The vertex identifier @p vertexId.
             * @param[in]       generatorProperty   The generator object
             *      @f$\vertex\in\generators@f$.
             * 
             * @return     The generator identifier.
             */
            inline Types::generatorId AddGeneratorAt ( Types::vertexId              vertexId
                                                     , TGeneratorProperties const & generatorProperty )
            {
                USAGE_ASSERT ( Graph().VertexExists( vertexId ) );

                // Add the generator property to the set V_G
                generators_.emplace_back( std::move( generatorProperty ) );
                generatorExists_.emplace_back( true );
                ++numberOfGenerators_;

                // Add a pointer from V to V_G, since we can have multiple
                // generators per vertex
                if ( vertexId >= generatorsAtVertex_.size() )
                {
                    generatorsAtVertex_.resize ( Graph().NumberOfVertices() );
                }
                ESSENTIAL_ASSERT ( generatorsAtVertex_.size() > vertexId  ); 

                //@TODO reuse empty slots
                Types::generatorId newId = generators_.size() - 1;
                generatorsAtVertex_[vertexId].emplace_back ( newId );

                return newId;
            }

            /**
             * @brief      Adds a generator @f$g\in\generators@f$ at
             *     a vertex @f$\vertex\in\vertices@f$ with vertex identifier
             *     @p vertexId.
             *     
             * @I{  Using universal references => type deduction. See the
             *      article of Scott Meyers
             *      https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers.
             *   }
             *
             * @param[in]  vertexId   The vertex identifier @p vertexId.
             * @param      generator  The generator object
             *     @f$\vertex\in\generators@f$.
             *
             * @return     The generator identifier.
             */
            inline Types::generatorId AddGeneratorAt ( Types::vertexId         vertexId
                                                     , TGeneratorProperties && generatorProperty )
            {
                USAGE_ASSERT ( Graph().VertexExists( vertexId ) );

                // Add the generator property to the set V_G
                generators_.emplace_back( std::move( generatorProperty ) );
                generatorExists_.emplace_back( true );
                ++numberOfGenerators_;

                // Add a pointer from V to V_G, since we can have multiple
                // generators per vertex
                if ( vertexId >= generatorsAtVertex_.size() )
                {
                    generatorsAtVertex_.resize ( Graph().NumberOfVertices() );
                }
                ESSENTIAL_ASSERT ( generatorsAtVertex_.size() > vertexId  ); // use update

                //@TODO reuse empty slots
                Types::generatorId newId = generators_.size() - 1;
                generatorsAtVertex_[vertexId].emplace_back( newId );

                return newId;
            }

            // Avoid implicit conversions
            inline Types::generatorId AddGeneratorAt ( int  vertexId, TGeneratorProperties generatorProperty ) = delete;
            inline Types::generatorId AddGeneratorAt ( char vertexId, TGeneratorProperties generatorProperty ) = delete;

            /**
             * @brief      Adds a generator @f$\vertex\in\generators@f$ at
             *     a vertex @p vertex @f$\vertex\in\vertices@f$.
             *
             * @I{  Using copy-and-swap idiom. }
             *
             * @param      vertex             The vertex object @f$\vertex\in\vertices@f$.
             * @param[in]  generatorProperty  The generator property.
             *
             * @return     The generator identifier.
             */
            inline Types::generatorId AddGeneratorAt ( TVertex              const & vertex
                                                     , TGeneratorProperties const & generatorProperty ) 
            {
                Types::vertexId vertexId = vertex.Identifier();

                USAGE_ASSERT ( Graph().VertexExists( vertexId ) );

                return AddGeneratorAt ( vertexId, std::move( generatorProperty ) );
            }

            /**
             * @brief      Adds a generator @f$g\in\generators@f$ at
             *     a vertex @p vertex @f$\vertex\in\vertices@f$.
             *
             * @I{  Using universal references => type deduction. See the
             *      article of Scott Meyers
             *      https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers.
             *   }
             *
             * @param      vertex             The vertex object @f$\vertex\in\vertices@f$.
             * @param[in]  generatorProperty  The generator property
             *     @f$\vertex\in\generators@f$.
             *
             * @return     The generator identifier.
             */
            inline Types::generatorId AddGeneratorAt ( TVertex              const &  vertex
                                                     , TGeneratorProperties       && generatorProperty ) 
            {
                Types::vertexId vertexId = vertex.Identifier();

                USAGE_ASSERT ( Graph().VertexExists( vertexId ) );

                return AddGeneratorAt ( vertexId, std::move ( generatorProperty ) );
            }

            /**
             * @brief      Removes a generator with @p generatorId at a vertex
             *     with identifier @p vertexId.
             *
             * @param[in]  vertexId     The vertex identifier.
             * @param[in]  generatorId  The generator identifier.
             */
            inline void RemoveGeneratorAt ( Types::vertexId    vertexId
                                          , Types::generatorId generatorId ) 
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );
                USAGE_ASSERT ( HasGenerator ( generatorId ) );
             
                // Remove generator object from V_G implicitly
                generatorExists_[ generatorId ] = false;

                // Reduce the number of generators
                --numberOfGenerators_;

                // Remove generator pointer from V to V_G
                auto result = std::find ( generatorsAtVertex_[vertexId].begin()
                                        , generatorsAtVertex_[vertexId].end()
                                        , generatorId
                                        );
                if ( result != generatorsAtVertex_[vertexId].end() ) 
                {
                    std::swap ( *result
                              , generatorsAtVertex_[vertexId].back() );
                    generatorsAtVertex_[vertexId].pop_back();
                } else { 
                    USAGE_ASSERT ( false 
                                && "The generatorId does not exist in generatorsAtVertex_[vertexId]!" );
                }
            }

            // Avoid implicit conversions
            inline void RemoveGeneratorAt ( Types::vertexId vertexId, int                generatorId ) = delete;
            inline void RemoveGeneratorAt ( Types::vertexId vertexId, char               generatorId ) = delete;
            inline void RemoveGeneratorAt ( int             vertexId, Types::generatorId generatorId ) = delete;
            inline void RemoveGeneratorAt ( int             vertexId, int                generatorId ) = delete;
            inline void RemoveGeneratorAt ( int             vertexId, char               generatorId ) = delete;
            inline void RemoveGeneratorAt ( char            vertexId, Types::generatorId generatorId ) = delete;
            inline void RemoveGeneratorAt ( char            vertexId, int                generatorId ) = delete;
            inline void RemoveGeneratorAt ( char            vertexId, char               generatorId ) = delete;

            /**
             * @brief      Removes a generator @f$g\in\generators@f$
             *     at a vertex @f$\vertex\in\vertices@f$ with identifier @p
             *     vertexId.
             *
             * @param[in]   vertexId           The vertex identifier.
             * @param       generatorProperty  The generator property.
             */
            inline void RemoveGeneratorAt ( Types::vertexId        vertexId
                                          , TGeneratorProperties & generatorProperty ) 
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );

                Types::generatorId generatorId = GeneratorId( generatorProperty );

                ESSENTIAL_ASSERT ( HasGenerator ( generatorId ) );

                RemoveGeneratorAt ( vertexId, generatorId );
            }

            // Avoid implicit conversions
            inline void RemoveGeneratorAt ( int  vertexId, TGeneratorProperties & generatorProperty ) = delete;
            inline void RemoveGeneratorAt ( char vertexId, TGeneratorProperties & generatorProperty ) = delete;
        ///@}

        /**@name Generator Accessors */
        ///@{
#pragma mark GENERATOR_ACCESSORS

            /**
             * @brief      Determines if there is a generator
             *     @f$\vertex\in\generators@f$ with the given @p
             *     generatorId.
             *
             * @param[in]  generatorId  The generator identifier.
             *
             * @return     @p true if the generator identifier exists, @p
             *     false otherwise.
             */
            inline bool HasGenerator ( Types::generatorId generatorId ) const 
            {
                return ( generatorId < generators_.size() 
                    &&   generatorExists_[generatorId] );
            }

            // Avoid implicit conversions
            inline bool HasGenerator ( int  generatorId ) const = delete;
            inline bool HasGenerator ( char generatorId ) const = delete;

            /**
             * @brief      Determines if there is a generator
             *     @f$\vertex\in\generators@f$.
             *
             * @param[in]  generatorProperty  The generator property.
             *
             * @return     @p true if the generator exists, @p false
             *     otherwise.
             */
            inline bool HasGenerator ( TGeneratorProperties const & generatorProperty ) const 
            {
                return HasGenerator ( GeneratorId ( generatorProperty ) );
            }

            /**
             * @brief      Determines if it has a generator at vertex with
             *     identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex with identifier @p vertexId.
             *
             * @return     @p true if there is a generator at vertex @p
             *     vertexId, @p false otherwise.
             */
            inline bool HasGeneratorAt ( Types::vertexId vertexId ) const 
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );
                return  ( generatorsAtVertex_.size() > vertexId 
                    && !( generatorsAtVertex_[vertexId].empty() ) );
            }

            // Avoid implicit conversions
            inline bool HasGeneratorAt ( int  vertexId ) const = delete;
            inline bool HasGeneratorAt ( char vertexId ) const = delete;

            /**
             * @brief      Determines if it has a generator at vertex with
             *     identifier @p vertexId.
             *
             * @param[in]  vertex  The vertex object @f$\vertex\in\vertices@f$.
             *
             * @return     @p true if there is a generator at vertex @p
             *     vertexId, @p false otherwise.
             */
            inline bool HasGeneratorAt ( TVertex const & vertex ) const 
            {
                Types::vertexId vertexId = Graph().VertexId ( vertex );
                USAGE_ASSERT( Graph().VertexExists ( vertexId ) );
                return HasGeneratorAt ( vertexId );
            }

            /**
             * @brief      The generator identifier of a @p generator
             *     @f$g\in\generators@f$.
             *
             * @param[in]  generatorProperty  The generator property.
             *
             * @note       If the @p generator @f$\vertex\in\generators@f$
             *     does not exist the method returns @p Const::NONE equivalent
             *     to @f$\emptyset@f$. However, for duplicate generators
             *     @f$\vertex\in\generators@f$ it will output the position
             *     it finds the first duplicate generator.
             *
             * @return     If the generator exists the generator's identifier
             *     @p generatorId is returned, @p Const::NONE otherwise.
             */
            inline Types::generatorId GeneratorId ( TGeneratorProperties const & generatorProperty ) const 
            {
                Types::generatorId generatorId = FindGenerator ( generatorProperty, generators_ );
                return generatorId; 
            }

            /**
             * @brief      Identifiers of all generators at a vertex with @p
             *     vertexId.
             *
             * @param[in]  vertexId      The vertex identifier.
             * @param      generatorIds  The generator identifiers.
             */
            inline void GeneratorIds ( Types::vertexId                   vertexId
                                     , std::vector<Types::generatorId> & generatorIds ) const 
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );
                
                if ( HasGeneratorAt( vertexId ) ) 
                {
                    generatorIds = generatorsAtVertex_[ vertexId ];
                }
            }

            // Avoid implicit conversions
            inline void GeneratorIds ( Types::vertexId  vertexId, std::vector<int>                  & generatorIds ) const = delete;
            inline void GeneratorIds ( Types::vertexId  vertexId, std::vector<char>                 & generatorIds ) const = delete;
            inline void GeneratorIds ( int              vertexId, std::vector<Types::generatorId>   & generatorIds ) const = delete;
            inline void GeneratorIds ( int              vertexId, std::vector<int>                  & generatorIds ) const = delete;
            inline void GeneratorIds ( int              vertexId, std::vector<char>                 & generatorIds ) const = delete;
            inline void GeneratorIds ( char             vertexId, std::vector<Types::generatorId>   & generatorIds ) const = delete;
            inline void GeneratorIds ( char             vertexId, std::vector<int>                  & generatorIds ) const = delete;
            inline void GeneratorIds ( char             vertexId, std::vector<char>                 & generatorIds ) const = delete;

            /**
             * @brief      Generator @f$\vertex\in\generators@f$ at
             *     generator's identifier @p generatorId.
             *
             * @param[in]  generatorId  The generator identifier.
             *
             * @return     The generator properties @f$\vertex\in\generators@f$.
             */
            inline TGeneratorProperties & GeneratorAt ( Types::generatorId generatorId ) 
            {
                USAGE_ASSERT ( HasGenerator ( generatorId ) );
                return generators_[generatorId];
            }

            /**
             * @brief      Generator @f$\vertex\in\generators@f$ at
             *     generator's identifier @p generatorId.
             *
             * @param[in]  generatorId  The generator identifier.
             *
             * @return     The generator property @f$\vertex\in\generators@f$.
             */
            inline TGeneratorProperties const & GeneratorAt ( Types::generatorId generatorId ) const
            {
                USAGE_ASSERT ( HasGenerator ( generatorId ) );

                return generators_[ generatorId ];
            }

            /**
             * @brief      All generator identifiers at a vertex with @p vertexId.
             *
             * @param[in]  vertexId                 The vertex identifier.
             * @param      generator identifiers    The generator identifiers
             *     at vertex with @p vertexId.
             * 
             * @pre        Check if the vertex identifier @p vertexId exists
             *     before using this method.
             *     
             * @see        StaticGraph#VertexExists
             * @see        DynamicGraph#VertexExists
             * 
             * @code{.cpp}
             *      std::vector<Types::generatorId> generatorIds;
             *      if ( this->Graph().VertexExists ( vertexId ) )
             *      {
             *          GeneratorsAt ( vertex, generatorIds );
             *      }
             * @endcode
             *     
             * @note       If the vertex @f$\vertex\in\vertices@f$ has no
             *     generator @f$\{\vertex\}\cap\generators = \emptyset@f$ then
             *     the generatorIds vectors returns empty.
             */
            inline void GeneratorsAt ( Types::vertexId                   vertexId
                                     , std::vector<Types::generatorId> & generatorIds ) const 
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );

                for_all_generator_identifiers_at <ExecutionPolicy::sequential> ( vertexId, 
                    [this, &generatorIds](Types::generatorId generatorId)
                    {
                        generatorIds.emplace_back( generatorId );
                    }
                );
            }

            /**
             * @brief      All generator objects at a vertex with @p vertexId.
             *
             * @param[in]  vertexId    The vertex identifier.
             * @param      generators  The generators at vertex with @p vertexId.
             * 
             * @pre        Check if the vertex identifier @p vertexId exists
             *     before using this method.
             *     
             * @see        StaticGraph#VertexExists
             * @see        DynamicGraph#VertexExists
             * 
             * @code{.cpp}
             *      std::vector<TGeneratorProperties> generators;
             *      if ( this->Graph().VertexExists ( vertexId ) )
             *          GeneratorsAt ( vertex, generators );
             * @endcode
             *     
             * @note       If the vertex @f$\vertex\in\vertices@f$ has no
             *     generator @f$\{\vertex\}\cap\generators = \emptyset@f$ then
             *     the generators vectors returns empty.
             */
            inline void GeneratorsAt ( Types::vertexId                     vertexId
                                     , std::vector<TGeneratorProperties> & generators ) const 
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );

                for_all_generator_identifiers_at <ExecutionPolicy::sequential> ( vertexId, 
                    [this, &generators](Types::generatorId generatorId)
                    {
                        generators.emplace_back( generators_[generatorId] );
                    }
                );
            }

            // Avoid implicit conversions
            inline void GeneratorsAt ( int  vertexId, std::vector<TGeneratorProperties> & generators ) const = delete;
            inline void GeneratorsAt ( char vertexId, std::vector<TGeneratorProperties> & generators ) const = delete;

            /**
             * @brief      All generator identifiers at a bus @p vertex.
             *
             * @param      vertex      The vertex object.
             * @param      generators  The generators at a @p vertex.
             * 
             * @pre        Check if the vertex identifier @p vertexId of the
             *     vertex exists before using this method.
             *     
             * @see        StaticGraph#VertexExists
             * @see        DynamicGraph#VertexExists
             * 
             * @code{.cpp}
             *      std::vector<Types::generatorId> generatorIds;
             *      if ( this->Graph().VertexExists ( this->Graph().VertexId ( vertexId ) ) )
             *          GeneratorsAt ( vertex, generatorIds );
             * @endcode
             *     
             * @note       If the vertex @f$\vertex\in\vertices@f$ has no
             *     generator @f$\{\vertex\}\cap\generators = \emptyset@f$ then
             *     the generatorIds vectors returns empty.
             */
            inline void GeneratorsAt ( TVertex const                   & vertex
                                     , std::vector<Types::generatorId> & generatorIds ) const 
            {
                Types::vertexId vertexId = Graph().VertexId( vertex );
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );

                GeneratorsAt ( vertexId, generatorIds );
            }

            /**
             * @brief      All generator objects at a bus @p vertex.
             *
             * @param      vertex      The vertex object.
             * @param      generators  The generators at a @p vertex.
             * 
             * @pre        Check if the vertex identifier @p vertexId of the
             *     vertex exists before using this method.
             *     
             * @see        StaticGraph#VertexExists
             * @see        DynamicGraph#VertexExists
             * 
             * @code{.cpp}
             *      std::vector<TGeneratorProperties> generators;
             *      if ( this->Graph().VertexExists ( this->Graph().VertexId ( vertexId ) ) )
             *          GeneratorsAt ( vertex, generators );
             * @endcode
             *     
             * @note       If the vertex @f$\vertex\in\vertices@f$ has no
             *     generator @f$\{\vertex\}\cap\generators = \emptyset@f$ then
             *     the generators vectors returns empty.
             */
            inline void GeneratorsAt ( TVertex const                     & vertex
                                     , std::vector<TGeneratorProperties> & generators ) const 
            {
                Types::vertexId vertexId = Graph().VertexId( vertex );
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );

                GeneratorsAt ( vertexId, generators );
            }

            /**
             * @brief      Find a generator in a vector.
             *
             * @param[in]  generatorProperty   The generator vertex.
             * @param[in]  generators          The generators.
             * 
             * @note       If the @p generator @f$\vertex\in\generators@f$
             *     does not exist the method returns @p Const::NONE equivalent
             *     to @f$\emptyset@f$. However, for duplicate generators
             *     @f$\vertex\in\generators@f$ it will output the position
             *     it finds the first duplicate generator.
             *
             * @return     The generator's identifier.
             */
            inline Types::generatorId FindGenerator ( TGeneratorProperties              const & generatorProperty
                                                    , std::vector<TGeneratorProperties> const & generators ) const 
            {
                auto result = std::find ( generators.begin()
                                        , generators.end()
                                        , generatorProperty );

                if ( result == generators.end() )
                {
                    return Const::NONE;
                }
                return static_cast<Types::generatorId> ( std::distance( generators.begin(), result ) );
            }
        ///@}

            
        /**@name Accessors for the Total Power Generation at a Vertex  */
        ///@{
#pragma mark TOTAL_POWER_GENERATION_AT_VERTEX

            /**
             * @brief      The total real power generation bound of all
             *     generators at a vertex.
             * @details    Returns the minimum and maximum of all generators
             *     at the vertex @p index. This depends also on if the power
             *     grid is set to (1) exact, (2) bounded, or (3)
             *     unbounded/pureunbounded.
             *     
             *     (1) Uses the sum of the generators real power generation
             *         (pg) snapshot, 
             *         
             *     (2) Uses the sum of the minimum
             *         (@f$\realpowergenerationmin@f$) and the sum of the
             *         maximum (@f$\realpowergenerationmax@f$) real power
             *         generation of the data,
             *         
             *     (3) Uses 0 and infinity for the minimum and maximum,
             *         respectively.
             * 
             * @param[in]  vertexId  The vertex identifier.
             *
             * @pre        The timestamp position is used for @p
             *     Vertices::BoundType::exact only.
             *
             * @return     The total real power generation bound---meaning
             *     minimum and maximum---at the vertex. If the vertex has no
             *     generator the minimum and maximum generation are set to 0.
             *     If all maximum values are Const::REAL_INFTY for @p
             *     Vertices::BoundType::bounded the return value might become
             *     @p std::numeric_limits<double>::infinity(), which is in
             *     fact a very large number.
             */
            template<Vertices::GenerationStrategyDifferentiationType Strategy>
            inline TBound TotalRealPowerGenerationBoundAt ( Types::vertexId vertexId
                                                          , Types::index    timestampPosition = 0 ) const 
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );

                if ( !HasGeneratorAt(vertexId) ) return TBound ( 0.0, 0.0 );

                if ( generatorBoundType_ == Vertices::BoundType::unbounded
                  || generatorBoundType_ == Vertices::BoundType::pureunbounded )
                { // PUREUNBOUNDED || UNBOUNDED
                    return TBound ( 0, Const::REAL_INFTY );
                }
                else if ( generatorBoundType_ == Vertices::BoundType::bounded )
                { // BOUNDED
                    TBound pg ( 0.0, 0.0 );
                    for_all_generators_at <ExecutionPolicy::sequential> ( vertexId, 
                        [ &pg ]( TGeneratorProperties const & generatorProperty )
                        {
                            if ( generatorProperty.IsActive() ) 
                            {
                                pg.Maximum() += generatorProperty.RealPowerBound().Maximum();
                                pg.Minimum() += generatorProperty.RealPowerBound().Minimum();
                            }
                        }
                    );
                    return pg;
                } else 
                { // EXACT
                    ESSENTIAL_ASSERT ( generatorBoundType_ == Vertices::BoundType::exact );
                    auto gen = TotalRealPowerGenerationAt<Strategy> ( vertexId, timestampPosition );
                    return TBound ( gen, gen );
                }
            }

            // Avoid implicit conversions
            inline TBound TotalRealPowerGenerationBoundAt ( int  vertexId )                         const = delete;
            inline TBound TotalRealPowerGenerationBoundAt ( int  vertexId, int  timestampPosition ) const = delete;
            inline TBound TotalRealPowerGenerationBoundAt ( int  vertexId, char timestampPosition ) const = delete;
            inline TBound TotalRealPowerGenerationBoundAt ( char vertexId )                         const = delete;
            inline TBound TotalRealPowerGenerationBoundAt ( char vertexId, int  timestampPosition ) const = delete;
            inline TBound TotalRealPowerGenerationBoundAt ( char vertexId, char timestampPosition ) const = delete;

            /**
             * @brief      The total real power generation
             *     @f$\realpowergeneration@f$ at a vertex
             *     @f$\vertex\in\vertices@f$ with @p vertexId.
             *
             * @param[in]  vertexId  The vertex @f$\vertex@f$ with @p vertexId.
             *
             * @note       The total real power generation
             *     @f$\realpowergeneration@f$ only includes the snapshots of
             *     @p active generators. In addition, if the vertex
             *     @f$\vertex\in\vertices@f$ has no generators the return value is 0.
             *
             * @return     The total real power generation
             *     @f$\realpowergeneration@f$ of all generator snapshots at a
             *     vertex @f$\vertex@f$ with @p vertexId.
             */
            template<Vertices::GenerationStrategyDifferentiationType Strategy>
            inline Types::real TotalRealPowerGenerationAt ( Types::vertexId vertexId 
                                                          , Types::index    timestampPosition = 0 ) const 
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );

                return internal::GenerationStrategyDifferentiation < TNetwork const, Strategy >
                               ::TotalRealPowerGenerationAt ( *this
                                                            , vertexId
                                                            , timestampPosition );
            }

            // Avoid implicit conversions
            inline Types::real TotalRealPowerGenerationAt ( int  vertexId ) const = delete;
            inline Types::real TotalRealPowerGenerationAt ( char vertexId ) const = delete;

            /**
             * @brief      The total reactive power generation bound.
             * @details    Returns the minimum and maximum of all generators
             *     @f$[\reactivepowergenerationmin,
             *     \reactivepowergenerationmax]@f$ at the vertex @p vertexId.
             *     This depends also on if the power grid is set to (1) exact,
             *     (2) bounded, or (3) unbounded/pureunbounded.
             *     
             *     (1) Uses the sum of the generators reactive power
             *         generation (@f$\reactivepowergeneration@f$) snapshot,
             *         
             *     (2) Uses the sum of the minimum
             *         (@f$\reactivepowergenerationmin@f$) and the sum of the
             *         maximum (@f$\reactivepowergenerationmax@f$) reactive
             *         power generation of the data,
             *         
             *     (3) Uses 0 and infinity for the minimum and maximum,
             *         respectively.
             *
             * @param[in]  vertexId  The vertex @f$\vertex\in\vertices@f$ with
             *     identifier @p vertexId.
             *
             * @return     The total reactive power generation bound---meaning
             *     minimum and maximum---at vertex identifier @p vertexId.
             */
            template<Vertices::GenerationStrategyDifferentiationType Strategy>
            inline TBound TotalReactivePowerGenerationBoundAt ( Types::vertexId vertexId
                                                              , Types::index    timestampPosition = 0 ) const 
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );

                TBound qg( 0.0, 0.0 );
                if (  HasGeneratorAt( vertexId ) 
                   && ( ( generatorBoundType_ == Vertices::BoundType::unbounded )
                     || ( generatorBoundType_ == Vertices::BoundType::pureunbounded ) )
                   ) 
                { // PUREUNBOUNDED || UNBOUNDED
                    return TBound( 0, Const::REAL_INFTY );
                } else if ( HasGeneratorAt( vertexId ) 
                       && ( generatorBoundType_ == Vertices::BoundType::bounded ) )
                { // BOUNDED
                    for_all_generators_at <ExecutionPolicy::sequential> ( vertexId, 
                        [ &qg ]( TGeneratorProperties const & generator )
                        {
                            if ( generator.IsActive() ) 
                            {
                                qg.Maximum() += generator.ReactivePowerBound().Maximum();
                                qg.Minimum() += generator.ReactivePowerBound().Minimum();
                            }
                        }
                    );
                } else if ( HasGeneratorAt( vertexId ) 
                       && ( generatorBoundType_ == Vertices::BoundType::exact ) )
                { // EXACT
                    qg.Maximum() = TotalReactivePowerGenerationAt<Strategy> ( vertexId
                                                                            , timestampPosition );
                    qg.Minimum() = qg.Maximum();
                }
                return qg;
            }

            // Avoid implicit conversions
            inline TBound TotalReactivePowerGenerationBoundAt ( int  vertexId ) const = delete;
            inline TBound TotalReactivePowerGenerationBoundAt ( char vertexId ) const = delete;

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
             *     @f$\reactivepowergeneration@f$ of all generatorsnapshots at a
             *     vertex @f$\vertex\in\vertices@f$ with identifier @p vertexId.
             *     
             * @todo Use the same logic as in Real Power using snapshot -> GeneratorRealPowerSnapshotAt( generator, timestampPosition );
             */
            template<Vertices::GenerationStrategyDifferentiationType Strategy>
            inline Types::real TotalReactivePowerGenerationAt ( Types::vertexId vertexId
                                                              , Types::index    timestampPosition = 0 ) const 
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );

                return internal::GenerationStrategyDifferentiation < TNetwork const, Strategy >
                               ::TotalReactivePowerGenerationAt ( *this
                                                                , vertexId
                                                                , timestampPosition );
            }

            // Avoid implicit conversions
            inline Types::real TotalReactivePowerGenerationAt ( int  vertexId ) const = delete;
            inline Types::real TotalReactivePowerGenerationAt ( char vertexId ) const = delete;
        ///@}

        ///@name Add and Remove Loads
        ///@{
#pragma mark ADD_AND_REMOVE_LOADS

            /**
             * @brief      Adds a @p load at a vertex with identifier @p vertexId.
             * @details    There are more than one load allowed at each vertex.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param      load      The load object.
             *
             * @return     The identifier of the load.
             */
            inline Types::loadId AddLoadAt ( Types::vertexId vertexId
                                           , TLoadProperties load ) 
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );

                // Add load to the set of loads V_L
                loads_.push_back ( std::move ( load ) );
                loadExists_.emplace_back ( true );
                ++numberOfLoads_;

                // Add pointer from V to V_L for that particular load
                if ( loadsAtVertex_.size() <= vertexId )
                {
                    loadsAtVertex_.resize( Graph().NumberOfVertices() );
                }
                ESSENTIAL_ASSERT ( loadsAtVertex_.size() > vertexId );

                loadsAtVertex_[vertexId].emplace_back( loads_.size() - 1 );
                return ( loads_.size() - 1 );
            }

            // Avoid implicit conversions
            inline Types::loadId AddLoadAt ( int  vertexId, TLoadProperties load ) = delete;
            inline Types::loadId AddLoadAt ( char vertexId, TLoadProperties load ) = delete;

            /**
             * @brief      Adds a @p load at a vertex with identifier @p vertexId.
             * @details    There are more than one load allowed at each vertex.
             *
             * @param      vertex  The vertex object @f$\vertex\in\vertices@f$.
             * @param[in]  load    The load object.
             *
             * @return     The load identifier.
             */
            inline Types::loadId AddLoadAt ( TVertex         const & vertex
                                           , TLoadProperties const & load ) 
            {
                Types::vertexId vertexId = Graph().VertexId( vertex );

                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );

                return AddLoadAt ( vertexId, load );
            }

            /**
             * @brief      Adds a @p load at a vertex with identifier @p vertexId.
             * @details    There are more than one load allowed at each vertex.
             *
             * @param      vertex  The vertex object @f$\vertex\in\vertices@f$.
             * @param      load    The load object.
             *
             * @return     The load identifier.
             */
            inline Types::loadId AddLoadAt ( TVertex         const &  vertex
                                           , TLoadProperties       && load ) 
            {
                Types::vertexId vertexId = Graph().VertexId ( vertex );

                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );

                return AddLoadAt ( vertexId, std::move ( load ) );
            }

            /**
             * @brief      Removes a load at a vertex
             *     @f$\vertex\in\vertices@f$ with identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param      loadId    The load identifier.
             */
            inline void RemoveLoadAt ( Types::vertexId vertexId
                                     , Types::loadId   loadId )
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );
                USAGE_ASSERT ( HasLoad ( loadId ) );

                // Remove load properties from V_L implicitly
                loadExists_[ loadId ] = false;

                // Reduce the number of loads
                --numberOfLoads_;

                // Remove load pointer from V to V_L
                auto result = std::find ( loadsAtVertex_[vertexId].begin()
                                        , loadsAtVertex_[vertexId].end()
                                        , loadId
                                        );
                if ( result != loadsAtVertex_[vertexId].end() ) 
                {
                    std::swap ( *result
                              , loadsAtVertex_[vertexId].back() );
                    loadsAtVertex_[vertexId].pop_back();
                } else { 
                    USAGE_ASSERT ( false 
                                && "The loadId does not exist in loadsAtVertex_[vertexId]!" );
                }
            }

            // Avoid implicit conversions
            inline void RemoveLoadAt ( Types::vertexId vertexId, int           loadId ) = delete;
            inline void RemoveLoadAt ( Types::vertexId vertexId, char          loadId ) = delete;
            inline void RemoveLoadAt ( int             vertexId, Types::loadId loadId ) = delete;
            inline void RemoveLoadAt ( int             vertexId, int           loadId ) = delete;
            inline void RemoveLoadAt ( int             vertexId, char          loadId ) = delete;
            inline void RemoveLoadAt ( char            vertexId, Types::loadId loadId ) = delete;
            inline void RemoveLoadAt ( char            vertexId, int           loadId ) = delete;
            inline void RemoveLoadAt ( char            vertexId, char          loadId ) = delete;

            /**
             * @brief      Removes a load at a vertex
             *     @f$\vertex\in\vertices@f$ with identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param      load      The load object.
             */
            inline void RemoveLoadAt ( Types::vertexId   vertexId
                                     , TLoadProperties & load )
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );

                Types::loadId loadId = LoadId( load );

                ESSENTIAL_ASSERT ( HasLoad ( loadId ) );

                RemoveLoadAt ( vertexId, loadId );
            }

            // Avoid implicit conversions
            inline void RemoveLoadAt ( int  vertexId, TLoadProperties & load ) = delete;
            inline void RemoveLoadAt ( char vertexId, TLoadProperties & load ) = delete;
        ///@}

        ///@name Load Accessors
        ///@{
#pragma mark LOAD_ACCESSORS

            /**
             * @brief      Determines if the load identifier @p loadId exists.
             *
             * @param[in]  loadId  The load identifier.
             *
             * @return     @p true if the load identifier exists, @p false
             *     otherwise.
             */
            inline bool HasLoad ( Types::loadId loadId ) const 
            {
                return ( loadId < loads_.size() )
                      && loadExists_[ loadId ] ;
            }

            // Avoid implicit conversions
            inline bool HasLoad ( int  loadId ) const = delete;
            inline bool HasLoad ( char loadId ) const = delete;

            /**
             * @brief      Determines if the load exists.
             *
             * @param      load  The load object.
             *
             * @return     @p true if the load exists, @p false otherwise.
             */
            inline bool HasLoad ( TLoadProperties const & load ) const 
            {
                return ( Const::NONE != LoadId ( load ) );
            }

            /**
             * @brief      Determines if there is a load at vertex with @p
             *     vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             *
             * @return     @p true if the load identifier exists, @p false
             *     otherwise.
             */
            inline bool HasLoadAt ( Types::vertexId vertexId ) const 
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );
                return  ( loadsAtVertex_.size() > vertexId 
                    && !( loadsAtVertex_[vertexId].empty() ) );
            }

            // Avoid implicit conversions
            inline bool HasLoadAt ( int  vertexId ) const = delete;
            inline bool HasLoadAt ( char vertexId ) const = delete;

            /**
             * @brief      Determines if it has loads at the vertex
             *     @f$\vertex\in\vertices@f$.
             *
             * @param      vertex  The vertex @f$\vertex\in\vertices@f$.
             *
             * @return     @p true if there are loads at the vertex, @p false
             *     otherwise.
             */
            inline bool HasLoadAt ( TVertex const & vertex ) const 
            {
                Types::vertexId vertexId = Graph().VertexId ( vertex );
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );
                return HasLoadAt ( vertexId );
            }

            /**
             * @brief      The load identifier of a load object.
             *
             * @param[in]  load  The load object.
             *
             * @return     If the load object exists it returns the unique
             *     identifier of a load object, otherwise it returns @p Const::NONE.
             */
            inline Types::loadId LoadId ( TLoadProperties const & load ) const 
            {
                auto result = std::find ( loads_.begin()
                                        , loads_.end()
                                        , load );
                if ( result == loads_.end() )
                {
                    return Const::NONE;
                }
                return std::distance ( loads_.begin(), result );
            }

            /**
             * @brief      Loads identifiers.
             *
             * @param[in]  vertexId  The vertex identifier.
             *
             * @return     A set of load identifiers.
             */
            inline void LoadIds ( Types::vertexId              vertexId
                                , std::vector<Types::loadId> & loadIds ) const 
            {
                USAGE_ASSERT ( Graph().VertexExists( vertexId ) );
                USAGE_ASSERT ( vertexId < loadsAtVertex_.size() );

                if ( HasLoadAt ( vertexId ) )
                {
                    loadIds = loadsAtVertex_[vertexId];
                }
            }

            // Avoid implicit conversions
            inline void LoadIds ( Types::vertexId  vertexId, std::vector<int>             & loadIds ) const = delete;
            inline void LoadIds ( Types::vertexId  vertexId, std::vector<char>            & loadIds ) const = delete;
            inline void LoadIds ( int              vertexId, std::vector<Types::loadId>   & loadIds ) const = delete;
            inline void LoadIds ( int              vertexId, std::vector<int>             & loadIds ) const = delete;
            inline void LoadIds ( int              vertexId, std::vector<char>            & loadIds ) const = delete;
            inline void LoadIds ( char             vertexId, std::vector<Types::loadId>   & loadIds ) const = delete;
            inline void LoadIds ( char             vertexId, std::vector<int>             & loadIds ) const = delete;
            inline void LoadIds ( char             vertexId, std::vector<char>            & loadIds ) const = delete;

            /**
             * @brief      Loads identifiers at a vertex.
             *
             * @param[in]       vertex   The vertex object.
             * @param[in/out]   loadIds  The load identifiers.
             */
            inline void LoadIds ( TVertex              const & vertex
                                , std::vector<Types::loadId> & loadIds ) const 
            {
                Types::vertexId vertexId = Graph().VertexId ( vertex );
                
                USAGE_ASSERT( vertexId < Graph().Vertices().size() );
                USAGE_ASSERT( vertexId < loadsAtVertex_.size()     );

                if ( HasLoadAt( vertexId ) )
                {
                    loadIds = loadsAtVertex_[vertexId];
                }
            }

            // Avoid implicit conversions
            inline void LoadIds ( TVertex const & vertex, std::vector<int>  & loadIds ) const = delete;
            inline void LoadIds ( TVertex const & vertex, std::vector<char> & loadIds ) const = delete;

            /**
             * @brief      Load at load's identifier @p loadId.
             *
             * @param[in]  loadId  The load identifier.
             *
             * @return     The load properties.
             */
            inline TLoadProperties & LoadAt ( Types::loadId loadId ) 
            {
                USAGE_ASSERT ( HasLoad ( loadId ) );
                return loads_[loadId];
            }

            /**
             * @brief      Load at load's identifier @p loadId.
             *
             * @param[in]  loadId  The load identifier.
             *
             * @return     The load properties.
             */
            inline TLoadProperties const & LoadAt ( Types::loadId loadId ) const
            {
                USAGE_ASSERT ( HasLoad ( loadId ) );
                return loads_[loadId];
            }

            /**
             * @brief      The loads at a vertex with identifier @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param      loads     The loads.
             */
            inline void LoadsAt ( Types::vertexId                vertexId
                                , std::vector<TLoadProperties> & loads    ) const
            {
                USAGE_ASSERT( Graph().VertexExists( vertexId ) );

                if ( HasLoadAt( vertexId ) ) 
                {
                    std::vector<Types::labelId> loadIds; 
                    LoadIds( vertexId, loadIds );
                    for ( auto id : loadIds ) 
                    {
                        loads.emplace_back( loads_[id] );
                    }
                }
            }

            /**
             * @brief      The loads at a vertex object.
             *
             * @param      vertex  The vertex object.
             * @param      loads   The loads.
             */
            inline void LoadsAt ( TVertex                const & vertex
                                , std::vector<TLoadProperties> & loads  ) const
            {
                Types::vertexId vertexId = Graph().VertexId ( vertex );
                USAGE_ASSERT ( Graph().VertexExists( vertexId ) );

                if ( HasLoadAt( vertexId ) ) 
                {
                    std::vector<Types::loadId> loadIds;
                    LoadIds ( vertexId, loadIds );
                    for ( auto id : loadIds ) 
                    {
                        loads.emplace_back( loads_[id] );
                    }
                }
            }
        ///@}

        ///@name Accessors for the Total Power Load at a Vertex
        ///@{
#pragma mark TOTAL_POWER_LOAD_AT_VERTEX

            /**
             * @brief      Total real power load for a certain snapshot
             *     (timestamp) at a vertex.
             *
             * @param[in]  vertexId    The vertex identifier.
             * @param[in]  snapshotId  The snapshot position.
             *
             * @return     The total real power load at a vertex for a timestamp.
             */
            inline Types::real RealPowerLoadAt ( Types::vertexId vertexId
                                               , Types::index    snapshotId = 0 ) const
            {
                USAGE_ASSERT( Graph().VertexExists( vertexId ) );

                Types::loadSnapshot result = 0;
                for_all_real_power_load_snapshots_at ( 
                    vertexId, 
                    snapshotId,
                    [&result](Types::loadSnapshot load )
                    {
                        result += load;
                    }
                );

                return result;
            }

            /**
             * @brief      Total real power load for a certain snapshot
             *     (timestamp) at a vertex.
             *
             * @param[in]  vertexId    The vertex identifier.
             * @param[in]  snapshotId  The snapshot position.
             *
             * @return     The total real power load at a vertex for a timestamp.
             */
            inline Types::real RealPowerLoadAt ( TVertex const & vertex
                                               , Types::index    snapshotId = 0 ) const
            {
                USAGE_ASSERT ( Graph().VertexExists( vertex.Identifier() ) );
                return RealPowerLoadAt( vertex.Identifier(), snapshotId );
            }

            /**
             * @brief      Total real power load bound at vertex @p vertexId.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param[in]  timestamp The time stamp.
             *
             * @note       The time stamp is only used when the type is set to
             *             exact.
             *
             * @return     The real power load bound at a vertex @p vertexId.
             */
            inline TBound TotalRealPowerLoadBoundAt( Types::vertexId vertexId
                                                   , Types::index    timestamp = 0 ) const
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );

                if ( loadBoundType_ == Vertices::BoundType::pureunbounded )
                { // PUREUNBOUNDED
                    if ( HasGeneratorAt ( vertexId ) ) 
                    { //@todo use when implemented the breakable loop to break after infty was found
                        Types::real loadMax = 0.0;
                        for_all_loads_at<ExecutionPolicy::sequential> ( vertexId, 
                            [ &loadMax ]( TLoadProperties const & load ) 
                            {
                                if ( load.RealPowerLoadBound().Maximum() < Const::REAL_INFTY 
                                  && loadMax < Const::REAL_INFTY )
                                {
                                    loadMax += load.RealPowerLoadBound().Maximum();
                                } else {
                                    loadMax = Const::REAL_INFTY;
                                }
                            }
                        );
                        return TBound ( 0, loadMax );
                    }
                    return TBound ( 0, Const::REAL_INFTY );
                } else if ( loadBoundType_ == Vertices::BoundType::unbounded )
                { // UNBOUNDED
                    return TBound ( 0, Const::REAL_INFTY );
                } else if ( loadBoundType_ == Vertices::BoundType::exact )
                { // EXACT: For power flow (PF) calculation
                    auto loadValue = TotalRealPowerLoadAt(vertexId, timestamp);
                    return TBound ( loadValue, loadValue );
                }
                // BOUNDED
                //@todo use when implemented the breakable loop to break after infty was found
                Types::real loadMin = 0.0;
                Types::real loadMax = 0.0;
                for_all_loads_at<ExecutionPolicy::sequential> ( vertexId, 
                    [ &loadMin, &loadMax ]( TLoadProperties const & load ) 
                    {
                        if ( load.RealPowerLoadBound().Minimum() < Const::REAL_INFTY 
                          && loadMin < Const::REAL_INFTY )
                        {
                            loadMin += load.RealPowerLoadBound().Minimum();
                        } else {
                            loadMin = Const::REAL_INFTY;
                        }
                        
                        if ( load.RealPowerLoadBound().Maximum() < Const::REAL_INFTY 
                          && loadMax < Const::REAL_INFTY )
                        {
                            loadMax += load.RealPowerLoadBound().Maximum();
                        } else {
                            loadMax = Const::REAL_INFTY;
                        }
                    }
                );
                return TBound ( loadMin, loadMax );
            }

            /**
             * @brief      The total real power load at a vertex with id
             *             @p vertexId.
             *
             * @param[in]  vertexId           The vertex identifier.
             * @param[in]  timestampPosition  The timestamp position.
             *
             * @return     The total real power load at the vertex with id
             *             @p vertexId.
             */
            inline Types::real TotalRealPowerLoadAt( Types::vertexId vertexId,
                                                     Types::index    timestampPosition ) const
            {
                USAGE_ASSERT ( Graph().VertexExists( vertexId ) );

                if ( !HasLoadAt ( vertexId ) ) return 0.0;

                Types::real total = 0;
                for_all_load_identifiers_at<ExecutionPolicy::breakable>( vertexId,
                    [ this, &total, timestampPosition ]( Types::loadId loadId )
                    {
                        auto myLoad = LoadSnapshotOf(loadId, timestampPosition);
                        if ( myLoad >= Const::REAL_INFTY ) 
                        {
                            total = Const::REAL_INFTY;
                            return false;
                        }
                        total += myLoad;
                        return true;
                    }
                );
                return total;
            }

            /**
             * @brief      Total reactive power load bound at a vertex.
             *
             * @param[in]  vertexId  The vertex identifier.
             *
             * @return     The reactive power load bound at a vertex @p vertexId.
             */
            inline TBound TotalReactivePowerLoadBoundAt( Types::vertexId vertexId ) const 
            {
                USAGE_ASSERT ( Graph().VertexExists ( vertexId ) );

                if ( loadBoundType_ == Vertices::BoundType::pureunbounded )
                { // PUREUNBOUNDED
                    if ( HasGeneratorAt( vertexId ) ) 
                    {
                        return TBound( 0, Graph().VertexAt( vertexId ).ReactivePowerLoadBound().Maximum() );        
                    }
                    return TBound( 0, Const::REAL_INFTY );    
                } else if ( loadBoundType_ == Vertices::BoundType::unbounded )
                { // UNBOUNDED
                    return TBound( 0, Const::REAL_INFTY ); 
                } else if ( loadBoundType_ == Vertices::BoundType::exact )
                { // EXACT: For power flow (PF) calculation
                    return TBound ( Graph().VertexAt( vertexId ).ReactivePowerLoad()
                                  , Graph().VertexAt( vertexId ).ReactivePowerLoad() );    
                }
                return TBound ( Graph().VertexAt( vertexId ).ReactivePowerLoadBound().Minimum()
                              , Graph().VertexAt( vertexId ).ReactivePowerLoadBound().Maximum() );
            }
        ///@}

        ///@name Snapshot Accessors and Modifiers
        ///@{
#pragma mark SNAPSHOT_ACCESSORS_AND_MODIFIERS

            /**
             * @brief      Adds a generator snapshot at generator with identifier
             *     @p generatorId.
             * @details    These values represent the maximum possible production
             *     of a generator at a certain timestamp.
             *     
             * @param[in]  generatorId                      The identifier of
             *                                              the generator.
             * @param[in]  maximumRealPowerGenerationPu     The generator
             *                                              snapshot
             *                                              representing the
             *                                              maximum real power
             *                                              generation in p.u.
             *                                              
             * @pre        The generator @f$\vertex\in\generators@f$ with
             *     the @p generatorId has to exist and the maximum real power
             *     generation p.u. has not to be @p Const::NONE.
             */
            inline void AddGeneratorRealPowerSnapshotAt ( Types::generatorId       generatorId
                                                        , Types::generatorSnapshot maximumRealPowerGenerationPu ) 
            {
                USAGE_ASSERT ( HasGenerator ( generatorId ) );
                // USAGE_ASSERT ( maximumRealPowerGenerationPu != Const::NONE );

                if ( generatorRealPowerSnapshots_.size() <= generatorId )
                {
                    UpdateGeneratorSnapshotSize();
                }
                ESSENTIAL_ASSERT( generatorId < generatorRealPowerSnapshots_.size() );
                generatorRealPowerSnapshots_[ generatorId ].emplace_back( maximumRealPowerGenerationPu );
            }

            /**
             * @brief      Update generator snapshot size.
             * @details    There can be more generators than buses.
             */
            inline void UpdateGeneratorSnapshotSize () 
            {
                generatorRealPowerSnapshots_.resize( generators_.size() );
            }

            /**
             * @brief      Update load snapshot
             * @details    Currently we assume that there is one load per bus
             */
            inline void UpdateLoadSnapshotSize( ) 
            {
                loadSnapshots_.resize( loads_.size() );
            }

            /**
             * @brief      Output generation snapshots.
             */
            void OutputGeneratorSnaps() 
            {
                for ( Types::count counter = 0
                    ; counter <  timestamps_.size()
                    ; ++counter )
                {
                    std::cout << std::setw(5) << timestamps_[counter];
                    for ( Types::vertexId generatorId = 0
                        ; generatorId < generatorRealPowerSnapshots_.size()
                        ; ++generatorId )
                    {
                        if ( generatorRealPowerSnapshots_[generatorId].size() == 0 
                          || GeneratorRealPowerSnapshotAt ( generatorId, counter ) == Const::NONE ) 
                        {
                            continue; // If the generator has no snapshot available
                        }
                        std::cout << " - " << std::setw(5) << GeneratorRealPowerSnapshotAt ( generatorId, counter );
                    }
                    std::cout << std::endl;
                }
            }

            /**
             * @brief      Output load snapshots.
             */
            void OutputLoadSnaps() 
            {
                for ( Types::count counter = 0
                    ; counter < timestamps_.size()
                    ; ++counter )
                {
                    std::cout << std::setw(5) << timestamps_[counter];
                    for ( Types::vertexId loadId = 0
                        ; loadId < loadSnapshots_.size()
                        ; ++loadId )
                    {
                        if ( loadSnapshots_[loadId].size() == 0 || LoadSnapshotOf ( loadId, counter ) == Const::NONE ) continue; // If the generator has no snapshot available
                        std::cout << " - " << std::setw(5) << LoadSnapshotOf ( loadId, counter );
                    }
                    std::cout << std::endl;
                }
            }

            /**
             * @brief      Adds a real power load snapshot.
             * @details    There are more than one load per bus permitted.
             *
             * @param[in]  loadId     The load identifier
             * @param[in]  snapshot   The load of a @p snapshot representing the
             *      real power load at a timestamp in p.u.
             */
            inline void AddLoadSnapshotAt ( Types::loadId       loadId
                                          , Types::loadSnapshot snapshot ) 
            {
                USAGE_ASSERT ( HasLoad ( loadId ) );
                USAGE_ASSERT ( snapshot < Const::NONE   );

                if ( loadSnapshots_.size() <= loadId 
                  || loadSnapshots_.empty() ) 
                {
                    UpdateLoadSnapshotSize();                    
                }
                    
                loadSnapshots_[loadId].emplace_back( snapshot );
            }

            /**
             * @brief      Adds a snapshot weighting.
             *
             * @param[in]  weight   The @p weight of a snapshot
             */
            inline void AddSnapshotWeighting( Types::weightSnapshot weight ) 
            {
                USAGE_ASSERT( weight != Const::NONE );
                snapshotWeights_.emplace_back( weight );
            }

            /**
             * @brief      Adds a timestamp.
             * @details    The timestamp should have the format
             *     "0000-00-00 00:00:00" representing
             *     "<year>-<month>-<day> <hour>:<minute>:<second>".
             *
             * @param[in]  timestamp  The timestamp, e.g., "2019-09-19 19:19:19"
             */
            inline void AddSnapshotTimestamp( Types::timestampSnapshot timestamp ) 
            {
                USAGE_ASSERT ( !timestamp.empty() );
                timestamps_.emplace_back( timestamp );
            }

            /**
             * @brief      Position of a @p timestamp.
             *
             * @param[in]  timestamp  The timestamp.
             *
             * @return     The position of a @p timestamp.
             * 
             * @note       Implementation is very inefficient.
             */
            inline Types::index PositionOf ( Types::timestampSnapshot timestamp ) const
            {
                auto result = std::find ( timestamps_.begin()
                                        , timestamps_.end()
                                        , timestamp );
                if ( result != timestamps_.end() )
                {
                    return std::distance( timestamps_.begin(), result );
                } else {
                    return Const::NONE;
                }
            }

            /**
             * @brief      Timestamp at @p position.
             *
             * @param[in]  timestamp  The timestamp.
             *
             * @return     The timestamp at the @p position.
             */
            inline Types::timestampSnapshot TimestampAt ( Types::index timestampPosition ) const 
            {
                USAGE_ASSERT ( timestampPosition < timestamps_.size() );
                return timestamps_[timestampPosition];
            }
        ///@}

        ///@name Generator Real Power Snapshot
        ///@{
#pragma mark GENERATOR_REAL_POWER_SNAPSHOT
            /**
             * @brief      Generator real power snapshot at a given timestamp.
             *
             * @details    If the generator has no generation value assigned for
             *             the given timestamp, the method returns
             *             @p Const::NONE.
             *
             * @post       If the timestamp is invalid the method returns @p
             *             Const::NONE.
             *
             * @param      generatorId  The generator identifier.
             * @param[in]  timestamp    The timestamp.
             *
             * @return     The real power generation at a @p timestamp
             *             (maximum real power generation in p.u.).
             */
            inline Types::generatorSnapshot GeneratorRealPowerSnapshotAt ( Types::generatorId        generatorId
                                                                         , Types::timestampSnapshot  timestamp   ) const
            {
                USAGE_ASSERT ( generatorId < NumberOfGenerators() );
                USAGE_ASSERT ( !timestamp.empty()                 );

                Types::index position = PositionOf ( timestamp );
                if ( position != Const::NONE )
                {
                    return GeneratorRealPowerSnapshotAt ( generatorId, position );
                } else 
                { // No snapshot available
                    return Const::NONE; 
                }
            }

            /**
             * @brief      Generator real power snapshot at a given timestamp.
             *
             * @details    If the generator has no generation value assigned for
             *             the given timestamp, the method returns
             *             @p Const::NONE.
             *
             * @param      generator  The generator object.
             * @param[in]  timestamp  The timestamp.
             *
             * @return     The real power generation at a @p timestamp
             *             (maximum real power generation in p.u.).
             */
            inline Types::generatorSnapshot GeneratorRealPowerSnapshotAt ( TGeneratorProperties const & generator
                                                                         , Types::timestampSnapshot     timestamp   ) const
            {
                Types::generatorId generatorId = GeneratorId ( generator );
                USAGE_ASSERT ( generatorId != Const::NONE );

                return GeneratorRealPowerSnapshotAt ( generatorId, timestamp );
            }

            /**
             * @brief      Generator real power snapshot at a given timestamp.
             *
             * @details    If the generator has no generation value assigned for
             *             the given timestamp, the method returns
             *             @p Const::NONE.
             * 
             * @pre        Check for a valid generatorId and timestamp position.
             * 
             * @param      generatorId        The generator identifier.
             * @param[in]  timestampPosition  The timestamp position.
             *
             * @return     The real power generation at a @p timestamp
             *             (maximum real power generation in p.u.).
             */
            inline Types::generatorSnapshot GeneratorRealPowerSnapshotAt ( Types::generatorId generatorId
                                                                         , Types::index       timestampPosition ) const
            {
                USAGE_ASSERT ( generatorId < NumberOfGenerators() );
                USAGE_ASSERT ( !timestamps_.empty()               );

                if ( generatorId >= generatorRealPowerSnapshots_.size() )
                {
                    return Const::NONE;
                }
                if ( timestampPosition >= generatorRealPowerSnapshots_[generatorId].size() )
                {
                    return Const::NONE;
                }
                return generatorRealPowerSnapshots_[generatorId][timestampPosition];
            }

            /**
             * @brief      Real power generator snapshot at a given timestamp.
             *
             * @details    If the generator has no generation value assigned for
             *             the given timestamp, the method returns
             *             @p Const::NONE.
             *
             * @param      generator          The generator object.
             * @param[in]  timestampPosition  The timestamp position.
             *
             * @return     The real power generation at a @p timestamp
             *             (maximum real power generation in p.u.).
             */
            inline Types::generatorSnapshot GeneratorRealPowerSnapshotAt ( TGeneratorProperties const & generator
                                                                         , Types::index                 timestampPosition ) const
            {
                Types::generatorId generatorId = GeneratorId ( generator );
                USAGE_ASSERT ( generatorId != Const::NONE );

                return GeneratorRealPowerSnapshotAt ( generatorId, timestampPosition );
            }

            /**
             * @brief      Generator snapshots at a timestamp.
             * @details    Some generators might not have snapshots over time.
             *             In this case this method returns a vector with @p
             *             Const::NONE at these generators.
             * 
             * @pre        The vector @p snapshotsAtTimestamp has to be empty
             *             and @p snapshotsAtTimestamp have to be empty.
             * 
             * @param[in]  timestamp             The timestamp.
             * @param      snapshotsAtTimestamp  The snapshots at the timestamp.
             * 
             * @todo Add the same for reactive power?
             */
            inline void GeneratorRealPowerSnapshotsAt ( Types::timestampSnapshot                timestamp
                                                      , std::vector<Types::generatorSnapshot> & snapshotsAtTimestamp ) const
            {
                USAGE_ASSERT ( !timestamps_.empty()         );
                USAGE_ASSERT ( snapshotsAtTimestamp.empty() );

                Types::index position = PositionOf( timestamp );
                if ( position != Const::NONE ) 
                {
                    for ( Types::vertexId generatorId = 0
                        ; generatorId < generatorRealPowerSnapshots_.size()
                        ; ++generatorId ) 
                    { // if there is a snapshot at a generator there should be at least position many
                        ESSENTIAL_ASSERT ( generatorRealPowerSnapshots_[generatorId].size() > position ); 
                        if ( generatorRealPowerSnapshots_[generatorId].size() == 0 )
                        { // No snapshots available at the generator with generatorId
                            snapshotsAtTimestamp.emplace_back( Const::NONE );
                        }
                        snapshotsAtTimestamp.emplace_back( GeneratorRealPowerSnapshotAt ( generatorId, position ) );
                    } // for
                } // if position
            }
        ///@}
        
        ///@name Generator Reactive Power Snapshot
        ///@todo Not fully supported
        ///@{
#pragma mark GENERATOR_REACTIVE_POWER_SNAPSHOT

            /**
             * @brief      Generator snapshot at a given timestamp.
             *
             * @details    If the generator has no generation value assigned for
             *             the given timestamp, the method returns
             *             @p Const::NONE.
             *
             * @param      generatorId  The generator identifier.
             * @param[in]  timestamp    The timestamp.
             *
             * @return     The generation at a @p timestamp (maximum real power
             *             generation in p.u.).
             *             
             * @todo       Reactive power is not supported in that way.
             */
            inline Types::generatorSnapshot GeneratorReactivePowerSnapshotAt ( Types::generatorId        generatorId
                                                                             , Types::timestampSnapshot  timestamp   ) const
            {
                USAGE_ASSERT ( generatorId < NumberOfGenerators() );
                USAGE_ASSERT ( !timestamps_.empty()               );

                Types::index position = PositionOf ( timestamp );
                if ( position != Const::NONE )
                {
                    return GeneratorReactivePowerSnapshotAt ( generatorId, position );
                } else 
                { // No snapshot available
                    return Const::NONE; 
                }
            }

            /**
             * @brief      Generator snapshot at a given timestamp.
             *
             * @details    If the generator has no generation value assigned for
             *             the given timestamp, the method returns
             *             @p Const::NONE.
             *
             * @param      generator  The generator object.
             * @param[in]  timestamp  The timestamp.
             *
             * @return     The generation at a @p timestamp (maximum real power
             *             generation in p.u.).
             */
            inline Types::generatorSnapshot GeneratorReactivePowerSnapshotAt ( TGeneratorProperties const & generator
                                                                             , Types::timestampSnapshot     timestamp   ) const
            {
                Types::generatorId generatorId = GeneratorId ( generator );
                USAGE_ASSERT ( generatorId != Const::NONE );

                return GeneratorReactivePowerSnapshotAt ( generatorId, timestamp );
            }

            /**
             * @brief      Generator real power snapshot at a given timestamp.
             *
             * @details    If the generator has no generation value assigned for
             *             the given timestamp, the method returns
             *             @p Const::NONE.
             *             
             * @note       Timestamp is not supported for reactive power currently!
             *
             * @param      generatorId        The generator identifier.
             * @param[in]  timestampPosition  The timestamp position.
             *
             * @return     The generation at a @p timestamp (maximum real power
             *             generation in p.u.).
             *             
             * @todo       Logic for reactive power if data allows it. This is not clean.
             */
            inline Types::generatorSnapshot GeneratorReactivePowerSnapshotAt ( Types::generatorId generatorId
                                                                             , Types::index       timestampPosition ) const
            {
                USAGE_ASSERT ( generatorId < NumberOfGenerators() );

                // if ( generatorId >= generatorReactivePowerSnapshots_.size() )
                // {
                //     return Const::NONE;
                // }
                // if ( timestampPosition >= generatorReactivePowerSnapshots_[generatorId].size() )
                // {
                //     return Const::NONE;
                // }
                return GeneratorAt ( generatorId ).ReactivePower(); // generatorReactivePowerSnapshots_[generatorId][timestampPosition];
            }

            /**
             * @brief      Generator reactive snapshot at a given timestamp.
             *
             * @details    If the generator has no generation value assigned for
             *             the given timestamp, the method returns
             *             @p Const::NONE.
             *
             * @param      generator          The generator object.
             * @param[in]  timestampPosition  The timestamp position.
             *
             * @return     The generation at a @p timestamp (maximum real power
             *             generation in p.u.).
             */
            inline Types::generatorSnapshot GeneratorReactivePowerSnapshotAt ( TGeneratorProperties const & generator
                                                                             , Types::index                 timestampPosition ) const
            {
                Types::generatorId generatorId = GeneratorId ( generator );
                USAGE_ASSERT ( generatorId != Const::NONE );

                return GeneratorReactivePowerSnapshotAt ( generatorId, timestampPosition );
            }
        ///@}

        ///@name Load Snapshot
        ///@{
#pragma mark LOAD_SNAPSHOT_LOGIC

            /**
             * @brief      Load snapshot at a @p timestamp.
             * @details    Some loads might not have snapshots over time. In
             *     this case this method returns @p Const::NONE as load value.
             *
             * @param[in]  timestamp  The timestamp.
             *
             * @return     The load at the timestamp.
             */
            inline Types::loadSnapshot LoadSnapshotOf ( Types::loadId            loadId
                                                      , Types::timestampSnapshot timestamp ) 
            {
                USAGE_ASSERT ( loadId != Const::NONE  );
                USAGE_ASSERT ( loadId < loads_.size() );
                USAGE_ASSERT ( !timestamps_.empty()   );

                Types::index position = PositionOf( timestamp );
                return LoadSnapshotOf ( loadId, position );
            }

            /**
             * @brief      Load snapshot at a @p timestamp.
             * @details    Some loads might not have snapshots over time. In
             *     this case this method returns @p Const::NONE as load value.
             *
             * @param[in]  timestamp  The timestamp.
             *
             * @return     The load at the timestamp.
             */
            inline Types::loadSnapshot LoadSnapshotOf ( Types::loadId            loadId
                                                      , Types::timestampSnapshot timestamp ) const
            {
                USAGE_ASSERT ( loadId != Const::NONE  );
                USAGE_ASSERT ( loadId < loads_.size() );
                USAGE_ASSERT ( ! timestamps_.empty()  );

                Types::index position = PositionOf( timestamp );
                return LoadSnapshotOf ( loadId, position );
            }

            /**
             * @brief      The load value of the load at @p loadId for the
             *     timestamp at @p timestampPosition.
             *
             * @param[in]  loadId             The load identifier.
             * @param[in]  timestampPosition  The timestamp position.
             *
             * @return     The load value at @p loadId for the timestamp at @p
             *     timestampPosition.
             */
            inline Types::loadSnapshot LoadSnapshotOf ( Types::loadId loadId
                                                      , Types::index  timestampPosition ) 
            {
                USAGE_ASSERT ( loadId                         != Const::NONE       );
                USAGE_ASSERT ( loadId                          < loads_.size()     );
                USAGE_ASSERT ( timestampPosition              != Const::NONE       );
                USAGE_ASSERT ( loadSnapshots_[loadId].size()  <= timestamps_.size());
                USAGE_ASSERT ( timestampPosition              <= loadSnapshots_[loadId].size() 
                            || loadSnapshots_[loadId].size()  == 0  );

                if ( loadSnapshots_[loadId].size() != 0 )
                {
                    return loadSnapshots_[loadId][timestampPosition];
                } else 
                { // No snapshot available at the load with loadId
                    return Const::NONE; 
                }
            }

            /**
             * @brief      The load value of the load at @p loadId for the
             *     timestamp at @p timestampPosition.
             *
             * @param[in]  loadId             The load identifier.
             * @param[in]  timestampPosition  The timestamp position.
             *
             * @return     The load value at @p loadId for the timestamp at @p
             *     timestampPosition.
             */
            inline Types::loadSnapshot LoadSnapshotOf ( Types::loadId   loadId
                                                      , Types::index    timestampPosition ) const
            {
                USAGE_ASSERT ( loadId                         != Const::NONE       );
                USAGE_ASSERT ( loadId                          < loads_.size()     );
                USAGE_ASSERT ( timestampPosition              != Const::NONE       );
                USAGE_ASSERT ( loadSnapshots_[loadId].size()  <= timestamps_.size());
                USAGE_ASSERT ( timestampPosition              <= loadSnapshots_[loadId].size() 
                            || loadSnapshots_[loadId].size()  == 0  );

                if ( loadSnapshots_[loadId].size() != 0 )
                {
                    return loadSnapshots_[loadId][timestampPosition];
                } else
                { // No snapshot available at the load with loadId
                    return Const::NONE; 
                }
            }

            /**
             * @brief      Loads a snapshot at a vertex with @p vertexId and a @p
             *     timestampPosition.
             *
             * @param[in]  vertexId           The vertex identifier
             * @param[in]  timestampPosition  The timestamp position
             * @param      loadSnapshots      The load snapshots (load
             *      snapshots are added to the back, if no loads are at a vertex input
             *      and output are the same).
             */
            inline void LoadSnapshotsAt ( Types::vertexId                    vertexId
                                        , Types::index                       timestampPosition
                                        , std::vector<Types::loadSnapshot> & loadSnapshots ) 
            {
                USAGE_ASSERT ( vertexId           < Graph().Vertices().size() );
                USAGE_ASSERT ( timestampPosition != Const::NONE               );
                USAGE_ASSERT ( loadSnapshots.empty()                          );

                std::vector<Types::loadId> loadIds;
                LoadsAt(vertexId, loadIds);

                for ( Types::index index = 0
                    ; index < loadIds.size()
                    ; ++index)
                {
                    loadSnapshots.emplace_back( loadSnapshots_[ loadIds[index] ][timestampPosition] );
                }
            }

            /**
             * @brief      Loads a snapshot at a vertex and a @p timestampPosition.
             *
             * @param[in]  vertex             The vertex.
             * @param[in]  timestampPosition  The timestamp position.
             * @param      loadSnapshots      The load snapshots (load
             *      snapshots are added to the back, if no loads are at a vertex input
             *      and output are the same).
             */
            inline void LoadSnapshotsAt ( TVertex                    const & vertex
                                        , Types::index                       timestampPosition
                                        , std::vector<Types::loadSnapshot> & loadSnapshots ) 
            {
                USAGE_ASSERT( loadSnapshots.empty() );

                Types::vertexId vertexId   = VertexId( vertex );
                ESSENTIAL_ASSERT( vertexId < Graph().Vertices().size() );
                
                LoadSnapshotsAt ( vertexId, timestampPosition, loadSnapshots );
            }

            /**
             * @brief      Loads a snapshot at a certain timestamp.
             * @details    Some loads might not have snapshots over time. In
             *     this case this method returns a vector with @p Const::NONE at
             *     these generators.
             *
             * @param[in]  timestamp                 The timestamp.
             * @param      loadSnapshotsAtTimestamp  The load snapshots at the timestamp.
             */
            inline void LoadSnapshotsAt ( Types::timestampSnapshot           timestamp
                                        , std::vector<Types::loadSnapshot> & loadSnapshotsAtTimestamp ) 
            {
                USAGE_ASSERT ( !timestamps_.empty()               );
                USAGE_ASSERT ( loadSnapshotsAtTimestamp.empty() );

                Types::index position = PositionOf( timestamp );
                if ( position != Const::NONE ) 
                {
                    for ( Types::loadId loadId = 0
                        ; loadId < loadSnapshots_.size()
                        ; ++loadId ) 
                    {
                        if ( loadSnapshots_[loadId].size() == 0 ) 
                        { // No snapshot available
                            loadSnapshotsAtTimestamp.emplace_back( Const::NONE );
                        }
                        loadSnapshotsAtTimestamp.emplace_back( LoadSnapshotOf ( loadId, position ) );
                    }
                }
            }
        ///@}

        ///@name Generator Loops
        ///@{
#pragma mark GENERATOR_LOOPS

            /**
             * @brief      Iterate over all generators (vertex independent).
             *
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a generator object as input.
             * 
             * @code{.cpp}
             *      for_all_generators (
             *          []( TGeneratorProperties & generatorProperty ) 
             *          { 
             *              // Do something with the generator object.
             *          }
             *      );
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all generators.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_generators ( FUNCTION function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_generators ( *this
                                         , function );
            }

            /**
             * @brief      Iterate over all generators (vertex independent)
             *
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a generator object as input
             * 
             * @code{.cpp}
             *      for_all_generators (
             *          []( TGeneratorProperties const & generatorProperty ) 
             *          { 
             *              // Do something with the generator object.
             *          }
             *      );
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all generators of a @c power grid. @c
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_generators ( FUNCTION function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_generators ( *this
                                         , function );
            }

            /**
             * @brief      The @c for loop @c over all generators at a vertex
             *     @f$\vertex\in\vertices@f$ with @p vertexId.
             *
             * @param      vertex      The vertex @f$\vertex\in\vertices@f$.
             * @param[in]  function    The function.
             * 
             * @code{.cpp}
             *      for_all_generators_at ( vertex, 
             *          []( TGeneratorProperties & generatorProperty ) 
             *          { 
             *              // Do something with the generator vertex. 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all generators of @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_generators_at ( TVertex  const & vertex
                                       , FUNCTION         function )
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_generators_at ( vertex
                                            , *this
                                            , function );
            }

            /**
             * @brief      The @c for loop @c over all generators at a vertex
             *     @f$\vertex\in\vertices@f$ with @p vertexId.
             *
             * @param      vertex      The vertex @f$\vertex\in\vertices@f$.
             * @param[in]  function    The function.
             * 
             * @code{.cpp}
             *      for_all_generators_at ( vertex, 
             *          []( TGeneratorProperties const & generatorProperty ) 
             *          { 
             *              // Do something with the generator vertex. 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all generators of @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_generators_at ( TVertex  const & vertex
                                       , FUNCTION         function ) const
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_generators_at ( vertex
                                            , *this
                                            , function );
            }

            /**
             * @brief      The @c for loop @c over all generators at a vertex
             *     with @p vertexId.
             *
             * @param      vertexId    The vertex identifier.
             * @param[in]  function    The function.
             * 
             * @code{.cpp}
             *      for_all_generators_at (
             *          []( TGeneratorProperties & generatorProperty ) 
             *          { 
             *              // Do something with the generator vertex. 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all generators of @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_generators_at ( Types::vertexId vertexId
                                       , FUNCTION        function )
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_generators_at ( vertexId
                                            , *this
                                            , function );
            }

            /**
             * @brief      The @c for loop @c over all generators at a vertex
             *     with @p vertexId.
             *
             * @param      vertexId    The vertex identifier.
             * @param[in]  function    The function.
             * 
             * @code{.cpp}
             *      for_all_generators_at ( vertexId,
             *          []( TGeneratorProperties const & generatorProperty ) 
             *          { 
             *              // Do something with the generator vertex. 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all generators of @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_generators_at ( Types::vertexId vertexId
                                       , FUNCTION        function ) const
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_generators_at ( vertexId
                                            , *this
                                            , function );
            }

            /**
             * @brief      Iterate over all vertices that have a generator.
             *
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a vertexId as input.
             *      
             * @code{.cpp}
             *      for_all_vertex_identifiers_with_generator (
             *          []( Types::vertexId vertexId ) 
             *          { 
             *              // Do something with the identifier of a vertex.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all vertex identifiers having a generator.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_vertex_identifiers_with_generator ( FUNCTION function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_vertex_identifiers_with_generator ( *this
                                                                , function );
            }

            /**
             * @brief      Iterate over all vertices that have a generator.
             *
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a vertexId as input.
             *      
             * @code{.cpp}
             *      for_all_vertex_identifiers_with_generator (
             *          []( Types::vertexId vertexId ) 
             *          { 
             *              // Do something with the identifier of a vertex.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all vertex identifiers having a generator.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_vertex_identifiers_with_generator ( FUNCTION function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_vertex_identifiers_with_generator ( *this
                                                                , function );
            }

            /**
             * @brief      Iterate over all generator identifiers at a vertex.
             *
             * @param[in]  vertex    The vertex object @f$\vertex\in\vertices@f$.
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a generatorId as input.
             *      
             * @code{.cpp}
             *      for_all_generator_identifiers_at ( vertex, 
             *          []( Types::generatorId generatorId ) 
             *          { 
             *              // Do something with the identifier of the generator.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all generator identifiers at @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_generator_identifiers_at ( TVertex const & vertex
                                                  , FUNCTION        function )
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_generator_identifiers_at ( vertex
                                                       , *this
                                                       , function );
            }

            /**
             * @brief      Iterate over all generator identifiers at a vertex.
             *
             * @param[in]  vertex    The vertex object @f$\vertex\in\vertices@f$.
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a generatorId as input.
             *      
             * @code{.cpp}
             *      for_all_generator_identifiers_at ( vertex, 
             *          []( Types::generatorId generatorId ) 
             *          { 
             *              // Do something with the identifier of the generator.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all generator identifiers at @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_generator_identifiers_at ( TVertex const & vertex
                                                  , FUNCTION        function ) const
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_generator_identifiers_at ( vertex
                                                       , *this
                                                       , function );
            }

            /**
             * @brief      Iterate over all generator identifiers at a vertex.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a generatorId as input.
             *      
             * @code{.cpp}
             *      for_all_generator_identifiers_at ( vertexId, 
             *          []( Types::generatorId generatorId ) 
             *          { 
             *              // Do something with the identifier of the generator.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all generator identifiers at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_generator_identifiers_at ( Types::vertexId vertexId
                                                  , FUNCTION        function )
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_generator_identifiers_at ( vertexId
                                                       , *this
                                                       , function );
            }

            /**
             * @brief      Iterate over all generator identifiers at a vertex.
             *
             * @param[in]  vertexId  The vertex identifier.
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a generatorId as input.
             *      
             * @code{.cpp}
             *      for_all_generator_identifiers_at ( vertexId, 
             *          []( Types::generatorId generatorId ) 
             *          { 
             *              // Do something with the identifier of the generator.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all generator identifiers at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_generator_identifiers_at ( Types::vertexId vertexId
                                                  , FUNCTION        function ) const
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_generator_identifiers_at ( vertexId
                                                       , *this
                                                       , function );
            }

            /**
             * @brief      Iterate over all vertices that have a generator and
             *     its generators.
             *
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a vertexId and a generator object as input.
             *      
             * @code{.cpp}
             *      for_all_generator_tuple (
             *          []( Types::vertexId        vertexId
             *            , TGeneratorProperties & generator ) 
             *          { 
             *              // Do something with ?.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all generator tuple of the from (vertexId, generator).
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_generator_tuple ( FUNCTION function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_generator_tuple ( *this
                                              , function );
            }

            /**
             * @brief      Iterate over all vertices that have a generator and
             *     its generators.
             *
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a vertexId and a generator object as input.
             *      
             * @code{.cpp}
             *      for_all_generator_tuple (
             *          []( Types::vertexId      vertexId
             *            , TGeneratorProperties generator ) 
             *          { 
             *              // Do something with ?.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all generator tuple of the from (vertexId, generator).
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_generator_tuple ( FUNCTION function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_generator_tuple ( *this
                                              , function );
            }

            /**
             * @brief      Iterate over all vertices that have a generator and
             *     its generators.
             *
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a vertexId and a vector of generator objects as input.
             *      
             * @code{.cpp}
             *      for_all_generators_tuple (
             *          []( Types::vertexId                   vertexId
             *            , std::vector<TGeneratorProperties> generators ) 
             *          { 
             *              // Do something with ?.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all generator tuple of the from (vertexId, generators).
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_generators_tuple ( FUNCTION function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_generators_tuple ( *this
                                               , function );
            }

            /**
             * @brief      Iterate over all vertices that have a generator and
             *     its generators.
             *
             * @param[in]  function  The function pointer, e.g., lambda function
             *      that has a vertexId and a vector of generator objects as input.
             *      
             * @code{.cpp}
             *      for_all_generators_tuple<ExecutionPolicy::sequential>(
             *          []( Types::vertexId                   vertexId
             *            , std::vector<TGeneratorProperties> generators ) 
             *          { 
             *              // Do something with ?.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all generator tuple of the from (vertexId, generators).
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_generators_tuple ( FUNCTION function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_generators_tuple ( *this
                                               , function );
            }
        ///@}

        ///@name Generator Snapshot Loops
        ///@{
#pragma mark GENERATOR_SNAPSHOT_LOOPS
            /**
             * @brief      The @c for loop @c over all generator maximum real power p.u. snapshots.
             *
             * @param[in]  function    The function, e.g., lambda function.
             *
             * @code{.cpp}
             *      for_all_real_power_generator_snapshots<ExecutionPolicy::sequential>(
             *          []( Types::index             snapshotId
             *            , Types::generatorSnapshot snapshot ) 
             *          { 
             *              // Do something with the snapshotId and generator snapshot object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power generator snapshots.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_generator_snapshots ( FUNCTION function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_generator_snapshots ( *this
                                                             , function );
            }

            /**
             * @brief      The @c for loop @c over all generator maximum real
             *     power p.u. snapshots.
             *
             * @param      generatorId The identifier of the generator.
             * @param[in]  function    The function, e.g., lambda function.
             *
             * @code{.cpp}
             *      for_all_real_power_generator_snapshots<ExecutionPolicy::sequential>(
             *          []( Types::index             snapshotId
             *            , Types::generatorSnapshot snapshot ) 
             *          { 
             *              // Do something with the snapshotId and generator snapshot object.
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power generator snapshots.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_generator_snapshots( FUNCTION function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_generator_snapshots ( *this
                                                             , function );
            }

            /**
             * @brief      The @c for loop @c over all maximum real power p.u.
             *     snapshots of a generator with @p generatorId.
             *
             * @param      generatorId The identifier of the generator.
             * @param[in]  function    The function, e.g., lambda function 
             * 
             * @pre        Check if the generator identifier @p generatorId of the
             *     generatorProperties exists before using this method.
             * 
             * @code{.cpp}
             *      if ( network.HasGenerator ( generatorId ) )
             *      {
             *          for_all_real_power_generator_snapshots_of<ExecutionPolicy::sequential> ( 
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
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power generator snapshots of @p generatorId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_generator_snapshots_of ( Types::generatorId generatorId
                                                           , FUNCTION           function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_generator_snapshots_of ( *this
                                                                , generatorId
                                                                , function );
            }

            /**
             * @brief      The @c for loop @c over all maximum real power p.u.
             *     snapshots of a generator with @p generatorId.
             *
             * @param[in]  function    The function, e.g., lambda function.
             *
             * @pre        Check if the generator identifier @p generatorId of the
             *     generatorProperties exists before using this method.
             *
             * @code{.cpp}
             *      if ( network.HasGenerator ( generatorId ) )
             *      {
             *          for_all_real_power_generator_snapshots_of<ExecutionPolicy::sequential> ( 
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
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power generator snapshots of @p generatorId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_generator_snapshots_of ( Types::vertexId generatorId
                                                           , FUNCTION        function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_generator_snapshots_of ( *this
                                                                , generatorId
                                                                , function );
            }

            /**
             * @brief      The @c for loop @c over all maximum real power p.u.
             *     snapshots of a @p generator.
             *
             * @param      generatorProperties  The generator properties.
             * @param[in]  function             The function, e.g., lambda function.
             * 
             * @pre        Check if the generator's properties @p
             *     generatorProperties exists before using this method.
             * 
             * @code{.cpp}
             *      if ( network.HasGenerator ( network.GeneratorId ( generatorProperties ) ) )
             *      {
             *          for_all_real_power_generator_snapshots_of<ExecutionPolicy::sequential> (
             *              []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              {    
             *                  // Do something with the snapshotId and generator snapshot object.
             *              }
             *          );
             *      }
             * @endcode 
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power generator snapshots of @p generator.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_generator_snapshots_of ( TGeneratorProperties const & generatorProperties
                                                           , FUNCTION                     function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_generator_snapshots_of ( *this
                                                                , generatorProperties
                                                                , function );
            }

            /**
             * @brief      The @c for loop @c over all maximum real power p.u.
             *     snapshots of a @p generator.
             *
             * @param      generatorProperties  The generator properties.
             * @param[in]  function             The function, e.g., lambda function.
             * 
             * @pre        Check if the generator's properties @p
             *     generatorProperties exists before using this method.
             * 
             * @code{.cpp}
             *      if ( network.HasGenerator ( network.GeneratorId ( generatorProperties ) ) )
             *      {
             *          for_all_real_power_generator_snapshots_of<ExecutionPolicy::sequential> (
             *              []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              {    
             *                  // Do something with the snapshotId and generator snapshot object.
             *              }
             *          );
             *      }
             * @endcode 
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power generator snapshots of @p generator.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_generator_snapshots_of ( TGeneratorProperties const & generatorProperties
                                                           , FUNCTION                     function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_generator_snapshots_of ( *this
                                                                , generatorProperties
                                                                , function );
            }

            /**
             * @brief      The @c for loop @c over all generator maximum real
             *     power p.u. snapshots at a vertex with @p vertexId.
             *
             * @param      vertexId    The identifier of a vertex.
             * @param[in]  function    The function, e.g., lambda function.
             * 
             * @pre        Check if the vertex identifier @p vertexId of the
             *     vertex exists before using this method.
             * 
             * @code{.cpp}
             *      if ( network.Graph().VertexExists( vertexId ) )
             *      {
             *          for_all_real_power_generator_snapshots_at<ExecutionPolicy::sequential> (
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
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power generator snapshots at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_generator_snapshots_at ( Types::vertexId vertexId
                                                           , FUNCTION        function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_generator_snapshots_at ( *this
                                                                , vertexId
                                                                , function );
            }

            /**
             * @brief      The @c for loop @c over all generator maximum real
             *     power p.u. snapshots at a vertex with @p vertexId.
             *
             * @param      vertexId    The identifier of a vertex.
             * @param[in]  function    The function, e.g., lambda function.
             * 
             * @pre        Check if the vertex identifier @p vertexId of the
             *     vertex exists before using this method.
             * 
             * @code{.cpp}
             *      if ( network.Graph().VertexExists( vertexId ) )
             *      {
             *          for_all_real_power_generator_snapshots_at<ExecutionPolicy::sequential> (
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
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power generator snapshots at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_generator_snapshots_at ( Types::vertexId vertexId
                                                           , FUNCTION        function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_generator_snapshots_at ( *this
                                                                , vertexId
                                                                , function );
            }

            /**
             * @brief      The @c for loop @c over all generator maximum real
             *     power p.u. snapshots at a @p vertex.
             *
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
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power generator snapshots at @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_generator_snapshots_at ( TVertex const & vertex
                                                           , FUNCTION        function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_generator_snapshots_at ( *this
                                                                , vertex
                                                                , function );
            }

            /**
             * @brief      The @c for loop @c over all generator maximum real
             *     power p.u. snapshots at a @p vertex.
             *
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
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power generator snapshots at @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_generator_snapshots_at ( TVertex const & vertex
                                                           , FUNCTION        function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_generator_snapshots_at ( *this
                                                                , vertex
                                                                , function );
            }

            /**
             * @brief      The sequential @c for loop @c over snapshots with a
             *     certain @ timestampPosition for all @p generators.
             * @details    This loop basically extracts a row.
             *
             * @param      vertexId             The identifier of a vertex.
             * @param      timestampPosition    The position of the snapshot.
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
             *              vertexId,
             *              timestampPosition,
             *              []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              { 
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      }       
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power generator at @p timestamp at @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION>  
            inline
            void for_all_real_power_generator_snapshots_at ( Types::vertexId vertexId
                                                           , Types::index    timestampPosition
                                                           , FUNCTION        function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_generator_snapshots_at ( *this
                                                                , vertexId
                                                                , timestampPosition
                                                                , function );
            }

            /**
             * @brief      The sequential @c for loop @c over snapshots with a
             *     certain @ timestampPosition for all @p generators.
             * @details    This loop basically extracts a row.
             *
             * @param      vertexId             The identifier of a vertex.
             * @param      timestampPosition    The position of the snapshot
             *     (timestamp of the snapshot).
             * @param[in]  function             The function, e.g. , lambda function.
             * 
             * @pre        Check if the vertex identifier @p vertexId of the
             *     vertex exists before using this method.
             * 
             * @code{.cpp}
             *      if ( network.Graph().VertexExists( vertexId ) )
             *      {
             *          for_all_real_power_generator_snapshots_at<ExecutionPolicy::sequential> (
             *              vertexId,
             *              timestampPosition,
             *              []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              { 
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      }       
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power generator at @p timestamp at @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline
            void for_all_real_power_generator_snapshots_at ( Types::vertexId    vertexId
                                                           , Types::index       timestampPosition
                                                           , FUNCTION           function ) const
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_generator_snapshots_at ( *this
                                                                , vertexId
                                                                , timestampPosition
                                                                , function );
            }

            /**
             * @brief      The @c for loop @c over all real power snapshots of a
             *     @p generator and a timestamp at @p timestampPosition.
             *
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
             *              vertex,
             *              timestampPosition,
             *              []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              { 
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      } 
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load at @p timestamp at @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline
            void for_all_real_power_generator_snapshots_at ( TVertex const & vertex
                                                           , Types::index    timestampPosition
                                                           , FUNCTION        function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_generator_snapshots_at ( *this
                                                                , vertex
                                                                , timestampPosition
                                                                , function );
            }

            /**
             * @brief      The @c for loop @c over all real power snapshots of a
             *     @p generator and a timestamp at @p timestampPosition.
             *
             * @param      vertex               The vertex.
             * @param[in]  timestampPosition    The timestamp position.
             * @param[in]  function             The function.
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
             *              []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              { 
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      } 
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load at @p timestamp at @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline
            void for_all_real_power_generator_snapshots_at ( TVertex  const & vertex
                                                           , Types::index     timestampPosition
                                                           , FUNCTION         function ) const
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_generator_snapshots_at ( *this
                                                                , vertex
                                                                , timestampPosition
                                                                , function );
            }
        ///@}

        ///@name Seriell Load Loops
        ///@{
#pragma mark SERIELL_LOAD_LOOPS
            
            /**
             * @brief      The @p for loop over all @p loads (vertex
             *     independent).
             *
             * @param[in]  function    The function pointer, e.g., lambda function
             *      that has a load object as input.
             *
             * @code{.cpp}
             *      for_all_loads<ExecutionPolicy::sequential> (
             *          []( TLoadProperties & load ) 
             *          { 
             *              // Do something with the load object. 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all loads.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_loads ( FUNCTION function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_loads ( *this
                                    , function );
            }

            /**
             * @brief      The @p for loop over all @p loads (vertex
             *     independent).
             *
             * @param[in]  function    The function pointer, e.g., lambda function
             *      that has a load object as input.
             *
             * @code{.cpp}
             *      for_all_loads<ExecutionPolicy::sequential> (
             *          []( TLoadProperties const & load ) 
             *          { 
             *              // Do something with the load object. 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all loads.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_loads ( FUNCTION function ) const
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_loads ( *this
                                    , function );
            }

            /**
             * @brief      The @p for loop over all @p vertices that have a
             *     load.
             *
             * @param[in]  function    The function pointer, e.g., lambda
             *      function that has a vertex identifier @p Types::vertexId
             *      as input.
             *
             * @code{.cpp}
             *      for_all_vertex_identifiers_with_load<ExecutionPolicy::sequential> (
             *          []( Types::vertexId vertexId ) 
             *          { 
             *              // Do something with the vertex identifier that has loads. 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all vertex identifier that have a load.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline
            void for_all_vertex_identifiers_with_load ( FUNCTION function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_vertex_identifiers_with_load ( *this
                                                           , function );
            }

            /**
             * @brief      The @p for loop over all load identifiers at a
             *     vertex identifier @p vertexId.
             *
             * @param[in]  vertexId    The vertex identifier.
             * @param[in]  function    The function pointer, e.g., lambda
             *      function that has a load identifier @p Types::loadId as
             *      input.
             *
             * @code{.cpp}
             *      for_all_load_identifiers_at<ExecutionPolicy::sequential>( vertexId
             *          , []( Types::loadId loadId ) 
             *          { 
             *              // Do something with the load identifier at the @p vertex. 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all load identifier at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline
            void for_all_load_identifiers_at ( Types::vertexId  vertexId
                                             , FUNCTION         function ) const
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_load_identifiers_at ( vertexId
                                                  , *this
                                                  , function );
            }

            /**
             * @brief      The @p for loop over all load identifiers at a
             *     vertex.
             *
             * @param      vertex      The vertex object.
             * @param[in]  function    The function pointer, e.g., lambda
             *      function that has a load identifier as input.
             *
             * @code{.cpp}
             *      for_all_load_identifiers_at<ExecutionPolicy::sequential> ( vertex
             *          , []( Types::loadId loadId ) 
             *          { 
             *              // Do something with the load identifier at the @p vertex. 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all load identifier at @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline
            void for_all_load_identifiers_at ( TVertex  const & vertex
                                             , FUNCTION         function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_load_identifiers_at ( vertex
                                                  , *this
                                                  , function );
            }

            /**
             * @brief      The @p for loop over all load objects at a
             *     @p vertex.
             *
             * @param      vertex      The vertex object.
             * @param[in]  function    The function pointer, e.g., lambda 
             *      function that has a load object as input.
             *
             * @code{.cpp}
             *      for_all_loads_at<ExecutionPolicy::sequential> ( vertex
             *          , []( TLoadProperties & load ) 
             *          { 
             *              // Do something with the load object at the @p vertex. 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all loads at @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_loads_at ( TVertex  const & vertex
                                  , FUNCTION         function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_loads_at ( vertex
                                       , *this
                                       , function );
            }

            /**
             * @brief      The @p for loop over all load objects at a
             *     @p vertex.
             *
             * @param      vertex      The vertex object.
             * @param[in]  function    The function pointer, e.g., lambda
             *      function that has a load object as input.
             *
             * @code{.cpp}
             *      for_all_loads_at<ExecutionPolicy::sequential> ( vertex
             *          , []( TLoadProperties const & load ) 
             *          { 
             *              // Do something with the load object at the @p vertex. 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all loads at @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_loads_at ( TVertex  const & vertex
                                  , FUNCTION         function ) const
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_loads_at ( vertex
                                       , *this
                                       , function );
            }

            /**
             * @brief      The @p for loop over all load objects at a vertex
             *     identifier @p vertexId.
             *
             * @param[in]  vertexId    The vertex identifier.
             * @param[in]  function    The function pointer, e.g., lambda
             *      function that has a load object as input.
             *
             * @code{.cpp}
             *      for_all_loads_at<ExecutionPolicy::sequential> ( vertexId
             *          , []( TLoadProperties & load ) 
             *          { 
             *              // Do something with the load object at the @p vertexId. 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all loads at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_loads_at ( Types::vertexId const vertexId
                                  , FUNCTION              function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_loads_at ( vertexId
                                       , *this
                                       , function );                
            }

            /**
             * @brief      The @p for loop over all load objects at a vertex
             *     identifier @p vertexId.
             *
             * @param[in]  vertexId    The vertex identifier.
             * @param[in]  function    The function pointer, e.g., lambda
             *      function that has a load object as input.
             *
             * @code{.cpp}
             *      for_all_loads_at<ExecutionPolicy::sequential> ( vertexId
             *          , []( TLoadProperties const & load ) 
             *          { 
             *              // Do something with the load object at the @p vertexId. 
             *          }
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all loads at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_loads_at ( Types::vertexId vertexId
                                  , FUNCTION        function ) const
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_loads_at ( vertexId
                                       , *this
                                       , function );
            }

            /**
             * @brief      The @p for loop over @c all vertices@c that have a
             *     load and its @c load objects@c.
             *
             * @param[in]  function    The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and a
             *      @c load object@c as input.
             *
             * @code{.cpp}
             *      for_all_load_tuples<ExecutionPolicy::sequential> (
             *          []( Types::vertexId   vertexId
             *            , TLoadProperties & load ) 
             *          { 
             *              // Do something with the vertexId and load object. 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all load tuples (vertexId, load).
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_load_tuples ( FUNCTION function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_load_tuples ( *this
                                          , function );                
            }

            /**
             * @brief      The @p for loop over @c all vertices@c that have a
             *     load and its @c load objects@c.
             *
             * @param[in]  function    The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and a
             *      @c load object@c as input.
             *
             * @code{.cpp}
             *      for_all_load_tuples<ExecutionPolicy::sequential> (
             *          []( Types::vertexId         vertexId
             *            , TLoadProperties const & load ) 
             *          { 
             *              // Do something with the vertexId and load object. 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all load tuples (vertexId, load).
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_load_tuples ( FUNCTION function ) const
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_load_tuples ( *this
                                          , function );
            }

            /**
             * @brief      The @p for loop over @c all vertices@c that
             *     have a load.
             *
             * @param[in]  function    The function pointer, e.g., lambda
             *      function that has a vertex identifier @p vertexId and its
             *      @c load objects@c as input.
             *
             * @code{.cpp}
             *      for_all_loads_tuple<ExecutionPolicy::sequential> (
             *          []( Types::vertexId                vertexId
             *            , std::vector<TLoadProperties> & loads ) 
             *          { 
             *              // Do something with the vertexId and load object. 
             *          }
             *      );
             * @endcode
             *
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all loads tuple (vertexId, load).
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_loads_tuple ( FUNCTION function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_loads_tuple ( *this
                                          , function );
            }

        ///@}

        ///@name Load Snapshot Loops
        ///@{
#pragma mark LOAD_SNAPSHOT_LOOPS
            /**
             * @brief      The @c for loop @c over all load real power snapshots.
             *
             * @param[in]  function    The function, e.g., lambda function.
             * 
             * @code{.cpp}
             *      for_all_real_power_load_snapshots<ExecutionPolicy::sequential>(
             *          []( Types::index        snapshotId
             *            , Types::loadSnapshot snapshot ) 
             *          { 
             *              // Do something with the snapshotId and load snapshot object.
             *          }
             *      );
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load snapshots.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_load_snapshots( FUNCTION function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_load_snapshots ( *this
                                                        , function );
            }

            /**
             * @brief      The @c for loop @c over all load real power snapshots.
             *
             * @param[in]  function    The function, e.g., lambda function.
             * 
             * @code{.cpp}
             *      for_all_real_power_load_snapshots<ExecutionPolicy::sequential>(
             *          []( Types::index        snapshotId
             *            , Types::loadSnapshot snapshot ) 
             *          { 
             *              // Do something with the snapshotId and load snapshot object.
             *          }
             *      );
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load snapshots.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_load_snapshots( FUNCTION function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_load_snapshots ( *this
                                                        , function );
            }

            /**
             * @brief      The @c for loop @c over all real power snapshots of
             *     a load with @p loadId.
             *
             * @param[in]  loadId      The load identifier.
             * @param[in]  function    The function, e.g., lambda function.
             * 
             * @pre        Check if the load identifier @p loadId of the
             *     loadProperties exists before using this method.
             * 
             * @code{.cpp}
             *      if ( network.HasLoad ( loadId ) )
             *      {
             *          for_all_real_power_load_snapshots_of<ExecutionPolicy::sequential> ( 
             *              loadId,
             *              []( Types::index snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              { 
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      }
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load snapshots of @p loadId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_load_snapshots_of ( Types::loadId loadId
                                                      , FUNCTION      function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_load_snapshots_of ( *this
                                                           , loadId
                                                           , function );
            }

            /**
             * @brief      The @c for loop @c over all real power snapshots of
             *     a load with @p loadId.
             *
             * @param[in]  loadId      The load identifier.
             * @param[in]  function    The function, e.g., lambda function.
             * 
             * @pre        Check if the load identifier @p loadId of the
             *     loadProperties exists before using this method.
             * 
             * @code{.cpp}
             *      if ( network.HasLoad ( loadId ) )
             *      {
             *          for_all_real_power_load_snapshots_of<ExecutionPolicy::sequential> ( 
             *              loadId,
             *              []( Types::index snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              { 
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      }
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load snapshots of @p loadId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_load_snapshots_of ( Types::vertexId loadId
                                                      , FUNCTION        function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_load_snapshots_of ( *this
                                                           , loadId
                                                           , function );
            }

            /**
             * @brief      The @c for loop @c over all real power snapshots of
             *     a @p load.
             *
             * @param[in]  load        The load object.
             * @param[in]  function    The function, e.g., lambda function.
             * 
             * @pre        Check if the load's properties @p loadProperties exists
             *     before using this method.
             * 
             * @code{.cpp}
             *      if ( network.HasLoad ( network.LoadId ( loadProperties ) ) )
             *      {
             *          for_all_real_power_load_snapshots_of<ExecutionPolicy::sequential> (
             *              []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              {    
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      }
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load snapshots of @p load.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_load_snapshots_of ( TLoadProperties load
                                                      , FUNCTION        function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_load_snapshots_of ( *this
                                                           , load
                                                           , function );
            }

            /**
             * @brief      The @c for loop @c over all real power snapshots of
             *     a @p load.
             *
             * @param[in]  load        The load object.
             * @param[in]  function    The function, e.g., lambda function.
             * 
             * @pre        Check if the load's properties @p loadProperties exists
             *     before using this method.
             * 
             * @code{.cpp}
             *      if ( network.HasLoad ( network.LoadId ( loadProperties ) ) )
             *      {
             *          for_all_real_power_load_snapshots_of<ExecutionPolicy::sequential> (
             *              []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              {    
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      }
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load snapshots of @p load.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_load_snapshots_of ( TLoadProperties const & load
                                                      , FUNCTION                function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_load_snapshots_of ( *this
                                                           , load
                                                           , function );
            }

            /**
             * @brief      The @c for loop @c over all real power snapshots of
             *     a @p load.
             *
             * @param[in]  vertexId    The vertex identifier.
             * @param[in]  function    The function, e.g., lambda function.
             * 
             * @pre        Check if the vertex identifier @p vertexId of the
             *     vertex exists before using this method.
             * 
             * @code{.cpp}
             *      if ( network.Graph().VertexExists( vertexId ) )
             *      {
             *          for_all_real_power_load_snapshots_at<ExecutionPolicy::sequential> (
             *              vertexId,
             *              []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              { 
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      }
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load snapshots at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_load_snapshots_at ( Types::vertexId vertexId
                                                      , FUNCTION        function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_load_snapshots_at ( *this
                                                           , vertexId
                                                           , function );
            }

            /**
             * @brief      The @c for loop @c over all real power snapshots of
             *     a @p load.
             *
             * @param[in]  vertexId    The vertex identifier.
             * @param[in]  function    The function, e.g., lambda function.
             * 
             * @pre        Check if the vertex identifier @p vertexId of the
             *     vertex exists before using this method.
             * 
             * @code{.cpp}
             *      if ( network.Graph().VertexExists( vertexId ) )
             *      {
             *          for_all_real_power_load_snapshots_at<ExecutionPolicy::sequential> (
             *              vertexId,
             *              []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              { 
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      }
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load snapshots at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_load_snapshots_at ( Types::vertexId vertexId
                                                      , FUNCTION        function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_load_snapshots_at ( *this
                                                           , vertexId
                                                           , function );
            }

            /**
             * @brief      The @c for loop @c over all real power snapshots of
             *     a @p load.
             *
             * @param      vertex      The vertex object.
             * @param[in]  function    The function, e.g., lambda function.
             * 
             * @pre        Check if the @p vertex exists before using this method.
             * 
             * @code{.cpp}
             *      if ( network.Graph().VertexExists( network.Graph().VertexId( vertex ) ) )
             *      {
             *          for_all_real_power_load_snapshots_at<ExecutionPolicy::sequential> (
             *              vertex,
             *              []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              { 
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      }
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load snapshots at @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_load_snapshots_at( TVertex const & vertex
                                                     , FUNCTION        function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_load_snapshots_at ( *this
                                                           , vertex
                                                           , function );
            }

            /**
             * @brief      The @c for loop @c over all real power snapshots of
             *     a @p load.
             *
             * @param      vertex               The vertex object.
             * @param[in]  timestampPosition    The timestamp position
             * @param[in]  function             The function, e.g., lambda function.
             * 
             * @pre        Check if the @p vertex exists before using this method.
             * 
             * @code{.cpp}
             *      if ( network.Graph().VertexExists( network.Graph().VertexId( vertex ) ) )
             *      {
             *          for_all_real_power_load_snapshots_at<ExecutionPolicy::sequential> (
             *              vertex,
             *              []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              { 
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      }
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load snapshots at @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_load_snapshots_at ( TVertex const & vertex
                                                      , FUNCTION        function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_load_snapshots_at ( *this
                                                           , vertex
                                                           , function );
            }

            /**
             * @brief      The @c for loop @c over all real power snapshots of
             *     a @p load.
             *
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
             *              vertexId,
             *              timestampPosition,
             *              []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              { 
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      }
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load snapshots at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_load_snapshots_at ( Types::vertexId vertexId
                                                      , Types::index    timestampPosition
                                                      , FUNCTION        function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_load_snapshots_at ( *this
                                                           , vertexId
                                                           , timestampPosition
                                                           , function );
            }

            /**
             * @brief      The @c for loop @c over all real power snapshots of
             *     a @p load.
             *
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
             *              vertexId
             *              , timestampPosition
             *              , []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              { 
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      }
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load snapshots at @p vertexId.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_load_snapshots_at ( Types::vertexId vertexId
                                                      , Types::index    timestampPosition
                                                      , FUNCTION        function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_load_snapshots_at ( *this
                                                           , vertexId
                                                           , timestampPosition
                                                           , function );
            }

            /**
             * @brief      The @c for loop @c over all real power snapshots of
             *     a @p load.
             *
             * @param      vertex               The vertex object.
             * @param[in]  timestampPosition    The timestamp position.
             * @param[in]  function             The function, e.g., lambda function.
             * 
             * @pre        Check if the @p vertex exists before using this method.
             * 
             * @code{.cpp}
             *      if ( network.Graph().VertexExists( vertexId ) )
             *      {
             *          for_all_real_power_load_snapshots_at<ExecutionPolicy::sequential> (
             *              vertex
             *              , timestampPosition
             *              , []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              { 
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      } 
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load at @p timestamp at @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_load_snapshots_at( TVertex const & vertex
                                                     , Types::index    timestampPosition
                                                     , FUNCTION        function ) 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_load_snapshots_at ( *this
                                                           , vertex
                                                           , timestampPosition
                                                           , function );
            }

            /**
             * @brief      The @c for loop @c over all real power snapshots of
             *     a @p load.
             *
             * @param      vertex               The vertex object.
             * @param[in]  timestampPosition    The timestamp position
             * @param[in]  function             The function, e.g., lambda function.
             * 
             * @pre        Check if the @p vertex exists before using this method.
             * 
             * @code{.cpp}
             *      if ( network.Graph().VertexExists( vertexId ) )
             *      {
             *          for_all_real_power_load_snapshots_at<ExecutionPolicy::sequential> (
             *              vertex,
             *              timestampPosition,
             *              []( Types::index        snapshotId
             *                , Types::loadSnapshot snapshot ) 
             *              { 
             *                  // Do something with the snapshotId and load snapshot object.
             *              }
             *          );
             *      } 
             * @endcode
             * 
             * @tparam     Policy      The execution policy, e.g., ExecutionPolicy::sequential.
             * @tparam     FUNCTION    The function object that is called for
             *     all real power load at @p timestamp at @p vertex.
             */
            template<ExecutionPolicy Policy = ExecutionPolicy::sequential, typename FUNCTION> 
            inline 
            void for_all_real_power_load_snapshots_at ( TVertex const & vertex
                                                      , Types::index    timestampPosition
                                                      , FUNCTION        function ) const 
            {
                internal::PowerGridLoopDifferentiation<TNetwork, Policy>
                    ::for_all_real_power_load_snapshots_at ( *this
                                                           , vertex
                                                           , timestampPosition
                                                           , function );
            }
        ///@}

        inline Types::count NumberOfGenerators() const 
        {
            return numberOfGenerators_;
        }

        inline Types::count NumberOfLoads() const
        {
            return numberOfLoads_;
        }

        inline Types::count NumberOfTimestamps() const
        {
            return timestamps_.size();
        }

    private:
#pragma mark FRIENDS
        friend internal::PowerGridLoopDifferentiation<TNetwork, ExecutionPolicy::sequential>;
        friend internal::PowerGridLoopDifferentiation<TNetwork, ExecutionPolicy::breakable>;
        friend internal::PowerGridLoopDifferentiation<TNetwork, ExecutionPolicy::parallel>;

#pragma mark MEMBERS
        Types::real                                         baseMva_;                       /**< Base MVA for the power grid used for the p.u. system, e.g., 100 MW */
        TBound                                              thetaBound_;                    /**< Theta bound used to calculate the big M value */

        Types::count                                        verticesWithGeneratorCount_;    /**< Number of vertices having generators */
        Types::count                                        numberOfGenerators_;            /**< Number of generators in the power grid */
        Types::count                                        numberOfLoads_;                 /**< Number of loads in the power grid */

        std::vector< std::vector<Types::vertexId> >         generatorsAtVertex_;            /**< Mapping generator to a vertex */
        std::vector< TGeneratorProperties >                 generators_;                    /**< Vector of generator vertices */
        std::vector< bool >                                 generatorExists_;               /**< Vector that describes which generator vertices exist */
        
        std::vector< std::vector<Types::vertexId> >         loadsAtVertex_;        
        std::vector< TLoadProperties >                      loads_;                         /**< Vector of load vertices */
        std::vector< bool >                                 loadExists_;                    /**< Vector that describes which load vertices exist */

        std::vector< std::vector<Types::generatorSnapshot>> generatorRealPowerSnapshots_;   /**< Generator snapshots */
        std::vector< std::vector<Types::loadSnapshot>>      loadSnapshots_;                 /**< Load snapshots */
        std::vector< Types::timestampSnapshot >             timestamps_;                    /**< Timestamps of the snapshots */
        std::vector< Types::weightSnapshot >                snapshotWeights_;               /**< Weights for each snapshot */

        Vertices::BoundType                                 generatorBoundType_;            /**< The generator bound type. */
        Vertices::BoundType                                 loadBoundType_;                 /**< The load bound type. */

        TGraph                                              graph_;                         /**< The graph. */
};

/**
 * @brief      Switches all edges that do not belong to the subgraph.
 *
 * @details    For all edges in the subgraph set
 *             <tt> edge.Properties().Status() = false </tt> and
 *             <tt> edge.Properties().Type() = Edges::ElectricalEdgeType::standard </tt>.
 *
 *             For all other edges set
 *             <tt> edge.Properties().Status() = true </tt> and
 *             <tt> edge.Properties().Type() = Edges::ElectricalEdgeType::switched </tt>.
 *
 * @param      grid           The grid
 * @param[in]  remainingSubgraph    The subgraph whose edges are not switched.
 *
 * @tparam     PowerGridType  The type of the power grid.
 */
template<typename PowerGridType>
inline void SwitchEdges ( PowerGridType                          & grid
                        , Subgraph<typename PowerGridType::TGraph> remainingSubgraph) 
{
    using TEdge = typename PowerGridType::TGraph::TEdge;
    grid.Graph().template for_all_edges<ExecutionPolicy::sequential>(
        []( TEdge & edge )
        {
            auto & properties = edge.Properties();
            properties.Status() = false;
            properties.Type()   = Edges::ElectricalEdgeType::switched;
        }
    );

    for ( auto edgeId : remainingSubgraph.Edges() ) 
    {
        auto & properties   = grid.Graph().EdgeAt(edgeId).Properties();
        properties.Status() = true;
        properties.Type()   = Edges::ElectricalEdgeType::standard;
    }
}

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__GRAPHS__POWER_GRID_HPP

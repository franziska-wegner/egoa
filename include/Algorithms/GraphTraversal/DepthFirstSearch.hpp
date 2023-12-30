/*
 * DFS.hpp
 *
 *  Created on: Feb 17, 2019
 *      Author: Franziska Wegner
 */
#ifndef EGOA__ALGORITHMS__GRAPH_TRAVERSAL__DEPTH_FIRST_SEARCH__HPP
#define EGOA__ALGORITHMS__GRAPH_TRAVERSAL__DEPTH_FIRST_SEARCH__HPP

#include "Algorithms/GraphTraversal/Traversal.hpp"

#include "Exceptions/Assertions.hpp"

namespace egoa {

enum class DfsEdgeType {
        tree        = 0
    ,   backward    = 1
    ,   forward     = 2
    ,   cross       = 3
    ,   none        = 99
};

/**
 * @brief      Class for the Depth-First Search (DFS).
 *
 * @tparam     GraphType  The graph should at least provide the same interface
 *     as the StaticGraph.
 * @tparam     IsDirected  If @p true the graph is treated as a directed graph,
 *     if @p false the graph is treated as an undirected graph.
 */
template< typename GraphType
        , bool IsDirected    = false
        , bool Recursive     = true >
class DepthFirstSearch : public Traversal<GraphType, IsDirected> {
    public:
        using TGraph    = GraphType;
        using TVertexId = typename TGraph::TVertexId;
        using TTime     = Types::count;

        ///@name Constructors and destructor
        ///@{
#pragma mark CONSTRUCTOR_AND_DESTRUCTOR

            /**
             * @brief      Constructs a new DFS instance.
             *
             * @param      graph   The graph
             * @param[in]  source  The source
             */
            DepthFirstSearch ( TGraph const & graph
                             , TVertexId      source )
            : Traversal<TGraph, IsDirected> ( graph, source )
            , time_( 0 )
            , terminate_( false )
            , entryTime_( std::vector<TTime>( graph.NumberOfVertices(), 0 ) )
            , exitTime_(  std::vector<TTime>( graph.NumberOfVertices(), 0 ) )
            {}

            virtual ~DepthFirstSearch () {}
        ///@}

#pragma mark DEPTH_FIRST_SEARCH
        inline void Run()
        {
            // Recursive call
            auto dfs = [this] ( TVertexId source, auto const & dfs )
            {
                if ( Terminate() ) return; // Search termination

                entryTime_[source] = Time();
                ++Time();

                this->SetVertexVisitedAt( source );
                PreprocessingVertexWith ( source );

                this->breakable_for_all_edges_at ( source,
                    [source, &dfs, this]( typename GraphType::TEdge const & edge )
                    {
                        TVertexId target = edge.Other  ( source );

                        // Ignore edges that directly lead back to the parent
                        if ( this->ParentOf( source ) == target ) return true;

                        bool targetVisited = this->VisitedVertexAt( target );

                        if ( !targetVisited )
                        {
                            this->ParentOf( target ) = source;
                            dfs ( target, dfs );
                        } else /* not processed */
                        { // Cycle edge
                            ProcessingEdgeWith( source, target, edge.Identifier() );
                        }

                        PostprocessingEdgeWith( source, target, edge.Identifier() );

                        // Search termination by returning false in the breakable loop
                        bool toContinue = !this->Terminate();
                        return toContinue;
                    }
                );
                if ( Terminate() ) return; // Search termination

                exitTime_[ source ] = Time();
                ++Time();

                PostprocessingVertexWith ( source );
                this->SetVertexProcessedAt ( source );
            };

            dfs ( this->Source(), dfs );
        }

    public:
#pragma mark DFS_EDGE_TYPE
        /**
         * @brief      Determine DFS edge type.
         *
         * @param[in]  source  The source identifier.
         * @param[in]  target  The target identifier.
         *
         * @return     The DFS edge type.
         *
         * @todo Cross edge is only possible in directed case -> check for graph type
         */
        inline DfsEdgeType TypifyEdge ( TVertexId source, TVertexId target )
        {
            // Tree edge
            if ( source == this->ParentOf ( target ) )
            {
                return DfsEdgeType::tree;
            }

            // Backward edge
            if ( this->VisitedVertexAt   ( target )
                && !this->ProcessedVertexAt ( target ) )
            {
                return DfsEdgeType::backward;
            }

            // Forward edge
            if ( this->ProcessedVertexAt ( target )
                && EntryTimeAt ( target ) > EntryTimeAt ( source ) )
            {
                return DfsEdgeType::forward;
            }

            // Cross edge
            if ( this->ProcessedVertexAt ( target )
                && EntryTimeAt ( target ) < EntryTimeAt ( source ) )    return DfsEdgeType::cross;

            // None of them -> should not happening
            ESSENTIAL_ASSERT( false && "DFS edge type is none." );
        }

#pragma mark GETTER_AND_SETTER

        /**
         * @brief      Terminate the DFS
         *
         * @return     TRUE if the DFS
         */
        inline bool Terminate()    const { return terminate_; }
        inline void SetTerminate()       { terminate_ = true; }

    private:

#pragma mark TIMERS
        /**
         * @brief      Modify time counter
         *
         * @return     Current time
         */
        ///@{
            inline TTime   Time() const { return time_; }
            inline TTime & Time()       { return time_; }
        ///@}

    public:
        /**
         * @brief      { function_description }
         *
         * @param      vertex  The vertex
         *
         * @return     { description_of_the_return_value }
         */
        inline TTime EntryTimeAt ( TVertexId vertexId ) const
        {
            return entryTime_[vertexId];
        }

        /**
         * @brief      Returns the exit time of a vertex.
         *
         * @param      vertexId  The vertex identifier.
         *
         * @return     The exit time for a vertex during the DFS.
         */
        inline TTime ExitTimeAt ( TVertexId const vertexId ) const
        {
            return exitTime_[vertexId];
        }


//exact behavior of the Depth-First Search (DFS) depends on the processing methods
#pragma mark FURTHER_PROCESSING

        /**
         * @brief      Preprocessing the vertex with @p vertexId.
         *
         * @param[in]  vertexId  The vertex identifier.
         * @param[in]  function  The function object that is called for the
         *      vertexId, e.g., a lambda function.
         *
         * @tparam     FUNCTION  The function object that is called for
         *     the vertex identifiers @p vertexId.
         */
        // template<typename FUNCTION>
        virtual
        inline
        void PreprocessingVertexWith ( TVertexId vertexId
                                     // , FUNCTION  function
                                     )
        {
            // function ( vertexId );
        }

        /**
         * @brief      Post processing the vertex with @p vertexId.
         *
         * @param[in]  vertexId  The vertex identifier.
         * @param[in]  function  The function object that is called for the
         *      vertexId, e.g., a lambda function.
         *
         * @tparam     FUNCTION  The function object that is called for
         *     the vertex identifiers @p vertexId.
         */
        // template<typename FUNCTION>
        virtual
        inline
        void PostprocessingVertexWith ( TVertexId vertexId
                                      // , FUNCTION  function
                                      )
        {
            // function ( vertexId );
        }

        // template<typename FUNCTION>
        virtual
        inline
        void ProcessingEdgeWith ( TVertexId     source
                                , TVertexId     target
                                , Types::edgeId edgeId
                                // , FUNCTION      function
                                )
        {
            // function ( source, target, edgeId );
        }

        /**
         * @brief      Post processing the edge with @p edgeId.
         *
         * @param[in]  vertexId  The vertex identifier.
         * @param[in]  function  The function object that is called for the
         *      vertexId, e.g., a lambda function.
         *
         * @tparam     FUNCTION  The function object that is called for
         *     the edge identifiers @p edgeId.
         */
        // template<typename FUNCTION>
        virtual
        inline
        void PostprocessingEdgeWith ( TVertexId     source
                                    , TVertexId     target
                                    , Types::edgeId edgeId
                                    // , FUNCTION      function
                                    )
        {
            // function ( source, target, edgeId );
        }

#pragma mark MEMBERS
    private:
        TTime               time_;      /**< Current time counter */
        bool                terminate_; /**< Terminate search */

        std::vector<TTime>  entryTime_; /**< Entry time at a vertex */
        std::vector<TTime>  exitTime_;  /**< Exit time at a vertex */
}; // class DepthFirstSearch

} // namespace egoa

#endif // EGOA__ALGORITHMS__GRAPH_TRAVERSAL__DEPTH_FIRST_SEARCH__HPP

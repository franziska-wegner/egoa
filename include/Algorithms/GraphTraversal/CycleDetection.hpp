/*
 * CycleDetection.hpp
 *
 *  Created on: Feb 17, 2019
 *      Author: Franziska Wegner
 */
#ifndef EGOA__ALGORITHMS__GRAPH_TRAVERSAL__CYCLE_DETECTION__HPP
#define EGOA__ALGORITHMS__GRAPH_TRAVERSAL__CYCLE_DETECTION__HPP

#include "Algorithms/GraphTraversal/DepthFirstSearch.hpp"

namespace egoa { 

/**
 * @brief      Class to detect a cycle in the graph.
 * @details    Similar to DFS, but overriding the @p ProcessingEdgeWith
 *     method. Note that a cycle detection can only be if the target vertex
 *     was already visited, but not processed. This represent the second
 *     branch in the if condition of the @p breakable_for_all_edges_at.
 *
 * @tparam     GraphType  The graph should at least provide the same interface
 *     as the StaticGraph().
 * @tparam     IsDirected  If @p true the graph is treated as a directed graph,
 *     if @p false the graph is treated as an undirected graph.
 */
template< typename GraphType = StaticGraph<Vertices::ElectricalProperties<>,Edges::ElectricalProperties>
        , bool IsDirected    = false >
class CycleDetection final : public DFS<GraphType, IsDirected> {
    public:
#pragma mark CONSTRUCTOR_AND_DESTRUCTOR
        CycleDetection ( TGraph const & graph, TVertex source )
        : DFS ( graph, source ){}

#pragma mark FURTHER_PROCESSING
        /**
         * @brief      Detect backward edge and thus, detect the first cycle found.
         * @details    Note that the DFS algorithm processes every edge
         *     exactly once using @p breakable_for_all_edges_at. Thus, there
         *     are no spurious two-vertex cycles in undirected graphs such as
         *     paths = (u,v) and (v,u).
         *
         * @param[in]  source  The source identifier.
         * @param[in]  target  The target identifier.
         */
        virtual inline void ProcessingEdgeWith  ( TVertex const source
                                                , TVertex const target ) override
        {
            if ( source != ParentOf ( target ) ) { 
                ExtractPath ( source, target );
                SetTerminate();
            }
        }
};

#endif // EGOA__ALGORITHMS__GRAPH_TRAVERSAL__CYCLE_DETECTION__HPP

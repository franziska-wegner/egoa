/*
 * DominatingThetaPath.hpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__ALGORITHMS__PATH_FINDING__DOMINATING_THETA_PATH_HPP
#define EGOA__ALGORITHMS__PATH_FINDING__DOMINATING_THETA_PATH_HPP

#include <unordered_set>

#include "Exceptions/Assertions.hpp"

#include "DataStructures/Graphs/Vertices/ElectricalProperties.hpp"
#include "DataStructures/Graphs/Edges/ElectricalProperties.hpp"

#include "DataStructures/Networks/PowerGrid.hpp"

#include "DataStructures/Graphs/StaticGraph.hpp"
#include "DataStructures/Graphs/Subgraph.hpp"

#include "DataStructures/Labels/VoltageAngleDifferenceLabel.hpp"

#include "DataStructures/Container/Queues/Bucket.hpp"
#include "DataStructures/Container/Queues/BinaryHeap.hpp"
#include "DataStructures/Container/Queues/MappingBinaryHeap.hpp"

#include "DataStructures/Container/DominationCriterion.hpp"

#include "IO/Statistics/DtpRuntimeRow.hpp"

#include "Auxiliary/Timer.hpp"

namespace egoa {

/**
 * @brief      Class for dominating theta path.
 *
 * @todo       Usage example
 *
 * @tparam     GraphType     The graph type, e.g., StaticGraph<Vertices::ElectricalProperties, Edges::ElectricalProperties>.
 * @tparam     LabelType     The label type such as Label, SusceptanceNormLabel, and VoltageAngleDifferenceLabel.
 * @tparam     QueueType     The priority queue type such as BinaryHeap.
 * @tparam     LabelSetType  The label set type representing the bucket Bucket.
 * @tparam     Domination    The domination criterion DominationCriterion, e.g., DominationCriterion::strict.
 *
 * @see        StaticGraph
 * @see        Label, SusceptanceNormLabel, VoltageAngleDifferenceLabel
 * @see        BinaryHeap
 * @see        Bucket
 */
template < typename GraphType             = StaticGraph< Vertices::ElectricalProperties<Vertices::IeeeBusType>, Edges::ElectricalProperties >
         , typename LabelType             = VoltageAngleDifferenceLabel< typename GraphType::TEdge >
         , typename QueueType             = MappingBinaryHeap< typename GraphType::TVertexId, LabelType >
         , typename LabelSetType          = Bucket< BinaryHeap< LabelType > >
         , DominationCriterion Domination = DominationCriterion::strict >
class DominatingThetaPath final {
    public:
#pragma mark TYPE_ALIASING
        // Graph specific types
        using TGraph        = GraphType;                        /**< The graph type.  */
        using TVertex       = typename GraphType::TVertex;      /**< The vertex type. */
        using TVertexId     = typename GraphType::TVertexId;    /**< The vertex identifier type. */
        using TEdge         = typename GraphType::TEdge;        /**< The edge type. */
        using TEdgeId       = typename GraphType::TEdgeId;      /**< The edge identifier type. */
        // Label specific types
        using TLabel        = LabelType;                        /**< The label type. */
        using TQueue        = QueueType;                        /**< The priority queue type. */
        using TLabelSet     = LabelSetType;                     /**< The label set type represented by a bucket. */

    public:
        ///@name Constructors and Destructor
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS

            /**
             * @brief      Constructs the object.
             *
             * @param      graph  The graph structure.
             */
            DominatingThetaPath ( TGraph const & graph )
            : graph_( graph )
            , labelSets_( graph.NumberOfVertices(), TLabelSet() )
            , queue_( )
            {
#ifdef EGOA_ENABLE_STATISTIC_DTP // NAME OF THE PROBLEM
                dtpRuntimeRow_.NameOfProblem = "DtpStandard";
#endif
            }

            /**
             * @brief      Constructs the object.
             *
             * @param      graph   The graph structure.
             * @param[in]  source  The source's vertex identifier.
             */
            DominatingThetaPath ( TGraph const & graph
                                , TVertexId      source )
            : DominatingThetaPath ( graph )
            {
                Clear ();
                Source( source );
            }
        ///@}

        ///@name Execute the DTP Algorithm
        ///@{
#pragma mark EXECUTE_ALGORITHM

            /**
             * @brief      Run the DTP algorithm.
             */
            inline void Run () {
#ifdef EGOA_ENABLE_STATISTIC_DTP // GRAPH INFORMATION
                dtpRuntimeRow_.Name             = graph_.Name();
                dtpRuntimeRow_.NumberOfVertices = graph_.NumberOfVertices();
                dtpRuntimeRow_.NumberOfEdges    = graph_.NumberOfEdges();
#endif

                Auxiliary::Timer dtpTime;

                while ( !QueueEmpty() )
                { // Q != {}
                    TLabel const label   = QueueDeleteMinimum();
                    const TVertexId u     = label.Vertex();
                    ESSENTIAL_ASSERT ( u < graph_.NumberOfVertices() );

                    // For all incident edges
                    graph_.template for_all_edges_at<ExecutionPolicy::sequential>( u,
                        [&]( TEdge const & edge )
                        {
                            ESSENTIAL_ASSERT ( u < graph_.NumberOfVertices() );

                            TVertexId v = edge.Other(u);

                            ESSENTIAL_ASSERT ( v < graph_.NumberOfVertices() );

#ifdef EGOA_ENABLE_STATISTIC_DTP // NUMBER OF SCANNED EDGES -> TOTAL NUMBER
                            ++dtpRuntimeRow_.NumberOfScannedEdges;
#endif
                            TLabel newlabel;

                            if ( ProduceCycle( newlabel, label + edge ) ) return;
                            SetParentOf( newlabel, label );

#ifdef EGOA_ENABLE_STATISTIC_DTP // NUMBER OF EDGES NOT PRODUCING A CYCLE
                            ++dtpRuntimeRow_.NumberOfEdgesProducingNoCycle;
#endif
                            if ( ! MergeLabelAt( v, newlabel ) ) return;

#ifdef EGOA_ENABLE_STATISTIC_DTP // NUMBER OF RELAXED EDGES
                            ++dtpRuntimeRow_.NumberOfRelaxedEdges;
#endif
                            UpdateQueueWith ( newlabel );
                        }
                    );

#ifdef EGOA_ENABLE_STATISTIC_DTP // TOTAL NUMBER OF LABELS
                    dtpRuntimeRow_.GlobalElapsedMilliseconds = dtpTime.ElapsedMilliseconds();
                    dtpRuntimeRow_.NumberOfLabels            = NumberOfLabels();
#endif

#if !defined(NDEBUG) && defined(EGOA_ENABLE_STATISTIC_DTP)
                        // IO::DtpRuntimeRow::Header(std::cout);
                        // std::cout << std::endl << dtpRuntimeRow_ << std::endl;
                        std::cout << "Number of relaxed edges: " << dtpRuntimeRow_.NumberOfRelaxedEdges << std::endl;
                        std::cout << "Number of labels: " << dtpRuntimeRow_.NumberOfLabels << std::endl<< std::endl;
                        // ESSENTIAL_ASSERT ( ( 1 + dtpRuntimeRow_.NumberOfRelaxedEdges )
                        //                 == dtpRuntimeRow_.NumberOfLabels );
#endif
                }
            }
        ///@}

        ///@name Access information
        ///@{
#pragma mark ACCESS_INFORMATION

            /**
             * @brief      Extracts the subgraph formed by the DTPs from the source
             *             to the given target.
             *
             * @param[out] resultSubgraph  The resulting subgraph formed by all
             *                             DTPs from the source to the target.
             * @param[in]  target          The target vertex.
             *
             * @return     The voltage angle difference from the source to the
             *             target vertex.
             */
            inline Types::real Result(Subgraph<TGraph const> & resultSubgraph,
                                      TVertexId const target)
            {
                USAGE_ASSERT( graph_.VertexExists( target ) );

                std::vector<bool> isVertexInSubgraph(graph_.NumberOfVertices(), false);
                std::vector<bool> isEdgeInSubgraph(graph_.NumberOfEdges(), false);

                std::vector<TVertexId> vertices;
                std::vector<TEdgeId>   edges;

                Types::real result = \
                    labelSets_[target].template for_all_optima<ExecutionPolicy::sequential>(
                        [ this, &vertices, &edges, &isVertexInSubgraph, &isEdgeInSubgraph ]( TLabel const & optLabel )
                        {
                            Types::labelId  labelId  = optLabel.Index();
                            TVertexId       vertexId = optLabel.Vertex();

                            do
                            {
                                TLabel const & label = LabelAt( vertexId, labelId );
                                labelId              = label.Index();

                                ESSENTIAL_ASSERT ( graph_.VertexExists( vertexId ) );

                                if ( !isVertexInSubgraph[vertexId] )
                                {
                                    isVertexInSubgraph[vertexId] = true;
                                    vertices.push_back(vertexId);
                                }

                                if ( label.PreviousVertex() != Const::NONE )
                                { // @todo multiple edges? It would be easier if the labels stored edges
                                    Types::edgeId edge = graph_.EdgeId ( vertexId, label.PreviousVertex() );
                                    if ( edge == Const::NONE )
                                    {
                                        edge = graph_.EdgeId ( label.PreviousVertex(), vertexId );
                                        ESSENTIAL_ASSERT( edge != Const::NONE );
                                    }

                                    if (!isEdgeInSubgraph[edge])
                                    {
                                        isEdgeInSubgraph[edge] = true;
                                        edges.push_back(edge);
                                    }
                                }

                                vertexId = label.PreviousVertex();
                                labelId  = label.PreviousLabel();

                            } while ( labelId  != Const::NONE
                                   && vertexId != Const::NONE );
                        }
                    );

                resultSubgraph = Subgraph<TGraph const>(&graph_, vertices, edges);
                return result;
            }

            /**
             * @brief      Extract result graph and value.
             * @details    The path is constructed from source to sink for
             *     each label that is optimal at the target. Note that the
             *     optimality is defined by the labels in the label set.
             *
             * @param      parent  The parent pointer.
             * @param[in]  target  The target vertex t.
             *
             * @return     The optimal value.
             */
            inline Types::real Result ( std::vector<std::vector<TVertexId>> & parent
                                      , TVertexId                     const   target )
            {
                USAGE_ASSERT ( graph_.VertexExists( target ) );

                // Iterate over all optima
                Types::real result = \
                    labelSets_[target].template for_all_optima<ExecutionPolicy::sequential>([ this, & parent = parent ]( TLabel const & optLabel )
                {
                    // Add a row for another label path from target t
                    parent.emplace_back( std::vector<TVertexId>() );

                    // Define function pointer for recursive call
                    std::function<void(TLabel const &)> FindPath;

                    // Construct path from the source to the sink
                    FindPath = [this, &FindPath, & parent = parent] ( TLabel const & label )
                    {
                        if ( ( Const::NONE == label.PreviousVertex() ) )
                        {
                            parent.back().emplace_back ( label.Vertex() );
                        } else
                        {
                            TVertexId       vertexId = label.Vertex();

                            FindPath ( LabelAt( label.PreviousVertex(), label.PreviousLabel() ) );
                            parent.back().emplace_back ( vertexId );
                        }
                    };
                    FindPath( optLabel );

                }); // For all labels on the DTP at target vertex
                return result;
            }

            /**
             * @brief      Current number of labels
             *
             * @return     Total number of labels
             */
            inline Types::count NumberOfLabels ()
            {
                Types::count numberOfLabels = 0;

                for ( TLabelSet const & labelSet : labelSets_ )
                {
                    numberOfLabels += labelSet.Size();
                }
                return numberOfLabels;
            }
        ///@}

        ///@name Modifiers
        ///@{
#pragma mark MODIFIERS

            /**
             * @brief      Set the source
             *
             * @param[in]  source  The source
             */
            inline void Source ( TVertexId source )
            {
                USAGE_ASSERT ( source < labelSets_.size() );
                Clear();
#ifdef EGOA_ENABLE_STATISTIC_DTP // SOURCE ID
                dtpRuntimeRow_.SourceId     = source;
#endif
                TLabel sourceLabel          = TLabel::SourceLabel ( source );
                labelSets_[source].template Merge<Domination>( sourceLabel );
                Insert( sourceLabel );
            }

            /**
             * @brief      Clear all data structures.
             */
            inline void Clear()
            {
                labelSets_.clear();
                labelSets_.assign( graph_.NumberOfVertices(), TLabelSet() );

                queue_.Clear();
#ifdef EGOA_ENABLE_STATISTIC_DTP // CLEAR
                dtpRuntimeRow_.Clear();
#endif
            }

            /**
             * @brief      Setter for the statistic.
             *
             * @return     The current statistic representing a row.
             */
            inline IO::DtpRuntimeRow & Statistic ()
            {
                return dtpRuntimeRow_;
            }

            /**
             * @brief      Getter for the statistic.
             *
             * @return     The current statistic representing a row.
             */
            inline IO::DtpRuntimeRow const & Statistic () const
            {
                return dtpRuntimeRow_;
            }
        ///@}

        ///@name Compute Path Numbers
        ///@{
#pragma mark LABEL_OPERATIONS

            /**
             * @brief      Total number of @f$\dtp@f$ paths through a vertex.
             *
             * @param      numberOfPathsPerVertex           The total number of paths per vertex.
             * @param      relativeNumberOfPathsPerVertex   The total relative number of paths per vertex.
             */
            inline void TotalNumberOfPathsThroughVertex ( std::vector<Types::count> & numberOfPathsPerVertex
                                                        , std::vector<Types::real>  & relativeNumberOfPathsPerVertex )
            {
                graph_.template for_all_vertex_identifiers<ExecutionPolicy::sequential> ( [   this
                                                                   , & numberOfPathsPerVertex
                                                                   , & relativeNumberOfPathsPerVertex ] ( TVertexId vertexId )
                {
                    NumberOfPathsThroughVertex ( vertexId, numberOfPathsPerVertex, relativeNumberOfPathsPerVertex );
                });
            }

            /**
             * @brief      Number of @f$\dtp@f$ paths at each vertex.
             * @details    This methods counts the number of paths through a
             *     vertex. However, a label path counts only once, which is
             *     realized by the @p marked flag.
             *
             * @param[in]  target         The target for which we count the paths.
             * @param      numberOfPaths  The number of paths. (Note that this
             *     field will be resized to the number of vertices in the
             *     graph if not already done.)
             *
             * @todo    Use DAG property of label paths.
             */
            inline void NumberOfPathsThroughVertex ( TVertexId                   target
                                                   , std::vector<Types::count> & numberOfPathsPerVertex
                                                   , std::vector<Types::real>  & relativeNumberOfPathsPerVertex )
            {
                //@todo This is inefficient.
                Types::count numberOfOptimalLabels = LabelSetAt(target).Optima().size(); // Divide by this value
                Types::real weightOfPath = static_cast<Types::real>(1) / numberOfOptimalLabels;

                numberOfPathsPerVertex.resize( graph_.NumberOfVertices(), 0 );

                labelSets_[target].template for_all_optima<ExecutionPolicy::sequential> (
                    [&]( TLabel const & optLabel )
                    {
                        Types::labelId  labelId  = optLabel.Index();
                        TVertexId       vertexId = target;

                        do {
                            TLabel & label = LabelAt( vertexId, labelId );
                            labelId        = label.Index();

                            ESSENTIAL_ASSERT ( graph_.VertexExists( vertexId ) );

                            // Increase number of paths
                            ++numberOfPathsPerVertex[vertexId];
                            relativeNumberOfPathsPerVertex[vertexId] += weightOfPath;

                            // Extract next label on the DTP
                            vertexId = label.PreviousVertex();
                            labelId  = label.PreviousLabel();

                        } while ( labelId  != Const::NONE
                               && vertexId != Const::NONE );
                    }
                ); // For all labels in DTP at target vertex
            }

            /**
             * @brief      Total number of @f$\dtp@f$ paths through an edge.
             *
             * @param      numberOfPathsPerEdge          The total number of paths per edge.
             * @param      relativeNumberOfPathsPerEdge  The total relative number of paths per edge.
             */
            inline void TotalNumberOfPathsThroughEdge ( std::vector<Types::count> & numberOfPathsPerEdge
                                                      , std::vector<Types::real>  & relativeNumberOfPathsPerEdge )
            {
                graph_.template for_all_vertex_identifiers<ExecutionPolicy::sequential> ( [  this
                                                                   , & numberOfPathsPerEdge
                                                                   , & relativeNumberOfPathsPerEdge ] ( TVertexId vertexId )
                {
                    NumberOfPathsThroughEdge ( vertexId, numberOfPathsPerEdge, relativeNumberOfPathsPerEdge );
                });
            }

            /**
             * @brief      Number of @f$\dtp@f$ paths through an edge.
             * @details    Note that this should not be used for a normal
             *     Dijkstra implementation as the labels are always optimal.
             *     However, here the labels are not always possible and we do
             *     nod see a faster implementation to calculate the number of
             *     paths faster.
             *
             * @param[in]  target              The target for which we count the paths.
             * @param      numberOfPaths       The number of paths (note that this
             *     field will be resized).
             * @param      relativeNumberOfPathsPerEdge  The edge score per thread (if we
             *     run the algorithm parallel).
             *
             * @todo    Use DAG property of label paths.
             */
            inline void NumberOfPathsThroughEdge ( TVertexId                   target
                                                 , std::vector<Types::count> & numberOfPathsPerEdge
                                                 , std::vector<Types::real>  & relativeNumberOfPathsPerEdge )
            {
                //@todo This is inefficient.
                Types::count numberOfOptimalLabels = LabelSetAt(target).Optima().size(); // Divide by this value
                Types::real weightOfPath = static_cast<Types::real>(1) / numberOfOptimalLabels;

                labelSets_[target].template for_all_optima<ExecutionPolicy::sequential>( 
                    [&]( TLabel const & optLabel )
                    {
                        Types::labelId  labelId  = optLabel.Index();
                        TVertexId       vertexId = target;

                        do {
                            TLabel & label = LabelAt( vertexId, labelId );
                            labelId        = label.Index();

                            if (   ( label.PreviousLabel()  == Const::NONE )
                                || ( label.PreviousVertex() == Const::NONE )
                                || ( vertexId == Const::NONE )
                               ) break; // Label is already on path

                            // Increase number of paths at "edgeId"
                            TEdgeId edgeId = ( graph_.EdgeId( label.PreviousVertex(), vertexId ) != Const::NONE )
                                                    ? graph_.EdgeId( label.PreviousVertex(), vertexId )
                                                    : graph_.EdgeId( vertexId, label.PreviousVertex() );

                            ESSENTIAL_ASSERT ( edgeId != Const::NONE );

                            ++numberOfPathsPerEdge[edgeId];

                            relativeNumberOfPathsPerEdge[edgeId] += weightOfPath;

                            // Extract next label on the DTP
                            vertexId = label.PreviousVertex();
                            labelId  = label.PreviousLabel();

                        } while ( labelId  != Const::NONE
                               && vertexId != Const::NONE );
                    }
                ); // For all labels in DTP at target vertex
            }
        ///@}

    private:
        ///@name Accessors
        ///@{
#pragma mark ACCESSORS

            /**
             * @brief      Access vertex identifier of a label.
             *
             * @param      label  The label
             *
             * @return     The vertex identifier.
             */
            inline TVertexId VertexIdOf ( TLabel const & label ) const
            {
                USAGE_ASSERT ( !label.Empty() );
                return label.Vertex();
            }

            /**
             * @brief      Getter for the set of labels @f$\labels(\vertex)@f$ of a vertex @f$\vertex@f$.
             *
             * @param[in]  vertexId  The vertex identifier.
             *
             * @return     The set of labels @f$\labels(\vertex)@f$ for the @p vertex.
             */
            inline TLabelSet const & LabelSetAt ( TVertexId const vertexId ) const
            {
                USAGE_ASSERT ( vertexId < labelSets_.size() );
                return labelSets_[vertexId];
            }

            /**
             * @brief      Setter for the set of labels @f$\labels(\vertex)@f$
             *     of a vertex @f$\vertex@f$.
             *
             * @param[in]  vertexId  The vertex identifier.
             *
             * @return     The set of labels @f$\labels(\vertex)@f$ for the @p
             *     vertex.
             */
            inline TLabelSet & LabelSetAt ( TVertexId const vertexId )
            {
                USAGE_ASSERT ( vertexId < labelSets_.size() );
                return labelSets_[vertexId];
            }

            /**
             * @brief      The label @f$\labelu@f$ at a vertex @f$\vertex@f$
             *     with @p vertexId and the label's identifier @p labelId.
             *
             * @param[in]  vertexId  The vertex identifier of vertex @f$\vertex@f$.
             * @param[in]  labelId   The label identifier of label @f$\labelu@f$.
             *
             * @return     The label @f$\labelu@f$.
             */
            inline TLabel & LabelAt ( TVertexId       const vertexId
                                    , Types::labelId  const labelId )
            {
                USAGE_ASSERT ( vertexId < labelSets_.size() );
                USAGE_ASSERT ( labelId  < Const::NONE );

                return labelSets_[vertexId].ElementAt ( labelId );
            }
        ///@}

        ///@name Label Set L(v) and Queue Q Operators
        ///@{
#pragma mark LABEL_SET_AND_QUEUE_OPERATIONS

            /**
             * @brief      Check if the main queue is empty.
             *
             * @return     @p True if the main queue is empty, @p False otherwise.
             */
            inline bool QueueEmpty() const
            {
                return queue_.Empty();
            }

            /**
             * @brief      Adds a label to the main queue.
             *
             * @pre        A precondition to that method is that the label set of
             *     the label's @p label vertex was updated. Thus, this method
             *     should only be called by #UpdateLabelSet() or #UpdateLabelSetAt().
             *
             * @param      label  The label.
             */
            inline void Insert( TLabel const & label )
            {
                queue_.Emplace( label.Vertex(), label );
            }

            /**
             * @brief      Update queue with new label @f$\labelu_{\mathrm{new}}@f$.
             * @details    If there is no label of the label's vertex the
             *     label will be added to the queue. However, if the new label
             *     @f$\labelu_{\mathrm{new}}@f$ is better than the existing
             *     one the key is changed to the new label
             *     @f$\labelu_{\mathrm{new}}@f$. Otherwise, nothing is
             *     happening.
             *
             * @param      newLabel  The new label @f$\labelu_{\mathrm{new}}@f$.
             */
            inline void UpdateQueueWith ( TLabel const & newLabel )
            {
                if ( !queue_.HasKeyOf ( newLabel.Vertex() ) )
                { // There is no label of vertex v in the queue
                    Insert ( newLabel );
                } else if ( queue_.KeyOf( newLabel.Vertex() ) > newLabel )
                { // The new label is better than the existing one
                    queue_.ChangeKey ( newLabel.Vertex(), newLabel );
                }
            }

            /**
             * @brief      Delete the minimum key from the queue @f$\queue@f$.
             * @details    Remove the top element of the queue and push the top
             *     element of the same bucket to the queue (forward top element to
             *     the main queue).
             *
             * @return     Label that has the minimum key
             *
             * @see TQueue
             */
            inline TLabel QueueDeleteMinimum ()
            {
                USAGE_ASSERT ( !queue_.Empty() );

                TVertexId vertexId;
                TLabel    label;

                std::tie ( vertexId, label ) = queue_.DeleteTop();

                ESSENTIAL_ASSERT ( !LabelSetEmptyAt(vertexId) );
                label.Index() = UpdateLabelSetAt ( vertexId );

                return label;
            }

            /**
             * @brief      Check if a label set @f$\labels(\vertex)@f$ is
             *     empty at vertex @f$\vertex@f$.
             *
             * @param[in]  vertexId  The vertex identifier of vertex @f$\vertex@f$.
             *
             * @return     @p True if the label set is empty, @p False otherwise.
             */
            inline bool LabelSetEmptyAt( TVertexId const vertexId ) const
            {
                USAGE_ASSERT ( vertexId < labelSets_.size() );
                return labelSets_[vertexId].EmptyQueue();
            }

            /**
             * @brief      Check if a label set @f$\labels(\vertex)@f$ is
             *     empty at vertex @f$\vertex@f$.
             *
             * @param      label  The label @f$\labelu@f$.
             *
             * @return     @p True if the label set @f$\labels(\vertex)@f$ is
             *     empty, @p False otherwise.
             */
            inline bool LabelSetEmptyAt( TLabel const & label )  const
            {
                USAGE_ASSERT ( !label.Empty() );
                return LabelSetEmptyAt( VertexIdOf ( label ) );
            }

            /**
             * @brief      Update a label set @f$\labels(\vertex)@f$ at a vertex @f$\vertex@f$.
             * @details    Remove a label @f$\labelu@f$ associated with a
             *     vertex @f$\vertex@f$ from the queue has to trigger an
             *     update (#labelSet.Pop()) of the label set
             *     @f$\labels(\vertex)@f$ at a vertex
             *     @f$\vertex@f$.
             *
             * @pre        As a precondition #QueueDeleteMinimum() has to be
             *     called.
             *
             * @param      labelSet  The label set @f$\labels(\vertex)@f$ at a
             *     vertex @f$\vertex@f$.
             */
            inline Types::labelId UpdateLabelSet ( TLabelSet & labelSet )
            {
                USAGE_ASSERT ( !labelSet.Empty() );

                Types::labelId labelId = labelSet.Pop();

                if ( ! labelSet.EmptyQueue() ) {
                    Insert ( labelSet.Top() );
                }

                return labelId;
            }

            /**
             * @brief      Update a label set at a vertex.
             * @details    Removing a label @f$\labelu@f$ associated with a
             *     vertex @f$\vertex@f$ from the queue has to trigger an
             *     update (#labelSet.Pop()) of the label bucket at vertex
             *     @f$\vertex@f$.
             *
             * @pre        As a precondition #QueueDeleteMinimum() has do be
             *     called.
             *
             * @param[in]  vertexId  The vertex identifier of vertex @f$\vertex@f$.
             *
             * @see        DominatingThetaPath#UpdateBucket
             */
            inline Types::labelId UpdateLabelSetAt ( TVertexId vertexId )
            {
                USAGE_ASSERT   ( vertexId < labelSets_.size() );
                return UpdateLabelSet ( labelSets_[vertexId] );
            }
        ///@}

        ///@name Label operations
        ///@{
#pragma mark LABEL_OPERATIONS

            /**
             * @brief      Sets the parent of @p label @f$\labelu@f$ to @p
             *     previousLabel @f$\labelu_{p}@f$.
             *
             * @param      label          The current label @f$\labelu@f$.
             * @param      previousLabel  The previous label @f$\labelu_p@f$
             */
            inline void SetParentOf ( TLabel       &  label
                                    , TLabel const &  previousLabel )
            {
                label.PreviousVertex() = previousLabel.Vertex();
                label.PreviousLabel()  = previousLabel.Index();
            }

            /**
             * @brief      Merge @p label @f$\labelu@f$ with the set of labels.
             *     @f$\labels(\vertex)@f$ at @p vertex @f$\vertex@f$.
             * @details    Checks if the new label
             *     @f$\labelu_{\mathrm{new}}@f$ is dominated by any label in
             *     @f$\labels(\vertex)@f$ and delete dominated labels. If
             *     @f$\labelu_{\mathrm{new}}@f$ is dominated by another label
             *     it is marked as invalid.
             *
             * @param[in]  vertexId     The vertex @f$\vertex@f$ with set of
             * labels @f$\labels(\vertex)@f$.
             * @param      labelStruct  The label that should be merged into
             *     the set of labels @f$\labels(\vertex)@f$.
             *
             * @return     @p True if the merging was successful, @p False otherwise.
             */
            inline bool MergeLabelAt( TVertexId vertexId
                                    , TLabel  & label )
            {
                return labelSets_[vertexId].template Merge<Domination>( label );
            }

            /**
             * @brief      Check if the new label @f$\labelu_{\mathrm{new}}@f$ produces a cycle.
             * @details    The term std::get<1>(pair) just says if the vertex
             *     could be inserted into the set of vertices. If @p True it does not
             *     produce a cycle, otherwise (meaning @p False) it produces a cycle.
             *     The latter means that the vertex was already in the set of
             *     vertices. Thus, the term (meaning std::get<1>(pair)) is
             *     negated.
             *
             * @param      label  The new label @f$\labelu_{\mathrm{new}}@f$.
             * @param      pair   The pair should be used with "label + edge" or "edge + label".
             *
             * @return     @p True if the new label produces a cycle, @p False otherwise.
             */
            inline bool ProduceCycle ( TLabel                  &  label
                                     , std::pair<TLabel, bool> && pair )
            {
                label = std::get<0>(pair);
                return  !( std::get<1>(pair) );
            }
        ///@}

#pragma mark MEMBERS
    private:
        TGraph            const & graph_;           /**< The graph @f$\graph = (\vertices,\edges)@f$ on which the DTP is calculated. */
        std::vector<TLabelSet>    labelSets_;       /**< At each vertex @f$\vertex\in\vertices@f$ there is a set of labels @f$\labels(\vertex)@f$. */
        TQueue                    queue_;           /**< The priority queue @f$\queue@f$. */

        IO::DtpRuntimeRow         dtpRuntimeRow_;   /**< To measure quality and time information. */
};

} // egoa

#endif // EGOA__ALGORITHMS__PATH_FINDING__DOMINATING_THETA_PATH_HPP

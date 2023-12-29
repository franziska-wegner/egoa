/*
 * Label.hpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__LABELS__LABEL_HPP
#define EGOA__DATA_STRUCTURES__LABELS__LABEL_HPP

#include <unordered_set>

#include "Auxiliary/Auxiliary.hpp"
#include "DataStructures/Graphs/Edges/Edge.hpp"
#include "DataStructures/Graphs/Edges/ElectricalProperties.hpp"

namespace egoa {

/**
 * @brief      Interface for label.
 * @details    This class represents an interface that has to implemented by
 *     all labels.
 *
 * @tparam     ElementType         Some element type, e.g., an electrical edge.
 * @tparam     VertexSetContainer  Container, e.g., unordered set to extract vertex conflicts, loops.
 * @tparam     PointerType         E.g., Types::vertexId.
 *
 * @see        Edge::ElectricalEdge representing an ElementType interface.
 * @see        BucketElement representing an minimum interface requirement for a bucket.
 */
template< typename ElementType          = Edges::Edge<Edges::ElectricalProperties>
        , typename VertexSetContainer   = std::unordered_set<Types::vertexId>
        , typename PointerType          = Types::vertexId >
class Label {
    public:
        // Type aliasing
        using TVertexId = Types::vertexId;      /**< The vertex identifier type used in LabelStruct. */

        using TElement  = ElementType;          /**< Some element to cover such as an edge. */
        using TVertexSet= VertexSetContainer;   /**< A hash map of TVertex. */

        using TPointer  = PointerType;

        using TLabel    = Label<TElement,TVertexSet, TPointer>;   /**< The label's own type. */

    public:
        ///@name Constructors and Destructor
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS

            /**
             * @brief      Constructs the label object.
             * @details    The label identifier and previous label/vertex
             *     identifiers are set to @p Const::NONE. The valid flag is
             *     set to @p True.
             *
             * @param[in]  vertexId  The vertex identifier.
             */
            Label( Types::vertexId vertexId )
            : index_(Const::NONE)
            , vertexId_(vertexId)
            , valid_(true)
            // , marked_(false)
            , previousVertexId_(Const::NONE)
            , previousLabelId_(Const::NONE)
            {}

            /**
             * @brief      Copy constructor.
             * @details    Constructs the label object by using the values of
             *     the other label.
             *
             * @param      label  The label.
             *
             */
            Label ( Label const & label ) = default;

            /**
             * @brief      Destroys the label object.
             */
            ~Label() {}
        ///@}

        ///@name Domination Operators
        ///@{
#pragma mark DOMINATION_OPERATORS
            // inline bool operator< ( Label const & rhs ) const { return true; }
            // inline bool operator<=( Label const & rhs ) const { return true; }
            // inline bool operator> ( Label const & rhs ) const { return true; }
            // inline bool operator>=( Label const & rhs ) const { return true; }
        ///@}

        ///@name Comparison Operators
        ///@{
#pragma mark COMPARISON_OPERATORS
            // inline bool operator==( Label const & rhs ) const { return true; }
            // inline bool operator!=( Label const & rhs ) const { return true; }
        ///@}

        ///@name Concatenation Operators
        ///@{
#pragma mark CONCATENATION_OPERATORS

            /**
             * @brief      In place addition.
             *
             * @param      rhs   The right hand side.
             *
             * @return     Label with added TElement.
             */
            // inline Label & operator+=( TElement const & rhs ) {}

            // inline Label   operator+ ( TElement const & rhs ) const {};

        ///@}

        ///@name Getter and Setter
        ///@{
#pragma mark GETTER_AND_SETTER

            /**
             * @brief      Getter for the label identifier.
             * @details    This identifier represents the label's position,
             *     e.g., within the buckets processed elements.
             * @todo For the vertices and edges the equivalent function is called Identifier(),
             *       which is more in line with the nomenclature in the comments.
             *       However, the paramters are usually called @p index.
             *
             * @return     The label's identifier.
             */
            inline Types::labelId Index () const
            {
                return index_;
            }

            /**
             * @brief      Setter for the label identifier.
             * @details    This identifier is set while the label is moved to
             *     the processed elements in the bucket. Thus, the element
             *     will be fixed to this position.
             *
             * @code
             *      this->Index() = 9;
             * @endcode
             *
             * @return     The label's identifier.
             */
            inline Types::labelId & Index ()
            {
                return index_;
            }

            /**
             * @brief      Getter for the valid flag.
             *
             * @return     @p True if the label is valid, @p False otherwise.
             */
            inline bool Valid () const
            {
                return valid_;
            }

            /**
             * @brief      Setter for the valid flag.
             *
             * @code
             *      this->Valid() = false;
             * @endcode
             *
             * @return     @p True if the label is valid, @p False otherwise.
             */
            inline bool & Valid()
            {
                return valid_;
            }

            /**
             * @brief      Getter for the value of the label.
             * @details    Represents the total value of the label. This is
             *     comparable with an objective value.
             *
             * @return     The value of the label.
             */
            // inline Types::real Value() const {}

            /**
             * @brief      Getter for the vertex identifier.
             *
             * @return     Vertex identifier.
             */
            inline Types::vertexId Vertex() const
            {
                return vertexId_;
            }

            /**
             * @brief      Setter for the vertex identifier.
             *
             * @code
             *      this->Vertex() = 42;
             * @endcode
             *
             * @return     Vertex identifier.
             */
            inline Types::vertexId & Vertex()
            {
                return vertexId_;
            }

            /**
             * @brief      Getter for the previous vertex.
             *
             * @return     Identifier of the previous vertex.
             */
            inline TPointer PreviousVertex() const
            {
                return previousVertexId_;
            }

            /**
             * @brief      Setter for the previous vertex.
             *
             * @code
             *      this->PreviousVertex() = 41;
             * @endcode
             *
             * @return     Identifier of the previous vertex.
             */
            inline TPointer & PreviousVertex()
            {
                return previousVertexId_;
            }

            /**
             * @brief      Getter and setter for the previous label.
             *
             * @return     Identifier of the previous label.
             */
            inline TPointer PreviousLabel() const
            {
                return previousLabelId_;
            }

            /**
             * @brief      Setter for the previous label.
             * @todo       It seems to be strange to call this a setter because
             *             it can also be used to "get" the value, e.g., the following
             *             code calls this member function but does not change the value:
             *             @code
             *             Label<T> label = ...;
             *             Types::labelId id = label.PreviousLabel():
             *             @endcodee
             *             This applies to all other "getters" and "setters".
             *
             * @code
             *      this->PreviousLabel() = 2;
             * @endcode
             *
             * @return     Identifier of the previous label.
             */
            inline TPointer  & PreviousLabel()
            {
                return previousLabelId_;
            }
        ///@}

#pragma mark OUTPUT
        /**
         * @brief      Output stream.
         *
         * @param      os    The output stream such as std::cout.
         * @param      rhs   The right hand side Label.
         *
         * @return     The output stream.
         */
        friend std::ostream & operator<< ( std::ostream & os
                                         , Label const & rhs )
        {
            return os << "(" << rhs.Value() << "," << rhs.Valid() << ")";
        }

#pragma mark MEMBERS
    private:
        Types::labelId  index_;             /**< The identifier of the label that is bucket dependent. */
        Types::vertexId vertexId_;          /**< The identifier of the vertex to which the label belongs. */

        bool            valid_;             /**< The valid flag that is @p True if the label is valid, @p False otherwise. */

        TPointer        previousVertexId_;  /**< The identifier of the previous vertex. */
        TPointer        previousLabelId_;   /**< The identifier of the previous label. */

};

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__LABELS__LABEL_HPP

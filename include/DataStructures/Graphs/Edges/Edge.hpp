/* 
 * Edge.hpp
 *
 *  Created on: Mar 8, 2019
 *      Author: Matthias Wolf
 */

#ifndef EGOA__DATA_STRUCTURES__EDGES__EDGE_HPP
#define EGOA__DATA_STRUCTURES__EDGES__EDGE_HPP

#include "Auxiliary/Types.hpp"
#include "Auxiliary/Constants.hpp"

namespace egoa {
    template<typename, typename>
    class DynamicGraph;
}

namespace egoa::Edges {

/**
 * @brief      Class for edge.
 *
 * @tparam     PropertiesType  The type of the edge's properties.
 */
template<typename PropertiesType>
class Edge {
    public:
        using TProperties = PropertiesType;

        /**@name Constructors and Destructor */
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS

            Edge(Types::edgeId identifier,
                 Types::vertexId source,
                 Types::vertexId target,
                 TProperties properties)
            : identifier_(identifier),
              source_(source),
              target_(target),
              properties_(std::move(properties)) {
            }
        ///@}

        /**@name Getter and setter */
        ///@{
#pragma mark GETTER_AND_SETTER
            inline Types::index      Identifier()   const { return identifier_; }
            inline Types::vertexId   Source()       const { return source_; }
            inline Types::vertexId   Target()       const { return target_; }

            inline TProperties       & Properties()       { return properties_; }
            inline TProperties const & Properties() const { return properties_; }
        ///@}

        /**
         * @brief      Return the adjacent vertex to @p vertexId.
         *
         * @param[in]  vertexId  The vertex identifier.
         *
         * @return     The vertex identifier of the adjacent vertex.
         */
        inline Types::vertexId Other( Types::vertexId vertexId ) const 
        { 
            return ( Source() == vertexId )?Target():Source(); 
        }

        /**
         * @brief      Swap two edges.
         *
         * @param      lhs   The left hand side.
         * @param      rhs   The right hand side.
         */
        friend void swap( Edge & lhs, Edge & rhs )
        {
            using std::swap;
            swap( lhs.Identifier(), rhs.Identifier() );
            swap( lhs.Source(),     rhs.Source() );
            swap( lhs.Target(),     lhs.Target() );
            swap( lhs.Properties(), rhs.Properties() );
        }

        ///@name Comparators
        ///@{
#pragma mark COMPARATORS
            /**
             * @brief      Comparator
             *
             * @param      lhs   The left edge.
             * @param      rhs   The right edge.
             *
             * @return     @p true if the edges are the same, @p false otherwise.
             */
            friend bool operator==(Edge const & lhs, Edge const & rhs) 
            {
                return ( lhs.Identifier() == rhs.Identifier() ) 
                    && ( lhs.Source()     == rhs.Source()     )
                    && ( lhs.Target()     == rhs.Target()     )
                    && ( lhs.Properties() == rhs.Properties() );
            }

            /**
             * @brief      Comparator
             *
             * @param      lhs   The left edge.
             * @param      rhs   The right edge.
             *
             * @return     @p false if the edges are the same, @p true otherwise.
             */
            friend bool operator!=(Edge const & lhs, Edge const & rhs) 
            {
                return !(lhs == rhs);
            }
        ///@}

    private:
        template<typename,typename> friend class egoa::DynamicGraph;

        ///@name Member
        ///@{
#pragma mark MEMBER
            Types::edgeId   identifier_;    /**< Unique identifier of the vertex. */
            Types::vertexId source_;        /**< The source vertex. */
            Types::vertexId target_;        /**< The target vertex. */
            TProperties     properties_;    /**< Property of the vertex.  */
        ///@}
};

} // namespace egoa::Edges

#endif // EGOA__DATA_STRUCTURES__EDGES__EDGE_HPP
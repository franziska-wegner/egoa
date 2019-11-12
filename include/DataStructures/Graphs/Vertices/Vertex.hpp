/*
 * Vertex.hpp
 *
 *  Created on: Sep 06, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__GRAPHS__VERTICES__VERTEX_HPP
#define EGOA__DATA_STRUCTURES__GRAPHS__VERTICES__VERTEX_HPP

#include "Type.hpp"

namespace egoa {
    template<typename, typename>
    class DynamicGraph;
}

namespace egoa::Vertices {

/**
 * @brief      Class for a vertex.
 *
 * @tparam     PropertyType  The property of a vertex, e.g.,
 *     ElectricalProperties, specialize the vertex.
 * 
 * @see        egoa::Vertices::ElectricalProperties
 */
template<class PropertyType>
class Vertex {

    public:
        // Template type aliasing
        using TProperties = PropertyType;   /**< The type of the properties. */

    public:
        /**@name Constructors and Destructor */
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS

            /**
             * @brief      Constructs the vertex object.
             *
             * @param[in]  identifier  The identifier of the vertex.
             * @param[in]  properties  The properties object of the vertex.
             */
            Vertex ( Types::vertexId identifier, TProperties properties )
            : identifier_(identifier)
            , properties_(properties)
            {}
        ///@}

        /**
         * @brief      Swapping the members of two Vertex.
         *
         * @param      lhs   The left vertex.
         * @param      rhs   The right vertex.
         */
        friend void swap ( Vertex & lhs, Vertex & rhs ) 
        { // Necessary for the copy and swap idiom
            using std::swap; // enable ADL
            swap( lhs.identifier_, rhs.identifier_ );
            swap( lhs.properties_, rhs.properties_ );
        }

        ///@name Comparators
        ///@{
#pragma mark COMPARATORS
        
            /**
             * @brief      Comparator
             *
             * @param      lhs   The left vertex.
             * @param      rhs   The right vertex.
             *
             * @return     @p true if the vertex are the same, @p false otherwise.
             */
            friend bool operator==( Vertex const & lhs, Vertex const & rhs ) 
            {
                return ( lhs.Identifier() == rhs.Identifier() )
                    && ( lhs.Properties() == rhs.Properties() );
            }

            /**
             * @brief      Comparator
             *
             * @param      lhs   The left vertex.
             * @param      rhs   The right vertex.
             *
             * @return     @p false if the vertices are the same, @p true otherwise.
             */
            friend bool operator!=( Vertex const & lhs, Vertex const & rhs ) 
            {
                return !(lhs == rhs);
            }
        ///@}

        /**@name Getter and setter */
        //@{
#pragma mark SETTER_AND_GETTER
            inline Types::vertexId   Identifier()   const { return identifier_; }

            inline TProperties       & Properties()       { return properties_; }
            inline TProperties const & Properties() const { return properties_; }
        //@}

    private:
        template<typename, typename> friend class egoa::DynamicGraph;   /**< The DynamicGraph class can access private members. */

#pragma mark MEMBER
        Types::vertexId         identifier_;    /**< Unique identifier of the vertex. */
        TProperties             properties_;    /**< Property of the vertex.  */
       
};

} // namespace egoa::Vertices

#endif // EGOA__DATA_STRUCTURES__GRAPHS__VERTICES__VERTEX_HPP

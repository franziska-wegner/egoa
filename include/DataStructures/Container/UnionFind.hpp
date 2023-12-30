/*
 * UnionFind.hpp
 *
 *  Created on: Nov 20, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__CONTAINER__UNION_FIND_HPP
#define EGOA__CONTAINER__UNION_FIND_HPP

#include "Auxiliary/Auxiliary.hpp"
#include "Exceptions/Assertions.hpp"

namespace egoa {

/**
 * @brief      This class describes an union find.
 */
class UnionFind {
    public:
        UnionFind( Types::count numberOfVertices )
        : parent_( numberOfVertices, 0 )
        , numberOfVerticesInSubtree_( numberOfVertices, 1 )
        , numberOfVertices_( numberOfVertices )
        {
            // Every vertex has itself as parent
            for ( Types::count counter = 0
                ; counter < NumberOfVertices()
                ; ++counter )
            {
                Parent ( counter ) = counter;
            }
        }

        /**
         * @brief      Find the root of the vertex
         * @detail     Find the tree root of element @p vertex and return the
         *     root's identifier.
         *
         * @param[in]  vertex  The vertex identifier.
         *
         * @return     The root's identifier.
         */
        inline Types::vertexId Find ( Types::vertexId vertex )
        {
            if ( Parent(vertex) == vertex ) return vertex;
            else return Find ( Parent(vertex) );
        }

        /**
         * @brief      Merges the two subtrees---if exist---of both components
         *     together.
         *
         * @param[in]  u     The vertex u
         * @param[in]  v     The vertex v
         */
        inline void Union ( Types::vertexId u, Types::vertexId v )
        {
            Types::vertexId root1 = Find(u);
            Types::vertexId root2 = Find(v);

            if ( root1 == root2 ) return;

            if ( SubtreeSize(root1) > SubtreeSize(root2) )
            {
                SubtreeSize(root1) += SubtreeSize(root2);
                Parent(root2)       = root1;
            } else {
                SubtreeSize(root2) += SubtreeSize(root1);
                Parent(root1)       = root2;
            }
        }

        /**
         * @brief      Are both vertices in the same component
         *
         * @param[in]  u     The vertex u.
         * @param[in]  v     The vertex v.
         *
         * @return     If they are in the same component
         */
        inline bool InSameComponent ( Types::vertexId u, Types::vertexId v )
        {
            return Find(u) == Find(v);
        }

        ///@Name Getter and setter
        ///@{
            inline Types::count NumberOfVertices()
            {
                return numberOfVertices_;
            }

            inline Types::vertexId & Parent ( Types::vertexId vertex )
            {
                USAGE_ASSERT ( vertex < numberOfVertices_
                            || vertex == Const::NONE );
                return parent_[vertex];
            }

            inline Types::vertexId Parent ( Types::vertexId vertex ) const
            {
                USAGE_ASSERT ( vertex < numberOfVertices_
                            || vertex == Const::NONE );
                return parent_[vertex];
            }

            inline Types::count & SubtreeSize ( Types::vertexId vertex )
            {
                USAGE_ASSERT ( vertex < numberOfVertices_ );
                return numberOfVerticesInSubtree_[vertex];
            }

            inline Types::count SubtreeSize ( Types::vertexId vertex ) const
            {
                USAGE_ASSERT ( vertex < numberOfVertices_ );
                return numberOfVerticesInSubtree_[vertex];
            }
        ///@}

    private:
        std::vector<Types::vertexId>    parent_;                       /*< Parent pointer */
        std::vector<Types::count>       numberOfVerticesInSubtree_;    /*< Number of vertices in subtree i */
        Types::count                    numberOfVertices_;             /*< Number of vertices */
};

} // namespace egoa

#endif // EGOA__CONTAINER__UNION_FIND_HPP

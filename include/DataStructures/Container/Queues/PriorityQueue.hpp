/*
 * PriorityQueue.hpp
 *
 *  Created on: Jan 28, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__CONTAINER__PRIORITY_QUEUE_HPP
#define EGOA__DATA_STRUCTURES__CONTAINER__PRIORITY_QUEUE_HPP

#include <queue>
#include "Queue.hpp"
#include "Auxiliary/Auxiliary.hpp"

namespace egoa {

template<typename Type>
class PriorityQueue : public Queue<Type> {
    // Type aliasing
    using TElement = Type;

    public:
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS
        PriorityQueue(){}

        template<typename Compare, class Container>
        PriorityQueue ( Compare const & compare ) {}

        template<class Container>
        PriorityQueue ( Container const & container ) {}

        template<typename Compare, class Container>
        PriorityQueue ( Compare const & compare
                      , Container const & container ) {}

        virtual ~PriorityQueue() override {}

#pragma mark LOOPS
        template<bool IsParallel, typename FUNCTION>
        inline void for_all_elements ( FUNCTION function ) {}

        template<bool IsParallel, typename FUNCTION>
        inline void for_all_elements ( FUNCTION function ) const {}

        template<typename FUNCTION>
        inline void breakable_for_all_elements ( FUNCTION function ) {}

        template<typename FUNCTION>
        inline void breakable_for_all_elements ( FUNCTION function ) const {}

#pragma mark ELEMENT_ACCESS
        ///@Name Element Access
        ///@{
            virtual inline TElement const & Top () const override = 0;
        ///@}

        ///@Name Modifiers
        ///@{
            virtual inline void BuildWith( std::vector<TElement> const & elements ) = 0;

#pragma mark ADD_ELEMENTS
            virtual inline void     Push ( TElement const &  value )     override = 0;
            virtual inline void     Push ( TElement && value )           override = 0;
#pragma mark MODIFIERS
            virtual inline void     Pop ()                               override = 0;
            virtual inline TElement DeleteMin ()                         override = 0;
            virtual inline void     Clear ()                             override = 0;

            virtual inline void     ChangeKey ( Types::index            index
                                              , TElement        const & element ) = 0;
            virtual inline void     DecreaseKey ( Types::index          index
                                                , TElement      const & element ) = 0;
        ///@}

#pragma mark CAPACITY
        ///@Name Capacity
        ///@{
            virtual inline bool         Empty () const override = 0;
            virtual inline Types::count Size  () const override = 0;
        ///@}
};

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__CONTAINER__PRIORITY_QUEUE_HPP

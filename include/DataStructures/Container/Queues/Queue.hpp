/*
 * Queue.hpp
 *
 *  Created on: Nov 18, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__CONTAINER__QUEUE__QUEUE_HPP
#define EGOA__DATA_STRUCTURES__CONTAINER__QUEUE__QUEUE_HPP

#include "Auxiliary/Types.hpp"

namespace egoa {

template<typename Type>
class Queue {
    using TElement = Type;
    public:
//@todo is Compare necessary? For PQ okay but standard queue?
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS
        Queue(){}

        template<typename Compare, class Container>
        Queue ( Compare const & compare ){}

        template<class Container>
        Queue ( Container const & container ){}

        template<typename Compare, class Container>
        Queue ( Compare const & compare, Container const & container ){}

        virtual ~Queue() {}

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
            virtual inline TElement const & Top () const = 0;
        ///@}

        ///@Name Modifiers
        ///@{
#pragma mark ADD_ELEMENTS
            virtual inline void     Push ( TElement const &  element ) = 0;
            virtual inline void     Push ( TElement       && element ) = 0;
#pragma mark MODIFIERS
            virtual inline void     Pop ()                             = 0;
            virtual inline void     Clear ()                           = 0;
            inline void             Swap ( Queue & rhs)                {};
        ///@}

#pragma mark CAPACITY
        ///@Name Capacity
        ///@{
            virtual inline bool         Empty () const = 0;
            virtual inline Types::count Size  () const = 0;
        ///@}
};

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__CONTAINER__QUEUE__QUEUE_HPP

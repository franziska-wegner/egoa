/*
 * StdQueue.hpp
 *
 *  Created on: Feb 17, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURES__CONTAINER__QUEUE__STD_FIFO_QUEUE_HPP
#define EGOA__DATA_STRUCTURES__CONTAINER__QUEUE__STD_FIFO_QUEUE_HPP

#include <queue>

#include "Auxiliary/Types.hpp"
#include "Exceptions/Assertions.hpp"

namespace egoa {

//@todo Emplace, Comments
// this queue does not implement loops
template<typename ElementType>
class StdQueue {
    public:
        // Type aliasing
        using TElement = ElementType;
    public:
#pragma mark CONSTRUCTORS_AND_DESTRUCTORS

        StdQueue ()
        : queue_(){}

        virtual ~StdQueue() {}

#pragma mark ELEMENT_ACCESS
        ///@Name Element Access
        ///@{
            virtual inline TElement const & Top () const {
                USAGE_ASSERT ( Size() > 0 );
                return queue_.front();
            }
        ///@}

        ///@Name Modifiers
        ///@{
#pragma mark ADD_ELEMENTS
            virtual inline void Push ( TElement const &  element ) {
                queue_.push ( element );
            }

            virtual inline void Push ( TElement       && element ) {
                queue_.push ( element );
            }

            //@todo
            virtual inline void Emplace ( TElement const &  element ) {
                queue_.emplace ( element );
            }
#pragma mark MODIFIERS
            virtual inline void Pop () {
                USAGE_ASSERT ( Size() > 0 );
                queue_.pop();
            }

            virtual inline TElement DeleteTop() {
                USAGE_ASSERT ( Size() > 0 );

                TElement top = std::move( Top() );
                Pop();
                return top;
            }

            virtual inline void Clear () {
                std::queue<TElement> empty;
                std::swap( queue_, empty );
            }

            virtual inline void Swap  ( StdQueue & rhs ) {
                queue_.swap( rhs.queue_ );
            }
        ///@}

#pragma mark CAPACITY
        ///@Name Capacity
        ///@{
            virtual inline bool         Empty () const {
                return queue_.empty();
            }

            virtual inline Types::count Size  () const {
                return queue_.size();
            }
        ///@}
#pragma mark MEMBERS
    private:
        std::queue<TElement>  queue_;
};

} // namespace egoa

#endif // EGOA__DATA_STRUCTURES__CONTAINER__QUEUE__STD_FIFO_QUEUE_HPP

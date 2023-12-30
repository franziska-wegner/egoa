/*
 * TestStdQueue.hpp
 *
 *  Created on: Feb 17, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__TESTS__DATA_STRUCTURES__CONTAINER__TEST_STD_QUEUE_HPP
#define EGOA__TESTS__DATA_STRUCTURES__CONTAINER__TEST_STD_QUEUE_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "DataStructures/Container/Queues/StdQueue.hpp"
#include "Auxiliary/Types.hpp"

namespace egoa::test {

class TestStdQueue : public ::testing::Test {
    protected:
        // Type aliasing
        using TElement = Types::integer;
        using TQueue   = StdQueue<TElement>;
        using TVector  = std::vector<TElement>;

        void AddContent ( TQueue                      & queue
                        , std::vector<TElement> const & elements)
        {
            for ( auto element : elements )
                queue.Emplace(element);
        }

        void ExpectContent  ( TQueue                        queue
                            , std::vector<TElement> const & elements)
        {
            for ( auto e : elements ) {
                ASSERT_FALSE ( queue.Empty() );
                EXPECT_EQ ( e, queue.DeleteTop() );
            }
            EXPECT_TRUE ( queue.Empty() );
        }

    protected:
        TQueue         queue_;
        TQueue const & queueConst_ = queue_;
};

/**
* @brief Fixture for testing class StdFiFoQueue with no elements
*/
class TestStdQueueWithZeroElements : public TestStdQueue {
    protected:
        TestStdQueueWithZeroElements(){}
        virtual ~TestStdQueueWithZeroElements(){}
};

/**
* @brief Fixture for testing class StdFiFoQueue with one element
*/
class TestStdQueueWithOneElements : public TestStdQueue {
    protected:
        TestStdQueueWithOneElements(){}
        virtual ~TestStdQueueWithOneElements(){}

        virtual void SetUp() override {
            TElement element = 99;
            queue_.Emplace ( element );
        }
};

/**
* @brief Fixture for testing class StdFiFoQueue with one element
*/
class TestStdQueueWithVectorOfInteger : public TestStdQueue {
    protected:
        TestStdQueueWithVectorOfInteger(){}
        virtual ~TestStdQueueWithVectorOfInteger(){}

        TVector elements_ = { 5, 9, 23, 55, 1, 4, 2};

        virtual void SetUp() override {
            AddContent ( queue_, elements_ );
        }
};

} // namespace egoa::test

#endif // EGOA__TESTS__DATA_STRUCTURES__CONTAINER__TEST_STD_QUEUE_HPP

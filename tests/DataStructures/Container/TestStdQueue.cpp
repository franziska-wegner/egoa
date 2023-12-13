/*
 * TestStdQueue.cpp
 *
 *  Created on: Feb 17, 2019
 *      Author: Franziska Wegner
 */

#include "TestStdQueue.hpp"
#include "Helper/TestHelper.hpp"

using ::testing::Eq;
using ::testing::MatchesRegex;

namespace egoa::test {

#pragma mark TEST_STD_QUEUE

TEST_F ( TestStdQueue,
         ConstructFromVectorWithEmplace )
{
    TVector vector = {1,4,6};
    TQueue queue;
    AddContent ( queue, vector );

    EXPECT_EQ ( 3, queue.Size() );
    ExpectContent ( queue, vector );
}

TEST_F ( TestStdQueue,
         ConstructFromVectorWithPush )
{
    TVector vector = {1, 4, 6};
    TQueue queue;
    for ( auto element : vector )
        queue.Push(element);

    EXPECT_EQ ( 3, queue.Size() );
    ExpectContent ( queue, vector );
}

#pragma mark TEST_STD_QUEUE_WITH_ZERO_ELEMENTS

///@Name Basic Functionalities
///@{
    TEST_F  ( TestStdQueueWithZeroElements
            , BasicFunctionalityIsEmptyWhenCreated ) 
    {
        ASSERT_TRUE( queueConst_.Empty() );
    }

    TEST_F  ( TestStdQueueWithZeroElements
            , BasicFunctionalityHasSizeOfZero ) 
    {
        ASSERT_EQ( queueConst_.Size(), 0 );
    }
///@}

#pragma mark TEST_STD_QUEUE_WITH_ONE_ELEMENT

#pragma mark TEST_STD_QUEUE_WITH_MULTIPLE_INTEGER_ELEMENTS

} // namespace egoa::test
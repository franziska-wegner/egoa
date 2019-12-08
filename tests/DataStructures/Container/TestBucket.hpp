/*
 * TestBucket.hpp
 *
 *  Created on: Feb 05, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__TESTS__DATA_STRUCTURES__CONTAINER__TEST_BUCKET_HPP
#define EGOA__TESTS__DATA_STRUCTURES__CONTAINER__TEST_BUCKET_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#ifdef OPENMP_AVAILABLE
    #include <omp.h>
#endif

#include "DataStructures/Container/Queues/Bucket.hpp"
#include "DataStructures/Container/Queues/BinaryHeap.hpp"
#include "DataStructures/Labels/BucketElement.hpp"

namespace egoa::test {

class TestBucket : public ::testing::Test {
    protected:
        // Type aliasing
        using TElement = BucketElement<Types::integer>;
        using TBucket  = Bucket< BinaryHeap<TElement> >;
    protected:
        TBucket bucket_;
        TBucket const & bucketConst_ = bucket_;
};

/**
* @brief Fixture for testing class Bucket
*/
class TestBucketWithZeroElements : public TestBucket {
    protected:
        TestBucketWithZeroElements(){}
        virtual ~TestBucketWithZeroElements(){}
};

using TestBucketWithZeroElementsDeathTest = TestBucketWithZeroElements;

class TestBucketWithOneIntegerElement : public TestBucket {
    protected:
        TestBucketWithOneIntegerElement(){}
        virtual ~TestBucketWithOneIntegerElement(){}

        virtual void SetUp() override {
            TElement element = TElement ( 99, true );
            bucket_.Merge( element );
        }
};

using TestBucketWithOneIntegerElementDeathTest = TestBucketWithOneIntegerElement;

class TestBucketWithMultipleInteger : public TestBucket {
    protected:
        std::vector<TElement> intVector_ =  { TElement(55)
                                            , TElement(23)
                                            , TElement(9)
                                            , TElement(5)
                                            , TElement(4)
                                            , TElement(2)
                                            , TElement(1) };

        TestBucketWithMultipleInteger(){}
        virtual ~TestBucketWithMultipleInteger(){}

        virtual void SetUp() override {
            for ( auto & element : intVector_ ) {
                bucket_.Merge( element );
            }
        }
};
using TestBucketWithMultipleIntegerDeathTest = TestBucketWithMultipleInteger;


class TestBucketWithComparatorMaximizeWithMultipleInteger : public TestBucket {
    protected:
        TestBucketWithComparatorMaximizeWithMultipleInteger(){}
        virtual ~TestBucketWithComparatorMaximizeWithMultipleInteger(){}

        virtual void SetUp() override {
            std::vector<TElement> intVector =   { TElement(55)
                                                , TElement(23)
                                                , TElement(9)
                                                , TElement(5)
                                                , TElement(4)
                                                , TElement(2)
                                                , TElement(1) };
            for ( auto & element : intVector ) {
                bucket_.Merge( element );
            }
        }
};
using TestBucketWithComparatorMaximizeWithMultipleIntegerDeathTest = TestBucketWithComparatorMaximizeWithMultipleInteger;

template<typename TElement>
void ParallelIteratorCheck   ( std::vector<TElement>                 const & numberVector
                             , std::vector<Types::count>             const & numberOfElements
                             , std::vector< std::vector<TElement> >  const & elementsLoopedOver ) 
{
    Types::count sum = 0;
    for ( Types::count number : numberOfElements ) {
        sum += number;
    }
    EXPECT_EQ( sum, numberVector.size() );

    sum = 0;
    Types::real elementSum = 0;
    for ( auto & elementPerThread : elementsLoopedOver ) {
        sum += elementPerThread.size();
        for ( TElement const & element : elementPerThread ) {
            elementSum += element.Value();
            auto iter = std::find(numberVector.begin(), numberVector.end(), element );
            EXPECT_NE( iter, numberVector.end() );
        }
    }
    EXPECT_EQ( sum, numberVector.size() );
    EXPECT_EQ ( elementSum
              , std::accumulate ( numberVector.begin()
                                , numberVector.end()
                                , 0
                                , [](TElement const & left, TElement const & right) { 
                                    return left.Value() + right.Value(); 
                                }) 
              );
}

} // namespace egoa::test

#endif // EGOA__TESTS__DATA_STRUCTURES__CONTAINER__TEST_BUCKET_HPP

/*
 * TestBinaryHeap.hpp
 *
 *  Created on: Feb 04, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__TESTS__DATA_STRUCTURES__CONTAINER__TEST_BINARY_HEAP_HPP
#define EGOA__TESTS__DATA_STRUCTURES__CONTAINER__TEST_BINARY_HEAP_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "DataStructures/Container/Queues/BinaryHeap.hpp"
#include "Auxiliary/Types.hpp"

namespace egoa::test {

/**
 * @brief      Base class for fixtures for testing class BinaryHeap
 */
class TestBinaryHeap : public ::testing::Test {
    protected:
        // Type aliasing
        using TElement    = Types::integer;
        using TBinaryHeap = BinaryHeap<TElement>;
        using TVector     = std::vector<TElement>;

        void ExpectContent  ( TBinaryHeap                   heap
                            , std::vector<TElement> const & elements) 
        {
            for ( auto e : elements ) {
                ASSERT_FALSE ( heap.Empty() );
                EXPECT_EQ ( e, heap.DeleteTop() );
            }
            EXPECT_TRUE ( heap.Empty() );
        }

    protected:
        TBinaryHeap         heap_;
        TBinaryHeap const & heapConst_ = heap_;
};

using TestBinaryHeapDeathTest = TestBinaryHeap;

/**
* @brief Fixture for testing class BinaryHeap with no elements
*/
class TestBinaryHeapWithZeroElements : public TestBinaryHeap {
    protected:
        TestBinaryHeapWithZeroElements(){}
        virtual ~TestBinaryHeapWithZeroElements(){}
};

using TestBinaryHeapWithZeroElementsDeathTest = TestBinaryHeapWithZeroElements;

/**
* @brief Fixture for testing class BinaryHeap with one element
*/
class TestBinaryHeapWithOneIntegerElement : public TestBinaryHeap {
    protected:
        TestBinaryHeapWithOneIntegerElement(){}
        virtual ~TestBinaryHeapWithOneIntegerElement(){}

        virtual void SetUp() override 
        {
            TElement element = 99;
            heap_.Emplace(element);
        }
};

/**
* @brief Fixture for testing class BinaryHeap with a vector of elements
*/
class TestBinaryHeapWithVectorOfInteger : public TestBinaryHeap {
    protected:
        TestBinaryHeapWithVectorOfInteger(){}
        virtual ~TestBinaryHeapWithVectorOfInteger(){}

        virtual void SetUp() override 
        {
            TVector elements = { 5, 9, 23, 55, 1, 4, 2};
            heap_.BuildWith ( elements );
        }
};

using TestBinaryHeapWithVectorOfIntegerDeathTest = TestBinaryHeapWithOneIntegerElement;

class TestHeapIterator : public TestBinaryHeap {
    protected:
        std::vector<TElement> elements_;

        void SetUp() override 
        {
            elements_ = {4, 5, 8, 32, 432, 3, 7};
            heap_.BuildWith(elements_);
            std::sort(elements_.begin(), elements_.end());
        }
};

} // namespace egoa::test

#endif // EGOA__TESTS__DATA_STRUCTURES__CONTAINER__TEST_BINARY_HEAP_HPP

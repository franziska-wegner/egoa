/*
 * TestMappingBinaryHeap.hpp
 *
 *  Created on: Feb 19, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */

#ifndef EGOA__TESTS__DATA_STRUCTURES__CONTAINER__TEST_MAPPING_BINARY_HEAP_HPP
#define EGOA__TESTS__DATA_STRUCTURES__CONTAINER__TEST_MAPPING_BINARY_HEAP_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Helper/TestHelper.hpp"

#include "DataStructures/Container/Queues/MappingBinaryHeap.hpp"
#include "Auxiliary/Types.hpp"

namespace egoa::test {

class TestMappingBinaryHeap : public ::testing::Test {
protected:
    using TElement = HashableElement;
    using TKey     = Types::integer;
    using THeap    = MappingBinaryHeap<TElement, TKey>;

    void ExpectContent(THeap heap, std::vector<TElement> const & elements) {
        for ( auto e : elements ) {
            ASSERT_FALSE ( heap.Empty() );
            auto top = heap.DeleteTop();
            EXPECT_EQ( e, top.first );
        }
        EXPECT_TRUE ( heap.Empty() );
    }

    THeap         heap_;
    THeap const & heapConst_ = heap_;
};

using TestMappingBinaryHeapEmpty = TestMappingBinaryHeap;
using TestMappingBinaryHeapEmptyDeathTest = TestMappingBinaryHeapEmpty;

class TestMappingBinaryHeapWithOneElement : public TestMappingBinaryHeap {
protected:
    void SetUp() override {
        heap_.Insert(element_, key_);
    }

    const TElement element_ = TElement(0);
    const TKey     key_     = 32;
};

class TestMappingBinaryHeapWithMultipleElements : public TestMappingBinaryHeap {
protected:
    void SetUp() override {
        for (Types::count i = 0; i < elements_.size(); ++i) {
            heap_.Insert(elements_[i], keys_[i]);
        }

        elementsSorted_ = elements_;
        sortById(elementsSorted_);
    }

    static void sortById(std::vector<TElement> & vector) {
        using std::begin, std::end;
        std::sort(begin(vector), end(vector),
            [](TElement const & first, TElement const & second) {
                return first.Identifier() < second.Identifier();
            });
    }

    std::vector<TElement> elements_ = {TElement(6),
                                       TElement(3),
                                       TElement(5),
                                       TElement(2),
                                       TElement(7),
                                       TElement(9),
                                       TElement(1)};
    std::vector<TKey> keys_ = {6, 3, 5, 2, 7, 9, 1};

    std::vector<TElement> elementsSorted_;

};

} // namespace egoa::test

#endif // EGOA__TESTS__DATA_STRUCTURES__CONTAINER__TEST_MAPPING_BINARY_HEAP_HPP

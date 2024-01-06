/*
 * TestMappingBinaryHeap.hpp
 *
 *  Created on: Feb 19, 2019
 *      Author: Franziska Wegner, Matthias Wolf
 */

#include "TestMappingBinaryHeap.hpp"

#include <tuple>

using ::testing::MatchesRegex;

namespace egoa::test {

auto buildAssertionString(std::string const & function, std::string const & message) -> std::string {
    return buildAssertionString("MappingBinaryHeap.hpp", "MappingBinaryHeap", function, message);
}

#pragma mark Empty
TEST_F(TestMappingBinaryHeapEmpty, Empty) {
    EXPECT_TRUE(heap_.Empty());
    EXPECT_TRUE(heapConst_.Empty());
}

TEST_F(TestMappingBinaryHeapWithOneElement, Empty) {
    EXPECT_FALSE(heap_.Empty());
    EXPECT_FALSE(heapConst_.Empty());
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, Empty) {
    EXPECT_FALSE(heap_.Empty());
    EXPECT_FALSE(heapConst_.Empty());
}

#pragma mark Size
TEST_F(TestMappingBinaryHeapEmpty, Size) {
    EXPECT_EQ(0, heap_.Size());
    EXPECT_EQ(0, heapConst_.Size());
}

TEST_F(TestMappingBinaryHeapWithOneElement, Size) {
    EXPECT_EQ(1, heap_.Size());
    EXPECT_EQ(1, heapConst_.Size());
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, Size) {
    EXPECT_EQ(elements_.size(), heap_.Size());
    EXPECT_EQ(elements_.size(), heapConst_.Size());
}

#pragma mark Content
TEST_F(TestMappingBinaryHeapEmpty, Content) {
    ExpectContent(heap_, {});
}

TEST_F(TestMappingBinaryHeapWithOneElement, Content) {
    ExpectContent(heap_, {element_});
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, Content) {
    ExpectContent(heap_, elementsSorted_);
}

#pragma mark Top

#ifdef EGOA_ENABLE_ASSERTION
    TEST_F ( TestMappingBinaryHeapEmptyDeathTest
           , TopDeathTest )
    {
        auto assertionString = buildAssertionString ( "MappingBinaryHeap.hpp"
                                                    , "MappingBinaryHeap"
                                                    , "Top"
                                                    , R"(!Empty\(\))");
        ASSERT_DEATH({heapConst_.Top();}, assertionString);
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestMappingBinaryHeapEmpty
            , TopExceptionHandling )
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "Top"
                                                    , R"(!Empty\(\))");
        try {
            heapConst_.Top();
        } catch ( std::runtime_error const & error ) {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) {
            FAIL()  << "Expected std::runtime_error with message: "
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION


TEST_F(TestMappingBinaryHeapWithOneElement, Top) {
    auto expected = std::make_pair(element_, key_);
    EXPECT_EQ(expected, heapConst_.Top());
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, Top) {
    auto expected = std::make_pair(elementsSorted_.front(),
                                   static_cast<TKey>(elementsSorted_.front().Identifier()));
    EXPECT_EQ(expected, heapConst_.Top());
}

#pragma mark TopElement
#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestMappingBinaryHeapEmptyDeathTest
            , TopElementDeathTest )
    {
        auto assertionString = buildAssertionString ( "MappingBinaryHeap.hpp"
                                                    , "MappingBinaryHeap"
                                                    , "TopElement"
                                                    , R"(!Empty\(\))");
        ASSERT_DEATH( {heapConst_.TopElement();}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestMappingBinaryHeapEmpty
            , TopElementExceptionHandling )
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "TopElement"
                                                    , R"(!Empty\(\))");
        try {
            heapConst_.TopElement();
        } catch ( std::runtime_error const & error ) {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) {
            FAIL()  << "Expected std::runtime_error with message: "
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

TEST_F(TestMappingBinaryHeapWithOneElement, TopElement) {
    EXPECT_EQ(element_, heapConst_.TopElement());
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, TopElement) {
    EXPECT_EQ(elementsSorted_.front(), heapConst_.TopElement());
}

#pragma mark TopKey
#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestMappingBinaryHeapEmptyDeathTest
            , TopKeyDeathTest )
    {
        auto assertionString = buildAssertionString ( "MappingBinaryHeap.hpp"
                                                    , "MappingBinaryHeap"
                                                    , "TopKey"
                                                    , R"(!Empty\(\))");
        ASSERT_DEATH( {heapConst_.TopKey();}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestMappingBinaryHeapEmpty
            , TopKeyExceptionHandling )
    {
        auto assertionString = buildAssertionString ( "MappingBinaryHeap.hpp"
                                                    , "MappingBinaryHeap"
                                                    , "TopKey"
                                                    , R"(!Empty\(\))");
        try {
            heapConst_.TopKey();
        } catch ( std::runtime_error const & error ) {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) {
            FAIL()  << "Expected std::runtime_error with message: "
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

TEST_F(TestMappingBinaryHeapWithOneElement, TopKey) {
    EXPECT_EQ(key_, heapConst_.TopKey());
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, TopKey) {
    EXPECT_EQ(elementsSorted_.front().Identifier(), heapConst_.TopKey());
}

#pragma mark KeyOf
TEST_F(TestMappingBinaryHeapWithOneElement, KeyOf) {
    EXPECT_EQ(key_, heapConst_.KeyOf(element_));
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, KeyOf) {
    for (const auto & element : elements_) {
        EXPECT_EQ(element.Identifier(), heapConst_.KeyOf(element));
    }
}

#pragma mark HasKeyOf
TEST_F(TestMappingBinaryHeapEmpty, HasKeyOfNonExisting) {
    EXPECT_FALSE(heap_.HasKeyOf(TElement(345)));
    EXPECT_FALSE(heapConst_.HasKeyOf(TElement(345)));
}

TEST_F(TestMappingBinaryHeapWithOneElement, HasKeyOfNonExisting) {
    EXPECT_FALSE(heap_.HasKeyOf(TElement(345)));
    EXPECT_FALSE(heapConst_.HasKeyOf(TElement(345)));
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, HasKeyOfNonExisting) {
    EXPECT_FALSE(heap_.HasKeyOf(TElement(345)));
    EXPECT_FALSE(heapConst_.HasKeyOf(TElement(345)));
}

TEST_F(TestMappingBinaryHeapWithOneElement, HasKeyOfExisting) {
    EXPECT_TRUE(heap_.HasKeyOf(element_));
    EXPECT_TRUE(heapConst_.HasKeyOf(element_));
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, HasKeyOfExisting) {
    for (const auto & element : elements_) {
        EXPECT_TRUE(heap_.HasKeyOf(element));
        EXPECT_TRUE(heapConst_.HasKeyOf(element));
    }
}

#pragma mark Insert(TElement, TKey)
TEST_F(TestMappingBinaryHeapEmpty, Insert) {
    TElement element(234);
    TKey key(12);

    heap_.Insert(element, key);

    EXPECT_EQ(1, heap_.Size());
    EXPECT_EQ(element, heap_.TopElement());
    EXPECT_EQ(key, heap_.TopKey());
}

TEST_F(TestMappingBinaryHeapEmpty, InsertTemporary) {
    TElement element(234);
    TKey key(12);

    heap_.Insert(TElement(234), TKey(12));

    EXPECT_EQ(1, heap_.Size());
    EXPECT_EQ(element, heap_.TopElement());
    EXPECT_EQ(key, heap_.TopKey());
}

TEST_F(TestMappingBinaryHeapEmpty, InsertOneTemporaryOneLValue) {
    TElement element(234);
    TKey key(12);

    heap_.Insert(TElement(234), key);

    EXPECT_EQ(1, heap_.Size());
    EXPECT_EQ(element, heap_.TopElement());
    EXPECT_EQ(key, heap_.TopKey());
}

TEST_F(TestMappingBinaryHeapEmpty, InsertOneLValueOneTemporary) {
    TElement element(234);
    TKey key(12);

    heap_.Insert(element, TKey(12));

    EXPECT_EQ(1, heap_.Size());
    EXPECT_EQ(element, heap_.TopElement());
    EXPECT_EQ(key, heap_.TopKey());
}

TEST_F(TestMappingBinaryHeapWithOneElement, InsertSmaller) {
    TElement newElement(234);
    TKey key(12);

    heap_.Insert(newElement, key);

    EXPECT_EQ(2, heap_.Size());
    EXPECT_EQ(newElement, heap_.TopElement());
    EXPECT_EQ(key, heap_.TopKey());
    ExpectContent(heap_, {newElement, element_});
}

TEST_F(TestMappingBinaryHeapWithOneElement, InsertEqual) {
    TElement newElement(234);
    TKey key(32);

    heap_.Insert(newElement, key);

    EXPECT_EQ(2, heap_.Size());
    EXPECT_EQ(32, heap_.TopKey());
}

TEST_F(TestMappingBinaryHeapWithOneElement, InsertLarger) {
    TElement newElement(234);
    TKey key(456);

    heap_.Insert(newElement, key);

    EXPECT_EQ(2, heap_.Size());
    ExpectContent(heap_, {element_, newElement});
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, InsertSmallest) {
    TElement newElement(0);
    TKey newKey(0);

    heap_.Insert(newElement, newKey);

    EXPECT_EQ(elements_.size() + 1, heap_.Size());
    EXPECT_EQ(newElement, heap_.TopElement());
    EXPECT_EQ(newKey, heap_.TopKey());

    std::vector<TElement> expected = elements_;
    expected.push_back(newElement);
    sortById(expected);
    ExpectContent(heap_, expected);
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, InsertMiddle) {
    TElement newElement(4);
    TKey newKey(4);

    heap_.Insert(newElement, newKey);

    EXPECT_EQ(elements_.size() + 1, heap_.Size());

    std::vector<TElement> expected = elements_;
    expected.push_back(newElement);
    sortById(expected);
    ExpectContent(heap_, expected);
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, InsertLargest) {
    TElement newElement(12);
    TKey newKey(12);

    heap_.Insert(newElement, newKey);

    EXPECT_EQ(elements_.size() + 1, heap_.Size());

    std::vector<TElement> expected = elements_;
    expected.push_back(newElement);
    sortById(expected);
    ExpectContent(heap_, expected);
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, InsertEqual) {
    TElement newElement(234);
    TKey newKey(5);

    heap_.Insert(newElement, newKey);

    EXPECT_EQ(elements_.size() + 1, heap_.Size());

    auto expectedKeys = keys_;
    expectedKeys.push_back(newKey);
    using std::begin, std::end;
    std::sort(begin(expectedKeys), end(expectedKeys));

    for (TKey key : expectedKeys) {
        ASSERT_FALSE(heap_.Empty());
        auto top = heap_.DeleteTop();
        EXPECT_EQ(key, top.second);
        if (key == newKey) {
            EXPECT_TRUE(top.first.Identifier() == key
                || top.first == newElement);
        } else {
            EXPECT_EQ(key, top.first.Identifier());
        }
    }
}

#pragma mark Insert(std::pair)
TEST_F(TestMappingBinaryHeapEmpty, InsertPair) {
    TElement newElement(234);
    TKey newKey(12);
    auto pair = std::make_pair(newElement, newKey);

    heap_.Insert(pair);

    EXPECT_EQ(1, heap_.Size());
    EXPECT_EQ(newElement, heap_.TopElement());
    EXPECT_EQ(newKey, heap_.TopKey());
}

TEST_F(TestMappingBinaryHeapEmpty, InsertPairConstReference) {
    TElement newElement(234);
    TKey newKey(12);
    auto pair = std::make_pair(newElement, newKey);
    auto const & pairConst = pair;

    heap_.Insert(pairConst);

    EXPECT_EQ(1, heap_.Size());
    EXPECT_EQ(newElement, heap_.TopElement());
    EXPECT_EQ(newKey, heap_.TopKey());
}

TEST_F(TestMappingBinaryHeapEmpty, InsertTemporaryPair) {
    TElement newElement(234);
    TKey newKey(12);

    heap_.Insert(std::make_pair(TElement(234), TKey(12)));

    EXPECT_EQ(1, heap_.Size());
    EXPECT_EQ(newElement, heap_.TopElement());
    EXPECT_EQ(newKey, heap_.TopKey());
}

TEST_F(TestMappingBinaryHeapWithOneElement, InsertPairSmaller) {
    TElement newElement(234);
    TKey newKey(12);
    auto pair = std::make_pair(newElement, newKey);

    heap_.Insert(pair);

    EXPECT_EQ(2, heap_.Size());
    EXPECT_EQ(newElement, heap_.TopElement());
    EXPECT_EQ(newKey, heap_.TopKey());
    ExpectContent(heap_, {newElement, element_});
}

TEST_F(TestMappingBinaryHeapWithOneElement, InsertPairEqual) {
    TElement newElement(234);
    TKey newKey(32);
    auto pair = std::make_pair(newElement, newKey);

    heap_.Insert(pair);

    EXPECT_EQ(2, heap_.Size());
    EXPECT_EQ(32, heap_.TopKey());
}

TEST_F(TestMappingBinaryHeapWithOneElement, InsertPairLarger) {
    TElement newElement(234);
    TKey newKey(456);
    auto pair = std::make_pair(newElement, newKey);

    heap_.Insert(pair);

    EXPECT_EQ(2, heap_.Size());
    ExpectContent(heap_, {element_, newElement});
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, InsertPairSmallest) {
    TElement newElement(0);
    TKey newKey(0);
    auto pair = std::make_pair(newElement, newKey);

    heap_.Insert(pair);

    EXPECT_EQ(elements_.size() + 1, heap_.Size());
    EXPECT_EQ(newElement, heap_.TopElement());
    EXPECT_EQ(newKey, heap_.TopKey());

    std::vector<TElement> expected = elements_;
    expected.push_back(newElement);
    sortById(expected);
    ExpectContent(heap_, expected);
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, InsertPairMiddle) {
    TElement newElement(4);
    TKey newKey(4);
    auto pair = std::make_pair(newElement, newKey);

    heap_.Insert(pair);

    EXPECT_EQ(elements_.size() + 1, heap_.Size());

    std::vector<TElement> expected = elements_;
    expected.push_back(newElement);
    sortById(expected);
    ExpectContent(heap_, expected);
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, InsertPairLargest) {
    TElement newElement(12);
    TKey newKey(12);
    auto pair = std::make_pair(newElement, newKey);

    heap_.Insert(pair);

    EXPECT_EQ(elements_.size() + 1, heap_.Size());

    std::vector<TElement> expected = elements_;
    expected.push_back(newElement);
    sortById(expected);
    ExpectContent(heap_, expected);
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, InsertPairEqual) {
    TElement newElement(234);
    TKey newKey(5);
    auto pair = std::make_pair(newElement, newKey);

    heap_.Insert(pair);

    EXPECT_EQ(elements_.size() + 1, heap_.Size());

    auto expectedKeys = keys_;
    expectedKeys.push_back(newKey);
    using std::begin, std::end;
    std::sort(begin(expectedKeys), end(expectedKeys));

    for (TKey key : expectedKeys) {
        ASSERT_FALSE(heap_.Empty());
        auto top = heap_.DeleteTop();
        EXPECT_EQ(key, top.second);
        if (key == newKey) {
            EXPECT_TRUE(top.first.Identifier() == key
                || top.first == newElement);
        } else {
            EXPECT_EQ(key, top.first.Identifier());
        }
    }
}

#pragma mark operator+=
TEST_F(TestMappingBinaryHeapEmpty, OperatorPlusEqual) {
    TElement newElement(234);
    TKey newKey(12);
    auto pair = std::make_pair(newElement, newKey);

    auto & heap = (heap_ += pair);

    EXPECT_EQ(&heap, &heap_);
    EXPECT_EQ(1, heap_.Size());
    EXPECT_EQ(newElement, heap_.TopElement());
    EXPECT_EQ(newKey, heap_.TopKey());
}

TEST_F(TestMappingBinaryHeapEmpty, OperatorPlusEqualConstReference) {
    TElement newElement(234);
    TKey newKey(12);
    auto pair = std::make_pair(newElement, newKey);
    auto const & pairConst = pair;

    auto & heap = (heap_ += pairConst);

    EXPECT_EQ(&heap, &heap_);
    EXPECT_EQ(1, heap_.Size());
    EXPECT_EQ(newElement, heap_.TopElement());
    EXPECT_EQ(newKey, heap_.TopKey());
}

TEST_F(TestMappingBinaryHeapEmpty, OperatorPlusEqualTemporaryPair) {
    TElement newElement(234);
    TKey newKey(12);

    auto & heap = (heap_ += std::make_pair(TElement(234), TKey(12)));

    EXPECT_EQ(&heap, &heap_);
    EXPECT_EQ(1, heap_.Size());
    EXPECT_EQ(newElement, heap_.TopElement());
    EXPECT_EQ(newKey, heap_.TopKey());
}

TEST_F(TestMappingBinaryHeapWithOneElement, OperatorPlusEqualSmaller) {
    TElement newElement(234);
    TKey newKey(12);
    auto pair = std::make_pair(newElement, newKey);

    auto & heap = (heap_ += pair);

    EXPECT_EQ(&heap, &heap_);
    EXPECT_EQ(2, heap_.Size());
    EXPECT_EQ(newElement, heap_.TopElement());
    EXPECT_EQ(newKey, heap_.TopKey());
    ExpectContent(heap_, {newElement, element_});
}

TEST_F(TestMappingBinaryHeapWithOneElement, OperatorPlusEqualEqual) {
    TElement newElement(234);
    TKey newKey(32);
    auto pair = std::make_pair(newElement, newKey);

    auto & heap = (heap_ += pair);

    EXPECT_EQ(&heap, &heap_);
    EXPECT_EQ(2, heap_.Size());
    EXPECT_EQ(32, heap_.TopKey());
}

TEST_F(TestMappingBinaryHeapWithOneElement, OperatorPlusEqualLarger) {
    TElement newElement(234);
    TKey newKey(456);
    auto pair = std::make_pair(newElement, newKey);

    auto & heap = (heap_ += pair);

    EXPECT_EQ(&heap, &heap_);
    EXPECT_EQ(2, heap_.Size());
    ExpectContent(heap_, {element_, newElement});
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, OperatorPlusEqualSmallest) {
    TElement newElement(0);
    TKey newKey(0);
    auto pair = std::make_pair(newElement, newKey);

    auto & heap = (heap_ += pair);

    EXPECT_EQ(&heap, &heap_);
    EXPECT_EQ(elements_.size() + 1, heap_.Size());
    EXPECT_EQ(newElement, heap_.TopElement());
    EXPECT_EQ(newKey, heap_.TopKey());

    std::vector<TElement> expected = elements_;
    expected.push_back(newElement);
    sortById(expected);
    ExpectContent(heap_, expected);
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, OperatorPlusEqualMiddle) {
    TElement newElement(4);
    TKey newKey(4);
    auto pair = std::make_pair(newElement, newKey);

    auto & heap = (heap_ += pair);

    EXPECT_EQ(&heap, &heap_);
    EXPECT_EQ(elements_.size() + 1, heap_.Size());

    std::vector<TElement> expected = elements_;
    expected.push_back(newElement);
    sortById(expected);
    ExpectContent(heap_, expected);
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, OperatorPlusEqualLargest) {
    TElement newElement(12);
    TKey newKey(12);
    auto pair = std::make_pair(newElement, newKey);

    auto & heap = (heap_ += pair);

    EXPECT_EQ(&heap, &heap_);
    EXPECT_EQ(elements_.size() + 1, heap_.Size());

    std::vector<TElement> expected = elements_;
    expected.push_back(newElement);
    sortById(expected);
    ExpectContent(heap_, expected);
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, OperatorPlusEqualEqual) {
    TElement newElement(234);
    TKey newKey(5);
    auto pair = std::make_pair(newElement, newKey);

    auto & heap = (heap_ += pair);

    EXPECT_EQ(&heap, &heap_);
    EXPECT_EQ(elements_.size() + 1, heap_.Size());

    auto expectedKeys = keys_;
    expectedKeys.push_back(newKey);
    using std::begin, std::end;
    std::sort(begin(expectedKeys), end(expectedKeys));

    for (TKey key : expectedKeys) {
        ASSERT_FALSE(heap_.Empty());
        auto top = heap_.DeleteTop();
        EXPECT_EQ(key, top.second);
        if (key == newKey) {
            EXPECT_TRUE(top.first.Identifier() == key
                || top.first == newElement);
        } else {
            EXPECT_EQ(key, top.first.Identifier());
        }
    }
}

#pragma mark Emplace
TEST_F(TestMappingBinaryHeapEmpty, Emplace) {
    TElement newElement(234);
    TKey newKey(12);

    heap_.Emplace(std::piecewise_construct,
                  std::forward_as_tuple(234),
                  std::forward_as_tuple(12));

    EXPECT_EQ(1, heap_.Size());
    EXPECT_TRUE(heap_.HasKeyOf(newElement));
    EXPECT_EQ(newElement, heap_.TopElement());
    EXPECT_EQ(newKey, heap_.TopKey());
}

TEST_F(TestMappingBinaryHeapWithOneElement, EmplaceSmaller) {
    TElement newElement(234);
    TKey newKey(12);

    heap_.Emplace(std::piecewise_construct,
                  std::forward_as_tuple(234),
                  std::forward_as_tuple(12));

    EXPECT_EQ(2, heap_.Size());
    EXPECT_EQ(newElement, heap_.TopElement());
    EXPECT_EQ(newKey, heap_.TopKey());
    ExpectContent(heap_, {newElement, element_});
}

TEST_F(TestMappingBinaryHeapWithOneElement, EmplaceEqual) {
    TElement newElement(234);
    TKey newKey(key_);

    heap_.Emplace(std::piecewise_construct,
                  std::forward_as_tuple(234),
                  std::forward_as_tuple(key_));

    EXPECT_EQ(2, heap_.Size());
    EXPECT_EQ(newKey, heap_.TopKey());
}

TEST_F(TestMappingBinaryHeapWithOneElement, EmplaceLarger) {
    TElement newElement(234);
    TKey newKey(456);
    auto pair = std::make_pair(newElement, newKey);

    heap_.Emplace(std::piecewise_construct,
                  std::forward_as_tuple(234),
                  std::forward_as_tuple(456));

    EXPECT_EQ(2, heap_.Size());
    ExpectContent(heap_, {element_, newElement});
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, EmplaceSmallest) {
    TElement newElement(0);
    TKey newKey(0);

    heap_.Emplace(std::piecewise_construct,
                  std::forward_as_tuple(0),
                  std::forward_as_tuple(0));

    EXPECT_EQ(elements_.size() + 1, heap_.Size());
    EXPECT_EQ(newElement, heap_.TopElement());
    EXPECT_EQ(newKey, heap_.TopKey());

    std::vector<TElement> expected = elements_;
    expected.push_back(newElement);
    sortById(expected);
    ExpectContent(heap_, expected);
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, EmplaceMiddle) {
    TElement newElement(4);
    TKey newKey(4);

    heap_.Emplace(std::piecewise_construct,
                  std::forward_as_tuple(4),
                  std::forward_as_tuple(4));

    EXPECT_EQ(elements_.size() + 1, heap_.Size());

    std::vector<TElement> expected = elements_;
    expected.push_back(newElement);
    sortById(expected);
    ExpectContent(heap_, expected);
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, EmplaceLargest) {
    TElement newElement(12);
    TKey newKey(12);

    heap_.Emplace(std::piecewise_construct,
                  std::forward_as_tuple(12),
                  std::forward_as_tuple(12));

    EXPECT_EQ(elements_.size() + 1, heap_.Size());

    std::vector<TElement> expected = elements_;
    expected.push_back(newElement);
    sortById(expected);
    ExpectContent(heap_, expected);
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, EmplaceEqual) {
    TElement newElement(234);
    TKey newKey(5);

    heap_.Emplace(std::piecewise_construct,
                  std::forward_as_tuple(234),
                  std::forward_as_tuple(5));

    EXPECT_EQ(elements_.size() + 1, heap_.Size());

    auto expectedKeys = keys_;
    expectedKeys.push_back(newKey);
    using std::begin, std::end;
    std::sort(begin(expectedKeys), end(expectedKeys));

    for (TKey key : expectedKeys) {
        ASSERT_FALSE(heap_.Empty());
        auto top = heap_.DeleteTop();
        EXPECT_EQ(key, top.second);
        if (key == newKey) {
            EXPECT_TRUE(top.first.Identifier() == key
                || top.first == newElement);
        } else {
            EXPECT_EQ(key, top.first.Identifier());
        }
    }
}

#pragma mark DeleteTop
#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestMappingBinaryHeapEmptyDeathTest
            , DeleteTopDeathTest )
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "DeleteTop"
                                                    , R"(!Empty\(\))");
        ASSERT_DEATH( {heap_.DeleteTop();}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestMappingBinaryHeapEmpty
            , DeleteTopExceptionHandling )
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "DeleteTop"
                                                    , R"(!Empty\(\))");
        try {
            heap_.DeleteTop();
        } catch ( std::runtime_error const & error ) {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) {
            FAIL()  << "Expected std::runtime_error with message: "
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

TEST_F(TestMappingBinaryHeapWithOneElement, DeleteTop) {
    auto top = heap_.DeleteTop();
    EXPECT_EQ(element_, top.first);
    EXPECT_EQ(key_, top.second);
    EXPECT_TRUE(heap_.Empty());
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, DeleteTop) {
    auto top = heap_.DeleteTop();
    EXPECT_EQ(elementsSorted_.front(), top.first);
    EXPECT_EQ(elementsSorted_.front().Identifier(), top.second);
    EXPECT_FALSE(heap_.Empty());
    EXPECT_EQ(elements_.size() - 1, heap_.Size());

    using std::begin, std::end;
    std::vector<TElement> expectedElements(begin(elementsSorted_) + 1,
                                           end(elementsSorted_));
    ExpectContent(heap_, expectedElements);
}

#pragma mark Pop
#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestMappingBinaryHeapEmptyDeathTest
            , PopDeathTest )
    {
        auto assertionString = buildAssertionString ( "MappingBinaryHeap.hpp"
                                                    , "MappingBinaryHeap"
                                                    , "Pop"
                                                    , R"(!Empty\(\))");
        ASSERT_DEATH( {heap_.Pop();}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestMappingBinaryHeapEmpty
            , PopExceptionHandling )
    {
        auto assertionString = buildAssertionString ( "MappingBinaryHeap.hpp"
                                                    , "MappingBinaryHeap"
                                                    , "Pop"
                                                    , R"(!Empty\(\))");
        try {
            heap_.Pop();
        } catch ( std::runtime_error const & error ) {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) {
            FAIL()  << "Expected std::runtime_error with message: "
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

TEST_F(TestMappingBinaryHeapWithOneElement, Pop) {
    heap_.Pop();
    EXPECT_TRUE(heap_.Empty());
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, Pop) {
    heap_.Pop();
    EXPECT_FALSE(heap_.Empty());
    EXPECT_EQ(elements_.size() - 1, heap_.Size());

    using std::begin, std::end;
    std::vector<TElement> expectedElements(begin(elementsSorted_) + 1,
                                           end(elementsSorted_));
    ExpectContent(heap_, expectedElements);
}

#pragma mark Clear
TEST_F(TestMappingBinaryHeapEmpty, Clear) {
    heap_.Clear();
    EXPECT_TRUE(heap_.Empty());
    EXPECT_EQ(0, heap_.Size());
}

TEST_F(TestMappingBinaryHeapWithOneElement, Clear) {
    heap_.Clear();
    EXPECT_TRUE(heap_.Empty());
    EXPECT_EQ(0, heap_.Size());
}

TEST_F(TestMappingBinaryHeapWithMultipleElements, Clear) {
    heap_.Clear();
    EXPECT_TRUE(heap_.Empty());
    EXPECT_EQ(0, heap_.Size());
}

#pragma mark Delete
TEST_F(TestMappingBinaryHeapWithMultipleElements, Delete) {
    TElement elementToDelete = elements_[2];
    auto deletedElement = heap_.Delete(elementToDelete);

    EXPECT_EQ(elementToDelete, deletedElement.first);
    EXPECT_EQ(keys_[2], deletedElement.second);
    EXPECT_EQ(elements_.size() - 1, heap_.Size());

    using std::begin, std::end;
    std::vector<TElement> expected;
    std::copy_if(begin(elementsSorted_),
                 end(elementsSorted_),
                 std::back_inserter(expected),
                 [elementToDelete](TElement e) { return e != elementToDelete; });
    ExpectContent(heap_, expected);
}

#pragma mark Iteration
TEST_F(TestMappingBinaryHeapWithMultipleElements, Iteration) {
    std::vector<TElement> extractedElements;

    for (auto & pair : heapConst_) {
        extractedElements.push_back(pair.first);
    }

    ExpectSameContent(elements_, extractedElements);
}

#pragma mark ForAllElements
TEST_F(TestMappingBinaryHeapWithMultipleElements, ForAllElements) {
    std::vector<TElement> extractedElements;

    heap_.template for_all_elements<egoa::ExecutionPolicy::sequential>(
        [&extractedElements](std::pair<TElement, TKey> const & pair) {
            extractedElements.push_back(pair.first);
        });

    ExpectSameContent(elements_, extractedElements);
}

} // namespace egoa::test

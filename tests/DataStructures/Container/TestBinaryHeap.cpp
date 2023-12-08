/*
 * TestBinaryHeap.cpp
 *
 *  Created on: Feb 04, 2019
 *      Author: Franziska Wegner
 */

#include "TestBinaryHeap.hpp"
#include "Helper/TestHelper.hpp"

#ifdef OPENMP_AVAILABLE
    #include <omp.h>
#endif

using ::testing::Eq;
using ::testing::MatchesRegex;

namespace egoa::test {

#pragma mark TEST_BINARY_HEAP

TEST_F( TestBinaryHeap,
       ConstructFromVector)
{
    TVector vector = {1,4,6};
    TBinaryHeap heap(vector);

    EXPECT_EQ(3, heap.Size());
    ExpectContent(heap, {1,4,6});
}

TEST_F( TestBinaryHeap,
         ConstructFromTemporaryVector)
{
    TBinaryHeap heap(TVector{1,4,6});
    EXPECT_EQ(3, heap.Size());
    ExpectContent(heap, {1,4,6});
}

#pragma mark TEST_BINARY_HEAP_THAT_IS_EMPTY

///@Name Basic Functionalities
///@{
    TEST_F  ( TestBinaryHeapWithZeroElements
            , BasicFunctionalityIsEmptyWhenCreated ) 
    {
        ASSERT_TRUE( heapConst_.Empty() );
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , BasicFunctionalityHasSizeOfZero ) 
    {
        ASSERT_EQ( heapConst_.Size(), 0 );
    }

#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBinaryHeapWithZeroElementsDeathTest
            , BasicFunctionalityCheckTopElementDeathTest ) 
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "Top"
                                                    , "!Empty\\(\\)");
        ASSERT_DEATH( {heapConst_.Top();}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBinaryHeapWithZeroElements
            , BasicFunctionalityCheckTopElementExceptionHandling ) 
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "Top"
                                                    , "!Empty\\(\\)");
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

    TEST_F  ( TestBinaryHeapWithZeroElements
            , BasicFunctionalityRemoveAllElements ) 
    {
        heap_.Clear();
        ASSERT_EQ( heap_.Size(), 0 );
        ASSERT_TRUE( heap_.Empty() );
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , BasicFunctionalitySearchForNonExistentElementWhileHeapIsEmpty ) 
    {
        EXPECT_EQ( heap_.Search(4), Const::NONE );
    }
///@}

///@Name Comparison check
///@{
    TEST_F  ( TestBinaryHeapWithZeroElements
            , EqualityCheckUsingFunctionWithNotIdenticalSuccess ) 
    {
        TBinaryHeap heapIdentical;
        EXPECT_TRUE( heap_.IsEqualTo<false>(heapIdentical) );
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , EqualityCheckUsingFunctionWithNotIdenticalFail ) 
    {
        TBinaryHeap heapIdentical;
        heapIdentical.Emplace(99);

        EXPECT_FALSE( heap_.IsEqualTo<false>(heapIdentical) );
        EXPECT_FALSE( heapIdentical.IsEqualTo<false>(heap_) );
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , EqualityCheckUsingOperatorSuccess ) 
    {
        TBinaryHeap heapIdentical;
        EXPECT_TRUE( ( heap_ == heapIdentical ) );
        EXPECT_FALSE( ( heap_ != heapIdentical ) );
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , EqualityCheckUsingOperatorFail ) 
    {
        TBinaryHeap heapIdentical;
        heapIdentical.Emplace(99);

        EXPECT_FALSE( ( heap_ == heapIdentical ) );
        EXPECT_FALSE( ( heapIdentical == heap_ ) );
        EXPECT_TRUE( heap_ != heapIdentical);
        EXPECT_TRUE(heapIdentical != heap_);
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , EqualityCheckUsingFunctionWithIdenticalSuccess ) 
    {
        TBinaryHeap heapIdentical;
        EXPECT_TRUE( heap_.IsEqualTo<true>(heapIdentical) );
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , EqualityCheckUsingFunctionWithIdenticalFail ) 
    {
        TBinaryHeap heapIdentical;
        heapIdentical.Emplace(99);

        EXPECT_FALSE( heap_.IsEqualTo<true>(heapIdentical) );
        EXPECT_FALSE( heapIdentical.IsEqualTo<true>(heap_) );
    }
///@}

///@Name Add element check
///@{
    TEST_F  ( TestBinaryHeapWithZeroElements
            , OperatorAddElementZero ) 
    {
        TElement i  = 0; 
        heap_      += i;

        EXPECT_EQ( heap_.Size(), 1 );
        EXPECT_EQ( heap_.Top(),  0 );
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , OperatorAddElementOneUsingMoverInsertion ) 
    {
        heap_ += 1; // == heap_ += std::move(1);

        EXPECT_EQ( heap_.Size(), 1 );
        EXPECT_EQ( heap_.Top(),  1 );
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , AddElementUsingEmplace ) 
    {
        heap_.Emplace(99); 

        EXPECT_EQ( heap_.Size(), 1 );
        EXPECT_EQ( heap_.Top(), 99 );
        heap_.Maximize();
        EXPECT_EQ( heap_.Top(), 99 );
        heap_.Minimize();
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , AddElementUsingInsert ) 
    {
        heap_.Insert(99); 

        EXPECT_EQ( heap_.Size(), 1 );
        EXPECT_EQ( heap_.Top(), 99 );
        heap_.Maximize();
        EXPECT_EQ( heap_.Top(), 99 );
        heap_.Minimize();
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , BuildHeapWithEmptyVector ) 
    {
        TVector emptyElementVector;
        heap_.BuildWith ( emptyElementVector );

        EXPECT_EQ( heap_.Size(), 0 );
        EXPECT_TRUE( heap_.Empty() );
    }
///@}

///@Name Change key of an element
///@{
#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBinaryHeapWithZeroElementsDeathTest
            , DecreaseKeyDeathTest ) 
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "DecreaseKey"
                                                    , "index < Size\\(\\)" );
        
        TElement p = -1;

        ASSERT_DEATH( {heap_.DecreaseKey(0, p);}, assertionString ); 
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBinaryHeapWithZeroElements
            , DecreaseKeyExceptionHandling ) 
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "DecreaseKey"
                                                    , "index < Size\\(\\)" );
        TElement p = -1;

        try {
            heap_.DecreaseKey(0, p);
        } catch ( std::runtime_error const & error ) {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBinaryHeapWithZeroElementsDeathTest
            , ChangeKeyDeathTest ) 
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "ChangeKey"
                                                    , "index < Size\\(\\)");
        
        TElement p = -1;

        ASSERT_DEATH( {heap_.ChangeKey(0, p);}, assertionString ); 
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBinaryHeapWithZeroElements
            , ChangeKeyExceptionHandling ) 
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "ChangeKey"
                                                    , "index < Size\\(\\)");
        TElement p = -1;
        
        try {
            heap_.ChangeKey(0, p);
        } catch ( std::runtime_error const & error ) {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION
///@}

///@Name Change comparator
///@{
    TEST_F  ( TestBinaryHeapWithZeroElements
            , ComparatorChangeToLess ) 
    {   
        heap_.Comparator( []( TElement a, TElement b ) { return a < b; } );

        EXPECT_EQ ( heap_.Size(), 0 );
        EXPECT_TRUE ( heap_.Empty() );
        
        heap_.Emplace(1);

        EXPECT_EQ ( heap_.Size(), 1 );
        EXPECT_FALSE ( heap_.Empty() );
        EXPECT_EQ ( heap_.Top(), 1 );

        heap_.Emplace(1);

        EXPECT_EQ ( heap_.Size(), 2 );
        EXPECT_EQ ( heap_.Top(), 1 );
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , ComparatorChangeToGreater ) 
    {   
        heap_.Comparator([]( TElement a, TElement b ) { return a > b; });

        EXPECT_EQ ( heap_.Size(), 0 );
        EXPECT_TRUE ( heap_.Empty() );
        
        heap_.Emplace(55);

        EXPECT_EQ ( heap_.Size(), 1 );
        EXPECT_FALSE ( heap_.Empty() );
        EXPECT_EQ ( heap_.Top(), 55 );

        heap_.Emplace(55);

        EXPECT_EQ ( heap_.Size(), 2 );
        EXPECT_EQ ( heap_.Top(), 55 );
    }
///@}

///@Name Remove elements
///@{
#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBinaryHeapWithZeroElementsDeathTest
            , RemoveElementUsingPopDeathTest ) 
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "Pop"
                                                    , "Size\\(\\) > 0");
        ASSERT_DEATH( {heap_.Pop();}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBinaryHeapWithZeroElements
            , RemoveElementUsingPopExceptionHandling ) 
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "Pop"
                                                    , "Size\\(\\) > 0");
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

#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBinaryHeapWithZeroElementsDeathTest
            , RemoveElementUsingDeleteMinDeathTest ) 
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "DeleteTop"
                                                    , "Size\\(\\) > 0");

        ASSERT_DEATH( {heap_.DeleteTop();}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBinaryHeapWithZeroElements
            , RemoveElementUsingDeleteMinExceptionHandling ) 
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "DeleteTop"
                                                    , "Size\\(\\) > 0");
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

    TEST_F  ( TestBinaryHeapWithZeroElements
            , ClearHeap ) 
    {
        EXPECT_TRUE( heap_.Empty() );
        heap_.Clear();
        EXPECT_TRUE( heap_.Empty() );
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , SwapEmptyHeaps ) 
    {
        TBinaryHeap heapForSwapping;
        
        EXPECT_TRUE( heap_.Empty() );
        EXPECT_TRUE( heapForSwapping.Empty() );

        using std::swap;

        swap( heap_, heapForSwapping );

        EXPECT_EQ( heap_.IsEqualTo<false>(heapForSwapping), true );
        EXPECT_EQ( heap_.IsEqualTo<true>(heapForSwapping),  true );
        EXPECT_EQ( heapForSwapping.IsEqualTo<false>(heap_), true );
        EXPECT_EQ( heapForSwapping.IsEqualTo<true>(heap_),  true );
    }
///@}

///@Name Check iterators
///@{
    TEST_F  ( TestBinaryHeapWithZeroElements
            , OutputStream ) 
    {
        std::ostringstream os; 
        os << heap_;
        EXPECT_EQ( os.str(), "" );
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , HeapIteratorWithOstream ) 
    {
        std::ostringstream os;
        std::copy( heap_.begin(), heap_.end(), std::ostream_iterator<TElement>( os , "|" ) );
        EXPECT_EQ( os.str(), "" );
    }

    // @todo std::copy does not work
    // TEST_F  ( TestBinaryHeapWithZeroElements
    //         , HeapIteratorCopy ) 
    // {
        // TBinaryHeap heapForCopy;
        // std::copy( heap_.Begin(), heap_.End(), heapForCopy );
    // }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , IteratorSerialForAllElements ) 
    {
        heap_.for_all_elements<egoa::ExecutionPolicy::sequential> ( []( TElement & element ) {
            EXPECT_FALSE ( true );
        });
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , IteratorParallelForAllElements ) 
    {
        heap_.for_all_elements<egoa::ExecutionPolicy::parallel> ( []( TElement & element ) {
            EXPECT_FALSE ( true );
        });
    }

    TEST_F  ( TestBinaryHeapWithZeroElements
            , IteratorBreakableForAllElements ) 
    {
        heap_.for_all_elements<egoa::ExecutionPolicy::breakable> ( []( TElement & element ) -> bool {
            EXPECT_FALSE ( true );
            return true;
        });
    }
///@}

#pragma mark TEST_BINARY_HEAP_WITH_ONE_INT_ELEMENT

TEST_F  ( TestBinaryHeapWithOneIntegerElement
        , IsNoLongerEmpty ) 
{
    ASSERT_FALSE( heap_.Empty() );
}

TEST_F  ( TestBinaryHeapWithOneIntegerElement
        , HasSizeOfOne ) 
{
    ASSERT_THAT( heap_.Size(), Eq(1) );
}

TEST_F  ( TestBinaryHeapWithOneIntegerElement
        , CheckTopElement ) 
{
    ASSERT_EQ( heap_.Top(), 99 );
}

TEST_F  ( TestBinaryHeapWithOneIntegerElement
        , DeleteTop )
{
    auto top = heap_.DeleteTop();
    ASSERT_EQ( top, 99 );
    ASSERT_TRUE( heap_.Empty() );
}

TEST_F ( TestBinaryHeapWithOneIntegerElement,
         BuildHeapWithEmptyVector) {
    heap_.BuildWith({});
    EXPECT_TRUE(heap_.Empty());
}

TEST_F (TestBinaryHeapWithOneIntegerElement,
        InsertVector) {
    TVector vector = {5, 9, 102, 42};
    heap_.Insert(vector);
    ExpectContent(heap_, {5, 9, 42, 99, 102});
}

TEST_F (TestBinaryHeapWithOneIntegerElement,
        InsertVectorWithDuplicates) {
    TVector vector = {5, 99, 102, 5};
    heap_.Insert(vector);
    ExpectContent(heap_, {5, 5, 99, 99, 102});
}

TEST_F (TestBinaryHeapWithOneIntegerElement,
        InsertEmptyVector) {
    heap_.Insert(TVector{});
    ExpectContent(heap_, {99});
}

#pragma mark TEST_BINARY_HEAP_WITH_VECTOR_OF_INT_ELEMENTS

///@Name Basic Functionalities
///@{
    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , BasicFunctionalityIsNoLongerEmpty ) 
    {
        ASSERT_FALSE( heap_.Empty() );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , BasicFunctionalityHasSizeOfSeven ) 
    {
        ASSERT_THAT( heap_.Size(), Eq(7) );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , BasicFunctionalityCheckTopElement ) 
    {
        EXPECT_EQ( heap_.Top(), 1 );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , BasicFunctionalitySearchForElementFour ) 
    {
        EXPECT_EQ( heap_.Search(4), 5 );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , BasicFunctionalitySwitchToMaxHeapAndCheckTop ) 
    {
        heap_.Maximize();
        EXPECT_EQ( heap_.Top(), 55 );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , BasicFunctionalitySwitchToMinHeapAndCheckTop ) 
    {
        heap_.Minimize();
        EXPECT_EQ( heap_.Top(), 1 );
    }

    TEST_F ( TestBinaryHeapWithVectorOfInteger,
             BuildHeapWithEmptyVector) {
        heap_.BuildWith({});
        EXPECT_TRUE(heap_.Empty());
    }
///@}

///@Name Comparison check
///@{
    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , EqualityCheckUsingFunctionWithNotIdenticalSuccess ) 
    {
        TBinaryHeap heapIdentical;
        TVector     intVector = { 1, 2, 4, 5, 9, 23, 55};

        heapIdentical.BuildWith(intVector);
        
        EXPECT_TRUE ( heap_.IsEqualTo<false>(heapIdentical) );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , EqualityCheckUsingFunctionWithNotIdenticalFail ) 
    {
        TBinaryHeap heapIdentical;
        TVector     intVector = { 1, 3, 4, 5, 9, 23, 55};

        heapIdentical.BuildWith(intVector);
        
        EXPECT_FALSE ( heap_.IsEqualTo<false>(heapIdentical) );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , EqualityCheckUsingOperatorSuccess ) 
    {
        TBinaryHeap heapIdentical;
        TVector     intVector = { 1, 2, 4, 5, 9, 23, 55};

        heapIdentical.BuildWith(intVector);
        
        EXPECT_TRUE ( ( heap_ == heapIdentical ) );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , EqualityCheckUsingOperatorFail ) 
    {
        TBinaryHeap heapIdentical;
        TVector     intVector = { 1, 2, 4, 5, 55, 23, 55};

        heapIdentical.BuildWith(intVector);
        
        EXPECT_FALSE ( ( heap_ == heapIdentical ) );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , EqualityCheckUsingFunctionWithIdenticalSuccess ) 
    {
        TBinaryHeap heapIdentical;
        TVector     intVector = { 5, 9, 23, 55, 1, 4, 2};

        heapIdentical.BuildWith(intVector);
        
        EXPECT_TRUE ( heap_.IsEqualTo<true>(heapIdentical) );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , EqualityCheckUsingFunctionWithIdenticalFail ) 
    {
        TBinaryHeap heapIdentical;
        TVector     intVector = { 1, 2, 4, 5, 55, 23, 55};

        heapIdentical.BuildWith(intVector);
        
        EXPECT_FALSE ( heap_.IsEqualTo<true>(heapIdentical) );
    }
///@}

///@Name Add element check
///@{
    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , AddElementUsingOperator ) 
    {
        TElement i  = 0; 
        heap_      += i;

        EXPECT_EQ( heap_.Size(), 8 );
        EXPECT_EQ( heap_.Top(), 0 );
        EXPECT_EQ( heap_.Search(9), 4 );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , AddElementUsingMoverOperator ) 
    {
        heap_ += 1; // == heap_ += std::move(1);

        EXPECT_EQ( heap_.Size(), 8 );
        EXPECT_EQ( heap_.Top(), 1 );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , AddElementUsingEmplace ) 
    {
        heap_.Emplace(99); 

        EXPECT_EQ( heap_.Size(), 8 );
        EXPECT_EQ( heap_.Top(), 1 );
        heap_.Maximize();
        EXPECT_EQ( heap_.Top(), 99 );
        heap_.Minimize();
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , AddElementUsingInsert ) 
    {
        heap_.Insert(99); 

        EXPECT_EQ( heap_.Size(), 8 );
        EXPECT_EQ( heap_.Top(), 1 );
        heap_.Maximize();
        EXPECT_EQ( heap_.Top(), 99 );
        heap_.Minimize();
    }
///@}

///@Name Change key of an element
///@{
    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , DecreaseKey )
    {
        TElement p = -1;
        // Decrease key of element with key 23 at position 6 to element with key -1
        heap_.DecreaseKey(6, p); 

        EXPECT_EQ( heap_.Size(), 7 );
        EXPECT_EQ( heap_.Top(), -1 );
        EXPECT_EQ( heap_.Search(1), 2 );
        ExpectContent( heap_, {-1, 1, 2, 4, 5, 9, 55});
    }

    /**
     * Calls DecreaseKey with an index that is too large.
     */
#ifdef EGOA_ENABLE_ASSERTION
    TEST_F ( TestBinaryHeapWithVectorOfIntegerDeathTest
           , DecreaseKeyInvalidIndex)
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "DecreaseKey"
                                                    , "index < Size\\(\\)" );

        ASSERT_DEATH( {heap_.DecreaseKey(7, 123);}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBinaryHeapWithZeroElements
            , DecreaseKeyInvalidIndexExceptionHandling ) 
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap"
                                                    , "DecreaseKey"
                                                    , "index < Size\\(\\)" );
        try {
            heap_.DecreaseKey(7, 123);
        } catch ( std::runtime_error const & error ) {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , ChangeKeyDecrease )
    {
        TElement p = -1;
        // Decrease key of element with key 23 at position 6 to element with key -1
        heap_.ChangeKey(6, p); 

        EXPECT_EQ( heap_.Size(), 7 );
        EXPECT_EQ( heap_.Top(), -1 );
        EXPECT_EQ( heap_.Search(1), 2 );
        ExpectContent( heap_, {-1, 1, 2, 4, 5, 9, 55});
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , ChangeKeyIncrease )
    {
        TElement p = 42;
        // Decrease key of element with key 23 at position 6 to element with key 42
        heap_.ChangeKey(6, p); 

        EXPECT_EQ( heap_.Size(), 7 );
        ExpectContent(heap_, {1, 2, 4, 5, 9, 42, 55});
    }

     TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , ChangeKeyIncreaseMinimum )
    {
        TElement p = 42;
        // Decrease key of element with key 1 at position 0 to element with key 42
        heap_.ChangeKey(0, p); 

        EXPECT_EQ( heap_.Size(), 7 );
        ExpectContent(heap_, {2, 4, 5, 9, 23, 42, 55});
    }

#ifdef EGOA_ENABLE_ASSERTION
    TEST_F ( TestBinaryHeapWithVectorOfIntegerDeathTest
           , ChangeKeyInvalidIndex)
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap" 
                                                    , "ChangeKey"
                                                    , "index < Size\\(\\)");

        ASSERT_DEATH( {heap_.ChangeKey(7, 123);}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBinaryHeapWithZeroElements
            , ChangeKeyInvalidIndexExceptionHandling ) 
    {
        auto assertionString = buildAssertionString ( "BinaryHeap.hpp"
                                                    , "BinaryHeap" 
                                                    , "ChangeKey"
                                                    , "index < Size\\(\\)");
        try {
            heap_.ChangeKey(7, 123);
        } catch ( std::runtime_error const & error ) {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION
///@}

///@Name Change comparator
///@{
    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , ComparatorChangeToLess ) 
    {
        heap_.Comparator([]( TElement a, TElement b ) { return a < b; });

        EXPECT_EQ( heap_.Size(), 7 );
        EXPECT_EQ( heap_.Top(), 1 );

        heap_.Emplace(1);

        EXPECT_EQ( heap_.Size(), 8 );
        EXPECT_EQ( heap_.Top(), 1 );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , ComparatorChangeToGreater ) 
    {
        heap_.Comparator([]( TElement a, TElement b ) { return a > b; });

        EXPECT_EQ( heap_.Size(), 7 );
        EXPECT_EQ( heap_.Top(), 55 );

        heap_.Emplace(55);

        EXPECT_EQ( heap_.Size(), 8 );
        EXPECT_EQ( heap_.Top(), 55 );
    }
///@}

///@Name Remove elements
///@{
    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , RemoveElementUsingPop ) 
    {
        heap_.Minimize();
        heap_.Pop();

        EXPECT_EQ( heap_.Size(), 6 );
        EXPECT_EQ( heap_.Top(),  2 );

        heap_.Pop();
        EXPECT_EQ( heap_.Size(), 5 );
        EXPECT_EQ( heap_.Top(),  4 );    
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , RemoveElementUsingDeleteMin ) 
    {
        EXPECT_EQ( heap_.DeleteTop(), 1 );
        EXPECT_EQ( heap_.DeleteTop(), 2 );

        EXPECT_EQ( heap_.Size(), 5 );
        EXPECT_EQ( heap_.Top(),  4 );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , RemoveElementUsingClearHeap ) 
    {
        heap_.Clear();
        EXPECT_TRUE( heap_.Empty() );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , SwapHeaps ) 
    {
        TBinaryHeap heapForSwapping;
        TBinaryHeap heapForComparison;
        TVector     intVector = { 11, 33, 9, 69, 42, 99};

        heapForSwapping.BuildWith(intVector);

        EXPECT_EQ( heap_.Size(), 7 );
        EXPECT_EQ( heap_.Top(),  1 );
        EXPECT_EQ( heapForSwapping.Size(), 6 );
        EXPECT_EQ( heapForSwapping.Top(),  9 );

        using std::swap;

        swap( heap_, heapForSwapping );

        EXPECT_EQ( heap_.Size(), 6 );
        EXPECT_EQ( heap_.Top(),  9 );
        EXPECT_EQ( heapForSwapping.Size(), 7 );
        EXPECT_EQ( heapForSwapping.Top(),  1 );

        EXPECT_EQ( heap_.IsEqualTo<false>(heapForComparison), 0 );
    }
///@}

///@Name Check iterators
///@{
    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , HeapIteratorOutputStream ) 
    {
        std::ostringstream os; 
        os << heap_;
        EXPECT_EQ( os.str(), "1|5|2|55|9|4|23|" );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , HeapIteratorWithOstream ) 
    {
        std::ostringstream os;
        std::copy( heap_.begin(), heap_.end(), std::ostream_iterator<TElement>( os , "|" ) );
        EXPECT_EQ( os.str(), "1|5|2|55|9|4|23|" );
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , ForEachConst )
    {
        TVector intVector = { 1, 5, 2, 55, 9, 4, 23 };
        Types::count counter = 0;
        for (const TElement& element : heapConst_) {
            EXPECT_EQ( element, intVector[counter] );
            ++counter;
        }
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , IteratorIsAssignable )
    {
        auto it = heapConst_.begin();
        it = heapConst_.end();
        EXPECT_EQ(it, heapConst_.end());
    }

    // @todo std::copy does not work
    // TEST_F  ( TestBinaryHeapWithVectorOfInteger
    //         , HeapIteratorCopy ) 
    // {
        // egoa::BinaryHeap<int> heapForCopy;
        // std::copy( heap_.begin(), heap_.end(), heapForCopy );
        // for ( auto element : rhs )  os << std::setw(10) << element << "|";
    // }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , IteratorSerialForAllElements )
    {
        TVector intVector = { 1, 5, 2, 55, 9, 4, 23 };
        Types::count counter = 0;
        heap_.for_all_elements<egoa::ExecutionPolicy::sequential>( [&counter,&intVector]( TElement & element ) {
            EXPECT_EQ( element, intVector[counter] );
            ++counter;
        });
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , IteratorSerialForAllElementsConst )
    {
        TVector intVector = { 1, 5, 2, 55, 9, 4, 23 };
        Types::count counter = 0;
        heapConst_.for_all_elements<egoa::ExecutionPolicy::sequential>( [&counter,&intVector](const TElement & element ) {
            EXPECT_EQ( element, intVector[counter] );
            ++counter;
        });
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , IteratorParallelForAllElements ) 
    {
        // For more details see
        // https://gitlab.inria.fr/Phylophile/Treerecs/blob/f6551e06797b52819ba3e630b92315254a944da5/tests/gtest/googletest/docs/AdvancedGuide.md
        ::testing::FLAGS_gtest_death_test_style = "threadsafe";

#ifdef OPENMP_AVAILABLE
        TVector intVector = { 1, 5, 2, 55, 9, 4, 23 };
        Types::count numberOfThreads = Auxiliary::MaximumNumberOfThreads();
        EXPECT_GE( numberOfThreads, 0 );
        std::vector<Types::count>            numberOfElements ( numberOfThreads, 0 );
        std::vector< std::vector<TElement> > elementsLoopedOver ( numberOfThreads
                                                                , std::vector<TElement>() );

        heap_.for_all_elements<egoa::ExecutionPolicy::parallel>(   [ & numberOfThreads
                                        , & numberOfElements
                                        , & elementsLoopedOver ]( TElement & element ) {
            ++numberOfElements[ omp_get_thread_num() ];
            elementsLoopedOver[ omp_get_thread_num() ].emplace_back ( element );
        });
        Types::count sum = 0;
        for ( Types::count number : numberOfElements ) {
            sum += number;
        }
        EXPECT_EQ( sum, 7 );

        sum = 0;
        Types::count elementSum = 0;
        for ( auto & elementPerThread : elementsLoopedOver ) {
            sum += elementPerThread.size();
            for ( TElement & element : elementPerThread ) {
                elementSum += element;
                auto iter = std::find(intVector.begin(), intVector.end(), element );
                EXPECT_NE( iter, intVector.end() );
            }
        }
        EXPECT_EQ( sum, 7 );
        EXPECT_EQ( elementSum, 99 );

#endif // OPENMP_AVAILABLE
    }

    TEST_F  ( TestBinaryHeapWithVectorOfInteger
            , IteratorBreakableForAllElements ) 
    {
        TVector intVector = { 1, 5, 2, 55, 9, 4, 23 };
        Types::count counter = 0;
        heap_.for_all_elements<egoa::ExecutionPolicy::breakable> ( [&counter,&intVector]( TElement & element ) -> bool {
            EXPECT_EQ( element, intVector[counter] );
            if ( 9 == intVector[counter] ) { 
                return false; // break
            }
            ++counter;
            return true;
        });
        EXPECT_EQ( counter, 4 );
        EXPECT_EQ( intVector[counter], 9 );
    }
///@}

/// @name Test HeapIterator
/// @{
#pragma mark TEST_HEAP_ITERATOR

    TEST_F ( TestHeapIterator, CompareBeginIteratorsFromDifferentHeaps) {
        TBinaryHeap heap1;
        TBinaryHeap heap2;
        EXPECT_FALSE(heap1.begin() == heap2.begin());
        EXPECT_TRUE(heap1.begin() != heap2.begin());
    }

    TEST_F ( TestHeapIterator, CompareBeginIteratorsFromSameHeap) {
        TBinaryHeap heap;
        EXPECT_TRUE(heap.begin() == heap.begin());
        EXPECT_FALSE(heap.begin() != heap.begin());
    }

    TEST_F ( TestHeapIterator, CompareEndIteratorsFromDifferentHeaps) {
        TBinaryHeap heap1;
        TBinaryHeap heap2;
        EXPECT_FALSE(heap1.end() == heap2.end());
        EXPECT_TRUE(heap1.end() != heap2.end());
    }

    TEST_F ( TestHeapIterator, CompareEndIteratorsFromSameHeap) {
        TBinaryHeap heap;
        EXPECT_TRUE(heap.end() == heap.end());
        EXPECT_FALSE(heap.end() != heap.end());
    }

    TEST_F (TestHeapIterator, EmptyHeapBeginEqualsEnd) {
        TBinaryHeap heap;
        EXPECT_TRUE(heap.begin() == heap.end());
        EXPECT_FALSE(heap.begin() != heap.end());
    }

    TEST_F (TestHeapIterator, NonEmptyHeapBeginNotEqualToEnd) {
        EXPECT_FALSE(heap_.begin() == heap_.end());
        EXPECT_TRUE(heap_.begin() != heap_.end());
    }

    TEST_F (TestHeapIterator, IncrementUntilEnd) {
        auto size = heap_.Size();
        Types::count count = 0;
        for (auto it = heap_.begin(), end = heap_.end(); it != end; ++it) {
            ++count;
        }
        EXPECT_EQ(size, count);

        count = 0;
         for (auto it = heap_.begin(), end = heap_.end(); it != end; it++) {
            ++count;
        }
        EXPECT_EQ(size, count);
    }

    TEST_F (TestHeapIterator, DereferenceBegin) {
        auto it = heap_.begin();
        EXPECT_EQ(3, *it);
    }

    TEST_F (TestHeapIterator, PointerFromBegin) {
        egoa::BinaryHeap<Dummy> heap;

        Types::count counter = 0;
        heap.Emplace(&counter);
        ASSERT_EQ(1, heap.Size());

        auto it = heap.begin();
        it->Increment();
        EXPECT_EQ(1, counter);
    }


/// @}

} // namespace egoa::test
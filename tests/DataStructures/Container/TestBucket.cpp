/*
 * TestBucket.cpp
 *
 *  Created on: Feb 05, 2019
 *      Author: Franziska Wegner
 */

#include "TestBucket.hpp"
#include "Auxiliary/Types.hpp"
#include "Helper/TestHelper.hpp"

using ::testing::Eq;
using ::testing::MatchesRegex;

namespace egoa::test {

// ***********************************************************************
// ***********************************************************************
#pragma mark Empty Bucket
// ***********************************************************************
// ***********************************************************************
    TEST_F  ( TestBucketWithZeroElements
            , IsEmptyWhenCreated ) 
    {
        ASSERT_TRUE( bucket_.Empty() );
    }

    TEST_F  ( TestBucketWithZeroElements
            , HasSizeOfZero ) 
    {
        ASSERT_THAT( bucket_.Size(), Eq(0) );
    }

#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBucketWithZeroElementsDeathTest
            , CheckTopElementDeathTest ) 
    {
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket"
                                                    , "Top"
                                                    , "!EmptyQueue\\(\\)");
        ASSERT_DEATH ( {bucket_.Top();}, ".*" );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBucketWithZeroElements
            , CheckTopElementExceptionHandling ) 
    {
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket"
                                                    , "Top"
                                                    , "!EmptyQueue\\(\\)");
        try {
            bucket_.Top();
        } catch ( std::runtime_error const & error ) 
        {
            EXPECT_THAT ( error.what(), MatchesRegex(assertionString.c_str()) );
        } catch ( ... ) 
        {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION
    
///@Name Compare two empty buckets with <, >, <=, >= ... 
///@todo Check what happens if processed elements are empty but not unprocessed elements, can this even happening?
///@{
#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBucketWithZeroElementsDeathTest
            , CompareTwoEmptyBucketsLhsSmallerRhsDeathTest ) 
    {
        TBucket bucketToCompare_;
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket"
                                                    , "operator<"
                                                    , "!EmptyQueue\\(\\)");
        ASSERT_DEATH ( { auto test = bucket_ < bucketToCompare_;}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBucketWithZeroElements
            , CompareTwoEmptyBucketsLhsSmallerRhsExceptionHandling ) 
    {
        TBucket bucketToCompare_;
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket"
                                                    , "operator<"
                                                    , "!EmptyQueue\\(\\)");
        try {
            auto test = bucket_ < bucketToCompare_;
        } catch ( std::runtime_error const & error ) 
        {
            EXPECT_THAT ( error.what(), MatchesRegex(assertionString.c_str()) );
        } catch ( ... ) 
        {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBucketWithZeroElementsDeathTest
            , CompareTwoEmptyBucketsLhsSmallerEqualRhsDeathTest ) 
    {
        TBucket bucketToCompare_;
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket" 
                                                    , "operator<="
                                                    , "!EmptyQueue\\(\\)");
        ASSERT_DEATH ( { auto test = bucket_ <= bucketToCompare_;}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBucketWithZeroElements
            , CompareTwoEmptyBucketsLhsSmallerEqualRhsExceptionHandling ) 
    {
        TBucket bucketToCompare_;
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket" 
                                                    , "operator<="
                                                    , "!EmptyQueue\\(\\)");
        try {
            auto test = bucket_ <= bucketToCompare_;
        } catch ( std::runtime_error const & error ) 
        {
            EXPECT_THAT ( error.what(), MatchesRegex(assertionString.c_str()) );
        } catch ( ... ) 
        {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBucketWithZeroElementsDeathTest
            , CompareTwoEmptyBucketsLhsGreaterRhsDeathTest ) 
    {
        TBucket bucketToCompare_;
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket"
                                                    , "operator>"
                                                    , "!EmptyQueue\\(\\)");
        ASSERT_DEATH ( { auto test = bucket_ > bucketToCompare_;}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBucketWithZeroElements
            , CompareTwoEmptyBucketsLhsGreaterRhsExceptionHandling ) 
    {
        TBucket bucketToCompare_;
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket"
                                                    , "operator>"
                                                    , "!EmptyQueue\\(\\)");
        try {
            auto test = bucket_ > bucketToCompare_;
        } catch ( std::runtime_error const & error ) 
        {
            EXPECT_THAT ( error.what(), MatchesRegex(assertionString.c_str()) );
        } catch ( ... ) 
        {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBucketWithZeroElementsDeathTest
            , CompareTwoEmptyBucketsLhsGreaterEqualRhsDeathTest ) 
    {
        TBucket bucketToCompare_;
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket"
                                                    , "operator>="
                                                    , "!EmptyQueue\\(\\)");
        ASSERT_DEATH ( { auto test = bucket_ >= bucketToCompare_;}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBucketWithZeroElements
            , CompareTwoEmptyBucketsLhsGreaterEqualRhsExceptionHandling ) 
    {
        TBucket bucketToCompare_;
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket"
                                                    , "operator>="
                                                    , "!EmptyQueue\\(\\)");
        try {
            auto test = bucket_ >= bucketToCompare_;
        } catch ( std::runtime_error const & error ) 
        {
            EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) 
        {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION
///@}

// Merge an element into an empty bucket
TEST_F  ( TestBucketWithZeroElements
        , MergeAnElementIntoEmptyBucket ) 
{
    TElement element = TElement(2,false);
    
    ASSERT_EQ   ( bucket_.Size(), 0 );
    ASSERT_TRUE ( bucket_.Merge( element ) );
    ASSERT_TRUE ( element.Valid()   );
    ASSERT_EQ   ( bucket_.Size(), 1 );
}

TEST_F  ( TestBucketWithZeroElements
        , MergeAnElementIntoEmptyBucketConstReference )
{
    TElement element = TElement(2, false);
    TElement const & elementConst = element;

    ASSERT_EQ   ( bucket_.Size(), 0 );
    ASSERT_TRUE ( bucket_.Merge( elementConst ) );
    ASSERT_EQ   ( bucket_.Size(), 1 );
}

TEST_F  ( TestBucketWithZeroElements
        , MergeAnElementIntoEmptyBucketMove )
{
    TElement element = TElement(2, false);

    ASSERT_EQ   ( bucket_.Size(), 0 );
    ASSERT_TRUE ( bucket_.Merge( std::move(element) ) );
    ASSERT_EQ   ( bucket_.Size(), 1 );
}

///@Name Check Domination
///@{
    TEST_F  ( TestBucketWithZeroElements
            , DominationCheckStrictDominationOfToElements ) 
    {
        TElement element = TElement(2,false);
        
        ASSERT_EQ   ( bucket_.Size(), 0 );
        ASSERT_TRUE ( bucket_.Merge<DominationCriterion::strict>( element ) );
        ASSERT_TRUE ( element.Valid()   );
        ASSERT_EQ   ( bucket_.Size(), 1 );
    }

    TEST_F  ( TestBucketWithZeroElements
            , DominationCheckWeakDominationOfToElements ) 
    {
        TElement element = TElement(2,false);
        
        ASSERT_EQ   ( bucket_.Size(), 0 );
        ASSERT_TRUE ( bucket_.Merge<DominationCriterion::weak>( element ) );
        ASSERT_TRUE ( element.Valid()   );
        ASSERT_EQ   ( bucket_.Size(), 1 );
    }

    TEST_F  ( TestBucketWithZeroElements
            , DominationCheckNoneDominationOfToElements ) 
    {
        TElement element = TElement(2,false);
        
        ASSERT_EQ   ( bucket_.Size(), 0 );
        ASSERT_TRUE ( bucket_.Merge<DominationCriterion::none>( element ) );
        ASSERT_TRUE ( element.Valid()   );
        ASSERT_EQ   ( bucket_.Size(), 1 );
    }
///@}

///@Name Access elements
///@{
    TEST_F  ( TestBucketWithZeroElements
            , AccessElementHasElementAt ) 
    {
        ASSERT_FALSE ( bucket_.HasElementAt(0)  );
        ASSERT_FALSE ( bucket_.HasElementAt(1)  );
        ASSERT_FALSE ( bucket_.HasElementAt(-1) );
    }

#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBucketWithZeroElementsDeathTest
            , AccessElementElementAtDeathTest ) 
    {
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket" 
                                                    , "ElementAt"
                                                    , "HasElementAt\\(index\\)");
        ASSERT_DEATH ( {bucket_.ElementAt(0);},  assertionString );
        ASSERT_DEATH ( {bucket_.ElementAt(1);},  assertionString );
        ASSERT_DEATH ( {bucket_.ElementAt(-1);}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBucketWithZeroElements
            , AccessElementElementAtExceptionHandling ) 
    {
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket" 
                                                    , "ElementAt"
                                                    , "HasElementAt\\(index\\)");
        try {
            try {
                bucket_.ElementAt(0);
            } catch ( std::runtime_error const & error ) 
            {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
            }
            try {
                bucket_.ElementAt(1);
            } catch ( std::runtime_error const & error ) 
            {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
            }
            try {
                bucket_.ElementAt(-1);
            } catch ( std::runtime_error const & error ) 
            {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
            }
        } catch ( ... ) 
        {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBucketWithZeroElementsDeathTest
            , AccessElementWithBracketOperatorDeathTest ) 
    {
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket" 
                                                    , "operator\\[\\]"
                                                    , "HasElementAt\\(index\\)");
        ASSERT_DEATH ( {bucket_[0];},  assertionString );
        ASSERT_DEATH ( {bucket_[1];},  assertionString );
        ASSERT_DEATH ( {bucket_[-1];}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBucketWithZeroElements
            , AccessElementWithBracketOperatorExceptionHandling ) 
    {
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket" 
                                                    , "operator\\[\\]"
                                                    , "HasElementAt\\(index\\)");
        try {
            try {
                bucket_[0];
            } catch ( std::runtime_error const & error ) 
            {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
            }
            try {
                bucket_[1];
            } catch ( std::runtime_error const & error ) 
            {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
            }
            try {
                bucket_[-1];
            } catch ( std::runtime_error const & error ) 
            {
                EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
            }
        } catch ( ... ) 
        {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION
///@}

///@Name Access bucket's top element
///@{
#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBucketWithZeroElementsDeathTest
            , AccessElementTopDeathTest ) 
    {
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket" 
                                                    , "Top"
                                                    , "!EmptyQueue\\(\\)");
        EXPECT_TRUE  ( bucket_.EmptyQueue() );
        ASSERT_DEATH ( {bucket_.Top();}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBucketWithZeroElements
            , AccessElementTopExceptionHandling ) 
    {
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket" 
                                                    , "Top"
                                                    , "!EmptyQueue\\(\\)");
        EXPECT_TRUE  ( bucket_.EmptyQueue() );
        try {
            bucket_.Top();
        } catch ( std::runtime_error const & error ) 
        {
            EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) 
        {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

    TEST_F  ( TestBucketWithZeroElements
            , AccessElementOptima ) 
    {
        bucket_.Optima();;
    }
///@}

///@Name Delete Elements
///@{
#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBucketWithZeroElementsDeathTest
            , RemoveElementUsingPopDeathTest ) 
    {
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket"
                                                    , "Pop"
                                                    , "!EmptyQueue\\(\\)" );
        ASSERT_DEATH ( {bucket_.Pop();}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBucketWithZeroElements
            , RemoveElementUsingPopExceptionHandling ) 
    {
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket"
                                                    , "Pop"
                                                    , "!EmptyQueue\\(\\)" );
        try {
            bucket_.Pop();
        } catch ( std::runtime_error const & error ) 
        {
            EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) 
        {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBucketWithZeroElementsDeathTest
            , RemoveElementUsingDeleteMinDeathTest ) 
    {
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket" 
                                                    , "DeleteTop" 
                                                    , "!EmptyQueue\\(\\)" );
        ASSERT_DEATH ( {bucket_.DeleteTop();}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBucketWithZeroElements
            , RemoveElementUsingDeleteMinExceptionHandling ) 
    {
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket" 
                                                    , "DeleteTop" 
                                                    , "!EmptyQueue\\(\\)" );
        try {
            bucket_.DeleteTop();
        } catch ( std::runtime_error const & error ) 
        {
            EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) 
        {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

    TEST_F  ( TestBucketWithZeroElements
            , RemoveElementAll ) 
    {
        bucket_.Clear();
        EXPECT_EQ   ( bucket_.Size(), 0 );
        EXPECT_TRUE ( bucket_.Empty()   );
    }
///@}

///@Name Empty
///@{
    TEST_F  ( TestBucketWithZeroElements
            , EmptyIsEmpty ) 
    {
        EXPECT_TRUE ( bucket_.Empty() );
    }

    TEST_F  ( TestBucketWithZeroElements
            , EmptyHasEmptyQueue ) 
    {
        EXPECT_TRUE ( bucket_.EmptyQueue() );
    }

    TEST_F  ( TestBucketWithZeroElements
            , EmptyIsSizeZero ) 
    {
        EXPECT_EQ   ( bucket_.Size(), 0 );
        EXPECT_TRUE ( bucket_.EmptyQueue() );
        EXPECT_TRUE ( bucket_.Empty() );
    }
///@}

///@Name Iterators
///@{
    TEST_F  ( TestBucketWithZeroElements
            , IteratorSerialForAllElements ) 
    {
        bucket_.for_all_elements<egoa::ExecutionPolicy::sequential> ( 
            []( TElement & element ) 
            {
                EXPECT_FALSE ( true );
            }
        );
    }

    TEST_F  ( TestBucketWithZeroElements
            , IteratorParallelForAllElements ) 
    {
        bucket_.for_all_elements<egoa::ExecutionPolicy::parallel> ( 
            []( TElement & element ) 
            {
                EXPECT_FALSE ( true );
            }
        );
    }

    TEST_F  ( TestBucketWithZeroElements
            , IteratorBreakableForAllElements ) 
    {
        bucket_.for_all_elements<egoa::ExecutionPolicy::breakable> ( 
            []( TElement & element ) -> bool 
            {
                EXPECT_FALSE ( true );
                return true;
            }
        );
    }

    TEST_F  ( TestBucketWithZeroElements
            , IteratorSerialForAllProcessedElements ) 
    {
        bucket_.for_all_processed_elements<egoa::ExecutionPolicy::sequential> ( 
            []( TElement & element ) 
            {
                EXPECT_FALSE ( true );
            }
        );
    }

    TEST_F  ( TestBucketWithZeroElements
            , IteratorParallelForAllProcessedElements ) 
    {
        bucket_.for_all_processed_elements<egoa::ExecutionPolicy::parallel> ( 
            []( TElement & element ) 
            {
                EXPECT_FALSE ( true );
            }
        );
    }

    TEST_F  ( TestBucketWithZeroElements
            , IteratorBreakableForAllProcessedElements ) 
    {
        bucket_.for_all_processed_elements<egoa::ExecutionPolicy::breakable> ( 
            []( TElement & element ) -> bool 
            {
                EXPECT_FALSE ( true );
                return true;
            }
        );
    }

    TEST_F  ( TestBucketWithZeroElements
            , IteratorSerialForAllUnprocessedElements ) 
    {
        bucket_.for_all_unprocessed_elements<egoa::ExecutionPolicy::sequential> ( 
            []( TElement & element ) 
            {
                EXPECT_FALSE ( true );
            }
        );
    }

    TEST_F  ( TestBucketWithZeroElements
            , IteratorParallelForAllUnprocessedElements ) 
    {
        bucket_.for_all_processed_elements<egoa::ExecutionPolicy::parallel> ( 
            []( TElement & element ) 
            {
                EXPECT_FALSE ( true );
            }
        );
    }

    TEST_F  ( TestBucketWithZeroElements
            , IteratorBreakableForAllUnprocessedElements ) 
    {
        bucket_.for_all_processed_elements<egoa::ExecutionPolicy::breakable> ( 
            []( TElement & element ) -> bool 
            {
                EXPECT_FALSE ( true );
                return true;
            }
        );
    }

    TEST_F  ( TestBucketWithZeroElements
            , IteratorSerialForAllOptima ) 
    {
        // For more details see
        // https://gitlab.inria.fr/Phylophile/Treerecs/blob/f6551e06797b52819ba3e630b92315254a944da5/tests/gtest/googletest/docs/AdvancedGuide.md
        ::testing::FLAGS_gtest_death_test_style = "threadsafe";

        bucket_.for_all_optima<egoa::ExecutionPolicy::sequential> (
            []( TElement const & element ) 
            {
                FAIL();
            }
        );
    }

    TEST_F  ( TestBucketWithZeroElements
            , IteratorParallelForAllOptima ) 
    {
        // For more details see
        // https://gitlab.inria.fr/Phylophile/Treerecs/blob/f6551e06797b52819ba3e630b92315254a944da5/tests/gtest/googletest/docs/AdvancedGuide.md
        ::testing::FLAGS_gtest_death_test_style = "threadsafe";

        bucket_.for_all_optima<egoa::ExecutionPolicy::parallel> (
            []( TElement const & element ) 
            {
                EXPECT_FALSE ( true );
            }
        );
    }

    /// @todo Test for breakable for_all_optima
///@}

// ***********************************************************************
// ***********************************************************************
#pragma mark Bucket with vector of int elements
// ***********************************************************************
// ***********************************************************************
///@Name Compare two empty buckets with <, >, <=, >= ... 
///@todo Check what happens if processed elements are empty but not unprocessed elements, can this even happening?
///@{
#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBucketWithMultipleIntegerDeathTest
            , CompareTwoBucketsWhereOneIsEmptyLhsSmallerRhsDeathTest ) 
    {
        // For more details see
        // https://gitlab.inria.fr/Phylophile/Treerecs/blob/f6551e06797b52819ba3e630b92315254a944da5/tests/gtest/googletest/docs/AdvancedGuide.md
        ::testing::FLAGS_gtest_death_test_style = "threadsafe";
        
        TBucket bucketToCompare_;
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket" 
                                                    , "operator<"
                                                    , "!rhs.EmptyQueue\\(\\)" );
        ASSERT_DEATH ( { auto test = bucket_ < bucketToCompare_;}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBucketWithMultipleInteger
            , CompareTwoBucketsWhereOneIsEmptyLhsSmallerRhsExceptionHandling ) 
    {
        TBucket bucketToCompare_;
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket" 
                                                    , "operator<"
                                                    , "!rhs.EmptyQueue\\(\\)" );
        try {
            auto test = bucket_ < bucketToCompare_;
        } catch ( std::runtime_error const & error ) 
        {
            EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) 
        {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

#ifdef EGOA_ENABLE_ASSERTION
    TEST_F  ( TestBucketWithMultipleIntegerDeathTest
            , CompareTwoEmptyBucketsLhsSmallerEqualRhsDeathTest ) 
    {
        // For more details see
        // https://gitlab.inria.fr/Phylophile/Treerecs/blob/f6551e06797b52819ba3e630b92315254a944da5/tests/gtest/googletest/docs/AdvancedGuide.md
        ::testing::FLAGS_gtest_death_test_style = "threadsafe";

        TBucket bucketToCompare_;
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket" 
                                                    , "operator<="
                                                    , "!rhs.EmptyQueue\\(\\)" );
        ASSERT_DEATH ( { auto test = bucket_ <= bucketToCompare_;}, assertionString );
    }
#else
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    TEST_F  ( TestBucketWithMultipleInteger
            , CompareTwoEmptyBucketsLhsSmallerEqualRhsExceptionHandling ) 
    {
        TBucket bucketToCompare_;
        auto assertionString = buildAssertionString ( "Bucket.hpp"
                                                    , "Bucket" 
                                                    , "operator<="
                                                    , "!rhs.EmptyQueue\\(\\)" );
        try {
            auto test = bucket_ <= bucketToCompare_;
        } catch ( std::runtime_error const & error ) {
            EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
        } catch ( ... ) {
            FAIL()  << "Expected std::runtime_error with message: " 
                    << assertionString;
        }
    }
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

// #ifdef EGOA_ENABLE_ASSERTION
//     TEST_F  ( TestBucketWithMultipleIntegerDeathTest
//             , CompareTwoEmptyBucketsLhsGreaterRhsDeathTest ) 
//     {
//         // For more details see
//         // https://gitlab.inria.fr/Phylophile/Treerecs/blob/f6551e06797b52819ba3e630b92315254a944da5/tests/gtest/googletest/docs/AdvancedGuide.md
//         ::testing::FLAGS_gtest_death_test_style = "threadsafe";

//         TBucket bucketToCompare_;
//         auto assertionString = buildAssertionString ( "Bucket.hpp"
//                                                     , "Bucket"
//                                                     , "operator>" 
//                                                     , "!rhs.EmptyQueue\\(\\)" );
//         ASSERT_DEATH ( { auto test = bucket_ > bucketToCompare_;}
//                      , assertionString );
//     }
// #else
// #ifdef EGOA_ENABLE_EXCEPTION_HANDLING
//     TEST_F  ( TestBucketWithMultipleInteger
//             , CompareTwoEmptyBucketsLhsGreaterRhsExceptionHandling ) 
//     {
//         TBucket bucketToCompare_;
//         auto assertionString = buildAssertionString ( "Bucket.hpp"
//                                                     , "Bucket"
//                                                     , "operator>" 
//                                                     , "!rhs.EmptyQueue\\(\\)" );
//         try {
//             auto test = bucket_ > bucketToCompare_;
//         } catch ( std::runtime_error const & error ) 
//         {
//             EXPECT_THAT ( MatchesRegex( assertionString.c_str() )
//                         , error.what() );
//         } catch ( ... ) 
//         {
//             FAIL()  << "Expected std::runtime_error with message: " 
//                     << assertionString;
//         }
//     }
// #endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
// #endif // ifdef EGOA_ENABLE_ASSERTION

// #ifdef EGOA_ENABLE_ASSERTION
//     TEST_F  ( TestBucketWithMultipleIntegerDeathTest
//             , CompareTwoEmptyBucketsLhsGreaterEqualRhsDeathTest ) 
//     {
//         // For more details see
//         // https://gitlab.inria.fr/Phylophile/Treerecs/blob/f6551e06797b52819ba3e630b92315254a944da5/tests/gtest/googletest/docs/AdvancedGuide.md
//         ::testing::FLAGS_gtest_death_test_style = "threadsafe";

//         TBucket bucketToCompare_;

//         auto assertionString = buildAssertionString ( "Bucket.hpp"
//                                                     , "Bucket"
//                                                     , "operator>="
//                                                     , "!rhs.EmptyQueue\\(\\)");
//         ASSERT_DEATH ( { auto test = bucket_ >= bucketToCompare_;}
//                      , assertionString );
//     }
// #else
// #ifdef EGOA_ENABLE_EXCEPTION_HANDLING
//     TEST_F  ( TestBucketWithMultipleInteger
//             , CompareTwoEmptyBucketsLhsGreaterEqualRhsExceptionHandling ) 
//     {
//         TBucket bucketToCompare_;
//         auto assertionString = buildAssertionString ( "Bucket.hpp"
//                                                     , "Bucket"
//                                                     , "operator>="
//                                                     , "!rhs.EmptyQueue\\(\\)");
//         try {
//             auto test = bucket_ >= bucketToCompare_;
//         } catch ( std::runtime_error const & error ) 
//         {
//             EXPECT_THAT ( MatchesRegex( assertionString.c_str() )
//                         , error.what() );
//         } catch ( ... ) 
//         {
//             FAIL()  << "Expected std::runtime_error with message: " 
//                     << assertionString;
//         }
//     }
// #endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
// #endif // ifdef EGOA_ENABLE_ASSERTION
///@}

// Merge an element into an empty bucket
TEST_F  ( TestBucketWithMultipleInteger
        , MergeANewElementIntoTheBucketStdMergeCorrespondsToDominatesWeakly ) 
{
    TElement elementDominated = TElement ( 2, false );
    TElement elementMergable  = TElement ( 0, false );
    
    ASSERT_EQ    ( bucket_.Size(), 1 );

    ASSERT_FALSE ( bucket_.Merge( elementDominated ) );
    ASSERT_FALSE ( elementDominated.Valid()          );

    ASSERT_TRUE  ( bucket_.Merge( elementMergable )  );
    ASSERT_TRUE  ( elementMergable.Valid()           );

    ASSERT_EQ    ( bucket_.Size(), 1 );
}

///@Name Check Domination
///@{
    TEST_F  ( TestBucketWithMultipleInteger
            , DominationCheckStrictDominationOfToElements ) 
    {
        TElement elementNotMergable = TElement ( 2, false );
        TElement elementMergable    = TElement ( 1, false );
        
        ASSERT_EQ   ( bucket_.Size(), 1 );
        ASSERT_FALSE( bucket_.Merge<DominationCriterion::strict>( elementNotMergable ) );
        ASSERT_FALSE( elementNotMergable.Valid()   );
        ASSERT_EQ   ( bucket_.Size(), 1 );
        ASSERT_TRUE ( bucket_.Merge<DominationCriterion::strict>( elementMergable ) );
        ASSERT_TRUE ( elementMergable.Valid()   );
        ASSERT_EQ   ( bucket_.Size(), 2 );
    }

    TEST_F  ( TestBucketWithMultipleInteger
            , DominationCheckWeakDominationOfToElements ) 
    {
        TElement elementNotMergable = TElement ( 1, false );
        TElement elementMergable    = TElement ( 0, false );
        
        ASSERT_EQ    ( bucket_.Size(), 1 );
        ASSERT_FALSE ( bucket_.Merge<DominationCriterion::weak>( elementNotMergable ) );
        ASSERT_FALSE ( elementNotMergable.Valid()   );
        ASSERT_EQ    ( bucket_.Size(), 1 );
        ASSERT_TRUE  ( bucket_.Merge<DominationCriterion::weak>( elementMergable ) );
        ASSERT_TRUE  ( elementMergable.Valid()   );
        ASSERT_EQ    ( bucket_.Size(), 1 );
    }

    TEST_F  ( TestBucketWithMultipleInteger
            , DominationCheckNoneDominationOfToElements ) 
    {
        TElement element = TElement ( 99, false );
        
        ASSERT_EQ   ( bucket_.Size(), 1 );
        ASSERT_TRUE ( bucket_.Merge<DominationCriterion::none>( element ) );
        ASSERT_TRUE ( element.Valid()   );
        ASSERT_EQ   ( bucket_.Size(), 2 );
    }
///@}

///@Name Access elements
///@{
    TEST_F  ( TestBucketWithMultipleInteger
            , AccessElementHasElementAt ) 
    {
        ASSERT_FALSE ( bucket_.HasElementAt(0)    );
        ASSERT_FALSE ( bucket_.HasElementAt(-1)   );
        bucket_.Pop();
        ASSERT_TRUE  ( bucket_.HasElementAt(0)    );
        ASSERT_EQ    ( bucket_.HasElementAt(0), 1 );
    }

// #ifdef EGOA_ENABLE_ASSERTION
//     TEST_F  ( TestBucketWithMultipleIntegerDeathTest
//             , AccessElementElementAtDeathTest ) 
//     {
//         // For more details see
//         // https://gitlab.inria.fr/Phylophile/Treerecs/blob/f6551e06797b52819ba3e630b92315254a944da5/tests/gtest/googletest/docs/AdvancedGuide.md
//         ::testing::FLAGS_gtest_death_test_style = "threadsafe";

//         auto assertionString = buildAssertionString ( "Bucket.hpp"
//                                                     , "Bucket" 
//                                                     , "ElementAt"
//                                                     , "HasElementAt\\(index\\)" );

//         ASSERT_DEATH ( {bucket_.ElementAt(0);},  assertionString );
//         ASSERT_DEATH ( {bucket_.ElementAt(1);},  assertionString );
//         ASSERT_DEATH ( {bucket_.ElementAt(-1);}, assertionString );

//         ASSERT_FALSE ( bucket_.HasElementAt(0)    );
//         ASSERT_FALSE ( bucket_.HasElementAt(-1)   );
//         bucket_.Pop();
//         ASSERT_TRUE  ( bucket_.HasElementAt(0)    );
//         ASSERT_EQ    ( bucket_.HasElementAt(0), 1 );
//         EXPECT_TRUE  ( bucket_.EmptyQueue()       );

//         auto assertionString2 = buildAssertionString ( "Bucket.hpp"
//                                                      , "Bucket" 
//                                                      , "Pop"
//                                                      , "!EmptyQueue\\(\\)" );
//         ASSERT_DEATH ( {bucket_.Pop();}, assertionString2 );
//     }
// #else
// #ifdef EGOA_ENABLE_EXCEPTION_HANDLING
//     TEST_F  ( TestBucketWithMultipleInteger
//             , AccessElementElementAtExceptionHandling ) 
//     {
//         auto assertionString = buildAssertionString ( "Bucket.hpp"
//                                                     , "Bucket" 
//                                                     , "ElementAt"
//                                                     , "HasElementAt\\(index\\)" );
//         try {
//             try {
//                 bucket_.ElementAt(0);
//             } catch ( std::runtime_error const & error ) 
//             {
//                 EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
//             }
//             try {
//                 bucket_.ElementAt(1);
//             } catch ( std::runtime_error const & error ) 
//             {
//                 EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
//             }
//             try {
//                 bucket_.ElementAt(-1);
//             } catch ( std::runtime_error const & error ) 
//             {
//                 EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
//             }

//             ASSERT_FALSE ( bucket_.HasElementAt(0)    );
//             ASSERT_FALSE ( bucket_.HasElementAt(-1)   );
//             bucket_.Pop();
//             ASSERT_TRUE  ( bucket_.HasElementAt(0)    );
//             ASSERT_EQ    ( bucket_.HasElementAt(0), 1 );
//             EXPECT_TRUE  ( bucket_.EmptyQueue()       );

//             auto assertionString2 = buildAssertionString ( "Bucket.hpp"
//                                                          , "Bucket" 
//                                                          , "Pop"
//                                                          , "!EmptyQueue\\(\\)" );
//             try {
//                 bucket_.Pop();
//             } catch ( std::runtime_error const & error ) 
//             {
//                 EXPECT_THAT ( MatchesRegex( assertionString2.c_str() ) 
//                             , error.what() );
//             }
//         } catch ( ... ) 
//         {
//             FAIL()  << "Expected std::runtime_error with message: " 
//                     << assertionString;
//         }
//     }
// #endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
// #endif // ifdef EGOA_ENABLE_ASSERTION

// #ifdef EGOA_ENABLE_ASSERTION
//     TEST_F  ( TestBucketWithMultipleIntegerDeathTest
//             , AccessElementWithBracketOperatorDeathTest ) 
//     {
//         // For more details see
//         // https://gitlab.inria.fr/Phylophile/Treerecs/blob/f6551e06797b52819ba3e630b92315254a944da5/tests/gtest/googletest/docs/AdvancedGuide.md
//         ::testing::FLAGS_gtest_death_test_style = "threadsafe";
        
//         auto assertionString = buildAssertionString ( "Bucket.hpp"
//                                                     , "Bucket"
//                                                     , "operator\\[\\]"
//                                                     , "HasElementAt\\(index\\)" );

//         ASSERT_DEATH ( { bucket_[0];  }, assertionString );
//         ASSERT_DEATH ( { bucket_[1];  }, assertionString );
//         ASSERT_DEATH ( { bucket_[-1]; }, assertionString );
//     }
// #else
// #ifdef EGOA_ENABLE_EXCEPTION_HANDLING
//     TEST_F  ( TestBucketWithMultipleInteger
//             , AccessElementWithBracketOperatorExceptionHandling ) 
//     {
//         auto assertionString = buildAssertionString ( "Bucket.hpp"
//                                                     , "Bucket"
//                                                     , "operator\\[\\]"
//                                                     , "HasElementAt\\(index\\)" );
//         try {
//             try {
//                 bucket_[0];
//             } catch ( std::runtime_error const & error ) 
//             {
//                 EXPECT_THAT ( error.what(), MatchesRegex( assertionString.c_str() ) );
//             }
//             try {
//                 bucket_[1];
//             } catch ( std::runtime_error const & error ) 
//             {
//                 EXPECT_THAT ( MatchesRegex( assertionString.c_str() )
//                             , error.what() );
//             }
//             try {
//                 bucket_[-1];
//             } catch ( std::runtime_error const & error ) 
//             {
//                 EXPECT_THAT ( MatchesRegex( assertionString.c_str() ) 
//                             , error.what() );
//             }
//         } catch ( ... ) 
//         {
//             FAIL()  << "Expected std::runtime_error with message: " 
//                     << assertionString;
//         }
//     }
// #endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
// #endif // ifdef EGOA_ENABLE_ASSERTION
// ///@}

///@Name Access bucket's top element
///@{
    TEST_F  ( TestBucketWithMultipleInteger
            , AccessElementTop ) 
    {
        EXPECT_FALSE ( bucket_.EmptyQueue() );
        EXPECT_EQ    ( bucket_.Top(), 1 );
    }

    TEST_F  ( TestBucketWithMultipleInteger
            , AccessElementOptima ) 
    {
        TElement element1 ( 1 ); 
        TElement element2 ( 1 ); 

        bucket_.Merge<DominationCriterion::strict>( element1 );
        bucket_.Merge<DominationCriterion::strict>( element2 );

        std::vector<TElement> optima = bucket_.Optima();
        ASSERT_EQ ( 3, optima.size() );
        
        for ( Types::count counter = 0
            ; counter < optima.size()
            ; ++counter ) 
        {
            ASSERT_EQ ( optima[counter], 1 );
        }
    }
///@}

///@Name Delete Elements
///@{
// #ifdef EGOA_ENABLE_ASSERTION
//     TEST_F  ( TestBucketWithMultipleIntegerDeathTest
//             , RemoveElementUsingPopDeathTest ) 
//     {
//         bucket_.Pop();
//         ASSERT_TRUE  ( bucket_.HasElementAt(0)    );
//         ASSERT_EQ    ( 1, bucket_.HasElementAt(0) );
        
//         ASSERT_TRUE ( bucket_.EmptyQueue() );

//         auto assertionString = buildAssertionString ( "Bucket.hpp"
//                                                     , "Bucket" 
//                                                     , "Pop"
//                                                     , "!EmptyQueue\\(\\)" );
//         ASSERT_DEATH ( {bucket_.Pop();}, assertionString );

//         bucket_.template for_all_processed_elements<egoa::ExecutionPolicy::sequential>( 
//             []( TElement const & element ) 
//             {
//                 ASSERT_TRUE ( element.Valid() );
//             }
//         );
//     }
// #else
// #ifdef EGOA_ENABLE_EXCEPTION_HANDLING
//     TEST_F  ( TestBucketWithMultipleInteger
//             , RemoveElementUsingPopExceptionHandling ) 
//     {
//         bucket_.Pop();
//         ASSERT_TRUE  ( bucket_.HasElementAt(0)    );
//         ASSERT_EQ    ( 1, bucket_.HasElementAt(0) );
        
//         ASSERT_TRUE ( bucket_.EmptyQueue() );

//         auto assertionString = buildAssertionString ( "Bucket.hpp"
//                                                     , "Bucket" 
//                                                     , "Pop"
//                                                     , "!EmptyQueue\\(\\)" );
//         try {
//             bucket_.Pop();
//         } catch ( std::runtime_error const & error ) 
//         {
//                 EXPECT_THAT ( MatchesRegex( assertionString.c_str() )
//                             , error.what() );
//         } catch ( ... ) 
//         {
//             FAIL()  << "Expected std::runtime_error with message: " 
//                     << assertionString;
//         }

//         bucket_.template for_all_processed_elements<egoa::ExecutionPolicy::sequential>( 
//             []( TElement const & element ) 
//             {
//                 ASSERT_TRUE ( element.Valid() );
//             }
//         );
//     }
// #endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
// #endif // ifdef EGOA_ENABLE_ASSERTION

// #ifdef EGOA_ENABLE_ASSERTION
//     TEST_F  ( TestBucketWithMultipleIntegerDeathTest
//             , RemoveElementUsingDeleteMinDeathTest ) 
//     {
//         // For more details see
//         // https://gitlab.inria.fr/Phylophile/Treerecs/blob/f6551e06797b52819ba3e630b92315254a944da5/tests/gtest/googletest/docs/AdvancedGuide.md
//         ::testing::FLAGS_gtest_death_test_style = "threadsafe";

//         auto       tuple = bucket_.DeleteTop();
//         TElement element = std::get<0>(tuple);
//         ASSERT_EQ    ( element,                 1 );
//         ASSERT_TRUE ( element.Valid() );
//         ASSERT_TRUE  ( bucket_.HasElementAt(0)    );
//         ASSERT_EQ    ( bucket_.ElementAt(0),    1 );
//         EXPECT_TRUE  ( bucket_.EmptyQueue()       );

//         auto assertionString = buildAssertionString ( "Bucket.hpp"
//                                                     , "Bucket"
//                                                     , "DeleteTop"
//                                                     , "!EmptyQueue\\(\\)" );
//         ASSERT_DEATH ( {bucket_.DeleteTop();}, assertionString );

//         bucket_.template for_all_processed_elements<egoa::ExecutionPolicy::sequential>( 
//             []( TElement const & element ) 
//             {
//                 ASSERT_TRUE ( element.Valid() );
//             }
//         );
//     }
// #else
// #ifdef EGOA_ENABLE_EXCEPTION_HANDLING
//     TEST_F  ( TestBucketWithMultipleInteger
//             , RemoveElementUsingDeleteMinExceptionHandling ) 
//     {
//         auto       tuple = bucket_.DeleteTop();
//         TElement element = std::get<0>(tuple);
//         ASSERT_EQ   ( element,                1 );
//         ASSERT_TRUE ( element.Valid()           );
//         ASSERT_TRUE ( bucket_.HasElementAt(0)   );
//         ASSERT_EQ   ( bucket_.ElementAt(0),   1 );
//         EXPECT_TRUE ( bucket_.EmptyQueue()      );

//         auto assertionString = buildAssertionString ( "Bucket.hpp"
//                                                     , "Bucket"
//                                                     , "DeleteTop"
//                                                     , "!EmptyQueue\\(\\)" );
//         try {
//             bucket_.DeleteTop();
//         } catch ( std::runtime_error const & error ) 
//         {
//                 EXPECT_THAT ( MatchesRegex( assertionString.c_str() )
//                             , error.what() );
//         } catch ( ... ) 
//         {
//             FAIL()  << "Expected std::runtime_error with message: " 
//                     << assertionString;
//         }

//         bucket_.template for_all_processed_elements<egoa::ExecutionPolicy::sequential>( 
//             []( TElement const & element ) 
//             {
//                 ASSERT_TRUE ( element.Valid() );
//             }
//         );
//     }
// #endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
// #endif // ifdef EGOA_ENABLE_ASSERTION

    TEST_F  ( TestBucketWithMultipleInteger
            , RemoveElementAll ) 
    {
        bucket_.Clear();
        EXPECT_EQ   ( bucket_.Size(), 0 );
        EXPECT_TRUE ( bucket_.Empty()   );
    }

    TEST_F  ( TestBucketWithMultipleInteger
            , RemoveElementAllWithPrecedingPop ) 
    {
        bucket_.Pop();
        bucket_.Clear();
        EXPECT_EQ   ( bucket_.Size(), 0 );
        EXPECT_TRUE ( bucket_.Empty()   );
    }
///@}

///@Name Empty and size check
///@{
    TEST_F  ( TestBucketWithMultipleInteger
            , IsEmpty ) 
    {
        EXPECT_FALSE ( bucket_.Empty() );
    }

    TEST_F  ( TestBucketWithMultipleInteger
            , HasEmptyQueue ) 
    {
        EXPECT_FALSE ( bucket_.EmptyQueue() );
    }

    TEST_F  ( TestBucketWithMultipleInteger
            , HaseCorrectSize ) 
    {
        EXPECT_EQ   ( bucket_.Size(), 1 );
    }
///@}

///@Name Iterators
///@{
    TEST_F  ( TestBucketWithMultipleInteger
            , IteratorSerialForAllElements ) 
    {
        // Starting with a bunch of unprocessed elements
        std::vector<TElement> const verificationVectorWithoutProcessedItems =  
                                                            { TElement(1,true)
                                                            , TElement(5,false)
                                                            , TElement(2,false)
                                                            , TElement(55,false)
                                                            , TElement(9,false)
                                                            , TElement(23,false)
                                                            , TElement(4,false) };
        Types::count counter = 0;
        bucket_.template for_all_elements<egoa::ExecutionPolicy::sequential> ( 
            [ & verificationVectorWithoutProcessedItems
            , & counter ]( TElement const & element ) 
            {
                EXPECT_EQ ( element, verificationVectorWithoutProcessedItems[counter] );
                EXPECT_EQ ( element.Valid(), verificationVectorWithoutProcessedItems[counter].Valid() );
                counter++;
            }
        );

        counter = 0;
        bucketConst_.template for_all_elements<egoa::ExecutionPolicy::sequential> ( 
            [ & verificationVectorWithoutProcessedItems
            , & counter ]( TElement const & element ) 
            {
                EXPECT_EQ ( element, verificationVectorWithoutProcessedItems[counter] );
                EXPECT_EQ ( element.Valid(), verificationVectorWithoutProcessedItems[counter].Valid() );
                counter++;
            }
        );

        // After this pop only processed items are available as all unprocessed items are not valid, meaning here one element
        bucket_.Pop();
        bucket_.template for_all_elements<egoa::ExecutionPolicy::sequential> ( 
            []( TElement const & element ) 
            {
                EXPECT_EQ ( element, 1 );
                EXPECT_EQ ( element.Valid(), true );
            }
        );
        
        // Const call
        bucketConst_.template for_all_elements<egoa::ExecutionPolicy::sequential> ( 
            []( TElement const & element ) 
            {
                EXPECT_EQ ( element, 1 );
                EXPECT_EQ ( element.Valid(), true );
            }
        );
    }

    // @todo same as in BinaryHeap: (Q1) Can we test more, (Q2) refactoring
    TEST_F  ( TestBucketWithMultipleInteger
            , IteratorParallelForAllElements ) 
    {
        // For more details see
        // https://gitlab.inria.fr/Phylophile/Treerecs/blob/f6551e06797b52819ba3e630b92315254a944da5/tests/gtest/googletest/docs/AdvancedGuide.md
        ::testing::FLAGS_gtest_death_test_style = "threadsafe";
#ifdef OPENMP_AVAILABLE
        // Number of threads check
        Types::count numberOfThreads = omp_get_max_threads();
        EXPECT_GE( numberOfThreads, 0 );

        // Non const loop check
        std::vector<Types::count>            numberOfElements ( numberOfThreads, 0 );
        std::vector< std::vector<TElement> > elementsLoopedOver ( numberOfThreads
                                                                , std::vector<TElement>() );
        bucket_.for_all_elements<egoa::ExecutionPolicy::parallel> ( 
            [ & numberOfThreads
            , & numberOfElements
            , & elementsLoopedOver ]( TElement & element ) 
            {
                ++numberOfElements[ omp_get_thread_num() ];
                elementsLoopedOver[ omp_get_thread_num() ].emplace_back ( element );
            }
        );
        ParallelIteratorCheck<TElement> ( {1}, numberOfElements, elementsLoopedOver );
        
        // Const loop check
        numberOfElements.clear();
        elementsLoopedOver.clear();
        numberOfElements.resize ( numberOfThreads, 0 );
        elementsLoopedOver.resize ( numberOfThreads, std::vector<TElement>() );
        bucketConst_.for_all_elements<egoa::ExecutionPolicy::parallel> ( 
            [ & numberOfThreads
            , & numberOfElements
            , & elementsLoopedOver ]( TElement const & element ) 
            {
                ++numberOfElements[ omp_get_thread_num() ];
                elementsLoopedOver[ omp_get_thread_num() ].emplace_back ( element );
            }
        );
        ParallelIteratorCheck<TElement> ( {1}, numberOfElements, elementsLoopedOver );
#endif // OPENMP_AVAILABLE
    }

    //@todo Refactoring concerning duplicated calls for const and non-const iterator tests
    TEST_F  ( TestBucketWithMultipleInteger
            , IteratorBreakableForAllElements ) 
    {
        // Starting with a bunch of unprocessed elements
        std::vector<TElement> const verificationVectorWithoutProcessedItems =  
                                                            { TElement(1,true) };
        // Test non-const iterator
        Types::count counter = 0;
        bucket_.for_all_unprocessed_elements<egoa::ExecutionPolicy::breakable> ( 
            [ & verificationVectorWithoutProcessedItems
            , & counter]( TElement & element ) -> bool 
            {
                EXPECT_EQ( element, verificationVectorWithoutProcessedItems[counter] );
                ++counter;
                return false;
            }
        );
        EXPECT_EQ( counter, 1 );

        // Test non-const iterator
        counter = 0;
        bucketConst_.for_all_unprocessed_elements<egoa::ExecutionPolicy::breakable> ( 
            [ & verificationVectorWithoutProcessedItems
            , & counter]( TElement const & element ) -> bool 
            {
                EXPECT_EQ( element, verificationVectorWithoutProcessedItems[counter] );
                ++counter;
                return false;
            }
        );
        EXPECT_EQ( counter, 1 );
    }

    TEST_F  ( TestBucketWithMultipleInteger
            , IteratorSerialForAllProcessedElements ) 
    {
        bucket_.for_all_processed_elements<egoa::ExecutionPolicy::sequential> ( 
            []( TElement & element ) 
            {
                EXPECT_FALSE ( true );
            }
        );
        bucketConst_.for_all_processed_elements<egoa::ExecutionPolicy::sequential> ( 
            []( TElement const & element ) 
            {
                EXPECT_FALSE ( true );
            }
        );

        bucket_.Pop();

        bucket_.for_all_processed_elements<egoa::ExecutionPolicy::sequential> ( 
            []( TElement & element ) 
            {
                EXPECT_EQ ( element, 1 );
                EXPECT_TRUE ( element.Valid() );
            }
        );
        bucketConst_.for_all_processed_elements<egoa::ExecutionPolicy::sequential> ( 
            []( TElement const & element ) 
            {
                EXPECT_EQ ( element, 1 );
                EXPECT_TRUE ( element.Valid() );
            }
        );

        TElement element ( 0, false );
        bucket_.Merge<DominationCriterion::strict> ( element );
        bucket_.Pop();
        
        std::vector<TElement> const checkProcessedElements =  { TElement ( 1, true )
                                                              , TElement ( 0, true ) };
        Types::count counter = 0;
        bucket_.for_all_processed_elements<egoa::ExecutionPolicy::sequential> ( 
            [ & checkProcessedElements
            , & counter]( TElement & element ) 
            {
                EXPECT_EQ ( element, checkProcessedElements [ counter ] );
                // EXPECT_TRUE ( element.Valid() ); // Note that this is for the majority of the algorithm correct, but not in general
                ++counter;
            }
        );
        counter = 0;
        bucketConst_.for_all_processed_elements<egoa::ExecutionPolicy::sequential> ( [&checkProcessedElements, &counter]( TElement const & element ) {
            EXPECT_EQ ( element, checkProcessedElements [ counter ] );
            // EXPECT_TRUE ( element.Valid() ); // Note that this is for the majority of the algorithm correct, but not in general
            ++counter;
        });
    }

    //@todo Refactoring
    TEST_F  ( TestBucketWithMultipleInteger
            , IteratorParallelForAllProcessedElements ) 
    {
        // For more details see
        // https://gitlab.inria.fr/Phylophile/Treerecs/blob/f6551e06797b52819ba3e630b92315254a944da5/tests/gtest/googletest/docs/AdvancedGuide.md
        ::testing::FLAGS_gtest_death_test_style = "threadsafe";
#ifdef OPENMP_AVAILABLE
        // Number of threads check
        Types::count numberOfThreads = omp_get_max_threads();
        EXPECT_GE( numberOfThreads, 0 );

        // Non const loop check
        std::vector<Types::count>            numberOfElements ( numberOfThreads, 0 );
        std::vector< std::vector<TElement> > elementsLoopedOver ( numberOfThreads
                                                                , std::vector<TElement>() );
        bucket_.for_all_processed_elements<egoa::ExecutionPolicy::parallel> ( 
            [ & numberOfThreads
            , & numberOfElements
            , & elementsLoopedOver ]( TElement & element ) 
            {
                ++numberOfElements[ omp_get_thread_num() ];
                elementsLoopedOver[ omp_get_thread_num() ].emplace_back ( element );
            }
        );
        std::vector<TElement> emptyVector;
        ParallelIteratorCheck<TElement> ( emptyVector, numberOfElements, elementsLoopedOver );
        
        // Const loop check
        numberOfElements.clear();
        elementsLoopedOver.clear();
        numberOfElements.resize ( numberOfThreads, 0 );
        elementsLoopedOver.resize ( numberOfThreads, std::vector<TElement>() );
        bucketConst_.for_all_processed_elements<egoa::ExecutionPolicy::parallel> ( 
            [ & numberOfThreads
            , & numberOfElements
            , & elementsLoopedOver ]( TElement const & element ) 
            {
                ++numberOfElements[ omp_get_thread_num() ];
                elementsLoopedOver[ omp_get_thread_num() ].emplace_back ( element );
            }
        );
        ParallelIteratorCheck<TElement> ( emptyVector, numberOfElements, elementsLoopedOver );

        TElement element ( 1, false );
        bucket_.Pop();
        bucket_.Merge<DominationCriterion::strict> ( element );
        bucket_.Pop();
        bucket_.Merge<DominationCriterion::strict> ( element );
        bucket_.Pop();
        bucket_.Merge<DominationCriterion::strict> ( element );
        bucket_.Pop();

        bucket_.for_all_processed_elements<egoa::ExecutionPolicy::parallel> ( 
            []( TElement & element ) 
            {
                EXPECT_EQ   ( element.Value(), 1 );
                EXPECT_TRUE ( element.Valid()    );
            }
        );

        bucketConst_.for_all_processed_elements<egoa::ExecutionPolicy::parallel> ( 
            []( TElement const & element ) 
            {
                EXPECT_EQ ( element.Value(), 1 );
                EXPECT_TRUE ( element.Valid() );
            }
        );
#endif // OPENMP_AVAILABLE
    }

    //@todo test more
    TEST_F  ( TestBucketWithMultipleInteger
            , IteratorBreakableForAllProcessedElements ) 
    {
        bucket_.for_all_processed_elements<egoa::ExecutionPolicy::breakable> ( 
            []( TElement & element ) -> bool 
            {
                EXPECT_FALSE ( true );
                return true;
            }
        );
        bucketConst_.for_all_processed_elements<egoa::ExecutionPolicy::breakable> ( 
            []( TElement const & element ) -> bool 
            {
                EXPECT_FALSE ( true );
                return true;
            }
        );
    }

    //@todo test something
    TEST_F  ( TestBucketWithMultipleInteger
            , IteratorSerialForAllUnprocessedElements ) 
    {
        // Starting with a bunch of unprocessed elements
        std::vector<TElement> const verificationVectorWithoutProcessedItems =  
                                                            { TElement ( 1, true ) };

        Types::count counter = 0;
        bucket_.for_all_unprocessed_elements<egoa::ExecutionPolicy::sequential> ( 
            [ & verificationVectorWithoutProcessedItems
            , & counter]( TElement & element ) 
            {
                EXPECT_EQ ( element, verificationVectorWithoutProcessedItems[counter] );
                ++counter;
            }
        );
        EXPECT_EQ ( 1, counter );

        counter = 0;
        bucketConst_.for_all_unprocessed_elements<egoa::ExecutionPolicy::sequential> ( 
            [ & verificationVectorWithoutProcessedItems
            , & counter]( TElement const & element ) 
            {
                EXPECT_EQ ( element, verificationVectorWithoutProcessedItems[counter] );
                ++counter;
            }
        );
        EXPECT_EQ ( 1, counter );
    }

    TEST_F  ( TestBucketWithMultipleInteger
            , IteratorParallelForAllUnprocessedElements ) 
    {
        // For more details see
        // https://gitlab.inria.fr/Phylophile/Treerecs/blob/f6551e06797b52819ba3e630b92315254a944da5/tests/gtest/googletest/docs/AdvancedGuide.md
        ::testing::FLAGS_gtest_death_test_style = "threadsafe";
#ifdef OPENMP_AVAILABLE
        // Number of threads check
        Types::count numberOfThreads = omp_get_max_threads();
        EXPECT_GE( numberOfThreads, 0 );

        // Non const loop check
        std::vector<Types::count>            numberOfElements ( numberOfThreads, 0 );
        std::vector< std::vector<TElement> > elementsLoopedOver ( numberOfThreads
                                                                , std::vector<TElement>() );
        bucket_.for_all_unprocessed_elements<egoa::ExecutionPolicy::parallel> ( 
            [ & numberOfThreads
            , & numberOfElements
            , & elementsLoopedOver ]( TElement & element ) 
            {
                ++numberOfElements[ omp_get_thread_num() ];
                elementsLoopedOver[ omp_get_thread_num() ].emplace_back ( element );
            }
        );
        ParallelIteratorCheck<TElement> ( {1}, numberOfElements, elementsLoopedOver );
        
        // Const loop check
        numberOfElements.clear();
        elementsLoopedOver.clear();
        numberOfElements.resize ( numberOfThreads, 0 );
        elementsLoopedOver.resize ( numberOfThreads, std::vector<TElement>() );
        bucketConst_.for_all_unprocessed_elements<egoa::ExecutionPolicy::parallel> ( 
            [ & numberOfThreads
            , & numberOfElements
            , & elementsLoopedOver ]( TElement const & element ) 
            {
                ++numberOfElements[ omp_get_thread_num() ];
                elementsLoopedOver[ omp_get_thread_num() ].emplace_back ( element );
            }
        );
        ParallelIteratorCheck<TElement> ( {1}, numberOfElements, elementsLoopedOver );

        bucket_.for_all_unprocessed_elements<egoa::ExecutionPolicy::parallel> ( 
            [&]( TElement & element ) 
            {
                auto iter = std::find ( intVector_.begin(), intVector_.end(), element );
                EXPECT_NE ( iter, intVector_.end()  );
                EXPECT_EQ ( element, *iter          );
            }
        );

        bucketConst_.for_all_processed_elements<egoa::ExecutionPolicy::parallel> ( 
            [&]( TElement const & element ) 
            {
                auto iter = std::find ( intVector_.begin(), intVector_.end(), element );
                EXPECT_NE ( iter, intVector_.end()  );
                EXPECT_EQ ( element, *iter          );
            }
        );
#endif // OPENMP_AVAILABLE
    }

    //@todo refactor with the other breakable loops for all elements
    /// @todo This does not really test breaking because there is only one unprocessed element
    TEST_F  ( TestBucketWithMultipleInteger
            , IteratorBreakableForAllUnprocessedElements ) 
    {
        // Starting with a bunch of unprocessed elements
        std::vector<TElement> const verificationVectorWithoutProcessedItems =  
                                                            { TElement(1, true) };
        // Test non-const iterator
        Types::count counter = 0;
        bucket_.for_all_unprocessed_elements<egoa::ExecutionPolicy::breakable> ( 
            [ & verificationVectorWithoutProcessedItems
            , & counter ]( TElement & element ) -> bool 
            {
                EXPECT_EQ ( element, verificationVectorWithoutProcessedItems[counter] );
                ++counter;
                return false;
            }
        );
        EXPECT_EQ( counter, 1 );

        // Test non-const iterator
        counter = 0;
        bucketConst_.for_all_unprocessed_elements<egoa::ExecutionPolicy::breakable> ( 
            [ & verificationVectorWithoutProcessedItems
            , & counter ]( TElement const & element ) -> bool 
            {
                EXPECT_EQ ( element, verificationVectorWithoutProcessedItems[counter] );
                ++counter;
                return false;
            }
        );
        EXPECT_EQ ( counter, 1 );
    }

    TEST_F  ( TestBucketWithMultipleInteger
            , IteratorSerialForAllOptima ) 
    {
        TElement minElement = bucket_.Top();

        bucket_.for_all_optima<egoa::ExecutionPolicy::sequential> ( 
            [ & minElement ]( TElement const & element ) 
            {
                EXPECT_EQ ( element, minElement );
            }
        );

        bucketConst_.for_all_optima<egoa::ExecutionPolicy::sequential> ( 
            [ & minElement ] ( TElement const & element ) 
            {
                EXPECT_EQ ( element, minElement );
            }
        );
    }

    TEST_F  ( TestBucketWithMultipleInteger
            , IteratorParallelForAllOptima ) 
    {
        TElement minElement = bucket_.Top();

        bucket_.for_all_optima<egoa::ExecutionPolicy::parallel> ( 
            [ & minElement ] ( TElement const & element ) 
            {
                EXPECT_EQ ( element, minElement );
            }
        );

        bucketConst_.for_all_optima<egoa::ExecutionPolicy::parallel> ( 
            [ & minElement ] ( TElement const & element ) 
            {
                EXPECT_EQ ( element, minElement );
            }
        );
    }

    /// @todo tests for breakable for_all_optima
///@}

} // namespace egoa::test

/*
 * TestBound.cpp
 *
 *  Created on: Jan 28, 2019
 *      Author: Franziska Wegner
 */

#include "TestBound.hpp"

#include "DataStructures/Bound.hpp"

#include "Helper/TestHelper.hpp"

// using ::testing::Eq;
// using ::testing::ByRef;
using ::testing::Ge;
using ::testing::Le;

namespace egoa::test {

TestBound::TestBound () {}

TestBound::~TestBound () {}

void TestBound::SetUp () {}

void TestBound::TearDown () {}

TEST_F ( TestBound, MinPositiveNos ) {
    egoa::Bound<> bound(2.1, 2.5);

    EXPECT_DOUBLE_EQ (2.1, bound.Minimum());
    ASSERT_THAT(bound.Minimum(), Le(bound.Maximum()));

    bound.Range(2.00000001, 2.00000005);

    EXPECT_DOUBLE_EQ (2.00000001, bound.Minimum());
    ASSERT_THAT(bound.Minimum(), Le(bound.Maximum()));
}

TEST_F ( TestBound, MaxPositiveNos ) {
    egoa::Bound<> bound(2.1, 2.5);

    EXPECT_DOUBLE_EQ (2.5, bound.Maximum());
    ASSERT_THAT(bound.Maximum(), Ge(bound.Minimum()));

    bound.Range(2.00000001, 2.00000005);
    EXPECT_DOUBLE_EQ (2.00000005, bound.Maximum());
    ASSERT_THAT(bound.Maximum(), Ge(bound.Minimum()));
}

TEST_F ( TestBound, DeathTest ) {
    // ASSERT_DEATH({ Bound(3, 1);}, "terminating with uncaught exception of type BoundMismatch: Minimum > maximum: 3 < 1");
#ifdef EGOA_EXCEPTION_HANDLING
    try {
        egoa::Bound<> bound (3,1);
        FAIL() << "Expected BoundMismatch";
    }
    catch(egoa::BoundMismatch const & err) {
        EXPECT_EQ(err.What(), std::string("Minimum > maximum: 3 < 1"));
    }
    catch(...) {
        FAIL() << "Expected BoundMismatch2";
    }
#elif EGOA_ENABLE_ASSERTION
    auto assertionString = buildAssertionString ( "Bound.hpp"
                                                , "Bound"
                                                , "Bound"
                                                , "minimum_ <= maximum_");
    ASSERT_DEATH( {egoa::Bound<> bound (3,1);}, assertionString );
#endif
}

} // namespace egoa::test

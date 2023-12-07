/*
 * TestBound.hpp
 *
 *  Created on: Jan 28, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__TESTS__DATA_STRUCTURES__BOUND_HPP
#define EGOA__TESTS__DATA_STRUCTURES__BOUND_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace egoa::test {

  /**
   * @brief Fixture for testing class Bound
   */
  class TestBound : public ::testing::Test {

  protected:

    // You can do set-up work for each test here.
    TestBound();

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~TestBound();

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();
  };

} // namespace egoa::test

#endif // EGOA__TESTS__DATA_STRUCTURES__BOUND_HPP

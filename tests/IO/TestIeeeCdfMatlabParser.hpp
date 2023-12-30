/*
 * TestIeeeCdfMatlabParser.cpp
 *
 *  Created on: Jan 29, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA___TESTS___IO___TEST_IEEE_CDF_MATLAB_PARSER_HPP
#define EGOA___TESTS___IO___TEST_IEEE_CDF_MATLAB_PARSER_HPP

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace egoa{
namespace test {
  /**
   * @brief Fixture for testing class IeeeCdfMatlabParser
   */
  class TestIeeeCdfMatlabParser : public ::testing::Test {

  protected:

    // You can do set-up work for each test here.
    TestIeeeCdfMatlabParser();

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~TestIeeeCdfMatlabParser();

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    // Code here will be called immediately after the constructor (right
    // before each test).
    virtual void SetUp();

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown();
  };
} // test
} // namespace egoa

#endif // EGOA___TESTS___IO___TEST_IEEE_CDF_MATLAB_PARSER_HPP

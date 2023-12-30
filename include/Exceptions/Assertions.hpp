/*
 * @file       Assertions.hpp
 * @brief      If the @p EGOA_ENABLE_ASSERTION is enabled in the cmake setting
 *             both @p ESSENTIAL_ASSERT and @p USAGE_ASSERT throw asserts if
 *             needed, otherwise if @p EGOA_ENABLE_EXCEPTION_HANDLING is
 *             enabled in the cmake setting both methods throw exceptions.
 *
 *             Operation                                    | Effect
 *             ---------------------------------------------|-----------------------------
 *             @code ESSENTIAL_ASSERT ( false ); @endcode   | Throws an essential assert. Essential asserts
 *                                                          | show that a crucial invariant in the code is
 *                                                          | violated. This is a hint of a programming mistake.
 *             @code USAGE_ASSERT ( false ); @endcode       | Throws a usage assert. A usage assert shows
 *                                                          | that the method is not used in a correct way,
 *                                                          | e.g., incorrect parameter input. Take a look
 *                                                          | at the precondition section of the comments.
 *
 *  Created on: Feb 14, 2019
 *      Author: Franziska Wegner
 */

#ifndef EGOA__EXCEPTIONS__ASSERTIONS_HPP
#define EGOA__EXCEPTIONS__ASSERTIONS_HPP

#include <exception>
#include <sstream>
#include <iostream>

#ifdef EGOA_ENABLE_ASSERTION
    #define ESSENTIAL_ASSERT( expr ) \
        if (!(expr)) \
        { \
            std::cerr   << "ESSENTIAL assertion failed at " << __FILE__ \
                        << ":"                              << __LINE__; \
            std::cerr   << " inside "                       << __FUNCTION__; \
            std::cerr   << ".\n Condition: "                << #expr; \
            abort(); \
        }

    #define USAGE_ASSERT( expr ) \
        if (!(expr)) \
        { \
            std::cerr   << "USAGE assertion failed at " << __FILE__ \
                        << ":"                          << __LINE__; \
            std::cerr   << " inside "                   << __FUNCTION__; \
            std::cerr   << ".\n Condition: "            << #expr; \
            abort(); \
        }
#else // ifdef EGOA_ENABLE_ASSERTION
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    #define ESSENTIAL_ASSERT( expr ) \
        if (!(expr)) \
        { \
            std::stringstream message; \
            message << "Essential exception at "<< __FILE__ \
                    << ":"                      << __LINE__ \
                    << " inside "               << __FUNCTION__ \
                    << ".\n Condition: "        << #expr; \
            throw ( std::runtime_error ( message.str() ) ); \
        }

    #define USAGE_ASSERT( expr ) \
        if (!(expr)) \
        { \
            std::stringstream message; \
            message << "Usage exception at "<< __FILE__ \
                    << ":"                  << __LINE__ \
                    << " inside "           << __FUNCTION__ \
                    << ".\n Condition: "    << #expr; \
            throw ( std::runtime_error( message.str() ) ); \
        }
#else // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    #define ESSENTIAL_ASSERT( expr ) ( expr )
    #define USAGE_ASSERT( expr ) ( expr )
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION

#endif // EGOA__EXCEPTIONS__ASSERTIONS_HPP

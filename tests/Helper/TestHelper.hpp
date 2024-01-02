/*
 * TestHelper.hpp
 *
 *  Created on: Feb 11, 2019
 *      Author: Matthias Wolf
 */

#ifndef EGOA__TESTS__HELPER__TEST_HELPER_HPP
#define EGOA__TESTS__HELPER__TEST_HELPER_HPP

#include "gtest/gtest.h"

#include <functional>

#include "Auxiliary/Types.hpp"

namespace egoa::test {

/**
 * @brief      Maps the type to the file name in which the type is defined.
 * @details    This is used by @p buildAssertionString to construct an
 *     assertion string.
 *
 * @see        egoa::test::buildAssertionString
 *
 * @tparam     Type  The type for which the assertion string shall be built.
 */
template<typename Type>
struct FileName {
    static Types::string Name() = delete;
};

/**
 * @brief      Builds a regular expression that matches the messages if an
 *     assertion is thrown.
 *
 * @param[in]  fileName        The name of the file, in which the assertion is
 *     thrown.
 * @param[in]  function        The function in which the assertion is thrown.
 * @param[in]  message         The assertion message.
 *
 * @return     The regular expression matching the assertion message.
 */
Types::string buildAssertionString ( Types::string fileName
                                   , Types::string function
                                   , Types::string message )
{
    std::stringstream result;
#ifdef EGOA_ENABLE_ASSERTION
    result  << ".* assertion failed at .*"
            << fileName
            << ":.* inside .*"
            << function
            << ".\n Condition: "
            << message
            << "";
#else // ifdef EGOA_ENABLE_ASSERTION
#ifdef EGOA_ENABLE_EXCEPTION_HANDLING
    result  << ".* exception at .*"
            << fileName
            << ":.* inside .*"
            << function
            << ".\n Condition: "
            << message
            << "";
#endif // ifdef EGOA_ENABLE_EXCEPTION_HANDLING
#endif // ifdef EGOA_ENABLE_ASSERTION
    return result.str();
}

/**
 * @brief      Builds a regular expression that matches the messages if an
 *      assertion is thrown.
 * @deprecated @p enclosingClass is not part of the assertion message anymore. Use
 *             the other overloads.
 *
 * @param[in]  fileName        The name of the file, in which the assertion is thrown.
 * @param[in]  enclosingClass  Unused.
 * @param[in]  function        The function in which the assertion is thrown.
 * @param[in]  message         The assertion message.
 *
 * @return     The regular expression matching the assertion message.
 */
Types::string buildAssertionString ( Types::string fileName
                                   , Types::string enclosingClass
                                   , Types::string function
                                   , Types::string message )
{
    return buildAssertionString ( fileName, function, message );
}

/**
 * @brief      Builds a regular expression that matches the messages if an
 *     assertion is thrown.
 * @details    Extracts the file name by calling
 *             @code FileName<Type>::FileName() @endcode.
 *             To use this function for your types you need to specialize
 *             FileName for your type.
 *
 * @param[in]  function  The function.
 * @param[in]  message   The message.
 *
 * @tparam     Type      The type for which the assertion string shall be built.
 *
 * @see        egoa::test::FileName
 *
 * @return     The assertion string.
 */
template<typename Type>
Types::string buildAssertionString ( Types::string function
                                   , Types::string message )
{
    return buildAssertionString ( FileName<Type>::Name(), function, message );
}

/**
 * @brief      Expects that two vectors have the same content but the
 *             order of the elements may differ.
 *
 * @param[in]  left   The first vector.
 * @param[in]  right  The second vector.
 *
 * @tparam     T      The type of the vectors' elements.
 */
template<typename T>
void ExpectSameContent ( std::vector<T> left
                       , std::vector<T> right )
{
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    EXPECT_EQ(left, right);
}

template<typename LeftIt, typename RightIt>
void ExpectSameContent ( LeftIt  leftBegin
                       , LeftIt  leftEnd
                       , RightIt rightBegin
                       , RightIt rightEnd )
{
    std::vector<decltype(*leftBegin)> left{leftBegin, leftEnd};
    std::vector<decltype(*rightBegin)> right{rightBegin, rightEnd};
    ExpectSameContent ( left, right );
}

/**
 * @brief      Expects that the two ranges contain the same elements in the
 *     same order.
 *
 * @param[in]  leftBegin   The begin of the left range.
 * @param[in]  leftEnd     The end of the left range.
 * @param[in]  rightBegin  The begin of the right range.
 * @param[in]  rightEnd    The end of the right range.
 *
 * @tparam     LeftIt      The type of the iterators for the left range.
 * @tparam     RightIt     The type of the iterators for the right range.
 */
template<typename LeftIt, typename RightIt>
void ExpectEqual ( LeftIt  leftBegin
                 , LeftIt  leftEnd
                 , RightIt rightBegin
                 , RightIt rightEnd )
{
    auto leftIt  = leftBegin;
    auto rightIt = rightBegin;
    while ( leftIt != leftEnd && rightIt != rightEnd )
    {
        EXPECT_EQ ( *leftIt, *rightIt );
        ++leftIt;
        ++rightIt;
    }
    EXPECT_EQ ( leftIt,  leftEnd )  << "Left contains more elements than right";
    EXPECT_EQ ( rightIt, rightEnd ) << "Right contains more elements than left";

}

template<typename LeftRange, typename RightRange>
void ExpectEqual ( LeftRange  && left
                 , RightRange && right )
{
    using std::begin, std::end;
    ExpectEqual ( begin(left), end(left), begin(right), end(right) );
}

/**
 * @brief      A minimal number of properties for testing graphs and related data structures.
 * @details    Each properties object maintains a private, immutable ID that
 *             is used to compare properties.
 */
class MinimalProperties {
    const static Types::index GARBAGE = 123456;
public:
    explicit MinimalProperties ( Types::index privateId )
    : privateId_(privateId) {}

    Types::index PrivateId() const { return privateId_; }

    /**
     * @brief      To check whether a non-const member function can be called.
     */
    void NonConstMemberFunction() {}

    friend bool operator== ( MinimalProperties const & left
                           , MinimalProperties const & right )
    {
        return left.privateId_ == right.privateId_;
    }
    friend bool operator!= ( MinimalProperties const & left
                           , MinimalProperties const & right )
    {
        return !(left == right);
    }

private:
    Types::index privateId_;
};

inline std::ostream & operator<< ( std::ostream            & stream
                                 , MinimalProperties const & edge )
{
    stream  << "{"
            << "privateId = "
            << edge.PrivateId()
            << "}";
    return stream;
}

/**
 * @brief      A dummy object that can be used to test the containers and iterators.
 */
struct Dummy {
    Types::count * counter_;

    Dummy ( Types::count * counter ) : counter_(counter) {}

    friend bool operator<  ( Dummy const &, Dummy const & ) { return false; }
    friend bool operator>  ( Dummy const &, Dummy const & ) { return false; }
    friend bool operator<= ( Dummy const &, Dummy const & ) { return true;  }
    friend bool operator>= ( Dummy const &, Dummy const & ) { return true;  }
    friend bool operator== ( Dummy const &, Dummy const & ) { return true;  }
    friend bool operator!= ( Dummy const &, Dummy const & ) { return true;  }
    void Increment() const {++*counter_;}
};

/**
 * @brief      A class for which @p std::hash<> is specialized
 * @details    Objects of this class may be used as keys for a
 *             @p std::unordered_map.
 */
class HashableElement {
public:
    explicit HashableElement(Types::index id) : id_(id) {}
    Types::index Identifier() const { return id_; }

    friend bool operator<  ( HashableElement const & left, HashableElement const & right) { return left.Identifier() <  right.Identifier(); }
    friend bool operator<= ( HashableElement const & left, HashableElement const & right) { return left.Identifier() <= right.Identifier(); }
    friend bool operator>  ( HashableElement const & left, HashableElement const & right) { return left.Identifier() >  right.Identifier(); }
    friend bool operator>= ( HashableElement const & left, HashableElement const & right) { return left.Identifier() >= right.Identifier(); }
    friend bool operator== ( HashableElement const & left, HashableElement const & right) { return left.Identifier() == right.Identifier(); }
    friend bool operator!= ( HashableElement const & left, HashableElement const & right) { return left.Identifier() != right.Identifier(); }
private:
    Types::index id_;
};

inline std::ostream & operator<< ( std::ostream          & stream
                                 , HashableElement const & element )
{
    stream << "#" << element.Identifier();
    return stream;
}

} // namespace egoa::test

namespace std {
    /**
     * @brief      Hash function for egoa::test::HashableElement
     */
    template<>
    struct hash<egoa::test::HashableElement> {
        size_t operator() ( egoa::test::HashableElement const & element ) const
        {
            return element.Identifier();
        }
    };
} // namespace std

#endif // EGOA__TESTS__HELPER__TEST_HELPER_HPP

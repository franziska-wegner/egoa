/*
 * PgtExceptions.hpp
 *
 *  Created on: Nov 07, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__EXCEPTIONS__PGT_EXCEPTIONS_HPP
#define EGOA__EXCEPTIONS__PGT_EXCEPTIONS_HPP

#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <string>

#include "Auxiliary/Types.hpp"

namespace egoa {

// https://stackoverflow.com/questions/348833/how-to-know-the-exact-line-of-code-where-where-an-exception-has-been-caused
template<typename T>
void my_exception(T arg1, T arg2, const char *file, const char *func, size_t line) {
#ifdef PGT_EXCEPTION_HANDLING
    if ( arg1 < arg2 )
        throw runtime_error( (std::string)file + ":" + (std::string)func + ":" + std::to_string(line) +
                            ": index out of bound error with index:"  + to_string(arg1) +
                            " > number of elements ( here " + to_string(arg2) + ")." );
#endif
}

#define throw_out_of_bound(arg1,arg2) throw my_exception(arg1, arg2, __FILE__, __func__, __LINE__);

// template<typename T = double>
class BoundMismatch : public std::runtime_error {
    typedef double T;
    public:
        /// constructor only which passes message to base class
        BoundMismatch(std::string msg, T minimum, T maximum)
        : std::runtime_error(msg), minimum_(minimum), maximum_(maximum) {}

        BoundMismatch(T minimum, T maximum)
        : std::runtime_error("Minimum > maximum"), minimum_(minimum), maximum_(maximum) {

        }

        inline T  Minimum() const   { return minimum_; }
        inline T& Minimum()         { return minimum_; }

        inline T  Maximum() const   { return maximum_; }
        inline T& Maximum()         { return maximum_; }

        template<typename T2 = double>
        static T2 Check(const T2& minimum, const T2& maximum)
        {
            if ( minimum > maximum ) {
                throw BoundMismatch( minimum, maximum );
            }
            return true;
        }

        virtual Types::string What() const throw() {
          std::ostringstream message;

          message   << runtime_error::what()
                    << ": "  << Minimum()
                    << " < " << Maximum();

          return message.str();
        }

    private:
        double minimum_;
        double maximum_;
};

// ostringstream BoundMismatch::message_;

} // namespace egoa

#endif // EGOA__EXCEPTIONS__PGT_EXCEPTIONS_HPP

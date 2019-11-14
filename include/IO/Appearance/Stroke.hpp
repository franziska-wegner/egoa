/*
 * Stroke.hpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__IO__STROKE_HPP
#define EGOA__IO__STROKE_HPP

#include "Auxiliary/Auxiliary.hpp"

namespace egoa {

/**
 * @class Stroke
 * 
 * @code{.cpp}
 *      ...
 *      //code example TODO
 *      ...
 * @endcode
 */
class Stroke {
    public:
        enum class Name {
            solid
            , dashed
            , dotted
            , dasheddotted
            , bold
            , none
        };
    public:
        ///@name Constructors and destructor
        ///@{
#pragma mark CONSTRUCTORS_AND_DESTRUCTOR
            /**
             * @brief      Constructs a new instance.
             *
             * @param[in]  name  The name
             */
            Stroke( Stroke::Name name )
            : stroke_(static_cast<Types::count>(name)) {}

            /**
             * @brief      Constructs a new instance.
             */
            Stroke()
            : stroke_( static_cast<Types::count>(Name::solid) ) {}

            ~Stroke() {}
        ///@}

        ///@name Operators
        ///@{
#pragma mark OPERATORS
            bool operator== ( const Stroke& rhs ) 
            {
                return stroke_ == rhs.stroke_;
            }

            bool operator!= ( const Stroke& rhs ) 
            {
                return !operator==(rhs);
            }
        ///@}

        Types::count Type() const { return stroke_; }
        
        ///@name Operators
        ///@{
#pragma mark OUTPUT
            friend std::ostream & operator<< ( std::ostream & outputStream, Name stroke ) 
            {
                switch ( stroke ) 
                {
                    case Name::solid:           outputStream << "solid";          break;
                    case Name::dashed:          outputStream << "dashed";         break;
                    case Name::dotted:          outputStream << "dotted";         break;
                    case Name::dasheddotted:    outputStream << "dasheddotted";   break;
                    case Name::bold:            outputStream << "bold";           break;
                    case Name::none:            outputStream << "invis";          break;
                }
                return outputStream;
            }
        ///@}
    private:
        Types::count stroke_;
};

} // namespace egoa

#endif // EGOA__IO__STROKE_HPP

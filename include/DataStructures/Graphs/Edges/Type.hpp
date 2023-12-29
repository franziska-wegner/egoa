/*
 * Type.hpp
 *
 *  Created on: Oct 13, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__DATA_STRUCTURE__EDGES__TYPE_HPP
#define EGOA__DATA_STRUCTURE__EDGES__TYPE_HPP

#ifdef OGDF_AVAILABLE
    #include <ogdf/basic/graphics.h>
#endif

#include "IO/Appearance/Color.hpp"
#include "IO/Appearance/Stroke.hpp"

namespace egoa::Edges {

///@name Edge types
///@{
#pragma mark EDGE_TYPES
    /**
     * @brief      This class describes an electrical edge type.
     */
    enum class ElectricalEdgeType {
          standard    = 0
        , switched    = 1    /**< This edge is switched off */
        , controller  = 2    /**< Controller on that edge */
        , transformer = 3    /**< Transformer on that edge */
        , facts       = 4    /**< Flexible AC Transmission System */
        , overloaded  = 5    /**< Overloaded edge */
        , unknown     = 99
    };

    /**
     * @brief      This class describes a carrier differentiation type.
     * @details    The AC (Alternating Current) and DC (Direct Current) represent
     *     to standard carrier types in the power grid.
     */
    enum class CarrierDifferentiationType {
          AC        = 0     /**< Alternating Current (AC) */
        , DC        = 1     /**< Direct Current (DC) */
        , unknown   = 99
    };
///@}

///@name Operators
///@{
#pragma mark OPERATORS
    /**
     * @brief      Writes the carrier differentiation type to an output stream.
     *
     * @param      outputStream  The stream to write data to, e.g., std::cout.
     * @param      rhs           The carrier differentiation type.
     *
     * @return     The output stream.
     */
    inline std::ostream & operator<< ( std::ostream                     & outputStream
                                     , CarrierDifferentiationType const & rhs )
    {
        if      ( rhs == CarrierDifferentiationType::AC    ){ outputStream << "AC";   }
        else if ( rhs == CarrierDifferentiationType::DC    ){ outputStream << "DC";   }
        else                                                { outputStream << "unknown";    }
        return outputStream;
    }

    /**
     * @brief      Writes the electrical edge type to an output stream.
     *
     * @param      outputStream  The stream to write data to, e.g., std::cout.
     * @param      rhs           The electrical edge type.
     *
     * @return     The output stream.
     */
    inline std::ostream & operator<< ( std::ostream             & outputStream
                                     , ElectricalEdgeType const & rhs)
    {
        if      ( rhs == ElectricalEdgeType::standard    ) { outputStream << "standard";   }
        else if ( rhs == ElectricalEdgeType::switched    ) { outputStream << "switched";   }
        else if ( rhs == ElectricalEdgeType::controller  ) { outputStream << "controller"; }
        else if ( rhs == ElectricalEdgeType::transformer ) { outputStream << "transformer";}
        else if ( rhs == ElectricalEdgeType::facts       ) { outputStream << "facts";      }
        else if ( rhs == ElectricalEdgeType::overloaded  ) { outputStream << "overloaded"; }
        else                                               { outputStream << "unknown";    }
        return outputStream;
    }
///@}

///@name Conversion methods
///@{
#pragma mark CONVERSION_METHODS

#ifdef OGDF_AVAILABLE
    /**
     * @brief      Conversion from an electrical edge to a stroke type.
     *
     * @param      type    The electrical edge type.
     * @param      stroke  The stroke type.
     */
    inline void ElectricalEdge2Stroke ( ElectricalEdgeType const & type
                                      , ogdf::StrokeType         & stroke )
    {
        switch (type) {
            case ElectricalEdgeType::standard:      stroke = ogdf::StrokeType::Solid;   break;
            case ElectricalEdgeType::switched:      stroke = ogdf::StrokeType::Dash;    break;
            case ElectricalEdgeType::controller:    stroke = ogdf::StrokeType::Dot;     break;
            case ElectricalEdgeType::transformer:   stroke = ogdf::StrokeType::Dot;     break;
            case ElectricalEdgeType::facts:         stroke = ogdf::StrokeType::Dashdot; break;
            case ElectricalEdgeType::overloaded:    stroke = ogdf::StrokeType::Solid;   break;
            default:                                stroke = ogdf::StrokeType::None;
        }
    }

    /**
     * @brief      Conversion from an electrical edge type to ogdf::Color.
     *
     * @param      type   The electrical edge type.
     * @param      color  The ogdf::Color type.
     */
    inline void ElectricalEdge2Color ( ElectricalEdgeType const & type
                                     , ogdf::Color              & color )
    {
        switch (type) {
            case ElectricalEdgeType::standard:      color = ogdf::Color::Name::Black;     break;
            case ElectricalEdgeType::switched:      color = ogdf::Color::Name::Gray;      break;
            case ElectricalEdgeType::controller:    color = ogdf::Color::Name::Steelblue; break;
            case ElectricalEdgeType::transformer:   color = ogdf::Color::Name::Mediumblue;break;
            case ElectricalEdgeType::facts:         color = ogdf::Color::Name::Royalblue; break;
            case ElectricalEdgeType::overloaded:    color = ogdf::Color::Name::Darkred;   break;
            default:                                color = ogdf::Color::Name::Yellow;
        }
    }

    /**
     * @brief      Conversion from stroke to an electrical edge.
     *
     * @param      stroke  The stroke type.
     * @param      type    The electrical edge type.
     */
    inline void Stroke2ElectricalEdge ( ogdf::StrokeType const & stroke
                                      , ElectricalEdgeType     & type )
    {
        switch (stroke) {
            case ogdf::StrokeType::Solid:   type = ElectricalEdgeType::standard;      break;
            case ogdf::StrokeType::Dash:    type = ElectricalEdgeType::switched;      break;
            // case ogdf::StrokeType::Dot:     type = ElectricalEdgeType::controller;    break;
            // case ogdf::StrokeType::Dot:     type = ElectricalEdgeType::transformer;   break;
            case ogdf::StrokeType::Dot:     type = ElectricalEdgeType::facts;         break;
            case ogdf::StrokeType::Dashdot: type = ElectricalEdgeType::overloaded;    break;
            default:                        type = ElectricalEdgeType::unknown;
        }
    }

    /**
     * @brief      Conversion from color to an electrical edge.
     *
     * @param      color  The ogdf::Color type.
     * @param      type   The electrical edge type.
     */
    inline void Color2ElectricalEdge ( ogdf::Color const  & color
                                     , ElectricalEdgeType & type )
    {
        if ( color == ogdf::Color::Name::Black          )   { type = ElectricalEdgeType::standard;      }
        else if ( color == ogdf::Color::Name::Gray      )   { type = ElectricalEdgeType::switched;      }
        else if ( color == ogdf::Color::Name::Steelblue )   { type = ElectricalEdgeType::controller;    }
        else if ( color == ogdf::Color::Name::Mediumblue)   { type = ElectricalEdgeType::transformer;   }
        else if ( color == ogdf::Color::Name::Royalblue )   { type = ElectricalEdgeType::facts;         }
        else if ( color == ogdf::Color::Name::Darkred   )   { type = ElectricalEdgeType::overloaded;    }
        else                                                { type = ElectricalEdgeType::unknown;       }
    }
#endif // OGDF_AVAILABLE

    /**
     * @brief      Conversion from an electrical edge to color.
     *
     * @param      type   The electrical edge type.
     * @param      color  The color type.
     */
    inline void ElectricalEdge2Color ( ElectricalEdgeType const & type
                                     , Color                    & color )
    {
        switch (type) {
            case ElectricalEdgeType::standard:      color = Color::Name::KITblack;     break;
            case ElectricalEdgeType::switched:      color = Color::Name::KITblack30;   break;
            case ElectricalEdgeType::controller:    color = Color::Name::KITseablue50; break;
            case ElectricalEdgeType::transformer:   color = Color::Name::KITcyanblue50;break;
            case ElectricalEdgeType::facts:         color = Color::Name::KITgreen70;   break;
            case ElectricalEdgeType::overloaded:    color = Color::Name::KITred70;     break;
            default:                                color = Color::Name::KITyellow;
        }
    }

    /**
     * @brief      Conversion from an electrical edge type to stroke.
     *
     * @param      type    The electrical edge type.
     * @param      stroke  The stroke type.
     */
    inline void ElectricalEdge2Stroke ( ElectricalEdgeType const & type
                                      , Stroke::Name             & stroke )
    {
        switch (type) {
            case ElectricalEdgeType::standard:      stroke = Stroke::Name::solid;          break;
            case ElectricalEdgeType::switched:      stroke = Stroke::Name::dashed;         break;
            case ElectricalEdgeType::controller:    stroke = Stroke::Name::dotted;         break;
            case ElectricalEdgeType::transformer:   stroke = Stroke::Name::dotted;         break;
            case ElectricalEdgeType::facts:         stroke = Stroke::Name::dasheddotted;   break;
            case ElectricalEdgeType::overloaded:    stroke = Stroke::Name::bold;           break;
            default:                                stroke = Stroke::Name::none;
        }
    }
///@}

} // namespace egoa::Edges

#endif // EGOA__DATA_STRUCTURE__EDGES__TYPE_HPP


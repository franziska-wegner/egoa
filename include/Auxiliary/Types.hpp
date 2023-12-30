/*
 * Types.hpp
 *
 *  Created on: Sep 07, 2018
 *      Author: Franziska Wegner
 */
#ifndef EGOA__AUXILIARY__TYPES_HPP
#define EGOA__AUXILIARY__TYPES_HPP

#include <QDebug>
#include <QRegularExpression>
#ifdef GUROBI_AVAILABLE
    #include "gurobi_c++.h"
#endif

namespace egoa::Types {

    // Integer Z
    typedef int64_t     integer;            /**< Integer */
    typedef integer     rcount;             /**< for backwards counter */
    typedef integer     difference;         /**< for differences */

    // Positive integer Z_{>=0}
    // for uint64_t check: https://en.cppreference.com/w/cpp/types/integer
    typedef uint64_t    posInteger;         /**< Positive integer */
    typedef uint8_t     ubyte;              /**< Small positive integer */
    typedef posInteger  largeNumber;        /**< TODO: include larger number handling */
    typedef posInteger  count;              /**< Positive counter, e.g., for forward for loops */
    typedef posInteger  index;              /**< When using indexing, e.g., for vectors. The type has to provide a conversion to size_t. */

    // Identifier
    typedef index       vertexId;           /**< node identifier are zero based  */
    typedef index       loadId;             /**< node identifier are zero based  */
    typedef index       generatorId;        /**< node identifier are zero based  */
    typedef index       edgeId;             /**< edge identifier are zero based  */
    typedef index       labelId;            /**< label identifier are zero based */
    typedef index       blockId;            /**< block identifier are zero based */

    // Real numbers R
    typedef double      real;               /**< */
    typedef long double largeReal;          /**< */

    // String
    typedef std::string string;             /**< */
    typedef std::string name;               /**< */

    // Snapshots
    typedef real        generatorSnapshot;  /**< */
    typedef real        loadSnapshot;       /**< */
    typedef real        weightSnapshot;     /**< */
    typedef string      timestampSnapshot;  /**< */


    /**
     * @brief      Convert a string to a double
     * @details    This function converts a string independent of the number
     *     convention---meaning "." or ","---to a double.
     *
     * @param[in]  str   The string that is a number
     *
     * @return     The converted double
     */
    inline real String2double( std::string str )
    {
        QRegularExpression rx("(^-?[0-9]?\\d*(\\.\\d+)?)"); // Filter numbers only
        QRegularExpressionMatchIterator i   = rx.globalMatch(QString::fromStdString(str));
        QRegularExpressionMatch match       = i.next();
        QString t_string                    = match.captured(1);

        // QString t_string(str.c_str());
        bool ok; double number(0);
        // QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
        number = QString(t_string).toDouble(&ok);   // ok == true, d == 1234.56
        // if (!ok) {
            // QLocale locale(QLocale::German); //QLocale::Catalan
            // number = locale.toDouble(t_string);
        // }
        return number;
    }

    /**
     * @brief      Convert a string to a integer
     *
     * @todo       The regular expression allows for negative numbers but the
     *             return type is unsigned.
     *
     * @param[in]  str   The string that is a number
     *
     * @return     The converted integer
     */
    inline count String2integer( std::string str )
    {
        QRegularExpression rx("(^-?[0-9]?\\d*(\\.\\d+)?)"); // Filter numbers only
        QRegularExpressionMatchIterator i   = rx.globalMatch(QString::fromStdString(str));
        QRegularExpressionMatch match       = i.next();
        QString t_string                    = match.captured(1);

        // QString t_string(str.c_str());
        bool ok; count number(0);
        number = QString(t_string).toUInt(&ok);
        return number;
    }

} // namespace egoa::Types

#endif // EGOA__AUXILIARY__TYPES_HPP

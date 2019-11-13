/*
 * Auxiliary.hpp
 *
 *  Created on: Sep 07, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__AUXILIARY__AUXILIARY_HPP
#define EGOA__AUXILIARY__AUXILIARY_HPP

#include "Auxiliary/Constants.hpp"
#include "Auxiliary/Types.hpp"

#ifdef OPENMP_AVAILABLE
    #include <omp.h>
#endif // OPENMP_AVAILABLE

namespace egoa::Auxiliary {

#ifdef OPENMP_AVAILABLE
    /**
     * @brief      Number of allowed threads.
     *
     * @return     The number of allowed threads.
     */
    inline Types::count NumberOfThreads ()        { return omp_get_num_threads(); }
    
    /**
     * @brief      Maximum number of possible threads.
     *
     * @return     The maximum number of threads.
     */
    inline Types::count MaximumNumberOfThreads () { return omp_get_max_threads(); }

    /**
     * @brief      Number of processors.
     *
     * @return     The number of processors.
     */
    inline Types::count NumberOfProcessors () { return omp_get_num_procs(); }
#else // OPENMP_AVAILABLE
    /**
     * @brief      Number of allowed threads.
     *
     * @return     The number of allowed threads.
     */
    inline Types::count NumberOfThreads () { return 1; }

    /**
     * @brief      Maximum number of possible threads.
     *
     * @return     The maximum number of threads.
     */
    inline Types::count MaximumNumberOfThreads () { return 1; }

    /**
     * @brief      Number of processors.
     *
     * @return     The number of processors.
     */
    inline Types::count NumberOfProcessors () { return 1; }
#endif // OPENMP_AVAILABLE

/**@name Floating-point tolerances */
///@{
/**
 * @brief      Check equality for floating points.
 * @details    Floating-point tolerances revisited
 *      https://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html
 *      https://en.wikipedia.org/wiki/IEEE_754
 *      http://realtimecollisiondetection.net/blog/?p=
 *      https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
 *      https://randomascii.wordpress.com/2012/06/26/doubles-are-not-floats-so-dont-compare-them/
 * 
 *      The absolute tolerance test fails when x and y become large, and the
 *      relative tolerance test fails when they become small. It is therefore
 *      desired to combine these two tests together in a single test. Over the
 *      years at GDC, as well as in my book, I've suggested the following combined
 *      tolerance test:
 *      fabs(x - y) <= absTol * std::max(1.0, ( relTol/absTol * std::max(fabs(x), fabs(y)) ) )
 *
 * @param[in]  a       The parameter a
 * @param[in]  b       The parameter b
 * @param[in]  absTol  The abs tolerance
 * @param[in]  relTol  The relative tolerance
 *
 * @return     TRUE if both doubles are equal with regards to the tolerance, FALSE otherwise.
 */
inline bool EQ (double a, double b, double absTol = Const::EPSILON, double relTol = Const::EPSILON) 
{
    if ( fabs(a - b) <= absTol * std::max(1.0, ( relTol/absTol * std::max(fabs(a), fabs(b)) ) ) )
        return true;
    else
        return false;
}
///@}

/**@name File and path related stuff */
///@{
/**
 * https://stackoverflow.com/questions/8520560/get-a-file-name-from-a-path
 */

///@todo Put in system dependent header
///@{
/**
 * @brief      Path separator in UNIX systems.
 */
struct MatchPathSeparator
{
    bool operator()( char ch ) const
    {
        return ch == '/';
    }
};

/**
 * @brief Path separator in Windows systems
 * 
 * @param ch [description]
 * @return [description]
 */
// struct MatchPathSeparator
// {
//     bool operator()( char ch ) const
//     {
//         return ch == '\\' || ch == '/';
//     }
// };
///@}

/**
 * @brief      The filename of a path.
 *
 * @param      pathname  The pathname
 *
 * @return     The filename
 */
inline Types::string Basename( Types::string const & pathname ) 
{
    return  std::string( 
                std::find_if(   pathname.rbegin(), 
                                pathname.rend(),
                                MatchPathSeparator() 
                            ).base(),
                        pathname.end() );
}

/**
 * @brief      Removes an extension.
 *
 * @param      filename  The filename with an extension
 *
 * @return     The filename without the extension.
 */
inline Types::string RemoveExtension( std::string const & filename ) 
{
    std::string::const_reverse_iterator pivot  = std::find( filename.rbegin(), filename.rend(), '.' );
    return pivot == filename.rend() ? filename : std::string( filename.begin(), pivot.base() - 1 );
}

} // namespace egoa::Auxiliary

#endif // EGOA__AUXILIARY__AUXILIARY_HPP

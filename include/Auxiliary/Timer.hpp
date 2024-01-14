/*
 * Timer.hpp
 *
 *  Created on: Jan 29, 2019
 *      Author: Franziska Wegner
 *
 *  Sources of discussion:
 *      * https://blog.habets.se/2010/09/gettimeofday-should-never-be-used-to-measure-time.html
 *      * https://linux.die.net/man/2/clock_gettime
 *      * https://svn.boost.org/trac10/ticket/7719
 *      * stackoverflow.com/q/13478093/175849
 *      * www.opensource.apple.com/source/xnu/xnu-1486.2.11/osfmk/man/clock_get_time.html
 *      * https://www.intel.com/content/dam/www/public/us/en/documents/white-papers/ia-32-ia-64-benchmark-code-execution-paper.pdf
 */

#ifndef EGOA__AUXILIARY__TIMER_HPP
#define EGOA__AUXILIARY__TIMER_HPP

#include "Constants.hpp"
#include "Types.hpp"

// Linux operation systems such as Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, or Centos.
#if defined (__linux__)
    #include <time.h>
    #include <sys/time.h>
// Apple and iOS.
#elif defined(__APPLE__) && defined(__MACH__)
    #include <mach/mach_time.h>
    #include <mach/clock.h>
    #include <mach/mach.h>
// Windows.
#elif defined (_WIN32) || defined (_WIN64)
    #include <time.h>
    #include <windows.h>
#endif

namespace egoa::Auxiliary {

/**
 * @class      Timer
 *
 * @details    The timer class provides an interface to measure the
 *     performance of the code. If not other set/stated the interface provides
 *     the most robust and accurate timer for the underlying operation system.
 *
 * @code{.cpp}
 *      #include <chrono> // just for sleep
 *      #include <thread> // just for sleep
 *
 *      int main(int argc, char *argv[]) {
 *          egoa::Auxiliary::Timer timer = egoa::Auxiliary::Timer();
 *
 *          // Do something
 *          ...
 *          std::this_thread::sleep_for(std::chrono::milliseconds(9999)); // sleep 9999 ms
 *
 *          std::cout << "Timer: " << timer.ElapsedMilliseconds() << std::endl;
 *      }
 * @endcode
 */
class Timer {
    public:
        Timer() { TimeStamp(); }

        inline void Restart () { TimeStamp(); }

        inline Types::largeReal ElapsedMilliseconds() {
            return ElapsedMillisecondsOS();
        }

    private:
/**
 * To use linux specific clock measurements the system must be a linux system
 * such as Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, or Centos.
 */
#if defined (__linux__)
/**
 * System-wide clock measuring the real time (wall-clock). However, note that
 * this timer can be influenced by administrative clock changes, adjtime(), and NTP.
 */
#ifdef EGOA_TIMER_CLOCK_REALTIME
        clockid_t linuxClockId = CLOCK_REALTIME;
/**
 * Fast version of real time measure. However, it lacks in precision. Note
 * that this is available since Linux 2.6.32.
 */
#elif defined(EGOA_TIMER_CLOCK_REALTIME_COARSE)
        clockid_t linuxClockId = CLOCK_REALTIME_COARSE;
/**
 * This is a more stable clock version, since it cannot be set, i.e., it has
 * an unspecified starting point. Thus, this clock cannot be affected by
 * administrative actions on the system clock. However, it can be affected by
 * adjtime() and NTP.
 */
#elif defined(EGOA_TIMER_CLOCK_MONOTONIC)
        clockid_t linuxClockId = CLOCK_MONOTONIC;
/**
 * Fast version of monotonic clock measure. However, it lacks in precision.
 * Note that this is available since Linux 2.6.32.
 */
#elif defined(EGOA_TIMER_CLOCK_MONOTONIC_COARSE)
        clockid_t linuxClockId = CLOCK_MONOTONIC_COARSE;
/**
 * The same as the pure monotonic clock measure, but it is not affected by
 * adjtime() and NTP, since it has access to raw hardware-based time.
 */
#elif defined(EGOA_TIMER_CLOCK_MONOTONIC_RAW)
        clockid_t linuxClockId = CLOCK_MONOTONIC_RAW;
/**
 * The same as the pure monotonic clock measure, but includes time where the
 * system is suspended, i.e., it is a suspend-aware monotonic clock without
 * using a clock (i.e., CLOCK_REALTIME) that is influenced/changed by
 * settimeofday().
 */
#elif defined(EGOA_TIMER_CLOCK_BOOTTIME)
        clockid_t linuxClockId = CLOCK_BOOTTIME;
/**
 * CPU's high-resolution per-process timer.
 */
#elif defined(EGOA_TIMER_CLOCK_PROCESS_CPUTIME_ID)
        clockid_t linuxClockId = CLOCK_PROCESS_CPUTIME_ID;
/**
 * CPU's high-resolution per-thread timer.
 */
#elif defined(EGOA_TIMER_CLOCK_THREAD_CPUTIME_ID)
        clockid_t linuxClockId = CLOCK_THREAD_CPUTIME_ID;
        // inline void GetTime( struct timespec * ts ) {
        //     clock_gettime(CLOCK_THREAD_CPUTIME_ID, ts);
        // }
#else
        clockid_t linuxClockId = CLOCK_MONOTONIC_RAW;
#endif // Specified clock measurement
        struct timespec start_;

        /**
         * @brief      Timestamp
         * @details    Get current time dependent on clock.
         *
         * @param      timeStamp    Timespec
         */
        inline void TimeStamp( struct timespec * timeStamp ) {
            clock_gettime( linuxClockId, timeStamp );
        }

        /**
         * @brief      Timestamp for the start of the timer
         */
        inline void TimeStamp() {
            clock_gettime( linuxClockId, & start_ );
        }

        /**
         * @brief      Elapsed time
         *
         * @details    Calculates the difference between the current time and
         *     start time that represents the duration.
         *
         * @param      elapsedTime    timespec
         */
        inline void ElapsedTime( struct timespec * elapsedTime ) {
            TimeStamp( elapsedTime );
            elapsedTime->tv_sec  = elapsedTime->tv_sec  - start_.tv_sec;
            elapsedTime->tv_nsec = elapsedTime->tv_nsec - start_.tv_nsec;
        }

        /**
         * @brief      Elapsed time in milliseconds
         *
         * @details    Calculates the difference between the current time and
         *     start time that represents the duration.
         *
         * @return     Elapsed time in milliseconds
         */
        inline Types::largeReal ElapsedMillisecondsOS() {
            struct timespec elapsedTime;
            ElapsedTime( & elapsedTime );
            return TimespecToMilliseconds( & elapsedTime );
        }

        /**
         * @brief      Gets the clock resolution representing the granularity.
         * @details    A possible output is
         *             CLOCK_MONOTONIC has a resolution of 1ns, and
         *             CLOCK_MONOTONIC_COARSE has a resolution of 999848ns (about 1ms).
         *
         * @return     The clock resolution.
         */
        inline Types::posInteger GetClockResolution() {
            struct timespec res;
            return clock_getres(linuxClockId, &res);
        }

        /**
         * @brief      Transformations between timespec and milliseconds and
         *     the other way around
         */
        ///@{
            inline void MillisecondsToTimespec ( Types::largeReal milliseconds
                                               , struct timespec * ts )
            {
                Types::largeReal seconds   = milliseconds / Const::MILLISEC_PER_SEC;
                Types::largeReal remainder = milliseconds - seconds * Const::MILLISEC_PER_SEC;
                ts->tv_sec  = seconds;
                ts->tv_nsec = std::llround(remainder * Const::NSEC_PER_MILLISEC);
            }

            inline void TimespecToMilliseconds ( struct timespec * ts
                                               , Types::largeReal & milliseconds )
            {
                milliseconds  = ts->tv_sec  * Const::MILLISEC_PER_SEC;
                milliseconds += static_cast<Types::largeReal>( ts->tv_nsec ) / Const::NSEC_PER_MILLISEC;
            }

            inline Types::largeReal TimespecToMilliseconds ( struct timespec * ts ) {
                return static_cast<Types::largeReal>( ts->tv_sec  * Const::MILLISEC_PER_SEC + ts->tv_nsec ) / Const::NSEC_PER_MILLISEC;
            }
        ///@}
// end of defined (__linux__)
#elif defined(__APPLE__) && defined(__MACH__)  // Apple and iOS
        Types::posInteger start_;

        /**
         * @brief      Timestamp
         * @details    Get current time dependent on clock.
         *
         * @param      timeStamp    Types::posInteger
         */
        inline void TimeStamp( Types::posInteger * timeStamp ) {
            (*timeStamp) = mach_absolute_time();
        }

        /**
         * @brief      Timestamp for the start of the timer
         */
        inline void TimeStamp() {
            start_ = mach_absolute_time();
        }

        /**
         * @brief      Elapsed time
         *
         * @details    Calculates the difference between the current time and
         *     start time that represents the duration.
         *
         * @param      elapsedTime    Types::posInteger
         */
        inline void ElapsedTime( Types::posInteger * elapsedTime ) {
            TimeStamp( elapsedTime );
            (*elapsedTime)  = (*elapsedTime)  - start_;
        }

        /**
         * @brief      Elapsed time in milliseconds
         *
         * @details    Calculates the difference between the current time and
         *     start time that represents the duration.
         *
         * @return     Elapsed time in milliseconds
         */
        inline Types::largeReal ElapsedMillisecondsOS() {
            Types::posInteger elapsedTime;
            ElapsedTime( &elapsedTime );

            mach_timebase_info_data_t info;
            assert( mach_timebase_info (&info) == KERN_SUCCESS); // Check if mach_timebase_info failed

            // nanosecs  = elapsedTime * info.numer / info.denom;
            // millisecs = nanosecs / Const::NSEC_PER_MILLISEC;
            // seconds   = nanosecs / Const::NSEC_PER_SEC;
            return static_cast<Types::largeReal>( elapsedTime * info.numer / info.denom ) / Const::NSEC_PER_MILLISEC;
        }

        /**
         * @brief      Gets the clock resolution representing the granularity.
         * @details    A possible output is
         *             CLOCK_MONOTONIC has a resolution of 1ns, and
         *             CLOCK_MONOTONIC_COARSE has a resolution of 999848ns (about 1ms).
         *
         * @return     The clock resolution.
         */
        inline Types::posInteger GetClockResolution() {
            return 1;
        }
// #elif defined(__unix__)
#elif defined (_WIN32)
        // #error "Windows 32-bit operation system"
        struct timespec start_;

        /**
         * @brief      Timestamp
         * @details    Get current time dependent on clock.
         *
         * @param      timeStamp    Timespec
         */
        inline void TimeStamp( struct timespec * timeStamp ) {
            GetSystemTime( timeStamp );
        }

        /**
         * @brief      Timestamp for the start of the timer
         */
        inline void TimeStamp() {
            GetSystemTime( & start_ );
        }

        /**
         * @brief      Elapsed time
         *
         * @details    Calculates the difference between the current time and
         *     start time that represents the duration.
         *
         * @param      elapsedTime    timespec
         */
        inline void ElapsedTime( struct timespec * elapsedTime ) {
            TimeStamp( elapsedTime );
            elapsedTime->tv_sec  = elapsedTime->tv_sec  - start_.tv_sec;
            elapsedTime->tv_nsec = elapsedTime->tv_nsec - start_.tv_nsec;
        }

        /**
         * @brief      Elapsed time in milliseconds
         *
         * @details    Calculates the difference between the current time and
         *     start time that represents the duration.
         *
         * @return     Elapsed time in milliseconds
         */
        inline Types::largeReal ElapsedMillisecondsOS() {
            struct timespec elapsedTime;
            ElapsedTime( & elapsedTime );
            return TimespecToMilliseconds( & elapsedTime );
        }

        /**
         * @brief      Gets the clock resolution representing the granularity.
         * @details    A possible output is
         *             CLOCK_MONOTONIC has a resolution of 1ns, and
         *             CLOCK_MONOTONIC_COARSE has a resolution of 999848ns (about 1ms).
         *
         * @return     The clock resolution.
         */
        inline Types::posInteger GetClockResolution() {
            struct timespec res;
            return clock_getres(linuxClockId, &res);
        }

        /**
         * @brief      Transformations between timespec and milliseconds and
         *     the other way around
         */
        ///@{
            inline void MillisecondsToTimespec ( Types::largeReal milliseconds
                                               , struct timespec * ts )
            {
                Types::largeReal seconds   = milliseconds / Const::MILLISEC_PER_SEC;
                Types::largeReal remainder = milliseconds - seconds * Const::MILLISEC_PER_SEC;
                ts->tv_sec  = seconds;
                ts->tv_nsec = std::llround(remainder * Const::NSEC_PER_MILLISEC);
            }

            inline void TimespecToMilliseconds ( struct timespec * ts
                                               , Types::largeReal & milliseconds )
            {
                milliseconds  = ts->tv_sec  * Const::MILLISEC_PER_SEC;
                milliseconds += static_cast<Types::largeReal>( ts->tv_nsec ) / Const::NSEC_PER_MILLISEC;
            }

            inline Types::largeReal TimespecToMilliseconds ( struct timespec * ts ) {
                return static_cast<Types::largeReal>( ts->tv_sec  * Const::MILLISEC_PER_SEC + ts->tv_nsec ) / Const::NSEC_PER_MILLISEC;
            }
#elif defined (_WIN64)
//         #error "Windows 64-bit operation system"
        struct timespec start_;

        /**
         * @brief      Timestamp
         * @details    Get current time dependent on clock.
         *
         * @param      timeStamp    Timespec
         */
        inline void TimeStamp( struct timespec * timeStamp ) {
            GetSystemTime( timeStamp );
        }

        /**
         * @brief      Timestamp for the start of the timer
         */
        inline void TimeStamp() {
            GetSystemTime( & start_ );
        }

        /**
         * @brief      Elapsed time
         *
         * @details    Calculates the difference between the current time and
         *     start time that represents the duration.
         *
         * @param      elapsedTime    timespec
         */
        inline void ElapsedTime( struct timespec * elapsedTime ) {
            TimeStamp( elapsedTime );
            elapsedTime->tv_sec  = elapsedTime->tv_sec  - start_.tv_sec;
            elapsedTime->tv_nsec = elapsedTime->tv_nsec - start_.tv_nsec;
        }

        /**
         * @brief      Elapsed time in milliseconds
         *
         * @details    Calculates the difference between the current time and
         *     start time that represents the duration.
         *
         * @return     Elapsed time in milliseconds
         */
        inline Types::largeReal ElapsedMillisecondsOS() {
            struct timespec elapsedTime;
            ElapsedTime( & elapsedTime );
            return TimespecToMilliseconds( & elapsedTime );
        }

        /**
         * @brief      Gets the clock resolution representing the granularity.
         * @details    A possible output is
         *             CLOCK_MONOTONIC has a resolution of 1ns, and
         *             CLOCK_MONOTONIC_COARSE has a resolution of 999848ns (about 1ms).
         *
         * @return     The clock resolution.
         */
        inline Types::posInteger GetClockResolution() {
            struct timespec res;
            return clock_getres(linuxClockId, &res);
        }

        /**
         * @brief      Transformations between timespec and milliseconds and
         *     the other way around
         */
        ///@{
            inline void MillisecondsToTimespec ( Types::largeReal milliseconds
                                               , struct timespec * ts )
            {
                Types::largeReal seconds   = milliseconds / Const::MILLISEC_PER_SEC;
                Types::largeReal remainder = milliseconds - seconds * Const::MILLISEC_PER_SEC;
                ts->tv_sec  = seconds;
                ts->tv_nsec = std::llround(remainder * Const::NSEC_PER_MILLISEC);
            }

            inline void TimespecToMilliseconds ( struct timespec * ts
                                               , Types::largeReal & milliseconds )
            {
                milliseconds  = ts->tv_sec  * Const::MILLISEC_PER_SEC;
                milliseconds += static_cast<Types::largeReal>( ts->tv_nsec ) / Const::NSEC_PER_MILLISEC;
            }

            inline Types::largeReal TimespecToMilliseconds ( struct timespec * ts ) {
                return static_cast<Types::largeReal>( ts->tv_sec  * Const::MILLISEC_PER_SEC + ts->tv_nsec ) / Const::NSEC_PER_MILLISEC;
            }
#endif
};

} // namespace egoa::Auxiliary

#endif // EGOA__AUXILIARY__TIMER_HPP

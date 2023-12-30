# SetEnvironmentVariables.cmake
#
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#
# Set environment variables that are used for, e.g.,
# - OpenMP
# - ...
#

# Set OpenMP variables
message( STATUS "Set OpenMP variables" )

set(ENV{OMP_WAIT_POLICY} "ACTIVE")
message( STATUS "${MY_SPACE}OMP_WAIT_POLICY:\t\t\t" $ENV{OMP_WAIT_POLICY})

# Stack size of each OpenMP threads
message( STATUS "${MY_SPACE}OMP_STACKSIZE:\t\t\t" $ENV{OMP_STACKSIZE} )

# Specifies schedule type and chunk size for the loops.
message( STATUS "${MY_SPACE}OMP_SCHEDULE:\t\t\t\t" $ENV{OMP_SCHEDULE} )

# Avoid OpenMP threads to be moved.
set(ENV{OMP_PROC_BIND} "TRUE")
message( STATUS "${MY_SPACE}OMP_PROC_BIND:\t\t\t\t" $ENV{OMP_PROC_BIND} )

# Thread limit of OpenMP
set(ENV{OMP_THREAD_LIMIT} "${EGOA_THREAD_LIMIT}")
message( STATUS "${MY_SPACE}OMP_THREAD_LIMIT:\t\t\t" $ENV{OMP_THREAD_LIMIT} )

# Number of OpenMP threads
include(ProcessorCount)
ProcessorCount(NUMBER_OF_PROCESSORS)
if(NOT NUMBER_OF_PROCESSORS EQUAL 0)
    message( STATUS "${MY_SPACE}Number of processors:\t\t${NUMBER_OF_PROCESSORS}" )
    set(CTEST_BUILD_FLAGS -j${NUMBER_OF_PROCESSORS})
    set(ENV{OMP_NUM_THREADS} ${NUMBER_OF_PROCESSORS})
    message( STATUS "${MY_SPACE}OMP_NUM_THREADS:\t\t\t" $ENV{OMP_NUM_THREADS} )
    set(ctest_test_args ${ctest_test_args} PARALLEL_LEVEL ${NUMBER_OF_PROCESSORS})
endif()

# EGOA_THREAD_LIMIT is not 0 use the user configuration
if(NOT EGOA_THREAD_LIMIT EQUAL 0)
    message( STATUS "Reset OpenMP compute configuration to CMAKE configuration" )
    message( STATUS "${MY_SPACE}EGOA_THREAD_LIMIT:\t\t\t" ${EGOA_THREAD_LIMIT} )
    set(ENV{OMP_NUM_THREADS} ${EGOA_THREAD_LIMIT})
    message( STATUS "${MY_SPACE}OMP_NUM_THREADS:\t\t\t" $ENV{OMP_NUM_THREADS} )
endif()
message( STATUS )

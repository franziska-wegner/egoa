# OpenMP.cmake
#
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#
# If EGOA_ENABLE_OPENMP is ON the script adds the target to use the <omp.h>
# header in the project.
#
# Installation of OpenMP
#   * To install OpenMP on Mac use:
#     * OPENMP: brew install llvm   PATH: /usr/local/Cellar/llvm/5.0.1/bin/clang
#     * CPP = /usr/local/opt/llvm/bin/clang | CPPFLAGS = -I/usr/local/opt/llvm/include -fopenmp
#                                           | LDFLAGS  = -L/usr/local/opt/llvm/lib

message(STATUS "OpenMP enabled: " ${EGOA_ENABLE_OPENMP})

# ${CMAKE_CXX_COMPILER}  ---  /usr/local/Cellar/llvm/9.0.0/bin/clang++
# /usr/local/opt/llvm@8/   or     /usr/local/Cellar/llvm@8/8.0.1/bin/clang++
# /usr/local/opt/llvm@7/   or     /usr/local/Cellar/llvm@7/7.1.0/bin/clang++

if ( EGOA_ENABLE_OPENMP AND NOT OPENMP_LIBRARIES OR NOT OPENMP_INCLUDES )
# OpenMP Library
    set(OPENMP_LIBRARIES "/usr/local/Cellar/llvm@8/8.0.1_1/lib" CACHE FILEPATH "Path to the OpenMP libraries." FORCE)
# OpenMP Includes
    set(OPENMP_INCLUDES "/usr/local/Cellar/llvm@8/8.0.1_1/include" CACHE FILEPATH "Path to the OpenMP includes." FORCE)
endif ( EGOA_ENABLE_OPENMP AND NOT OPENMP_LIBRARIES OR NOT OPENMP_INCLUDES )

message(STATUS "${MY_SPACE}OPENMP_LIBRARIES:\t\t\t\t" ${OPENMP_LIBRARIES})
message(STATUS "${MY_SPACE}OPENMP_INCLUDES:\t\t\t\t" ${OPENMP_INCLUDES})

####################################################################
# Find OpenMP ######################################################
####################################################################
if(APPLE AND EGOA_ENABLE_OPENMP)
    if(CMAKE_C_COMPILER_ID MATCHES "Clang")
        set(OpenMP_C "${CMAKE_C_COMPILER}")
        set(OpenMP_C_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
        set(OpenMP_C_LIB_NAMES "libomp" "libgomp" "libiomp5")
        set(OpenMP_libomp_LIBRARY ${OpenMP_C_LIB_NAMES})
        set(OpenMP_libgomp_LIBRARY ${OpenMP_C_LIB_NAMES})
        set(OpenMP_libiomp5_LIBRARY ${OpenMP_C_LIB_NAMES})
    endif()
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(OpenMP_CXX "${CMAKE_CXX_COMPILER}")
        set(OpenMP_CXX_FLAGS "-fopenmp=libomp -Wno-unused-command-line-argument")
        set(OpenMP_CXX_LIB_NAMES "libomp" "libgomp" "libiomp5")
        set(OpenMP_libomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
        set(OpenMP_libgomp_LIBRARY ${OpenMP_CXX_LIB_NAMES})
        set(OpenMP_libiomp5_LIBRARY ${OpenMP_CXX_LIB_NAMES})
    endif()
endif()

if(EGOA_ENABLE_OPENMP)
    find_package(OpenMP) # REQUIRED
endif(EGOA_ENABLE_OPENMP)

if (APPLE AND OPENMP_FOUND)
    include_directories("${OPENMP_INCLUDES}")
    link_directories("${OPENMP_LIBRARIES}")
    # set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

####################################################################
# Output Message ###################################################
####################################################################
if(EGOA_ENABLE_OPENMP AND NOT OPENMP_FOUND)
    message( FATAL_ERROR
      "OpenMP is enabled, but not available on the system. Please, check the \
      specification of your compiler or disable OpenMP by setting \
      EGOA_ENABLE_OPENMP to OFF." )
endif(EGOA_ENABLE_OPENMP AND NOT OPENMP_FOUND)

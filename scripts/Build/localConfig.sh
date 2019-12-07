#!/bin/sh
#
# localConfig.sh
# 
#   Created on:
#       Author: Franziska Wegner
#       
# Project configuration on the local computer to avoid "ccmake ."
# configuration.
# 
#########################################################
# Define local standard argument ########################
#########################################################

# Environment variable /Users/fw/Documents/work/frameworks/egoa/external_libraries/Bonming-1.8/build/include/coin
BONMIN_ROOT_DIR="/Users/fw/Documents/work/frameworks/egoa/external_libraries/Bonming-1.8/build"

# Build information
BUILD_DIR_RELEASE="/Users/fw/Documents/work/frameworks/egoa/build-release"
BUILD_DIR_DEBUG="/Users/fw/Documents/work/frameworks/egoa/build-debug"
BUILD_MODE="Release"
BUILD_CLEAN_DIR="FALSE"

# Cmake target
CMAKE_TARGET="/Users/fw/Documents/work/frameworks/egoa/framework"

# Compiler
CMAKE_CXX_COMPILER="/usr/local/Cellar/llvm@7/7.1.0_1/bin/clang++",
CMAKE_C_COMPILER="/usr/local/Cellar/llvm@7/7.1.0_1/bin/clang",

# Enable/Disable Tools 
EGOA_ENABLE_BONMIN="ON"
EGOA_ENABLE_BOOST="OFF"
EGOA_ENABLE_CPLEX="ON"
EGOA_ENABLE_DOCUMENTATION="ON"
EGOA_ENABLE_EXCEPTION_HANDLING="ON"
EGOA_ENABLE_GUROBI="ON"
EGOA_ENABLE_IPOPT="OFF"
EGOA_ENABLE_OGDF="ON"
EGOA_ENABLE_OPENMP="ON"
EGOA_ENABLE_TESTS="ON"
EGOA_ENABLE_VERBOSE_MAKEFILE="ON"
# Select test framework
EGOA_TEST_FRAMEWORK="OfflineGoogleTestFramework" 
# The following path is used when
# EGOA_TEST_FRAMEWORK="OfflineGoogleTestFramework" otherwise it will be
# ignored
EGOA_TEST_FRAMEWORK_LOCATION="external/GoogleTestFramework" 
# Number of Threads
# EGOA_THREAD_LIMIT="0", i.e., uses the maximum possible number of threads
EGOA_THREAD_LIMIT="1"
# Compiler flags
EGOA_PEDANTIC_AS_ERRORS="OFF"
EGOA_PEDANTIC_MODE="ON"
EGOA_WARNINGS_AS_ERRORS="ON"

# Gurobi
GUROBI_ROOT_DIR="/Library/gurobi800"
GUROBI_INCLUDE="${GUROBI_HOME}/mac64/include"
GUROBI_LIBRARIES="${GUROBI_HOME}/mac64/lib/libgurobi_c++.a;${GUROBI_HOME}/mac64/lib/libgurobi75.so"

# OGDF Release
OGDF_AUTOGEN_INCLUDE_DIR_RELEASE="/Users/fw/Documents/work/frameworks/egoa/external_libraries/ogdf20170723/include"
OGDF_INCLUDE_DIR_RELEASE="/Users/fw/Documents/work/frameworks/egoa/external_libraries/ogdf20170723/include"
OGDF_LIBRARY_DIR_RELEASE="/Users/fw/Documents/work/frameworks/egoa/external_libraries/ogdf20170723"
# OGDF Debug
OGDF_AUTOGEN_INCLUDE_DIR_DEBUG="/Users/fw/Documents/work/frameworks/egoa/external_libraries/ogdf-debug/include"
OGDF_INCLUDE_DIR_DEBUG="/Users/fw/Documents/work/frameworks/egoa/external_libraries/ogdf20170723-debug/include"
OGDF_LIBRARY_DIR_DEBUG="/Users/fw/Documents/work/frameworks/egoa/external_libraries/ogdf-debug"
# OGDF flags
OGDF_WARNING_ERRORS_DEBUG="ON"
OGDF_USE_ASSERT_EXCEPTIONS_DEBUG="ON"
OGDF_WARNING_ERRORS_RELEASE="ON"
OGDF_USE_ASSERT_EXCEPTIONS_RELEASE="ON"
# @todo comp in cmake
OGDF_AUTOGEN_INCLUDE_DIR="/Users/fw/Documents/work/frameworks/egoa/external_libraries/ogdf-debug/include",
OGDF_INCLUDE_DIR="/Users/fw/Documents/work/frameworks/egoa/external_libraries/ogdf20170723-debug/include",
OGDF_LIBRARY_DIR="/Users/fw/Documents/work/frameworks/egoa/external_libraries/ogdf-debug",

# Bonmin
BONMIN_ROOT_DIR="/Users/fw/Documents/work/frameworks/egoa/external_libraries/Bonming-1.8/build",

# Boost
Boost_DIRECTORIES="/usr/local/Cellar/boost/1.71.0/",
Boost_NO_SYSTEM_PATHS="TRUE",

# COIN Release
COIN_INCLUDE_DIR_RELEASE="$OGDF_INCLUDE_DIR_RELEASE"
COIN_LIBRARY_DIR_RELEASE="$OGDF_LIBRARY_DIR_RELEASE"
# COIN Debug
COIN_INCLUDE_DIR_DEBUG="$OGDF_INCLUDE_DIR_DEBUG"
COIN_LIBRARY_DIR_DEBUG="$OGDF_LIBRARY_DIR_DEBUG"
# sublimetexproject
COIN_INCLUDE_DIR="/Users/fw/Documents/work/frameworks/egoa/external_libraries/ogdf-debug/include",
COIN_LIBRARY_DIR="/Users/fw/Documents/work/frameworks/egoa/external_libraries/ogdf-debug",

# Cplex
CPLEX_HOME="/Applications/CPLEX_Studio128",

# OPENMP
OPENMP_INCLUDES="/usr/local/Cellar/llvm/5.0.1/include"
OPENMP_LIBRARIES="/usr/local/Cellar/llvm/5.0.1/lib"

#!/bin/sh
#
# buildProject.sh
#
#   Created on:
#       Author: Franziska Wegner
#
# Project configuration on the server to avoid "ccmake ." configuration.
#
#########################################################
# Define local standard argument ########################
#########################################################

# Environment variable
BONMIN_ROOT_DIR="<path-to-project>/externalLibraries/Bonming-1.8/build"

# Build information
BUILD_DIR_RELEASE="<path-to-folder-with>/egoa/build-release"
BUILD_DIR_DEBUG="<path-to-folder-with>/egoa/build-debug"
BUILD_MODE="Release"
BUILD_CLEAN_DIR="TRUE"

# Cmake target
CMAKE_TARGET="TODO/egoa/framework"

# Compiler
CMAKE_CXX_COMPILER="/usr/bin/g++-7"
CMAKE_C_COMPILER="/usr/bin/gcc-7"

# Enable/Disable Tools
EGOA_ENABLE_BONMIN="ON"
EGOA_ENABLE_BOOST="OFF"
EGOA_ENABLE_DOCUMENTATION="ON"
EGOA_ENABLE_EXCEPTION_HANDLING="ON"
EGOA_ENABLE_GUROBI="ON"
EGOA_ENABLE_IPOPT="OFF"
EGOA_ENABLE_OGDF="ON"
EGOA_ENABLE_OPENMP="ON"
EGOA_ENABLE_TESTS="ON"
EGOA_ENABLE_VERBOSE_MAKEFILE="ON"
# Select test framework
EGOA_TEST_FRAMEWORK="OnlineGoogleTestFramework"
EGOA_TEST_FRAMEWORK_LOCATION=""
# Number of Threads
EGOA_THREAD_LIMIT="1"
# Compiler flags
EGOA_PEDANTIC_AS_ERRORS="OFF"
EGOA_PEDANTIC_MODE="ON"
EGOA_WARNINGS_AS_ERRORS="ON"

# Gurobi
GUROBI_HOME="/opt/gurobi800/linux64"
GUROBI_INCLUDE="${GUROBI_HOME}/mac64/include"
GUROBI_LIBRARIES="${GUROBI_HOME}/mac64/lib/libgurobi_c++.a;${GUROBI_HOME}/mac64/lib/libgurobi75.so"

# OGDF Release
OGDF_AUTOGEN_INCLUDE_DIR_RELEASE="/<path-to-project>/externalLibraries/OGDF/ogdf20170723/build-release/include"
OGDF_INCLUDE_DIR_RELEASE="/<path-to-project>/externalLibraries/OGDF/ogdf20170723/include"
OGDF_LIBRARY_DIR_RELEASE="/<path-to-project>/externalLibraries/OGDF/ogdf20170723/build-release"
# OGDF Debug
OGDF_AUTOGEN_INCLUDE_DIR_DEBUG="/<path-to-project>/externalLibraries/OGDF/ogdf20170723/build-debug/include"
OGDF_INCLUDE_DIR_DEBUG="/<path-to-project>/externalLibraries/OGDF/ogdf20170723/include"
OGDF_LIBRARY_DIR_DEBUG="/<path-to-project>/externalLibraries/OGDF/ogdf20170723/build-debug"
# OGDF flags
OGDF_WARNING_ERRORS_DEBUG="ON"
OGDF_USE_ASSERT_EXCEPTIONS_DEBUG="ON"
OGDF_WARNING_ERRORS_RELEASE="OFF"
OGDF_USE_ASSERT_EXCEPTIONS_RELEASE="OFF"

# COIN Release
COIN_INCLUDE_DIR_RELEASE="$OGDF_INCLUDE_DIR_RELEASE"
COIN_LIBRARY_DIR_RELEASE="$OGDF_LIBRARY_DIR_RELEASE"
# COIN Debug
COIN_INCLUDE_DIR_DEBUG="$OGDF_INCLUDE_DIR_DEBUG"
COIN_LIBRARY_DIR_DEBUG="$OGDF_LIBRARY_DIR_DEBUG"

# OPENMP - Not needed for Linux
OPENMP_INCLUDES=""
OPENMP_LIBRARIES=""

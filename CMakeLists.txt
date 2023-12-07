# CMakeLists.txt
# 
#   Created on: 30.01.2019
#       Author: Franziska Wegner
#       
# Main cmake configuration file.
# 

cmake_minimum_required ( VERSION 3.13.1 ) 
project ( EGOA CXX )

# The version number.
set ( EGOA_VERSION_MAJOR 1 )
set ( EGOA_VERSION_MINOR 0 )

####################################################################
# Input Parameter ##################################################
####################################################################

message ( STATUS "${PROJECT_INCLUDE_DIR}" )
message ( STATUS "${PROJECT_SOURCE_DIR}" )
message ( STATUS "${CMAKE_MODULE_PATH}" )
message ( STATUS "${CMAKE_CURRENT_BINARY_DIR}" )

set ( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake )
include ( InputProperties )

if ( EGOA_ENABLE_VERBOSE_MAKEFILE )
    set ( CMAKE_VERBOSE_MAKEFILE TRUE )
else ( EGOA_ENABLE_VERBOSE_MAKEFILE )
    set ( CMAKE_VERBOSE_MAKEFILE FALSE )
endif ( EGOA_ENABLE_VERBOSE_MAKEFILE )

if ( EGOA_TEST_FRAMEWORK STREQUAL "OfflineGoogleTestFramework" AND EGOA_ENABLE_TESTS )
    if ( NOT EGOA_TEST_FRAMEWORK_LOCATION )
        if ( EXISTS ${EGOA_GOOGLE_TEST_FRAMEWORK_STD_LOCATION} )
            set ( EGOA_TEST_FRAMEWORK_LOCATION ${EGOA_GOOGLE_TEST_FRAMEWORK_STD_LOCATION} )
        else()
            message ( WARNING "Location of the google test framework not found (default: \"${EGOA_GOOGLE_TEST_FRAMEWORK_STD_LOCATION}\"). Switch to online version." )
            set ( EGOA_TEST_FRAMEWORK "OnlineGoogleTestFramework" )
        endif()
    endif()
endif()

set ( MY_SPACE "\t")

####################################################################
# Compiler options #################################################
####################################################################

set ( CMAKE_CXX_STANDARD 17 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )
set ( CMAKE_CXX_EXTENSIONS OFF )

# specify the cross compiler
set ( CMAKE_C_COMPILER_ID GNU )

# Set cmake build type
if ( EGOA_BUILD_TYPE )
    set ( CMAKE_BUILD_TYPE "${EGOA_BUILD_TYPE}" )
else ( EGOA_BUILD_TYPE )
    set ( CMAKE_BUILD_TYPE "Debug" )
endif ( EGOA_BUILD_TYPE )

# Build options
set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib )
set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib )
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin )
set ( PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR} )

set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

####################################################################
# Find external libraries ##########################################
#################################################################### 

# Initial Configuration
include ( SetEnvironmentVariables )
include ( CompilerConfiguration )
include ( HelperFunctions )
include ( ExternalProjectConfiguration )

# Find External Libraries
include(QtConfiguration)

if ( EGOA_ENABLE_DOCUMENTATION )
    configure_file ( DoxyfileConfig.in ${PROJECT_INCLUDE_DIR}/Doxyfile.in )
    include ( Doxygen )
endif ( EGOA_ENABLE_DOCUMENTATION )

if ( EGOA_ENABLE_OPENMP )
    include ( OpenMP )
endif ( EGOA_ENABLE_OPENMP )

# Find solvers
if ( EGOA_ENABLE_GUROBI )
    find_package ( Gurobi REQUIRED )
endif ( EGOA_ENABLE_GUROBI )

if ( EGOA_ENABLE_CPLEX )
    find_package ( Cplex REQUIRED )
endif ( EGOA_ENABLE_CPLEX )

if ( EGOA_ENABLE_IPOPT )
    find_package ( Ipopt )
endif ( EGOA_ENABLE_IPOPT )

if ( EGOA_ENABLE_BONMIN )
    find_package ( Bonmin )
endif ( EGOA_ENABLE_BONMIN )

# Find external libraries
if ( EGOA_ENABLE_OGDF )
    find_package ( OGDF )
endif ( EGOA_ENABLE_OGDF )

if ( EGOA_ENABLE_BOOST )
    include ( Boost )
endif ( EGOA_ENABLE_BOOST )

# Google tests
if ( EGOA_ENABLE_TESTS )
    include ( CTest )
    # Temp for all, maybe only Windows and MacOS
    include(FindGoogleTestFramework)
    # if ( EGOA_TEST_FRAMEWORK STREQUAL "OfflineGoogleTestFramework" )
    #     find_package ( GoogleTestFramework PATHS ${EGOA_TEST_FRAMEWORK_LOCATION})
    # elseif ( EGOA_TEST_FRAMEWORK STREQUAL "OnlineGoogleTestFramework" )
    #     find_package ( GoogleTestFrameworkOnlineVersion )
    # else ()
    #     find_package ( GoogleTestFramework )
    # endif ()

    # Add test coverage 
    # -coverage includes -fprofile-arcs -ftest-coverage while compiling and
    # -lgcov while linking -coverage
    # 
    # brew install lcov || gcovr (https://gcovr.com/en/stable/)
    # 
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${EGOA_COVERAGE_COMPILE_FLAGS}")
    # set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${EGOA_COVERAGE_LINK_FLAGS}")
endif(EGOA_ENABLE_TESTS)

# Generate an internal header automatically
# file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/include")
# configure_file("${CMAKE_MODULE_PATH}/mtsf_internal_configuration.h.in" "${CMAKE_CURRENT_BINARY_DIR}/include/mtsf_internal_configuration.h")

if ( OGDF_FOUND AND COIN_FOUND )
    message( STATUS "OGDF and COIN include directory and library are added to the project.")
    include_directories(SYSTEM ${OGDF_INCLUDE_DIR} ${OGDF_AUTOGEN_INCLUDE_DIR} ${COIN_INCLUDE_DIRS} GUROBI_INCLUDE_DIRS} ${CPLEX_INCLUDE_DIRS})
    include_directories(${PROJECT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}/include)
    link_directories(${OGDF_LIBRARY_DIR} ${COIN_LIBRARY_DIR})
elseif ( OGDF_FOUND )
    message( STATUS "OGDF include directory and library are added to the project.")
    include_directories(SYSTEM ${OGDF_INCLUDE_DIR} ${OGDF_AUTOGEN_INCLUDE_DIR} ${GUROBI_INCLUDE_DIRS} ${CPLEX_INCLUDE_DIRS})
    include_directories(${PROJECT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}/include)
    link_directories(${OGDF_LIBRARY_DIR})
elseif ( COIN_FOUND )
    message( STATUS "COIN include directory and library are added to the project.")
    include_directories(SYSTEM ${COIN_INCLUDE_DIRS} ${GUROBI_INCLUDE_DIRS} ${CPLEX_INCLUDE_DIRS})
    include_directories(${PROJECT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}/include)
    link_directories(${COIN_LIBRARY_DIR})
else()  
    message( STATUS "Neither OGDF nor COIN include directory and library are added to the project.")
    include_directories(SYSTEM ${GUROBI_INCLUDE_DIRS} ${CPLEX_INCLUDE_DIRS})
    include_directories(${PROJECT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}/include)
endif()

####################################################################
# Add files, libraries and sources #################################
#################################################################### 
file ( GLOB_RECURSE HEADERS ${PROJECT_INCLUDE_DIR} include/*.hpp )
file ( GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp ) 
file ( GLOB_RECURSE SOURCES_REMOVE ${PROJECT_SOURCE_DIR}/src/Runnables/*.cpp )
list ( FILTER SOURCES EXCLUDE REGEX ".*Runnables.*" )

# Add library target EGOA to be build from the source files
add_library ( EGOA ${SOURCES} )
target_link_libraries ( EGOA ${QT6_LIBRARIES} )

# Add subdirectory here the source directory with the corresponding
# CMakeLists.txt
add_subdirectory ( src )
# include_directories(${PROJECT_INCLUDE_DIR})

####################################################################
# Testing ##########################################################
#################################################################### 
if ( EGOA_ENABLE_TESTS )
    add_subdirectory ( tests )
    enable_testing()
    # Build all of gtest's own tests.
    set ( gtest_build_tests ON )
endif ( EGOA_ENABLE_TESTS )

####################################################################
# Documentation ###################################################
####################################################################
message ( STATUS "")
message ( STATUS "Compiler:")
# the compiler used for C files
message ( STATUS "${MY_SPACE}CMAKE_C_COMPILER:\t\t" ${CMAKE_C_COMPILER} )
# the compiler used for C++ files
message ( STATUS "${MY_SPACE}CMAKE_CXX_COMPILER:\t\t" ${CMAKE_CXX_COMPILER} )
# Verbose mode - make VERBOSE = 1?
message ( STATUS "${MY_SPACE}make VERBOSE = 1? :\t\t" ${CMAKE_VERBOSE_MAKEFILE} )

message ( STATUS "")
message ( STATUS "Other important targets:")

# QT5 found
if ( Qt6_FOUND )
    message ( STATUS "${MY_SPACE}qt6:\t\t\t\tadd libraries of QT6" )
    target_compile_definitions ( EGOA PUBLIC QT6_AVAILABLE )
endif ( Qt6_FOUND )

# OpenMP found
if ( OPENMP_FOUND )
    message ( STATUS "${MY_SPACE}OpenMP:\t\t\t\tadd libraries of OpenMP" )
    target_compile_definitions ( EGOA PUBLIC OPENMP_AVAILABLE )
endif ( OPENMP_FOUND )

# Doxygen found
if ( DOXYGEN_FOUND )
    message ( STATUS "${MY_SPACE}doc:\t\t\t\tbuild doxygen documentation" )
endif ( DOXYGEN_FOUND )

# Boost found
if ( Boost_FOUND )
    message ( STATUS "${MY_SPACE}Boost:\t\t\t\tadd library boost" )
    target_compile_definitions ( EGOA PUBLIC BOOST_AVAILABLE )
endif ( Boost_FOUND )

# OGDF found
if ( OGDF_FOUND )
    message ( STATUS "${MY_SPACE}OGDF:\t\t\t\tadd libraries of OGDF" )
    target_compile_definitions ( EGOA PUBLIC OGDF_AVAILABLE )
endif ( OGDF_FOUND )

# Gurobi found
if ( GUROBI_FOUND )
    message ( STATUS "${MY_SPACE}GUROBI:\t\t\t\tadd libraries of GUROBI" )
    target_compile_definitions ( EGOA PUBLIC GUROBI_AVAILABLE )
endif ( GUROBI_FOUND )

# Cplex found
if ( CPLEX_FOUND )
    message ( STATUS "${MY_SPACE}CPLEX:\t\t\t\tadd libraries of CPLEX" )
    target_compile_definitions ( EGOA PUBLIC CPLEX_AVAILABLE )
endif ( CPLEX_FOUND )

# Cplex found
if ( EGOA_CPLEX_VERSION )
    message ( STATUS "${MY_SPACE}CPLEX Version:\t\t${EGOA_CPLEX_VERSION_MAJOR}.${EGOA_CPLEX_VERSION_MINOR} (${EGOA_CPLEX_VERSION})" )
    target_compile_definitions ( EGOA PUBLIC EGOA_CPLEX_VERSION=${EGOA_CPLEX_VERSION} )
    target_compile_definitions ( EGOA PUBLIC EGOA_CPLEX_VERSION_MAJOR=${EGOA_CPLEX_VERSION_MAJOR} )
    target_compile_definitions ( EGOA PUBLIC EGOA_CPLEX_VERSION_MINOR=${EGOA_CPLEX_VERSION_MINOR} )
endif ( EGOA_CPLEX_VERSION )

# Ipopt found
if ( IPOPT_FOUND )
    message ( STATUS "${MY_SPACE}IPOPT:\t\t\t\tadd libraries of IPOPT" )
    target_compile_definitions ( EGOA PUBLIC IPOPT_AVAILABLE )
endif ( IPOPT_FOUND )

# Bonmin found
if ( BONMIN_FOUND )
    message ( STATUS "${MY_SPACE}BONMIN:\t\t\t\tadd libraries of BONMIN" )
    target_compile_definitions ( EGOA PUBLIC BONMIN_AVAILABLE )
endif ( BONMIN_FOUND )

if ( EGOA_ENABLE_EXCEPTION_HANDLING )
    message(STATUS "${MY_SPACE}EGOA Exceptions:\t\t${EGOA_ENABLE_EXCEPTION_HANDLING}")
    target_compile_definitions(EGOA PUBLIC EGOA_ENABLE_EXCEPTION_HANDLING)
endif ( EGOA_ENABLE_EXCEPTION_HANDLING )

if ( EGOA_ENABLE_ASSERTION AND CMAKE_BUILD_TYPE STREQUAL "Debug" )
    message(STATUS "${MY_SPACE}EGOA Assertions:\t\t${EGOA_ENABLE_ASSERTION}")
    target_compile_definitions(EGOA PUBLIC EGOA_ENABLE_ASSERTION)
endif ( )

# Define a macro to get number of configured threads
target_compile_definitions ( EGOA PUBLIC EGOA_USER_DEFINED_THREAD_LIMIT=$ENV{OMP_NUM_THREADS} )

# 
target_compile_definitions ( EGOA PUBLIC EGOA_ENABLE_STATISTIC_DTP )
target_compile_definitions ( EGOA PUBLIC EGOA_ENABLE_STATISTIC_BETWEENNESS_CENTRALITY )

message ( STATUS "")
message ( STATUS "Build type is set to:\t\t" ${CMAKE_BUILD_TYPE})
message ( STATUS "Build files have been written to:\t" ${CMAKE_CURRENT_BINARY_DIR} )
message ( STATUS "Runtime output directory:\t\t" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
message ( STATUS "Archive output directory:\t\t" ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} )
message ( STATUS "Library output directory:\t\t" ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} )
message ( STATUS "")

####################################################################
# Clean command ####################################################
####################################################################
# Proper cleanup while using "make clean"
set_property ( DIRECTORY PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    "${PROJECT_INCLUDE_DIR}/Doxyfile.in"
    "${PROJECT_INCLUDE_DIR}/DoxygenWarningLogs.txt"
    "${PROJECT_INCLUDE_DIR}/documentation/html"
    "${PROJECT_INCLUDE_DIR}/documentation/*.tmp"
    "${PROJECT_INCLUDE_DIR}/documentation/Doxyfile"
    "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/00-Matpower-Data"
    "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/01-Pypower-Data"
    # "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/02-gml"
    "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/03-IEEE-Power_Flow_Test_Cases"
    "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/04-IEEE-Dynamic_Test_Cases"
    "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/05-IEEE-Reliability_Test_Systems-RTS"
    "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/06-IEEE-Voltage_Collapse_Sensitivities"
    "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/07-PEGASE_Test_Cases"
    "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/08-Edinburgh_Power_Flow_Test_Cases"
    "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/09-Edinburgh_Dynamic_Test_Cases"
    # "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/10-NESTA"
    # "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/11-Dimacs"
    # "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/12-Hitting-Sets"
    # "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/13-Publication_Test_Cases"
    # "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/14-EIRGrid_Test_Cases"
    # "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/15-Synthetic_Power_Grid_Test_Cases"
    # "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/16-Literature_Based_Power_Flow_Test_Cases"
    # "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/17-Small_Signal_Stability_Test_Cases"
    "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/18-IEEE-Data_Formats"
    "${PROJECT_INCLUDE_DIR}/data/PowerGrids/IEEE/19-Power_System_Application_Data_Dictionary"
    "${PROJECT_INCLUDE_DIR}/data/PowerGrids/PyPSA/pypsa-eur/*"
    "${PROJECT_INCLUDE_DIR}/data/PowerGrids/PyPSA/pypsa-iti-collaboration/elec*"
    "${PROJECT_INCLUDE_DIR}/data/PowerGrids/SciGrid"
    "${PROJECT_INCLUDE_DIR}/data/Windfarms/Networks"
    "${CMAKE_CURRENT_BINARY_DIR}/bin"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_install.cmake"
    # "${CMAKE_CURRENT_BINARY_DIR}/CMakeCache.txt" #c
    "${CMAKE_CURRENT_BINARY_DIR}/CMakeDoxyfile.in"
    "${CMAKE_CURRENT_BINARY_DIR}/CMakeDoxygenDefaults.cmake"
    # "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles" #c
    "${CMAKE_CURRENT_BINARY_DIR}/CTestTestfile.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/DartConfiguration.tcl"
    "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.in"
    "${CMAKE_CURRENT_BINARY_DIR}/DoxyfileConfig.in"
    "${CMAKE_CURRENT_BINARY_DIR}/googletest-build"
    "${CMAKE_CURRENT_BINARY_DIR}/googletest-download"
    "${CMAKE_CURRENT_BINARY_DIR}/googletest-src"
    "${CMAKE_CURRENT_BINARY_DIR}/lib"
    # "${CMAKE_CURRENT_BINARY_DIR}/Makefile" #c
    "${CMAKE_CURRENT_BINARY_DIR}/PGT_autogen"
    "${CMAKE_CURRENT_BINARY_DIR}/src/cmake_install.cmake"
    # "${CMAKE_CURRENT_BINARY_DIR}/src/CMakeFiles" #c
    "${CMAKE_CURRENT_BINARY_DIR}/src/CTestTestfile.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/src/Makefile"
    "${CMAKE_CURRENT_BINARY_DIR}/src/pgt_autogen"
    "${CMAKE_CURRENT_BINARY_DIR}/Testing"
    "${CMAKE_CURRENT_BINARY_DIR}/tests/cmake_install.cmake"
    # "${CMAKE_CURRENT_BINARY_DIR}/tests/CMakeFiles" #c
    "${CMAKE_CURRENT_BINARY_DIR}/tests/CTestTestfile.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/tests/Makefile"
    "${CMAKE_CURRENT_BINARY_DIR}/tests/TestQueues_autogen"
)

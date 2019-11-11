# FindOGDF.cmake
# 
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#       
# If EGOA_ENABLE_OGDF is ON the script searches for OGDF and COIN in given and
# standard location. If found it adds the library to the project by adding the
# include paths and libraries to the project.
# 

get_filename_component(PARENT_DIRECTORY ${PROJECT_SOURCE_DIR} DIRECTORY)

set ( OGDF_LIBRARY_DIR ${OGDF_LIBRARY_DIR} CACHE FILEPATH "Path to the OGDF library directory including libOGDF.a or libOGDF.so; please use no snapshot higher than 23th of July 2017" )
set ( OGDF_INCLUDE_DIR ${OGDF_INCLUDE_DIR} CACHE FILEPATH "OGDF include directory" )
set ( OGDF_AUTOGEN_INCLUDE_DIR ${OGDF_AUTOGEN_INCLUDE_DIR} CACHE FILEPATH "OGDF include directory for automatic generated header (out of source build)." )
set ( COIN_LIBRARY_DIR ${COIN_LIBRARY_DIR} CACHE FILEPATH "Path to the COIN library directory including libCOIN.a or libCOIN.so" )
set ( COIN_INCLUDE_DIR ${COIN_INCLUDE_DIR} CACHE FILEPATH "COIN include directory" )

message(STATUS "")
message(STATUS "OGDF:")

####################################################################
# Find Libraries Directory #########################################
####################################################################
# find ODGF include directory if not given by input
if(NOT OGDF_INCLUDE_DIR)
find_path(  OGDF_INCLUDE_DIR 
    NAMES   ogdf/tree/LCA.h ogdf/basic/Graph.h
    HINTS   /opt/ogdf/include/
            /usr/local/include
         )
endif(NOT OGDF_INCLUDE_DIR)
message(STATUS "${MY_SPACE}OGDF_INCLUDE_DIR:\t\t${OGDF_INCLUDE_DIR}")

# find ODGF automatically generated include directory if not given by input
if(NOT OGDF_AUTOGEN_INCLUDE_DIR)
find_path(  OGDF_AUTOGEN_INCLUDE_DIR 
    NAMES   ogdf/basic/internal/config_autogen.h
    HINTS   ${OGDF_INCLUDE_DIR}
            ${OGDF_LIBRARY_DIR}/include/
            /usr/local/lib/
            /opt/ogdf/include/
         )
endif(NOT OGDF_AUTOGEN_INCLUDE_DIR)
message(STATUS "${MY_SPACE}OGDF_AUTOGEN_INCLUDE_DIR:\t${OGDF_AUTOGEN_INCLUDE_DIR}")

# find COIN include directory if not given by input
if(NOT COIN_INCLUDE_DIR)
find_path(  COIN_INCLUDE_DIR 
    NAMES   coin/ClpSimplexNonlinear.hpp
    HINTS   ${OGDF_INCLUDE_DIR}
            /usr/local/lib/
            /opt/ogdf/include/
            /opt/coin/include/
            /usr/local/include
         )
endif(NOT COIN_INCLUDE_DIR)
message(STATUS "${MY_SPACE}COIN_INCLUDE_DIR: ${COIN_INCLUDE_DIR}")

####################################################################
# OGDF Library Directory ###########################################
####################################################################
find_library(OGDF_LIBRARY 
    libOGDF.a libOGDF.so
    HINTS   ${OGDF_LIBRARY_DIR}
            /usr/local/lib/
            /opt/ogdf/
            /usr/local/lib/ogdf/
            )
message(STATUS "${MY_SPACE}OGDF_LIBRARY:\t\t\t${OGDF_LIBRARY}")

####################################################################
# COIN Library Directory ###########################################
####################################################################
find_library(COIN_LIBRARY 
    libCOIN.a libCOIN.so
    HINTS   ${COIN_LIBRARY_DIR}
            ${OGDF_LIBRARY_DIR}
            /usr/local/lib/ogdf/
            /usr/local/lib/
            /opt/ogdf/
            )
message(STATUS "${MY_SPACE}COIN_LIBRARY:\t\t\t${COIN_LIBRARY}")

####################################################################
# Check if OGDF and COIN are available #############################
####################################################################
# Set OGDF_FOUND and COIN_FOUND variable and handles the REQUIRED argument
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OGDF DEFAULT_MSG OGDF_LIBRARY OGDF_INCLUDE_DIR OGDF_AUTOGEN_INCLUDE_DIR)
find_package_handle_standard_args(COIN DEFAULT_MSG COIN_LIBRARY COIN_INCLUDE_DIR)

# if OGDF was found set necessary variables and flags
if(OGDF_FOUND)
    set(OGDF_INCLUDE_DIRS ${OGDF_INCLUDE_DIR})
    set(OGDF_LIBRARIES ${OGDF_LIBRARY})
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(OGDF_LIBRARIES "${OGDF_LIBRARIES};m;pthread")
    endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
endif(OGDF_FOUND)

# if COIN was found set necessary variables and flags
if(COIN_FOUND)
    set(COIN_INCLUDE_DIRS ${COIN_INCLUDE_DIR})
    set(COIN_LIBRARIES ${COIN_LIBRARY})
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(COIN_LIBRARIES "${COIN_LIBRARIES};m;pthread")
    endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
endif(COIN_FOUND)

mark_as_advanced(OGDF_LIBRARY)

####################################################################
# Output Message ###################################################
####################################################################
message(STATUS "${MY_SPACE}OGDF_DEBUG:\t\t\t${OGDF_DEBUG}")
if(EGOA_ENABLE_OGDF AND NOT OGDF_FOUND) 
message( FATAL_ERROR 
    "OGDF is enabled, but either not available on the system or the \
    installation is demaged. Please, check the installation of OGDF, the OGDF \
    paths OGDF_AUTOGEN_INCLUDE_DIR, OGDF_INCLUDE_DIR, and OGDF_LIBRARY_DIR in \
    the cmake configuration or disable OGDF by setting EGOA_ENABLE_OGDF to OFF." )
endif(EGOA_ENABLE_OGDF AND NOT OGDF_FOUND)

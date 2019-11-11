# FindGurobi.cmake
# 
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#       
# If GPGT_ENABLE_GUROBI is ON the script searches for Gurobi in given
# and standard location. If found it adds the library to the project.
# 

set(GUROBI_HOME "${GUROBI_HOME}" CACHE PATH "Path to the Gurobi home directory; default on MacOS \"/Library/gurobi<version>\" use \"/Library\". You can find the current directory by using the command \">which gurobi.sh\". " FORCE)
set(GUROBI_VERSION "${GUROBI_VERSION}" CACHE STRING "Version of Gurobi, e.g., 751" FORCE)

if(GUROBI_HOME)
  file(GLOB dirs "${GUROBI_HOME}*")
elseif(APPLE)
    file(GLOB dirs $ENV{GUROBI_HOME}*)
    if(NOT dirs)
        file(GLOB dirs /Library/gurobi*)
    endif()
elseif(UNIX)
    file(GLOB dirs $ENV{GUROBI_HOME}*)
endif()

message(STATUS "")
message(STATUS "Gurobi:")
message(STATUS "${MY_SPACE}Gurobi version:\t\t\t\t" ${GUROBI_VERSION})

if(APPLE)
    string(CONCAT GUROBI_DIR /Library/gurobi;${GUROBI_VERSION};/mac64)
elseif(UNIX)
    string(CONCAT GUROBI_DIR ${GUROBI_HOME})
elseif(WIN32)
    string(CONCAT GUROBI_DIR ${GUROBI_HOME})
endif()
message(STATUS "${MY_SPACE}Looking for Gurobi in:\t\t" ${GUROBI_DIR})

string(SUBSTRING ${GUROBI_VERSION} 0 2 GUROBI_VERSION_SHORT)

####################################################################
# Unset ############################################################
####################################################################
unset(GUROBI_INCLUDE_DIR CACHE)
unset(GUROBI_LIBRARY_DIR CACHE)
unset(GUROBI_LIBRARY     CACHE)
unset(GUROBI_CPP_LIBRARY CACHE)

####################################################################
# Find gurobi include directory ####################################
####################################################################
find_path(GUROBI_INCLUDE_DIR 
        gurobi_c++.h 
        HINTS "${GUROBI_DIR}/include"
                $ENV{GUROBI_HOME}/include
        )
message(STATUS "${MY_SPACE}GUROBI_INCLUDE_DIR:\t\t\t" ${GUROBI_INCLUDE_DIR})

####################################################################
# Find Gurobi library directory ####################################
####################################################################
find_path(GUROBI_LIBRARY_DIR 
        libgurobi${GUROBI_VERSION_SHORT}.a libgurobi${GUROBI_VERSION_SHORT}.so 
        HINTS   ${GUROBI_DIR}/lib
                $ENV{GUROBI_HOME}/lib
        )

####################################################################
# Find Gurobi library ##############################################
####################################################################
find_library(GUROBI_LIBRARY 
        libgurobi${GUROBI_VERSION_SHORT}.a libgurobi${GUROBI_VERSION_SHORT}.so
        HINTS   ${GUROBI_DIR}/lib
                $ENV{GUROBI_HOME}/lib
        )
message(STATUS "${MY_SPACE}GUROBI_LIBRARY:\t\t\t\t" ${GUROBI_LIBRARY})

####################################################################
# Find Gurobi CPP library ##########################################
####################################################################
find_library(GUROBI_CPP_LIBRARY 
        libgurobi_c++.a libgurobi_c++.so 
        HINTS   ${GUROBI_DIR}/lib
                $ENV{GUROBI_HOME}/lib
        )
message(STATUS "${MY_SPACE}GUROBI_CPP_LIBRARY:\t\t\t" ${GUROBI_CPP_LIBRARY})

####################################################################
# Check if Gurobi is available #####################################
####################################################################
# Set GUROBI_FOUND variable and handles the REQUIRED argument
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GUROBI DEFAULT_MSG GUROBI_LIBRARY GUROBI_CPP_LIBRARY GUROBI_INCLUDE_DIR)

if(GUROBI_FOUND)
    set(GRB_LICENSE_FILE "~/gurobi.research.lic") # TODO: Add possible variable
    set(GUROBI_INCLUDE_DIRS ${GUROBI_INCLUDE_DIR})
    set(GUROBI_LIBRARIES ${GUROBI_CPP_LIBRARY} ${GUROBI_LIBRARY})
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(GUROBI_LIBRARIES "${GUROBI_LIBRARIES};m;pthread")
    endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
endif(GUROBI_FOUND)

mark_as_advanced(GUROBI_LIBRARY GUROBI_CPP_LIBRARY GUROBI_INCLUDE_DIR)

####################################################################
# Output Message ###################################################
####################################################################
message(STATUS "")

if(EGOA_ENABLE_GUROBI AND NOT GUROBI_FOUND)
    message( FATAL_ERROR 
        "Gurobi is enabled, but not available on the system. Please, check the \
      Gurobi installation, and cmake configuration for GUROBI_HOME or disable \
      Gurobi by setting EGOA_ENABLE_GUROBI to OFF." )
endif(EGOA_ENABLE_GUROBI AND NOT GUROBI_FOUND)

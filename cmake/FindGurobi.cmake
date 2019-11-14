# FindGurobi.cmake
# 
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#       
# If EGOA_ENABLE_GUROBI is ON the script searches for Gurobi in given
# and standard location. If found it adds the library to the project.
# 

####################################################################
# Unset ############################################################
####################################################################
unset(GUROBI_HOME       CACHE)
unset(GUROBI_VERSION    CACHE)
# Hidden
unset(GUROBI_LIBRARIES   CACHE)
unset(GUROBI_INCLUDE_DIR CACHE)
unset(GUROBI_LIBRARY_DIR CACHE)
unset(GUROBI_LIBRARY     CACHE)
unset(GUROBI_CPP_LIBRARY CACHE)

####################################################################
# Initial Configuration and (Sub-)Version Extraction ###############
####################################################################
set(GUROBI_HOME "${GUROBI_ROOT_DIR}" CACHE PATH
    "Path to the Gurobi home directory; default on MacOS \"/Library/gurobi<version>\" \
    use \"/Library\". You can find the current directory by using the command \">which \
    gurobi.sh\". ")

if(GUROBI_HOME AND NOT GUROBI_VERSION)
    string(REGEX MATCH "[0-9]+" GUROBI_VERSION "${GUROBI_HOME}")
    message(STATUS "${MY_SPACE}Gurobi version:\t\t\t\t" ${GUROBI_VERSION})
else()
    string(REGEX MATCH "[0-9]+" GUROBI_VERSION "$ENV{GUROBI_HOME}")
    message(STATUS "${MY_SPACE}Gurobi version:\t\t\t\t" ${GUROBI_VERSION})
endif()

message(STATUS "${MY_SPACE}Looking for Gurobi in:\t\t" ${GUROBI_HOME})
string(SUBSTRING ${GUROBI_VERSION} 0 2 GUROBI_VERSION_SHORT)

####################################################################
# Find gurobi include directory ####################################
####################################################################
find_path(GUROBI_INCLUDE_DIR 
        gurobi_c++.h 
        HINTS "${GUROBI_HOME}/include"
                $ENV{GUROBI_HOME}/include
        )
message(STATUS "${MY_SPACE}GUROBI_INCLUDE_DIR:\t\t\t" ${GUROBI_INCLUDE_DIR})

####################################################################
# Find Gurobi library directory ####################################
####################################################################
find_path(GUROBI_LIBRARY_DIR 
        libgurobi${GUROBI_VERSION_SHORT}.a libgurobi${GUROBI_VERSION_SHORT}.so 
        HINTS   ${GUROBI_HOME}/lib
                $ENV{GUROBI_HOME}/lib
        )

####################################################################
# Find Gurobi library ##############################################
####################################################################
find_library(GUROBI_LIBRARY 
        libgurobi${GUROBI_VERSION_SHORT}.a libgurobi${GUROBI_VERSION_SHORT}.so
        HINTS   ${GUROBI_HOME}/lib
                $ENV{GUROBI_HOME}/lib
        )
message(STATUS "${MY_SPACE}GUROBI_LIBRARY:\t\t\t\t" ${GUROBI_LIBRARY})

####################################################################
# Find Gurobi CPP library ##########################################
####################################################################
find_library(GUROBI_CPP_LIBRARY 
        libgurobi_c++.a libgurobi_c++.so 
        HINTS   ${GUROBI_HOME}/lib
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

####################################################################
# Mark some variables as advanced, i.e., not visible for users  ####
####################################################################
mark_as_advanced(GUROBI_INCLUDE_DIR)
mark_as_advanced(GUROBI_LIBRARY_DIR)
mark_as_advanced(GUROBI_LIBRARY)
mark_as_advanced(GUROBI_CPP_LIBRARY)
mark_as_advanced(GUROBI_LIBRARIES)

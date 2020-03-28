# FindIpopt.cmake
# 
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#       
# If EGOA_ENABLE_IPOPT is ON the script searches for Ipopt in given
# and standard location. If found it adds the library to the project.
# 

# Environment variable IPOPT_ROOT_DIR of IPOPT should be set, e.g., /Users/<user_name>/Documents/CoinIpopt/build 
set ( IPOPT_ROOT_DIR "$ENV{IPOPT_ROOT_DIR}" CACHE PATH "Ipopt root directory." )

get_filename_component ( PARENT_DIRECTORY ${PROJECT_SOURCE_DIR} DIRECTORY )
string  ( CONCAT IPOPT_HOME ${PARENT_DIRECTORY};/external_libraries )
message ( STATUS "Ipopt:" )
message ( STATUS "${MY_SPACE}Environment variable:\t\t" $ENV{IPOPT_ROOT_DIR} )
message ( STATUS "${MY_SPACE}Looking for Ipopt in:\t\t" ${IPOPT_ROOT_DIR} )

set ( IPOPT_HOME "${IPOPT_HOME}" CACHE PATH "Path to the Ipopt home directory; \
                                 see \"/<installation directory of IPOPT>\". " )

####################################################################
# Unset ############################################################
####################################################################
unset ( IPOPT_INCLUDE_DIR CACHE )
unset ( IPOPT_LIBRARY_DIR CACHE )
unset ( IPOPT_LIBRARY     CACHE )

####################################################################
# Ipopt include directory ##########################################
####################################################################
find_path ( IPOPT_INCLUDE_DIR
    NAMES IpNLP.hpp 
    HINTS   /usr/local/include/coin
            ${IPOPT_ROOT_DIR}/include/coin
            ${IPOPT_ROOT_DIR}/include
    )
message ( STATUS "${MY_SPACE}IPOPT_INCLUDE_DIR:\t\t\t" ${IPOPT_INCLUDE_DIR} )

####################################################################
# Ipopt library directory ##########################################
####################################################################
find_path ( IPOPT_LIBRARY_DIR 
    libipopt.dylib libipopt.so 
    HINTS   /usr/local/lib
            ${IPOPT_ROOT_DIR}/lib
    )
message ( STATUS "${MY_SPACE}IPOPT_LIBRARY_DIR:\t\t\t" ${IPOPT_LIBRARY_DIR} )

if(APPLE)
    find_library(IPOPT_LIBRARY 
        libipopt.dylib
        HINTS   /usr/local/lib
                ${IPOPT_ROOT_DIR}/lib
    )
elseif(UNIX)
    find_library(IPOPT_LIBRARY 
        libipopt.so 
        HINTS   /usr/local/lib
                ${IPOPT_ROOT_DIR}/lib
    )
endif()
message ( STATUS "${MY_SPACE}IPOPT_LIBRARY:\t\t\t\t" ${IPOPT_LIBRARY} )

####################################################################
# Check if IPOPT is available ######################################
####################################################################
include ( FindPackageHandleStandardArgs )
find_package_handle_standard_args ( IPOPT DEFAULT_MSG IPOPT_LIBRARY IPOPT_LIBRARY_DIR IPOPT_INCLUDE_DIR )

if ( IPOPT_FOUND )
    set ( IPOPT_INCLUDE_DIRS ${IPOPT_INCLUDE_DIR} )
    set ( IPOPT_LIBRARIES ${IPOPT_LIBRARY} )
    if ( CMAKE_SYSTEM_NAME STREQUAL "Linux" )
        set ( IPOPT_LIBRARIES "${IPOPT_LIBRARIES};m;pthread" )
    endif ( CMAKE_SYSTEM_NAME STREQUAL "Linux" )
    include_directories ( ${IPOPT_INCLUDE_DIR} )
endif ( IPOPT_FOUND )

mark_as_advanced ( IPOPT_LIBRARY IPOPT_INCLUDE_DIR IPOPT_LIBRARY_DIR )

####################################################################
# Output Message ###################################################
####################################################################
message ( STATUS "" )
if ( EGOA_ENABLE_IPOPT AND NOT IPOPT_FOUND )
    message ( FATAL_ERROR 
        "Ipopt is enabled, but not available on the system. Please, check the \
        Ipopt installation, and cmake configuration or disable Ipopt by \
        setting EGOA_ENABLE_IPOPT to OFF." )
endif ( EGOA_ENABLE_IPOPT AND NOT IPOPT_FOUND )
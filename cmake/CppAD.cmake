# FindCppAD.cmake
# 
#   Created on: Jan 26, 2020
#       Author: Franziska Wegner
#       
# If EGOA_ENABLE_CPPAD is ON the script searches for CppAD in given and
# standard location (see EGOA_DOWNLOAD_CPPAD). If found it adds the library to
# the project.
# 

# Environment variable CPPAD_ROOT_DIR of CPPAD should be set, e.g.,
# /usr/local/include or /external/CppAD/include
set ( CPPAD_ROOT_DIR "$ENV{CPPAD_ROOT_DIR}" CACHE PATH "CppAD root directory." )

message ( STATUS "CppAD:" )
message ( STATUS "${MY_SPACE}Environment variable:\t\t" $ENV{CPPAD_ROOT_DIR} )
message ( STATUS "${MY_SPACE}Looking for CppAD in:\t\t" ${CPPAD_ROOT_DIR} )

set ( CPPAD_HOME "${CPPAD_HOME}" CACHE PATH "Path to the CppAD home directory; \
                                 see \"/<installation directory of CppAD>\". " )

####################################################################
# Unset ############################################################
####################################################################
unset ( CPPAD_INCLUDE_DIR CACHE )

####################################################################
# CppAD include directory ##########################################
####################################################################
find_path ( CPPAD_INCLUDE_DIR
    NAMES cppad/cppad.hpp 
    HINTS   /external/CppAD/include
            ${CPPAD_ROOT_DIR}/include/
    )
message ( STATUS "${MY_SPACE}CPPAD_INCLUDE_DIR:\t\t\t" ${CPPAD_INCLUDE_DIR} )

####################################################################
# Check if CPPAD is available ######################################
####################################################################
include ( FindPackageHandleStandardArgs )
find_package_handle_standard_args ( CPPAD DEFAULT_MSG CPPAD_INCLUDE_DIR )

if ( CPPAD_FOUND)
    set ( CPPAD_INCLUDE_DIRS ${CPPAD_INCLUDE_DIR} )
    set ( CPPAD_LIBRARIES ${CPPAD_LIBRARY} )
    include_directories ( ${CPPAD_INCLUDE_DIR} )
endif ( CPPAD_FOUND )

mark_as_advanced ( CPPAD_INCLUDE_DIR )

####################################################################
# Output Message ###################################################
####################################################################
message ( STATUS "" )
if ( EGOA_ENABLE_CPPAD AND NOT CPPAD_FOUND )
    message( FATAL_ERROR 
        "CppAD is enabled, but not available on the system. Please, check the \
       CppAD installation, and cmake configuration or disable CppAD by \
       setting EGOA_ENABLE_CPPAD to OFF." )
endif ( EGOA_ENABLE_CPPAD AND NOT CPPAD_FOUND )

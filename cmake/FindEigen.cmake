# FindEigen.cmake
#
#   Created on: Jan 26, 2020
#       Author: Franziska Wegner
#
# If EGOA_ENABLE_EIGEN is ON the script searches for Eigen in given and
# standard location (see EGOA_DOWNLOAD_EIGEN). If found it adds the library to
# the project.
#

####################################################################
# Unset ############################################################
####################################################################
unset ( EIGEN_INCLUDE_DIR CACHE )

####################################################################
# Eigen include directory ##########################################
####################################################################
find_path ( EIGEN_INCLUDE_DIR
    NAMES   Eigen/src/Core/Array.h
    HINTS   ./external/Eigen
            ${EIGEN_ROOT_DIR}/Eigen/
            ${EIGEN_ROOT_DIR}
    )
message ( STATUS "${MY_SPACE}EIGEN_INCLUDE_DIR:\t\t\t" ${EIGEN_INCLUDE_DIR} )

####################################################################
# Check if EIGEN is available ######################################
####################################################################
include ( FindPackageHandleStandardArgs )
find_package_handle_standard_args ( EIGEN DEFAULT_MSG EIGEN_INCLUDE_DIR )

if ( EIGEN_FOUND)
    set ( EIGEN_INCLUDE_DIRS ${EIGEN_INCLUDE_DIR} )
    include_directories ( ${EIGEN_INCLUDE_DIR} )
endif ( EIGEN_FOUND )

message ( STATUS "${MY_SPACE}EIGEN_INCLUDE_DIR:\t\t\t" ${EIGEN_INCLUDE_DIR} )

mark_as_advanced ( EIGEN_INCLUDE_DIR )

####################################################################
# Output Message ###################################################
####################################################################
message ( STATUS "" )
if ( EGOA_ENABLE_EIGEN AND NOT EIGEN_FOUND )
    message( FATAL_ERROR
        "Eigen is enabled, but not available on the system. Please, check the \
       Eigen installation, and cmake configuration or disable Eigen by \
       setting EGOA_ENABLE_EIGEN to OFF." )
endif ( EGOA_ENABLE_EIGEN AND NOT EIGEN_FOUND )

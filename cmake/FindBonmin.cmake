# FindBonmin.cmake
# 
#   Created on: 30.01.2019
#       Author: Franziska Wegner
#       
# If EGOA_ENABLE_BONMIN is ON the script searches for Bonmin in given
# and standard location. If found it adds the library to the project.
# 

set(BONMIN_ROOT_DIR "$ENV{BONMIN_ROOT_DIR}" CACHE PATH "BONMIN root directory.")

get_filename_component(PARENT_DIRECTORY ${PROJECT_SOURCE_DIR} DIRECTORY)
string(CONCAT BONMIN_HOME ${PARENT_DIRECTORY};/external_libraries)

message(STATUS "Bonmin:")
message(STATUS "${MY_SPACE}BONMIN_ROOT_DIR:\t\t\t" ${BONMIN_ROOT_DIR})

####################################################################
# Unset ############################################################
####################################################################
unset(BONMIN_INCLUDE_DIR CACHE)
unset(BONMIN_LIBRARY_DIR CACHE)
unset(BONMIN_LIBRARY     CACHE)

####################################################################
# Bonmin Include Directory #########################################
####################################################################
find_path(BONMIN_INCLUDE_DIR
    NAMES BonTMINLP.hpp 
    HINTS   /usr/local/include/coin
            ${BONMIN_ROOT_DIR}/include/coin
            ${BONMIN_ROOT_DIR}/include
)
message(STATUS "${MY_SPACE}BONMIN_INCLUDE_DIR:\t\t\t" ${BONMIN_INCLUDE_DIR})

####################################################################
# Bonmin Library Directory #########################################
####################################################################
find_path(BONMIN_LIBRARY_DIR
    NAMES libbonmin.a 
    HINTS   /usr/local/lib
            ${BONMIN_ROOT_DIR}/lib
)
message(STATUS "${MY_SPACE}BONMIN_LIBRARY_DIR:\t\t\t" ${BONMIN_LIBRARY_DIR})

if(APPLE)
    find_library(BONMIN_LIBRARY 
        NAMES libbonmin.a #.dylib #libCbcSolver.a libCbc.a libCgl.a libOsiClp.a libClpSolver.a libClp.a libcoinasl.a libOsi.a libCoinUtils.a libcoinmumps.a
        HINTS   /usr/local/lib
                ${BONMIN_ROOT_DIR}/lib
    )
    set(LIBS ${LIBS} ${BONMIN_LIBRARY})

    set(MAC_BONMIN_COMPILER_FLAGS "-fno-common -no-cpp-precomp -fexceptions -arch x86_64 -m64 -DBONMIN_BUILD")
elseif(UNIX)
    find_library(BONMIN_LIBRARY 
        NAMES libbonmin.a #.so #libCbcSolver.a libCbc.a libCgl.a libOsiClp.a libClpSolver.a libClp.a libcoinasl.a libOsi.a libCoinUtils.a libcoinmumps.a
        HINTS   /usr/local/lib
                ${BONMIN_ROOT_DIR}/lib
    )
endif()
message(STATUS "${MY_SPACE}BONMIN_LIBRARY:\t\t\t\t" ${BONMIN_LIBRARY})

####################################################################
# Configure pkg-config for cross-compilation #######################
####################################################################
# see https://stackoverflow.com/questions/44487053/set-pkg-config-path-in-cmake
if(IS_DIRECTORY "${BONMIN_LIBRARY_DIR}/pkgconfig")
    set(CMAKE_PREFIX_PATH "${BONMIN_LIBRARY_DIR}/pkgconfig")
    set(ENV{PKG_CONFIG_PATH} "${BONMIN_LIBRARY_DIR}/pkgconfig")
else()
    message(STATUS "${MY_SPACE}Directory ${BONMIN_LIBRARY_DIR}/pkgconfig does not exist!")
endif()

include(FindPkgConfig)

####################################################################
# Check if Bonmin is available #####################################
####################################################################
set( ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:${BONMIN_LIBRARY_DIR}/../lib/pkgconfig" )
set( ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:${BONMIN_LIBRARY_DIR}/../lib64/pkgconfig" )
set( ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:${BONMIN_LIBRARY_DIR}/../share/pkgconfig" )
pkg_search_module(PKG_BONMIN QUIET bonmin)  # this looks for bonmin.pc file

# include_directories(${PKG_BONMIN_INCLUDE_DIRS})
# target_link_libraries (FINAL_BINARY ${PKG_BONMIN_LDFLAGS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(BONMIN DEFAULT_MSG BONMIN_LIBRARY BONMIN_INCLUDE_DIR)

####################################################################
# Output Message ###################################################
####################################################################
if(BONMIN_FOUND)
    message(STATUS "${MY_SPACE}Package Config:\t\t\t\t${BONMIN_LIBRARY_DIR}/pkgconfig")
    # set(BONMIN_INCLUDE_DIRS ${BONMIN_INCLUDE_DIR})
    set(BONMIN_INCLUDE_DIRS ${PKG_BONMIN_INCLUDE_DIRS})
    # set(BONMIN_LIBRARIES ${BONMIN_LIBRARY})
    set(BONMIN_LIBRARIES ${PKG_BONMIN_LDFLAGS})
    message(STATUS "${MY_SPACE}Bonmin Pkg Config:\t\t\t" ${PKG_BONMIN_LDFLAGS})
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(BONMIN_LIBRARIES "${BONMIN_LIBRARIES};m;pthread")
    endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
endif(BONMIN_FOUND)

mark_as_advanced(BONMIN_LIBRARY BONMIN_INCLUDE_DIR)
message(STATUS "")

if(EGOA_ENABLE_BONMIN AND NOT BONMIN_FOUND)
    message( FATAL_ERROR 
        "Bonmin is enabled, but not available on the system. Please, check the \
         Bonmin installation, and cmake configuration for BONMIN_ROOT_DIR or \
         disable Bonmin by setting EGOA_ENABLE_BONMIN to OFF." )
endif(EGOA_ENABLE_BONMIN AND NOT BONMIN_FOUND)
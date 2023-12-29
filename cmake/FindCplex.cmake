# FindCplex.cmake
#
#   Created on: May 11, 2019
#       Author: Franziska Wegner
#
# If EGOA_ENABLE_CPLEX is ON the script searches for Cplex in given
# and standard location. If found it adds the library to the project.
#

# Environment variable CPLEX_ROOT_DIR of CPLEX should be set, e.g., /Applications/CPLEX_Studio128
set(CPLEX_HOME "${CPLEX_HOME}" CACHE PATH "Path to the Cplex home \
    directory; default on MacOS \"/Applications/CPLEX_Studio<version>\" \
    use \"/Library\". You can find the current directory by using the \
    command \">locate ILOG\". " FORCE)
message(STATUS "${MY_SPACE}CPLEX_HOME:\t\t\t\t\t" ${CPLEX_HOME})

####################################################################
# Unset ############################################################
####################################################################
unset(CPLEX_INCLUDE_DIR         CACHE)
unset(CPLEX_CONCERT_INCLUDE_DIR CACHE)
unset(CPLEX_LIBRARY_DIR         CACHE)
unset(CPLEX_CONCERT_LIBRARY_DIR CACHE)
unset(CPLEX_LIBRARY             CACHE)
unset(CPLEX_DISTMIP_LIBRARY     CACHE)
unset(ILO_CPLEX_LIBRARY         CACHE)
unset(CPLEX_CONCERT_LIBRARY     CACHE)

####################################################################
# Cplex Include Directory ##########################################
####################################################################
find_path(CPLEX_INCLUDE_DIR
    NAMES ilcplex/cplex.h
    HINTS   /usr/local/include
            ${CPLEX_HOME}/cplex/include
    )
message(STATUS "${MY_SPACE}CPLEX_INCLUDE_DIR:\t\t\t" ${CPLEX_INCLUDE_DIR})

####################################################################
# Find path Cplex concert include directory ########################
####################################################################
find_path(CPLEX_CONCERT_INCLUDE_DIR
    NAMES ilconcert/ilobasic.h
    HINTS   /usr/local/include
            /Applications/CPLEX_Studio128/concert/include
            ${CPLEX_HOME}/concert/include
    )
message(STATUS "${MY_SPACE}CPLEX_CONCERT_INCLUDE_DIR:\t" ${CPLEX_CONCERT_INCLUDE_DIR})

####################################################################
# Find path Cplex Library ##########################################
####################################################################
if(CPLEX_HOME)
    file(GLOB dirs ${CPLEX_HOME}*)
endif()

find_path(CPLEX_LIBRARY_DIR
    libcplex.a libcplexdistmip.a
    HINTS   /usr/local/lib
            /Applications/CPLEX_Studio128/cplex/lib/x86-64_osx/static_pic
            ${CPLEX_HOME}/cplex/lib/x86-64_osx/static_pic
            ${CPLEX_HOME}/cplex/lib/x86-64_darwin/static_pic
            ${CPLEX_HOME}/cplex/lib/x86-64_debian4.0_4.1/static_pic
            ${CPLEX_HOME}/cplex/lib/x86-64_sles10_4.1/static_pic
            ${CPLEX_HOME}/cplex/lib/x86-64_linux/static_pic
            ${CPLEX_HOME}/cplex/lib/${CPLEX_WIN_PLATFORM}
    )
message(STATUS "${MY_SPACE}CPLEX_LIBRARY_DIR:\t\t\t" ${CPLEX_LIBRARY_DIR})

####################################################################
# Find path Cplex concert library directory ########################
####################################################################
find_path(CPLEX_CONCERT_LIBRARY_DIR
    libconcert.a
    HINTS   /usr/local/lib
            /Applications/CPLEX_Studio128/concert/lib/x86-64_osx/static_pic
            ${CPLEX_HOME}/concert/lib/x86-64_osx/static_pic
            ${CPLEX_HOME}/concert/lib/x86-64_darwin/static_pic
            ${CPLEX_HOME}/concert/lib/x86-64_debian4.0_4.1/static_pic
            ${CPLEX_HOME}/concert/lib/x86-64_sles10_4.1/static_pic
            ${CPLEX_HOME}/concert/lib/x86-64_linux/static_pic
            ${CPLEX_HOME}/concert/lib/${CPLEX_WIN_PLATFORM}
    )
message(STATUS "${MY_SPACE}CPLEX_CONCERT_LIBRARY_DIR:\t" ${CPLEX_CONCERT_LIBRARY_DIR})

find_library(CPLEX_LIBRARY
    NAMES   cplex
    HINTS   /usr/local/lib
            ${CPLEX_LIBRARY_DIR}
)
find_library(CPLEX_DISTMIP_LIBRARY
    NAMES   cplexdistmip
    HINTS   /usr/local/lib
            ${CPLEX_LIBRARY_DIR}
)
find_library(ILO_CPLEX_LIBRARY
    NAMES   ilocplex
    HINTS   /usr/local/lib
            ${CPLEX_LIBRARY_DIR}
)
find_library(CPLEX_CONCERT_LIBRARY
    NAMES   concert
    HINTS   /usr/local/lib
            ${CPLEX_CONCERT_LIBRARY_DIR}
)

message(STATUS "${MY_SPACE}CPLEX_LIBRARY:\t\t\t\t" ${CPLEX_LIBRARY})
message(STATUS "${MY_SPACE}CPLEX_DISTMIP_LIBRARY:\t\t" ${CPLEX_DISTMIP_LIBRARY})
message(STATUS "${MY_SPACE}ILO_CPLEX_LIBRARY:\t\t\t" ${ILO_CPLEX_LIBRARY})
message(STATUS "${MY_SPACE}CPLEX_CONCERT_LIBRARY_DIR:\t" ${CPLEX_CONCERT_LIBRARY_DIR})

if(WIN32)
    FIND_PATH(CPLEX_BIN_DIR
      cplex${CPLEX_WIN_VERSION}.dll
          HINTS ${CPLEX_HOME}/cplex/bin/${CPLEX_WIN_PLATFORM}
      )
else()
    FIND_PATH(CPLEX_BIN_DIR
        cplex
        HINTS   ${CPLEX_HOME}/cplex/bin/x86-64_osx
                ${CPLEX_HOME}/cplex/bin/x86-64_darwin
                ${CPLEX_HOME}/cplex/bin/x86-64_sles10_4.1
                ${CPLEX_HOME}/cplex/bin/x86-64_debian4.0_4.1
                ${CPLEX_HOME}/cplex/lib/x86-64_linux

      )
endif()

message(STATUS "${MY_SPACE}CPLEX_BIN_DIR:\t\t\t\t" ${CPLEX_BIN_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CPLEX DEFAULT_MSG CPLEX_LIBRARY CPLEX_DISTMIP_LIBRARY ILO_CPLEX_LIBRARY CPLEX_CONCERT_LIBRARY_DIR CPLEX_LIBRARY_DIR CPLEX_CONCERT_LIBRARY_DIR CPLEX_INCLUDE_DIR CPLEX_CONCERT_INCLUDE_DIR CPLEX_BIN_DIR)

####################################################################
# Output Message ###################################################
####################################################################
if(CPLEX_FOUND)
    set(CPLEX_INCLUDE_DIRS ${CPLEX_INCLUDE_DIR} ${CPLEX_CONCERT_INCLUDE_DIR})
    message(STATUS "TEST:${CPLEX_INCLUDE_DIRS}")
    set(CPLEX_LIBRARIES ${CPLEX_LIBRARY} ${CPLEX_DISTMIP_LIBRARY} ${ILO_CPLEX_LIBRARY} ${CPLEX_CONCERT_LIBRARY})
    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(CPLEX_LIBRARIES "${CPLEX_LIBRARIES};m;pthread")
    endif(CMAKE_SYSTEM_NAME STREQUAL "Linux")

    message("Adding -DIL_STD flag...")
    ADD_DEFINITIONS(-DIL_STD)
endif(CPLEX_FOUND)

mark_as_advanced(CPLEX_LIBRARY CPLEX_DISTMIP_LIBRARY ILO_CPLEX_LIBRARY CPLEX_CONCERT_LIBRARY_DIR CPLEX_LIBRARY_DIR CPLEX_CONCERT_LIBRARY_DIR CPLEX_INCLUDE_DIR CPLEX_CONCERT_INCLUDE_DIR CPLEX_BIN_DIR)
message(STATUS "")

if(EGOA_ENABLE_CPLEX AND NOT CPLEX_FOUND)
    message( FATAL_ERROR
        "CPLEX is enabled, but not available on the system. Please, check the \
       CPLEX installation, and cmake configuration or disable Cplex by \
       setting EGOA_ENABLE_CPLEX to OFF." )
endif(EGOA_ENABLE_CPLEX AND NOT CPLEX_FOUND)

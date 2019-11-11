# Boost.cmake
# 
#   Created on: Nov 04, 2019
#       Author: Franziska Wegner
#       
# Find the Boost library.
# 

####################################################################
# Reset variables ##################################################
####################################################################
unset(Boost_DIRECTORIES)
unset(Boost_LIBRARY_DIRS)
unset(Boost_INCLUDE_DIRS)

####################################################################
# Create variables #################################################
####################################################################
set( Boost_DIRECTORIES "/usr/local/Cellar/boost/1.71.0/" CACHE STRING
     "EGOA_BUILD_TYPE sets the CMAKE_BUILD_TYPES to /usr/local/Cellar/boost/1.71.0/" )
set( Boost_LIBRARY_DIRS "" )
set( Boost_INCLUDE_DIRS "" )
set( BOOST_ROOT "" CACHE PATH "Boost library path" )
# https://stackoverflow.com/questions/58081084/target-boostlibrary-already-has-an-imported-location-link-errors 
# https://stackoverflow.com/questions/3016448/how-can-i-get-cmake-to-find-my-alternative-boost-installation/51904185
set( Boost_NO_SYSTEM_PATHS on CACHE BOOL "Do not search system for Boost" )
set( Boost_NO_BOOST_CMAKE on CACHE INTERNAL "" )
set( ENV{BOOST_ROOT} "${Boost_DIRECTORIES}" )

####################################################################
# Find Boost #######################################################
####################################################################
find_package( Boost REQUIRED COMPONENTS system filesystem)
include_directories(${Boost_INCLUDE_DIRS})
# link_directories(${Boost_LIBRARY_DIRS})

####################################################################
# Output ###########################################################
####################################################################
message(STATUS "${MY_SPACE}Boost_LIBRARY_DIRS:\t\t\t${Boost_LIBRARY_DIRS}")
message(STATUS "${MY_SPACE}Boost_INCLUDE_DIRS:\t\t\t${Boost_INCLUDE_DIRS}")
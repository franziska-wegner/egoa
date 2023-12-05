# QtConfiguration.cmake
#
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#
# Find QT6 include directory and libraries for linking and its required modules.
#
# * Once done this will define
#   * Qt6_FOUND         - system has Qt6
#   * QT6_LIBRARIES     - the libraries needed to use Qt6
#   * QTCORE_LOCATION   - location of the module Qt6::Core
#   * QTQUICK_LOCATION  - location of the module Qt6::Quick

# Find includes in corresponding build directories
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# Instruct CMake to run moc automatically when needed.
set( CMAKE_AUTOMOC ON )

# https://cmake.org/cmake/help/v3.0/prop_tgt/AUTOUIC.html
set( CMAKE_AUTOUIC ON )
# Note that without enabling it headers such as "ui_mainwindow.h" and
# "ui_*.h" will not be found.

####################################################################
# Find QT5 #########################################################
####################################################################
message(STATUS "Looking for Qt6")
find_package(Qt6 COMPONENTS Core Quick Widgets Concurrent REQUIRED)
get_target_property(QTCORE_LOCATION Qt6::Core LOCATION)
get_target_property(QTQUICK_LOCATION Qt6::Quick LOCATION) # LOCATION_Release
get_target_property(QTWIDGETS_LOCATION Qt6::Widgets LOCATION) # LOCATION_Release
get_target_property(QTConcurrent_LOCATION Qt6::Concurrent LOCATION) # LOCATION_Release
add_definitions( ${QT_DEFINITIONS} )

####################################################################
# Output Message ###################################################
####################################################################
if( Qt6_FOUND )
    message( STATUS "${MY_SPACE}Found Qt6 Core module in \"${QTCORE_LOCATION}\" " )
    message( STATUS "${MY_SPACE}Found Qt6 Quick module in \"${QTQUICK_LOCATION}\" " )
    message( STATUS "${MY_SPACE}Found Qt6 Widgets module in \"${QTWIDGETS_LOCATION}\" " )
    message( STATUS "${MY_SPACE}Found Qt6 Concurrent module in \"${QTConcurrent_LOCATION}\" " )
endif( Qt6_FOUND )

####################################################################
# Check if QT is available #########################################
####################################################################
set( QT6_LIBRARIES Qt6::Core Qt6::Quick Qt6::Widgets )
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QT6 DEFAULT_MSG QT6_LIBRARIES)

# QtConfiguration.cmake
# 
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#       
# Find QT5 include directory and libraries for linking and its required modules.
# 
# * Once done this will define
#   * Qt5_FOUND         - system has Qt5
#   * QT5_LIBRARIES     - the libraries needed to use Qt5
#   * QTCORE_LOCATION   - location of the module Qt5::Core
#   * QTQUICK_LOCATION  - location of the module Qt5::Quick

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# https://cmake.org/cmake/help/v3.0/prop_tgt/AUTOUIC.html
set(CMAKE_AUTOUIC ON)
# Note that without enabling it headers such as "ui_mainwindow.h" and 
# "ui_*.h" will not be found.

####################################################################
# Find QT5 #########################################################
####################################################################
message(STATUS "Looking for Qt5")
FIND_PACKAGE(Qt5 COMPONENTS Core Quick Widgets Concurrent REQUIRED) # 
get_target_property(QTCORE_LOCATION Qt5::Core LOCATION)
get_target_property(QTQUICK_LOCATION Qt5::Quick LOCATION) # LOCATION_Release
get_target_property(QTWIDGETS_LOCATION Qt5::Widgets LOCATION) # LOCATION_Release
get_target_property(QTConcurrent_LOCATION Qt5::Concurrent LOCATION) # LOCATION_Release
add_definitions( ${QT_DEFINITIONS} )

####################################################################
# Output Message ###################################################
####################################################################
if(Qt5_FOUND)
    message( STATUS "${MY_SPACE}Found Qt5 Core module in \"${QTCORE_LOCATION}\" " )
    message( STATUS "${MY_SPACE}Found Qt5 Quick module in \"${QTQUICK_LOCATION}\" " )
    message( STATUS "${MY_SPACE}Found Qt5 Widgets module in \"${QTWIDGETS_LOCATION}\" " )
    message( STATUS "${MY_SPACE}Found Qt5 Concurrent module in \"${QTConcurrent_LOCATION}\" " )
endif()

####################################################################
# Check if QT is available #########################################
####################################################################
set ( QT5_LIBRARIES Qt5::Core Qt5::Quick Qt5::Widgets )
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(QT5 DEFAULT_MSG QT5_LIBRARIES)

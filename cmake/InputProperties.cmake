# InputProperties.cmake
#
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#
# Create variables and their drop down menus, and mark some variables as
# advanced.
#

####################################################################
# Reset variables ##################################################
####################################################################
# Enable variables
unset ( EGOA_BUILD_TYPE )
unset ( EGOA_ENABLE_BONMIN )
unset ( EGOA_ENABLE_BOOST )
unset ( EGOA_ENABLE_DOCUMENTATION )
unset ( EGOA_ENABLE_GUROBI )
unset ( EGOA_ENABLE_CPLEX )
unset ( EGOA_ENABLE_CPPAD )
unset ( EGOA_ENABLE_EIGEN )
unset ( EGOA_ENABLE_IPOPT )
unset ( EGOA_ENABLE_OGDF )
unset ( EGOA_ENABLE_OPENMP )
unset ( EGOA_ENABLE_TESTS )
unset ( EGOA_ENABLE_VERBOSE_MAKEFILE )
unset ( EGOA_ENABLE_EXCEPTION_HANDLING )
unset ( EGOA_ENABLE_ASSERTION )
unset ( EGOA_TEST_FRAMEWORK )
unset ( EGOA_THREAD_LIMIT )

# Download variables
unset ( EGOA_DOWNLOAD_CPPAD )
unset ( EGOA_DOWNLOAD_EIGEN )
unset ( EGOA_DOWNLOAD_GOOGLE_TEST_FRAMEWORK )
unset ( EGOA_DOWNLOAD_IEEE )
unset ( EGOA_DOWNLOAD_PYPSA_EUR )
unset ( EGOA_DOWNLOAD_PYPSA_ITI_COLLABORATION )
unset ( EGOA_DOWNLOAD_SCIGRID )
unset ( EGOA_DOWNLOAD_WINDFARM )

####################################################################
# Variables to enable external framework and drop down menu ########
####################################################################

# Build type
set ( EGOA_BUILD_TYPE Debug CACHE STRING
     "EGOA_BUILD_TYPE sets the CMAKE_BUILD_TYPES to either Debug or Release" )
set_property ( CACHE EGOA_BUILD_TYPE PROPERTY STRINGS Debug Release )

# Property Bonmin
set ( EGOA_ENABLE_BONMIN ON CACHE BOOL
     "EGOA_ENABLE_BONMIN enables to search for the ipopt framework" )
set_property ( CACHE EGOA_ENABLE_BONMIN PROPERTY STRINGS ON OFF )

# Property Boost
set ( EGOA_ENABLE_BOOST ON CACHE BOOL
     "EGOA_ENABLE_BOOST enables to search for the boost framework" )
set_property ( CACHE EGOA_ENABLE_BOOST PROPERTY STRINGS ON OFF )

# Property Doxygen
set ( EGOA_ENABLE_DOCUMENTATION ON CACHE BOOL
     "EGOA_ENABLE_DOCUMENTATION enables to search for the documentation framework" )
set_property ( CACHE EGOA_ENABLE_DOCUMENTATION PROPERTY STRINGS ON OFF )

# Property Eigen
set ( EGOA_ENABLE_EIGEN ON CACHE BOOL
     "EGOA_ENABLE_EIGEN enables to search for the Eigen framework" )
set_property ( CACHE EGOA_ENABLE_EIGEN PROPERTY STRINGS ON OFF )

# Property Gurobi
set ( EGOA_ENABLE_GUROBI ON CACHE BOOL
     "EGOA_ENABLE_GUROBI enables to search for the gurobi framework" )
set_property ( CACHE EGOA_ENABLE_GUROBI PROPERTY STRINGS ON OFF )

# Property Cplex
set ( EGOA_ENABLE_CPLEX ON CACHE BOOL
     "EGOA_ENABLE_CPLEX enables to search for the cplex framework" )
set_property ( CACHE EGOA_ENABLE_CPLEX PROPERTY STRINGS ON OFF )

# Property Cplex
set ( EGOA_ENABLE_CPPAD ON CACHE BOOL
     "EGOA_ENABLE_CPPAD enables to search for the CppAD framework" )
set_property ( CACHE EGOA_ENABLE_CPPAD PROPERTY STRINGS ON OFF )

# Property Ipopt
set ( EGOA_ENABLE_IPOPT ON CACHE BOOL
     "EGOA_ENABLE_IPOPT enables to search for the ipopt framework" )
set_property ( CACHE EGOA_ENABLE_IPOPT PROPERTY STRINGS ON OFF )

# Property OGDF
set ( EGOA_ENABLE_OGDF ON CACHE BOOL
     "EGOA_ENABLE_OGDF enables to search for the ogdf framework" )
set_property ( CACHE EGOA_ENABLE_OGDF PROPERTY STRINGS ON OFF )

# Property OpenMP
set ( EGOA_ENABLE_OPENMP OFF CACHE BOOL
     "EGOA_ENABLE_OPENMP enables to search for the OpenMP framework" )
set_property ( CACHE EGOA_ENABLE_OPENMP PROPERTY STRINGS ON OFF )

# Property GoogleTestFramework
set ( EGOA_ENABLE_TESTS ON CACHE BOOL
     "EGOA_ENABLE_TESTS enables the test framework" )
set_property ( CACHE EGOA_ENABLE_TESTS PROPERTY STRINGS ON OFF )

# Property exception handling
set ( EGOA_ENABLE_EXCEPTION_HANDLING ON CACHE BOOL
     "EGOA_ENABLE_EXCEPTION_HANDLING enables exception handling in the framework" )
set_property ( CACHE EGOA_ENABLE_EXCEPTION_HANDLING PROPERTY STRINGS ON OFF )

# Property exception handling
set ( EGOA_ENABLE_ASSERTION ON CACHE BOOL
     "EGOA_ENABLE_ASSERTION enables assertions in debug mode in the framework" )
set_property ( CACHE EGOA_ENABLE_ASSERTION PROPERTY STRINGS ON OFF )

# Property verbose makefile
set ( EGOA_ENABLE_VERBOSE_MAKEFILE ON CACHE BOOL
     "EGOA_ENABLE_VERBOSE_MAKEFILE enables the test framework" )
set_property ( CACHE EGOA_ENABLE_VERBOSE_MAKEFILE PROPERTY STRINGS ON OFF )

# Select test framework (default is GoogleOfflineTestFramework)
set ( EGOA_TEST_FRAMEWORK "GoogleOfflineTestFramework" CACHE STRING
     "Select a test framework (default: GoogleOfflineTestFramework)" )
set_property ( CACHE EGOA_TEST_FRAMEWORK PROPERTY STRINGS OfflineGoogleTestFramework OnlineGoogleTestFramework )

# Set number of threads
set ( EGOA_THREAD_LIMIT "100" CACHE STRING "Sets OpenMP limit for number of threads" )

####################################################################
# Download properties and drop down menus ##########################
####################################################################

# Download Cpp AD (Algorithmic Differentiation) Library
set ( EGOA_DOWNLOAD_CPPAD ON CACHE BOOL
     "EGOA_DOWNLOAD_CPPAD triggers the download of the Google Test Framework library" )
set_property ( CACHE EGOA_DOWNLOAD_CPPAD PROPERTY STRINGS ON OFF )

# Download Eigen Library
set ( EGOA_DOWNLOAD_EIGEN ON CACHE BOOL
     "EGOA_DOWNLOAD_EIGEN triggers the download of the library Eigen" )
set_property ( CACHE EGOA_DOWNLOAD_EIGEN PROPERTY STRINGS ON OFF )

# Download Google Test Framework Library
set ( EGOA_DOWNLOAD_GOOGLE_TEST_FRAMEWORK ON CACHE BOOL
     "EGOA_DOWNLOAD_GOOGLE_TEST_FRAMEWORK triggers the download of the Google Test Framework library" )
set_property ( CACHE EGOA_DOWNLOAD_GOOGLE_TEST_FRAMEWORK PROPERTY STRINGS ON OFF )

# Download IEEE data
set ( EGOA_DOWNLOAD_IEEE ON CACHE BOOL
     "EGOA_DOWNLOAD_IEEE triggers the download of the IEEE benchmark data sets" )
set_property ( CACHE EGOA_DOWNLOAD_IEEE PROPERTY STRINGS ON OFF )

# Download PyPSA-eur data
set ( EGOA_DOWNLOAD_PYPSA_EUR ON CACHE BOOL
     "EGOA_DOWNLOAD_PYPSA_EUR triggers the download for PyPSA-eur" )
set_property ( CACHE EGOA_DOWNLOAD_PYPSA_EUR PROPERTY STRINGS ON OFF )

# Download PyPSA-eur data
set ( EGOA_DOWNLOAD_PYPSA_ITI_COLLABORATION ON CACHE BOOL
     "EGOA_DOWNLOAD_PYPSA_ITI_COLLABORATION triggers the download for PyPSA-iti-collaboration" )
set_property ( CACHE EGOA_DOWNLOAD_PYPSA_ITI_COLLABORATION PROPERTY STRINGS ON OFF )

# Download SciGrid data
set ( EGOA_DOWNLOAD_SCIGRID ON CACHE BOOL
     "EGOA_DOWNLOAD_SCIGRID triggers the download for SciGrid" )
set_property ( CACHE EGOA_DOWNLOAD_SCIGRID PROPERTY STRINGS ON OFF )

# Download Wind Farm data
set ( EGOA_DOWNLOAD_WINDFARM ON CACHE BOOL
     "EGOA_DOWNLOAD_WINDFARM triggers the download for Windfarms" )
set_property ( CACHE EGOA_DOWNLOAD_WINDFARM PROPERTY STRINGS ON OFF )

####################################################################
# Mark some variables as advanced, i.e., not visible for users  ####
####################################################################
mark_as_advanced ( CMAKE_BUILD_TYPE )
mark_as_advanced ( CMAKE_C_COMPILER )
mark_as_advanced ( CMAKE_CXX_COMPILER )
mark_as_advanced ( CMAKE_INSTALL_PREFIX )
mark_as_advanced ( CMAKE_OSX_SYSROOT )
mark_as_advanced ( CMAKE_OSX_DEPLOYMENT_TARGET )
mark_as_advanced ( CMAKE_OSX_ARCHITECTURES )

mark_as_advanced ( COIN_LIBRARY )
mark_as_advanced ( OGDF_LIBRARY )

mark_as_advanced ( Qt5_DIR )
mark_as_advanced ( Qt5Concurrent_DIR )
mark_as_advanced ( Qt5Core_DIR )
mark_as_advanced ( Qt5Gui_DIR )
mark_as_advanced ( Qt5Network_DIR )
mark_as_advanced ( Qt5Qml_DIR )
mark_as_advanced ( Qt5Quick_DIR )
mark_as_advanced ( Qt5Widgets_DIR )

# FindGoogleTestFrameworkOnlineVersion.cmake
# 
#   Created on: Jan 30, 2019
#       Source: https://github.com/google/googletest/tree/master/googletest 
# 
# Requirements      
#   * CMake 2.8. or later due to the use of ExternalProject_Add(). 
# 
# CMake Warning (dev):
#   * Policy CMP0042 is not set: MACOSX_RPATH is enabled by default.  Run
#     "cmake --help-policy CMP0042" for policy details. Use the cmake_policy
#     command to set the policy and suppress this warning. MACOSX_RPATH is not
#     specified for the following targets: gtest_dll
#   * This warning is for project developers. Use -Wno-dev to suppress it.
# 
# If EGOA_ENABLE_TESTS is TRUE the necessary directories of the google test
# framework are added to the project such as the includes for gtest and gmock.
# 

set(CMAKE_MACOSX_RPATH 1)

####################################################################
# Include test framework ###########################################
####################################################################
if (EGOA_ENABLE_TESTS)
    # Download and unpack googletest at configure time
    configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
    if(result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif(result)
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
    if(result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif(result)

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                     ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                     EXCLUDE_FROM_ALL)

    # The gtest/gtest_main targets carry header search path
    # dependencies automatically when using CMake 2.8.11 or
    # later. Otherwise we have to add them here ourselves.
    if (CMAKE_VERSION VERSION_LESS 2.8.11)
        include_directories("${gtest_SOURCE_DIR}/include")
    endif()
endif (EGOA_ENABLE_TESTS)

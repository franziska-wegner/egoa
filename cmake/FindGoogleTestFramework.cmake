# FindGoogleTestFramework.cmake
# 
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#       
# If EGOA_ENABLE_TESTS is TRUE the necessary directories of the google test
# framework are added to the project such as the includes for gtest and gmock.
# 

####################################################################
# Include test framework ###########################################
####################################################################
if (EGOA_ENABLE_TESTS)
    if (APPLE)
        add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
        add_definitions(-D__GLIBCXX__)
    endif (APPLE)

    # This adds the googletest framework subdirectory, which has
    # the projects gtest and gmock.
    add_subdirectory(${EGOA_TEST_FRAMEWORK_LOCATION})

    # Include the gtest library. gtest_SOURCE_DIR is available due to
    # the project gtest.
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

    # Include the gmock library. gmock_SOURCE_DIR is available due to
    # the project gmock.
    include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})
endif (EGOA_ENABLE_TESTS)

####################################################################
# Output Message ###################################################
####################################################################
message(STATUS "Google Test Framework")
message(STATUS "${MY_SPACE}EGOA_ENABLE_TESTS:\t\t\t" ${EGOA_ENABLE_TESTS})
message(STATUS "")

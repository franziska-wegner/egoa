# CompilerConfiguration.cmake
# 
#   Created on: Nov 04, 2019
#       Author: Franziska Wegner
#       
# Compiler specific configurations.
# 

####################################################################
# Compiler Options #################################################
####################################################################
# option(EGOA_USE_ASSERT_EXCEPTIONS "Whether to throw an exception on failed assertions." OFF)
option(EGOA_WARNINGS_AS_ERRORS "Whether to treat compiler warnings as errors." ON)
# Pedantic compiler mode
option(EGOA_PEDANTIC_MODE "Whether to treat compiler diagnostics (issued by extensions) as warnings." ON)
set(EGOA_PEDANTIC_WARNING_FLAG "-pedantic")
option(EGOA_PEDANTIC_AS_ERRORS "Whether to treat compiler diagnostics (issued by extensions) warnings as errors." ON)
set(EGOA_PEDANTIC_ERROR_FLAG "-pedantic-errors")

# set default warning flags
set(EGOA_WARNING_FLAGS "")
set(EGOA_WARNING_FLAGS_DEBUG "")
set(EGOA_WARNING_FLAGS_RELEASE "")
set(EGOA_WARNINGS_AS_ERRORS_FLAG "")

# Consider -Wpedantic, -pedantic, or -pedantic-errors
set(PEDANTIC_FLAGS "-pedantic")

####################################################################
# Microsoft Visual Studio ##########################################
####################################################################
if(MSVC)
    add_definitions(/MP /DNOMINMAX)
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /Debug:fastlink")
    # https://docs.microsoft.com/en-us/cpp/build/reference/wx-treat-linker-warnings-as-errors?view=vs-2019
    set(EGOA_WARNINGS_AS_ERRORS_FLAG "/WX")
endif()

####################################################################
# GNU and Clang ####################################################
####################################################################
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
    set(EGOA_WARNING_FLAGS "-Wall -Wextra -Wunused-result -Wno-error=unused-but-set-variable -Wno-error=conversion -Wshadow")
    if(CMAKE_CXX_COMPILER_ID MATCHES Clang)
        set(EGOA_WARNING_FLAGS "${EGOA_WARNING_FLAGS} -Wno-error=zero-length-array")
    endif()
    set(EGOA_WARNINGS_AS_ERRORS_FLAG "-Werror")
endif()

####################################################################
# Extra compiler flags #############################################
####################################################################
set(extra_flags ${EGOA_WARNING_FLAGS})
# Debug mode
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(extra_flags  "${extra_flags} ${EGOA_WARNING_FLAGS_DEBUG}")
else()
    set(extra_flags  "${extra_flags} ${EGOA_WARNING_FLAGS_RELEASE}")
endif()
# Warning and error 
if(EGOA_WARNINGS_AS_ERRORS)
    set(extra_flags "${EGOA_WARNINGS_AS_ERRORS_FLAG} ${extra_flags}")
endif()
# Pedantic mode
if(EGOA_PEDANTIC_MODE)
    if(EGOA_PEDANTIC_AS_ERRORS)
        set(extra_flags "${EGOA_PEDANTIC_ERROR_FLAG} ${extra_flags}")
    else()
        set(extra_flags "${EGOA_PEDANTIC_WARNING_FLAG} ${extra_flags}")
    endif()
endif()
# 
set_property(TARGET ${TARGET_NAME} APPEND_STRING PROPERTY COMPILE_FLAGS " ${extra_flags} ")
message(STATUS "${MY_SPACE}Compiler extra flags:\t\t\t${TARGET_NAME} ${extra_flags}")

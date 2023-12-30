# FindClangTidy.cmake
#
#   Created on: Dec 27, 2023
#       Author: Franziska Wegner
#
# This file enables clang tidy for the project.
#


# Search for clang-tidy
find_program(CLANG_TIDY_PROG
    HINTS "/opt/homebrew/opt/llvm/bin/"
          "/usr/local/opt/llvm/bin/"
    NAMES "clang-tidy"
    REQUIRED
    )
# Setup clang-tidy command with executable and options, see https://cmake.org/cmake/help/latest/variable/CMAKE_LANG_CLANG_TIDY.html.
# Disable all default checks (-*) and only enable checks that advocate the use of modern C++ language constructs with (modernize-*).
set(CMAKE_CXX_CLANG_TIDY
    "${CLANG_TIDY_PROG}"
    "-checks=-*,modernize-*"
    # -format-style='file';
    # -header-filter=${CMAKE_CURRENT_SOURCE_DIR};
    # -header-filter=.;
    # -warnings-as-errors=*;
    )

# set CXX_CLANG_TIDY property after defining the target
# set_target_properties(EGOA PROPERTIES CXX_CLANG_TIDY "${CMAKE_CXX_CLANG_TIDY}")

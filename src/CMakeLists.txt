# CMakeLists.txt
#
#   Created on: 30.01.2019
#       Author: Franziska Wegner
#
# Install binaries into the bin folder. The project can be build with any of
# the available cmake generators.
#

include_directories(Boost_INCLUDE_DIRS)

# Define the main binary egoa with the linked source file main.cpp
add_executable(egoa Runnables/main.cpp)
# Link libraries to the binary
target_link_libraries(egoa EGOA)
add_ogdf_coin_if_available(egoa)
add_gurobi_if_available(egoa)

# Other executables
# add_executable(testTemplate Runnables/testTemplate.cpp)
# target_link_libraries(testTemplate EGOA)

# Other executables
if(CPLEX_FOUND)
    add_executable(testCplex Runnables/cplexExample.cpp)
    target_link_libraries(testCplex EGOA ${CPLEX_LIBRARIES})
endif(CPLEX_FOUND)

if(IPOPT_FOUND)
    add_executable(testIpopt1 Runnables/cpp_example.cpp)
    target_link_libraries(testIpopt1 EGOA ${IPOPT_LIBRARIES})
endif(IPOPT_FOUND)

# Install binary into the bin directory of the installation directory
# install(TARGETS egoa testTemplate DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
install(TARGETS egoa DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Other executables
# add_executable(convertFiles Runnables/convertFiles.cpp)
# target_link_libraries(convertFiles EGOA)

# add_executable(phase_oscillator_ensemble Runnables/phase_oscillator_ensemble.cpp)
# add_dependencies(phase_oscillator_ensemble Boost)
# target_link_libraries(phase_oscillator_ensemble ${Boost_LIBRARY_DIRS})

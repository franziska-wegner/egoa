
# Now simply link against gtest or gtest_main as needed
add_executable(TestBound DataStructures/TestBound.cpp)
target_link_libraries(TestBound EGOA gtest gtest_main gmock_main) #${GUROBI_LIBRARIES}
add_test(NAME TestBound COMMAND TestBound)

####################################################################################
# Tests for QUEUE data structures ##################################################
####################################################################################

# add_executable(TestStdQueue DataStructures/Container/TestStdQueue.cpp)
# target_link_libraries(TestStdQueue EGOA gtest gtest_main gmock_main)
# add_test(NAME TestStdQueue COMMAND TestStdQueue)

add_executable(TestBinaryHeap DataStructures/Container/TestBinaryHeap.cpp)
target_link_libraries(TestBinaryHeap EGOA gtest gtest_main gmock_main)
add_test(NAME TestBinaryHeap COMMAND TestBinaryHeap)

add_executable(TestMappingBinaryHeap DataStructures/Container/TestMappingBinaryHeap.cpp)
target_link_libraries(TestMappingBinaryHeap EGOA gtest gtest_main gmock_main)
add_test(NAME TestMappingBinaryHeap COMMAND TestMappingBinaryHeap)

add_executable(TestBucket DataStructures/Container/TestBucket.cpp)
target_link_libraries(TestBucket EGOA gtest gtest_main gmock_main)
add_test(NAME TestBucket COMMAND TestBucket)

####################################################################################
# Tests for GRAPH data structures ##################################################
####################################################################################
# add_executable(TestGraph DataStructures/Graphs/TestGraph.cpp)
# target_link_libraries(TestGraph EGOA ${GUROBI_LIBRARIES} gtest gtest_main gmock_main)
# add_test(NAME TestGraph COMMAND TestGraph)

# add_executable(TestDynamicGraph DataStructures/Graphs/TestDynamicGraph.cpp)
# target_link_libraries(TestDynamicGraph EGOA ${GUROBI_LIBRARIES} gtest gtest_main gmock_main)
# add_test(NAME TestDynamicGraph COMMAND TestDynamicGraph)

# add_executable(TestPowerGrid DataStructures/Graphs/TestPowerGrid.cpp)
# target_link_libraries(TestPowerGrid EGOA ${GUROBI_LIBRARIES} gtest gtest_main gmock_main)
# add_test(NAME TestPowerGrid COMMAND TestPowerGrid)

# add_executable(TestBlockCutTree DataStructures/Graphs/TestBlockCutTree.cpp)
# target_link_libraries(TestBlockCutTree EGOA ${GUROBI_LIBRARIES} gtest gtest_main gmock_main)
# add_test(NAME TestBlockCutTree COMMAND TestBlockCutTree)

####################################################################################
# Tests for other data structures ##################################################
####################################################################################
# add_executable(TestPiecewiseLinearFunction DataStructures/TestPiecewiseLinearFunction.cpp)
# target_link_libraries(TestPiecewiseLinearFunction EGOA gtest gtest_main)
# add_test(NAME TestPiecewiseLinearFunction COMMAND TestPiecewiseLinearFunction)

####################################################################################
# Tests for PATH FINDING ALGORITHMS ################################################
####################################################################################
# add_executable(TestDominatingThetaPath Algorithms/PathFinding/TestDominatingThetaPath.cpp)
# target_link_libraries(TestDominatingThetaPath EGOA gtest gtest_main gmock_main)
# add_test(NAME TestDominatingThetaPath COMMAND TestDominatingThetaPath)

# add_executable(TestBetweennessCentrality Algorithms/Centralities/TestBetweennessCentrality.cpp)
# target_link_libraries(TestBetweennessCentrality EGOA gtest gtest_main gmock_main)
# add_test(NAME TestBetweennessCentrality COMMAND TestBetweennessCentrality)

# add_executable(TestGeneratorBasedBetweennessCentrality Algorithms/Centralities/TestGeneratorBasedBetweennessCentrality.cpp)
# target_link_libraries(TestGeneratorBasedBetweennessCentrality EGOA gtest gtest_main gmock_main)
# add_test(NAME TestGeneratorBasedBetweennessCentrality COMMAND TestGeneratorBasedBetweennessCentrality)

######################################################################################
# Tests for Flow Algorithms ##########################################################
######################################################################################
# add_executable(TestMaxFlow Algorithms/Flows/TestMaxFlow.cpp)
# target_link_libraries(TestMaxFlow EGOA gtest gtest_main gmock_main ${Boost_LIBRARIES})
# add_test(NAME TestMaxFlow COMMAND TestMaxFlow)

# Now simply link against gtest or gtest_main as needed
# add_executable(PowerFlowModel PowerFlowModels/PowerFlowModel.cpp)
# target_link_libraries(PowerFlowModel gtest gtest_main gmock_main EGOA)
# add_test(NAME TestPowerFlowModel COMMAND PowerFlowModel)

# Now simply link against gtest or gtest_main as needed
# add_executable(PowerFlow PowerFlowModels/PowerFlow.cpp)
# target_link_libraries(PowerFlow gtest gtest_main gmock_main EGOA)
# add_test(NAME TestPowerFlow COMMAND PowerFlow)
# 
######################################################################################
# Tests for MST ALGORITHMS ###########################################################
######################################################################################
# add_executable(TestSpanningTree Algorithms/SpanningTree/TestSpanningTree.cpp)
# target_link_libraries(TestSpanningTree EGOA gtest gtest_main gmock_main)
# add_test(NAME TestSpanningTree COMMAND TestSpanningTree)

######################################################################################
# Tests for other ALGORITHMS #########################################################
######################################################################################
# add_executable(TestBlockCutTreeTraversal Algorithms/TestBlockCutTreeTraversal.cpp)
# target_link_libraries(TestBlockCutTreeTraversal EGOA gtest gtest_main gmock_main)
# add_test(NAME TestBlockCutTreeTraversal COMMAND TestBlockCutTreeTraversal)

######################################################################################
# Tests for Mathematical Models ######################################################
######################################################################################

# add_executable(TestVariable MathematicalModel/Variables/TestVariable.cpp)
# target_link_libraries(TestVariable EGOA ${GUROBI_LIBRARIES} ${CPLEX_LIBRARIES} gtest gtest_main gmock_main)
# add_test(NAME TestVariable COMMAND TestVariable)

# add_executable(TestSolver MathematicalModel/Solver/TestSolver.cpp)
# target_link_libraries(TestSolver EGOA ${GUROBI_LIBRARIES} ${CPLEX_LIBRARIES} gtest gtest_main gmock_main)
# add_test(NAME TestSolver COMMAND TestSolver)

# add_executable(TestDcPf MathematicalModel/TestDcPf.cpp)
# target_link_libraries(TestDcPf EGOA ${GUROBI_LIBRARIES} gtest gtest_main gmock_main)
# add_test(NAME TestDcPf COMMAND TestDcPf)

# add_executable(TestDcMpf MathematicalModel/TestDcMpf.cpp)
# target_link_libraries(TestDcMpf EGOA ${GUROBI_LIBRARIES} gtest gtest_main gmock_main)
# add_test(NAME TestDcMpf COMMAND TestDcMpf)

# add_executable(TestDcMtsf MathematicalModel/TestDcMtsf.cpp)
# target_link_libraries(TestDcMtsf EGOA ${GUROBI_LIBRARIES} gtest gtest_main gmock_main)
# add_test(NAME TestDcMtsf COMMAND TestDcMtsf)

######################################################################################
# Tests for IO #######################################################################
######################################################################################
# add_executable(TestPyPsaParser IO/TestPyPsaParser.cpp)
# target_link_libraries(TestPyPsaParser EGOA gtest gtest_main gmock_main)
# add_test(NAME TestPyPsaParser COMMAND TestPyPsaParser)

# add_executable(TestGeojsonWriter IO/TestGeojsonWriter.cpp)
# target_link_libraries(TestGeojsonWriter EGOA gtest gtest_main gmock_main)
# add_test(NAME TestGeojsonWriter COMMAND TestGeojsonWriter)


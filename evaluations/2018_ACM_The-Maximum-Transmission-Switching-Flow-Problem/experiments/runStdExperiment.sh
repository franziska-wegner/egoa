#!/bin/sh
#
# runStdExperiment.sh
#
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#
# Runs the standard experiments for the paper.
#

EGOA_STD_CONFIG_FILE="../Configurations/localStdConfig.sh"
source "./Usages/standardUsage.sh"

#########################################################
# Execute ###############################################
#########################################################
source "../helper.sh"

# Clean output directory
if [ "${cleanOutputDirectory}" = "TRUE" ]; then
    echo "\n-- Clean output directory $(dirOutput)\n"
    $(/bin/rm -rf ${dirOutput}/*)
    sleep 2
fi

# Run executable on all files in directory
pids=""
for entry in "$dirBenchmarkData"/*; do
    if [ -f "$entry" ]; then
        echo "Run experiment for $entry"
        waitforprocesses $PROCESSES
        ${executable} -f "$entry" -a "$algorithm" -o "$dirOutput/" -z "$maxExecutionTime" -r "$trackSolutions" &
        pids+=" $!"
    fi
done

waitforallprocesses $pids

#########################################################
# Output general information ############################
#########################################################
echo
echo "---------------------------------------------------------------------------------------------------"
echo
echo "-- The config file is set to:\t\t${configFile}"
echo "-- Current directory is:\t\t$(pwd)"
echo
echo "Experiment Configuration Overview"
echo "\tAlgorithm:                              $algorithm"
echo "\tClean Output Directory:                 $cleanOutputDirectory"
echo "\tBenchmark Data Directory:               $dirBenchmarkData"
echo "\tOutput Directory:                       $dirOutput"
echo "\tExecutable:                             $executable"
echo "\tMaximum Execution Time:                 $maxExecutionTime"
echo "\tTrack Solutions:                        $trackSolutions"
echo "\tNumber of Parallel Executions:          $numParallelExecutions"
echo "\tNumber of Parallel Processes Per Algo:  $numParallelProcessesEach"

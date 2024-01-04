#!/bin/sh
#
# localConfig.sh
#
#   Created on:
#       Author: Franziska Wegner
#
# Project configuration on the local computer to avoid long command line text
# with arguments.
#
#########################################################
# Define local standard argument ########################
#########################################################

EGOA_ALGORITHM="DCMTSF"
EGOA_DIR_PATH_BENCHMARK_DATA="/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/IEEEcases/11-NESTA/nesta-0.7.0/opf"
EGOA_DIR_PATH_OUTPUT="/Users/franziska-wegner/Documents/work/frameworks/egoa/output"
EGOA_FILE_PATH_EXECUTABLE="/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/egoa"

# Maximum execution time of the algorithm
EGOA_MAXIMUM_EXECUTION_TIME="0"
# Track solutions over time (e.g., MILP solver via callbacks)
EGOA_TRACK_SOLUTIONS="TRUE"
# Number of parallel program executions (compute/server dependent)
EGOA_NUM_PARALLEL_EXECUTIONS="40"
# Number of parallel processes each execution of the algorithm gets (dependent
# on the evaluation)
EGOA_NUM_PARALLEL_PROCESSES="1"

# Clean output directory
EGOA_CLEAN_OUTPUT_DIR="TRUE"

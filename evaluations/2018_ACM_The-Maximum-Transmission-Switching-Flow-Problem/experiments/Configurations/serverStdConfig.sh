#!/bin/sh
#
# serverConfig.sh
# 
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#       
# Project configuration on the server to avoid long command line text with
# arguments.
# 
#########################################################
# Define server standard argument ########################
#########################################################

EGOA_ALGORITHM="DCMTSF"
EGOA_DIR_PATH_BENCHMARK_DATA=""
EGOA_DIR_PATH_OUTPUT=""
EGOA_FILE_PATH_EXECUTABLE=""
EGOA_EXECUTABLE_NAME="egoa"

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

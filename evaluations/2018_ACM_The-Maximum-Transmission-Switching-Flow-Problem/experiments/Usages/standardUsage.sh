#!/bin/sh
#
# experimentUsage.sh
# 
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#       
# Defines a standard usage interface for the experiments including the details
# of a specified configuration script. Templates for configuration scripts can
# be found under 
#   ./localConfig.sh 
#   ./serverConfig.sh
# where "./localConfig.sh" is the default configuration.  
#  

#########################################################
# Define input argument #################################
#########################################################

# Usage of this file --help
usage() { echo -e "Usage: $0 -a <algorithm> \t\t\t(default: DCMTSF)
                  \t\t -c <clean output directory> \t\t(default: FALSE)
                  \t\t -b <directory path to benchmark data> \t\t\t
                  \t\t -o <directory path to output> \t\t\t
                  \t\t -e <directory path to executable> \t\t\t
                  \t\t -t <maximum execution time> \t\t\t
                  \t\t -s <track solutions over time> \t\t\t(default: FALSE)
                  \t\t -p <number parallel executions> \t\t\t(default: ?)
                  \t\t -q <number parallel processes each> \t\t\t(default: 1)
                  \t\t -i <configuration file> \t\t\t
                                        " 1>&2; exit 1; }

# Check input arguments
while getopts ":a:c:b:o:e:t:s:p:q:" opt; do
  case $opt in
    a)
      algorithm="${OPTARG}"
      ;;
    c)
      cleanOutputDirectory=${OPTARG}
      ;;
    b)
      dirBenchmarkData=${OPTARG}
      ;;
    o)
      dirOutput=${OPTARG}
      ;;
    e)
      executable=${OPTARG}
      ;;
    t)
      maxExecutionTime=${OPTARG}
      ;;
    s)
      trackSolutions=${OPTARG}
      ;;
    p)
      numParallelExecutions=${OPTARG}
      ;;
    t)
      numParallelProcessesEach=${OPTARG}
      ;;
    i)
      configFile=${OPTARG}
      ;;
    \?)
      echo "Invalid option: -$OPTARG" >&2
      usage
      ;;
    :)
      ;;
  esac
done
shift "$((OPTIND-1))"

#########################################################
# Define local standard argument ########################
#########################################################
# Location and the file of the cmake configuration
if [ -z "${configFile}" ]; then
    configFile="$EGOA_STD_CONFIG_FILE"
fi

source "${configFile}"

#########################################################
# Check for empty options and fill ######################
#########################################################

# Algorithm (e.g., DCMTSF)
if [ -z "${algorithm}" ]; then
    algorithm="$EGOA_ALGORITHM"
fi

# Clean output directory
if [ -z "${cleanOutputDirectory}" ]; then
    cleanOutputDirectory="$EGOA_CLEAN_OUTPUT_DIR"
fi

# Path to the benchmark data directory
if [ -z "${dirBenchmarkData}" ]; then
    dirBenchmarkData="$EGOA_DIR_PATH_BENCHMARK_DATA"
fi

# Path to the output directory
if [ -z "${dirOutput}" ]; then
    dirOutput="$EGOA_DIR_PATH_OUTPUT"
fi

# Create output directory if it does not exist
if [ ! -d "${dirOutput}" ]; then
    mkdir "${dirOutput}"
fi

# Path to the executable file
if [ -z "${executable}" ]; then
    executable="$EGOA_FILE_PATH_EXECUTABLE"
fi

# Maximum execution time of the program
if [ -z "${maxExecutionTime}" ]; then
    maxExecutionTime="$EGOA_MAXIMUM_EXECUTION_TIME"
fi

# Track solutions over time (e.g., MILP solver via callbacks)
if [ -z "${trackSolutions}" ]; then
    trackSolutions="$EGOA_TRACK_SOLUTIONS"
fi

# Number of parallel executions
if [ -z "${numParallelExecutions}" ]; then
    numParallelExecutions="$EGOA_NUM_PARALLEL_EXECUTIONS"
fi

# Number of parallel processes each execution of the algorithm gets
if [ -z "${numParallelProcessesEach}" ]; then
    numParallelProcessesEach="$EGOA_NUM_PARALLEL_PROCESSES"
fi

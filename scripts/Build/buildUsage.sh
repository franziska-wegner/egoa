#!/bin/sh
#
# buildUsage.sh
# 
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#       
# Defines a standard usage interface for the build scripts including the
# details of a specified configuration script. Templates for configuration
# scripts can be found under 
#   ./localConfig.sh 
#   ./serverConfig.sh
# where "./localConfig.sh" is the default configuration.  
#  

#########################################################
# Define input argument #################################
#########################################################

# Usage of this file --help
usage() { echo -e "Usage: $0 -b <build mode> \t\t\t(default: Debug)
                  \t\t -c <clean build directory> \t\t(default: FALSE)
                  \t\t -t <cmake target> \t\t\t(default: \"..\")
                  \t\t -i <build directory> \t\t\t(default: \"../build-debug\")
                  \t\t -s <config file> \t\t\t(default: \"./localConfig.sh\")
                  \t\t <options> \nOPTIONS:\n\t \tpath to executable \t(default: \"../../build-debug/bin/egoa\") \
                                           \n\t \tBuild directory \t\t(default: \"<Path-To-Build-Directory>/build-<BUILDMODE>\") \
                                           \n\t \tCmake directory \t\t(default: \"<Path-To-Project-Directory>\") \
                                        " 1>&2; exit 1; }

# Check input arguments
while getopts ":b:c:t:i:s:" opt; do
  case $opt in
    b)
      buildMode="${OPTARG}"
      ;;
    c)
      cleanBuildDirectory=${OPTARG}
      ;;
    t)
      cmakeTarget=${OPTARG}
      ;;
    i)
      buildDirectory=${OPTARG}
      ;;
    s)
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
    configFile="./localConfig.sh"
fi

source "${configFile}"

#########################################################
# Check for empty options and fill ######################
#########################################################

# Mode (e.g., Debug or Release)
if [ -z "${buildMode}" ]; then
    buildMode="$BUILD_MODE"
fi

# Clean build directory
if [ -z "${cleanBuildDirectory}" ]; then
    cleanBuildDirectory="$BUILD_CLEAN_DIR"
fi

# Path to the folder of the project's main cmake file location
if [ -z "${cmakeTarget}" ]; then
    cmakeTarget="$CMAKE_TARGET"
fi

# Build directory (e.g., build-debug or build-release)
if [ -z "${buildDirectory}" ]; then
    # usage
    if [ "${buildMode}" = "Release" ]; then
        buildDirectory="$BUILD_DIR_RELEASE"
    else
        buildDirectory="$BUILD_DIR_DEBUG"
    fi
fi

# Create build directory if it does not exist
if [ ! -d "${buildDirectory}" ]; then
    mkdir "${buildDirectory}"
fi

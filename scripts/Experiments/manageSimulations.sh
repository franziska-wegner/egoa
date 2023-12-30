#!/bin/sh
#
# manageSimulations.sh
#
#   Created on: Feb 03, 2019
#       Author: Franziska Wegner
#   Basic idea: "Modern Computational Science 18 - Energy of the Future"
#               by Stefan Harfst and Alexander K. Hartmann
#               ISBN 978-3-8142-2370-4
#
# This script enables to manage simulations on a large number of
# server/compute nodes. It is basically a wrapper that can check on a list of
# server information such as running jobs. In addition, it provides the
# possibility to run all kind of commands on multiple server such as kill,
# pause, or start of simulations.
#
# Examples:
#   ./manageSimulations.sh date -u
#   ./manageSimulations.sh killall egoa
#
# To avoid entering at each time your password for the compute node you can do
# the following steps and do step 2 for all necessary server (if not mirrored):
#
#   1. user@localmachine> ssh-keygen -t rsa
#   2. ssh-copy-id user@server.node.kit.edu
#
# Note:
#   1. Change working directory to 'run' and excutes './runme >& logfile &'
#           >ssh ${server_node} -n "cd run; ./runme >& logfile &"
#           -s TRUE -c "cd run; ./runme"
#   2. Check for simulations
#           ssh ${server_node} -n "/bin/ps axo user,pid,%cpu,%mem,lstart,etime,nice,stat,time,cmd | egrep \" R | RN | RN+ | R+ \" "
#           -b TRUE
#           ssh ${server_node} -n "/bin/ps axo user,pid,%cpu,%mem,lstart,etime,nice,stat,time,cmd | egrep \" *windfarmCabling* \" "
#           -b TRUE -c "*windfarmCabling*"
#

if [ -f "../Personal/StandardConfiguration.sh" ]; then
    source "../Personal/StandardConfiguration.sh"
fi

# List of all server we want to manage
if [ -z "${SERVER_LIST}" ]; then
    SERVER_LIST="$(hostname)"
fi

COMMAND="R | RN | RN+ | R+"

#########################################################
# Define input argument #################################
#########################################################

# Usage of this file --help
usage() { echo "Usage: $0 <Options>
                  Options:
                          -h <help>
                          -c <command>                                                 (default: \"date -u\")
                          -b <check status of running simulations -c becomes filter>   (default: FALSE)
                          -s <run simulation>                                          (default: FALSE)
                          -w <list of server/workstation/compute>                      (default: Either from ../Personal/StandardConfiguration.sh \"\$SERVER_LIST\"
                                                                                                          or \"host.local\")
                  Examples:
                        > ./manageSimulations.sh -c \"date -u\"
                        > ./manageSimulations.sh -c \"killall egoa\"
                        > ./manageSimulations.sh -b TRUE -c \"*egoa*\"
                        > ./manageSimulations.sh -s TRUE -w \"server1.kit.edu server2.kit.edu\"
                                                         -c \"cd /algoDaten/egoa/build-debug/bin; ./egoa >& logfile &\"
                                        " 1>&2; exit 1; }

# Check input arguments
while getopts ":c:b:s:d:w:" opt; do
  case $opt in
    c)
      command="${OPTARG}"
      ;;
    b)
      checkStatus=${OPTARG}
      ;;
    s)
      runSimulation=${OPTARG}
      ;;
    w)
      serverList=${OPTARG}
      ;;
    \?)
      echo "Invalid option: -${OPTARG}" >&2
      usage
      ;;
    :)
      ;;
  esac
done
shift "$((OPTIND-1))"


#########################################################
# Check for empty options and fill ######################
#########################################################

# Check the status of the simulations on the list of server?
if [ -z "${checkStatus}" ]; then
    checkStatus="FALSE"
fi

# Run simulation using the command field
if [ -z "${runSimulation}" ]; then
    runSimulation="FALSE"
fi

# List of server
if [ -z "${serverList}" ]; then
    serverList="${SERVER_LIST}"
fi

# Command
if [ -z "${command}" ]; then
    if [ "${checkStatus}" = "TRUE" ]; then
        command="${COMMAND}"
    elif [ "${runSimulation}" = "TRUE" ]; then
        usage
    else
        command="date -u"
    fi

fi

for compute_node in ${serverList} ;
do
    echo "Server \"${compute_node}\":"
    echo "-------------------------------------------------"
    if [ "${checkStatus}" = "TRUE" ]; then
        ssh ${compute_node} -n "/bin/ps axo user,pid,%cpu,%mem,lstart,etime,nice,stat,time,cmd | egrep \" ${command} \" "
    elif [ "${runSimulation}" = "TRUE" ]; then
        ssh ${compute_node} -n "${command} >& logfile &"
    else
        ssh ${compute_node} -n ${command}
    fi
    echo "================================================="
done

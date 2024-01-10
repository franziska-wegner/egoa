#!/bin/sh
#
# serverInformation.sh
#
#   Created on: Jan 30, 2019
#       Author: Franziska Wegner
#
# Get the physical information about the Unix machine. These information are
# required for the evaluation/simulation section.
#

uname -a
cat /proc/version
# Information about the Linux distribution
lsb_release -a
# Linux release information
cat /etc/*release*

# Display information about the CPU architecture.
lscpu
# print out an extended readable format: CPU | NODE | SOCKET | CORE | L1d:L1i:L2:L3 | ONLINE | MAXMHZ | MINMHZ
lscpu -e
# Show free and used memory
cat /proc/meminfo

# All hardware information: Motherboard, CPU, Vendor, Serial-number, RAM, Disks, and other information (BIOS)
dmidecode | less

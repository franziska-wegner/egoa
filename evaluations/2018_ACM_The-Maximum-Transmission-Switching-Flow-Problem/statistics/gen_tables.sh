#!/bin/sh
#
# gen_tables.sh
#
#   Created on: -
#       Author: Franziska Wegner
#
# Generates the short and long tables that are used in the paper
# "The Maximum Transmission Switching Flow Problem", 2018, ACM e-Energy,
# doi:10.1145/3208903.3208910.
#

/Users/fwegner/anaconda/bin/Rscript ./table_models_algorithms.R $PATH "tbl:MTSF_MPF_PF_MF_long" "TRUE" "FALSE" >$OUTPUT/tbl-milp-comparison-long.tex
#........................................................................................................./\
#.......................................................................................................Short?
#.........................................................................................................\/
/Users/fwegner/anaconda/bin/Rscript ./table_models_algorithms.R $PATH "tbl:MTSF_MPF_PF_MF_short" "TRUE" "TRUE" >$OUTPUT/tbl-milp-comparison-short.tex

# ---------------------------------------------------------------------------
# Replace strings
# ---------------------------------------------------------------------------
/usr/bin/sed -i -- 's/\$\\backslash\$/\\/g' $OUTPUT/*
/usr/bin/sed -i -- 's/\\{/{/g' $OUTPUT/*
/usr/bin/sed -i -- 's/\\}/}/g' $OUTPUT/*
/bin/rm -f $OUTPUT/*.tex-*

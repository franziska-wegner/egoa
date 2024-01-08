#!/bin/sh
#
# gen_dc_maximizing_gurobi_csv_files.sh
#
#   Created on: -
#       Author: Franziska Wegner
#
# Defines a standard usage interface for the experiments including the details
# of a specified configuration script. Templates for configuration scripts can
# be found under
#   ./localConfig.sh
#   ./serverConfig.sh
# where "./localConfig.sh" is the default configuration.
#

if [ -n "$1" ]; then
    PATH=$1
else
    PATH="/Users/fwegner/Documents/work/frameworks/egoa/.build/test/testdata/dc_mtsf_cases/"
fi
echo "Path to the benchmark cases:\t$PATH"

if [ -n "$2" ]; then
    OUTPUT=$2
else
    OUTPUT="/Users/fwegner/Documents/work/frameworks/egoa/.build/test/testdata"
fi
echo "Output path:\t$OUTPUT"
# "/Users/fwegner/Documents/work/frameworks/egoa/.build/test/testdata/dc_mtsf_cases/"
# "/Users/fwegner/Documents/work/frameworks/egoa/.build/test/testdata/dc_mtsf_cases/dc_pf_gurobi.csv"

# ---------------------------------------------------------------------------
# Run Power Flow (PF)
# ---------------------------------------------------------------------------
# /Users/fwegner/Documents/work/frameworks/egoa/.build/bin/DCMTSF $PATH "$OUTPUT/dc_pf_gurobi.csv" PF gurobi

# find "/Users/fwegner/Documents/work/frameworks/egoa/.build/bin/" -name \*.lp -exec cp {} "/Users/fwegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/MTSF-gurobi/lp"
# find "/Users/fwegner/Documents/work/frameworks/egoa/.build/bin/" -name \*.mps -exec cp {} "/Users/fwegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/MTSF-gurobi/mps"
# find "/Users/fwegner/Documents/work/frameworks/egoa/.build/bin/" -name \*.rew -exec cp {} "/Users/fwegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/MTSF-gurobi/rew"
# find "/Users/fwegner/Documents/work/frameworks/egoa/.build/bin/" -name \*.rlp -exec cp {} "/Users/fwegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/MTSF-gurobi/rlp"

# ---------------------------------------------------------------------------
# Run Maximum Power Flow (MPF)
# ---------------------------------------------------------------------------
/Users/fwegner/Documents/work/frameworks/egoa/.build/bin/DCMTSF $PATH "$OUTPUT/dc_MYTEST_mpf_gurobi.csv" MPF gurobi

# ---------------------------------------------------------------------------
# Run Maximum Transmission Switching Flow (MTSF)
# ---------------------------------------------------------------------------
# /Users/fwegner/Documents/work/frameworks/egoa/.build/bin/DCMTSF $PATH "$OUTPUT/dc_mtsf_gurobi.csv" DCMTSF gurobi

# ---------------------------------------------------------------------------
# Run Maximum Flow (MF)
# ---------------------------------------------------------------------------
# /Users/fwegner/Documents/work/frameworks/egoa/.build/bin/DCMTSF $PATH "$OUTPUT/dc_mf_gurobi.csv" MF gurobi

# ---------------------------------------------------------------------------
# Run Optimal Transmission Switching (OTS)
# ---------------------------------------------------------------------------
# /Users/fwegner/Documents/work/frameworks/egoa/.build/bin/DCOTS "/Users/fwegner/Documents/work/frameworks/egoa/.build/test/testdata/dc_mtsf_cases/" "/Users/fwegner/Documents/work/frameworks/egoa/.build/test/testdata/dc_mtsf_cases/dc_ots_gurobi.csv" DCOTS gurobi
# /Users/fwegner/Documents/work/frameworks/egoa/.build/bin/DCOTS $PATH "$OUTPUT/dc_ots_gurobi.csv" DCOTS gurobi

# ---------------------------------------------------------------------------
# Run Maximum Spanning Tree with MF (MaxStMF)
# ---------------------------------------------------------------------------
# /Users/fwegner/Documents/work/frameworks/egoa/.build/bin/MaxST "/Users/fwegner/Documents/work/frameworks/egoa/.build/test/testdata/dc_mtf_cases/" "/Users/fwegner/Documents/work/frameworks/egoa/.build/test/testdata/dc_mtsf_cases/dc_MaxST_gurobi.csv"
# /Users/fwegner/Documents/work/frameworks/egoa/.build/bin/MaxST $PATH "$OUTPUT/dc_maxst_mf_gurobi.csv" MF gurobi

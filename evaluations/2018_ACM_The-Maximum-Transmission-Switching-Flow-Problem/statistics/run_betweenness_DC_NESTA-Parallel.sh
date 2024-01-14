#!/bin/sh
#
# run_betweenness_DC_NESTA-Parallel.sh
#
#   Created on: -
#       Author: Franziska Wegner
#
# Defines a standard script to run the DTP betweenness centrality
# on the NESTA benchmark cases in parallel mode.
#

if [ -n "$1" ]; then
    PATH=$1
else
    PATH="/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/"
fi
echo "Path to the benchmark cases:\t$PATH"

if [ -n "$2" ]; then
    OUTPUT=$2
else
    OUTPUT="/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/tables"
fi
echo "Output path:\t$OUTPUT"

# ---------------------------------------------------------------------------
# Check number of Threads (OpenMP)
# ---------------------------------------------------------------------------
echo "Standard number of OpenMP threads of the system is $OMP_NUM_THREADS"
export OMP_NUM_THREADS=1
echo "Number of OpenMP Threads for the run is $OMP_NUM_THREADS\n"

# ---------------------------------------------------------------------------
# Dominating Theta Path (DTP) betweenness centrality
# ---------------------------------------------------------------------------
# with "->"" does not work or is to slow
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case3_lmbd.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case3_lmbd.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case4_gs.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case4_gs.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case5_pjm.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case5_pjm.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case6_c.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case6_c.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case6_ww.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case6_ww.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case9_wscc.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case9_wscc.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case14_ieee.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case14_ieee.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case24_ieee_rts.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case24_ieee_rts.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"

# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case30_as.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case30_as.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case30_fsr.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case30_fsr.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case30_ieee.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case30_ieee.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case39_epri.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case39_epri.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case57_ieee.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case57_ieee.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case73_ieee_rts.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case73_ieee_rts.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case89_pegase.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case89_pegase.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case118_ieee.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case118_ieee.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case162_ieee_dtc.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case162_ieee_dtc.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case189_edin.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case189_edin.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case300_ieee.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case300_ieee.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case2383wp_mp.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case2383wp_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case2736sp_mp.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case2736sp_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case2737sop_mp.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case2737sop_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case2746wop_mp.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case2746wop_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case2746wp_mp.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case2746wp_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case3012wp_mp.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case3012wp_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case3120sp_mp.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case3120sp_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"

# /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case29_edin.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case29_edin.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# # -> /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case3375wp_mp.m" -sf "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/SwitchingBetweenness_nesta_case3375wp_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"

/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case3_lmbd.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case3_lmbd.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case4_gs.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case4_gs.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case5_pjm.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case5_pjm.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case6_c.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case6_c.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case6_ww.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case6_ww.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case9_wscc.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case9_wscc.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case14_ieee.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case14_ieee.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case24_ieee_rts.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case24_ieee_rts.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"

/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case30_as.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case30_as.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case30_fsr.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case30_fsr.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case30_ieee.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case30_ieee.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case39_epri.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case39_epri.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case57_ieee.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case57_ieee.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case73_ieee_rts.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case73_ieee_rts.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case89_pegase.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case89_pegase.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case118_ieee.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case118_ieee.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case162_ieee_dtc.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case162_ieee_dtc.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case189_edin.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case189_edin.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case300_ieee.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case300_ieee.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case2383wp_mp.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case2383wp_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case2736sp_mp.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case2736sp_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case2737sop_mp.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case2737sop_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case2746wop_mp.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case2746wop_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case2746wp_mp.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case2746wp_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case3012wp_mp.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case3012wp_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case3120sp_mp.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case3120sp_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"

/Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case29_edin.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case29_edin.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"
# # -> /Users/franziska-wegner/Documents/work/frameworks/egoa/.build/bin/dtpCentrality -i "/Users/franziska-wegner/Documents/work/frameworks/egoa/data/PowerGrids/nesta/dc_mtsf_cases/nesta_case3375wp_mp.m" -sf "/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/SwitchingBetweenness_nesta_case3375wp_mp.csv" -a DTP -cr sm | /usr/bin/egrep -v "Academic license - for non-commercial use only"

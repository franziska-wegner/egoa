#!/bin/sh
#
# gen_plot_dtp_betweenness_centrality.sh
#
#   Created on: -
#       Author: Franziska Wegner
#
# Generates the DTP betweenness centrality plot that is used in the paper
# "The Maximum Transmission Switching Flow Problem", 2018, ACM e-Energy,
# doi:10.1145/3208903.3208910.
#

if [ -n "$1" ]; then
    PATH=$1
else
    PATH="/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/"
fi
echo "\nPath to the benchmark cases:\t$PATH"

if [ -n "$2" ]; then
    OUTPUT=$2
else
    OUTPUT="/Users/franziska-wegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/plots"
fi
echo "Output path:\t\t\t$OUTPUT"

if [ -n "$3" ]; then
    AS_STANDALONE=$3
else
    AS_STANDALONE=false
fi
echo "Write .tex as standalone:\t$AS_STANDALONE\n"

# ---------------------------------------------------------------------------
# Run plots
# - does not work: # /Users/fwegner/anaconda/bin/Rscript
# ---------------------------------------------------------------------------
echo "RUN SCRIPTS IN RSTUDIO USING CMD+B! ISSUE COULD NOT BE RESOLVED. Franzi"
# if [ $AS_STANDALONE != false ]; then # Print out as tex standalone
# echo "Print out as tex standalone"
# /Library/Frameworks/R.framework/Versions/Current/Resources/Rscript ./plot_dtp_betweenness_centrality_single.R "$PATH" "$OUTPUT" FALSE TRUE
# /Library/Frameworks/R.framework/Versions/Current/Resources/Rscript ./plot_dtp_betweenness_centrality_single_cutY.R "$PATH" "$OUTPUT" FALSE TRUE
# else # Print out as tex
# echo "Print out as .tex includeable file"
# /Library/Frameworks/R.framework/Versions/Current/Resources/Rscript ./plot_dtp_betweenness_centrality_single.R "$PATH" "$OUTPUT" FALSE FALSE
# /Library/Frameworks/R.framework/Versions/Current/Resources/Rscript ./plot_dtp_betweenness_centrality_single_cutY.R "$PATH" "$OUTPUT" FALSE FALSE
# fi

# All Cases in one plot with quantiles
# /Library/Frameworks/R.framework/Versions/Current/Resources/Rscript ./plot_dtp_betweenness_centrality_all_quantiles.R "$PATH" "$OUTPUT/plot_dtp_betweenness_centrality_all_quantiles" "FALSE"

# ---------------------------------------------------------------------------
# Replace strings
# ---------------------------------------------------------------------------
# /usr/bin/sed -i -- 's/\\tablecase/tablecase/g' "$OUTPUT/DTP_BC-AllNestaCases_And_Quantiles.tex"
# /usr/bin/sed -i -- 's/\\{/{/g' $OUTPUT/*
# /usr/bin/sed -i -- 's/\\}/}/g' $OUTPUT/*
# /bin/rm -f $OUTPUT/*.tex-*

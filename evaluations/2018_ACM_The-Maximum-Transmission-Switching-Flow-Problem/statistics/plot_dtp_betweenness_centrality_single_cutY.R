#! /opt/local/bin/Rscript
#
# plot-maxst-vs-mtsf-violin-swarm.R
#
#   Created on: -
#       Author: Franziska Wegner
#
# This script computes the DTP betweenness centrality plot for each case
# in "The Maximum Transmission Switching Flow Problem", 2018, ACM e-Energy,
# doi:10.1145/3208903.3208910.
#

require(lattice)
library(lattice)

#install.packages('plotrix', repos='http://cran.us.r-project.org')
library(plotrix)
require(plotrix)

# install.packages('Cairo')
# Necessary for saving as SVG
library(Cairo)
require(Cairo)
library(latex2exp)

# install.packages('tikzDevice')
library('tikzDevice')
require('tikzDevice')
library(tools)
require(tools)

source("../Helper/colors.R", chdir=T)

# Arguments
args <- commandArgs(trailingOnly = TRUE)
argument.path       <- args[1]
argument.output     <- args[2]
argument.standAlone <- args[3]
argument.latex_path <- args[4]

if(is.na(argument.path)){
  # new
  argument.path       <- "/Users/fwegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/"
  # old
  # argument.path       <- "/Users/fwegner/Desktop/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/"
}
if(is.na(argument.output)){
  argument.output     <- "/Users/fwegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/plots/"
}
if(is.na(argument.standAlone)){
  argument.standAlone <- FALSE
}
if(!is.na(argument.latex_path)){
  options(latexcmd = argument.latex_path)
}else{
  argument.latex_path = "/opt/local/bin/pdflatex"
  options(latexcmd    = "/opt/local/bin/pdflatex")
}

lfontsize = 1.0

# Extract necessary files
files <- NULL
files <- list.files(path = argument.path, pattern = "\\-dtpbc-mpf.csv$")
files <- files[files != ""]

# ------- READING IN DATA FROM A CSV -------------------------------------------

while ( length(files)!=0 ) {
  data      <- NULL
  data      <- read.csv(paste(argument.path, files[1], sep = ""), header=TRUE, sep=",")
  data      <- data[order(data$BetweennessNormalizedValue, decreasing = TRUE),]
  #data_temp = data
  data_temp <- subset(data, data$OptimumSolutions > 0)

  scenario  <- strsplit(files[1], "_")
  filename  <- files[1]
  filename  <- gsub('.{4}$', '', filename)
  files[1]  <- ""
  files     <- files[files != ""]

  if(nrow(data) == 0){
    next
  }

# ------- PLOT DATA USING TIKZ -------------------------------------------
  filename = paste("plot", filename, sep="-")

  if ( argument.standAlone == TRUE ) { # Tex file for standalone
    tex_output_file <- paste(argument.output, filename, "-cutY-standalone", ".tex",sep = "")
    tikzDevice::tikz(tex_output_file,
                     width      = 6.1,
                     height     = 3.75,
                     pointsize  = 8,
                     standAlone = TRUE)
  } else { # Tex file as include
    tex_output_file <- paste(argument.output, filename, "-cutY", ".tex",sep = "")
    tikzDevice::tikz(tex_output_file,
                     width      = 6.1,
                     height     = 3.75,
                     pointsize  = 8,
                     standAlone = FALSE)
  }
  print(paste("File written to: ", tex_output_file, sep = "") )

  # create extra margin room on the right for an axis
  # mar=c(unten, links, oben, rechts)
  par(mar=c(4,5,3.5,5.3)+.1, mgp = c(4, 0.8, 0), xpd=TRUE)
  par(las=1, cex=lfontsize) # make label text perpendicular to axis

  leg = list()
  leg = c("$\\mathsf{MPF}~|S|=1$", "Normalized~$c_\\mathsf{DTPBC}$")
  l_colim = c(seq(from=1,to=nrow(data),by=1))

  # Calculate x, y, z axis limits
  if ( ( is.finite( min(data_temp$OptimumSolutions))) && ( is.finite(max(data_temp$OptimumSolutions) )) ) {
    l_ylim=c(min(data_temp$OptimumSolutions), max(data_temp$OptimumSolutions))
  } else {
    l_ylim=c(0, 0)
  }

  l_xlim=c(1, nrow(data))

  if ( ( is.finite(min(data_temp$BetweennessNormalizedValue) )) && ( is.finite(max(data_temp$BetweennessNormalizedValue) ) ) ) {
    l_clim=c(min(data_temp$BetweennessNormalizedValue), max(data_temp$BetweennessNormalizedValue))
  } else {
    l_clim=c(0, 0)
  }

  # Plot z-axis first since all other lines should be above it
  plot(l_colim,data$BetweennessNormalizedValue,
       type="l",
       xlab="",
       ylab="",
       ylim=l_clim,
       xlim=l_xlim,
       xaxt="n",
       yaxt="n",
       col=KITseablue30,
       lty=2,
       lwd=2
       #bty='n' # Plot without box
  )

  # Add a title for the right axis
  axis( 4, cex.axis = 1, las = 2 )

  # Add legend
  scenario[[1]][4] <-  gsub( '.{14}$', '', scenario[[1]][4])
  legendName       <- paste( scenario[[1]][2], scenario[[1]][3], scenario[[1]][4], sep="\\_")
  legendName       <- paste( "\\texttt{", legendName, "}", sep="")
  legend("top",
         inset=c(-4,-0.18),
         title=legendName,#paste("Legend for", ix), # add name of the whole plot
         legend=leg,
         lty=c(1,2),
         lwd=c(2,2),
         col=c(KITgreen, KITseablue30),
         ncol=2,
         bty='n',
         cex=.89,
         text.font=1
  )

  # No plotting, but ajusting sizes and units
  par(new=TRUE)
  plot(max(l_colim), max(data$OptimumSolutions),  type="l",
       xlab="",
       ylab="",
       ylim=l_ylim,
       xlim=l_xlim,
       xaxt="n",
       yaxt="n",
       cex.axis=1,
       cex.lab=1,
       # lty=3,
       col=KITgreen,
       lwd=0,
       bty='n' # Plot without box
  )

  # Add a title for the left axis
  y_delta = ( par("yaxp")[2] - par("yaxp")[1] ) / par("yaxp")[3]
  lab = seq( par("yaxp")[1], par("yaxp")[2], len = par("yaxp")[3] )
  # lab_temp = pretty(data$OptimumSolutions, n = par("yaxp")[3])

  ylab <- lab
  ylab[(ylab < l_ylim[1] ) & (ylab < min(data_temp$OptimumSolutions)) & ylab == min(ylab) ] = 0

  axis(2, las=2, cex.axis=1, at=lab, labels=sprintf("%.0f", ylab ) )
  # axis(2, las=2 )

  if (min(ylab) == 0) {
    b_pos <- lab[1] + y_delta/1.8
  } else {
    if (lab[1] - y_delta/5 > min(data_temp$OptimumSolutions)){
      b_pos <- min(data_temp$OptimumSolutions)
    } else {
      b_pos <- lab[1] - y_delta/5
    }
  }

  axis.break( axis    = 2,
              breakpos = b_pos,
              breakcol= KITred70,
              style   = "slash",
              brw     = 0.035)

  # Plotting main line
  par(new=TRUE)
  plot(l_colim, data$OptimumSolutions,
       type     = "l",
       xlab     = "",
       ylab     = "",
       ylim     = l_ylim,
       xlim     = l_xlim,
       xaxt     = "n",
       yaxt     = "n",
       cex.axis = 1,
       cex.lab  = 1,
       # lty=3,
       col      = KITgreen,
       lwd      = 2,
       bty      = 'n' # Plot without box
  )

  # Plot the maximum as a point with y-value as label
  par(new=TRUE)
  plot(which.max(data$OptimumSolutions), max(data$OptimumSolutions),
       type     = "p",
       xlab     = "",
       ylab     = "",
       ylim     = l_ylim,
       xlim     = l_xlim,
       xaxt     = "n",
       yaxt     = "n",
       cex.axis = 1,
       cex.lab  = 1,
       cex      = 1.4,
       pch      = 16,
       lty      = 5,
       col      = KITred50,
       bty      = 'n'      # Plot without box
  )
  # Calculate reasonable offset to place the labels for the point
  offset_x = (l_xlim[2]-l_xlim[1]) * -8 / 100
  offset_y = (l_ylim[2]-l_ylim[1]) * -5 / 100
  # Place text
  text(which.max(data$OptimumSolutions) - offset_x,
       max(data$OptimumSolutions)       + offset_y,
       labels = sprintf("%.2f", max(data$OptimumSolutions)),
       cex    = 0.9,
       col    = KITblack70
      )

  # Add a title for the bottom axis
  lab = seq(par("xaxp")[1], par("xaxp")[2], len = par("xaxp")[3])
  axis(1,cex.axis=1, at=lab, labels=sprintf("%.0f", lab))

  # Add x-axis label (bottom)
  mtext("Switched Edge", side=1, line=2, font=1, cex=0.95)

  par(las=0) # make label text perpendicular to axis

  # Add y-axis label (left)
  mtext("$\\mathsf{MPF}$ in~$\\mathrm{MW}$",side=2, line=3.5, cex=0.95)
  # Add z-axis label (right)
  mtext("Normalized~$c_\\mathsf{DTPBC}$",side=4, line=4.0, cex=0.95)

  par(font=1)
  dev.off()

} # while files

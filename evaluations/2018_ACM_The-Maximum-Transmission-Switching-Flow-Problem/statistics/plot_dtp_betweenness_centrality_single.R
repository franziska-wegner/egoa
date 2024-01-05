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

# install.packages('Cairo')
# Necessary for saving as SVG
library(Cairo)
require(Cairo)
library(latex2exp)

require(lattice)
library(lattice)

source("../Helper/colors.R", chdir=T)

# Arguments
args <- commandArgs(trailingOnly = TRUE)
argument.path       <- args[1]
argument.output     <- args[2]
argument.saveToPdf  <- args[3]
argument.standAlone <- args[4]
argument.latex_path <- args[5]

if(is.na(argument.path)){
  argument.path       <- "/Users/fwegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/"
}
if(is.na(argument.output)){
  argument.output     <- "/Users/fwegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/"
}
if(is.na(argument.saveToPdf)){
  argument.saveToPdf  <- TRUE
}
if(is.na(argument.standAlone)){
  argument.standAlone <- TRUE
}
if(!is.na(argument.latex_path)){
  options(latexcmd = argument.latex_path)
}else{
  argument.latex_path = "/opt/local/bin/pdflatex"
  options(latexcmd = "/opt/local/bin/pdflatex")
}

# Extract necessary files
files <- NULL
files <- list.files(path = argument.path, pattern = "\\-dtpbc-mpf.csv$")
files <- files[files != ""]

# ------- READING IN DATA FROM A CSV -------------------------------------------

while (length(files)!=0){
  # ------- READING DATA FROM A CSV -------------------------------------------
  data = NULL
  data = read.csv(paste(argument.path, files[1], sep = ""), header=TRUE, sep=",")
  data = data[order(data$BetweennessNormalizedValue, decreasing = TRUE),]

  scenario <- strsplit(files[1], "_")
  filename <- files[1]
  filename = gsub('.{4}$', '', filename)
  files[1] <- ""
  files <- files[files != ""]

  # ------- PLOT DATA ------------------------------------------------------------
  if (argument.saveToPdf){
      mainfont <- "Garamond"
      CairoFonts(regular = paste(mainfont,"style=Regular",sep=":"),
               bold = paste(mainfont,"style=Bold",sep=":"),
               italic = paste(mainfont,"style=Italic",sep=":"),
               bolditalic = paste(mainfont,"style=Bold Italic,BoldItalic",sep=":"))
      pdf <- CairoPDF

      filename = paste("plot", filename, sep="-")
      pdf(paste(argument.output, filename, sep = ""))

      lfontsize = 1.0

      # create extra margin room on the right for an axis
      # mar=c(unten, links, oben, rechts)
      par(mar=c(4,5.8,3.5,4.3)+.1, mgp = c(4, 0.8, 0), xpd=TRUE)
      par(las=1, cex=lfontsize) # make label text perpendicular to axis

      leg = list()
      l_colim = c(seq(from=1,to=nrow(data),by=1))

      l_ylim=c(min(data$OptimumSolutions), max(data$OptimumSolutions))
      l_xlim=c(1, nrow(data))
      l_clim=c(min(data$BetweennessNormalizedValue), max(data$BetweennessNormalizedValue))

      leg = c("MPF by removing an edge", "Normalized DTP betweenness centrality")

      plot(l_colim,data$BetweennessNormalizedValue, type="l",
           xlab="",
           ylab="",
           ylim=l_clim,
           xlim=l_xlim,
           xaxt="n",
           yaxt="n",
           col=KITseablue30,
           lty=2,
           lwd=2
      )


      par(new=TRUE)

      plot(l_colim, data$OptimumSolutions,  type="l",
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
                                            lwd=2
                                            )

      #par(new=TRUE)

      # add a title for the left axis
      lab = seq(par("yaxp")[1], par("yaxp")[2], len = par("yaxp")[3])
      #axis(2, cex.axis=1, at=lab, labels=sprintf("%.2f", data$OptimumSolution))
      axis(2, las=2)

      par(new=TRUE)

      # plot max as point with x label
      plot(which.max(data$OptimumSolutions), max(data$OptimumSolutions), type="p",
           xlab="",
           ylab="",
           ylim=l_ylim,
           xlim=l_xlim,
           xaxt="n",
           yaxt="n",
           cex.axis=1,
           cex.lab=1,
           pch=16,
           lty=3,
           col=KITred50
      )
      offset_x = (l_xlim[2]-l_xlim[1]) * -6 / 100
      offset_y = (l_ylim[2]-l_ylim[1]) * 2 / 100
      text(which.max(data$OptimumSolutions)-offset_x, max(data$OptimumSolutions)+offset_y, labels = sprintf("%.2f", max(data$OptimumSolutions)), cex = 1, col = KITblack70)

      # add a title for the right axis
      axis(4,cex.axis=1)

      # add a title for the bottom axis
      lab = seq(par("xaxp")[1], par("xaxp")[2], len = par("xaxp")[3])
      axis(1,cex.axis=1, at=lab, labels=sprintf("%.0f", lab))
      # add x-axis label (bottom)

      mtext("Switched Edge", side=1, line=2, font=1, cex=lfontsize)

      par(las=0) # make label text perpendicular to axis
      # add y-axis label (left)
      mtext("MPF Costs in $/MWh",side=2, line=3.5, cex=lfontsize)
      # add z-axis label (right)
      mtext("Normalized DTP Betweenness Centrality",side=4, line=3.0, cex=lfontsize)

      # add legend
      #install.packages("extrafont")
      #library(extrafont)

      scenario[[1]][4] = gsub('.{14}$', '', scenario[[1]][4])
      legendName = paste(scenario[[1]][2], scenario[[1]][3], scenario[[1]][4], sep="_")
      #legendName = paste( "$\\mathtt ", legendName, "$", sep="")
      legend("top",
             inset=c(0,-0.15),
             title=legendName,
             legend=leg,
             lty=c(1,3),
             lwd=c(2,2),
             col=c(KITgreen, KITseablue30),
             ncol=1,
             bty='n',
             cex=.9,
             text.font=1
      )

      par(font=1)

      dev.off()
  } # if print as pdf
  else { ####################################################################################################################################################
    #########################################################################################################################################################
    #########################################################################################################################################################
    #########################################################################################################################################################

    # install.packages('tikzDevice')
    library('tikzDevice')
    require('tikzDevice')
    library(tools)
    require(tools)

    filename = paste("plot", filename, sep="-")

    if(argument.standAlone == TRUE){
      tex_output_file <- paste(argument.output, filename, "-StandAlone", ".tex",sep = "")
      tikzDevice::tikz(tex_output_file,
                       width = 6.1,
                       height = 3.75,
                       pointsize=8,
                       standAlone=TRUE)
      #options( tikzLatexPackages = c("\\usepackage{xfrac}") )
    }else{
      tex_output_file <- paste(argument.output, filename, ".tex",sep = "")
      tikzDevice::tikz(tex_output_file,
                       width = 6.1,
                       height = 3.75,
                       pointsize=8,
                       standAlone=FALSE)
    }
    print(paste("File written to: ",getwd(),"/",tex_output_file, sep = ""))

    lfontsize = 1.0

    # create extra margin room on the right for an axis
    # mar=c(unten, links, oben, rechts)
    par(mar=c(4,5,3.5,5.3)+.1, mgp = c(4, 0.8, 0), xpd=TRUE)
    par(las=1, cex=lfontsize) # make label text perpendicular to axis

    leg = list()
    l_colim = c(seq(from=1,to=nrow(data),by=1))

    l_ylim=c(min(data$OptimumSolutions), max(data$OptimumSolutions))
    l_xlim=c(1, nrow(data))
    l_clim=c(min(data$BetweennessNormalizedValue), max(data$BetweennessNormalizedValue))

    leg = c("$\\mathsf{MPF}~|S|=1$", "Normalized~$\\mathsf{DTP}$bc")

    plot(l_colim,data$BetweennessNormalizedValue, type="l",
         xlab="",
         ylab="",
         ylim=l_clim,
         xlim=l_xlim,
         xaxt="n",
         yaxt="n",
         col=KITseablue30,
         lty=2,
         lwd=2
    )

    # add a title for the right axis
    axis(4,cex.axis=1)

    par(new=TRUE)

    plot(l_colim, data$OptimumSolutions,  type="l",
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
         lwd=2
    )

    #par(new=TRUE)

    # add a title for the left axis
    lab = seq(par("yaxp")[1], par("yaxp")[2], len = par("yaxp")[3])
    #axis(2, cex.axis=1, at=lab, labels=sprintf("%.2f", data$OptimumSolution))
    axis(2, las=2)

    par(new=TRUE)

    # plot max as point with x label
    plot(which.max(data$OptimumSolutions), max(data$OptimumSolutions), type="p",
         xlab="",
         ylab="",
         ylim=l_ylim,
         xlim=l_xlim,
         xaxt="n",
         yaxt="n",
         cex.axis=1,
         cex.lab=1,
         pch=16,
         lty=3,
         col=KITred50
    )
    offset_x = (l_xlim[2]-l_xlim[1]) * -8 / 100
    offset_y = (l_ylim[2]-l_ylim[1]) * -5 / 100
    text(which.max(data$OptimumSolutions)-offset_x, max(data$OptimumSolutions)+offset_y, labels = sprintf("%.2f", max(data$OptimumSolutions)), cex = 0.9, col = KITblack70)

    # add a title for the bottom axis
    lab = seq(par("xaxp")[1], par("xaxp")[2], len = par("xaxp")[3])
    axis(1,cex.axis=1, at=lab, labels=sprintf("%.0f", lab))
    # add x-axis label (bottom)
    mtext("Switched Edge", side=1, line=2, font=1, cex=0.95)

    par(las=0) # make label text perpendicular to axis
    # add y-axis label (left)
    mtext("$\\mathsf{MPF}$ in~$\\mathrm{MW}$",side=2, line=3.5, cex=0.95)
    # add z-axis label (right)
    mtext("Normalized~$\\mathsf{DTP}$ Betweenness Centrality",side=4, line=4.0, cex=0.95)

    # add legend
    scenario[[1]][4] = gsub('.{14}$', '', scenario[[1]][4])
    legendName = paste(scenario[[1]][2], scenario[[1]][3], scenario[[1]][4], sep="\\_")
    legendName = paste( "\\texttt{", legendName, "}", sep="")
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
    par(font=1)

    dev.off()

  } # else print as pdf

} # while files

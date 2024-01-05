#! /opt/local/bin/Rscript
#
# plot-maxst-vs-mtsf-violin-swarm.R
#
#   Created on: -
#       Author: Franziska Wegner
#
# This script computes the swarm plot in "The Maximum Transmission Switching
# Flow Problem", 2018, ACM e-Energy, doi:10.1145/3208903.3208910.
#

source("../Helper/plotting.R", chdir=T)
source("../Helper/colors.R", chdir=T)

# Arguments
args <- commandArgs(trailingOnly = TRUE)
argument.path          <- args[1]
argument.output        <- args[2]
argument.standAlone    <- args[3]

argument.latex_path    <- args[4]

if(is.na(argument.path)){
  argument.path        <- "/Users/fwegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/"
}
if(is.na(argument.output)){
  argument.output      <- "/Users/fwegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/plots/plot-maxst-vs-mtsf-violin-swarm.tex"
}
if(is.na(argument.standAlone)){
  argument.standAlone  <- FALSE
}

if(!is.na(argument.latex_path)){
  options(latexcmd     <- argument.latex_path)
}else{
  argument.latex_path  <- "/opt/local/bin/pdflatex"
  options(latexcmd     <- "/opt/local/bin/pdflatex")
}

# Extract data from file
data_dc_mtsf_gurobi          <- read.csv( paste( argument.path, "dc_mtsf_gurobi.csv",     sep = ""), header=TRUE, sep=",")
data_dc_mtsf_gurobi$path     <- NULL;
data_dc_maxst_mf_gurobi      <- read.csv( paste( argument.path, "dc_maxst_mf_gurobi.csv", sep = ""), header=TRUE, sep=",")
data_dc_maxst_mf_gurobi$path <- NULL;

# Format data
      data_dc_mtsf_gurobi$opt     <- as.numeric( format( round( data_dc_mtsf_gurobi$opt,     digits = 2), nsmall = 2) )
names(data_dc_mtsf_gurobi)        <- c("Name", "NumberOfVertices", "NumberOfEdges", "MtsfOptimumValue", "GenerationUpperBound", "MtsfNumberOfSwitchings")
      data_dc_maxst_mf_gurobi$opt <- as.numeric( format( round( data_dc_maxst_mf_gurobi$opt, digits = 2), nsmall = 2) )
names(data_dc_maxst_mf_gurobi)    <- c("Name", "NumberOfVertices", "NumberOfEdges", "MaxstOptimumValue", "GenerationUpperBound", "MaxstNumberOfSwitchings")

# Merge data
data <- NULL
data <- merge  ( data_dc_mtsf_gurobi, data_dc_maxst_mf_gurobi,
                 by   = c( "Name","NumberOfVertices", "NumberOfEdges","GenerationUpperBound" ),
                 type = "inner" )
data <- subset ( data, data$MtsfOptimumValue > 0 )

# Normalize using MTSF optimum value
data$MaxstOptimumValue <- data$MaxstOptimumValue / data$MtsfOptimumValue
data$Season            <- rep(0, nrow(data) )

# Plot as TIKZ
if ( argument.standAlone == TRUE ) {
     tex_output_file <- paste(argument.output, "-StandAlone", "",sep = "")
     tikzDevice::tikz( tex_output_file,
                       width      = 6.1,
                       height     = 3.75,
                       pointsize  = 8,
                       standAlone = TRUE )
} else {
     tex_output_file <- paste(argument.output, "",sep = "")
     tikzDevice::tikz( tex_output_file,
                       width      = 6.1,
                       height     = 3.75,
                       pointsize  = 8,
                       standAlone = FALSE )
}

# create extra margin room on the right for an axis
# mar=c(unten, links, oben, rechts)
par(mar=c(4.8,5,3.5,5.3)+.1, mgp = c(4, 0.8, 0), xpd=TRUE)
par(las=1, cex=1.2) # make label text perpendicular to axis

# Generate violin plot with jitter and other features
rectWorseHalfOpt <- data.frame(ymin=-Inf, ymax=0.5, xmin=-Inf, xmax=Inf)
rectBetterHalfOpt <- data.frame(ymin=0.5, ymax=Inf, xmin=-Inf, xmax=Inf)

g <- ggplot( data,
             aes(           x = Season,
                            y = MaxstOptimumValue
                )
    ) + geom_rect( data       = rectWorseHalfOpt,
                  aes(   xmin = xmin,
                         xmax = xmax,
                         ymin = ymin,
                         ymax = ymax
                     ),
                  color       = KITyellow15,
                  fill        = KITyellow15,
                  alpha       = 0.3,
                  inherit.aes = FALSE
    ) + geom_rect( data       = rectBetterHalfOpt,
                  aes(   xmin = xmin,
                         xmax = xmax,
                         ymin = ymin,
                         ymax = ymax
                     ),
                  color       = KITyellow15,
                  fill        = KITgreen15,
                  alpha       = 0.2,
                  inherit.aes = FALSE
    ) + geom_violin( alpha    = 0.5,
                     color    = KITseablue50,
                     fill     = KITseablue15,
                     trim     = FALSE
    # ) + geom_jitter(alpha=0.5,
    #                 aes(color=Season),
    #                 color = KITred,
    #                 position = position_jitter(width = 0.1)
    ) + geom_dotplot( #aes(color=Season),
                      binaxis  = 'y',
                      binwidth = 0.045,
                      stackdir = 'center',
                      dotsize  = 0.5,
                      color    = KITred30,
                      fill     = KITred50,
                      alpha    = 0.8
    ) + coord_flip(
    ) + annotate("text",     x = 0.5,
                             y = 0.225,#0.4
                         label = "\\bf Worse than~$\\frac{ \\mathsf{OPT}_{\\mathsf{MTSF}} }{ 2 }$", parse = FALSE, color = KITorange
    ) + annotate("text",     x = 0.5,
                             y = 0.775,
                         label = "\\bf Better than~$\\frac{ \\mathsf{ OPT }_{ \\mathsf{MTSF} } }{ 2 }$", parse = FALSE, color = KITgreen
    )

ticksHelper <- c(0,0.25,0.5,0.75,1)

g + labs(y = "Normalized flow value~$F(\\mathcal{N}, f)$~by~$\\mathsf{ OPT }_{ \\mathsf{MTSF} }$ in MW",
         x = "$\\mathsf{MaxST}$"
) + stat_summary(fun.data = mean_sdl,
                 fun.args = list(mult = 0.4),
                 geom     = "pointrange",
                 color    = KITgreen30,
                 size     = 0.5
) + stat_summary(fun.y    = median,
                 geom     = "point",
                 size     = 2.9,
                 color    = KITgreen30,
                 shape    = 18
) + theme_gray(base_size  = 14
) + theme(#axis.title.x   = element_blank(),
          axis.text.y     = element_blank(),
          axis.text.x     = element_text(size=13),
          axis.ticks.y    = element_blank(),
          axis.title.x    = element_text(margin = margin(t = 13.5, r = 0, b = 0, l = 0))
          # text = element_text(size=8)#,
          # axis.text.x = element_text(colour="grey20",size=20,angle=90,hjust=.5,vjust=.5,face="plain"),
          # axis.text.y = element_text(colour="grey20",size=12,angle=0,hjust=1,vjust=0,face="plain"),
          # axis.title.x = element_text(colour="grey20",size=12,angle=0,hjust=.5,vjust=0,face="plain"),
          # axis.title.y = element_text(colour="grey20",size=12,angle=90,hjust=.5,vjust=.5,face="plain")
          # axis.text.x = element_text(angle=90, hjust=1)
          # axis.ticks.x  = element_blank()
) + scale_y_continuous(breaks=ticksHelper
)

#+ ylim(-0.06,1.06)

print( paste("File written to: ", tex_output_file, sep = "") )

#par(font=1)

dev.off()

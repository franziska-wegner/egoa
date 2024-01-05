#! /opt/local/bin/Rscript
#
# plot_dtp_betweenness_centrality_all.R
#
#   Created on: -
#       Author: Franziska Wegner
#
# This script computes the DTP betweenness centrality plot with all cases 
# "The Maximum Transmission Switching Flow Problem", 2018, ACM e-Energy, 
# doi:10.1145/3208903.3208910.
#

# R include 
source("../Helper/plotting.R", chdir=T)
source("../Helper/colors.R", chdir=T)

## https://www.bioconductor.org/packages/release/bioc/html/BiSeq.html
## try http:// if https:// URLs are not supported
# source("https://bioconductor.org/biocLite.R")
# biocLite("BiSeq")
## Documentation
# browseVignettes("BiSeq")
library(BiSeq)
# require(BiSeq)

# Commandline arguments 
args                   <- commandArgs(trailingOnly = TRUE)
argument.path          <- args[1]
argument.output        <- args[2]
argument.standAlone    <- args[3]

argument.lowerQuantile <- args[4]
argument.avgQuantile   <- args[5]
argument.upperQuantile <- args[6]

argument.latex_path    <- args[7]

# Path to the data files
if ( is.na(argument.path) ) {
  argument.path       <- "/Users/fwegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/DTP-Betweenness/"
}

# Output path
if ( is.na(argument.output) ) {
  argument.output     <- "/Users/fwegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/plots/plot_dtp_betweenness_centrality_all_quantiles"
}

# Standalone
if ( is.na(argument.standAlone) ) {
  argument.standAlone <- FALSE
}
if ( argument.standAlone == "TRUE" ) {
  argument.standAlone <- TRUE
} else {
  argument.standAlone <- FALSE
}

if ( is.na(argument.lowerQuantile) ) {
  argument.lowerQuantile <- 0.32#0.31#0.32
}
if ( is.na(argument.avgQuantile) ) {
  argument.avgQuantile   <- 0.35#0.35#0.36
}
if ( is.na(argument.upperQuantile) ) {
  argument.upperQuantile <- 0.75
}

if ( !is.na(argument.latex_path) ) {
  options(latexcmd = argument.latex_path)
} else {
  argument.latex_path    <- "/opt/local/bin/pdflatex"
  options(latexcmd = "/opt/local/bin/pdflatex")
}

# Extract necessary files
files     <- NULL
files     <- list.files(path = argument.path, pattern = "\\-dtpbc-mpf.csv$")
files     <- files[files != ""]
filename  <- "DTP_BC-AllNestaCases_And_Quantiles"

lfontsize <- 1.0

totaldata = NULL

# ------- READING IN DATA FROM A CSV -------------------------------------------
while ( length(files) != 0 ) {
  # CSV access
  data   <- NULL
  data   <- read.csv(paste(argument.path, files[1], sep = ""), header=TRUE, sep=",")
  data   <- data[order(data$BetweennessNormalizedValue, decreasing = TRUE),]
  
  # Normalize opt of mpf -> y-axis
  data$OptimumSolutions <- data$OptimumSolutions / max(data$OptimumSolutions)
  
  # Add and normalize edge ids -> x-axis
  data$EdgeIndex       <- seq.int(nrow(data))
  data$EdgeIndex       <- data$EdgeIndex/data$NumberOfEdges
  
  # Next file in the list
  files[1]             <- ""
  files                <- files[files != ""]
  
  # Data frame of all data sets
  totaldata            <- rbind(totaldata,data)
} # while files

# ------- PROCESS DATA ---------------------------------------------------------

# Prepare data -> rounding, sorting and replace NA by 0 (not solvable instances)
totaldata$EdgeIndex        <- round( totaldata$EdgeIndex, digits = 2 )
totaldata                  <- totaldata[ order( totaldata$EdgeIndex, decreasing = FALSE), ]
totaldata$OptimumSolutions <- replace( totaldata$OptimumSolutions, is.na(totaldata$OptimumSolutions), 0 )

# Initialize
forSeq       <- c( seq(from=0,to=1,by=0.01) )
quantileData <- NULL
quantileData <- data.frame( matrix(ncol = 4, nrow = 0) )
# totaldata <- subset(totaldata, totaldata$OptimumSolutions > 0)

# Get quantiles for similar edge ids
for ( i in forSeq ) {
  subtotaldata <- subset(totaldata, EdgeIndex %in% c(i) )
  quantileData <-  rbind(quantileData, c( i, quantile(subtotaldata$OptimumSolutions, probs=c(argument.lowerQuantile, argument.avgQuantile, argument.upperQuantile), type=5) ))
}

# Postprocess quantile data
colnames(quantileData) <- c("EdgeIndex", "lowerQuantile", "avgQuantile", "upperQuantile")
quantileData           <- quantileData[complete.cases(quantileData), ]


library(stringr)
totaldata$Name <-  gsub("\t", "", totaldata$Name)
totaldata$Name <-  gsub("dc_mpf_nesta_case", "", totaldata$Name)
#totaldata$Name = paste( "\\\\tablecase\\{", str_pad(gsub("\\D*", "", totaldata$Name ), 4, pad = "0"),str_replace(totaldata$Name,"^.[0-9]*",""), "\\}" ,sep = "")
totaldata$Name <- paste( "\\\\tablecase\\{nestacase", str_pad(gsub("\\D*", "", totaldata$Name ), 4, pad = "0"), gsub("_", "", str_replace(totaldata$Name,"^.[0-9]*","") ), "\\}" ,sep = "")
totaldata$Name <-  gsub("_", "\\\\_",totaldata$Name)
totaldata      <- totaldata[ order(totaldata$NumberOfVertices, totaldata$EdgeIndex) , ]

# Sample the data set using sample(data, nr, replace = FALSE, prob = NULL)
# 10 % sample produced
# if(argument.sample == TRUE){

  totaldata[!duplicated(totaldata[,c('EdgeIndex', 'OptimumSolutions')]),]#EdgeIndex, OptimumSolutions
  #removed
  #noSamples   <- nrow(totaldata)/22#3#22#23
  #totaldata   <- filterBySharedRegions(object = totaldata, perc.samples = 1)
  #totaldata   <- totaldata[sample(nrow(totaldata), noSamples, replace = TRUE),] 
  
  #require(plotrix)
  #cluster.overplot(x,y)
  #plot(cluster.overplot(x, y ), main=”Using cluster.overplot”)
# }

# ------- PLOT DATA USING TIKZ -----------------------------------------------------

if ( argument.standAlone == TRUE ) { # Standalone tex
  tex_output_file <- paste(argument.output, "-standalone", ".tex",sep = "")
  tikzDevice::tikz(tex_output_file, 
                   width      = 6.1, 
                   height     = 3.75, 
                   pointsize  = 8, 
                   standAlone = TRUE)  
} else { # Tikz include graphic
  tex_output_file <- paste(argument.output, ".tex",sep = "")
  tikzDevice::tikz(tex_output_file, 
                   width      = 6.1, 
                   height     = 3.75, 
                   pointsize  = 8, 
                   standAlone = FALSE)
}

# create extra margin room on the right for an axis
# mar=c(unten, links, oben, rechts)
par(mar=c(4,5,3.5,5.3)+.1, mgp = c(4, 0.8, 0), xpd=TRUE)
par(las=1, cex=lfontsize) # make label text perpendicular to axis

g <- ggplot(  ) 
g + theme_gray(base_size      = 14
  ) + theme(legend.position   = "top", 
            axis.text.x       = element_text(size=13),
            axis.text.y       = element_text(size=13)
  # Vertical line at 0 to mark values with highest centrality
  ) +  geom_vline( xintercept = 0, 
                   color      = KITcyanblue70, 
                   size       = 2.2, 
                   alpha      = 0.7
  # Vertical line at 1 to mark values with lowest centrality
  ) +  geom_vline( xintercept = 1, 
                   color      = KITorange70,   
                   size       = 2.2, 
                   alpha      = 0.7
  # Plot background as lines
  # ) +   geom_line( aes(EdgeIndex, OptimumSolutions, column = Name), 
  #                  totaldata, 
  #                  colour = KITblack15
  # Plot background as points
  ) + geom_jitter(alpha    = 0.5, 
                  aes(EdgeIndex, OptimumSolutions), #, column = Name
                  totaldata,
                  color    = KITblack25, 
                  position = position_jitter(width = 0.01)
  # Coloring between the green curve and the blue one
  ) + geom_ribbon( data    = subset(quantileData, 0 <= quantileData$EdgeIndex & quantileData$EdgeIndex <= 1), 
                   aes( x    = EdgeIndex, 
                        ymin = lowerQuantile,
                        ymax = upperQuantile
                      ), 
                   fill    = KITgreen15, 
                   alpha   = "0.7"
  # Coloring between the red curve and the blue one
  ) + geom_ribbon( data    = subset(quantileData, 0 <= quantileData$EdgeIndex & quantileData$EdgeIndex <= 1), 
                   aes( x    = EdgeIndex, 
                        ymin = avgQuantile,
                        ymax = upperQuantile
                      ), 
                   fill    = KITred30, 
                   alpha   = "0.7"
  # 40 % quantile line
  ) +   geom_line( aes(EdgeIndex, lowerQuantile, col=paste(argument.lowerQuantile*100, "\\%~quantile", sep = "") ), 
                   quantileData, 
                   size    = 0.8
  # 45 % quantile line
  ) +   geom_line( aes(EdgeIndex, avgQuantile, col=paste(argument.avgQuantile*100, "\\%~quantile", sep = "") ), 
                   quantileData, 
                   size    = 0.8
  # 75 % quantile line
  ) +   geom_line( aes(EdgeIndex, upperQuantile, col=paste(argument.upperQuantile*100, "\\%~quantile", sep = "") ), 
                   quantileData, 
                   size    = 0.6
  # Colors used for the lines
  ) + scale_color_manual(values=c(KITgreen50, KITred50, KITseablue70, KITblack02, KITblack03, KITblack04, KITblack05, KITblack06, KITblack07, KITblack08, KITblack09, 
                                  KITblack10, KITblack11, KITblack12, KITblack13, KITblack14, KITblack15, KITblack16, KITblack17,KITblack18, KITblack19, KITblack20, 
                                  KITblack21, KITblack23, KITblack25, KITblack26, KITblack27, KITblack28, KITblack29, KITblack30, KITblack31, KITblack32)
  # Labels
  ) +        labs( x       = "Edges normalized by factor~$|E|$", 
                   y       = "Normalized~$\\mathsf{MPF}$ in~$\\mathrm{MW}$", 
                   color   = "NESTA Cases \\& Quantiles\n"
  ) +      guides( col     = guide_legend(title = NULL)
  # Text telling that "High c-DTPBC"
  ) + annotate("text", x   = 0.093, 
                       y   = 1.06,
               label       = "\\bf High $c_{\\mathsf{DTPBC}}$", 
               parse       = FALSE, 
               color       = KITcyanblue
  # Text telling that "Low c-DTPBC"
  ) + annotate("text", x   = 0.91, 
                       y   = 1.06,
               label       = "\\bf Low $c_{\\mathsf{DTPBC}}$", 
               parse       = FALSE, 
               color       = KITorange
  ) 

# Print output path
print(paste("File written to: ",tex_output_file, sep = ""))
par(font=1)
dev.off()



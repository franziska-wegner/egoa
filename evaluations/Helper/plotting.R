#! /opt/local/bin/Rscript
#
# plotting.R
#
#   Created on: 30.10.2018
#       Author: Franziska Wegner
#
# Necessary controller number per case.
#

require(lattice)
library(lattice)

#install.packages('plotrix', repos='http://cran.us.r-project.org')
library(plotrix)
require(plotrix)

# install.packages('Cairo')
# Necessary for saving as SVG or PDF
library(Cairo)
require(Cairo)


library(latex2exp)
require(latex2exp)

# install.packages('ggplot2')
library(ggplot2)
require(ggplot2)

# install.packages('tikzDevice')
library('tikzDevice')
require('tikzDevice')
library(tools)
require(tools)

# install.packages("rpart", "nnet", "cluster", "scales", "colorspace", "munsell", "scales", "ggplot2", "latticeExtras", "RColorBrewer", "survival", "Matrix", "lavaan", "Hmisc")
# install.packages("Hmisc")
library("Hmisc")

lfontsize           <- 1.0

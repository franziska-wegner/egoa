#! /opt/local/bin/Rscript
#
# table_models_algorithms.R
#
#   Created on: -
#       Author: Franziska Wegner
#
# This script computes the comparison table of PF, MPF, and MTSF models
# that are evaluated on the NESTA benchmark sets in the paper
# "The Maximum Transmission Switching Flow Problem", 2018, ACM e-Energy,
# doi:10.1145/3208903.3208910.
#

#system('defaults write org.R-project.R force.LANG en_US.UTF-8') #https://stackoverflow.com/questions/3907719/how-to-fix-tar-failed-to-set-default-locale-error
#install.packages("xtable")
require("xtable")
library(xtable)

# Commandline Arguments
args                   <- commandArgs(trailingOnly = TRUE)
argument.path          <- args[1]
argument.label         <- args[2]
argument.floating      <- args[3]
argument.short         <- args[4]
argument.caption       <- args[5]
argument.header        <- args[6]

if ( is.na(argument.path     ) ) {
  argument.path    <- "/Users/fwegner/Documents/work/paper/MTSF-ACM-e-Energy/02-ACM/data/results/"
}

if ( is.na( argument.short ) || (argument.short == "TRUE")  ) {
  argument.short     <- TRUE
} else {
  argument.short     <- FALSE
}

if ( is.na(argument.label  ) ) {
  if ( argument.short  ) {
    argument.label   <- "tbl:MTSF_MPF_PF_MF_short"
  } else {
    argument.label   <- "tbl:MTSF_MPF_PF_MF_long"
  }
}


if ( is.na(argument.caption) ) {
  if ( argument.short  ) {
    # argument.caption <- " The models~\\pfbf, \\mpfbf\\ and \\mtsfbf\\ from~\\cref{sec:model} are
    # evaluated on the NESTA benchmark sets~\\cite{DBLP:journals/corr/CoffrinGS14}.
    # The parameter~$\\bf n$, $\\bf m$ and~$\\bf |\\switched_{\\Pi}|$ represent the
    # number of vertices, edges and switched edges for a problem~$\\bf\\Pi$,
    # respectively, and the optimal solutions are given in~$\\optbf_{\\bf\\Pi}$.
    # %
    # The~\\colorbox{KITyellow15}{\\parbox[t][1.7mm]{9mm}{yellow}} rows mark the
    # interesting cases where~$\\optbf_{\\mpfbf}$ is smaller than
    # the~$\\optbf_{\\mtsfbf}$.
    # %
    # The highlighted cases are where the~$\\optbf_\\mtsfbf$ is smaller than
    # the~$\\optbf_\\mfbf$ (\\colorbox{KITblue15}{\\parbox[b][1.7mm]{6mm}{blue}}),
    # $\\optbf_\\maxstbf$ (see~\\cref{sec:approximation_algorithm_on_cacti})
    # and~$\\optbf_\\mpfbf$ are equal to~$\\optbf_\\mtsfbf$
    # (\\colorbox{KITblack!10}{\\parbox[b][1.7mm]{6mm} {gray}}), maximum possible
    # generation is greater than the~$\\optbf_\\mfbf$ (\\colorbox{KITred15}{\\parbox[b]
    # [1.7mm]{4.5mm}{red}}) and~$\\switched_\\maxstbf\\geq\\switched_\\mtsfbf$
    # (\\colorbox{KITgreen15}{\\parbox [b][1.7mm]{8mm}{green}}) (see all cases in~
    # \\cref{tbl:MTSF_MPF_PF_MF_long}).\n"

    argument.caption <- "The models~\\pfbf, \\mpfbf\\ and \\mtsfbf\\ from~\\cref{sec:model} are
    evaluated on the NESTA benchmark sets~\\cite{DBLP:journals/corr/CoffrinGS14}.
    The parameters~$\\bf n$, $\\bf m$ and~$\\bf |\\switched_{\\Pi}|$ represent the
    number of vertices, edges and switched edges for a problem~$\\bf\\Pi$,
    respectively, and the optimal solutions are given in~$\\optbf_{\\bf\\Pi}$.
    %
    The~\\colorbox{KITyellow15}{\\parbox[t][1.7mm]{9mm}{yellow}} rows mark the
    interesting cases where~$\\optbf_{\\mpfbf}$ is smaller than
    the~$\\optbf_{\\mtsfbf}$.
    %
    The highlighted cases are where the~$\\optbf_\\mtsfbf$ is smaller than
    the~$\\optbf_\\mfbf$ (\\colorbox{KITblue15}{\\parbox[b][1.7mm]{6mm}{blue}}),
    $\\optbf_\\maxstbf$ (see~\\cref{sec:approximation_algorithm_on_cacti})
    and~$\\optbf_\\mpfbf$ are equal to~$\\optbf_\\mtsfbf$
    (\\colorbox{KITblack!10}{\\parbox[b][1.7mm]{6mm} {gray}}), the maximum
    possible
    generation is greater than the~$\\optbf_\\mfbf$ (\\colorbox{KITred15}{\\parbox[b]
    [1.7mm]{4.5mm}{red}}) and~$|\\switched_\\maxstbf|\\geq|\\switched_\\mtsfbf|$
    (\\colorbox{KITgreen15}{\\parbox [b][1.7mm]{8mm}{green}}) (all cases see~
    \\cref{tbl:MTSF_MPF_PF_MF_long})."

    argument.header   <- "NESTA Case &\\hspace{-3mm} $n$ &\\hspace{-3mm} $m$ &\\hspace{-3mm} $|\\switched_{\\mtsf}|$ &\\hspace{-3mm} $|\\switched_{\\maxst}|$ &\\hspace{-3mm} $\\opt_{\\pf}$ &\\hspace{-3mm} $\\opt_{\\mpf}$ &\\hspace{-3mm} $\\opt_{\\mtsf}$ &\\hspace{-3mm} $\\opt_{\\maxst}$ &\\hspace{-3mm} $\\opt_{\\mf}$ &\\hspace{-3mm} $\\max$ Gen"

  } else {
    # argument.caption <- "The models~\\pfbf, \\mpfbf, \\mtsfbf\\ and \\otsbf\\ from~\\cref{sec:model} are
    # evaluated on the NESTA benchmark sets~\\cite{DBLP:journals/corr/CoffrinGS14}. The
    # parameter~$n$, $m$ and~$\\bf |\\switched_{\\Pi}|$ represent the number of vertices,
    # edges and switched edges for a problem~$\\bf\\Pi$, respectively, and the optimal
    # solutions are given in~$\\optbf_{\\bf\\Pi}$. Since~\\otsbf\\ minimizes the cost, the
    # flowvalue~$\\bf \\flowvaluebf_{\\otsbf}$ is shown, too. The maximum possible
    # generation is given in the last column
    # (marked~\\colorbox{KITred15}{\\parbox[t][1.7mm]{4.5mm}{red}} if it is larger than
    # the~$\\optbf_\\mfbf$).
    # %
    # The~\\colorbox{KITyellow15}{\\parbox[t][1.7mm]{9mm}{yellow}} rows mark the
    # interesting cases where~$\\optbf_{\\mpfbf}$ is smaller than the~$\\optbf_{\\mtsfbf}$.
    # However, the five cases in which the~$\\optbf_\\mtsfbf$ is smaller than
    # the~$\\optbf_\\mfbf$ are marked~\\colorbox{KITblue15}{\\parbox[b][1.7mm]
    # {6mm}{blue}}. The cases in which the~$\\optbf_\\maxstbf$
    # (see~\\cref{sec:approximation_algorithm_on_cacti}) and~$\\optbf_\\mpfbf$ are equal
    # to~$\\optbf_\\mtsfbf$ are marked~\\colorbox{KITblack!10}{\\parbox[b][1.7mm]{6mm}{gray}}.
    # In addition, there are three cases in which the number of switched lines in
    # the~$\\switched_\\maxstbf$ is greater than in the~$\\switched_\\mtsfbf$ shown
    # as~\\colorbox{KITgreen15}{\\parbox[b][1.7mm]{8mm}{green}}.\n"

    argument.caption <- "The models~\\pfbf, \\mpfbf, \\mtsfbf\\ and \\otsbf\\ from~\\cref{sec:model} are
    evaluated on the NESTA benchmark sets~\\cite{DBLP:journals/corr/CoffrinGS14}. The
    parameter~$n$, $m$ and~$\\bf |\\switched_{\\Pi}|$ represent the number of vertices,
    edges and switched edges for a problem~$\\bf\\Pi$, respectively, and the optimal
    solutions are given in~$\\optbf_{\\bf\\Pi}$. Since~\\otsbf\\ minimizes the cost, the
    flowvalue~$\\bf \\flowvaluebf_{\\otsbf}$ is shown, too. The maximum possible
    generation is given in the last column
    (marked~\\colorbox{KITred15}{\\parbox[t][1.7mm]{4.5mm}{red}} if it is larger than
    the~$\\optbf_\\mfbf$).
    %
    The~\\colorbox{KITyellow15}{\\parbox[t][1.7mm]{9mm}{yellow}} rows mark the
    interesting cases where~$\\optbf_{\\mpfbf}$ is smaller than the~$\\optbf_{\\mtsfbf}$.
    However, the five cases in which the~$\\optbf_\\mtsfbf$ is smaller than
    the~$\\optbf_\\mfbf$ are marked~\\colorbox{KITblue15}{\\parbox[b][1.7mm]
    {6mm}{blue}}. The cases in which the~$\\optbf_\\maxstbf$
    (see~\\cref{sec:approximation_algorithm_on_cacti}) and~$\\optbf_\\mpfbf$ are equal
    to~$\\optbf_\\mtsfbf$ are marked~\\colorbox{KITblack!10}{\\parbox[b][1.7mm]{6mm}{gray}}.
    In addition, there are three cases in which the number of switched lines in
    the~$\\switched_\\maxstbf$ is greater than in the~$\\switched_\\mtsfbf$ shown
    as~\\colorbox{KITgreen15}{\\parbox[b][1.7mm]{8mm}{green}}.\n"

    argument.header   <- "NESTA Case &\\hspace{-3mm} $n$ &\\hspace{-3mm} $m$ &\\hspace{-3mm} $|\\switched_{\\mtsf}|$ &\\hspace{-3mm} $|\\switched_{\\ots}|$ &\\hspace{-3mm} $|\\switched_{\\maxst}|$ &\\hspace{-3mm} $\\opt_{\\ots}$ in \\$ &\\hspace{-3mm} $\\flowvalue_{\\ots}$ &\\hspace{-3mm} $\\opt_{\\pf}$ &\\hspace{-3mm} $\\opt_{\\mpf}$ &\\hspace{-3mm} $\\opt_{\\mtsf}$ &\\hspace{-3mm} $\\opt_{\\maxst}$ &\\hspace{-3mm} $\\opt_{\\mf}$ &\\hspace{-3mm} $\\max$ Gen"
  }
}

if ( is.na( argument.floating ) || ( argument.floating == "FALSE" ) ) {
  argument.floating <- FALSE
} else {
  argument.floating <- TRUE
}

files         <- NULL
cc_latex_data <- NULL

# Extract necessary files
data_dc_mf_gurobi       <- read.csv(paste(argument.path, "dc_mf_gurobi.csv",       sep = ""), header=TRUE, sep=",")
data_dc_mpf_gurobi      <- read.csv(paste(argument.path, "dc_mpf_gurobi.csv",      sep = ""), header=TRUE, sep=",")
data_dc_pf_gurobi       <- read.csv(paste(argument.path, "dc_pf_gurobi.csv",       sep = ""), header=TRUE, sep=",")
data_dc_mtsf_gurobi     <- read.csv(paste(argument.path, "dc_mtsf_gurobi.csv",     sep = ""), header=TRUE, sep=",")
data_dc_ots_gurobi      <- read.csv(paste(argument.path, "dc_ots_gurobi.csv",      sep = ""), header=TRUE, sep=",")
data_dc_maxst_mf_gurobi <- read.csv(paste(argument.path, "dc_maxst_mf_gurobi.csv", sep = ""), header=TRUE, sep=",")

      data_dc_mf_gurobi$path   <- NULL;
      data_dc_mf_gurobi$status <- NULL;
     data_dc_mpf_gurobi$path   <- NULL;
     data_dc_mpf_gurobi$status <- NULL;
      data_dc_pf_gurobi$path   <- NULL;
      data_dc_pf_gurobi$status <- NULL;
    data_dc_mtsf_gurobi$path   <- NULL;
     data_dc_ots_gurobi$path   <- NULL;
data_dc_maxst_mf_gurobi$path   <- NULL;

big_number_mark                <- "\\\\,"
data_dc_pf_gurobi$opt          <- format(round(data_dc_pf_gurobi$opt, digits = 2), nsmall = 2, big.mark=big_number_mark)
names(data_dc_pf_gurobi)       <- c("case", "n", "m", "OPT_PF", "MaxGen")
data_dc_mpf_gurobi$opt         <- format(round(data_dc_mpf_gurobi$opt, digits = 2), nsmall = 2, big.mark=big_number_mark)
names(data_dc_mpf_gurobi)      <- c("case", "n", "m", "OPT_MPF", "MaxGen")
data_dc_mtsf_gurobi$opt        <- format(round(data_dc_mtsf_gurobi$opt, digits = 2), nsmall = 2, big.mark=big_number_mark)
names(data_dc_mtsf_gurobi)     <- c("case", "n", "m", "OPT_MTSF", "MaxGen", "S_MTSF")
data_dc_mf_gurobi$opt          <- format(round(data_dc_mf_gurobi$opt, digits = 2), nsmall = 2, big.mark=big_number_mark)
names(data_dc_mf_gurobi)       <- c("case", "n", "m", "OPT_MF", "MaxGen")
data_dc_ots_gurobi$opt         <- format(round(data_dc_ots_gurobi$opt, digits = 2), nsmall = 2, big.mark=big_number_mark)
names(data_dc_ots_gurobi)      <- c("case", "n", "m", "OPF_OTS", "OPT_OTS", "MaxGen", "S_OTS")
data_dc_maxst_mf_gurobi$opt    <- format(round(data_dc_maxst_mf_gurobi$opt, digits = 2), nsmall = 2, big.mark=big_number_mark)
names(data_dc_maxst_mf_gurobi) <- c("case", "n", "m", "OPT_MAXST", "MaxGen", "S_MAXST")

# Join (using inner join) all data sets into one table
data2 <- NULL
data2 <- merge(data_dc_pf_gurobi, data_dc_mpf_gurobi,      by=c("case","n", "m","MaxGen"), type="inner")
data2 <- merge(data2,             data_dc_mtsf_gurobi,     by=c("case","n", "m","MaxGen"), type="inner")
data2 <- merge(data2,             data_dc_mf_gurobi,       by=c("case","n", "m","MaxGen"), type="inner")
data2 <- merge(data2,             data_dc_ots_gurobi,      by=c("case","n", "m","MaxGen"), type="inner")
data2 <- merge(data2,             data_dc_maxst_mf_gurobi, by=c("case","n", "m","MaxGen"), type="inner")

# Formating the whole table
data2$MaxGen <- format(round(data2$MaxGen, digits = 2), nsmall = 2, big.mark=big_number_mark)
data2        <- data2[, c(1:3, 8, 12, 14, 10, 11, 5:7, 13, 9, 4)] # Change order of the columns
data2        <- data2[order(data2$n),                           ] # Sort data set by n increasing
data2$case   <- gsub("_", "",  as.character(factor(data2$case)) ) # Remove "_"
data2$case   <-  sub("^", "\\\\tablecase{",        data2$case   ) # Adding \tablecase to the front of the string
data2$case   <- gsub(" ", "",  as.character(factor(data2$case)) ) # Removing whitespaces
data2$case   <- gsub("$", "}", as.character(factor(data2$case)) ) # Adding } at the end of the string

# Remove some selected data, which do not really give more information, but are for completness of the data set
if ( argument.short ) {
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase4gs}"        )
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase5pjm}"       )
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase6c}"         )
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase14ieee}"     )
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase30fsr}"      )
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase30ieee}"     )
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase89pegase}"   )
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase118ieee}"    )
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase162ieeedtc}" )
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase2383wpmp}"   )
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase2746wopmp}"  )
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase2746wpmp}"   )
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase3012wpmp}"   )
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase3375wpmp}"   )
  data2$OPF_OTS <- NULL
  data2$OPT_OTS <- NULL
  data2$S_OTS   <- NULL
} else {
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase2383wpmp}"   )
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase3012wpmp}"   )
  data2 <- subset ( data2, data2$case != "\\tablecase{nestacase3375wpmp}"   )
}

# Create latex table
latextable                                 <- NULL
latextable                                 <- xtable(data2, label=argument.label, caption=argument.caption)

if (!argument.short) {
  # Replace zero by "---" TODO: make it more general! This is very bad!!!
  latextable[latextable=="       0.00"     ] <- "---"
  latextable[latextable=="            0.00"] <- "---"
  latextable[latextable=="0.00"            ] <- "---"
  latextable[latextable=="0"               ] <- "---"
  latextable[latextable=="  0"             ] <- "---"

  # Replace some stuff TODO: super bad
  # latextable[data2$S_MTSF  == data2$m, ]$S_MTSF  <- "---"
  latextable[data2$S_MTSF  == 0,       ]$S_MTSF  <- "0"


  # latextable[data2$S_MAXST == 0,       ]$S_MAXST <- "0"

  latextable[data2$S_OTS   == 0,       ]$S_OTS   <- "0"
  latextable[data2$OPT_OTS == 0,       ]$S_OTS   <- "---"
}
# Add cell color or color for some scenarios using \cellcolor{color} or \rowcolor{color}
## OPT_MPF < OPT_MTSF:    color row in KITyellow
latextable[data2$OPT_MPF   < data2$OPT_MTSF, ]$case      <- sub("^", "\\\\rowcolor{KITyellow15}",    latextable[data2$OPT_MPF   < data2$OPT_MTSF, ]$case      )
## OPT_MTSF < OPT_MF:     color both cells in KITcyanblue
latextable[data2$OPT_MTSF  < data2$OPT_MF,   ]$OPT_MTSF  <- sub("^", "\\\\cellcolor{KITcyanblue15}", latextable[data2$OPT_MTSF  < data2$OPT_MF,   ]$OPT_MTSF  )
latextable[data2$OPT_MTSF  < data2$OPT_MF,   ]$OPT_MF    <- sub("^", "\\\\cellcolor{KITcyanblue15}", latextable[data2$OPT_MTSF  < data2$OPT_MF,   ]$OPT_MF    )
## S_MTSF < S_MAXST:      color both cells in KITgreen15
latextable[data2$S_MTSF    < data2$S_MAXST,  ]$S_MTSF    <- sub("^", "\\\\cellcolor{KITgreen15}",    latextable[data2$S_MTSF    < data2$S_MAXST,  ]$S_MTSF    )
latextable[data2$S_MTSF    < data2$S_MAXST,  ]$S_MAXST   <- sub("^", "\\\\cellcolor{KITgreen15}",    latextable[data2$S_MTSF    < data2$S_MAXST,  ]$S_MAXST   )
## OPT_MF < MaxGen:       color MaxGen cell in KITred15
latextable[data2$OPT_MF    < data2$MaxGen,   ]$MaxGen    <- sub("^", "\\\\cellcolor{KITred15}",      latextable[data2$OPT_MF    < data2$MaxGen,   ]$MaxGen    )
## OPT_MTSF == OPT_MAXST: color OPT_MAXST cell in KITblack!10
latextable[data2$OPT_MTSF == data2$OPT_MAXST,]$OPT_MAXST <- sub("^", "\\\\cellcolor{KITblack!10}",   latextable[data2$OPT_MTSF == data2$OPT_MAXST,]$OPT_MAXST )
## OPT_MTSF == OPT_MPF:   color OPT_MPF cell in KITblack!10
latextable[data2$OPT_MTSF == data2$OPT_MPF,  ]$OPT_MPF   <- sub("^", "\\\\cellcolor{KITblack!10}",   latextable[data2$OPT_MTSF == data2$OPT_MPF,  ]$OPT_MPF   )

# Write out Latex table with options
if ( !argument.short ) {
  align(latextable) <- "llrrrrrrrrrrrrr"
} else {
  align(latextable) <- "llrrrrrrrrrr"
}
addtorow          <- list()
addtorow$pos      <- list(0)
addtorow$command  <- c(paste(argument.header," \\\\\n", sep = ""))
print(latextable,
      add.to.row           = addtorow,
      include.rownames     = FALSE,
      include.colnames     = FALSE,
      table.placement      = "tb!",
      booktabs             = TRUE,
      caption.placement    = "top",
      floating             = argument.floating,
      floating.environment = getOption("xtable.floating.environment", "table*"   ),
      latex.environments   = getOption("xtable.latex.environments",   c("center")),
      size                 = getOption("xtable.size",                 "\n\\small\n\\setlength{\\tabcolsep}{4pt}\n% \\setlength\\minrowclearance{3pt}")
      )# floating=FALSE for without table environment

#! /opt/local/bin/Rscript
#
# colors.R
# 
#   Created on: 30.10.2018
#       Author: Franziska Wegner
#       
# Add color definition of KITcolors, Thesis colors, and others.
# 

# install.packages("lubridate")
library(lubridate)
#theme_set(theme_bw())

# install.packages("RColorBrewer")
library(RColorBrewer)
require(RColorBrewer)

display.brewer.all()

LipicsYellow        <- rgb(0.99  , 0.78 , 0.07 )

# KITgreen
KITgreen            <- rgb(0    , 0.588, 0.509)
KITgreen70          <- rgb(0.3  , 0.711, 0.656)
KITgreen50          <- rgb(0.5  , 0.794, 0.754)
KITgreen30          <- rgb(0.7  , 0.876, 0.852)
KITgreen15          <- rgb(0.85 , 0.938, 0.926)
# KITblue
KITblue             <- rgb(0.274, 0.392, 0.666)
KITblue70           <- rgb(0.492, 0.574, 0.766)
KITblue50           <- rgb(0.637, 0.696, 0.833)
KITblue30           <- rgb(0.782, 0.817, 0.9  )
KITblue15           <- rgb(0.891, 0.908, 0.95 )
# KITblack
KITblack            <- rgb(0    , 0    , 0    )
KITblack70          <- rgb(0.3  , 0.3  , 0.3  )
KITblack50          <- rgb(0.5  , 0.5  , 0.5  )
KITblack32          <- rgb(0.7  , 0.7  , 0.7  )
KITblack31          <- rgb(0.7  , 0.7  , 0.7  )
KITblack30          <- rgb(0.7  , 0.7  , 0.7  )
KITblack29          <- rgb(0.71 , 0.71 , 0.71 )
KITblack28          <- rgb(0.72 , 0.72 , 0.72 )
KITblack27          <- rgb(0.73 , 0.73 , 0.73 )
KITblack26          <- rgb(0.74 , 0.74 , 0.74 )
KITblack25          <- rgb(0.75 , 0.75 , 0.75 )
KITblack24          <- rgb(0.76 , 0.76 , 0.76 )
KITblack23          <- rgb(0.77 , 0.77 , 0.77 )
KITblack22          <- rgb(0.78 , 0.78 , 0.78 )
KITblack21          <- rgb(0.79 , 0.79 , 0.79 )
KITblack20          <- rgb(0.80 , 0.80 , 0.80 )
KITblack19          <- rgb(0.81 , 0.81 , 0.81 )
KITblack18          <- rgb(0.82 , 0.82 , 0.82 )
KITblack17          <- rgb(0.83 , 0.83 , 0.83 )
KITblack16          <- rgb(0.84 , 0.84 , 0.84 )
KITblack15          <- rgb(0.85 , 0.85 , 0.85 )
KITblack14          <- rgb(0.86 , 0.86 , 0.86 )
KITblack13          <- rgb(0.87 , 0.87 , 0.87 )
KITblack12          <- rgb(0.88 , 0.88 , 0.88 )
KITblack11          <- rgb(0.89 , 0.89 , 0.89 )
KITblack10          <- rgb(0.90 , 0.90 , 0.90 )
KITblack09          <- rgb(0.91 , 0.91 , 0.91 )
KITblack08          <- rgb(0.92 , 0.92 , 0.92 )
KITblack07          <- rgb(0.93 , 0.93 , 0.93 )
KITblack06          <- rgb(0.94 , 0.94 , 0.94 )
KITblack05          <- rgb(0.95 , 0.95 , 0.95 )
KITblack04          <- rgb(0.96 , 0.96 , 0.96 )
KITblack03          <- rgb(0.97 , 0.97 , 0.97 )
KITblack02          <- rgb(0.98 , 0.98 , 0.98 )
KITblack01          <- rgb(0.99 , 0.99 , 0.99 )
# KITpalegreen
KITpalegreen        <- rgb(0.509, 0.745, 0.235)
KITpalegreen70      <- rgb(0.656, 0.821, 0.464)
KITpalegreen50      <- rgb(0.754, 0.872, 0.617)
KITpalegreen30      <- rgb(0.852, 0.923, 0.77 )
KITpalegreen15      <- rgb(0.926, 0.961, 0.885)
# KITyellow
KITyellow           <- rgb(0.98 , 0.901, 0.078)
KITyellow70         <- rgb(0.986, 0.931, 0.354)
KITyellow50         <- rgb(0.99 , 0.95 , 0.539)
KITyellow30         <- rgb(0.994, 0.97 , 0.723)
KITyellow15         <- rgb(0.997, 0.985, 0.861)
# KITorange
KITorange           <- rgb(0.862, 0.627, 0.117)
KITorange70         <- rgb(0.903, 0.739, 0.382)
KITorange50         <- rgb(0.931, 0.813, 0.558)
KITorange30         <- rgb(0.958, 0.888, 0.735)
KITorange15         <- rgb(0.979, 0.944, 0.867)
# KITbrown
KITbrown            <- rgb(0.627, 0.509, 0.196)
KITbrown70          <- rgb(0.739, 0.656, 0.437)
KITbrown50          <- rgb(0.813, 0.754, 0.598)
KITbrown30          <- rgb(0.888, 0.852, 0.758)
KITbrown15          <- rgb(0.944, 0.926, 0.879)
# KITred
KITred              <- rgb(0.627, 0.117, 0.156)
KITred70            <- rgb(0.739, 0.382, 0.409)
KITred50            <- rgb(0.813, 0.558, 0.578)
KITred30            <- rgb(0.888, 0.735, 0.747)
KITred15            <- rgb(0.944, 0.867, 0.873)
# KITlilac
KITlilac            <- rgb(0.627, 0    , 0.47 )
KITlilac70          <- rgb(0.739, 0.3  , 0.629)
KITlilac50          <- rgb(0.813, 0.5  , 0.735)
KITlilac30          <- rgb(0.888, 0.7  , 0.841)
KITlilac15          <- rgb(0.944, 0.85 , 0.92 )
# KITcyanblue
KITcyanblue         <- rgb(0.313, 0.666, 0.901)
KITcyanblue70       <- rgb(0.519, 0.766, 0.931)
KITcyanblue50       <- rgb(0.656, 0.833, 0.95 )
KITcyanblue30       <- rgb(0.794, 0.9  , 0.97 )
KITcyanblue15       <- rgb(0.897, 0.95 , 0.985)
# KITseablue
KITseablue          <- rgb(0.196, 0.313, 0.549)
KITseablue70        <- rgb(0.437, 0.519, 0.684)
KITseablue50        <- rgb(0.598, 0.656, 0.774)
KITseablue30        <- rgb(0.758, 0.794, 0.864)
KITseablue15        <- rgb(0.879, 0.897, 0.932)

# Thesis Colors.
THESISblue          <- rgb(0.337, 0.592, 0.773)
THESISblue_dark     <- rgb(0.212, 0.471, 0.655)
THESISblue_light    <- rgb(0.490, 0.710, 0.867)
THESISblue_vlight   <- rgb(0.871, 0.937, 0.988)

THESISred           <- rgb(0.776, 0.357, 0.396)
THESISred_dark      <- rgb(0.663, 0.235, 0.271)
THESISred_light     <- rgb(0.867, 0.502, 0.533)
THESISred_vlight    <- rgb(0.984, 0.871, 0.878)

THESISgreen         <- rgb(0.337, 0.765, 0.235)
THESISgreen_dark    <- rgb(0.267, 0.612, 0.184)
THESISgreen_light   <- rgb(0.443, 0.871, 0.341)
THESISgreen_vlight  <- rgb(0.710, 0.984, 0.643)

THESISyellow        <- rgb(0.808, 0.659, 0.263)
THESISyellow_dark   <- rgb(0.667, 0.529, 0.180)
THESISyellow_light  <- rgb(0.898, 0.765, 0.412)
THESISyellow_vlight <- rgb(0.992, 0.933, 0.776)

THESISblack         <- rgb(0,0,0)
THESISblack70       <- rgb(0.30,0.30,0.30)
THESISblack50       <- rgb(0.50,0.50,0.50)
THESISblack30       <- rgb(0.70,0.70,0.70)
THESISblack15       <- rgb(0.85,0.85,0.85)
THESISblack7        <- rgb(0.92,0.92,0.92)

KITcolors           <- c(KITblack,   KITseablue,   KITblue,   KITcyanblue,   KITgreen,   KITpalegreen,   KITred,   KITlilac,   KITyellow,   KITorange,   KITbrown);
KITcolors70         <- c(KITblack70, KITseablue70, KITblue70, KITcyanblue70, KITgreen70, KITpalegreen70, KITred70, KITlilac70, KITyellow70, KITorange70, KITbrown70);
KITcolors50         <- c(KITblack50, KITseablue50, KITblue50, KITcyanblue50, KITgreen50, KITpalegreen50, KITred50, KITlilac50, KITyellow50, KITorange50, KITbrown50);
KITcolors30         <- c(KITblack30, KITseablue30, KITblue30, KITcyanblue30, KITgreen30, KITpalegreen30, KITred30, KITlilac30, KITyellow30, KITorange30, KITbrown30);
KITcolors15         <- c(KITblack15, KITseablue15, KITblue15, KITcyanblue15, KITgreen15, KITpalegreen15, KITred15, KITlilac15, KITyellow15, KITorange15, KITbrown15);


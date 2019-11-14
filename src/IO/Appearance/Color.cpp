#include "IO/Appearance/Color.hpp"
#include <sstream>
#include <iomanip>

namespace egoa {

    Types::ubyte RGB[][3] = {
        // KITgreen
          {   0, 150, 130 }  // KITgreen
        , {  77, 181, 167 }  // KITgreen70
        , { 128, 202, 192 }  // KITgreen50
        , { 179, 223, 217 }  // KITgreen30
        , { 217, 239, 236 }  // KITgreen15
        // KITblue
        , {  70, 100, 170 }  // KITblue
        , { 125, 146, 195 }  // KITblue70
        , { 162, 177, 212 }  // KITblue50
        , { 199, 208, 230 }  // KITblue30
        , { 227, 232, 242 }  // KITblue15
        // KITblack
        , {   0,   0,   0 }  // KITblack
        , {  77,  77,  77 }  // KITblack70
        , { 128, 128, 128 }  // KITblack50
        , { 179, 179, 179 }  // KITblack32
        , { 179, 179, 179 }  // KITblack31
        , { 179, 179, 179 }  // KITblack30
        , { 181, 181, 181 }  // KITblack29
        , { 184, 184, 184 }  // KITblack28
        , { 186, 186, 186 }  // KITblack27
        , { 189, 189, 189 }  // KITblack26
        , { 191, 191, 191 }  // KITblack25
        , { 194, 194, 194 }  // KITblack24
        , { 196, 196, 196 }  // KITblack23
        , { 199, 199, 199 }  // KITblack22
        , { 201, 201, 201 }  // KITblack21
        , { 204, 204, 204 }  // KITblack20
        , { 207, 207, 207 }  // KITblack19
        , { 209, 209, 209 }  // KITblack18
        , { 212, 212, 212 }  // KITblack17
        , { 214, 214, 214 }  // KITblack16
        , { 217, 217, 217 }  // KITblack15
        , { 219, 219, 219 }  // KITblack14
        , { 222, 222, 222 }  // KITblack13
        , { 224, 224, 224 }  // KITblack12
        , { 227, 227, 227 }  // KITblack11
        , { 230, 230, 230 }  // KITblack10
        , { 232, 232, 232 }  // KITblack09
        , { 235, 235, 235 }  // KITblack08
        , { 237, 237, 237 }  // KITblack07
        , { 240, 240, 240 }  // KITblack06
        , { 242, 242, 242 }  // KITblack05
        , { 245, 245, 245 }  // KITblack04
        , { 247, 247, 247 }  // KITblack03
        , { 250, 250, 250 }  // KITblack02
        , { 252, 252, 252 }  // KITblack01
        // KITpalegreen
        , { 130, 190,  60 }  // KITpalegreen
        , { 167, 209, 118 }  // KITpalegreen70
        , { 192, 222, 157 }  // KITpalegreen50
        , { 217, 235, 196 }  // KITpalegreen30
        , { 236, 245, 226 }  // KITpalegreen15
        // KITyellow
        , { 250, 230,  20 }  // KITyellow
        , { 251, 237,  90 }  // KITyellow70
        , { 252, 242, 137 }  // KITyellow50
        , { 253, 247, 184 }  // KITyellow30
        , { 254, 251, 220 }  // KITyellow15
        // KITorange
        , { 220, 160,  30 }  // KITorange
        , { 230, 188,  97 }  // KITorange70
        , { 237, 207, 142 }  // KITorange50
        , { 244, 226, 187 }  // KITorange30
        , { 250, 241, 221 }  // KITorange15
        // KITbrown
        , { 160, 130,  50 }  // KITbrown
        , { 188, 167, 111 }  // KITbrown70
        , { 207, 192, 152 }  // KITbrown50
        , { 226, 217, 193 }  // KITbrown30
        , { 241, 236, 224 }  // KITbrown15
        // KITred
        , { 160,  30,  40 }  // KITred
        , { 188,  97, 104 }  // KITred70
        , { 207, 142, 147 }  // KITred50
        , { 226, 187, 190 }  // KITred30
        , { 241, 221, 223 }  // KITred15
        // KITlilac
        , { 160,   0, 120 }  // KITlilac
        , { 188,  77, 160 }  // KITlilac70
        , { 207, 128, 187 }  // KITlilac50
        , { 226, 179, 214 }  // KITlilac30
        , { 241, 217, 235 }  // KITlilac15
        // KITcyanblue
        , {  80, 170, 230 }  // KITcyanblue
        , { 132, 195, 237 }  // KITcyanblue70
        , { 167, 212, 242 }  // KITcyanblue50
        , { 202, 230, 247 }  // KITcyanblue30
        , { 229, 242, 251 }  // KITcyanblue15
        // KITseablue
        , {  50,  80, 140 }  // KITseablue
        , { 111, 132, 174 }  // KITseablue70
        , { 152, 167, 197 }  // KITseablue50
        , { 193, 202, 220 }  // KITseablue30
        , { 224, 229, 238 }  // KITseablue15
        // 
        // Thesis Colors
        , {  86, 151, 197 }  // THESISblue
        , {  54, 120, 167 }  // THESISblue_dark
        , { 125, 181, 221 }  // THESISblue_light
        , { 222, 239, 252 }  // THESISblue_vlight
        //
        , { 198,  91, 101 }  // THESISred
        , { 169,  60,  69 }  // THESISred_dark
        , { 221, 128, 136 }  // THESISred_light
        , { 251, 222, 224 }  // THESISred_vlight
        //
        , {  86, 195,  60 }  // THESISgreen
        , {  68, 156,  47 }  // THESISgreen_dark
        , { 112, 222,  87 }  // THESISgreen_light
        , { 181, 251, 164 }  // THESISgreen_vlight
        //
        , { 206, 168,  67 }  // THESISyellow
        , { 170, 135,  46 }  // THESISyellow_dark
        , { 229, 195, 105 }  // THESISyellow_light
        , { 253, 238, 198 }  // THESISyellow_vlight
        //
        , {   0,   0,   0 }  // THESISblack
        , {  77,  77,  77 }  // THESISblack70
        , { 128, 128, 128 }  // THESISblack50
        , { 179, 179, 179 }  // THESISblack30
        , { 217, 217, 217 }  // THESISblack15
        , { 235, 235, 235 }  // THESISblack7
        // OGDF
        , { 218, 165,  32 }  // Goldenrod
        , { 128, 128, 128 }  // Gray
        , {   0, 128,   0 }  // Green
        , { 173, 255,  47 }  // Greenyellow
        , { 128, 128, 128 }  // Grey
        , { 240, 255, 240 }  // Honeydew
        , { 255, 105, 180 }  // Hotpink
        , { 205,  92,  92 }  // Indianred
        , {  75,   0, 130 }  // Indigo
        , { 255, 255, 240 }  // Ivory
        , { 240, 230, 140 }  // Khaki
        , { 230, 230, 250 }  // Lavender
        , { 255, 240, 245 }  // Lavenderblush
        , { 124, 252,   0 }  // Lawngreen
        , { 255, 250, 205 }  // Lemonchiffon
        , { 173, 216, 230 }  // Lightblue
        , { 240, 128, 128 }  // Lightcoral
        , { 224, 255, 255 }  // Lightcyan
        , { 250, 250, 210 }  // Lightgoldenrodyellow
        , { 211, 211, 211 }  // Lightgray
        , { 144, 238, 144 }  // Lightgreen
        , { 211, 211, 211 }  // Lightgrey
        , { 255, 182, 193 }  // Lightpink
        , { 255, 160, 122 }  // Lightsalmon
        , {  32, 178, 170 }  // Lightseagreen
        , { 135, 206, 250 }  // Lightskyblue
        , { 119, 136, 153 }  // Lightslategray
        , { 119, 136, 153 }  // Lightslategrey
        , { 176, 196, 222 }  // Lightsteelblue
        , { 255, 255, 224 }  // Lightyellow
        , {   0, 255,   0 }  // Lime
        , {  50, 205,  50 }  // Limegreen
        , { 250, 240, 230 }  // Linen
        , { 255,   0, 255 }  // Magenta
        , { 128,   0,   0 }  // Maroon
        , { 102, 205, 170 }  // Mediumaquamarine
        , {   0,   0, 205 }  // Mediumblue
        , { 186,  85, 211 }  // Mediumorchid
        , { 147, 112, 219 }  // Mediumpurple
        , {  60, 179, 113 }  // Mediumseagreen
        , { 123, 104, 238 }  // Mediumslateblue
        , {   0, 250, 154 }  // Mediumspringgreen
        , {  72, 209, 204 }  // Mediumturquoise
        , { 199,  21, 133 }  // Mediumvioletred
        , {  25,  25, 112 }  // Midnightblue
        , { 245, 255, 250 }  // Mintcream
        , { 255, 228, 225 }  // Mistyrose
        , { 255, 228, 181 }  // Moccasin
        , { 255, 222, 173 }  // Navajowhite
        , {   0,   0, 128 }  // Navy
        , { 253, 245, 230 }  // Oldlace
        , { 128, 128,   0 }  // Olive
        , { 107, 142,  35 }  // Olivedrab
        , { 255, 165,   0 }  // Orange
        , { 255,  69,   0 }  // Orangered
        , { 218, 112, 214 }  // Orchid
        , { 238, 232, 170 }  // Palegoldenrod
        , { 152, 251, 152 }  // Palegreen
        , { 175, 238, 238 }  // Paleturquoise
        , { 219, 112, 147 }  // Palevioletred
        , { 255, 239, 213 }  // Papayawhip
        , { 255, 218, 185 }  // Peachpuff
        , { 205, 133,  63 }  // Peru
        , { 255, 192, 203 }  // Pink
        , { 221, 160, 221 }  // Plum
        , { 176, 224, 230 }  // Powderblue
        , { 128,   0, 128 }  // Purple
        , { 255,   0,   0 }  // Red
        , { 188, 143, 143 }  // Rosybrown
        , {  65, 105, 225 }  // Royalblue
        , { 139,  69,  19 }  // Saddlebrown
        , { 250, 128, 114 }  // Salmon
        , { 244, 164,  96 }  // Sandybrown
        , {  46, 139,  87 }  // Seagreen
        , { 255, 245, 238 }  // Seashell
        , { 160,  82,  45 }  // Sienna
        , { 192, 192, 192 }  // Silver
        , { 135, 206, 235 }  // Skyblue
        , { 106,  90, 205 }  // Slateblue
        , { 112, 128, 144 }  // Slategray
        , { 112, 128, 144 }  // Slategrey
        , { 255, 250, 250 }  // Snow
        , {   0, 255, 127 }  // Springgreen
        , {  70, 130, 180 }  // Steelblue
        , { 210, 180, 140 }  // Tan
        , {   0, 128, 128 }  // Teal
        , { 216, 191, 216 }  // Thistle
        , { 255,  99,  71 }  // Tomato
        , {  64, 224, 208 }  // Turquoise
        , { 238, 130, 238 }  // Violet
        , { 245, 222, 179 }  // Wheat
        , { 255, 255, 255 }  // White
        , { 245, 245, 245 }  // Whitesmoke
        , { 255, 255,   0 } // Yellow
        , { 154, 205,  50 } // Yellowgreen
    };

    Types::real ArithmeticRGB[][3] = {
        // KITgreen
          { 0    , 0.588, 0.509 }  // KITgreen
        , { 0.3  , 0.711, 0.656 }  // KITgreen70
        , { 0.5  , 0.794, 0.754 }  // KITgreen50
        , { 0.7  , 0.876, 0.852 }  // KITgreen30
        , { 0.85 , 0.938, 0.926 }  // KITgreen15
        // KITblue
        , { 0.274, 0.392, 0.666 }  // KITblue
        , { 0.492, 0.574, 0.766 }  // KITblue70
        , { 0.637, 0.696, 0.833 }  // KITblue50
        , { 0.782, 0.817, 0.9   }  // KITblue30
        , { 0.891, 0.908, 0.95  }  // KITblue15
        // KITblack
        , { 0    , 0    , 0     }  // KITblack
        , { 0.3  , 0.3  , 0.3   }  // KITblack70
        , { 0.5  , 0.5  , 0.5   }  // KITblack50
        , { 0.7  , 0.7  , 0.7   }  // KITblack32
        , { 0.7  , 0.7  , 0.7   }  // KITblack31
        , { 0.7  , 0.7  , 0.7   }  // KITblack30
        , { 0.71 , 0.71 , 0.71  }  // KITblack29
        , { 0.72 , 0.72 , 0.72  }  // KITblack28
        , { 0.73 , 0.73 , 0.73  }  // KITblack27
        , { 0.74 , 0.74 , 0.74  }  // KITblack26
        , { 0.75 , 0.75 , 0.75  }  // KITblack25
        , { 0.76 , 0.76 , 0.76  }  // KITblack24
        , { 0.77 , 0.77 , 0.77  }  // KITblack23
        , { 0.78 , 0.78 , 0.78  }  // KITblack22
        , { 0.79 , 0.79 , 0.79  }  // KITblack21
        , { 0.80 , 0.80 , 0.80  }  // KITblack20
        , { 0.81 , 0.81 , 0.81  }  // KITblack19
        , { 0.82 , 0.82 , 0.82  }  // KITblack18
        , { 0.83 , 0.83 , 0.83  }  // KITblack17
        , { 0.84 , 0.84 , 0.84  }  // KITblack16
        , { 0.85 , 0.85 , 0.85  }  // KITblack15
        , { 0.86 , 0.86 , 0.86  }  // KITblack14
        , { 0.87 , 0.87 , 0.87  }  // KITblack13
        , { 0.88 , 0.88 , 0.88  }  // KITblack12
        , { 0.89 , 0.89 , 0.89  }  // KITblack11
        , { 0.90 , 0.90 , 0.90  }  // KITblack10
        , { 0.91 , 0.91 , 0.91  }  // KITblack09
        , { 0.92 , 0.92 , 0.92  }  // KITblack08
        , { 0.93 , 0.93 , 0.93  }  // KITblack07
        , { 0.94 , 0.94 , 0.94  }  // KITblack06
        , { 0.95 , 0.95 , 0.95  }  // KITblack05
        , { 0.96 , 0.96 , 0.96  }  // KITblack04
        , { 0.97 , 0.97 , 0.97  }  // KITblack03
        , { 0.98 , 0.98 , 0.98  }  // KITblack02
        , { 0.99 , 0.99 , 0.99  }  // KITblack01
        // KITpalegreen
        , { 0.509, 0.745, 0.235 }  // KITpalegreen
        , { 0.656, 0.821, 0.464 }  // KITpalegreen70
        , { 0.754, 0.872, 0.617 }  // KITpalegreen50
        , { 0.852, 0.923, 0.77  }  // KITpalegreen30
        , { 0.926, 0.961, 0.885 }  // KITpalegreen15
        // KITyellow
        , { 0.98 , 0.901, 0.078 }  // KITyellow
        , { 0.986, 0.931, 0.354 }  // KITyellow70
        , { 0.99 , 0.95 , 0.539 }  // KITyellow50
        , { 0.994, 0.97 , 0.723 }  // KITyellow30
        , { 0.997, 0.985, 0.861 }  // KITyellow15
        // KITorange
        , { 0.862, 0.627, 0.117 }  // KITorange
        , { 0.903, 0.739, 0.382 }  // KITorange70
        , { 0.931, 0.813, 0.558 }  // KITorange50
        , { 0.958, 0.888, 0.735 }  // KITorange30
        , { 0.979, 0.944, 0.867 }  // KITorange15
        // KITbrown
        , { 0.627, 0.509, 0.196 }  // KITbrown
        , { 0.739, 0.656, 0.437 }  // KITbrown70
        , { 0.813, 0.754, 0.598 }  // KITbrown50
        , { 0.888, 0.852, 0.758 }  // KITbrown30
        , { 0.944, 0.926, 0.879 }  // KITbrown15
        // KITred
        , { 0.627, 0.117, 0.156 }  // KITred
        , { 0.739, 0.382, 0.409 }  // KITred70
        , { 0.813, 0.558, 0.578 }  // KITred50
        , { 0.888, 0.735, 0.747 }  // KITred30
        , { 0.944, 0.867, 0.873 }  // KITred15
        // KITlilac
        , { 0.627, 0    , 0.47  }  // KITlilac
        , { 0.739, 0.3  , 0.629 }  // KITlilac70
        , { 0.813, 0.5  , 0.735 }  // KITlilac50
        , { 0.888, 0.7  , 0.841 }  // KITlilac30
        , { 0.944, 0.85 , 0.92  }  // KITlilac15
        // KITcyanblue
        , { 0.313, 0.666, 0.901 }  // KITcyanblue
        , { 0.519, 0.766, 0.931 }  // KITcyanblue70
        , { 0.656, 0.833, 0.95  }  // KITcyanblue50
        , { 0.794, 0.9  , 0.97  }  // KITcyanblue30
        , { 0.897, 0.95 , 0.985 }  // KITcyanblue15
        // KITseablue
        , { 0.196, 0.313, 0.549 }  // KITseablue
        , { 0.437, 0.519, 0.684 }  // KITseablue70
        , { 0.598, 0.656, 0.774 }  // KITseablue50
        , { 0.758, 0.794, 0.864 }  // KITseablue30
        , { 0.879, 0.897, 0.932 }  // KITseablue15
        // 
        // Thesis Colors
        , { 0.337, 0.592, 0.773 }  // THESISblue
        , { 0.212, 0.471, 0.655 }  // THESISblue_dark
        , { 0.490, 0.710, 0.867 }  // THESISblue_light
        , { 0.871, 0.937, 0.988 }  // THESISblue_vlight
        //
        , { 0.776, 0.357, 0.396 }  // THESISred
        , { 0.663, 0.235, 0.271 }  // THESISred_dark
        , { 0.867, 0.502, 0.533 }  // THESISred_light
        , { 0.984, 0.871, 0.878 }  // THESISred_vlight
        //
        , { 0.337, 0.765, 0.235 }  // THESISgreen
        , { 0.267, 0.612, 0.184 }  // THESISgreen_dark
        , { 0.443, 0.871, 0.341 }  // THESISgreen_light
        , { 0.710, 0.984, 0.643 }  // THESISgreen_vlight
        //
        , { 0.808, 0.659, 0.263 }  // THESISyellow
        , { 0.667, 0.529, 0.180 }  // THESISyellow_dark
        , { 0.898, 0.765, 0.412 }  // THESISyellow_light
        , { 0.992, 0.933, 0.776 }  // THESISyellow_vlight
        //
        , { 0    , 0    , 0     }  // THESISblack
        , { 0.3  , 0.3  , 0.3   }  // THESISblack70
        , { 0.5  , 0.5  , 0.5   }  // THESISblack50
        , { 0.7  , 0.7  , 0.7   }  // THESISblack30
        , { 0.85 , 0.85 , 0.85  }  // THESISblack15
        , { 0.92 , 0.92 , 0.92  }  // THESISblack7
        // OGDF
        , { 0.855, 0.647, 0.125 }  // Goldenrod
        , { 0.002, 0.002, 0.002 }  // Gray
        , { 0    , 0.002, 0     }  // Green
        , { 0.678, 1.0  , 0.184 }  // Greenyellow
        , { 0.002, 0.002, 0.002 }  // Grey
        , { 0.941, 1.0  , 0.941 }  // Honeydew
        , { 1.000, 0.412, 0.706 }  // Hotpink
        , { 0.804, 0.361, 0.361 }  // Indianred
        , { 0.294, 0.000, 0.510 }  // Indigo
        , { 1.000, 1.000, 0.941 }  // Ivory
        , { 0.941, 0.902, 0.549 }  // Khaki
        , { 0.902, 0.902, 0.980 }  // Lavender
        , { 1.000, 0.941, 0.961 }  // Lavenderblush
        , { 0.486, 0.988, 0.000 }  // Lawngreen
        , { 1.000, 0.980, 0.804 }  // Lemonchiffon
        , { 0.678, 0.847, 0.902 }  // Lightblue
        , { 0.941, 0.002, 0.002 }  // Lightcoral
        , { 0.878, 1.000, 1.000 }  // Lightcyan
        , { 0.980, 0.980, 0.824 }  // Lightgoldenrodyellow
        , { 0.827, 0.827, 0.827 }  // Lightgray
        , { 0.565, 0.933, 0.565 }  // Lightgreen
        , { 0.827, 0.827, 0.827 }  // Lightgrey
        , { 1.000, 0.714, 0.757 }  // Lightpink
        , { 1.000, 0.627, 0.478 }  // Lightsalmon
        , { 0.125, 0.698, 0.667 }  // Lightseagreen
        , { 0.529, 0.808, 0.980 }  // Lightskyblue
        , { 0.467, 0.533, 0.600 }  // Lightslategray
        , { 0.467, 0.533, 0.600 }  // Lightslategrey
        , { 0.690, 0.769, 0.871 }  // Lightsteelblue
        , { 1.000, 1.000, 0.878 }  // Lightyellow
        , { 0.000, 1.000, 0.000 }  // Lime
        , { 0.196, 0.804, 0.196 }  // Limegreen
        , { 0.980, 0.941, 0.902 }  // Linen
        , { 1.000, 0.000, 1.000 }  // Magenta
        , { 0.002, 0    , 0     }  // Maroon
        , { 0.400, 0.804, 0.667 }  // Mediumaquamarine
        , { 0.000, 0.000, 0.804 }  // Mediumblue
        , { 0.729, 0.333, 0.827 }  // Mediumorchid
        , { 0.576, 0.439, 0.859 }  // Mediumpurple
        , { 0.235, 0.700, 0.443 }  // Mediumseagreen
        , { 0.482, 0.408, 0.933 }  // Mediumslateblue
        , { 0.000, 0.980, 0.604 }  // Mediumspringgreen
        , { 0.282, 0.820, 0.800 }  // Mediumturquoise
        , { 0.780, 0.082, 0.522 }  // Mediumvioletred
        , { 0.098, 0.098, 0.439 }  // Midnightblue
        , { 0.961, 1.000, 0.980 }  // Mintcream
        , { 1.000, 0.894, 0.882 }  // Mistyrose
        , { 1.000, 0.894, 0.003 }  // Moccasin
        , { 1.000, 0.871, 0.678 }  // Navajowhite
        , { 0    , 0    , 0.002 }  // Navy
        , { 0.992, 0.961, 0.902 }  // Oldlace
        , { 0.002, 0.002, 0     }  // Olive
        , { 0.420, 0.557, 0.137 }  // Olivedrab
        , { 1.000, 0.647, 0.000 }  // Orange
        , { 1.000, 0.271, 0.000 }  // Orangered
        , { 0.855, 0.439, 0.839 }  // Orchid
        , { 0.933, 0.910, 0.667 }  // Palegoldenrod
        , { 0.596, 0.984, 0.596 }  // Palegreen
        , { 0.686, 0.933, 0.933 }  // Paleturquoise
        , { 0.859, 0.439, 0.576 }  // Palevioletred
        , { 1.0  , 0.937, 0.835 }  // Papayawhip
        , { 1.0  , 0.855, 0.725 }  // Peachpuff
        , { 0.804, 0.522, 0.247 }  // Peru
        , { 1.0  , 0.753, 0.796 }  // Pink
        , { 0.867, 0.627, 0.867 }  // Plum
        , { 0.690, 0.878, 0.902 }  // Powderblue
        , { 0.002, 0    , 0.002 }  // Purple
        , { 1.0  , 0    , 0     }  // Red
        , { 0.737, 0.561, 0.561 }  // Rosybrown
        , { 0.255, 0.412, 0.882 }  // Royalblue
        , { 0.545, 0.271, 0.075 }  // Saddlebrown
        , { 0.980, 0.002, 0.447 }  // Salmon
        , { 0.957, 0.643, 0.376 }  // Sandybrown
        , { 0.180, 0.545, 0.341 }  // Seagreen
        , { 1.0  , 0.961, 0.933 }  // Seashell
        , { 0.627, 0.322, 0.176 }  // Sienna
        , { 0.753, 0.753, 0.753 }  // Silver
        , { 0.529, 0.808, 0.922 }  // Skyblue
        , { 0.416, 0.353, 0.804 }   // Slateblue
        , { 0.439, 0.002, 0.565 }   // Slategray
        , { 0.439, 0.002, 0.565 }   // Slategrey
        , { 1.0  , 0.980, 0.980 }   // Snow
        , { 0    , 1.0  , 0.498 }   // Springgreen
        , { 0.275, 0.510, 0.706 }   // Steelblue
        , { 0.824, 0.706, 0.549 }   // Tan
        , { 0    , 0.002, 0.002 }   // Teal
        , { 0.847, 0.749, 0.847 }   // Thistle
        , { 1.0  , 0.388, 0.278 }   // Tomato
        , { 0.251, 0.878, 0.826 }   // Turquoise
        , { 0.933, 0.510, 0.933 }   // Violet
        , { 0.961, 0.871, 0.003 }   // Wheat
        , { 1.0  , 1.0  , 1.0   }   // White
        , { 0.961, 0.961, 0.961 }  // Whitesmoke
        , { 1.0  , 1.0  , 0     }   // Yellow
        , { 0.604, 0.804, 0.196 }   // Yellowgreen
    };

    Color::Color(Color::Name name)
    :   red_( ArithmeticRGB[static_cast<Types::count>(name)][0])
    , green_( ArithmeticRGB[static_cast<Types::count>(name)][1])
    ,  blue_( ArithmeticRGB[static_cast<Types::count>(name)][2])
    , alpha_(0)
    {}

    void Color::Red( Types::ubyte red ) {   
        this->red() = ( red   / 255 ); 
    }

    Types::ubyte Color::Red() const { 
        return static_cast<Types::ubyte>( red_   * 255 >= 0.0 )?
                                        ( red_   * 255 + 0.5  ):
                                        ( red_   * 255 - 0.5  ); 
    }

    void Color::Green( Types::ubyte green ) {   
        this->green() = ( green   / 255 ); 
    }

    Types::ubyte Color::Green() const { 
        return static_cast<Types::ubyte>( green_ * 255 >= 0.0 )?
                                        ( green_ * 255 + 0.5  ):
                                        ( green_ * 255 - 0.5  ); 
    }

    void Color::Blue( Types::ubyte blue ) {   
        this->blue() = ( blue   / 255 ); 
    }    

    Types::ubyte Color::Blue() const { 
        return static_cast<Types::ubyte>( blue_  * 255 >= 0.0 )?
                                        ( blue_  * 255 + 0.5  ):
                                        ( blue_  * 255 - 0.5  ); 
    }

    std::string Color::Hexadecimal( ) {
        std::stringstream hexstring;
        hexstring << "#"    << std::setfill('0') << std::setw(2) << std::uppercase
                            << std::hex          << static_cast<int>(Red()) 
                            << std::setfill('0') << std::setw(2) << std::uppercase
                            << std::hex          << static_cast<int>(Green())
                            << std::setfill('0') << std::setw(2) << std::uppercase
                            << std::hex          << static_cast<int>(Blue()) 
                            << std::endl;
        return hexstring.str(); 
    }

} // namespace egoa
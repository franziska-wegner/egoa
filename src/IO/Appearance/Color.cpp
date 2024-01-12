/*
 * Color.cpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Franziska Wegner
 */

#include "IO/Appearance/Color.hpp"

#include <sstream>
#include <iomanip>

#include <Auxiliary/Types.hpp>

namespace egoa {

    using ubyte_array = std::array<Types::ubyte,3>;
    using float_array = std::array<Types::real,3>;

    std::array RGB = { // Types::ubyte RGB[][3]
        // KITgreen
          ubyte_array{   0, 150, 130 }  // KITgreen
        , ubyte_array{  77, 181, 167 }  // KITgreen70
        , ubyte_array{ 128, 202, 192 }  // KITgreen50
        , ubyte_array{ 179, 223, 217 }  // KITgreen30
        , ubyte_array{ 217, 239, 236 }  // KITgreen15
        // KITblue
        , ubyte_array{  70, 100, 170 }  // KITblue
        , ubyte_array{ 125, 146, 195 }  // KITblue70
        , ubyte_array{ 162, 177, 212 }  // KITblue50
        , ubyte_array{ 199, 208, 230 }  // KITblue30
        , ubyte_array{ 227, 232, 242 }  // KITblue15
        // KITblack
        , ubyte_array{   0,   0,   0 }  // KITblack
        , ubyte_array{  77,  77,  77 }  // KITblack70
        , ubyte_array{ 128, 128, 128 }  // KITblack50
        , ubyte_array{ 179, 179, 179 }  // KITblack32
        , ubyte_array{ 179, 179, 179 }  // KITblack31
        , ubyte_array{ 179, 179, 179 }  // KITblack30
        , ubyte_array{ 181, 181, 181 }  // KITblack29
        , ubyte_array{ 184, 184, 184 }  // KITblack28
        , ubyte_array{ 186, 186, 186 }  // KITblack27
        , ubyte_array{ 189, 189, 189 }  // KITblack26
        , ubyte_array{ 191, 191, 191 }  // KITblack25
        , ubyte_array{ 194, 194, 194 }  // KITblack24
        , ubyte_array{ 196, 196, 196 }  // KITblack23
        , ubyte_array{ 199, 199, 199 }  // KITblack22
        , ubyte_array{ 201, 201, 201 }  // KITblack21
        , ubyte_array{ 204, 204, 204 }  // KITblack20
        , ubyte_array{ 207, 207, 207 }  // KITblack19
        , ubyte_array{ 209, 209, 209 }  // KITblack18
        , ubyte_array{ 212, 212, 212 }  // KITblack17
        , ubyte_array{ 214, 214, 214 }  // KITblack16
        , ubyte_array{ 217, 217, 217 }  // KITblack15
        , ubyte_array{ 219, 219, 219 }  // KITblack14
        , ubyte_array{ 222, 222, 222 }  // KITblack13
        , ubyte_array{ 224, 224, 224 }  // KITblack12
        , ubyte_array{ 227, 227, 227 }  // KITblack11
        , ubyte_array{ 230, 230, 230 }  // KITblack10
        , ubyte_array{ 232, 232, 232 }  // KITblack09
        , ubyte_array{ 235, 235, 235 }  // KITblack08
        , ubyte_array{ 237, 237, 237 }  // KITblack07
        , ubyte_array{ 240, 240, 240 }  // KITblack06
        , ubyte_array{ 242, 242, 242 }  // KITblack05
        , ubyte_array{ 245, 245, 245 }  // KITblack04
        , ubyte_array{ 247, 247, 247 }  // KITblack03
        , ubyte_array{ 250, 250, 250 }  // KITblack02
        , ubyte_array{ 252, 252, 252 }  // KITblack01
        // KITpalegreen
        , ubyte_array{ 130, 190,  60 }  // KITpalegreen
        , ubyte_array{ 167, 209, 118 }  // KITpalegreen70
        , ubyte_array{ 192, 222, 157 }  // KITpalegreen50
        , ubyte_array{ 217, 235, 196 }  // KITpalegreen30
        , ubyte_array{ 236, 245, 226 }  // KITpalegreen15
        // KITyellow
        , ubyte_array{ 250, 230,  20 }  // KITyellow
        , ubyte_array{ 251, 237,  90 }  // KITyellow70
        , ubyte_array{ 252, 242, 137 }  // KITyellow50
        , ubyte_array{ 253, 247, 184 }  // KITyellow30
        , ubyte_array{ 254, 251, 220 }  // KITyellow15
        // KITorange
        , ubyte_array{ 220, 160,  30 }  // KITorange
        , ubyte_array{ 230, 188,  97 }  // KITorange70
        , ubyte_array{ 237, 207, 142 }  // KITorange50
        , ubyte_array{ 244, 226, 187 }  // KITorange30
        , ubyte_array{ 250, 241, 221 }  // KITorange15
        // KITbrown
        , ubyte_array{ 160, 130,  50 }  // KITbrown
        , ubyte_array{ 188, 167, 111 }  // KITbrown70
        , ubyte_array{ 207, 192, 152 }  // KITbrown50
        , ubyte_array{ 226, 217, 193 }  // KITbrown30
        , ubyte_array{ 241, 236, 224 }  // KITbrown15
        // KITred
        , ubyte_array{ 160,  30,  40 }  // KITred
        , ubyte_array{ 188,  97, 104 }  // KITred70
        , ubyte_array{ 207, 142, 147 }  // KITred50
        , ubyte_array{ 226, 187, 190 }  // KITred30
        , ubyte_array{ 241, 221, 223 }  // KITred15
        // KITlilac
        , ubyte_array{ 160,   0, 120 }  // KITlilac
        , ubyte_array{ 188,  77, 160 }  // KITlilac70
        , ubyte_array{ 207, 128, 187 }  // KITlilac50
        , ubyte_array{ 226, 179, 214 }  // KITlilac30
        , ubyte_array{ 241, 217, 235 }  // KITlilac15
        // KITcyanblue
        , ubyte_array{  80, 170, 230 }  // KITcyanblue
        , ubyte_array{ 132, 195, 237 }  // KITcyanblue70
        , ubyte_array{ 167, 212, 242 }  // KITcyanblue50
        , ubyte_array{ 202, 230, 247 }  // KITcyanblue30
        , ubyte_array{ 229, 242, 251 }  // KITcyanblue15
        // KITseablue
        , ubyte_array{  50,  80, 140 }  // KITseablue
        , ubyte_array{ 111, 132, 174 }  // KITseablue70
        , ubyte_array{ 152, 167, 197 }  // KITseablue50
        , ubyte_array{ 193, 202, 220 }  // KITseablue30
        , ubyte_array{ 224, 229, 238 }  // KITseablue15
        //
        // Thesis Colors
        , ubyte_array{  86, 151, 197 }  // THESISblue
        , ubyte_array{  54, 120, 167 }  // THESISblue_dark
        , ubyte_array{ 125, 181, 221 }  // THESISblue_light
        , ubyte_array{ 222, 239, 252 }  // THESISblue_vlight
        //
        , ubyte_array{ 198,  91, 101 }  // THESISred
        , ubyte_array{ 169,  60,  69 }  // THESISred_dark
        , ubyte_array{ 221, 128, 136 }  // THESISred_light
        , ubyte_array{ 251, 222, 224 }  // THESISred_vlight
        //
        , ubyte_array{  86, 195,  60 }  // THESISgreen
        , ubyte_array{  68, 156,  47 }  // THESISgreen_dark
        , ubyte_array{ 112, 222,  87 }  // THESISgreen_light
        , ubyte_array{ 181, 251, 164 }  // THESISgreen_vlight
        //
        , ubyte_array{ 206, 168,  67 }  // THESISyellow
        , ubyte_array{ 170, 135,  46 }  // THESISyellow_dark
        , ubyte_array{ 229, 195, 105 }  // THESISyellow_light
        , ubyte_array{ 253, 238, 198 }  // THESISyellow_vlight
        //
        , ubyte_array{   0,   0,   0 }  // THESISblack
        , ubyte_array{  77,  77,  77 }  // THESISblack70
        , ubyte_array{ 128, 128, 128 }  // THESISblack50
        , ubyte_array{ 179, 179, 179 }  // THESISblack30
        , ubyte_array{ 217, 217, 217 }  // THESISblack15
        , ubyte_array{ 235, 235, 235 }  // THESISblack7
        // OGDF
        , ubyte_array{ 218, 165,  32 }  // Goldenrod
        , ubyte_array{ 128, 128, 128 }  // Gray
        , ubyte_array{   0, 128,   0 }  // Green
        , ubyte_array{ 173, 255,  47 }  // Greenyellow
        , ubyte_array{ 128, 128, 128 }  // Grey
        , ubyte_array{ 240, 255, 240 }  // Honeydew
        , ubyte_array{ 255, 105, 180 }  // Hotpink
        , ubyte_array{ 205,  92,  92 }  // Indianred
        , ubyte_array{  75,   0, 130 }  // Indigo
        , ubyte_array{ 255, 255, 240 }  // Ivory
        , ubyte_array{ 240, 230, 140 }  // Khaki
        , ubyte_array{ 230, 230, 250 }  // Lavender
        , ubyte_array{ 255, 240, 245 }  // Lavenderblush
        , ubyte_array{ 124, 252,   0 }  // Lawngreen
        , ubyte_array{ 255, 250, 205 }  // Lemonchiffon
        , ubyte_array{ 173, 216, 230 }  // Lightblue
        , ubyte_array{ 240, 128, 128 }  // Lightcoral
        , ubyte_array{ 224, 255, 255 }  // Lightcyan
        , ubyte_array{ 250, 250, 210 }  // Lightgoldenrodyellow
        , ubyte_array{ 211, 211, 211 }  // Lightgray
        , ubyte_array{ 144, 238, 144 }  // Lightgreen
        , ubyte_array{ 211, 211, 211 }  // Lightgrey
        , ubyte_array{ 255, 182, 193 }  // Lightpink
        , ubyte_array{ 255, 160, 122 }  // Lightsalmon
        , ubyte_array{  32, 178, 170 }  // Lightseagreen
        , ubyte_array{ 135, 206, 250 }  // Lightskyblue
        , ubyte_array{ 119, 136, 153 }  // Lightslategray
        , ubyte_array{ 119, 136, 153 }  // Lightslategrey
        , ubyte_array{ 176, 196, 222 }  // Lightsteelblue
        , ubyte_array{ 255, 255, 224 }  // Lightyellow
        , ubyte_array{   0, 255,   0 }  // Lime
        , ubyte_array{  50, 205,  50 }  // Limegreen
        , ubyte_array{ 250, 240, 230 }  // Linen
        , ubyte_array{ 255,   0, 255 }  // Magenta
        , ubyte_array{ 128,   0,   0 }  // Maroon
        , ubyte_array{ 102, 205, 170 }  // Mediumaquamarine
        , ubyte_array{   0,   0, 205 }  // Mediumblue
        , ubyte_array{ 186,  85, 211 }  // Mediumorchid
        , ubyte_array{ 147, 112, 219 }  // Mediumpurple
        , ubyte_array{  60, 179, 113 }  // Mediumseagreen
        , ubyte_array{ 123, 104, 238 }  // Mediumslateblue
        , ubyte_array{   0, 250, 154 }  // Mediumspringgreen
        , ubyte_array{  72, 209, 204 }  // Mediumturquoise
        , ubyte_array{ 199,  21, 133 }  // Mediumvioletred
        , ubyte_array{  25,  25, 112 }  // Midnightblue
        , ubyte_array{ 245, 255, 250 }  // Mintcream
        , ubyte_array{ 255, 228, 225 }  // Mistyrose
        , ubyte_array{ 255, 228, 181 }  // Moccasin
        , ubyte_array{ 255, 222, 173 }  // Navajowhite
        , ubyte_array{   0,   0, 128 }  // Navy
        , ubyte_array{ 253, 245, 230 }  // Oldlace
        , ubyte_array{ 128, 128,   0 }  // Olive
        , ubyte_array{ 107, 142,  35 }  // Olivedrab
        , ubyte_array{ 255, 165,   0 }  // Orange
        , ubyte_array{ 255,  69,   0 }  // Orangered
        , ubyte_array{ 218, 112, 214 }  // Orchid
        , ubyte_array{ 238, 232, 170 }  // Palegoldenrod
        , ubyte_array{ 152, 251, 152 }  // Palegreen
        , ubyte_array{ 175, 238, 238 }  // Paleturquoise
        , ubyte_array{ 219, 112, 147 }  // Palevioletred
        , ubyte_array{ 255, 239, 213 }  // Papayawhip
        , ubyte_array{ 255, 218, 185 }  // Peachpuff
        , ubyte_array{ 205, 133,  63 }  // Peru
        , ubyte_array{ 255, 192, 203 }  // Pink
        , ubyte_array{ 221, 160, 221 }  // Plum
        , ubyte_array{ 176, 224, 230 }  // Powderblue
        , ubyte_array{ 128,   0, 128 }  // Purple
        , ubyte_array{ 255,   0,   0 }  // Red
        , ubyte_array{ 188, 143, 143 }  // Rosybrown
        , ubyte_array{  65, 105, 225 }  // Royalblue
        , ubyte_array{ 139,  69,  19 }  // Saddlebrown
        , ubyte_array{ 250, 128, 114 }  // Salmon
        , ubyte_array{ 244, 164,  96 }  // Sandybrown
        , ubyte_array{  46, 139,  87 }  // Seagreen
        , ubyte_array{ 255, 245, 238 }  // Seashell
        , ubyte_array{ 160,  82,  45 }  // Sienna
        , ubyte_array{ 192, 192, 192 }  // Silver
        , ubyte_array{ 135, 206, 235 }  // Skyblue
        , ubyte_array{ 106,  90, 205 }  // Slateblue
        , ubyte_array{ 112, 128, 144 }  // Slategray
        , ubyte_array{ 112, 128, 144 }  // Slategrey
        , ubyte_array{ 255, 250, 250 }  // Snow
        , ubyte_array{   0, 255, 127 }  // Springgreen
        , ubyte_array{  70, 130, 180 }  // Steelblue
        , ubyte_array{ 210, 180, 140 }  // Tan
        , ubyte_array{   0, 128, 128 }  // Teal
        , ubyte_array{ 216, 191, 216 }  // Thistle
        , ubyte_array{ 255,  99,  71 }  // Tomato
        , ubyte_array{  64, 224, 208 }  // Turquoise
        , ubyte_array{ 238, 130, 238 }  // Violet
        , ubyte_array{ 245, 222, 179 }  // Wheat
        , ubyte_array{ 255, 255, 255 }  // White
        , ubyte_array{ 245, 245, 245 }  // Whitesmoke
        , ubyte_array{ 255, 255,   0 } // Yellow
        , ubyte_array{ 154, 205,  50 } // Yellowgreen
    };

    std::array ArithmeticRGB = { // Types::real ArithmeticRGB[][3]
        // KITgreen
          float_array{ 0    , 0.588, 0.509 }  // KITgreen
        , float_array{ 0.3  , 0.711, 0.656 }  // KITgreen70
        , float_array{ 0.5  , 0.794, 0.754 }  // KITgreen50
        , float_array{ 0.7  , 0.876, 0.852 }  // KITgreen30
        , float_array{ 0.85 , 0.938, 0.926 }  // KITgreen15
        // KITblue
        , float_array{ 0.274, 0.392, 0.666 }  // KITblue
        , float_array{ 0.492, 0.574, 0.766 }  // KITblue70
        , float_array{ 0.637, 0.696, 0.833 }  // KITblue50
        , float_array{ 0.782, 0.817, 0.9   }  // KITblue30
        , float_array{ 0.891, 0.908, 0.95  }  // KITblue15
        // KITblack
        , float_array{ 0    , 0    , 0     }  // KITblack
        , float_array{ 0.3  , 0.3  , 0.3   }  // KITblack70
        , float_array{ 0.5  , 0.5  , 0.5   }  // KITblack50
        , float_array{ 0.7  , 0.7  , 0.7   }  // KITblack32
        , float_array{ 0.7  , 0.7  , 0.7   }  // KITblack31
        , float_array{ 0.7  , 0.7  , 0.7   }  // KITblack30
        , float_array{ 0.71 , 0.71 , 0.71  }  // KITblack29
        , float_array{ 0.72 , 0.72 , 0.72  }  // KITblack28
        , float_array{ 0.73 , 0.73 , 0.73  }  // KITblack27
        , float_array{ 0.74 , 0.74 , 0.74  }  // KITblack26
        , float_array{ 0.75 , 0.75 , 0.75  }  // KITblack25
        , float_array{ 0.76 , 0.76 , 0.76  }  // KITblack24
        , float_array{ 0.77 , 0.77 , 0.77  }  // KITblack23
        , float_array{ 0.78 , 0.78 , 0.78  }  // KITblack22
        , float_array{ 0.79 , 0.79 , 0.79  }  // KITblack21
        , float_array{ 0.80 , 0.80 , 0.80  }  // KITblack20
        , float_array{ 0.81 , 0.81 , 0.81  }  // KITblack19
        , float_array{ 0.82 , 0.82 , 0.82  }  // KITblack18
        , float_array{ 0.83 , 0.83 , 0.83  }  // KITblack17
        , float_array{ 0.84 , 0.84 , 0.84  }  // KITblack16
        , float_array{ 0.85 , 0.85 , 0.85  }  // KITblack15
        , float_array{ 0.86 , 0.86 , 0.86  }  // KITblack14
        , float_array{ 0.87 , 0.87 , 0.87  }  // KITblack13
        , float_array{ 0.88 , 0.88 , 0.88  }  // KITblack12
        , float_array{ 0.89 , 0.89 , 0.89  }  // KITblack11
        , float_array{ 0.90 , 0.90 , 0.90  }  // KITblack10
        , float_array{ 0.91 , 0.91 , 0.91  }  // KITblack09
        , float_array{ 0.92 , 0.92 , 0.92  }  // KITblack08
        , float_array{ 0.93 , 0.93 , 0.93  }  // KITblack07
        , float_array{ 0.94 , 0.94 , 0.94  }  // KITblack06
        , float_array{ 0.95 , 0.95 , 0.95  }  // KITblack05
        , float_array{ 0.96 , 0.96 , 0.96  }  // KITblack04
        , float_array{ 0.97 , 0.97 , 0.97  }  // KITblack03
        , float_array{ 0.98 , 0.98 , 0.98  }  // KITblack02
        , float_array{ 0.99 , 0.99 , 0.99  }  // KITblack01
        // KITpalegreen
        , float_array{ 0.509, 0.745, 0.235 }  // KITpalegreen
        , float_array{ 0.656, 0.821, 0.464 }  // KITpalegreen70
        , float_array{ 0.754, 0.872, 0.617 }  // KITpalegreen50
        , float_array{ 0.852, 0.923, 0.77  }  // KITpalegreen30
        , float_array{ 0.926, 0.961, 0.885 }  // KITpalegreen15
        // KITyellow
        , float_array{ 0.98 , 0.901, 0.078 }  // KITyellow
        , float_array{ 0.986, 0.931, 0.354 }  // KITyellow70
        , float_array{ 0.99 , 0.95 , 0.539 }  // KITyellow50
        , float_array{ 0.994, 0.97 , 0.723 }  // KITyellow30
        , float_array{ 0.997, 0.985, 0.861 }  // KITyellow15
        // KITorange
        , float_array{ 0.862, 0.627, 0.117 }  // KITorange
        , float_array{ 0.903, 0.739, 0.382 }  // KITorange70
        , float_array{ 0.931, 0.813, 0.558 }  // KITorange50
        , float_array{ 0.958, 0.888, 0.735 }  // KITorange30
        , float_array{ 0.979, 0.944, 0.867 }  // KITorange15
        // KITbrown
        , float_array{ 0.627, 0.509, 0.196 }  // KITbrown
        , float_array{ 0.739, 0.656, 0.437 }  // KITbrown70
        , float_array{ 0.813, 0.754, 0.598 }  // KITbrown50
        , float_array{ 0.888, 0.852, 0.758 }  // KITbrown30
        , float_array{ 0.944, 0.926, 0.879 }  // KITbrown15
        // KITred
        , float_array{ 0.627, 0.117, 0.156 }  // KITred
        , float_array{ 0.739, 0.382, 0.409 }  // KITred70
        , float_array{ 0.813, 0.558, 0.578 }  // KITred50
        , float_array{ 0.888, 0.735, 0.747 }  // KITred30
        , float_array{ 0.944, 0.867, 0.873 }  // KITred15
        // KITlilac
        , float_array{ 0.627, 0    , 0.47  }  // KITlilac
        , float_array{ 0.739, 0.3  , 0.629 }  // KITlilac70
        , float_array{ 0.813, 0.5  , 0.735 }  // KITlilac50
        , float_array{ 0.888, 0.7  , 0.841 }  // KITlilac30
        , float_array{ 0.944, 0.85 , 0.92  }  // KITlilac15
        // KITcyanblue
        , float_array{ 0.313, 0.666, 0.901 }  // KITcyanblue
        , float_array{ 0.519, 0.766, 0.931 }  // KITcyanblue70
        , float_array{ 0.656, 0.833, 0.95  }  // KITcyanblue50
        , float_array{ 0.794, 0.9  , 0.97  }  // KITcyanblue30
        , float_array{ 0.897, 0.95 , 0.985 }  // KITcyanblue15
        // KITseablue
        , float_array{ 0.196, 0.313, 0.549 }  // KITseablue
        , float_array{ 0.437, 0.519, 0.684 }  // KITseablue70
        , float_array{ 0.598, 0.656, 0.774 }  // KITseablue50
        , float_array{ 0.758, 0.794, 0.864 }  // KITseablue30
        , float_array{ 0.879, 0.897, 0.932 }  // KITseablue15
        //
        // Thesis Colors
        , float_array{ 0.337, 0.592, 0.773 }  // THESISblue
        , float_array{ 0.212, 0.471, 0.655 }  // THESISblue_dark
        , float_array{ 0.490, 0.710, 0.867 }  // THESISblue_light
        , float_array{ 0.871, 0.937, 0.988 }  // THESISblue_vlight
        //
        , float_array{ 0.776, 0.357, 0.396 }  // THESISred
        , float_array{ 0.663, 0.235, 0.271 }  // THESISred_dark
        , float_array{ 0.867, 0.502, 0.533 }  // THESISred_light
        , float_array{ 0.984, 0.871, 0.878 }  // THESISred_vlight
        //
        , float_array{ 0.337, 0.765, 0.235 }  // THESISgreen
        , float_array{ 0.267, 0.612, 0.184 }  // THESISgreen_dark
        , float_array{ 0.443, 0.871, 0.341 }  // THESISgreen_light
        , float_array{ 0.710, 0.984, 0.643 }  // THESISgreen_vlight
        //
        , float_array{ 0.808, 0.659, 0.263 }  // THESISyellow
        , float_array{ 0.667, 0.529, 0.180 }  // THESISyellow_dark
        , float_array{ 0.898, 0.765, 0.412 }  // THESISyellow_light
        , float_array{ 0.992, 0.933, 0.776 }  // THESISyellow_vlight
        //
        , float_array{ 0    , 0    , 0     }  // THESISblack
        , float_array{ 0.3  , 0.3  , 0.3   }  // THESISblack70
        , float_array{ 0.5  , 0.5  , 0.5   }  // THESISblack50
        , float_array{ 0.7  , 0.7  , 0.7   }  // THESISblack30
        , float_array{ 0.85 , 0.85 , 0.85  }  // THESISblack15
        , float_array{ 0.92 , 0.92 , 0.92  }  // THESISblack7
        // OGDF
        , float_array{ 0.855, 0.647, 0.125 }  // Goldenrod
        , float_array{ 0.002, 0.002, 0.002 }  // Gray
        , float_array{ 0    , 0.002, 0     }  // Green
        , float_array{ 0.678, 1.0  , 0.184 }  // Greenyellow
        , float_array{ 0.002, 0.002, 0.002 }  // Grey
        , float_array{ 0.941, 1.0  , 0.941 }  // Honeydew
        , float_array{ 1.000, 0.412, 0.706 }  // Hotpink
        , float_array{ 0.804, 0.361, 0.361 }  // Indianred
        , float_array{ 0.294, 0.000, 0.510 }  // Indigo
        , float_array{ 1.000, 1.000, 0.941 }  // Ivory
        , float_array{ 0.941, 0.902, 0.549 }  // Khaki
        , float_array{ 0.902, 0.902, 0.980 }  // Lavender
        , float_array{ 1.000, 0.941, 0.961 }  // Lavenderblush
        , float_array{ 0.486, 0.988, 0.000 }  // Lawngreen
        , float_array{ 1.000, 0.980, 0.804 }  // Lemonchiffon
        , float_array{ 0.678, 0.847, 0.902 }  // Lightblue
        , float_array{ 0.941, 0.002, 0.002 }  // Lightcoral
        , float_array{ 0.878, 1.000, 1.000 }  // Lightcyan
        , float_array{ 0.980, 0.980, 0.824 }  // Lightgoldenrodyellow
        , float_array{ 0.827, 0.827, 0.827 }  // Lightgray
        , float_array{ 0.565, 0.933, 0.565 }  // Lightgreen
        , float_array{ 0.827, 0.827, 0.827 }  // Lightgrey
        , float_array{ 1.000, 0.714, 0.757 }  // Lightpink
        , float_array{ 1.000, 0.627, 0.478 }  // Lightsalmon
        , float_array{ 0.125, 0.698, 0.667 }  // Lightseagreen
        , float_array{ 0.529, 0.808, 0.980 }  // Lightskyblue
        , float_array{ 0.467, 0.533, 0.600 }  // Lightslategray
        , float_array{ 0.467, 0.533, 0.600 }  // Lightslategrey
        , float_array{ 0.690, 0.769, 0.871 }  // Lightsteelblue
        , float_array{ 1.000, 1.000, 0.878 }  // Lightyellow
        , float_array{ 0.000, 1.000, 0.000 }  // Lime
        , float_array{ 0.196, 0.804, 0.196 }  // Limegreen
        , float_array{ 0.980, 0.941, 0.902 }  // Linen
        , float_array{ 1.000, 0.000, 1.000 }  // Magenta
        , float_array{ 0.002, 0    , 0     }  // Maroon
        , float_array{ 0.400, 0.804, 0.667 }  // Mediumaquamarine
        , float_array{ 0.000, 0.000, 0.804 }  // Mediumblue
        , float_array{ 0.729, 0.333, 0.827 }  // Mediumorchid
        , float_array{ 0.576, 0.439, 0.859 }  // Mediumpurple
        , float_array{ 0.235, 0.700, 0.443 }  // Mediumseagreen
        , float_array{ 0.482, 0.408, 0.933 }  // Mediumslateblue
        , float_array{ 0.000, 0.980, 0.604 }  // Mediumspringgreen
        , float_array{ 0.282, 0.820, 0.800 }  // Mediumturquoise
        , float_array{ 0.780, 0.082, 0.522 }  // Mediumvioletred
        , float_array{ 0.098, 0.098, 0.439 }  // Midnightblue
        , float_array{ 0.961, 1.000, 0.980 }  // Mintcream
        , float_array{ 1.000, 0.894, 0.882 }  // Mistyrose
        , float_array{ 1.000, 0.894, 0.003 }  // Moccasin
        , float_array{ 1.000, 0.871, 0.678 }  // Navajowhite
        , float_array{ 0    , 0    , 0.002 }  // Navy
        , float_array{ 0.992, 0.961, 0.902 }  // Oldlace
        , float_array{ 0.002, 0.002, 0     }  // Olive
        , float_array{ 0.420, 0.557, 0.137 }  // Olivedrab
        , float_array{ 1.000, 0.647, 0.000 }  // Orange
        , float_array{ 1.000, 0.271, 0.000 }  // Orangered
        , float_array{ 0.855, 0.439, 0.839 }  // Orchid
        , float_array{ 0.933, 0.910, 0.667 }  // Palegoldenrod
        , float_array{ 0.596, 0.984, 0.596 }  // Palegreen
        , float_array{ 0.686, 0.933, 0.933 }  // Paleturquoise
        , float_array{ 0.859, 0.439, 0.576 }  // Palevioletred
        , float_array{ 1.0  , 0.937, 0.835 }  // Papayawhip
        , float_array{ 1.0  , 0.855, 0.725 }  // Peachpuff
        , float_array{ 0.804, 0.522, 0.247 }  // Peru
        , float_array{ 1.0  , 0.753, 0.796 }  // Pink
        , float_array{ 0.867, 0.627, 0.867 }  // Plum
        , float_array{ 0.690, 0.878, 0.902 }  // Powderblue
        , float_array{ 0.002, 0    , 0.002 }  // Purple
        , float_array{ 1.0  , 0    , 0     }  // Red
        , float_array{ 0.737, 0.561, 0.561 }  // Rosybrown
        , float_array{ 0.255, 0.412, 0.882 }  // Royalblue
        , float_array{ 0.545, 0.271, 0.075 }  // Saddlebrown
        , float_array{ 0.980, 0.002, 0.447 }  // Salmon
        , float_array{ 0.957, 0.643, 0.376 }  // Sandybrown
        , float_array{ 0.180, 0.545, 0.341 }  // Seagreen
        , float_array{ 1.0  , 0.961, 0.933 }  // Seashell
        , float_array{ 0.627, 0.322, 0.176 }  // Sienna
        , float_array{ 0.753, 0.753, 0.753 }  // Silver
        , float_array{ 0.529, 0.808, 0.922 }  // Skyblue
        , float_array{ 0.416, 0.353, 0.804 }   // Slateblue
        , float_array{ 0.439, 0.002, 0.565 }   // Slategray
        , float_array{ 0.439, 0.002, 0.565 }   // Slategrey
        , float_array{ 1.0  , 0.980, 0.980 }   // Snow
        , float_array{ 0    , 1.0  , 0.498 }   // Springgreen
        , float_array{ 0.275, 0.510, 0.706 }   // Steelblue
        , float_array{ 0.824, 0.706, 0.549 }   // Tan
        , float_array{ 0    , 0.002, 0.002 }   // Teal
        , float_array{ 0.847, 0.749, 0.847 }   // Thistle
        , float_array{ 1.0  , 0.388, 0.278 }   // Tomato
        , float_array{ 0.251, 0.878, 0.826 }   // Turquoise
        , float_array{ 0.933, 0.510, 0.933 }   // Violet
        , float_array{ 0.961, 0.871, 0.003 }   // Wheat
        , float_array{ 1.0  , 1.0  , 1.0   }   // White
        , float_array{ 0.961, 0.961, 0.961 }  // Whitesmoke
        , float_array{ 1.0  , 1.0  , 0     }   // Yellow
        , float_array{ 0.604, 0.804, 0.196 }   // Yellowgreen
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

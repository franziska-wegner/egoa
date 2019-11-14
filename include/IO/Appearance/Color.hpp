/*
 * Color.hpp
 *
 *  Created on: Nov 15, 2018
 *      Author: Franziska Wegner
 */

#ifndef EGOA__IO__COLOR_HPP
#define EGOA__IO__COLOR_HPP

#include "Auxiliary/Types.hpp"

namespace egoa {

/**
 *  @class Color
 *  
 *  @code{.cpp}
 *      ...
 *      pgt::Color color(255,255,255);
 *      pgt::Color color(0.9,0.5,0.1);
 *      pgt::Color color(pgt::Color::Name::KITred);
 *      std::cout << "Color: " << to_string(color.Green()) << std::endl;
 *      std::cout << "Color: " << color.Hexadecimal() << std::endl;     
 *      
 *      std::cout << std::fixed << std::setprecision(3);
 *      std::cout   << color.red()   << ", "
 *                  << color.green() << ", "
 *                  << color.blue()  << ""
 *                  << std::endl;
 *      std::cout << "Color: " << color.Hexadecimal() << std::endl;
 *      ...
 *      
 *  @endcode
 */
class Color {
    public:
        enum class Name {
              KITgreen              /**< RGB <- (   0, 150, 130 ), rgb <- ( 0    , 0.588, 0.509 ) */
            , KITgreen70            /**< RGB <- (  77, 181, 167 ), rgb <- ( 0.3  , 0.711, 0.656 ) */
            , KITgreen50            /**< RGB <- ( 128, 202, 192 ), rgb <- ( 0.5  , 0.794, 0.754 ) */
            , KITgreen30            /**< RGB <- ( 179, 223, 217 ), rgb <- ( 0.7  , 0.876, 0.852 ) */
            , KITgreen15            /**< RGB <- ( 217, 239, 236 ), rgb <- ( 0.85 , 0.938, 0.926 ) */
            // KITblue
            , KITblue               /**< RGB <- (  70, 100, 170 ), rgb <- ( 0.274, 0.392, 0.666 ) */
            , KITblue70             /**< RGB <- ( 125, 146, 195 ), rgb <- ( 0.492, 0.574, 0.766 ) */
            , KITblue50             /**< RGB <- ( 162, 177, 212 ), rgb <- ( 0.637, 0.696, 0.833 ) */
            , KITblue30             /**< RGB <- ( 199, 208, 230 ), rgb <- ( 0.782, 0.817, 0.9   ) */
            , KITblue15             /**< RGB <- ( 227, 232, 242 ), rgb <- ( 0.891, 0.908, 0.95  ) */
            // KITblack
            , KITblack              /**< RGB <- (   0,   0,   0 ), rgb <- ( 0    , 0    , 0     ) */
            , KITblack70            /**< RGB <- (  77,  77,  77 ), rgb <- ( 0.3  , 0.3  , 0.3   ) */
            , KITblack50            /**< RGB <- ( 128, 128, 128 ), rgb <- ( 0.5  , 0.5  , 0.5   ) */
            , KITblack32            /**< RGB <- ( 179, 179, 179 ), rgb <- ( 0.7  , 0.7  , 0.7   ) */
            , KITblack31            /**< RGB <- ( 179, 179, 179 ), rgb <- ( 0.7  , 0.7  , 0.7   ) */
            , KITblack30            /**< RGB <- ( 179, 179, 179 ), rgb <- ( 0.7  , 0.7  , 0.7   ) */
            , KITblack29            /**< RGB <- ( 181, 181, 181 ), rgb <- ( 0.71 , 0.71 , 0.71  ) */
            , KITblack28            /**< RGB <- ( 184, 184, 184 ), rgb <- ( 0.72 , 0.72 , 0.72  ) */
            , KITblack27            /**< RGB <- ( 186, 186, 186 ), rgb <- ( 0.73 , 0.73 , 0.73  ) */
            , KITblack26            /**< RGB <- ( 189, 189, 189 ), rgb <- ( 0.74 , 0.74 , 0.74  ) */
            , KITblack25            /**< RGB <- ( 191, 191, 191 ), rgb <- ( 0.75 , 0.75 , 0.75  ) */
            , KITblack24            /**< RGB <- ( 194, 194, 194 ), rgb <- ( 0.76 , 0.76 , 0.76  ) */
            , KITblack23            /**< RGB <- ( 196, 196, 196 ), rgb <- ( 0.77 , 0.77 , 0.77  ) */
            , KITblack22            /**< RGB <- ( 199, 199, 199 ), rgb <- ( 0.78 , 0.78 , 0.78  ) */
            , KITblack21            /**< RGB <- ( 201, 201, 201 ), rgb <- ( 0.79 , 0.79 , 0.79  ) */
            , KITblack20            /**< RGB <- ( 204, 204, 204 ), rgb <- ( 0.80 , 0.80 , 0.80  ) */
            , KITblack19            /**< RGB <- ( 207, 207, 207 ), rgb <- ( 0.81 , 0.81 , 0.81  ) */
            , KITblack18            /**< RGB <- ( 209, 209, 209 ), rgb <- ( 0.82 , 0.82 , 0.82  ) */
            , KITblack17            /**< RGB <- ( 212, 212, 212 ), rgb <- ( 0.83 , 0.83 , 0.83  ) */
            , KITblack16            /**< RGB <- ( 214, 214, 214 ), rgb <- ( 0.84 , 0.84 , 0.84  ) */
            , KITblack15            /**< RGB <- ( 217, 217, 217 ), rgb <- ( 0.85 , 0.85 , 0.85  ) */
            , KITblack14            /**< RGB <- ( 219, 219, 219 ), rgb <- ( 0.86 , 0.86 , 0.86  ) */
            , KITblack13            /**< RGB <- ( 222, 222, 222 ), rgb <- ( 0.87 , 0.87 , 0.87  ) */
            , KITblack12            /**< RGB <- ( 224, 224, 224 ), rgb <- ( 0.88 , 0.88 , 0.88  ) */
            , KITblack11            /**< RGB <- ( 227, 227, 227 ), rgb <- ( 0.89 , 0.89 , 0.89  ) */
            , KITblack10            /**< RGB <- ( 230, 230, 230 ), rgb <- ( 0.90 , 0.90 , 0.90  ) */
            , KITblack09            /**< RGB <- ( 232, 232, 232 ), rgb <- ( 0.91 , 0.91 , 0.91  ) */
            , KITblack08            /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , KITblack07            /**< RGB <- ( 237, 237, 237 ), rgb <- ( 0.93 , 0.93 , 0.93  ) */
            , KITblack06            /**< RGB <- ( 240, 240, 240 ), rgb <- ( 0.94 , 0.94 , 0.94  ) */
            , KITblack05            /**< RGB <- ( 242, 242, 242 ), rgb <- ( 0.95 , 0.95 , 0.95  ) */
            , KITblack04            /**< RGB <- ( 245, 245, 245 ), rgb <- ( 0.96 , 0.96 , 0.96  ) */
            , KITblack03            /**< RGB <- ( 247, 247, 247 ), rgb <- ( 0.97 , 0.97 , 0.97  ) */
            , KITblack02            /**< RGB <- ( 250, 250, 250 ), rgb <- ( 0.98 , 0.98 , 0.98  ) */
            , KITblack01            /**< RGB <- ( 252, 252, 252 ), rgb <- ( 0.99 , 0.99 , 0.99  ) */
            // KITpalegreen
            , KITpalegreen          /**< RGB <- ( 130, 190,  60 ), rgb <- ( 0.509, 0.745, 0.235 ) */
            , KITpalegreen70        /**< RGB <- ( 167, 209, 118 ), rgb <- ( 0.656, 0.821, 0.464 ) */
            , KITpalegreen50        /**< RGB <- ( 192, 222, 157 ), rgb <- ( 0.754, 0.872, 0.617 ) */
            , KITpalegreen30        /**< RGB <- ( 217, 235, 196 ), rgb <- ( 0.852, 0.923, 0.77  ) */
            , KITpalegreen15        /**< RGB <- ( 236, 245, 226 ), rgb <- ( 0.926, 0.961, 0.885 ) */
            // KITyellow
            , KITyellow             /**< RGB <- ( 250, 230,  20 ), rgb <- ( 0.98 , 0.901, 0.078 ) */
            , KITyellow70           /**< RGB <- ( 251, 237,  90 ), rgb <- ( 0.986, 0.931, 0.354 ) */
            , KITyellow50           /**< RGB <- ( 252, 242, 137 ), rgb <- ( 0.99 , 0.95 , 0.539 ) */
            , KITyellow30           /**< RGB <- ( 253, 247, 184 ), rgb <- ( 0.994, 0.97 , 0.723 ) */
            , KITyellow15           /**< RGB <- ( 254, 251, 220 ), rgb <- ( 0.997, 0.985, 0.861 ) */
            // KITorange
            , KITorange             /**< RGB <- ( 220, 160,  30 ), rgb <- ( 0.862, 0.627, 0.117 ) */
            , KITorange70           /**< RGB <- ( 230, 188,  97 ), rgb <- ( 0.903, 0.739, 0.382 ) */
            , KITorange50           /**< RGB <- ( 237, 207, 142 ), rgb <- ( 0.931, 0.813, 0.558 ) */
            , KITorange30           /**< RGB <- ( 244, 226, 187 ), rgb <- ( 0.958, 0.888, 0.735 ) */
            , KITorange15           /**< RGB <- ( 250, 241, 221 ), rgb <- ( 0.979, 0.944, 0.867 ) */
            // KITbrown
            , KITbrown              /**< RGB <- ( 160, 130,  50 ), rgb <- ( 0.627, 0.509, 0.196 ) */
            , KITbrown70            /**< RGB <- ( 188, 167, 111 ), rgb <- ( 0.739, 0.656, 0.437 ) */
            , KITbrown50            /**< RGB <- ( 207, 192, 152 ), rgb <- ( 0.813, 0.754, 0.598 ) */
            , KITbrown30            /**< RGB <- ( 226, 217, 193 ), rgb <- ( 0.888, 0.852, 0.758 ) */
            , KITbrown15            /**< RGB <- ( 241, 236, 224 ), rgb <- ( 0.944, 0.926, 0.879 ) */
            // KITred
            , KITred                /**< RGB <- ( 160,  30,  40 ), rgb <- ( 0.627, 0.117, 0.156 ) */
            , KITred70              /**< RGB <- ( 188,  97, 104 ), rgb <- ( 0.739, 0.382, 0.409 ) */
            , KITred50              /**< RGB <- ( 207, 142, 147 ), rgb <- ( 0.813, 0.558, 0.578 ) */
            , KITred30              /**< RGB <- ( 226, 187, 190 ), rgb <- ( 0.888, 0.735, 0.747 ) */
            , KITred15              /**< RGB <- ( 241, 221, 223 ), rgb <- ( 0.944, 0.867, 0.873 ) */
            // KITlilac
            , KITlilac              /**< RGB <- ( 160,   0, 120 ), rgb <- ( 0.627, 0    , 0.47  ) */
            , KITlilac70            /**< RGB <- ( 188,  77, 160 ), rgb <- ( 0.739, 0.3  , 0.629 ) */
            , KITlilac50            /**< RGB <- ( 207, 128, 187 ), rgb <- ( 0.813, 0.5  , 0.735 ) */
            , KITlilac30            /**< RGB <- ( 226, 179, 214 ), rgb <- ( 0.888, 0.7  , 0.841 ) */
            , KITlilac15            /**< RGB <- ( 241, 217, 235 ), rgb <- ( 0.944, 0.85 , 0.92  ) */
            // KITcyanblue
            , KITcyanblue           /**< RGB <- (  80, 170, 230 ), rgb <- ( 0.313, 0.666, 0.901 ) */
            , KITcyanblue70         /**< RGB <- ( 132, 195, 237 ), rgb <- ( 0.519, 0.766, 0.931 ) */
            , KITcyanblue50         /**< RGB <- ( 167, 212, 242 ), rgb <- ( 0.656, 0.833, 0.95  ) */
            , KITcyanblue30         /**< RGB <- ( 202, 230, 247 ), rgb <- ( 0.794, 0.9  , 0.97  ) */
            , KITcyanblue15         /**< RGB <- ( 229, 242, 251 ), rgb <- ( 0.897, 0.95 , 0.985 ) */
            // KITseablue
            , KITseablue            /**< RGB <- (  50,  80, 140 ), rgb <- ( 0.196, 0.313, 0.549 ) */
            , KITseablue70          /**< RGB <- ( 111, 132, 174 ), rgb <- ( 0.437, 0.519, 0.684 ) */
            , KITseablue50          /**< RGB <- ( 152, 167, 197 ), rgb <- ( 0.598, 0.656, 0.774 ) */
            , KITseablue30          /**< RGB <- ( 193, 202, 220 ), rgb <- ( 0.758, 0.794, 0.864 ) */
            , KITseablue15          /**< RGB <- ( 224, 229, 238 ), rgb <- ( 0.879, 0.897, 0.932 ) */
            // 
            // Thesis Colors
            , THESISblue            /**< RGB <- (  86, 151, 197 ), rgb <- ( 0.337, 0.592, 0.773 ) */
            , THESISblue_dark       /**< RGB <- (  54, 120, 167 ), rgb <- ( 0.212, 0.471, 0.655 ) */
            , THESISblue_light      /**< RGB <- ( 125, 181, 221 ), rgb <- ( 0.490, 0.710, 0.867 ) */
            , THESISblue_vlight     /**< RGB <- ( 222, 239, 252 ), rgb <- ( 0.871, 0.937, 0.988 ) */
            //
            , THESISred             /**< RGB <- ( 198,  91, 101 ), rgb <- ( 0.776, 0.357, 0.396 ) */
            , THESISred_dark        /**< RGB <- ( 169,  60,  69 ), rgb <- ( 0.663, 0.235, 0.271 ) */
            , THESISred_light       /**< RGB <- ( 221, 128, 136 ), rgb <- ( 0.867, 0.502, 0.533 ) */
            , THESISred_vlight      /**< RGB <- ( 251, 222, 224 ), rgb <- ( 0.984, 0.871, 0.878 ) */
            //
            , THESISgreen           /**< RGB <- (  86, 195,  60 ), rgb <- ( 0.337, 0.765, 0.235 ) */
            , THESISgreen_dark      /**< RGB <- (  68, 156,  47 ), rgb <- ( 0.267, 0.612, 0.184 ) */
            , THESISgreen_light     /**< RGB <- ( 112, 222,  87 ), rgb <- ( 0.443, 0.871, 0.341 ) */
            , THESISgreen_vlight    /**< RGB <- ( 181, 251, 164 ), rgb <- ( 0.710, 0.984, 0.643 ) */
            //
            , THESISyellow          /**< RGB <- ( 206, 168,  67 ), rgb <- ( 0.808, 0.659, 0.263 ) */
            , THESISyellow_dark     /**< RGB <- ( 170, 135,  46 ), rgb <- ( 0.667, 0.529, 0.180 ) */
            , THESISyellow_light    /**< RGB <- ( 229, 195, 105 ), rgb <- ( 0.898, 0.765, 0.412 ) */
            , THESISyellow_vlight   /**< RGB <- ( 253, 238, 198 ), rgb <- ( 0.992, 0.933, 0.776 ) */
            //
            , THESISblack           /**< RGB <- (   0,   0,   0 ), rgb <- ( 0    , 0    , 0     ) */
            , THESISblack70         /**< RGB <- (  77,  77,  77 ), rgb <- ( 0.3  , 0.3  , 0.3   ) */
            , THESISblack50         /**< RGB <- ( 128, 128, 128 ), rgb <- ( 0.5  , 0.5  , 0.5   ) */
            , THESISblack30         /**< RGB <- ( 179, 179, 179 ), rgb <- ( 0.7  , 0.7  , 0.7   ) */
            , THESISblack15         /**< RGB <- ( 217, 217, 217 ), rgb <- ( 0.85 , 0.85 , 0.85  ) */
            , THESISblack7          /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            // OGDF
            , Goldenrod             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.855, 0.647, 0.125 ) */
            , Gray                  /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.002, 0.002, 0.002 ) */
            , Green                 /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0    , 0.002, 0     ) */
            , Greenyellow           /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Grey                  /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Honeydew              /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Hotpink               /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Indianred             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Indigo                /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Ivory                 /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Khaki                 /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lavender              /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lavenderblush         /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lawngreen             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lemonchiffon          /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lightblue             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lightcoral            /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lightcyan             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lightgoldenrodyellow  /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lightgray             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lightgreen            /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lightgrey             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lightpink             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lightsalmon           /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lightseagreen         /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lightskyblue          /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lightslategray        /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lightslategrey        /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lightsteelblue        /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lightyellow           /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Lime                  /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Limegreen             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Linen                 /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Magenta               /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Maroon                /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Mediumaquamarine      /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Mediumblue            /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Mediumorchid          /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Mediumpurple          /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Mediumseagreen        /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Mediumslateblue       /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Mediumspringgreen     /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Mediumturquoise       /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Mediumvioletred       /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Midnightblue          /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Mintcream             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Mistyrose             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Moccasin              /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Navajowhite           /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Navy                  /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Oldlace               /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Olive                 /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Olivedrab             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Orange                /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Orangered             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Orchid                /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Palegoldenrod         /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Palegreen             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Paleturquoise         /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Palevioletred         /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Papayawhip            /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Peachpuff             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Peru                  /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Pink                  /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Plum                  /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Powderblue            /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Purple                /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Red                   /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Rosybrown             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Royalblue             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Saddlebrown           /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Salmon                /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Sandybrown            /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Seagreen              /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Seashell              /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Sienna                /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Silver                /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Skyblue               /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Slateblue             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Slategray             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Slategrey             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Snow                  /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Springgreen           /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Steelblue             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Tan                   /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Teal                  /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Thistle               /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Tomato                /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Turquoise             /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Violet                /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Wheat                 /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , White                 /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Whitesmoke            /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Yellow                /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
            , Yellowgreen           /**< RGB <- ( 235, 235, 235 ), rgb <- ( 0.92 , 0.92 , 0.92  ) */
        };
    public:        
        // Color ( Type::ubyte red = 0, Type::ubyte green = 0, Type::ubyte blue = 0, Type::ubyte alpha = 0 ) 
        // : red_(red), green_(green), blue_(blue), alpha_(alpha) {}

        Color ( Types::real red = 0.0, Types::real green = 0.0, Types::real blue = 0, Types::real alpha = 0 ) 
        : red_(red), green_(green), blue_(blue), alpha_(alpha) {
            if ( red_ > 1) {
                red_ = red_ / 255;
            }
            if ( green_ > 1) {
                green_ = green_ / 255;
            }
            if ( blue_ > 1) {
                blue_ = blue_ / 255;
            }
        }

        Color(Color::Name name);
        
        ~Color(){}


        bool operator== ( const Color& rhs ) {
            return Red() == rhs.Red() && Green() == rhs.Green() && Blue() == rhs.Blue();
        }

        bool operator!= ( const Color& rhs ) {
            return !operator==(rhs);
        }

        friend std::ostream& operator<<(std::ostream& os, const Name color ) {
            switch ( color ) {
                case Name::KITgreen:      os << "KITgreen";   break;
                case Name::KITgreen70:    os << "KITgreen70"; break;
                case Name::KITgreen50:    os << "KITgreen50"; break;
                case Name::KITgreen30:    os << "KITgreen30"; break;
                case Name::KITgreen15:    os << "KITgreen15"; break;

                case Name::KITblue:       os << "KITgreen";   break;
                case Name::KITblue70:     os << "KITgreen70"; break;
                case Name::KITblue50:     os << "KITgreen50"; break;
                case Name::KITblue30:     os << "KITgreen30"; break;
                case Name::KITblue15:     os << "KITgreen15"; break;

                case Name::KITblack:      os << "KITblack";   break;
                case Name::KITblack70:    os << "KITblack70"; break;
                case Name::KITblack50:    os << "KITblack50"; break;
                case Name::KITblack32:    os << "KITblack32"; break;
                case Name::KITblack31:    os << "KITblack31"; break;
                case Name::KITblack30:    os << "KITblack30"; break;
                case Name::KITblack29:    os << "KITblack29"; break;
                case Name::KITblack28:    os << "KITblack28"; break;
                case Name::KITblack27:    os << "KITblack27"; break;
                case Name::KITblack26:    os << "KITblack26"; break;
                case Name::KITblack25:    os << "KITblack25"; break;
                case Name::KITblack24:    os << "KITblack24"; break;
                case Name::KITblack23:    os << "KITblack23"; break;
                case Name::KITblack22:    os << "KITblack22"; break;
                case Name::KITblack21:    os << "KITblack21"; break;
                case Name::KITblack20:    os << "KITblack20"; break;
                case Name::KITblack19:    os << "KITblack19"; break;
                case Name::KITblack18:    os << "KITblack18"; break;
                case Name::KITblack17:    os << "KITblack17"; break;
                case Name::KITblack16:    os << "KITblack16"; break;
                case Name::KITblack15:    os << "KITblack15"; break;
                case Name::KITblack14:    os << "KITblack14"; break;
                case Name::KITblack13:    os << "KITblack13"; break;
                case Name::KITblack12:    os << "KITblack12"; break;
                case Name::KITblack11:    os << "KITblack11"; break;
                case Name::KITblack10:    os << "KITblack10"; break;
                case Name::KITblack09:    os << "KITblack09"; break;
                case Name::KITblack08:    os << "KITblack08"; break;
                case Name::KITblack07:    os << "KITblack07"; break;
                case Name::KITblack06:    os << "KITblack06"; break;
                case Name::KITblack05:    os << "KITblack05"; break;
                case Name::KITblack04:    os << "KITblack04"; break;
                case Name::KITblack03:    os << "KITblack03"; break;
                case Name::KITblack02:    os << "KITblack02"; break;
                case Name::KITblack01:    os << "KITblack01"; break;

                case Name::KITpalegreen:   os << "KITpalegreen";   break;
                case Name::KITpalegreen70: os << "KITpalegreen70"; break;
                case Name::KITpalegreen50: os << "KITpalegreen50"; break;
                case Name::KITpalegreen30: os << "KITpalegreen30"; break;
                case Name::KITpalegreen15: os << "KITpalegreen15"; break;

                case Name::KITyellow:       os << "KITyellow";   break;
                case Name::KITyellow70:     os << "KITyellow70"; break;
                case Name::KITyellow50:     os << "KITyellow50"; break;
                case Name::KITyellow30:     os << "KITyellow30"; break;
                case Name::KITyellow15:     os << "KITyellow15"; break;

                case Name::KITorange:       os << "KITorange";   break;
                case Name::KITorange70:     os << "KITorange70"; break;
                case Name::KITorange50:     os << "KITorange50"; break;
                case Name::KITorange30:     os << "KITorange30"; break;
                case Name::KITorange15:     os << "KITorange15"; break;

                case Name::KITbrown:        os << "KITbrown";   break;
                case Name::KITbrown70:      os << "KITbrown70"; break;
                case Name::KITbrown50:      os << "KITbrown50"; break;
                case Name::KITbrown30:      os << "KITbrown30"; break;
                case Name::KITbrown15:      os << "KITbrown15"; break;

                case Name::KITred:          os << "KITred";   break;
                case Name::KITred70:        os << "KITred70"; break;
                case Name::KITred50:        os << "KITred50"; break;
                case Name::KITred30:        os << "KITred30"; break;
                case Name::KITred15:        os << "KITred15"; break;

                case Name::KITlilac:        os << "KITlilac";   break;
                case Name::KITlilac70:      os << "KITlilac70"; break;
                case Name::KITlilac50:      os << "KITlilac50"; break;
                case Name::KITlilac30:      os << "KITlilac30"; break;
                case Name::KITlilac15:      os << "KITlilac15"; break;

                case Name::KITcyanblue:     os << "KITcyanblue";   break;
                case Name::KITcyanblue70:   os << "KITcyanblue70"; break;
                case Name::KITcyanblue50:   os << "KITcyanblue50"; break;
                case Name::KITcyanblue30:   os << "KITcyanblue30"; break;
                case Name::KITcyanblue15:   os << "KITcyanblue15"; break;

                case Name::KITseablue:      os << "KITseablue";   break;
                case Name::KITseablue70:    os << "KITseablue70"; break;
                case Name::KITseablue50:    os << "KITseablue50"; break;
                case Name::KITseablue30:    os << "KITseablue30"; break;
                case Name::KITseablue15:    os << "KITseablue15"; break;

                case Name::THESISblue:          os << "THESISblue";         break;
                case Name::THESISblue_dark:     os << "THESISblue_dark";    break;
                case Name::THESISblue_light:    os << "THESISblue_light";   break;
                case Name::THESISblue_vlight:   os << "THESISblue_vlight"; break;

                case Name::THESISred:           os << "THESISred";   break;
                case Name::THESISred_dark:      os << "THESISred_dark"; break;
                case Name::THESISred_light:     os << "THESISred_light"; break;
                case Name::THESISred_vlight:    os << "THESISred_vlight"; break;

                case Name::THESISgreen:         os << "THESISgreen";   break;
                case Name::THESISgreen_dark:    os << "THESISgreen_dark"; break;
                case Name::THESISgreen_light:   os << "THESISgreen_light"; break;
                case Name::THESISgreen_vlight:  os << "THESISgreen_vlight"; break;

                case Name::THESISyellow:        os << "THESISyellow";   break;
                case Name::THESISyellow_dark:   os << "THESISyellow_dark"; break;
                case Name::THESISyellow_light:  os << "THESISyellow_light"; break;
                case Name::THESISyellow_vlight: os << "THESISyellow_vlight"; break;

                case Name::THESISblack:     os << "THESISblack";   break;
                case Name::THESISblack70:   os << "THESISblack70"; break;
                case Name::THESISblack50:   os << "THESISblack50"; break;
                case Name::THESISblack30:   os << "THESISblack30"; break;
                case Name::THESISblack15:   os << "THESISblack15"; break;
                case Name::THESISblack7:    os << "THESISblack7";  break;
                default:                    os << "unknown COLOR"; break;
            }
            return os;
        }

        

        ///@Name Getter and setter
        ///@{
        // RGB color model
            // Arithmetic
            Types::real   red()   const { return red_; }
            Types::real & red()         { return red_; }

            Types::real   green() const { return green_; }
            Types::real & green()       { return green_; }

            Types::real   blue()  const { return blue_; }
            Types::real & blue()        { return blue_; }

            // Digital 8-bit per channel
            Types::ubyte Red()   const;
            void   Red( Types::ubyte red);

            Types::ubyte Green() const;
            void Green( Types::ubyte green);

            Types::ubyte Blue()  const;
            void Blue( Types::ubyte blue );
        ///@}

        std::string Hexadecimal();
    private:
        Types::real    red_;
        Types::real    green_;
        Types::real    blue_;
        Types::real    alpha_;
}; //Color

} // egoa

#endif // EGOA__IO__COLOR_HPP

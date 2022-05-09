#pragma once

#include "font_8x8ASCII.h"
#include "Display.h"

#include "vector"

namespace SmartGlasses{

    template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
    class Font{
    public:
        static constexpr Font<unsigned char,CHAR_WIDTH,NB_ASCII_CHARS> ASCII8x8 = Font(font8x8_basic);
        
        /**
         * @brief Adds the pixel pairs indicating which pixels are set for the char c using font f, in the vector v
         * 
         * @param f (Font&) reference to the font used
         * @param s (std::string&) reference to string
         * @param v (std::vector<pixel_pair_t>&) vector referencne where we are to put the output
         */
        static void getPixelPairs(Font<CHAR_T,CHAR_WIDTH,NB_CHARS>& f, char& c, std::vector<pixel_pair_t>& v){getPixelPairsWithOffset(f,c,v,0,0);};
        /**
         * @brief Similarly as getPixelPairsWithOffset. If an offset is  wanted, it has to be specified as part of the Drawable object
         * 
         * @see getPixelPairsWithOffset
         */
        static void getPixelPairs(Font<CHAR_T,CHAR_WIDTH,NB_CHARS>& f, std::string& s, std::vector<pixel_pair_t>&v);
        

    private: 
        constexpr Font(CHAR_T (&font)[NB_CHARS][CHAR_WIDTH]):font(std::move(font)){};
        CHAR_T font[NB_CHARS][CHAR_WIDTH];

        /**
         * @brief Adds the pixel pairs indicating which pixels are set for the char c using font f, in the vector v
         * Note: Here, offsets are allowed to take into account newLines and char spacing;
         * 
         * @param f (Font&) reference to the font used
         * @param s (std::string&) reference to string
         * @param v (std::vector<pixel_pair_t>&) vector referencne where we are to put the output
         * @param offsetX the x axis offset
         * @param offsetY the y axis offset
         */
        static void getPixelPairsWithOffset(Font<CHAR_T,CHAR_WIDTH,NB_CHARS>& f, char& c, std::vector<pixel_pair_t>& v, unsigned char offsetX, unsigned char offsetY);
    };

};
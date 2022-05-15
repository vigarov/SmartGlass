#pragma once

#include "font_8x8ASCII.h"
#include "Display.h"
#include <memory>
#include <unordered_set>

namespace SmartGlasses{
    template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
    class Font{
    public:
        /**
         * @brief Adds in the unordered_set v the pixel pairs indicating which pixels are unordered_set for the char c using font f
         * 
         * @param f (Font&) reference to the font used
         * @param s (std::string&) reference to string
         * @param v (std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction>&) unordered_set referencne where we are to put the output
         */
        static void getPixelPairs(const Font<CHAR_T,CHAR_WIDTH,NB_CHARS>& f,const char& c, std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction>& v){getPixelPairsWithOffset(f,c,v,0,0);}
        /**
         * @brief Similarly as getPixelPairsWithOffset. If an offset is  wanted, it has to be specified as part of the Drawable object
         * 
         * @see getPixelPairsWithOffset
         */
        static void getPixelPairs(const Font<CHAR_T,CHAR_WIDTH,NB_CHARS>& f,const std::string& s, std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction>&v);
        
        Font(Font const&) = delete; 
        void operator=(Font const&) = delete; 
        
        Font(const CHAR_T (&font)[NB_CHARS][CHAR_WIDTH]):font(font){}
    private: 
        const CHAR_T (&font)[NB_CHARS][CHAR_WIDTH];

        /**
         * @brief Adds the pixel pairs indicating which pixels are unordered_set for the char c using font f, in the unordered_set v
         * Note: Here, offsets are allowed to take into account newLines and char spacing;
         * 
         * @param f (Font&) reference to the font used
         * @param s (std::string&) reference to string
         * @param v (std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction>&) unordered_set referencne where we are to put the output
         * @param offsetX the x axis offset
         * @param offsetY the y axis offset
         */
        static void getPixelPairsWithOffset(const Font<CHAR_T,CHAR_WIDTH,NB_CHARS>& f,const char& c, std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction>& v, unsigned char offsetX, unsigned char offsetY);
    };
    
    static const Font<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS> ASCII8x8 = Font(std::move(font8x8_basic));

};
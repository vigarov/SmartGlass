#pragma once

#include "Content.h"
#include "string.h"
#include "Font.h"
#include <vector>

namespace SmartGlasses{
    template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
    class Text : public Content {
    public:
        Text(const std::string& s, bool overwrites = true, pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 1) : Text(s,overwrites,&ASCII8x8,std::move(offsets),animate,priority) {}

        Text(const std::string& s, bool overwrites ,const Font<CHAR_T,CHAR_WIDTH,NB_CHARS>* font = ASCII8x8, pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 1);
    
        /**
         * @brief Changes the current displayed string
         * Already calls update(), no need to call it again
         * @param newS the newString to display
         */ 
        void changeString(const std::string &newS);

        static Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS> textWithDefaultFontFrom(std::string s, bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 1){
            return SmartGlasses::Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>(s,overwrites,offsets,animate,priority);
        }
    protected:
        std::unique_ptr<pixels_set_t> createPixels();
    private:
        std::string m_s = "";
        const Font<CHAR_T,CHAR_WIDTH,NB_CHARS> *m_f;
    };
};
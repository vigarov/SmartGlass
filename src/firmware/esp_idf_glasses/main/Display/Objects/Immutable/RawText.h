#pragma once
#include "Content.h"
#include "font.h"

namespace SmartGlasses{

    class RawText : public ConstantContent{
    public:
        RawText(const std::string& s) : RawText(s,ASCII8x8,false,{0,0},1){}

        template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
        RawText(const std::string& s, const Font<CHAR_T,CHAR_WIDTH,NB_CHARS>& font = ASCII8x8, bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char priority = 1);
    protected:
        void updatePixels() override;
    };
};
#pragma once
#include "Content.h"
#include "font.h"

namespace SmartGlasses{

    class RawText : public ConstantContent{
    public:
        RawText(const std::string& s, bool overwrites=false, pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 1) : RawText(s,ASCII8x8,overwrites,std::move(offsets),animate,priority) {}

        template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
        RawText(const std::string& s, const Font<CHAR_T,CHAR_WIDTH,NB_CHARS>& font = ASCII8x8, bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 1);
    };
};
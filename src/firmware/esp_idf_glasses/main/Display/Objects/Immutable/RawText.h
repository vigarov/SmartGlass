#pragma once
#include "Content.h"
#include "font.h"

namespace SmartGlasses{

    class RawText : public ConstantContent{
    public:
        RawText(const std::string& s, bool overwrites=false, pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 1) :ConstantContent("Constant <"+s+">", overwrites, offsets,priority),m_string(s){}

        std::unique_ptr<pixels_set_t> createPixels()override;
    private:
        const std::string m_string;
    };
};
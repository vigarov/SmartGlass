#pragma once
#include "Content.h"

namespace SmartGlasses{

    #define BLEICON_WIDTH 6
    class BLEIcon : public Content{
    public:
        BLEIcon(std::string name, bool overwrites = true,pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 1 ) :
            Content(name,overwrites,offsets,animate,priority){}
    protected:
        std::unique_ptr<pixels_set_t> createPixels();
    };
};
#pragma once

#include <vector>

namespace SmartGlasses{
    
    /**
     * @brief a pair of pixels
     * could also use std::pair<unsigned char> instead, but this is clearer
     */
    struct __attribute__((packed)) pixel_pair_t{
        unsigned char x;
        unsigned char y;
    };

    /**
     * @brief A drawable object, defined as a set of pixels at an offset
     * 
     */
    class Drawable{
    public:
        std::vector<pixel_pair_t> pixels;
        unsigned char offsetX=0;
        unsigned char offsetY=0;
        unsigned char overwrite =1;
    };

    /**
     * @brief the type of the pending object we would like to display
     * 
     */
    struct display_t{
        // display_t(unsigned char p, Drawable&& d) : priority(p),object(std::move(d)){}
        unsigned char priority; //TODO: can make it a bitfield to save... one byte if necessary
        Drawable object;
    };
    
    
};
#pragma once

#include <unordered_set>

namespace SmartGlasses{
    
    /**
     * @brief a pair of pixels
     * could also use std::pair<unsigned char> instead, but this is clearer
     */
    struct __attribute__((packed,aligned(2))) pixel_pair_t{
        unsigned char x;
        unsigned char y;
        bool operator==(pixel_pair_t const & rhs) const {
                return x==rhs.x && y==rhs.y;
        }
        struct HashFunction
        {
            size_t operator()(const pixel_pair_t& pp) const
            {
                size_t x = static_cast<size_t>(pp.x);
                size_t y = static_cast<size_t>(pp.y);
                return x<<8|y; //This way, no collisions can happen over our input space
            }
        };
    };

    struct __attribute__((packed,aligned(4))) border_t{
        pixel_pair_t topLeft;
        pixel_pair_t bottomRight;
    };

    /**
     * @brief A drawable object, defined as a unordered_set of pixels at an offunordered_set
     * 
     */
    class Drawable{
    public:
        std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction> pixels ; 
        std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction> border ; //must have pixels \cap border == 0. border = 0 <=> don't overwrite
        pixel_pair_t offsets = {0,0};
    };

    /**
     * @brief the type of the pending object we would like to display
     * 
     */
    struct display_t{
        // display_t(unsigned char p, Drawable&& d) : priority(p),object(std::move(d)){}
        unsigned char priority{}; //TODO: can make it a bitfield to save... one byte if necessary
        Drawable object;
    };
    
    
};
#pragma once

#include "Content.h"

namespace SmartGlasses{

    class StraightArrow : public ConstantContent{
    public:
        StraightArrow(const std::string& name, bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority) {}
        std::unique_ptr<pixels_set_t> createPixels(){
            auto pixels = std::make_unique<pixels_set_t>();
            pixels->insert(std::move(pixel_pair_t{7, 0})); pixels->insert(std::move(pixel_pair_t{8, 0})); pixels->insert(std::move(pixel_pair_t{9, 0})); 
            pixels->insert(std::move(pixel_pair_t{6, 1})); pixels->insert(std::move(pixel_pair_t{7, 1})); pixels->insert(std::move(pixel_pair_t{9, 1})); pixels->insert(std::move(pixel_pair_t{10, 1})); 
            pixels->insert(std::move(pixel_pair_t{5, 2})); pixels->insert(std::move(pixel_pair_t{6, 2})); pixels->insert(std::move(pixel_pair_t{8, 2})); pixels->insert(std::move(pixel_pair_t{10, 2})); pixels->insert(std::move(pixel_pair_t{11, 2})); 
            pixels->insert(std::move(pixel_pair_t{4, 3})); pixels->insert(std::move(pixel_pair_t{5, 3})); pixels->insert(std::move(pixel_pair_t{7, 3})); pixels->insert(std::move(pixel_pair_t{8, 3})); pixels->insert(std::move(pixel_pair_t{9, 3})); pixels->insert(std::move(pixel_pair_t{11, 3})); pixels->insert(std::move(pixel_pair_t{12, 3})); 
            pixels->insert(std::move(pixel_pair_t{3, 4})); pixels->insert(std::move(pixel_pair_t{4, 4})); pixels->insert(std::move(pixel_pair_t{6, 4})); pixels->insert(std::move(pixel_pair_t{7, 4})); pixels->insert(std::move(pixel_pair_t{8, 4})); pixels->insert(std::move(pixel_pair_t{9, 4})); pixels->insert(std::move(pixel_pair_t{10, 4})); pixels->insert(std::move(pixel_pair_t{12, 4})); pixels->insert(std::move(pixel_pair_t{13, 4})); 
            pixels->insert(std::move(pixel_pair_t{2, 5})); pixels->insert(std::move(pixel_pair_t{3, 5})); pixels->insert(std::move(pixel_pair_t{5, 5})); pixels->insert(std::move(pixel_pair_t{6, 5})); pixels->insert(std::move(pixel_pair_t{7, 5})); pixels->insert(std::move(pixel_pair_t{9, 5})); pixels->insert(std::move(pixel_pair_t{10, 5})); pixels->insert(std::move(pixel_pair_t{11, 5})); pixels->insert(std::move(pixel_pair_t{13, 5})); pixels->insert(std::move(pixel_pair_t{14, 5})); 
            pixels->insert(std::move(pixel_pair_t{1, 6})); pixels->insert(std::move(pixel_pair_t{2, 6})); pixels->insert(std::move(pixel_pair_t{4, 6})); pixels->insert(std::move(pixel_pair_t{5, 6})); pixels->insert(std::move(pixel_pair_t{7, 6})); pixels->insert(std::move(pixel_pair_t{9, 6})); pixels->insert(std::move(pixel_pair_t{11, 6})); pixels->insert(std::move(pixel_pair_t{12, 6})); pixels->insert(std::move(pixel_pair_t{14, 6})); pixels->insert(std::move(pixel_pair_t{15, 6})); 
            pixels->insert(std::move(pixel_pair_t{0, 7})); pixels->insert(std::move(pixel_pair_t{1, 7})); pixels->insert(std::move(pixel_pair_t{3, 7})); pixels->insert(std::move(pixel_pair_t{4, 7})); pixels->insert(std::move(pixel_pair_t{7, 7})); pixels->insert(std::move(pixel_pair_t{9, 7})); pixels->insert(std::move(pixel_pair_t{12, 7})); pixels->insert(std::move(pixel_pair_t{13, 7})); pixels->insert(std::move(pixel_pair_t{15, 7})); pixels->insert(std::move(pixel_pair_t{16, 7})); 
            pixels->insert(std::move(pixel_pair_t{0, 8})); pixels->insert(std::move(pixel_pair_t{2, 8})); pixels->insert(std::move(pixel_pair_t{3, 8})); pixels->insert(std::move(pixel_pair_t{7, 8})); pixels->insert(std::move(pixel_pair_t{9, 8})); pixels->insert(std::move(pixel_pair_t{13, 8})); pixels->insert(std::move(pixel_pair_t{14, 8})); pixels->insert(std::move(pixel_pair_t{16, 8})); 
            pixels->insert(std::move(pixel_pair_t{7, 9})); pixels->insert(std::move(pixel_pair_t{8, 9})); pixels->insert(std::move(pixel_pair_t{9, 9})); 
            pixels->insert(std::move(pixel_pair_t{7, 10})); pixels->insert(std::move(pixel_pair_t{8, 10})); pixels->insert(std::move(pixel_pair_t{9, 10})); 
            pixels->insert(std::move(pixel_pair_t{7, 11})); pixels->insert(std::move(pixel_pair_t{9, 11})); 
            pixels->insert(std::move(pixel_pair_t{7, 12})); pixels->insert(std::move(pixel_pair_t{9, 12})); 
            pixels->insert(std::move(pixel_pair_t{7, 13})); pixels->insert(std::move(pixel_pair_t{9, 13})); 
            pixels->insert(std::move(pixel_pair_t{7, 14})); pixels->insert(std::move(pixel_pair_t{8, 14})); pixels->insert(std::move(pixel_pair_t{9, 14})); 
            pixels->insert(std::move(pixel_pair_t{7, 15})); pixels->insert(std::move(pixel_pair_t{8, 15})); pixels->insert(std::move(pixel_pair_t{9, 15})); 
            pixels->insert(std::move(pixel_pair_t{7, 16})); pixels->insert(std::move(pixel_pair_t{9, 16})); 
            pixels->insert(std::move(pixel_pair_t{7, 17})); pixels->insert(std::move(pixel_pair_t{9, 17})); 
            pixels->insert(std::move(pixel_pair_t{7, 18})); pixels->insert(std::move(pixel_pair_t{9, 18})); 
            pixels->insert(std::move(pixel_pair_t{7, 19})); pixels->insert(std::move(pixel_pair_t{8, 19})); pixels->insert(std::move(pixel_pair_t{9, 19})); 
            return std::move(pixels);
        }
    };
};
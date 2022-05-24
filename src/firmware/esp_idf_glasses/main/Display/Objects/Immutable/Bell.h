#pragma once
#include "Content.h"

namespace SmartGlasses{

    #define BELL_WIDTH 7

    class Bell: public ConstantContent{
    public:
        Bell(const std::string& name, bool overwrites, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority) {}
        std::unique_ptr<pixels_set_t> createPixels(){
            auto pixels = std::make_unique<pixels_set_t>();
            pixels->insert(std::move(pixel_pair_t{4, 1})); 
            pixels->insert(std::move(pixel_pair_t{3, 2})); pixels->insert(std::move(pixel_pair_t{4, 2})); pixels->insert(std::move(pixel_pair_t{5, 2})); 
            pixels->insert(std::move(pixel_pair_t{2, 3})); pixels->insert(std::move(pixel_pair_t{6, 3})); 
            pixels->insert(std::move(pixel_pair_t{2, 4})); pixels->insert(std::move(pixel_pair_t{6, 4})); 
            pixels->insert(std::move(pixel_pair_t{1, 5})); pixels->insert(std::move(pixel_pair_t{7, 5})); 
            pixels->insert(std::move(pixel_pair_t{1, 6})); pixels->insert(std::move(pixel_pair_t{7, 6})); 
            pixels->insert(std::move(pixel_pair_t{1, 7})); pixels->insert(std::move(pixel_pair_t{2, 7})); pixels->insert(std::move(pixel_pair_t{3, 7})); pixels->insert(std::move(pixel_pair_t{4, 7})); pixels->insert(std::move(pixel_pair_t{5, 7})); pixels->insert(std::move(pixel_pair_t{6, 7})); pixels->insert(std::move(pixel_pair_t{7, 7})); 
            pixels->insert(std::move(pixel_pair_t{3, 8})); pixels->insert(std::move(pixel_pair_t{4, 8})); pixels->insert(std::move(pixel_pair_t{5, 8})); 
            pixels->insert(std::move(pixel_pair_t{4, 9})); 
            return std::move(pixels);
        }
    };
};
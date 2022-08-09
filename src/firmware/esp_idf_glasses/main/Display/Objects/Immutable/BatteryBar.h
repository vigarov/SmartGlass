#pragma once

#include "Content.h"
namespace SmartGlasses{

    #define BATTERY_BAR_WIDTH 2

    class BatteryBar : public ConstantContent{
    public:
        BatteryBar(const std::string& name, bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority) {}
        std::unique_ptr<pixels_set_t> createPixels(){
            auto pixels = std::make_unique<pixels_set_t>();
            pixels->insert(std::move(pixel_pair_t{0, 0})); pixels->insert(std::move(pixel_pair_t{1, 0})); 
            pixels->insert(std::move(pixel_pair_t{0, 1})); pixels->insert(std::move(pixel_pair_t{1, 1})); 
            pixels->insert(std::move(pixel_pair_t{0, 2})); pixels->insert(std::move(pixel_pair_t{1, 2})); 
            pixels->insert(std::move(pixel_pair_t{0, 3})); pixels->insert(std::move(pixel_pair_t{1, 3})); 
            pixels->insert(std::move(pixel_pair_t{0, 4})); pixels->insert(std::move(pixel_pair_t{1, 4})); 
            pixels->insert(std::move(pixel_pair_t{0, 5})); pixels->insert(std::move(pixel_pair_t{1, 5})); 
            pixels->insert(std::move(pixel_pair_t{0, 6})); pixels->insert(std::move(pixel_pair_t{1, 6})); 
            return std::move(pixels);
        }
    };
};
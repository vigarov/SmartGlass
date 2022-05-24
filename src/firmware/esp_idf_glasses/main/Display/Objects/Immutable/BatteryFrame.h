#pragma once

#include "Content.h"

namespace SmartGlasses{

    #define BATTERYFRAME_WIDTH 16

    class BatteryFrame : public ConstantContent{
    public:
        BatteryFrame(const std::string& name, bool overwrites = false, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority){}

        std::unique_ptr<pixels_set_t> createPixels(){
            auto pixels = std::make_unique<pixels_set_t>();
            pixels->insert(std::move(pixel_pair_t{2, 1})); pixels->insert(std::move(pixel_pair_t{3, 1})); pixels->insert(std::move(pixel_pair_t{4, 1})); pixels->insert(std::move(pixel_pair_t{5, 1})); pixels->insert(std::move(pixel_pair_t{6, 1})); pixels->insert(std::move(pixel_pair_t{7, 1})); pixels->insert(std::move(pixel_pair_t{8, 1})); pixels->insert(std::move(pixel_pair_t{9, 1})); pixels->insert(std::move(pixel_pair_t{10, 1})); pixels->insert(std::move(pixel_pair_t{11, 1})); pixels->insert(std::move(pixel_pair_t{12, 1})); pixels->insert(std::move(pixel_pair_t{13, 1})); pixels->insert(std::move(pixel_pair_t{14, 1})); pixels->insert(std::move(pixel_pair_t{15, 1})); pixels->insert(std::move(pixel_pair_t{16, 1})); 
            pixels->insert(std::move(pixel_pair_t{2, 2})); pixels->insert(std::move(pixel_pair_t{16, 2})); 
            pixels->insert(std::move(pixel_pair_t{2, 3})); pixels->insert(std::move(pixel_pair_t{16, 3})); 
            pixels->insert(std::move(pixel_pair_t{2, 4})); pixels->insert(std::move(pixel_pair_t{16, 4})); 
            pixels->insert(std::move(pixel_pair_t{1, 5})); pixels->insert(std::move(pixel_pair_t{2, 5})); pixels->insert(std::move(pixel_pair_t{16, 5})); 
            pixels->insert(std::move(pixel_pair_t{1, 6})); pixels->insert(std::move(pixel_pair_t{2, 6})); pixels->insert(std::move(pixel_pair_t{16, 6})); 
            pixels->insert(std::move(pixel_pair_t{1, 7})); pixels->insert(std::move(pixel_pair_t{2, 7})); pixels->insert(std::move(pixel_pair_t{16, 7})); 
            pixels->insert(std::move(pixel_pair_t{1, 8})); pixels->insert(std::move(pixel_pair_t{2, 8})); pixels->insert(std::move(pixel_pair_t{16, 8})); 
            pixels->insert(std::move(pixel_pair_t{2, 9})); pixels->insert(std::move(pixel_pair_t{16, 9})); 
            pixels->insert(std::move(pixel_pair_t{2, 10})); pixels->insert(std::move(pixel_pair_t{16, 10})); 
            pixels->insert(std::move(pixel_pair_t{2, 11})); pixels->insert(std::move(pixel_pair_t{3, 11})); pixels->insert(std::move(pixel_pair_t{4, 11})); pixels->insert(std::move(pixel_pair_t{5, 11})); pixels->insert(std::move(pixel_pair_t{6, 11})); pixels->insert(std::move(pixel_pair_t{7, 11})); pixels->insert(std::move(pixel_pair_t{8, 11})); pixels->insert(std::move(pixel_pair_t{9, 11})); pixels->insert(std::move(pixel_pair_t{10, 11})); pixels->insert(std::move(pixel_pair_t{11, 11})); pixels->insert(std::move(pixel_pair_t{12, 11})); pixels->insert(std::move(pixel_pair_t{13, 11})); pixels->insert(std::move(pixel_pair_t{14, 11})); pixels->insert(std::move(pixel_pair_t{15, 11})); pixels->insert(std::move(pixel_pair_t{16, 11})); 
            return std::move(pixels);
        }
    };
}
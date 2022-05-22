#pragma once

#include "Content.h"
namespace SmartGlasses{

    #define BATTERY_BAR_WIDTH 2

    class BatteryBar : public ConstantContent{
    public:
        BatteryBar(const std::string& name, bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,priority) {
            m_pixels.insert(std::move(pixel_pair_t{0, 0})); m_pixels.insert(std::move(pixel_pair_t{1, 0})); 
            m_pixels.insert(std::move(pixel_pair_t{0, 1})); m_pixels.insert(std::move(pixel_pair_t{1, 1})); 
            m_pixels.insert(std::move(pixel_pair_t{0, 2})); m_pixels.insert(std::move(pixel_pair_t{1, 2})); 
            m_pixels.insert(std::move(pixel_pair_t{0, 3})); m_pixels.insert(std::move(pixel_pair_t{1, 3})); 
            m_pixels.insert(std::move(pixel_pair_t{0, 4})); m_pixels.insert(std::move(pixel_pair_t{1, 4})); 
            m_pixels.insert(std::move(pixel_pair_t{0, 5})); m_pixels.insert(std::move(pixel_pair_t{1, 5})); 
            m_pixels.insert(std::move(pixel_pair_t{0, 6})); m_pixels.insert(std::move(pixel_pair_t{1, 6})); 

        }
    };
};
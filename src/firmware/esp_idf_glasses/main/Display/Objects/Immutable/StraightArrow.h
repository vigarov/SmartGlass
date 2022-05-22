#pragma once

#include "Content.h"

namespace SmartGlasses{

    class StraightArrow : public ConstantContent{
    public:
        StraightArrow(const std::string& name, bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,priority) {
            m_pixels.insert(std::move(pixel_pair_t{7, 0})); m_pixels.insert(std::move(pixel_pair_t{8, 0})); m_pixels.insert(std::move(pixel_pair_t{9, 0})); 
            m_pixels.insert(std::move(pixel_pair_t{6, 1})); m_pixels.insert(std::move(pixel_pair_t{7, 1})); m_pixels.insert(std::move(pixel_pair_t{9, 1})); m_pixels.insert(std::move(pixel_pair_t{10, 1})); 
            m_pixels.insert(std::move(pixel_pair_t{5, 2})); m_pixels.insert(std::move(pixel_pair_t{6, 2})); m_pixels.insert(std::move(pixel_pair_t{8, 2})); m_pixels.insert(std::move(pixel_pair_t{10, 2})); m_pixels.insert(std::move(pixel_pair_t{11, 2})); 
            m_pixels.insert(std::move(pixel_pair_t{4, 3})); m_pixels.insert(std::move(pixel_pair_t{5, 3})); m_pixels.insert(std::move(pixel_pair_t{7, 3})); m_pixels.insert(std::move(pixel_pair_t{8, 3})); m_pixels.insert(std::move(pixel_pair_t{9, 3})); m_pixels.insert(std::move(pixel_pair_t{11, 3})); m_pixels.insert(std::move(pixel_pair_t{12, 3})); 
            m_pixels.insert(std::move(pixel_pair_t{3, 4})); m_pixels.insert(std::move(pixel_pair_t{4, 4})); m_pixels.insert(std::move(pixel_pair_t{6, 4})); m_pixels.insert(std::move(pixel_pair_t{7, 4})); m_pixels.insert(std::move(pixel_pair_t{8, 4})); m_pixels.insert(std::move(pixel_pair_t{9, 4})); m_pixels.insert(std::move(pixel_pair_t{10, 4})); m_pixels.insert(std::move(pixel_pair_t{12, 4})); m_pixels.insert(std::move(pixel_pair_t{13, 4})); 
            m_pixels.insert(std::move(pixel_pair_t{2, 5})); m_pixels.insert(std::move(pixel_pair_t{3, 5})); m_pixels.insert(std::move(pixel_pair_t{5, 5})); m_pixels.insert(std::move(pixel_pair_t{6, 5})); m_pixels.insert(std::move(pixel_pair_t{7, 5})); m_pixels.insert(std::move(pixel_pair_t{9, 5})); m_pixels.insert(std::move(pixel_pair_t{10, 5})); m_pixels.insert(std::move(pixel_pair_t{11, 5})); m_pixels.insert(std::move(pixel_pair_t{13, 5})); m_pixels.insert(std::move(pixel_pair_t{14, 5})); 
            m_pixels.insert(std::move(pixel_pair_t{1, 6})); m_pixels.insert(std::move(pixel_pair_t{2, 6})); m_pixels.insert(std::move(pixel_pair_t{4, 6})); m_pixels.insert(std::move(pixel_pair_t{5, 6})); m_pixels.insert(std::move(pixel_pair_t{7, 6})); m_pixels.insert(std::move(pixel_pair_t{9, 6})); m_pixels.insert(std::move(pixel_pair_t{11, 6})); m_pixels.insert(std::move(pixel_pair_t{12, 6})); m_pixels.insert(std::move(pixel_pair_t{14, 6})); m_pixels.insert(std::move(pixel_pair_t{15, 6})); 
            m_pixels.insert(std::move(pixel_pair_t{0, 7})); m_pixels.insert(std::move(pixel_pair_t{1, 7})); m_pixels.insert(std::move(pixel_pair_t{3, 7})); m_pixels.insert(std::move(pixel_pair_t{4, 7})); m_pixels.insert(std::move(pixel_pair_t{7, 7})); m_pixels.insert(std::move(pixel_pair_t{9, 7})); m_pixels.insert(std::move(pixel_pair_t{12, 7})); m_pixels.insert(std::move(pixel_pair_t{13, 7})); m_pixels.insert(std::move(pixel_pair_t{15, 7})); m_pixels.insert(std::move(pixel_pair_t{16, 7})); 
            m_pixels.insert(std::move(pixel_pair_t{0, 8})); m_pixels.insert(std::move(pixel_pair_t{2, 8})); m_pixels.insert(std::move(pixel_pair_t{3, 8})); m_pixels.insert(std::move(pixel_pair_t{7, 8})); m_pixels.insert(std::move(pixel_pair_t{9, 8})); m_pixels.insert(std::move(pixel_pair_t{13, 8})); m_pixels.insert(std::move(pixel_pair_t{14, 8})); m_pixels.insert(std::move(pixel_pair_t{16, 8})); 
            m_pixels.insert(std::move(pixel_pair_t{7, 9})); m_pixels.insert(std::move(pixel_pair_t{8, 9})); m_pixels.insert(std::move(pixel_pair_t{9, 9})); 
            m_pixels.insert(std::move(pixel_pair_t{7, 10})); m_pixels.insert(std::move(pixel_pair_t{8, 10})); m_pixels.insert(std::move(pixel_pair_t{9, 10})); 
            m_pixels.insert(std::move(pixel_pair_t{7, 11})); m_pixels.insert(std::move(pixel_pair_t{9, 11})); 
            m_pixels.insert(std::move(pixel_pair_t{7, 12})); m_pixels.insert(std::move(pixel_pair_t{9, 12})); 
            m_pixels.insert(std::move(pixel_pair_t{7, 13})); m_pixels.insert(std::move(pixel_pair_t{9, 13})); 
            m_pixels.insert(std::move(pixel_pair_t{7, 14})); m_pixels.insert(std::move(pixel_pair_t{8, 14})); m_pixels.insert(std::move(pixel_pair_t{9, 14})); 
            m_pixels.insert(std::move(pixel_pair_t{7, 15})); m_pixels.insert(std::move(pixel_pair_t{8, 15})); m_pixels.insert(std::move(pixel_pair_t{9, 15})); 
            m_pixels.insert(std::move(pixel_pair_t{7, 16})); m_pixels.insert(std::move(pixel_pair_t{9, 16})); 
            m_pixels.insert(std::move(pixel_pair_t{7, 17})); m_pixels.insert(std::move(pixel_pair_t{9, 17})); 
            m_pixels.insert(std::move(pixel_pair_t{7, 18})); m_pixels.insert(std::move(pixel_pair_t{9, 18})); 
            m_pixels.insert(std::move(pixel_pair_t{7, 19})); m_pixels.insert(std::move(pixel_pair_t{8, 19})); m_pixels.insert(std::move(pixel_pair_t{9, 19})); 
        }
    };
};
#pragma once
#include "Content.h"

namespace SmartGlasses{

    class Bell: public ConstantContent{
    public:
        Bell(const std::string& name, bool overwrites, pixel_pair_t offsets = {0,0}, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,priority) {        
            m_pixels.insert(std::move(pixel_pair_t{4, 1})); 
            m_pixels.insert(std::move(pixel_pair_t{3, 2})); m_pixels.insert(std::move(pixel_pair_t{4, 2})); m_pixels.insert(std::move(pixel_pair_t{5, 2})); 
            m_pixels.insert(std::move(pixel_pair_t{2, 3})); m_pixels.insert(std::move(pixel_pair_t{6, 3})); 
            m_pixels.insert(std::move(pixel_pair_t{2, 4})); m_pixels.insert(std::move(pixel_pair_t{6, 4})); 
            m_pixels.insert(std::move(pixel_pair_t{1, 5})); m_pixels.insert(std::move(pixel_pair_t{7, 5})); 
            m_pixels.insert(std::move(pixel_pair_t{1, 6})); m_pixels.insert(std::move(pixel_pair_t{7, 6})); 
            m_pixels.insert(std::move(pixel_pair_t{1, 7})); m_pixels.insert(std::move(pixel_pair_t{2, 7})); m_pixels.insert(std::move(pixel_pair_t{3, 7})); m_pixels.insert(std::move(pixel_pair_t{4, 7})); m_pixels.insert(std::move(pixel_pair_t{5, 7})); m_pixels.insert(std::move(pixel_pair_t{6, 7})); m_pixels.insert(std::move(pixel_pair_t{7, 7})); 
            m_pixels.insert(std::move(pixel_pair_t{3, 8})); m_pixels.insert(std::move(pixel_pair_t{4, 8})); m_pixels.insert(std::move(pixel_pair_t{5, 8})); 
            m_pixels.insert(std::move(pixel_pair_t{4, 9})); 
        }
    };
};
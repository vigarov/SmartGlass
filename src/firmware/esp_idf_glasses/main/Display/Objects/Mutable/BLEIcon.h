#pragma once
#include "Content.h"

namespace SmartGlasses{

    class BLEIcon : public Content{
    public:
        BLEIcon(std::string name, bool overwrites = true,pixel_pair_t offsets = {0,0}, unsigned char priority = 1 ) :
            Content(name,overwrites,offsets,priority){
            m_pixels.insert(std::move(pixel_pair_t{3, 0})); m_pixels.insert(std::move(pixel_pair_t{4, 0})); 
            m_pixels.insert(std::move(pixel_pair_t{3, 1})); m_pixels.insert(std::move(pixel_pair_t{5, 1})); 
            m_pixels.insert(std::move(pixel_pair_t{0, 2})); m_pixels.insert(std::move(pixel_pair_t{3, 2})); m_pixels.insert(std::move(pixel_pair_t{6, 2})); 
            m_pixels.insert(std::move(pixel_pair_t{1, 3})); m_pixels.insert(std::move(pixel_pair_t{3, 3})); m_pixels.insert(std::move(pixel_pair_t{6, 3})); 
            m_pixels.insert(std::move(pixel_pair_t{2, 4})); m_pixels.insert(std::move(pixel_pair_t{3, 4})); m_pixels.insert(std::move(pixel_pair_t{5, 4})); 
            m_pixels.insert(std::move(pixel_pair_t{3, 5})); m_pixels.insert(std::move(pixel_pair_t{4, 5})); 
            m_pixels.insert(std::move(pixel_pair_t{2, 6})); m_pixels.insert(std::move(pixel_pair_t{3, 6})); m_pixels.insert(std::move(pixel_pair_t{5, 6})); 
            m_pixels.insert(std::move(pixel_pair_t{1, 7})); m_pixels.insert(std::move(pixel_pair_t{3, 7})); m_pixels.insert(std::move(pixel_pair_t{6, 7})); 
            m_pixels.insert(std::move(pixel_pair_t{0, 8})); m_pixels.insert(std::move(pixel_pair_t{3, 8})); m_pixels.insert(std::move(pixel_pair_t{6, 8})); 
            m_pixels.insert(std::move(pixel_pair_t{3, 9})); m_pixels.insert(std::move(pixel_pair_t{5, 9})); 
            m_pixels.insert(std::move(pixel_pair_t{3, 10})); m_pixels.insert(std::move(pixel_pair_t{4, 10})); 
        }
    //To finish: override updatePixels, somehow save the handle of the task somewhere where the BT callback can call it (add getter for task handle and yeet in globals?)
    protected:
        void updatePixels() override;
    };
};
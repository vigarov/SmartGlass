#pragma once

namespace SmartGlasses{

    class BatteryFrame : public ConstantContent{
    public:
        BatteryFrame(const std::stirng& name, bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,priority){      
            m_pixels.insert(std::move(pixel_pair_t{2, 1})); m_pixels.insert(std::move(pixel_pair_t{3, 1})); m_pixels.insert(std::move(pixel_pair_t{4, 1})); m_pixels.insert(std::move(pixel_pair_t{5, 1})); m_pixels.insert(std::move(pixel_pair_t{6, 1})); m_pixels.insert(std::move(pixel_pair_t{7, 1})); m_pixels.insert(std::move(pixel_pair_t{8, 1})); m_pixels.insert(std::move(pixel_pair_t{9, 1})); m_pixels.insert(std::move(pixel_pair_t{10, 1})); m_pixels.insert(std::move(pixel_pair_t{11, 1})); m_pixels.insert(std::move(pixel_pair_t{12, 1})); m_pixels.insert(std::move(pixel_pair_t{13, 1})); m_pixels.insert(std::move(pixel_pair_t{14, 1})); m_pixels.insert(std::move(pixel_pair_t{15, 1})); m_pixels.insert(std::move(pixel_pair_t{16, 1})); 
            m_pixels.insert(std::move(pixel_pair_t{2, 2})); m_pixels.insert(std::move(pixel_pair_t{16, 2})); 
            m_pixels.insert(std::move(pixel_pair_t{2, 3})); m_pixels.insert(std::move(pixel_pair_t{16, 3})); 
            m_pixels.insert(std::move(pixel_pair_t{2, 4})); m_pixels.insert(std::move(pixel_pair_t{16, 4})); 
            m_pixels.insert(std::move(pixel_pair_t{1, 5})); m_pixels.insert(std::move(pixel_pair_t{2, 5})); m_pixels.insert(std::move(pixel_pair_t{16, 5})); 
            m_pixels.insert(std::move(pixel_pair_t{1, 6})); m_pixels.insert(std::move(pixel_pair_t{2, 6})); m_pixels.insert(std::move(pixel_pair_t{16, 6})); 
            m_pixels.insert(std::move(pixel_pair_t{1, 7})); m_pixels.insert(std::move(pixel_pair_t{2, 7})); m_pixels.insert(std::move(pixel_pair_t{16, 7})); 
            m_pixels.insert(std::move(pixel_pair_t{1, 8})); m_pixels.insert(std::move(pixel_pair_t{2, 8})); m_pixels.insert(std::move(pixel_pair_t{16, 8})); 
            m_pixels.insert(std::move(pixel_pair_t{2, 9})); m_pixels.insert(std::move(pixel_pair_t{16, 9})); 
            m_pixels.insert(std::move(pixel_pair_t{2, 10})); m_pixels.insert(std::move(pixel_pair_t{16, 10})); 
            m_pixels.insert(std::move(pixel_pair_t{2, 11})); m_pixels.insert(std::move(pixel_pair_t{3, 11})); m_pixels.insert(std::move(pixel_pair_t{4, 11})); m_pixels.insert(std::move(pixel_pair_t{5, 11})); m_pixels.insert(std::move(pixel_pair_t{6, 11})); m_pixels.insert(std::move(pixel_pair_t{7, 11})); m_pixels.insert(std::move(pixel_pair_t{8, 11})); m_pixels.insert(std::move(pixel_pair_t{9, 11})); m_pixels.insert(std::move(pixel_pair_t{10, 11})); m_pixels.insert(std::move(pixel_pair_t{11, 11})); m_pixels.insert(std::move(pixel_pair_t{12, 11})); m_pixels.insert(std::move(pixel_pair_t{13, 11})); m_pixels.insert(std::move(pixel_pair_t{14, 11})); m_pixels.insert(std::move(pixel_pair_t{15, 11})); m_pixels.insert(std::move(pixel_pair_t{16, 11})); 

        }
    };
}
#pragma once


#include "Content.h"

namespace SmartGlasses{

    class RightArrow : public ConstantContent{
    public:
        RightArrow(const std::string& name, bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,priority) {
            m_pixels.insert(std::move(pixel_pair_t{38, 0})); m_pixels.insert(std::move(pixel_pair_t{39, 0})); m_pixels.insert(std::move(pixel_pair_t{40, 0})); m_pixels.insert(std::move(pixel_pair_t{41, 0})); m_pixels.insert(std::move(pixel_pair_t{42, 0})); m_pixels.insert(std::move(pixel_pair_t{43, 0})); m_pixels.insert(std::move(pixel_pair_t{44, 0})); m_pixels.insert(std::move(pixel_pair_t{45, 0})); 
m_pixels.insert(std::move(pixel_pair_t{39, 1})); m_pixels.insert(std::move(pixel_pair_t{40, 1})); m_pixels.insert(std::move(pixel_pair_t{41, 1})); m_pixels.insert(std::move(pixel_pair_t{44, 1})); m_pixels.insert(std::move(pixel_pair_t{45, 1})); m_pixels.insert(std::move(pixel_pair_t{46, 1})); 
m_pixels.insert(std::move(pixel_pair_t{40, 2})); m_pixels.insert(std::move(pixel_pair_t{41, 2})); m_pixels.insert(std::move(pixel_pair_t{42, 2})); m_pixels.insert(std::move(pixel_pair_t{45, 2})); m_pixels.insert(std::move(pixel_pair_t{46, 2})); m_pixels.insert(std::move(pixel_pair_t{47, 2})); 
m_pixels.insert(std::move(pixel_pair_t{41, 3})); m_pixels.insert(std::move(pixel_pair_t{42, 3})); m_pixels.insert(std::move(pixel_pair_t{43, 3})); m_pixels.insert(std::move(pixel_pair_t{46, 3})); m_pixels.insert(std::move(pixel_pair_t{47, 3})); m_pixels.insert(std::move(pixel_pair_t{48, 3})); 
m_pixels.insert(std::move(pixel_pair_t{42, 4})); m_pixels.insert(std::move(pixel_pair_t{43, 4})); m_pixels.insert(std::move(pixel_pair_t{44, 4})); m_pixels.insert(std::move(pixel_pair_t{47, 4})); m_pixels.insert(std::move(pixel_pair_t{48, 4})); m_pixels.insert(std::move(pixel_pair_t{49, 4})); 
m_pixels.insert(std::move(pixel_pair_t{43, 5})); m_pixels.insert(std::move(pixel_pair_t{44, 5})); m_pixels.insert(std::move(pixel_pair_t{45, 5})); m_pixels.insert(std::move(pixel_pair_t{48, 5})); m_pixels.insert(std::move(pixel_pair_t{49, 5})); m_pixels.insert(std::move(pixel_pair_t{50, 5})); 
m_pixels.insert(std::move(pixel_pair_t{1, 6})); m_pixels.insert(std::move(pixel_pair_t{2, 6})); m_pixels.insert(std::move(pixel_pair_t{3, 6})); m_pixels.insert(std::move(pixel_pair_t{4, 6})); m_pixels.insert(std::move(pixel_pair_t{5, 6})); m_pixels.insert(std::move(pixel_pair_t{6, 6})); m_pixels.insert(std::move(pixel_pair_t{7, 6})); m_pixels.insert(std::move(pixel_pair_t{8, 6})); m_pixels.insert(std::move(pixel_pair_t{9, 6})); m_pixels.insert(std::move(pixel_pair_t{10, 6})); m_pixels.insert(std::move(pixel_pair_t{11, 6})); m_pixels.insert(std::move(pixel_pair_t{12, 6})); m_pixels.insert(std::move(pixel_pair_t{13, 6})); m_pixels.insert(std::move(pixel_pair_t{14, 6})); m_pixels.insert(std::move(pixel_pair_t{15, 6})); m_pixels.insert(std::move(pixel_pair_t{16, 6})); m_pixels.insert(std::move(pixel_pair_t{17, 6})); m_pixels.insert(std::move(pixel_pair_t{18, 6})); m_pixels.insert(std::move(pixel_pair_t{19, 6})); m_pixels.insert(std::move(pixel_pair_t{20, 6})); m_pixels.insert(std::move(pixel_pair_t{21, 6})); m_pixels.insert(std::move(pixel_pair_t{22, 6})); m_pixels.insert(std::move(pixel_pair_t{23, 6})); m_pixels.insert(std::move(pixel_pair_t{24, 6})); m_pixels.insert(std::move(pixel_pair_t{25, 6})); m_pixels.insert(std::move(pixel_pair_t{26, 6})); m_pixels.insert(std::move(pixel_pair_t{27, 6})); m_pixels.insert(std::move(pixel_pair_t{28, 6})); m_pixels.insert(std::move(pixel_pair_t{29, 6})); m_pixels.insert(std::move(pixel_pair_t{30, 6})); m_pixels.insert(std::move(pixel_pair_t{31, 6})); m_pixels.insert(std::move(pixel_pair_t{32, 6})); m_pixels.insert(std::move(pixel_pair_t{33, 6})); m_pixels.insert(std::move(pixel_pair_t{34, 6})); m_pixels.insert(std::move(pixel_pair_t{35, 6})); m_pixels.insert(std::move(pixel_pair_t{36, 6})); m_pixels.insert(std::move(pixel_pair_t{37, 6})); m_pixels.insert(std::move(pixel_pair_t{38, 6})); m_pixels.insert(std::move(pixel_pair_t{39, 6})); m_pixels.insert(std::move(pixel_pair_t{40, 6})); m_pixels.insert(std::move(pixel_pair_t{41, 6})); m_pixels.insert(std::move(pixel_pair_t{42, 6})); m_pixels.insert(std::move(pixel_pair_t{43, 6})); m_pixels.insert(std::move(pixel_pair_t{44, 6})); m_pixels.insert(std::move(pixel_pair_t{45, 6})); m_pixels.insert(std::move(pixel_pair_t{46, 6})); m_pixels.insert(std::move(pixel_pair_t{49, 6})); m_pixels.insert(std::move(pixel_pair_t{50, 6})); m_pixels.insert(std::move(pixel_pair_t{51, 6})); 
m_pixels.insert(std::move(pixel_pair_t{1, 7})); m_pixels.insert(std::move(pixel_pair_t{2, 7})); m_pixels.insert(std::move(pixel_pair_t{3, 7})); m_pixels.insert(std::move(pixel_pair_t{4, 7})); m_pixels.insert(std::move(pixel_pair_t{5, 7})); m_pixels.insert(std::move(pixel_pair_t{6, 7})); m_pixels.insert(std::move(pixel_pair_t{7, 7})); m_pixels.insert(std::move(pixel_pair_t{8, 7})); m_pixels.insert(std::move(pixel_pair_t{9, 7})); m_pixels.insert(std::move(pixel_pair_t{10, 7})); m_pixels.insert(std::move(pixel_pair_t{11, 7})); m_pixels.insert(std::move(pixel_pair_t{12, 7})); m_pixels.insert(std::move(pixel_pair_t{13, 7})); m_pixels.insert(std::move(pixel_pair_t{14, 7})); m_pixels.insert(std::move(pixel_pair_t{15, 7})); m_pixels.insert(std::move(pixel_pair_t{16, 7})); m_pixels.insert(std::move(pixel_pair_t{17, 7})); m_pixels.insert(std::move(pixel_pair_t{18, 7})); m_pixels.insert(std::move(pixel_pair_t{19, 7})); m_pixels.insert(std::move(pixel_pair_t{20, 7})); m_pixels.insert(std::move(pixel_pair_t{21, 7})); m_pixels.insert(std::move(pixel_pair_t{22, 7})); m_pixels.insert(std::move(pixel_pair_t{23, 7})); m_pixels.insert(std::move(pixel_pair_t{24, 7})); m_pixels.insert(std::move(pixel_pair_t{25, 7})); m_pixels.insert(std::move(pixel_pair_t{26, 7})); m_pixels.insert(std::move(pixel_pair_t{27, 7})); m_pixels.insert(std::move(pixel_pair_t{28, 7})); m_pixels.insert(std::move(pixel_pair_t{29, 7})); m_pixels.insert(std::move(pixel_pair_t{30, 7})); m_pixels.insert(std::move(pixel_pair_t{31, 7})); m_pixels.insert(std::move(pixel_pair_t{32, 7})); m_pixels.insert(std::move(pixel_pair_t{33, 7})); m_pixels.insert(std::move(pixel_pair_t{34, 7})); m_pixels.insert(std::move(pixel_pair_t{35, 7})); m_pixels.insert(std::move(pixel_pair_t{36, 7})); m_pixels.insert(std::move(pixel_pair_t{37, 7})); m_pixels.insert(std::move(pixel_pair_t{38, 7})); m_pixels.insert(std::move(pixel_pair_t{39, 7})); m_pixels.insert(std::move(pixel_pair_t{40, 7})); m_pixels.insert(std::move(pixel_pair_t{41, 7})); m_pixels.insert(std::move(pixel_pair_t{42, 7})); m_pixels.insert(std::move(pixel_pair_t{43, 7})); m_pixels.insert(std::move(pixel_pair_t{44, 7})); m_pixels.insert(std::move(pixel_pair_t{45, 7})); m_pixels.insert(std::move(pixel_pair_t{46, 7})); m_pixels.insert(std::move(pixel_pair_t{47, 7})); m_pixels.insert(std::move(pixel_pair_t{50, 7})); m_pixels.insert(std::move(pixel_pair_t{51, 7})); m_pixels.insert(std::move(pixel_pair_t{52, 7})); 
m_pixels.insert(std::move(pixel_pair_t{1, 8})); m_pixels.insert(std::move(pixel_pair_t{2, 8})); m_pixels.insert(std::move(pixel_pair_t{46, 8})); m_pixels.insert(std::move(pixel_pair_t{47, 8})); m_pixels.insert(std::move(pixel_pair_t{48, 8})); m_pixels.insert(std::move(pixel_pair_t{51, 8})); m_pixels.insert(std::move(pixel_pair_t{52, 8})); m_pixels.insert(std::move(pixel_pair_t{53, 8})); 
m_pixels.insert(std::move(pixel_pair_t{1, 9})); m_pixels.insert(std::move(pixel_pair_t{2, 9})); m_pixels.insert(std::move(pixel_pair_t{4, 9})); m_pixels.insert(std::move(pixel_pair_t{5, 9})); m_pixels.insert(std::move(pixel_pair_t{6, 9})); m_pixels.insert(std::move(pixel_pair_t{7, 9})); m_pixels.insert(std::move(pixel_pair_t{9, 9})); m_pixels.insert(std::move(pixel_pair_t{10, 9})); m_pixels.insert(std::move(pixel_pair_t{11, 9})); m_pixels.insert(std::move(pixel_pair_t{12, 9})); m_pixels.insert(std::move(pixel_pair_t{13, 9})); m_pixels.insert(std::move(pixel_pair_t{14, 9})); m_pixels.insert(std::move(pixel_pair_t{15, 9})); m_pixels.insert(std::move(pixel_pair_t{17, 9})); m_pixels.insert(std::move(pixel_pair_t{18, 9})); m_pixels.insert(std::move(pixel_pair_t{19, 9})); m_pixels.insert(std::move(pixel_pair_t{20, 9})); m_pixels.insert(std::move(pixel_pair_t{21, 9})); m_pixels.insert(std::move(pixel_pair_t{22, 9})); m_pixels.insert(std::move(pixel_pair_t{23, 9})); m_pixels.insert(std::move(pixel_pair_t{24, 9})); m_pixels.insert(std::move(pixel_pair_t{25, 9})); m_pixels.insert(std::move(pixel_pair_t{26, 9})); m_pixels.insert(std::move(pixel_pair_t{28, 9})); m_pixels.insert(std::move(pixel_pair_t{29, 9})); m_pixels.insert(std::move(pixel_pair_t{30, 9})); m_pixels.insert(std::move(pixel_pair_t{31, 9})); m_pixels.insert(std::move(pixel_pair_t{32, 9})); m_pixels.insert(std::move(pixel_pair_t{33, 9})); m_pixels.insert(std::move(pixel_pair_t{34, 9})); m_pixels.insert(std::move(pixel_pair_t{35, 9})); m_pixels.insert(std::move(pixel_pair_t{36, 9})); m_pixels.insert(std::move(pixel_pair_t{37, 9})); m_pixels.insert(std::move(pixel_pair_t{38, 9})); m_pixels.insert(std::move(pixel_pair_t{40, 9})); m_pixels.insert(std::move(pixel_pair_t{41, 9})); m_pixels.insert(std::move(pixel_pair_t{42, 9})); m_pixels.insert(std::move(pixel_pair_t{43, 9})); m_pixels.insert(std::move(pixel_pair_t{44, 9})); m_pixels.insert(std::move(pixel_pair_t{47, 9})); m_pixels.insert(std::move(pixel_pair_t{48, 9})); m_pixels.insert(std::move(pixel_pair_t{49, 9})); m_pixels.insert(std::move(pixel_pair_t{52, 9})); m_pixels.insert(std::move(pixel_pair_t{53, 9})); m_pixels.insert(std::move(pixel_pair_t{54, 9})); 
m_pixels.insert(std::move(pixel_pair_t{1, 10})); m_pixels.insert(std::move(pixel_pair_t{2, 10})); m_pixels.insert(std::move(pixel_pair_t{4, 10})); m_pixels.insert(std::move(pixel_pair_t{5, 10})); m_pixels.insert(std::move(pixel_pair_t{6, 10})); m_pixels.insert(std::move(pixel_pair_t{7, 10})); m_pixels.insert(std::move(pixel_pair_t{9, 10})); m_pixels.insert(std::move(pixel_pair_t{10, 10})); m_pixels.insert(std::move(pixel_pair_t{11, 10})); m_pixels.insert(std::move(pixel_pair_t{12, 10})); m_pixels.insert(std::move(pixel_pair_t{13, 10})); m_pixels.insert(std::move(pixel_pair_t{14, 10})); m_pixels.insert(std::move(pixel_pair_t{15, 10})); m_pixels.insert(std::move(pixel_pair_t{17, 10})); m_pixels.insert(std::move(pixel_pair_t{18, 10})); m_pixels.insert(std::move(pixel_pair_t{19, 10})); m_pixels.insert(std::move(pixel_pair_t{20, 10})); m_pixels.insert(std::move(pixel_pair_t{21, 10})); m_pixels.insert(std::move(pixel_pair_t{22, 10})); m_pixels.insert(std::move(pixel_pair_t{23, 10})); m_pixels.insert(std::move(pixel_pair_t{24, 10})); m_pixels.insert(std::move(pixel_pair_t{25, 10})); m_pixels.insert(std::move(pixel_pair_t{26, 10})); m_pixels.insert(std::move(pixel_pair_t{28, 10})); m_pixels.insert(std::move(pixel_pair_t{29, 10})); m_pixels.insert(std::move(pixel_pair_t{30, 10})); m_pixels.insert(std::move(pixel_pair_t{31, 10})); m_pixels.insert(std::move(pixel_pair_t{32, 10})); m_pixels.insert(std::move(pixel_pair_t{33, 10})); m_pixels.insert(std::move(pixel_pair_t{34, 10})); m_pixels.insert(std::move(pixel_pair_t{35, 10})); m_pixels.insert(std::move(pixel_pair_t{36, 10})); m_pixels.insert(std::move(pixel_pair_t{37, 10})); m_pixels.insert(std::move(pixel_pair_t{38, 10})); m_pixels.insert(std::move(pixel_pair_t{40, 10})); m_pixels.insert(std::move(pixel_pair_t{41, 10})); m_pixels.insert(std::move(pixel_pair_t{42, 10})); m_pixels.insert(std::move(pixel_pair_t{43, 10})); m_pixels.insert(std::move(pixel_pair_t{44, 10})); m_pixels.insert(std::move(pixel_pair_t{47, 10})); m_pixels.insert(std::move(pixel_pair_t{48, 10})); m_pixels.insert(std::move(pixel_pair_t{49, 10})); m_pixels.insert(std::move(pixel_pair_t{52, 10})); m_pixels.insert(std::move(pixel_pair_t{53, 10})); m_pixels.insert(std::move(pixel_pair_t{54, 10})); 
m_pixels.insert(std::move(pixel_pair_t{1, 11})); m_pixels.insert(std::move(pixel_pair_t{2, 11})); m_pixels.insert(std::move(pixel_pair_t{46, 11})); m_pixels.insert(std::move(pixel_pair_t{47, 11})); m_pixels.insert(std::move(pixel_pair_t{48, 11})); m_pixels.insert(std::move(pixel_pair_t{51, 11})); m_pixels.insert(std::move(pixel_pair_t{52, 11})); m_pixels.insert(std::move(pixel_pair_t{53, 11})); 
m_pixels.insert(std::move(pixel_pair_t{1, 12})); m_pixels.insert(std::move(pixel_pair_t{2, 12})); m_pixels.insert(std::move(pixel_pair_t{3, 12})); m_pixels.insert(std::move(pixel_pair_t{4, 12})); m_pixels.insert(std::move(pixel_pair_t{5, 12})); m_pixels.insert(std::move(pixel_pair_t{6, 12})); m_pixels.insert(std::move(pixel_pair_t{7, 12})); m_pixels.insert(std::move(pixel_pair_t{8, 12})); m_pixels.insert(std::move(pixel_pair_t{9, 12})); m_pixels.insert(std::move(pixel_pair_t{10, 12})); m_pixels.insert(std::move(pixel_pair_t{11, 12})); m_pixels.insert(std::move(pixel_pair_t{12, 12})); m_pixels.insert(std::move(pixel_pair_t{13, 12})); m_pixels.insert(std::move(pixel_pair_t{14, 12})); m_pixels.insert(std::move(pixel_pair_t{15, 12})); m_pixels.insert(std::move(pixel_pair_t{16, 12})); m_pixels.insert(std::move(pixel_pair_t{17, 12})); m_pixels.insert(std::move(pixel_pair_t{18, 12})); m_pixels.insert(std::move(pixel_pair_t{19, 12})); m_pixels.insert(std::move(pixel_pair_t{20, 12})); m_pixels.insert(std::move(pixel_pair_t{21, 12})); m_pixels.insert(std::move(pixel_pair_t{22, 12})); m_pixels.insert(std::move(pixel_pair_t{23, 12})); m_pixels.insert(std::move(pixel_pair_t{24, 12})); m_pixels.insert(std::move(pixel_pair_t{25, 12})); m_pixels.insert(std::move(pixel_pair_t{26, 12})); m_pixels.insert(std::move(pixel_pair_t{27, 12})); m_pixels.insert(std::move(pixel_pair_t{28, 12})); m_pixels.insert(std::move(pixel_pair_t{29, 12})); m_pixels.insert(std::move(pixel_pair_t{30, 12})); m_pixels.insert(std::move(pixel_pair_t{31, 12})); m_pixels.insert(std::move(pixel_pair_t{32, 12})); m_pixels.insert(std::move(pixel_pair_t{33, 12})); m_pixels.insert(std::move(pixel_pair_t{34, 12})); m_pixels.insert(std::move(pixel_pair_t{35, 12})); m_pixels.insert(std::move(pixel_pair_t{36, 12})); m_pixels.insert(std::move(pixel_pair_t{37, 12})); m_pixels.insert(std::move(pixel_pair_t{38, 12})); m_pixels.insert(std::move(pixel_pair_t{39, 12})); m_pixels.insert(std::move(pixel_pair_t{40, 12})); m_pixels.insert(std::move(pixel_pair_t{41, 12})); m_pixels.insert(std::move(pixel_pair_t{42, 12})); m_pixels.insert(std::move(pixel_pair_t{43, 12})); m_pixels.insert(std::move(pixel_pair_t{44, 12})); m_pixels.insert(std::move(pixel_pair_t{45, 12})); m_pixels.insert(std::move(pixel_pair_t{46, 12})); m_pixels.insert(std::move(pixel_pair_t{47, 12})); m_pixels.insert(std::move(pixel_pair_t{50, 12})); m_pixels.insert(std::move(pixel_pair_t{51, 12})); m_pixels.insert(std::move(pixel_pair_t{52, 12})); 
m_pixels.insert(std::move(pixel_pair_t{1, 13})); m_pixels.insert(std::move(pixel_pair_t{2, 13})); m_pixels.insert(std::move(pixel_pair_t{3, 13})); m_pixels.insert(std::move(pixel_pair_t{4, 13})); m_pixels.insert(std::move(pixel_pair_t{5, 13})); m_pixels.insert(std::move(pixel_pair_t{6, 13})); m_pixels.insert(std::move(pixel_pair_t{7, 13})); m_pixels.insert(std::move(pixel_pair_t{8, 13})); m_pixels.insert(std::move(pixel_pair_t{9, 13})); m_pixels.insert(std::move(pixel_pair_t{10, 13})); m_pixels.insert(std::move(pixel_pair_t{11, 13})); m_pixels.insert(std::move(pixel_pair_t{12, 13})); m_pixels.insert(std::move(pixel_pair_t{13, 13})); m_pixels.insert(std::move(pixel_pair_t{14, 13})); m_pixels.insert(std::move(pixel_pair_t{15, 13})); m_pixels.insert(std::move(pixel_pair_t{16, 13})); m_pixels.insert(std::move(pixel_pair_t{17, 13})); m_pixels.insert(std::move(pixel_pair_t{18, 13})); m_pixels.insert(std::move(pixel_pair_t{19, 13})); m_pixels.insert(std::move(pixel_pair_t{20, 13})); m_pixels.insert(std::move(pixel_pair_t{21, 13})); m_pixels.insert(std::move(pixel_pair_t{22, 13})); m_pixels.insert(std::move(pixel_pair_t{23, 13})); m_pixels.insert(std::move(pixel_pair_t{24, 13})); m_pixels.insert(std::move(pixel_pair_t{25, 13})); m_pixels.insert(std::move(pixel_pair_t{26, 13})); m_pixels.insert(std::move(pixel_pair_t{27, 13})); m_pixels.insert(std::move(pixel_pair_t{28, 13})); m_pixels.insert(std::move(pixel_pair_t{29, 13})); m_pixels.insert(std::move(pixel_pair_t{30, 13})); m_pixels.insert(std::move(pixel_pair_t{31, 13})); m_pixels.insert(std::move(pixel_pair_t{32, 13})); m_pixels.insert(std::move(pixel_pair_t{33, 13})); m_pixels.insert(std::move(pixel_pair_t{34, 13})); m_pixels.insert(std::move(pixel_pair_t{35, 13})); m_pixels.insert(std::move(pixel_pair_t{36, 13})); m_pixels.insert(std::move(pixel_pair_t{37, 13})); m_pixels.insert(std::move(pixel_pair_t{38, 13})); m_pixels.insert(std::move(pixel_pair_t{39, 13})); m_pixels.insert(std::move(pixel_pair_t{40, 13})); m_pixels.insert(std::move(pixel_pair_t{41, 13})); m_pixels.insert(std::move(pixel_pair_t{42, 13})); m_pixels.insert(std::move(pixel_pair_t{43, 13})); m_pixels.insert(std::move(pixel_pair_t{44, 13})); m_pixels.insert(std::move(pixel_pair_t{45, 13})); m_pixels.insert(std::move(pixel_pair_t{46, 13})); m_pixels.insert(std::move(pixel_pair_t{49, 13})); m_pixels.insert(std::move(pixel_pair_t{50, 13})); m_pixels.insert(std::move(pixel_pair_t{51, 13})); 
m_pixels.insert(std::move(pixel_pair_t{43, 14})); m_pixels.insert(std::move(pixel_pair_t{44, 14})); m_pixels.insert(std::move(pixel_pair_t{45, 14})); m_pixels.insert(std::move(pixel_pair_t{48, 14})); m_pixels.insert(std::move(pixel_pair_t{49, 14})); m_pixels.insert(std::move(pixel_pair_t{50, 14})); 
m_pixels.insert(std::move(pixel_pair_t{42, 15})); m_pixels.insert(std::move(pixel_pair_t{43, 15})); m_pixels.insert(std::move(pixel_pair_t{44, 15})); m_pixels.insert(std::move(pixel_pair_t{47, 15})); m_pixels.insert(std::move(pixel_pair_t{48, 15})); m_pixels.insert(std::move(pixel_pair_t{49, 15})); 
m_pixels.insert(std::move(pixel_pair_t{41, 16})); m_pixels.insert(std::move(pixel_pair_t{42, 16})); m_pixels.insert(std::move(pixel_pair_t{43, 16})); m_pixels.insert(std::move(pixel_pair_t{46, 16})); m_pixels.insert(std::move(pixel_pair_t{47, 16})); m_pixels.insert(std::move(pixel_pair_t{48, 16})); 
m_pixels.insert(std::move(pixel_pair_t{40, 17})); m_pixels.insert(std::move(pixel_pair_t{41, 17})); m_pixels.insert(std::move(pixel_pair_t{42, 17})); m_pixels.insert(std::move(pixel_pair_t{45, 17})); m_pixels.insert(std::move(pixel_pair_t{46, 17})); m_pixels.insert(std::move(pixel_pair_t{47, 17})); 
m_pixels.insert(std::move(pixel_pair_t{39, 18})); m_pixels.insert(std::move(pixel_pair_t{40, 18})); m_pixels.insert(std::move(pixel_pair_t{41, 18})); m_pixels.insert(std::move(pixel_pair_t{44, 18})); m_pixels.insert(std::move(pixel_pair_t{45, 18})); m_pixels.insert(std::move(pixel_pair_t{46, 18})); 
m_pixels.insert(std::move(pixel_pair_t{38, 19})); m_pixels.insert(std::move(pixel_pair_t{39, 19})); m_pixels.insert(std::move(pixel_pair_t{40, 19})); m_pixels.insert(std::move(pixel_pair_t{41, 19})); m_pixels.insert(std::move(pixel_pair_t{42, 19})); m_pixels.insert(std::move(pixel_pair_t{43, 19})); m_pixels.insert(std::move(pixel_pair_t{44, 19})); m_pixels.insert(std::move(pixel_pair_t{45, 19})); 
        }
    };
};

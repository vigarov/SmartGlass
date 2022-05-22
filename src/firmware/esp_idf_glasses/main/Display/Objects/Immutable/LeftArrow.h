#pragma once

namespace SmartGlasses{

    class LeftArrow : public ConstantContent{
    public:
        LeftArrow(const std::stirng& name, bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char priority = 1): ConstantContent(name,overwrites,offsets,priority) {
            m_pixels.insert(std::move(pixel_pair_t{9, 0})); m_pixels.insert(std::move(pixel_pair_t{10, 0})); m_pixels.insert(std::move(pixel_pair_t{11, 0})); m_pixels.insert(std::move(pixel_pair_t{12, 0})); m_pixels.insert(std::move(pixel_pair_t{13, 0})); m_pixels.insert(std::move(pixel_pair_t{14, 0})); m_pixels.insert(std::move(pixel_pair_t{15, 0})); m_pixels.insert(std::move(pixel_pair_t{16, 0})); 
m_pixels.insert(std::move(pixel_pair_t{8, 1})); m_pixels.insert(std::move(pixel_pair_t{9, 1})); m_pixels.insert(std::move(pixel_pair_t{10, 1})); m_pixels.insert(std::move(pixel_pair_t{13, 1})); m_pixels.insert(std::move(pixel_pair_t{14, 1})); m_pixels.insert(std::move(pixel_pair_t{15, 1})); 
m_pixels.insert(std::move(pixel_pair_t{7, 2})); m_pixels.insert(std::move(pixel_pair_t{8, 2})); m_pixels.insert(std::move(pixel_pair_t{9, 2})); m_pixels.insert(std::move(pixel_pair_t{12, 2})); m_pixels.insert(std::move(pixel_pair_t{13, 2})); m_pixels.insert(std::move(pixel_pair_t{14, 2})); 
m_pixels.insert(std::move(pixel_pair_t{6, 3})); m_pixels.insert(std::move(pixel_pair_t{7, 3})); m_pixels.insert(std::move(pixel_pair_t{8, 3})); m_pixels.insert(std::move(pixel_pair_t{11, 3})); m_pixels.insert(std::move(pixel_pair_t{12, 3})); m_pixels.insert(std::move(pixel_pair_t{13, 3})); 
m_pixels.insert(std::move(pixel_pair_t{5, 4})); m_pixels.insert(std::move(pixel_pair_t{6, 4})); m_pixels.insert(std::move(pixel_pair_t{7, 4})); m_pixels.insert(std::move(pixel_pair_t{10, 4})); m_pixels.insert(std::move(pixel_pair_t{11, 4})); m_pixels.insert(std::move(pixel_pair_t{12, 4})); 
m_pixels.insert(std::move(pixel_pair_t{4, 5})); m_pixels.insert(std::move(pixel_pair_t{5, 5})); m_pixels.insert(std::move(pixel_pair_t{6, 5})); m_pixels.insert(std::move(pixel_pair_t{9, 5})); m_pixels.insert(std::move(pixel_pair_t{10, 5})); m_pixels.insert(std::move(pixel_pair_t{11, 5})); 
m_pixels.insert(std::move(pixel_pair_t{3, 6})); m_pixels.insert(std::move(pixel_pair_t{4, 6})); m_pixels.insert(std::move(pixel_pair_t{5, 6})); m_pixels.insert(std::move(pixel_pair_t{8, 6})); m_pixels.insert(std::move(pixel_pair_t{9, 6})); m_pixels.insert(std::move(pixel_pair_t{10, 6})); m_pixels.insert(std::move(pixel_pair_t{11, 6})); m_pixels.insert(std::move(pixel_pair_t{12, 6})); m_pixels.insert(std::move(pixel_pair_t{13, 6})); m_pixels.insert(std::move(pixel_pair_t{14, 6})); m_pixels.insert(std::move(pixel_pair_t{15, 6})); m_pixels.insert(std::move(pixel_pair_t{16, 6})); m_pixels.insert(std::move(pixel_pair_t{17, 6})); m_pixels.insert(std::move(pixel_pair_t{18, 6})); m_pixels.insert(std::move(pixel_pair_t{19, 6})); m_pixels.insert(std::move(pixel_pair_t{20, 6})); m_pixels.insert(std::move(pixel_pair_t{21, 6})); m_pixels.insert(std::move(pixel_pair_t{22, 6})); m_pixels.insert(std::move(pixel_pair_t{23, 6})); m_pixels.insert(std::move(pixel_pair_t{24, 6})); m_pixels.insert(std::move(pixel_pair_t{25, 6})); m_pixels.insert(std::move(pixel_pair_t{26, 6})); m_pixels.insert(std::move(pixel_pair_t{27, 6})); m_pixels.insert(std::move(pixel_pair_t{28, 6})); m_pixels.insert(std::move(pixel_pair_t{29, 6})); m_pixels.insert(std::move(pixel_pair_t{30, 6})); m_pixels.insert(std::move(pixel_pair_t{31, 6})); m_pixels.insert(std::move(pixel_pair_t{32, 6})); m_pixels.insert(std::move(pixel_pair_t{33, 6})); m_pixels.insert(std::move(pixel_pair_t{34, 6})); m_pixels.insert(std::move(pixel_pair_t{35, 6})); m_pixels.insert(std::move(pixel_pair_t{36, 6})); m_pixels.insert(std::move(pixel_pair_t{37, 6})); m_pixels.insert(std::move(pixel_pair_t{38, 6})); m_pixels.insert(std::move(pixel_pair_t{39, 6})); m_pixels.insert(std::move(pixel_pair_t{40, 6})); m_pixels.insert(std::move(pixel_pair_t{41, 6})); m_pixels.insert(std::move(pixel_pair_t{42, 6})); m_pixels.insert(std::move(pixel_pair_t{43, 6})); m_pixels.insert(std::move(pixel_pair_t{44, 6})); m_pixels.insert(std::move(pixel_pair_t{45, 6})); m_pixels.insert(std::move(pixel_pair_t{46, 6})); m_pixels.insert(std::move(pixel_pair_t{47, 6})); m_pixels.insert(std::move(pixel_pair_t{48, 6})); m_pixels.insert(std::move(pixel_pair_t{49, 6})); m_pixels.insert(std::move(pixel_pair_t{50, 6})); m_pixels.insert(std::move(pixel_pair_t{51, 6})); m_pixels.insert(std::move(pixel_pair_t{52, 6})); m_pixels.insert(std::move(pixel_pair_t{53, 6})); 
m_pixels.insert(std::move(pixel_pair_t{2, 7})); m_pixels.insert(std::move(pixel_pair_t{3, 7})); m_pixels.insert(std::move(pixel_pair_t{4, 7})); m_pixels.insert(std::move(pixel_pair_t{7, 7})); m_pixels.insert(std::move(pixel_pair_t{8, 7})); m_pixels.insert(std::move(pixel_pair_t{9, 7})); m_pixels.insert(std::move(pixel_pair_t{10, 7})); m_pixels.insert(std::move(pixel_pair_t{11, 7})); m_pixels.insert(std::move(pixel_pair_t{12, 7})); m_pixels.insert(std::move(pixel_pair_t{13, 7})); m_pixels.insert(std::move(pixel_pair_t{14, 7})); m_pixels.insert(std::move(pixel_pair_t{15, 7})); m_pixels.insert(std::move(pixel_pair_t{16, 7})); m_pixels.insert(std::move(pixel_pair_t{17, 7})); m_pixels.insert(std::move(pixel_pair_t{18, 7})); m_pixels.insert(std::move(pixel_pair_t{19, 7})); m_pixels.insert(std::move(pixel_pair_t{20, 7})); m_pixels.insert(std::move(pixel_pair_t{21, 7})); m_pixels.insert(std::move(pixel_pair_t{22, 7})); m_pixels.insert(std::move(pixel_pair_t{23, 7})); m_pixels.insert(std::move(pixel_pair_t{24, 7})); m_pixels.insert(std::move(pixel_pair_t{25, 7})); m_pixels.insert(std::move(pixel_pair_t{26, 7})); m_pixels.insert(std::move(pixel_pair_t{27, 7})); m_pixels.insert(std::move(pixel_pair_t{28, 7})); m_pixels.insert(std::move(pixel_pair_t{29, 7})); m_pixels.insert(std::move(pixel_pair_t{30, 7})); m_pixels.insert(std::move(pixel_pair_t{31, 7})); m_pixels.insert(std::move(pixel_pair_t{32, 7})); m_pixels.insert(std::move(pixel_pair_t{33, 7})); m_pixels.insert(std::move(pixel_pair_t{34, 7})); m_pixels.insert(std::move(pixel_pair_t{35, 7})); m_pixels.insert(std::move(pixel_pair_t{36, 7})); m_pixels.insert(std::move(pixel_pair_t{37, 7})); m_pixels.insert(std::move(pixel_pair_t{38, 7})); m_pixels.insert(std::move(pixel_pair_t{39, 7})); m_pixels.insert(std::move(pixel_pair_t{40, 7})); m_pixels.insert(std::move(pixel_pair_t{41, 7})); m_pixels.insert(std::move(pixel_pair_t{42, 7})); m_pixels.insert(std::move(pixel_pair_t{43, 7})); m_pixels.insert(std::move(pixel_pair_t{44, 7})); m_pixels.insert(std::move(pixel_pair_t{45, 7})); m_pixels.insert(std::move(pixel_pair_t{46, 7})); m_pixels.insert(std::move(pixel_pair_t{47, 7})); m_pixels.insert(std::move(pixel_pair_t{48, 7})); m_pixels.insert(std::move(pixel_pair_t{49, 7})); m_pixels.insert(std::move(pixel_pair_t{50, 7})); m_pixels.insert(std::move(pixel_pair_t{51, 7})); m_pixels.insert(std::move(pixel_pair_t{52, 7})); m_pixels.insert(std::move(pixel_pair_t{53, 7})); 
m_pixels.insert(std::move(pixel_pair_t{1, 8})); m_pixels.insert(std::move(pixel_pair_t{2, 8})); m_pixels.insert(std::move(pixel_pair_t{3, 8})); m_pixels.insert(std::move(pixel_pair_t{6, 8})); m_pixels.insert(std::move(pixel_pair_t{7, 8})); m_pixels.insert(std::move(pixel_pair_t{8, 8})); m_pixels.insert(std::move(pixel_pair_t{52, 8})); m_pixels.insert(std::move(pixel_pair_t{53, 8})); 
m_pixels.insert(std::move(pixel_pair_t{0, 9})); m_pixels.insert(std::move(pixel_pair_t{1, 9})); m_pixels.insert(std::move(pixel_pair_t{2, 9})); m_pixels.insert(std::move(pixel_pair_t{5, 9})); m_pixels.insert(std::move(pixel_pair_t{6, 9})); m_pixels.insert(std::move(pixel_pair_t{7, 9})); m_pixels.insert(std::move(pixel_pair_t{10, 9})); m_pixels.insert(std::move(pixel_pair_t{11, 9})); m_pixels.insert(std::move(pixel_pair_t{12, 9})); m_pixels.insert(std::move(pixel_pair_t{13, 9})); m_pixels.insert(std::move(pixel_pair_t{14, 9})); m_pixels.insert(std::move(pixel_pair_t{16, 9})); m_pixels.insert(std::move(pixel_pair_t{17, 9})); m_pixels.insert(std::move(pixel_pair_t{18, 9})); m_pixels.insert(std::move(pixel_pair_t{19, 9})); m_pixels.insert(std::move(pixel_pair_t{20, 9})); m_pixels.insert(std::move(pixel_pair_t{21, 9})); m_pixels.insert(std::move(pixel_pair_t{22, 9})); m_pixels.insert(std::move(pixel_pair_t{23, 9})); m_pixels.insert(std::move(pixel_pair_t{24, 9})); m_pixels.insert(std::move(pixel_pair_t{25, 9})); m_pixels.insert(std::move(pixel_pair_t{26, 9})); m_pixels.insert(std::move(pixel_pair_t{28, 9})); m_pixels.insert(std::move(pixel_pair_t{29, 9})); m_pixels.insert(std::move(pixel_pair_t{30, 9})); m_pixels.insert(std::move(pixel_pair_t{31, 9})); m_pixels.insert(std::move(pixel_pair_t{32, 9})); m_pixels.insert(std::move(pixel_pair_t{33, 9})); m_pixels.insert(std::move(pixel_pair_t{34, 9})); m_pixels.insert(std::move(pixel_pair_t{35, 9})); m_pixels.insert(std::move(pixel_pair_t{36, 9})); m_pixels.insert(std::move(pixel_pair_t{37, 9})); m_pixels.insert(std::move(pixel_pair_t{39, 9})); m_pixels.insert(std::move(pixel_pair_t{40, 9})); m_pixels.insert(std::move(pixel_pair_t{41, 9})); m_pixels.insert(std::move(pixel_pair_t{42, 9})); m_pixels.insert(std::move(pixel_pair_t{43, 9})); m_pixels.insert(std::move(pixel_pair_t{44, 9})); m_pixels.insert(std::move(pixel_pair_t{45, 9})); m_pixels.insert(std::move(pixel_pair_t{47, 9})); m_pixels.insert(std::move(pixel_pair_t{48, 9})); m_pixels.insert(std::move(pixel_pair_t{49, 9})); m_pixels.insert(std::move(pixel_pair_t{50, 9})); m_pixels.insert(std::move(pixel_pair_t{52, 9})); m_pixels.insert(std::move(pixel_pair_t{53, 9})); 
m_pixels.insert(std::move(pixel_pair_t{0, 10})); m_pixels.insert(std::move(pixel_pair_t{1, 10})); m_pixels.insert(std::move(pixel_pair_t{2, 10})); m_pixels.insert(std::move(pixel_pair_t{5, 10})); m_pixels.insert(std::move(pixel_pair_t{6, 10})); m_pixels.insert(std::move(pixel_pair_t{7, 10})); m_pixels.insert(std::move(pixel_pair_t{10, 10})); m_pixels.insert(std::move(pixel_pair_t{11, 10})); m_pixels.insert(std::move(pixel_pair_t{12, 10})); m_pixels.insert(std::move(pixel_pair_t{13, 10})); m_pixels.insert(std::move(pixel_pair_t{14, 10})); m_pixels.insert(std::move(pixel_pair_t{16, 10})); m_pixels.insert(std::move(pixel_pair_t{17, 10})); m_pixels.insert(std::move(pixel_pair_t{18, 10})); m_pixels.insert(std::move(pixel_pair_t{19, 10})); m_pixels.insert(std::move(pixel_pair_t{20, 10})); m_pixels.insert(std::move(pixel_pair_t{21, 10})); m_pixels.insert(std::move(pixel_pair_t{22, 10})); m_pixels.insert(std::move(pixel_pair_t{23, 10})); m_pixels.insert(std::move(pixel_pair_t{24, 10})); m_pixels.insert(std::move(pixel_pair_t{25, 10})); m_pixels.insert(std::move(pixel_pair_t{26, 10})); m_pixels.insert(std::move(pixel_pair_t{28, 10})); m_pixels.insert(std::move(pixel_pair_t{29, 10})); m_pixels.insert(std::move(pixel_pair_t{30, 10})); m_pixels.insert(std::move(pixel_pair_t{31, 10})); m_pixels.insert(std::move(pixel_pair_t{32, 10})); m_pixels.insert(std::move(pixel_pair_t{33, 10})); m_pixels.insert(std::move(pixel_pair_t{34, 10})); m_pixels.insert(std::move(pixel_pair_t{35, 10})); m_pixels.insert(std::move(pixel_pair_t{36, 10})); m_pixels.insert(std::move(pixel_pair_t{37, 10})); m_pixels.insert(std::move(pixel_pair_t{39, 10})); m_pixels.insert(std::move(pixel_pair_t{40, 10})); m_pixels.insert(std::move(pixel_pair_t{41, 10})); m_pixels.insert(std::move(pixel_pair_t{42, 10})); m_pixels.insert(std::move(pixel_pair_t{43, 10})); m_pixels.insert(std::move(pixel_pair_t{44, 10})); m_pixels.insert(std::move(pixel_pair_t{45, 10})); m_pixels.insert(std::move(pixel_pair_t{47, 10})); m_pixels.insert(std::move(pixel_pair_t{48, 10})); m_pixels.insert(std::move(pixel_pair_t{49, 10})); m_pixels.insert(std::move(pixel_pair_t{50, 10})); m_pixels.insert(std::move(pixel_pair_t{52, 10})); m_pixels.insert(std::move(pixel_pair_t{53, 10})); 
m_pixels.insert(std::move(pixel_pair_t{1, 11})); m_pixels.insert(std::move(pixel_pair_t{2, 11})); m_pixels.insert(std::move(pixel_pair_t{3, 11})); m_pixels.insert(std::move(pixel_pair_t{6, 11})); m_pixels.insert(std::move(pixel_pair_t{7, 11})); m_pixels.insert(std::move(pixel_pair_t{8, 11})); m_pixels.insert(std::move(pixel_pair_t{52, 11})); m_pixels.insert(std::move(pixel_pair_t{53, 11})); 
m_pixels.insert(std::move(pixel_pair_t{2, 12})); m_pixels.insert(std::move(pixel_pair_t{3, 12})); m_pixels.insert(std::move(pixel_pair_t{4, 12})); m_pixels.insert(std::move(pixel_pair_t{7, 12})); m_pixels.insert(std::move(pixel_pair_t{8, 12})); m_pixels.insert(std::move(pixel_pair_t{9, 12})); m_pixels.insert(std::move(pixel_pair_t{10, 12})); m_pixels.insert(std::move(pixel_pair_t{11, 12})); m_pixels.insert(std::move(pixel_pair_t{12, 12})); m_pixels.insert(std::move(pixel_pair_t{13, 12})); m_pixels.insert(std::move(pixel_pair_t{14, 12})); m_pixels.insert(std::move(pixel_pair_t{15, 12})); m_pixels.insert(std::move(pixel_pair_t{16, 12})); m_pixels.insert(std::move(pixel_pair_t{17, 12})); m_pixels.insert(std::move(pixel_pair_t{18, 12})); m_pixels.insert(std::move(pixel_pair_t{19, 12})); m_pixels.insert(std::move(pixel_pair_t{20, 12})); m_pixels.insert(std::move(pixel_pair_t{21, 12})); m_pixels.insert(std::move(pixel_pair_t{22, 12})); m_pixels.insert(std::move(pixel_pair_t{23, 12})); m_pixels.insert(std::move(pixel_pair_t{24, 12})); m_pixels.insert(std::move(pixel_pair_t{25, 12})); m_pixels.insert(std::move(pixel_pair_t{26, 12})); m_pixels.insert(std::move(pixel_pair_t{27, 12})); m_pixels.insert(std::move(pixel_pair_t{28, 12})); m_pixels.insert(std::move(pixel_pair_t{29, 12})); m_pixels.insert(std::move(pixel_pair_t{30, 12})); m_pixels.insert(std::move(pixel_pair_t{31, 12})); m_pixels.insert(std::move(pixel_pair_t{32, 12})); m_pixels.insert(std::move(pixel_pair_t{33, 12})); m_pixels.insert(std::move(pixel_pair_t{34, 12})); m_pixels.insert(std::move(pixel_pair_t{35, 12})); m_pixels.insert(std::move(pixel_pair_t{36, 12})); m_pixels.insert(std::move(pixel_pair_t{37, 12})); m_pixels.insert(std::move(pixel_pair_t{38, 12})); m_pixels.insert(std::move(pixel_pair_t{39, 12})); m_pixels.insert(std::move(pixel_pair_t{40, 12})); m_pixels.insert(std::move(pixel_pair_t{41, 12})); m_pixels.insert(std::move(pixel_pair_t{42, 12})); m_pixels.insert(std::move(pixel_pair_t{43, 12})); m_pixels.insert(std::move(pixel_pair_t{44, 12})); m_pixels.insert(std::move(pixel_pair_t{45, 12})); m_pixels.insert(std::move(pixel_pair_t{46, 12})); m_pixels.insert(std::move(pixel_pair_t{47, 12})); m_pixels.insert(std::move(pixel_pair_t{48, 12})); m_pixels.insert(std::move(pixel_pair_t{49, 12})); m_pixels.insert(std::move(pixel_pair_t{50, 12})); m_pixels.insert(std::move(pixel_pair_t{51, 12})); m_pixels.insert(std::move(pixel_pair_t{52, 12})); m_pixels.insert(std::move(pixel_pair_t{53, 12})); 
m_pixels.insert(std::move(pixel_pair_t{3, 13})); m_pixels.insert(std::move(pixel_pair_t{4, 13})); m_pixels.insert(std::move(pixel_pair_t{5, 13})); m_pixels.insert(std::move(pixel_pair_t{8, 13})); m_pixels.insert(std::move(pixel_pair_t{9, 13})); m_pixels.insert(std::move(pixel_pair_t{10, 13})); m_pixels.insert(std::move(pixel_pair_t{11, 13})); m_pixels.insert(std::move(pixel_pair_t{12, 13})); m_pixels.insert(std::move(pixel_pair_t{13, 13})); m_pixels.insert(std::move(pixel_pair_t{14, 13})); m_pixels.insert(std::move(pixel_pair_t{15, 13})); m_pixels.insert(std::move(pixel_pair_t{16, 13})); m_pixels.insert(std::move(pixel_pair_t{17, 13})); m_pixels.insert(std::move(pixel_pair_t{18, 13})); m_pixels.insert(std::move(pixel_pair_t{19, 13})); m_pixels.insert(std::move(pixel_pair_t{20, 13})); m_pixels.insert(std::move(pixel_pair_t{21, 13})); m_pixels.insert(std::move(pixel_pair_t{22, 13})); m_pixels.insert(std::move(pixel_pair_t{23, 13})); m_pixels.insert(std::move(pixel_pair_t{24, 13})); m_pixels.insert(std::move(pixel_pair_t{25, 13})); m_pixels.insert(std::move(pixel_pair_t{26, 13})); m_pixels.insert(std::move(pixel_pair_t{27, 13})); m_pixels.insert(std::move(pixel_pair_t{28, 13})); m_pixels.insert(std::move(pixel_pair_t{29, 13})); m_pixels.insert(std::move(pixel_pair_t{30, 13})); m_pixels.insert(std::move(pixel_pair_t{31, 13})); m_pixels.insert(std::move(pixel_pair_t{32, 13})); m_pixels.insert(std::move(pixel_pair_t{33, 13})); m_pixels.insert(std::move(pixel_pair_t{34, 13})); m_pixels.insert(std::move(pixel_pair_t{35, 13})); m_pixels.insert(std::move(pixel_pair_t{36, 13})); m_pixels.insert(std::move(pixel_pair_t{37, 13})); m_pixels.insert(std::move(pixel_pair_t{38, 13})); m_pixels.insert(std::move(pixel_pair_t{39, 13})); m_pixels.insert(std::move(pixel_pair_t{40, 13})); m_pixels.insert(std::move(pixel_pair_t{41, 13})); m_pixels.insert(std::move(pixel_pair_t{42, 13})); m_pixels.insert(std::move(pixel_pair_t{43, 13})); m_pixels.insert(std::move(pixel_pair_t{44, 13})); m_pixels.insert(std::move(pixel_pair_t{45, 13})); m_pixels.insert(std::move(pixel_pair_t{46, 13})); m_pixels.insert(std::move(pixel_pair_t{47, 13})); m_pixels.insert(std::move(pixel_pair_t{48, 13})); m_pixels.insert(std::move(pixel_pair_t{49, 13})); m_pixels.insert(std::move(pixel_pair_t{50, 13})); m_pixels.insert(std::move(pixel_pair_t{51, 13})); m_pixels.insert(std::move(pixel_pair_t{52, 13})); m_pixels.insert(std::move(pixel_pair_t{53, 13})); 
m_pixels.insert(std::move(pixel_pair_t{4, 14})); m_pixels.insert(std::move(pixel_pair_t{5, 14})); m_pixels.insert(std::move(pixel_pair_t{6, 14})); m_pixels.insert(std::move(pixel_pair_t{9, 14})); m_pixels.insert(std::move(pixel_pair_t{10, 14})); m_pixels.insert(std::move(pixel_pair_t{11, 14})); 
m_pixels.insert(std::move(pixel_pair_t{5, 15})); m_pixels.insert(std::move(pixel_pair_t{6, 15})); m_pixels.insert(std::move(pixel_pair_t{7, 15})); m_pixels.insert(std::move(pixel_pair_t{10, 15})); m_pixels.insert(std::move(pixel_pair_t{11, 15})); m_pixels.insert(std::move(pixel_pair_t{12, 15})); 
m_pixels.insert(std::move(pixel_pair_t{6, 16})); m_pixels.insert(std::move(pixel_pair_t{7, 16})); m_pixels.insert(std::move(pixel_pair_t{8, 16})); m_pixels.insert(std::move(pixel_pair_t{11, 16})); m_pixels.insert(std::move(pixel_pair_t{12, 16})); m_pixels.insert(std::move(pixel_pair_t{13, 16})); 
m_pixels.insert(std::move(pixel_pair_t{7, 17})); m_pixels.insert(std::move(pixel_pair_t{8, 17})); m_pixels.insert(std::move(pixel_pair_t{9, 17})); m_pixels.insert(std::move(pixel_pair_t{12, 17})); m_pixels.insert(std::move(pixel_pair_t{13, 17})); m_pixels.insert(std::move(pixel_pair_t{14, 17})); 
m_pixels.insert(std::move(pixel_pair_t{8, 18})); m_pixels.insert(std::move(pixel_pair_t{9, 18})); m_pixels.insert(std::move(pixel_pair_t{10, 18})); m_pixels.insert(std::move(pixel_pair_t{13, 18})); m_pixels.insert(std::move(pixel_pair_t{14, 18})); m_pixels.insert(std::move(pixel_pair_t{15, 18})); 
m_pixels.insert(std::move(pixel_pair_t{9, 19})); m_pixels.insert(std::move(pixel_pair_t{10, 19})); m_pixels.insert(std::move(pixel_pair_t{11, 19})); m_pixels.insert(std::move(pixel_pair_t{12, 19})); m_pixels.insert(std::move(pixel_pair_t{13, 19})); m_pixels.insert(std::move(pixel_pair_t{14, 19})); m_pixels.insert(std::move(pixel_pair_t{15, 19})); m_pixels.insert(std::move(pixel_pair_t{16, 19})); 

        }
    };
};
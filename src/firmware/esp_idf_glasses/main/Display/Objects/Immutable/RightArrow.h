#pragma once


#include "Content.h"

namespace SmartGlasses{

    class RightArrow : public ConstantContent{
    public:
        RightArrow(const std::string& name, bool overwrites = false, pixel_pair_t offsets = {0,0},unsigned char animate = false,  unsigned char priority = 1): ConstantContent(name,overwrites,offsets,animate,priority) {}

        std::unique_ptr<pixels_set_t> createPixels(){
            auto pixels = std::make_unique<pixels_set_t>();
            pixels->insert(std::move(pixel_pair_t{38, 0})); pixels->insert(std::move(pixel_pair_t{39, 0})); pixels->insert(std::move(pixel_pair_t{40, 0})); pixels->insert(std::move(pixel_pair_t{41, 0})); pixels->insert(std::move(pixel_pair_t{42, 0})); pixels->insert(std::move(pixel_pair_t{43, 0})); pixels->insert(std::move(pixel_pair_t{44, 0})); pixels->insert(std::move(pixel_pair_t{45, 0})); 
            pixels->insert(std::move(pixel_pair_t{39, 1})); pixels->insert(std::move(pixel_pair_t{40, 1})); pixels->insert(std::move(pixel_pair_t{41, 1})); pixels->insert(std::move(pixel_pair_t{44, 1})); pixels->insert(std::move(pixel_pair_t{45, 1})); pixels->insert(std::move(pixel_pair_t{46, 1})); 
            pixels->insert(std::move(pixel_pair_t{40, 2})); pixels->insert(std::move(pixel_pair_t{41, 2})); pixels->insert(std::move(pixel_pair_t{42, 2})); pixels->insert(std::move(pixel_pair_t{45, 2})); pixels->insert(std::move(pixel_pair_t{46, 2})); pixels->insert(std::move(pixel_pair_t{47, 2})); 
            pixels->insert(std::move(pixel_pair_t{41, 3})); pixels->insert(std::move(pixel_pair_t{42, 3})); pixels->insert(std::move(pixel_pair_t{43, 3})); pixels->insert(std::move(pixel_pair_t{46, 3})); pixels->insert(std::move(pixel_pair_t{47, 3})); pixels->insert(std::move(pixel_pair_t{48, 3})); 
            pixels->insert(std::move(pixel_pair_t{42, 4})); pixels->insert(std::move(pixel_pair_t{43, 4})); pixels->insert(std::move(pixel_pair_t{44, 4})); pixels->insert(std::move(pixel_pair_t{47, 4})); pixels->insert(std::move(pixel_pair_t{48, 4})); pixels->insert(std::move(pixel_pair_t{49, 4})); 
            pixels->insert(std::move(pixel_pair_t{43, 5})); pixels->insert(std::move(pixel_pair_t{44, 5})); pixels->insert(std::move(pixel_pair_t{45, 5})); pixels->insert(std::move(pixel_pair_t{48, 5})); pixels->insert(std::move(pixel_pair_t{49, 5})); pixels->insert(std::move(pixel_pair_t{50, 5})); 
            pixels->insert(std::move(pixel_pair_t{1, 6})); pixels->insert(std::move(pixel_pair_t{2, 6})); pixels->insert(std::move(pixel_pair_t{3, 6})); pixels->insert(std::move(pixel_pair_t{4, 6})); pixels->insert(std::move(pixel_pair_t{5, 6})); pixels->insert(std::move(pixel_pair_t{6, 6})); pixels->insert(std::move(pixel_pair_t{7, 6})); pixels->insert(std::move(pixel_pair_t{8, 6})); pixels->insert(std::move(pixel_pair_t{9, 6})); pixels->insert(std::move(pixel_pair_t{10, 6})); pixels->insert(std::move(pixel_pair_t{11, 6})); pixels->insert(std::move(pixel_pair_t{12, 6})); pixels->insert(std::move(pixel_pair_t{13, 6})); pixels->insert(std::move(pixel_pair_t{14, 6})); pixels->insert(std::move(pixel_pair_t{15, 6})); pixels->insert(std::move(pixel_pair_t{16, 6})); pixels->insert(std::move(pixel_pair_t{17, 6})); pixels->insert(std::move(pixel_pair_t{18, 6})); pixels->insert(std::move(pixel_pair_t{19, 6})); pixels->insert(std::move(pixel_pair_t{20, 6})); pixels->insert(std::move(pixel_pair_t{21, 6})); pixels->insert(std::move(pixel_pair_t{22, 6})); pixels->insert(std::move(pixel_pair_t{23, 6})); pixels->insert(std::move(pixel_pair_t{24, 6})); pixels->insert(std::move(pixel_pair_t{25, 6})); pixels->insert(std::move(pixel_pair_t{26, 6})); pixels->insert(std::move(pixel_pair_t{27, 6})); pixels->insert(std::move(pixel_pair_t{28, 6})); pixels->insert(std::move(pixel_pair_t{29, 6})); pixels->insert(std::move(pixel_pair_t{30, 6})); pixels->insert(std::move(pixel_pair_t{31, 6})); pixels->insert(std::move(pixel_pair_t{32, 6})); pixels->insert(std::move(pixel_pair_t{33, 6})); pixels->insert(std::move(pixel_pair_t{34, 6})); pixels->insert(std::move(pixel_pair_t{35, 6})); pixels->insert(std::move(pixel_pair_t{36, 6})); pixels->insert(std::move(pixel_pair_t{37, 6})); pixels->insert(std::move(pixel_pair_t{38, 6})); pixels->insert(std::move(pixel_pair_t{39, 6})); pixels->insert(std::move(pixel_pair_t{40, 6})); pixels->insert(std::move(pixel_pair_t{41, 6})); pixels->insert(std::move(pixel_pair_t{42, 6})); pixels->insert(std::move(pixel_pair_t{43, 6})); pixels->insert(std::move(pixel_pair_t{44, 6})); pixels->insert(std::move(pixel_pair_t{45, 6})); pixels->insert(std::move(pixel_pair_t{46, 6})); pixels->insert(std::move(pixel_pair_t{49, 6})); pixels->insert(std::move(pixel_pair_t{50, 6})); pixels->insert(std::move(pixel_pair_t{51, 6})); 
            pixels->insert(std::move(pixel_pair_t{1, 7})); pixels->insert(std::move(pixel_pair_t{2, 7})); pixels->insert(std::move(pixel_pair_t{3, 7})); pixels->insert(std::move(pixel_pair_t{4, 7})); pixels->insert(std::move(pixel_pair_t{5, 7})); pixels->insert(std::move(pixel_pair_t{6, 7})); pixels->insert(std::move(pixel_pair_t{7, 7})); pixels->insert(std::move(pixel_pair_t{8, 7})); pixels->insert(std::move(pixel_pair_t{9, 7})); pixels->insert(std::move(pixel_pair_t{10, 7})); pixels->insert(std::move(pixel_pair_t{11, 7})); pixels->insert(std::move(pixel_pair_t{12, 7})); pixels->insert(std::move(pixel_pair_t{13, 7})); pixels->insert(std::move(pixel_pair_t{14, 7})); pixels->insert(std::move(pixel_pair_t{15, 7})); pixels->insert(std::move(pixel_pair_t{16, 7})); pixels->insert(std::move(pixel_pair_t{17, 7})); pixels->insert(std::move(pixel_pair_t{18, 7})); pixels->insert(std::move(pixel_pair_t{19, 7})); pixels->insert(std::move(pixel_pair_t{20, 7})); pixels->insert(std::move(pixel_pair_t{21, 7})); pixels->insert(std::move(pixel_pair_t{22, 7})); pixels->insert(std::move(pixel_pair_t{23, 7})); pixels->insert(std::move(pixel_pair_t{24, 7})); pixels->insert(std::move(pixel_pair_t{25, 7})); pixels->insert(std::move(pixel_pair_t{26, 7})); pixels->insert(std::move(pixel_pair_t{27, 7})); pixels->insert(std::move(pixel_pair_t{28, 7})); pixels->insert(std::move(pixel_pair_t{29, 7})); pixels->insert(std::move(pixel_pair_t{30, 7})); pixels->insert(std::move(pixel_pair_t{31, 7})); pixels->insert(std::move(pixel_pair_t{32, 7})); pixels->insert(std::move(pixel_pair_t{33, 7})); pixels->insert(std::move(pixel_pair_t{34, 7})); pixels->insert(std::move(pixel_pair_t{35, 7})); pixels->insert(std::move(pixel_pair_t{36, 7})); pixels->insert(std::move(pixel_pair_t{37, 7})); pixels->insert(std::move(pixel_pair_t{38, 7})); pixels->insert(std::move(pixel_pair_t{39, 7})); pixels->insert(std::move(pixel_pair_t{40, 7})); pixels->insert(std::move(pixel_pair_t{41, 7})); pixels->insert(std::move(pixel_pair_t{42, 7})); pixels->insert(std::move(pixel_pair_t{43, 7})); pixels->insert(std::move(pixel_pair_t{44, 7})); pixels->insert(std::move(pixel_pair_t{45, 7})); pixels->insert(std::move(pixel_pair_t{46, 7})); pixels->insert(std::move(pixel_pair_t{47, 7})); pixels->insert(std::move(pixel_pair_t{50, 7})); pixels->insert(std::move(pixel_pair_t{51, 7})); pixels->insert(std::move(pixel_pair_t{52, 7})); 
            pixels->insert(std::move(pixel_pair_t{1, 8})); pixels->insert(std::move(pixel_pair_t{2, 8})); pixels->insert(std::move(pixel_pair_t{46, 8})); pixels->insert(std::move(pixel_pair_t{47, 8})); pixels->insert(std::move(pixel_pair_t{48, 8})); pixels->insert(std::move(pixel_pair_t{51, 8})); pixels->insert(std::move(pixel_pair_t{52, 8})); pixels->insert(std::move(pixel_pair_t{53, 8})); 
            pixels->insert(std::move(pixel_pair_t{1, 9})); pixels->insert(std::move(pixel_pair_t{2, 9})); pixels->insert(std::move(pixel_pair_t{4, 9})); pixels->insert(std::move(pixel_pair_t{5, 9})); pixels->insert(std::move(pixel_pair_t{6, 9})); pixels->insert(std::move(pixel_pair_t{7, 9})); pixels->insert(std::move(pixel_pair_t{9, 9})); pixels->insert(std::move(pixel_pair_t{10, 9})); pixels->insert(std::move(pixel_pair_t{11, 9})); pixels->insert(std::move(pixel_pair_t{12, 9})); pixels->insert(std::move(pixel_pair_t{13, 9})); pixels->insert(std::move(pixel_pair_t{14, 9})); pixels->insert(std::move(pixel_pair_t{15, 9})); pixels->insert(std::move(pixel_pair_t{17, 9})); pixels->insert(std::move(pixel_pair_t{18, 9})); pixels->insert(std::move(pixel_pair_t{19, 9})); pixels->insert(std::move(pixel_pair_t{20, 9})); pixels->insert(std::move(pixel_pair_t{21, 9})); pixels->insert(std::move(pixel_pair_t{22, 9})); pixels->insert(std::move(pixel_pair_t{23, 9})); pixels->insert(std::move(pixel_pair_t{24, 9})); pixels->insert(std::move(pixel_pair_t{25, 9})); pixels->insert(std::move(pixel_pair_t{26, 9})); pixels->insert(std::move(pixel_pair_t{28, 9})); pixels->insert(std::move(pixel_pair_t{29, 9})); pixels->insert(std::move(pixel_pair_t{30, 9})); pixels->insert(std::move(pixel_pair_t{31, 9})); pixels->insert(std::move(pixel_pair_t{32, 9})); pixels->insert(std::move(pixel_pair_t{33, 9})); pixels->insert(std::move(pixel_pair_t{34, 9})); pixels->insert(std::move(pixel_pair_t{35, 9})); pixels->insert(std::move(pixel_pair_t{36, 9})); pixels->insert(std::move(pixel_pair_t{37, 9})); pixels->insert(std::move(pixel_pair_t{38, 9})); pixels->insert(std::move(pixel_pair_t{40, 9})); pixels->insert(std::move(pixel_pair_t{41, 9})); pixels->insert(std::move(pixel_pair_t{42, 9})); pixels->insert(std::move(pixel_pair_t{43, 9})); pixels->insert(std::move(pixel_pair_t{44, 9})); pixels->insert(std::move(pixel_pair_t{47, 9})); pixels->insert(std::move(pixel_pair_t{48, 9})); pixels->insert(std::move(pixel_pair_t{49, 9})); pixels->insert(std::move(pixel_pair_t{52, 9})); pixels->insert(std::move(pixel_pair_t{53, 9})); pixels->insert(std::move(pixel_pair_t{54, 9})); 
            pixels->insert(std::move(pixel_pair_t{1, 10})); pixels->insert(std::move(pixel_pair_t{2, 10})); pixels->insert(std::move(pixel_pair_t{4, 10})); pixels->insert(std::move(pixel_pair_t{5, 10})); pixels->insert(std::move(pixel_pair_t{6, 10})); pixels->insert(std::move(pixel_pair_t{7, 10})); pixels->insert(std::move(pixel_pair_t{9, 10})); pixels->insert(std::move(pixel_pair_t{10, 10})); pixels->insert(std::move(pixel_pair_t{11, 10})); pixels->insert(std::move(pixel_pair_t{12, 10})); pixels->insert(std::move(pixel_pair_t{13, 10})); pixels->insert(std::move(pixel_pair_t{14, 10})); pixels->insert(std::move(pixel_pair_t{15, 10})); pixels->insert(std::move(pixel_pair_t{17, 10})); pixels->insert(std::move(pixel_pair_t{18, 10})); pixels->insert(std::move(pixel_pair_t{19, 10})); pixels->insert(std::move(pixel_pair_t{20, 10})); pixels->insert(std::move(pixel_pair_t{21, 10})); pixels->insert(std::move(pixel_pair_t{22, 10})); pixels->insert(std::move(pixel_pair_t{23, 10})); pixels->insert(std::move(pixel_pair_t{24, 10})); pixels->insert(std::move(pixel_pair_t{25, 10})); pixels->insert(std::move(pixel_pair_t{26, 10})); pixels->insert(std::move(pixel_pair_t{28, 10})); pixels->insert(std::move(pixel_pair_t{29, 10})); pixels->insert(std::move(pixel_pair_t{30, 10})); pixels->insert(std::move(pixel_pair_t{31, 10})); pixels->insert(std::move(pixel_pair_t{32, 10})); pixels->insert(std::move(pixel_pair_t{33, 10})); pixels->insert(std::move(pixel_pair_t{34, 10})); pixels->insert(std::move(pixel_pair_t{35, 10})); pixels->insert(std::move(pixel_pair_t{36, 10})); pixels->insert(std::move(pixel_pair_t{37, 10})); pixels->insert(std::move(pixel_pair_t{38, 10})); pixels->insert(std::move(pixel_pair_t{40, 10})); pixels->insert(std::move(pixel_pair_t{41, 10})); pixels->insert(std::move(pixel_pair_t{42, 10})); pixels->insert(std::move(pixel_pair_t{43, 10})); pixels->insert(std::move(pixel_pair_t{44, 10})); pixels->insert(std::move(pixel_pair_t{47, 10})); pixels->insert(std::move(pixel_pair_t{48, 10})); pixels->insert(std::move(pixel_pair_t{49, 10})); pixels->insert(std::move(pixel_pair_t{52, 10})); pixels->insert(std::move(pixel_pair_t{53, 10})); pixels->insert(std::move(pixel_pair_t{54, 10})); 
            pixels->insert(std::move(pixel_pair_t{1, 11})); pixels->insert(std::move(pixel_pair_t{2, 11})); pixels->insert(std::move(pixel_pair_t{46, 11})); pixels->insert(std::move(pixel_pair_t{47, 11})); pixels->insert(std::move(pixel_pair_t{48, 11})); pixels->insert(std::move(pixel_pair_t{51, 11})); pixels->insert(std::move(pixel_pair_t{52, 11})); pixels->insert(std::move(pixel_pair_t{53, 11})); 
            pixels->insert(std::move(pixel_pair_t{1, 12})); pixels->insert(std::move(pixel_pair_t{2, 12})); pixels->insert(std::move(pixel_pair_t{3, 12})); pixels->insert(std::move(pixel_pair_t{4, 12})); pixels->insert(std::move(pixel_pair_t{5, 12})); pixels->insert(std::move(pixel_pair_t{6, 12})); pixels->insert(std::move(pixel_pair_t{7, 12})); pixels->insert(std::move(pixel_pair_t{8, 12})); pixels->insert(std::move(pixel_pair_t{9, 12})); pixels->insert(std::move(pixel_pair_t{10, 12})); pixels->insert(std::move(pixel_pair_t{11, 12})); pixels->insert(std::move(pixel_pair_t{12, 12})); pixels->insert(std::move(pixel_pair_t{13, 12})); pixels->insert(std::move(pixel_pair_t{14, 12})); pixels->insert(std::move(pixel_pair_t{15, 12})); pixels->insert(std::move(pixel_pair_t{16, 12})); pixels->insert(std::move(pixel_pair_t{17, 12})); pixels->insert(std::move(pixel_pair_t{18, 12})); pixels->insert(std::move(pixel_pair_t{19, 12})); pixels->insert(std::move(pixel_pair_t{20, 12})); pixels->insert(std::move(pixel_pair_t{21, 12})); pixels->insert(std::move(pixel_pair_t{22, 12})); pixels->insert(std::move(pixel_pair_t{23, 12})); pixels->insert(std::move(pixel_pair_t{24, 12})); pixels->insert(std::move(pixel_pair_t{25, 12})); pixels->insert(std::move(pixel_pair_t{26, 12})); pixels->insert(std::move(pixel_pair_t{27, 12})); pixels->insert(std::move(pixel_pair_t{28, 12})); pixels->insert(std::move(pixel_pair_t{29, 12})); pixels->insert(std::move(pixel_pair_t{30, 12})); pixels->insert(std::move(pixel_pair_t{31, 12})); pixels->insert(std::move(pixel_pair_t{32, 12})); pixels->insert(std::move(pixel_pair_t{33, 12})); pixels->insert(std::move(pixel_pair_t{34, 12})); pixels->insert(std::move(pixel_pair_t{35, 12})); pixels->insert(std::move(pixel_pair_t{36, 12})); pixels->insert(std::move(pixel_pair_t{37, 12})); pixels->insert(std::move(pixel_pair_t{38, 12})); pixels->insert(std::move(pixel_pair_t{39, 12})); pixels->insert(std::move(pixel_pair_t{40, 12})); pixels->insert(std::move(pixel_pair_t{41, 12})); pixels->insert(std::move(pixel_pair_t{42, 12})); pixels->insert(std::move(pixel_pair_t{43, 12})); pixels->insert(std::move(pixel_pair_t{44, 12})); pixels->insert(std::move(pixel_pair_t{45, 12})); pixels->insert(std::move(pixel_pair_t{46, 12})); pixels->insert(std::move(pixel_pair_t{47, 12})); pixels->insert(std::move(pixel_pair_t{50, 12})); pixels->insert(std::move(pixel_pair_t{51, 12})); pixels->insert(std::move(pixel_pair_t{52, 12})); 
            pixels->insert(std::move(pixel_pair_t{1, 13})); pixels->insert(std::move(pixel_pair_t{2, 13})); pixels->insert(std::move(pixel_pair_t{3, 13})); pixels->insert(std::move(pixel_pair_t{4, 13})); pixels->insert(std::move(pixel_pair_t{5, 13})); pixels->insert(std::move(pixel_pair_t{6, 13})); pixels->insert(std::move(pixel_pair_t{7, 13})); pixels->insert(std::move(pixel_pair_t{8, 13})); pixels->insert(std::move(pixel_pair_t{9, 13})); pixels->insert(std::move(pixel_pair_t{10, 13})); pixels->insert(std::move(pixel_pair_t{11, 13})); pixels->insert(std::move(pixel_pair_t{12, 13})); pixels->insert(std::move(pixel_pair_t{13, 13})); pixels->insert(std::move(pixel_pair_t{14, 13})); pixels->insert(std::move(pixel_pair_t{15, 13})); pixels->insert(std::move(pixel_pair_t{16, 13})); pixels->insert(std::move(pixel_pair_t{17, 13})); pixels->insert(std::move(pixel_pair_t{18, 13})); pixels->insert(std::move(pixel_pair_t{19, 13})); pixels->insert(std::move(pixel_pair_t{20, 13})); pixels->insert(std::move(pixel_pair_t{21, 13})); pixels->insert(std::move(pixel_pair_t{22, 13})); pixels->insert(std::move(pixel_pair_t{23, 13})); pixels->insert(std::move(pixel_pair_t{24, 13})); pixels->insert(std::move(pixel_pair_t{25, 13})); pixels->insert(std::move(pixel_pair_t{26, 13})); pixels->insert(std::move(pixel_pair_t{27, 13})); pixels->insert(std::move(pixel_pair_t{28, 13})); pixels->insert(std::move(pixel_pair_t{29, 13})); pixels->insert(std::move(pixel_pair_t{30, 13})); pixels->insert(std::move(pixel_pair_t{31, 13})); pixels->insert(std::move(pixel_pair_t{32, 13})); pixels->insert(std::move(pixel_pair_t{33, 13})); pixels->insert(std::move(pixel_pair_t{34, 13})); pixels->insert(std::move(pixel_pair_t{35, 13})); pixels->insert(std::move(pixel_pair_t{36, 13})); pixels->insert(std::move(pixel_pair_t{37, 13})); pixels->insert(std::move(pixel_pair_t{38, 13})); pixels->insert(std::move(pixel_pair_t{39, 13})); pixels->insert(std::move(pixel_pair_t{40, 13})); pixels->insert(std::move(pixel_pair_t{41, 13})); pixels->insert(std::move(pixel_pair_t{42, 13})); pixels->insert(std::move(pixel_pair_t{43, 13})); pixels->insert(std::move(pixel_pair_t{44, 13})); pixels->insert(std::move(pixel_pair_t{45, 13})); pixels->insert(std::move(pixel_pair_t{46, 13})); pixels->insert(std::move(pixel_pair_t{49, 13})); pixels->insert(std::move(pixel_pair_t{50, 13})); pixels->insert(std::move(pixel_pair_t{51, 13})); 
            pixels->insert(std::move(pixel_pair_t{43, 14})); pixels->insert(std::move(pixel_pair_t{44, 14})); pixels->insert(std::move(pixel_pair_t{45, 14})); pixels->insert(std::move(pixel_pair_t{48, 14})); pixels->insert(std::move(pixel_pair_t{49, 14})); pixels->insert(std::move(pixel_pair_t{50, 14})); 
            pixels->insert(std::move(pixel_pair_t{42, 15})); pixels->insert(std::move(pixel_pair_t{43, 15})); pixels->insert(std::move(pixel_pair_t{44, 15})); pixels->insert(std::move(pixel_pair_t{47, 15})); pixels->insert(std::move(pixel_pair_t{48, 15})); pixels->insert(std::move(pixel_pair_t{49, 15})); 
            pixels->insert(std::move(pixel_pair_t{41, 16})); pixels->insert(std::move(pixel_pair_t{42, 16})); pixels->insert(std::move(pixel_pair_t{43, 16})); pixels->insert(std::move(pixel_pair_t{46, 16})); pixels->insert(std::move(pixel_pair_t{47, 16})); pixels->insert(std::move(pixel_pair_t{48, 16})); 
            pixels->insert(std::move(pixel_pair_t{40, 17})); pixels->insert(std::move(pixel_pair_t{41, 17})); pixels->insert(std::move(pixel_pair_t{42, 17})); pixels->insert(std::move(pixel_pair_t{45, 17})); pixels->insert(std::move(pixel_pair_t{46, 17})); pixels->insert(std::move(pixel_pair_t{47, 17})); 
            pixels->insert(std::move(pixel_pair_t{39, 18})); pixels->insert(std::move(pixel_pair_t{40, 18})); pixels->insert(std::move(pixel_pair_t{41, 18})); pixels->insert(std::move(pixel_pair_t{44, 18})); pixels->insert(std::move(pixel_pair_t{45, 18})); pixels->insert(std::move(pixel_pair_t{46, 18})); 
            pixels->insert(std::move(pixel_pair_t{38, 19})); pixels->insert(std::move(pixel_pair_t{39, 19})); pixels->insert(std::move(pixel_pair_t{40, 19})); pixels->insert(std::move(pixel_pair_t{41, 19})); pixels->insert(std::move(pixel_pair_t{42, 19})); pixels->insert(std::move(pixel_pair_t{43, 19})); pixels->insert(std::move(pixel_pair_t{44, 19})); pixels->insert(std::move(pixel_pair_t{45, 19})); 
            return std::move(pixels);
        }
    };
};

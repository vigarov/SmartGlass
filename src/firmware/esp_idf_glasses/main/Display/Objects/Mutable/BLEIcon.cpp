#include "BLEIcon.h"

using namespace SmartGlasses;


std::unique_ptr<pixels_set_t> BLEIcon::createPixels(){
    auto pixels = std::make_unique<pixels_set_t>();        
    pixels->insert(std::move(pixel_pair_t{3, 0})); pixels->insert(std::move(pixel_pair_t{4, 0})); 
    pixels->insert(std::move(pixel_pair_t{3, 1})); pixels->insert(std::move(pixel_pair_t{5, 1})); 
    pixels->insert(std::move(pixel_pair_t{0, 2})); pixels->insert(std::move(pixel_pair_t{3, 2})); pixels->insert(std::move(pixel_pair_t{6, 2})); 
    pixels->insert(std::move(pixel_pair_t{1, 3})); pixels->insert(std::move(pixel_pair_t{3, 3})); pixels->insert(std::move(pixel_pair_t{6, 3})); 
    pixels->insert(std::move(pixel_pair_t{2, 4})); pixels->insert(std::move(pixel_pair_t{3, 4})); pixels->insert(std::move(pixel_pair_t{5, 4})); 
    pixels->insert(std::move(pixel_pair_t{3, 5})); pixels->insert(std::move(pixel_pair_t{4, 5})); 
    pixels->insert(std::move(pixel_pair_t{2, 6})); pixels->insert(std::move(pixel_pair_t{3, 6})); pixels->insert(std::move(pixel_pair_t{5, 6})); 
    pixels->insert(std::move(pixel_pair_t{1, 7})); pixels->insert(std::move(pixel_pair_t{3, 7})); pixels->insert(std::move(pixel_pair_t{6, 7})); 
    pixels->insert(std::move(pixel_pair_t{0, 8})); pixels->insert(std::move(pixel_pair_t{3, 8})); pixels->insert(std::move(pixel_pair_t{6, 8})); 
    pixels->insert(std::move(pixel_pair_t{3, 9})); pixels->insert(std::move(pixel_pair_t{5, 9})); 
    pixels->insert(std::move(pixel_pair_t{3, 10})); pixels->insert(std::move(pixel_pair_t{4, 10}));
    return std::move(pixels);
}
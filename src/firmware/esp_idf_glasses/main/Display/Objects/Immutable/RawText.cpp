#include "RawText.h"

using namespace SmartGlasses;


std::unique_ptr<pixels_set_t> RawText::createPixels(){    
    auto pixels = std::make_unique<pixels_set_t>();
    Font<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>::getPixelPairs(ASCII8x8,m_string,*pixels);
    return std::move(pixels);
}

#include "RawText.h"

using namespace SmartGlasses;

template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
RawText::RawText(const std::string &s,const Font<CHAR_T,CHAR_WIDTH,NB_CHARS>& font, bool overwrites,pixel_pair_t offsets,unsigned char priority) : ConstantContent("Constant <"+s+">", overwrites, offsets,priority){
    Font<CHAR_T,CHAR_WIDTH,NB_CHARS>::getPixelPairs(font,s,m_pixels);
}

template RawText::RawText<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>(const std::string &s,const Font<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>& font, bool overwrites,pixel_pair_t offsets,unsigned char priority);


void RawText::updatePixels(){
    //Sort the pixels
}
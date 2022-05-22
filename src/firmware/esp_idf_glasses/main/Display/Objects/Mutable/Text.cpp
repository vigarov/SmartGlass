#include "Text.h"

using namespace SmartGlasses;

template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
Text<CHAR_T,CHAR_WIDTH,NB_CHARS>::Text(const std::string &s, bool overwrites,const Font<CHAR_T,CHAR_WIDTH,NB_CHARS>* font,pixel_pair_t offsets,unsigned char priority) : Content("Mutable <"+s+">", overwrites, offsets,priority){
    m_s = s;
    m_f = font;
}

template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
void Text<CHAR_T,CHAR_WIDTH,NB_CHARS>::updatePixels(){
    Font<CHAR_T,CHAR_WIDTH,NB_CHARS>::getPixelPairs(*m_f,m_s,m_pixels);
}

Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS> textWithDefaultFontFrom(std::string s){
    return Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>(s);
} 


template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
void  Text<CHAR_T,CHAR_WIDTH,NB_CHARS>::changeString(std::string &newS){
    if(newS != m_s ){
        m_modifiedSinceLastUpdate = true;
        m_s = newS;
        update();
    }
}


//template class Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>;

#include "Text.h"

using namespace SmartGlasses;

template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
Text<CHAR_T,CHAR_WIDTH,NB_CHARS>::Text(const std::string &s, bool overwrites,const Font<CHAR_T,CHAR_WIDTH,NB_CHARS>* font,pixel_pair_t offsets,unsigned char animate, unsigned char priority) : Content("Mutable <"+s+">", overwrites, offsets,animate,priority){
    m_s = s;
    m_f = font;
}

template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
std::unique_ptr<pixels_set_t> Text<CHAR_T,CHAR_WIDTH,NB_CHARS>::createPixels(){
    auto pixels = std::make_unique<pixels_set_t>();
    Font<CHAR_T,CHAR_WIDTH,NB_CHARS>::getPixelPairs(*m_f,m_s,*pixels);
    return std::move(pixels);
}

template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
void Text<CHAR_T,CHAR_WIDTH,NB_CHARS>::changeString(const std::string &newS){
    if(newS != m_s ){
        m_modifiedSinceLastUpdate = true;
        forceHide();
        m_s = newS;
        update();
    }
}

template class Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>;

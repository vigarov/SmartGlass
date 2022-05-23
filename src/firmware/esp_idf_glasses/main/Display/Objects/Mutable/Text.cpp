#include "Text.h"

using namespace SmartGlasses;

template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
Text<CHAR_T,CHAR_WIDTH,NB_CHARS>::Text(const std::string &s, bool overwrites,const Font<CHAR_T,CHAR_WIDTH,NB_CHARS>* font,pixel_pair_t offsets,unsigned char animate, unsigned char priority) : Content("Mutable <"+s+">", overwrites, offsets,animate,priority){
    m_s = s;
    m_f = font;
}

template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
void Text<CHAR_T,CHAR_WIDTH,NB_CHARS>::updatePixels(){
    Font<CHAR_T,CHAR_WIDTH,NB_CHARS>::getPixelPairs(*m_f,m_s,m_pixels);
}


template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
void Text<CHAR_T,CHAR_WIDTH,NB_CHARS>::changeString(std::string &newS){
    if(newS != m_s ){
        m_modifiedSinceLastUpdate = true;
        m_s = newS;
        forceHide();
        m_pixels.clear();
        update();
    }
}

template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
void Text<CHAR_T,CHAR_WIDTH,NB_CHARS>::setup(){
    createUpdateTask(8048);
    finishSetup();
}

template class Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>;

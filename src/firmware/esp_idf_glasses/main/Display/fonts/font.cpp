#include "font.h"
#include "utils.h"

using namespace SmartGlasses;

#define CHAR_SPACING 0
#define LINE_ADD_SPACING 1

template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
void Font<CHAR_T,CHAR_WIDTH,NB_CHARS>::getPixelPairs(const Font<CHAR_T,CHAR_WIDTH,NB_CHARS>& f,const std::string& s, std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction>&v){
    unsigned short numberNewlines = 0;
    unsigned short xCursor = 0;
    for(int i=0;i<s.size();i++){
        char c = s[i];
        if(static_cast<int>(c)<NB_CHARS){
            if(c=='\n'){
                numberNewlines++;
                xCursor = 0;
            }else{
                getPixelPairsWithOffset(f,c,v,xCursor,numberNewlines*(8*sizeof(CHAR_T)+LINE_ADD_SPACING));
                xCursor += 8*sizeof(CHAR_T) + CHAR_SPACING;
            }
        }
    }
}

//TODO: Caching the whole font is too memory expensive. 
//We could however cache the most used elements (i.e.: implement a smart cache which would have a counter per element)
template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
void Font<CHAR_T,CHAR_WIDTH,NB_CHARS>::getPixelPairsWithOffset(const Font<CHAR_T,CHAR_WIDTH,NB_CHARS>& f,const char& c, std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction>& v,unsigned char offsetX, unsigned char offsetY){
    if(static_cast<int>(c)<NB_CHARS){
        const CHAR_T* charRepr = f.font[static_cast<int>(c)];
        for(unsigned char j = 0; j<CHAR_WIDTH;j++){
            const CHAR_T cRRowJ = charRepr[j];
            for(unsigned char i=0;i<sizeof(CHAR_T)*8;i++){
                if((cRRowJ & (1<<i))!=0){
                    v.insert({static_cast<unsigned char>(i+offsetX),static_cast<unsigned char>(j+offsetY)});
                }
            }
        }
    }
}

template class Font<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>;
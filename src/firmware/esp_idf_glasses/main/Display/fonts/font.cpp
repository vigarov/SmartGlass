#include "font.h"
#include "utils.h"

using namespace SmartGlasses;

#define CHAR_SPACING 1
#define LINE_ADD_SPACING 1

template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
void getPixelPairsWithOffset(Font<CHAR_T,CHAR_WIDTH,NB_CHARS>& f, std::string& s, std::vector<pixel_pair_t>&v){
    unsigned short numberNewlines = 0;
    for(int i=0;i<s.size();i++){
        char c = s[i];
        if(static_cast<int>(c)<NB_CHARS){
            if(c=='\n'){
                numberNewlines++;
            }
            getPixelPairsWithOffset(f,c,v,i*CHAR_SPACING,numberNewlines*sizeof(CHAR_T)+LINE_ADD_SPACING);
        }
    }
}

//TODO: Caching the whole font is too memory expensive. 
//We could however cache the most used elements (i.e.: implement a smart cache which would have a counter per element)
template<typename CHAR_T,unsigned int CHAR_WIDTH,unsigned long NB_CHARS>
void getPixelPairsWithOffset(Font<CHAR_T,CHAR_WIDTH,NB_CHARS>& f, char& c, std::vector<pixel_pair_t>& v,unsigned char offsetX, unsigned char offsetY){
    if(static_cast<int>(c)<NB_CHARS){
        const CHAR_T* charRepr = f.font[static_cast<int>(c)];
        for(short j = 0; j<CHAR_WIDTH;j++){
            const CHAR_T cRRowJ = charRepr[j];
            for(short i=0;i<sizeof(CHAR_T)*8;i++){
                if(cRRowJ & (1<<i)!=0){
                    v.push_back({i+offsetX,j+offsetY});
                }
            }
        }
    }
}
#include "Battery.h"

using namespace SmartGlasses;

Battery::Battery(battery_level_t initialLevel,bool overwrites, pixel_pair_t offsets, unsigned char priority): Content("Header Battery",overwrites,offsets,priority){
    m_contents.push_back(std::make_shared<BatteryFrame>("Header battery frame",false,offsets,priority));
    updateBatteryLevel(initialLevel);
}

void Battery::updateBatteryLevel(battery_level_t newLevel){
    const unsigned char numberOfBars = newLevel/PERCENTAGE_PER_BAR;
    const int currentNbBars = m_contents.size()-1;
    if(numberOfBars<currentNbBars){
        for(int i=currentNbBars-numberOfBars;i>0;i--){
            m_contents.pop_back();
        }
        m_modifiedSinceLastUpdate = true;
    }
    else if(numberOfBars>currentNbBars){
        const int nbBarsToAdd = numberOfBars - currentNbBars;
        for(int i=0;i<nbBarsToAdd;i++){
            std::string s = "Header Battery Bar";
            m_contents.push_back(std::make_shared<BatteryBar>(
                s + static_cast<char>('0'+i),m_overwrite, 
                m_offsets+(pixel_pair_t){static_cast<unsigned char>(BATTERY_BAR_X_MIN_OFFSET - (i+1)*(BATTERY_BAR_SPACING+BATTERY_BAR_WIDTH)),BATTERY_BAR_Y_OFFSET}
            ));
        }
        m_modifiedSinceLastUpdate = true;
    }
}

void Battery::updatePixels(){
    for(auto& content : m_contents){
        content->update();
    }
}
#include "Battery.h"

using namespace SmartGlasses;

Battery::Battery(battery_level_t initialLevel,bool overwrites, pixel_pair_t offsets, unsigned char animate,unsigned char priority,TaskHandle_t notifyOnDraw): Container(notifyOnDraw,"Header Battery",overwrites,offsets,animate,priority){
    m_displayables.push_back(std::make_shared<BatteryFrame>("Header battery frame",false,offsets,animate,priority));
    updateBatteryLevel(initialLevel);
}

void Battery::updateBatteryLevel(battery_level_t newLevel){
    const unsigned char numberOfBars = newLevel <= ONE_BAR_PERCENTAGE ? 1 : 
                                            newLevel <= TWO_BAR_PERCENTAGE ? 2 :
                                            newLevel <= THREE_BAR_BERCENTAGE ? 3 : 4; 
    const int currentNbBars = m_displayables.size()-1;
    if(numberOfBars<currentNbBars){
        for(int i=currentNbBars-numberOfBars;i>0;i--){
            m_displayables.pop_back();
        }
        m_modifiedSinceLastUpdate = true;
    }
    else if(numberOfBars>currentNbBars){
        const int nbBarsToAdd = numberOfBars - currentNbBars;
        for(int i=0;i<nbBarsToAdd;i++){
            std::string s = "Header Battery Bar";
            m_displayables.push_back(std::make_shared<BatteryBar>(
                s + static_cast<char>('0'+i),m_overwrite, 
                m_offsets+(pixel_pair_t){static_cast<unsigned char>(BATTERY_BAR_X_MIN_OFFSET - (i+1)*(BATTERY_BAR_SPACING+BATTERY_BAR_WIDTH)),BATTERY_BAR_Y_OFFSET},m_animate,m_priority
            ));
        }
        m_modifiedSinceLastUpdate = true;
    }
}

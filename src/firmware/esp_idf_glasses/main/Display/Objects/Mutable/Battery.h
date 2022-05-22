#pragma once

#include "BatteryBar.h"
#include "BatteryFrame.h"
#include "Display.h"
#include "Content.h"
#include "Container.h"

namespace SmartGlasses{

    typedef unsigned char battery_level_t;


    #define PERCENTAGE_PER_BAR 25
    #define BATTERY_BAR_Y_OFFSET 3
    #define BATTERY_BAR_X_MIN_OFFSET 15
    #define BATTERY_BAR_SPACING 1

    class Battery : public Content,Container{
    public:
        Battery(battery_level_t initialLevel = 100,bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char priority = 1);
        void updateBatteryLevel(battery_level_t newLevel);
    protected:
        void updatePixels() override;
    };

};
#pragma once

#include "BatteryBar.h"
#include "BatteryFrame.h"
#include "Display.h"
#include "Content.h"
#include "Container.h"

namespace SmartGlasses{

    typedef unsigned char battery_level_t;

    #define ONE_BAR_PERCENTAGE  10
    #define TWO_BAR_PERCENTAGE  30
    #define THREE_BAR_BERCENTAGE 60
    #define BATTERY_BAR_Y_OFFSET 3
    #define BATTERY_BAR_X_MIN_OFFSET 16
    #define BATTERY_BAR_SPACING 1

    class Battery : public Content,Container{
    public:
        Battery(battery_level_t initialLevel = 100,bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 1);
        void updateBatteryLevel(battery_level_t newLevel);
    protected:
        void updatePixels() override;
    };

};
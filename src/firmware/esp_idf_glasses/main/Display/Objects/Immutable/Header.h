#pragma once

#include "Content.h"
#include "Container.h"
#include <memory>
#include "Text.h"
#include "Bell.h"
#include "RawText.h"
#include "Battery.h"
#include "BLEIcon.h"
#include "constants.h"

namespace SmartGlasses{

    #define MINUTES_OFFSET_X (3*(8*sizeof(unsigned char) + 1))
    #define COLON_OFFSET_X (2*(8*sizeof(unsigned char) + 1))
    #define BELL_OFFSET_X 39
    #define NOTIFICATION_OFFSET_X ((BELL_OFFSET_X) + (BELL_WIDTH))
    #define BLEICON_OFFSET_X ((SCREEN_WIDTH) - (BLEICON_WIDTH))
    
    #define HEADER_M "Header"

    class Header : public ConstantContent, Container{
    public:
        Header(std::string& s,unsigned char hours = 0, unsigned char minutes = 0,bool overwrites = true, pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 2);

        void setup() override;
        void update() override;
    private: 
        std::shared_ptr<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>> m_hourText_p;
        std::shared_ptr<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>> m_minuteText_p;
        std::shared_ptr<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>> m_notificationText_p;
        std::shared_ptr<Battery> m_battery_p;
        std::shared_ptr<BLEIcon> m_bleIcon_p;
    };
};
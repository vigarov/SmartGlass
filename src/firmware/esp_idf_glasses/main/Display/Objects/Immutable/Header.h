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

    #define TEXT_OFFSET_Y 3
    #define MINUTES_OFFSET_X (COLON_OFFSET_X + (8*sizeof(unsigned char))-1)
    #define COLON_OFFSET_X (2*(8*sizeof(unsigned char))-1)
    #define BELL_OFFSET_X 55
    #define BELL_OFFSET_Y 1
    #define NOTIFICATION_OFFSET_X ((BELL_OFFSET_X) + (BELL_WIDTH)+2)
    #define BLEICON_OFFSET_X ((SCREEN_WIDTH) - (BLEICON_WIDTH)-1)
    #define BLEICON_OFFSET_Y 1
    #define BATTERY_OFFSET_X ((BLEICON_OFFSET_X)-(BATTERYFRAME_WIDTH)-5)

    #define HEADER_M "Header"

    class Header : public Container{
    public:
        Header(std::string& s,unsigned char hours = 0, unsigned char minutes = 0,bool overwrites = true, pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 2,TaskHandle_t notifyOnDraw = nullptr);
        /**
         * @brief Update the blink status of the BLE Icon
         * 
         * @param STARTstop true <=> start blinking
         */
        void updateBLEBlink(bool STARTstop);
        ~Header();
    private: 
        std::shared_ptr<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>> m_hourText_p;
        std::shared_ptr<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>> m_minuteText_p;
        std::shared_ptr<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>> m_notificationText_p;
        std::shared_ptr<Battery> m_battery_p;
        std::shared_ptr<BLEIcon> m_bleIcon_p;

        static void T_BLINK_ICON(void* pvParameters);
        TaskHandle_t m_blinkTask;
        bool m_bleBlinking = false;
    };
};
#include "Header.h"
#include "esp_log.h"
#include "HeaderOutline.h"

using namespace SmartGlasses;

Header::Header(std::string& s,unsigned char hours , unsigned char minutes ,bool overwrites, pixel_pair_t offsets , unsigned char animate, unsigned char priority,TaskHandle_t notifyOnDraw):
    Container(notifyOnDraw,s,overwrites,offsets,animate,priority),
    m_hourText_p(std::make_shared<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>>(Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>::textWithDefaultFontFrom(std::to_string((unsigned int)hours),overwrites,offsets+(pixel_pair_t){0,TEXT_OFFSET_Y},animate,priority))),
    m_minuteText_p(std::make_shared<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>>(Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>::textWithDefaultFontFrom(std::to_string((unsigned int)minutes),overwrites,offsets+(pixel_pair_t){MINUTES_OFFSET_X,TEXT_OFFSET_Y},animate,priority))),
    m_notificationText_p(std::make_shared<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>>(Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>::textWithDefaultFontFrom("0",overwrites,offsets+(pixel_pair_t){NOTIFICATION_OFFSET_X,TEXT_OFFSET_Y},animate,priority))),
    m_battery_p(std::make_shared<Battery>(67,overwrites,offsets + (pixel_pair_t){BATTERY_OFFSET_X,0},animate,priority)),
    m_bleIcon_p(std::make_shared<BLEIcon>(s+"BLE Icon",overwrites,offsets + (pixel_pair_t){BLEICON_OFFSET_X,BLEICON_OFFSET_Y},animate,priority))
    {
    std::string tempS = s+"Outline";
    m_displayables.push_back(std::make_shared<HeaderOutline>(tempS,overwrites,offsets,animate,priority));
    m_displayables.push_back(m_hourText_p);
    tempS = ":";
    m_displayables.push_back(std::make_shared<RawText>(tempS,overwrites,offsets+(pixel_pair_t){COLON_OFFSET_X,TEXT_OFFSET_Y},animate,priority));
    m_displayables.push_back(m_minuteText_p);
    tempS = s+"bell";
    m_displayables.push_back(std::make_shared<Bell>(tempS,overwrites,offsets+(pixel_pair_t){BELL_OFFSET_X,BELL_OFFSET_Y},animate,priority));
    m_displayables.push_back(m_notificationText_p);
    m_displayables.push_back(m_battery_p);
    m_displayables.push_back(m_bleIcon_p);
}

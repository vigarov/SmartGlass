#include "NavigationContainer.h"
#include "utils.h"
#include "RawText.h"

using namespace SmartGlasses;

NavigationContainer::NavigationContainer(const std::string& s,navigation_t navigation,bool overwrites, pixel_pair_t offsets, unsigned char animate, unsigned char priority,TaskHandle_t notifyOnDraw)
: Container(notifyOnDraw,s,overwrites,offsets,animate,priority),
 m_arrow_p(std::make_shared<Arrow>(m_contentName+" Arrow",navigation.direction,overwrites,offsets+(pixel_pair_t){ARROW_OFFSET_X,ARROW_OFFSET_Y},animate,priority)),
 m_ETAHour_p(std::make_shared<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>>(Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>::textWithDefaultFontFrom(timeToString((unsigned int)navigation.hour),overwrites,offsets+(pixel_pair_t){NAV_HOUR_OFFSET_X,NAV_HOUR_OFFSET_Y},animate,priority))),
 m_ETAMinute_p(std::make_shared<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>>(Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>::textWithDefaultFontFrom(timeToString((unsigned int)navigation.min),overwrites,offsets+(pixel_pair_t){NAV_MINUTE_OFFSET_X,NAV_MINUTE_OFFSET_Y},animate,priority))),
 m_distanceText_p(std::make_shared<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>>(Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>::textWithDefaultFontFrom(distanceToString(navigation.distance),overwrites,offsets+(pixel_pair_t){NAV_DISTANCE_OFFSET_X,NAV_DISTANCE_OFFSET_Y},animate,priority)))
{
    m_displayables.push_back(m_arrow_p);
    std::string tempS = "ETA";
    m_displayables.push_back(std::make_shared<RawText>(tempS,overwrites,offsets+(pixel_pair_t){NAV_ETA_TEXT_OFFSET_X,NAV_ETA_TEXT_OFFSET_Y},animate,priority));
    m_displayables.push_back(m_ETAHour_p);
    tempS = ":";
    m_displayables.push_back(std::make_shared<RawText>(tempS,overwrites,offsets+(pixel_pair_t){NAV_COLON_OFFSET_X,NAV_COLON_OFFSET_Y},animate,priority));
    m_displayables.push_back(m_ETAMinute_p);
    m_displayables.push_back(m_distanceText_p);
    id=NAVIGATION_CONTAINER_ID;
}

void NavigationContainer::changeDistance(unsigned int newDistance){
    m_distanceText_p->changeString(distanceToString(newDistance));
}
void NavigationContainer::changeEta(unsigned char hour,unsigned char min){
    m_ETAHour_p->changeString(timeToString(hour));
    m_ETAMinute_p->changeString(timeToString(min));
}
void NavigationContainer::changeNavigation(navigation_t newNav){
    ESP_LOGI(NCONT_M,"Updating with new navigation");
    m_arrow_p->changeDirection(newNav.direction);
    changeDistance(newNav.distance);
    changeEta(newNav.hour,newNav.min);
}
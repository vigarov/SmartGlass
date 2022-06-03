#pragma once

#include "Container.h"
#include "Navigation.h"
#include "Text.h"
#include "Arrow.h"

namespace SmartGlasses{
    class NavigationContainer : public Container{
        #define NAVIGATION_CONTAINER_ID 2
        #define ARROW_OFFSET_X 10
        #define ARROW_OFFSET_Y 25
        #define NAV_ETA_TEXT_OFFSET_X 98
        #define NAV_ETA_TEXT_OFFSET_Y 20
        #define NAV_HOUR_OFFSET_X 90
        #define NAV_HOUR_OFFSET_Y ((NAV_ETA_TEXT_OFFSET_Y)+10)
        #define NAV_COLON_OFFSET_X ((NAV_HOUR_OFFSET_X)+14)
        #define NAV_COLON_OFFSET_Y NAV_HOUR_OFFSET_Y
        #define NAV_MINUTE_OFFSET_X ((NAV_HOUR_OFFSET_X)+20)
        #define NAV_MINUTE_OFFSET_Y NAV_HOUR_OFFSET_Y
        #define NAV_DISTANCE_OFFSET_X ((ARROW_OFFSET_X) +3)
        #define NAV_DISTANCE_OFFSET_Y 52
    public:
        NavigationContainer(const std::string& s,navigation_t navigation,bool overwrites = true, pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 2,TaskHandle_t notifyOnDraw = nullptr);
    
        /**
         * @brief Utilitary function to update the distance to target
         * 
         * @param newDistance the new distacne
         */
        void changeDistance(unsigned int newDistance);
        /**
         * @brief Utilitary function to update the ETA to target
         * 
         * @param hour new hour
         * @param min new min
         */
        void changeEta(unsigned char hour,unsigned char min);
        /**
         * @brief Utilitary function several characteristics at once, or the direction
         * 
         * @param newNav the updated navigation object containing the new values
         */
        void changeNavigation(navigation_t newNav);
    private:
        
        std::shared_ptr<Arrow> m_arrow_p;
        std::shared_ptr<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>> m_ETAHour_p;
        std::shared_ptr<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>> m_ETAMinute_p;
        std::shared_ptr<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>> m_distanceText_p;
    };

};
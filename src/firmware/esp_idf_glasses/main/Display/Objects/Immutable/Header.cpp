#include "Header.h"
#include "esp_log.h"

using namespace SmartGlasses;

Header::Header(std::string& s,unsigned char hours , unsigned char minutes ,bool overwrites, pixel_pair_t offsets , unsigned char animate, unsigned char priority):
        ConstantContent(s,overwrites,offsets,animate,priority),
        m_hourText_p(std::make_shared<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>>(Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>::textWithDefaultFontFrom(std::to_string((unsigned int)hours),overwrites,offsets,animate,priority))),
        m_minuteText_p(std::make_shared<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>>(Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>::textWithDefaultFontFrom(std::to_string((unsigned int)minutes),overwrites,offsets+(pixel_pair_t){MINUTES_OFFSET_X,0},animate,priority))),
        m_notificationText_p(std::make_shared<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>>(Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>::textWithDefaultFontFrom("0",overwrites,offsets+(pixel_pair_t){NOTIFICATION_OFFSET_X,0},animate,priority))),
        m_battery_p(std::make_shared<Battery>(67,overwrites,offsets + (pixel_pair_t){BLEICON_OFFSET_X-BATTERYFRAME_WIDTH-1,0},animate,priority)),
        m_bleIcon_p(std::make_shared<BLEIcon>("Header BLE Icon",overwrites,offsets + (pixel_pair_t){BLEICON_OFFSET_X,0},animate,priority))
        {
        m_pixels.insert(std::move(pixel_pair_t{37, 0})); m_pixels.insert(std::move(pixel_pair_t{57, 0})); m_pixels.insert(std::move(pixel_pair_t{99, 0})); 
        m_pixels.insert(std::move(pixel_pair_t{37, 1})); m_pixels.insert(std::move(pixel_pair_t{57, 1})); m_pixels.insert(std::move(pixel_pair_t{99, 1})); 
        m_pixels.insert(std::move(pixel_pair_t{37, 2})); m_pixels.insert(std::move(pixel_pair_t{57, 2})); m_pixels.insert(std::move(pixel_pair_t{99, 2})); 
        m_pixels.insert(std::move(pixel_pair_t{37, 3})); m_pixels.insert(std::move(pixel_pair_t{57, 3})); m_pixels.insert(std::move(pixel_pair_t{99, 3})); 
        m_pixels.insert(std::move(pixel_pair_t{37, 4})); m_pixels.insert(std::move(pixel_pair_t{57, 4})); m_pixels.insert(std::move(pixel_pair_t{99, 4})); 
        m_pixels.insert(std::move(pixel_pair_t{37, 5})); m_pixels.insert(std::move(pixel_pair_t{57, 5})); m_pixels.insert(std::move(pixel_pair_t{99, 5})); 
        m_pixels.insert(std::move(pixel_pair_t{37, 6})); m_pixels.insert(std::move(pixel_pair_t{57, 6})); m_pixels.insert(std::move(pixel_pair_t{99, 6})); 
        m_pixels.insert(std::move(pixel_pair_t{37, 7})); m_pixels.insert(std::move(pixel_pair_t{57, 7})); m_pixels.insert(std::move(pixel_pair_t{99, 7})); 
        m_pixels.insert(std::move(pixel_pair_t{37, 8})); m_pixels.insert(std::move(pixel_pair_t{57, 8})); m_pixels.insert(std::move(pixel_pair_t{99, 8})); 
        m_pixels.insert(std::move(pixel_pair_t{37, 9})); m_pixels.insert(std::move(pixel_pair_t{57, 9})); m_pixels.insert(std::move(pixel_pair_t{99, 9})); 
        m_pixels.insert(std::move(pixel_pair_t{37, 10})); m_pixels.insert(std::move(pixel_pair_t{57, 10})); m_pixels.insert(std::move(pixel_pair_t{99, 10})); 
        m_pixels.insert(std::move(pixel_pair_t{37, 11})); m_pixels.insert(std::move(pixel_pair_t{57, 11})); m_pixels.insert(std::move(pixel_pair_t{99, 11})); 
        m_pixels.insert(std::move(pixel_pair_t{37, 12})); m_pixels.insert(std::move(pixel_pair_t{57, 12})); m_pixels.insert(std::move(pixel_pair_t{99, 12})); 
        m_pixels.insert(std::move(pixel_pair_t{0, 13})); m_pixels.insert(std::move(pixel_pair_t{1, 13})); m_pixels.insert(std::move(pixel_pair_t{2, 13})); m_pixels.insert(std::move(pixel_pair_t{3, 13})); m_pixels.insert(std::move(pixel_pair_t{4, 13})); m_pixels.insert(std::move(pixel_pair_t{5, 13})); m_pixels.insert(std::move(pixel_pair_t{6, 13})); m_pixels.insert(std::move(pixel_pair_t{7, 13})); m_pixels.insert(std::move(pixel_pair_t{8, 13})); m_pixels.insert(std::move(pixel_pair_t{9, 13})); m_pixels.insert(std::move(pixel_pair_t{10, 13})); m_pixels.insert(std::move(pixel_pair_t{11, 13})); m_pixels.insert(std::move(pixel_pair_t{12, 13})); m_pixels.insert(std::move(pixel_pair_t{13, 13})); m_pixels.insert(std::move(pixel_pair_t{14, 13})); m_pixels.insert(std::move(pixel_pair_t{15, 13})); m_pixels.insert(std::move(pixel_pair_t{16, 13})); m_pixels.insert(std::move(pixel_pair_t{17, 13})); m_pixels.insert(std::move(pixel_pair_t{18, 13})); m_pixels.insert(std::move(pixel_pair_t{19, 13})); m_pixels.insert(std::move(pixel_pair_t{20, 13})); m_pixels.insert(std::move(pixel_pair_t{21, 13})); m_pixels.insert(std::move(pixel_pair_t{22, 13})); m_pixels.insert(std::move(pixel_pair_t{23, 13})); m_pixels.insert(std::move(pixel_pair_t{24, 13})); m_pixels.insert(std::move(pixel_pair_t{25, 13})); m_pixels.insert(std::move(pixel_pair_t{26, 13})); m_pixels.insert(std::move(pixel_pair_t{27, 13})); m_pixels.insert(std::move(pixel_pair_t{28, 13})); m_pixels.insert(std::move(pixel_pair_t{29, 13})); m_pixels.insert(std::move(pixel_pair_t{30, 13})); m_pixels.insert(std::move(pixel_pair_t{31, 13})); m_pixels.insert(std::move(pixel_pair_t{32, 13})); m_pixels.insert(std::move(pixel_pair_t{33, 13})); m_pixels.insert(std::move(pixel_pair_t{34, 13})); m_pixels.insert(std::move(pixel_pair_t{35, 13})); m_pixels.insert(std::move(pixel_pair_t{36, 13})); m_pixels.insert(std::move(pixel_pair_t{37, 13})); m_pixels.insert(std::move(pixel_pair_t{38, 13})); m_pixels.insert(std::move(pixel_pair_t{39, 13})); m_pixels.insert(std::move(pixel_pair_t{40, 13})); m_pixels.insert(std::move(pixel_pair_t{41, 13})); m_pixels.insert(std::move(pixel_pair_t{42, 13})); m_pixels.insert(std::move(pixel_pair_t{43, 13})); m_pixels.insert(std::move(pixel_pair_t{44, 13})); m_pixels.insert(std::move(pixel_pair_t{45, 13})); m_pixels.insert(std::move(pixel_pair_t{46, 13})); m_pixels.insert(std::move(pixel_pair_t{47, 13})); m_pixels.insert(std::move(pixel_pair_t{48, 13})); m_pixels.insert(std::move(pixel_pair_t{49, 13})); m_pixels.insert(std::move(pixel_pair_t{50, 13})); m_pixels.insert(std::move(pixel_pair_t{51, 13})); m_pixels.insert(std::move(pixel_pair_t{52, 13})); m_pixels.insert(std::move(pixel_pair_t{53, 13})); m_pixels.insert(std::move(pixel_pair_t{54, 13})); m_pixels.insert(std::move(pixel_pair_t{55, 13})); m_pixels.insert(std::move(pixel_pair_t{56, 13})); m_pixels.insert(std::move(pixel_pair_t{57, 13})); m_pixels.insert(std::move(pixel_pair_t{58, 13})); m_pixels.insert(std::move(pixel_pair_t{59, 13})); m_pixels.insert(std::move(pixel_pair_t{60, 13})); m_pixels.insert(std::move(pixel_pair_t{61, 13})); m_pixels.insert(std::move(pixel_pair_t{62, 13})); m_pixels.insert(std::move(pixel_pair_t{63, 13})); m_pixels.insert(std::move(pixel_pair_t{64, 13})); m_pixels.insert(std::move(pixel_pair_t{65, 13})); m_pixels.insert(std::move(pixel_pair_t{66, 13})); m_pixels.insert(std::move(pixel_pair_t{67, 13})); m_pixels.insert(std::move(pixel_pair_t{68, 13})); m_pixels.insert(std::move(pixel_pair_t{69, 13})); m_pixels.insert(std::move(pixel_pair_t{70, 13})); m_pixels.insert(std::move(pixel_pair_t{71, 13})); m_pixels.insert(std::move(pixel_pair_t{72, 13})); m_pixels.insert(std::move(pixel_pair_t{73, 13})); m_pixels.insert(std::move(pixel_pair_t{74, 13})); m_pixels.insert(std::move(pixel_pair_t{75, 13})); m_pixels.insert(std::move(pixel_pair_t{76, 13})); m_pixels.insert(std::move(pixel_pair_t{77, 13})); m_pixels.insert(std::move(pixel_pair_t{78, 13})); m_pixels.insert(std::move(pixel_pair_t{79, 13})); m_pixels.insert(std::move(pixel_pair_t{80, 13})); m_pixels.insert(std::move(pixel_pair_t{81, 13})); m_pixels.insert(std::move(pixel_pair_t{82, 13})); m_pixels.insert(std::move(pixel_pair_t{83, 13})); m_pixels.insert(std::move(pixel_pair_t{84, 13})); m_pixels.insert(std::move(pixel_pair_t{85, 13})); m_pixels.insert(std::move(pixel_pair_t{86, 13})); m_pixels.insert(std::move(pixel_pair_t{87, 13})); m_pixels.insert(std::move(pixel_pair_t{88, 13})); m_pixels.insert(std::move(pixel_pair_t{89, 13})); m_pixels.insert(std::move(pixel_pair_t{90, 13})); m_pixels.insert(std::move(pixel_pair_t{91, 13})); m_pixels.insert(std::move(pixel_pair_t{92, 13})); m_pixels.insert(std::move(pixel_pair_t{93, 13})); m_pixels.insert(std::move(pixel_pair_t{94, 13})); m_pixels.insert(std::move(pixel_pair_t{95, 13})); m_pixels.insert(std::move(pixel_pair_t{96, 13})); m_pixels.insert(std::move(pixel_pair_t{97, 13})); m_pixels.insert(std::move(pixel_pair_t{98, 13})); m_pixels.insert(std::move(pixel_pair_t{99, 13})); m_pixels.insert(std::move(pixel_pair_t{100, 13})); m_pixels.insert(std::move(pixel_pair_t{101, 13})); m_pixels.insert(std::move(pixel_pair_t{102, 13})); m_pixels.insert(std::move(pixel_pair_t{103, 13})); m_pixels.insert(std::move(pixel_pair_t{104, 13})); m_pixels.insert(std::move(pixel_pair_t{105, 13})); m_pixels.insert(std::move(pixel_pair_t{106, 13})); m_pixels.insert(std::move(pixel_pair_t{107, 13})); m_pixels.insert(std::move(pixel_pair_t{108, 13})); m_pixels.insert(std::move(pixel_pair_t{109, 13})); m_pixels.insert(std::move(pixel_pair_t{110, 13})); m_pixels.insert(std::move(pixel_pair_t{111, 13})); m_pixels.insert(std::move(pixel_pair_t{112, 13})); m_pixels.insert(std::move(pixel_pair_t{113, 13})); m_pixels.insert(std::move(pixel_pair_t{114, 13})); m_pixels.insert(std::move(pixel_pair_t{115, 13})); m_pixels.insert(std::move(pixel_pair_t{116, 13})); m_pixels.insert(std::move(pixel_pair_t{117, 13})); m_pixels.insert(std::move(pixel_pair_t{118, 13})); m_pixels.insert(std::move(pixel_pair_t{119, 13})); m_pixels.insert(std::move(pixel_pair_t{120, 13})); m_pixels.insert(std::move(pixel_pair_t{121, 13})); m_pixels.insert(std::move(pixel_pair_t{122, 13})); m_pixels.insert(std::move(pixel_pair_t{123, 13})); m_pixels.insert(std::move(pixel_pair_t{124, 13})); m_pixels.insert(std::move(pixel_pair_t{125, 13})); m_pixels.insert(std::move(pixel_pair_t{126, 13})); m_pixels.insert(std::move(pixel_pair_t{127, 13})); 

        m_contents.push_back(m_hourText_p);
        std::string tempS = ":";
        m_contents.push_back(std::make_shared<RawText>(tempS,overwrites,offsets+(pixel_pair_t){COLON_OFFSET_X,0},animate,priority));
        m_contents.push_back(m_minuteText_p);
        tempS = "Header bell";
        m_contents.push_back(std::make_shared<Bell>(tempS,overwrites,offsets+(pixel_pair_t){BELL_OFFSET_X,0},animate,priority));
        m_contents.push_back(m_notificationText_p);
        m_contents.push_back(m_battery_p);
        m_contents.push_back(m_bleIcon_p);
    }

void Header::setup(){
    ESP_LOGI(HEADER_M,"Starting setup");
    ConstantContent::setup();
    vTaskDelay(30/portTICK_PERIOD_MS);
    for(auto & c : m_contents){
        c->setup();
        vTaskDelay(30/portTICK_PERIOD_MS); //To let the display time to update
    }
    ESP_LOGI(HEADER_M,"Finished setup");
}

void Header::update(){
    ESP_LOGD(HEADER_M,"Starting update");
    ConstantContent::update();
    vTaskDelay(30/portTICK_PERIOD_MS);
    for(auto & c : m_contents){
        c->update();
        vTaskDelay(30/portTICK_PERIOD_MS); //To let the display time to update
    }
}


#include "Header.h"
#include "esp_log.h"
#include "HeaderOutline.h"
#include "GlobalsManager.h"
#include "Timers.h"
#include "utils.h"

using namespace SmartGlasses;

Header::Header(std::string& s,unsigned char hours , unsigned char minutes ,bool overwrites, pixel_pair_t offsets , unsigned char animate, unsigned char priority,TaskHandle_t notifyOnDraw):
    Container(notifyOnDraw,s,overwrites,offsets,animate,priority),
    m_hourText_p(std::make_shared<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>>(Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>::textWithDefaultFontFrom(timeToString((unsigned int)hours),overwrites,offsets+(pixel_pair_t){0,TEXT_OFFSET_Y},animate,priority))),
    m_minuteText_p(std::make_shared<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>>(Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>::textWithDefaultFontFrom(timeToString((unsigned int)minutes),overwrites,offsets+(pixel_pair_t){MINUTES_OFFSET_X,TEXT_OFFSET_Y},animate,priority))),
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
    createTask(T_BLINK_ICON,"BLEIcon Blink",4096,BLINKING_TASKS_PRIORITY,&m_blinkTask,APP_CPU,m_bleIcon_p.get());
}
Header::~Header(){
    vTaskDelete(m_blinkTask);
}

void Header::T_BLINK_ICON(void* pvParameters){
    BLEIcon* bleIcon = static_cast<BLEIcon*>(pvParameters);
    bool state = false;
    while(1){
        ulTaskNotifyTake(pdTRUE,portMAX_DELAY);
        if(state){
            bleIcon->update();
        }
        else{
            bleIcon->hide();
        }
        state=!state;
    }
}

void Header::updateBLEBlink(bool STARTstop){
    ESP_LOGI(m_contentName.c_str(),"Updating BLE Blink with start = %s,m_bleBlinking=%s", STARTstop?"true":"false",m_bleBlinking?"true":"false");
    if(STARTstop){
        if(!m_bleBlinking){
            DEVICEMANAGER.getOneSecondTimer()->addTaskNotifiedOnAlarm(m_blinkTask);
            m_bleBlinking = true;
        }
    }
    else{
        if(m_bleBlinking){
            DEVICEMANAGER.getOneSecondTimer()->removeTaskNotifiedOnAlarm(m_blinkTask);
            m_bleBlinking = false;
        }
    }
}



void Header::updateTime(simple_time_t st){
    std::string s;
    if(st.hour!=-1){
        s=timeToString(st.hour);
        std::static_pointer_cast<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>>(m_displayables[HOUR_IDX])->changeString(s);
    }
    if(st.min!=-1){
        s=timeToString(st.min);
        std::static_pointer_cast<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>>(m_displayables[MINUTE_IDX])->changeString(s);
    }
}
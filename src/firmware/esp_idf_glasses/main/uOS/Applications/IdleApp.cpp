#include "IdleApp.h"
#include "Header.h"
#include "utils.h"
#include "constants.h"
#include "NotificationContainer.h"



using namespace SmartGlasses;

IdleApp::IdleApp(std::shared_ptr<uOS> uOS_p) : Application(uOS_p,IDLE){
    IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
    {
        auto tm = getCurrentTime();
        m_st = {tm->tm_hour,tm->tm_min};
    }
    std::string s = "Header";
   /*  m_displayables.push_back(std::make_shared<RawText>(s,false));
    m_displayables.push_back(std::make_shared<Battery>(88,false,(pixel_pair_t){100,0},0,3));
    //s = "arrowTop";
    //m_displayables.push_back(std::make_shared<StraightArrow>(s,true,(pixel_pair_t){36,0}));
    s = "arrowLeft";
    IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
    m_displayables.push_back(std::make_shared<LeftArrow>(s,true,(pixel_pair_t){36,15}));
    s = "500 M";
    m_displayables.push_back(std::make_shared<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>>(Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>::textWithDefaultFontFrom("500 m",true,{36,50},USE_ANIMATIONS,1)));
    //s = "arrowRight";*/
    //m_displayables.push_back(std::make_shared<RightArrow>(s,true,(pixel_pair_t){36,20}));
    m_displayables.push_back(std::make_shared<Header>(s,m_st.hour,m_st.min));
    notification_t n = {.application=FACEBOOK,.title={true,"test"},.additionalInfo={false,"test2"}};
    s="Idle notif";
    m_displayables.push_back(std::make_shared<NotificationContainer>(s,n,true,(pixel_pair_t){16,22}));
    IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
}

void IdleApp::onClose(){
    ESP_LOGI(IDLE_M,"Closed application");
}

void IdleApp::onResume(){
    ESP_LOGI(IDLE_M,"Resuming application");
    update();
    //vTaskDelay(10000 / portTICK_PERIOD_MS);
    //std::string ns = "hello";
    //static_cast<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>*>(m_displayables[m_displayables.size()-1].get())->changeString(ns);
}


void IdleApp::changeBLE(ble_status_t newStatus){
    ESP_LOGI(IDLE_M,"Got change request from %u,to%u",(unsigned int)m_ble_status,(unsigned int)newStatus);
    if(newStatus!=m_ble_status){
        if(newStatus == BLE_ADVERTISING){
            std::static_pointer_cast<Header>(m_displayables[HEADER_POS])->updateBLEBlink(true);
        }
        else{
            std::static_pointer_cast<Header>(m_displayables[HEADER_POS])->updateBLEBlink(false);
        }
    }
}

void IdleApp::run(){updateTime();}

void IdleApp::updateTime(){
    auto tm = getCurrentTime();
    simple_time_t st = {tm->tm_hour,tm->tm_min};
    if(st.hour!=m_st.hour){
        m_st.hour = st.hour;
    }
    else{
        st.hour=-1;
    }
    if(st.min!=m_st.min){
        m_st.min = st.min;
    }
    else{
        st.min=-1;
    }
    static_cast<Header*>(m_displayables[HEADER_POS].get())->updateTime(st);
     
}

void IdleApp::newNotification(notification_t n){

}


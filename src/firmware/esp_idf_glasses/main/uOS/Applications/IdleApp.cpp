#include "IdleApp.h"
#include "RawText.h"
#include "Battery.h"
#include "StraightArrow.h"
#include "LeftArrow.h"
#include "RightArrow.h" 
#include "Header.h"
#include "utils.h"
#include "constants.h"



using namespace SmartGlasses;

IdleApp::IdleApp(std::shared_ptr<uOS> uOS_p) : Application(uOS_p,IDLE){
    IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
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
    m_displayables.push_back(std::make_shared<Header>(s,15,37));
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
            static_cast<Header*>(m_displayables[HEADER_POS].get())->updateBLEBlink(true);
        }
        else{
            static_cast<Header*>(m_displayables[HEADER_POS].get())->updateBLEBlink(false);
        }
    }
}

void IdleApp::run(){}


#include "IdleApp.h"
#include "RawText.h"
#include "Battery.h"
#include "StraightArrow.h"
#include "LeftArrow.h"
#include "RightArrow.h"



using namespace SmartGlasses;

void IdleApp::onClose(){
    //There is no state to be saved for the idle app --> do nothing
    m_contents.clear();
    ESP_LOGI(IDLE_M,"Closed application");
}

void IdleApp::onResume(){
    ESP_LOGI(IDLE_M,"Resuming application");
    createAndDisplayHeader();
    for(auto& content_p : m_contents){
        content_p->setup();
    }
}

void IdleApp::run(){}

void IdleApp::createAndDisplayHeader(){
    heap_caps_print_heap_info(MALLOC_CAP_8BIT);
    std::string s = "test";
    m_contents.push_back(std::make_shared<RawText>(s,false));
    m_contents.push_back(std::make_shared<Battery>(88,false,(pixel_pair_t){100,0},3));
    //s = "arrowTop";
    //m_contents.push_back(std::make_shared<StraightArrow>(s,true,(pixel_pair_t){36,0}));
    s = "arrowLeft";
    heap_caps_print_heap_info(MALLOC_CAP_8BIT);
    m_contents.push_back(std::make_shared<LeftArrow>(s,true,(pixel_pair_t){36,15}));
    s = "500 M";
        m_contents.push_back(std::make_shared<RawText>(s,false,(pixel_pair_t){36,50}));
    //s = "arrowRight";
    //m_contents.push_back(std::make_shared<RightArrow>(s,true,(pixel_pair_t){36,20}));
    heap_caps_print_heap_info(MALLOC_CAP_8BIT);
}

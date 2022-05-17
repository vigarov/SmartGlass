#include "IdleApp.h"
#include "RawText.h"


using namespace SmartGlasses;

void IdleApp::onClose(){
    //There is no state to be saved for the idle app --> do nothing
    m_contents.clear();
    ESP_LOGI(IDLE_M,"Closed application");
}

void IdleApp::onResume(){
    ESP_LOGI(IDLE_M,"Resuming application");
    createAndDisplayHeader();
}

void IdleApp::run(){}

void IdleApp::createAndDisplayHeader(){
    std::string s = "test";
    m_contents.push_back(std::move(std::make_unique<RawText>(s,true)));
}

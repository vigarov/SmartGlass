#include "IdleApp.h"
#include "RawText.h"


using namespace SmartGlasses;

void IdleApp::onClose(){
    //There is no state to be saved for the idle app --> do nothing
    m_contents.clear();
}

void IdleApp::onResume(){
    createAndDisplayHeader();
}

void IdleApp::run(){}

void IdleApp::createAndDisplayHeader(){
    std::string s = "test";
    m_contents.push_back(std::move(std::make_unique<RawText>(s)));
}

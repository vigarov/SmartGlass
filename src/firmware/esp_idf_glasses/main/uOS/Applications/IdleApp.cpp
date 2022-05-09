#include "IdleApp.h"

using namespace SmartGlasses;

void IdleApp::onClose(){
    //There is no state to be saved for the idle app --> do nothing
}

void IdleApp::onResume(){
    displayHeader();
}

void IdleApp::displayHeader(){

}

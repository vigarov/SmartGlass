#include "ApplicationContainer.h"

using namespace SmartGlasses;

Application* ApplicationContainer::getCurrentApplication(){
    return currentApplication; //from ApplicationContainer
}

void ApplicationContainer::setCurrentApplication(Application* app){
    currentApplication->onClose();
    currentApplication = app;
    currentApplication->onResume();
}

void ApplicationContainer::setCurrentApplication(Application& app){
    setCurrentApplication(&app);
}
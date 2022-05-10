#include "ApplicationContainer.h"

using namespace SmartGlasses;

const Application* ApplicationContainer::getCurrentApplication(){
    return currentApplication.get(); //from ApplicationContainer
}

void ApplicationContainer::setCurrentApplication(std::shared_ptr<Application> app){
    currentApplication->onClose();
    currentApplication = app;
    currentApplication->onResume();
}

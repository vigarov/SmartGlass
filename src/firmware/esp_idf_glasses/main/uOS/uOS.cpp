#include "uOS.h"
#include "IdleApp.h"
#include "ApplicationContainer.h"

using namespace SmartGlasses;

void uOS::startUp(){
    //Upon startup, we want to start the Idle application
    //TODO: loading screen beforehand?

    std::shared_ptr<IdleApp> idleApp = std::make_shared<IdleApp>(shared_from_this());
    applications[IDLE] = idleApp;
    ApplicationContainer::getInstance().setCurrentApplication(idleApp);
}
#include "uOS.h"
#include "IdleApp.h"
#include "ApplicationContainer.h"

using namespace SmartGlasses;

void uOS::setup(){
    //Upon startup, we want to start the Idle application
    //doing it here insted of in ctor because we need `this` pointer to be created
    //TODO: loading screen beforehand?

    std::shared_ptr<IdleApp> idleApp = std::make_shared<IdleApp>(shared_from_this());
    applications[IDLE] = idleApp;
    ApplicationContainer::getInstance().setCurrentApplication(idleApp);
}
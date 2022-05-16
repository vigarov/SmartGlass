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
    ApplicationContainer::getInstance().init(idleApp);
}

void uOS::handleEvent(){
    if(xQueueReceive(xEventsQueue,&eventBuffer,2000/portTICK_PERIOD_MS) == pdPASS){

    }
    else{
        ESP_LOGI(UOS_M,"Didn't get an event after 2 seconds");
    }
}
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

QueueHandle_t uOS::getQueueHandle(){
    return xEventsQueue;
}

void uOS::handleEvent(){
    if(xQueueReceive(xEventsQueue,&eventBuffer,2000/portTICK_PERIOD_MS) == pdPASS){
        ESP_LOGI(UOS_M,"Got new event");
        switch (eventBuffer.id)
        {
        case BT_START_SEARCHING:
        {
            auto currapp = CURRENTAPP;
            if(currapp->id == IDLE){
                //Start blinking the BL icon <=> add as task handle to notify to the 1s Timer the handle of the updatePixel task of the BLEIcon (or its Container, see how this gets implemented)
                
            }
            break;
        }
        default:
            break;
        }
    }
    else{
        ESP_LOGI(UOS_M,"Didn't get an event after 2 seconds");
    }
}
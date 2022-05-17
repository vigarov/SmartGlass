#include "uOS.h"
#include "IdleApp.h"
#include "ApplicationContainer.h"
#include "BLECharacteristic.h"
#include "DeviceManager.h"

using namespace SmartGlasses;

void uOS::setup(){
    //Upon startup, we want to start the Idle application
    //doing it here insted of in ctor because we need `this` pointer to be created
    //TODO: loading screen beforehand?
    std::shared_ptr<IdleApp> idleApp = std::make_shared<IdleApp>(shared_from_this());
    ESP_LOGI(UOS_M,"Created IdleApp");
    applications[IDLE] = idleApp;
    ApplicationContainer::getInstance().init(idleApp);
    ESP_LOGI(UOS_M,"Initialized AC");
}   

QueueHandle_t uOS::getQueueHandle(){
    return xEventsQueue;
}

QueueHandle_t uOS::getButtonsQueue(){
    return xButtonsQueue;
}

void uOS::handleEvent(){
    if(xQueueReceive(xEventsQueue,&eventBuffer,500/portTICK_PERIOD_MS) == pdPASS){
        ESP_LOGI(UOS_M,"Got new event");
        //First check whether a button press hasn't happened in the meantime
        if(uxQueueMessagesWaiting(xButtonsQueue)!=0){
            ESP_LOGI(UOS_M,"But first got a button press");
            if(xQueueReceive(xButtonsQueue,&buttonBuffer,0) == pdPASS){
                uint32_t temp = (uint32_t)buttonBuffer.sender;
                handleButtonPress(static_cast<gpio_num_t>(temp));
            }
            else{
                ESP_LOGI(UOS_M,"one pending message in the queue, yet unable to take it: this shouldn't be possible");
            }
        }
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
        case NOTIFICATION_NEW:
        {
            auto notifCharac = static_cast<BLECharacteristic*>(eventBuffer.sender);
            std::string notifData = notifCharac->getValue();
            ESP_LOGI(UOS_M,"Received new notification %s",notifData.c_str());
            notification_t notification = {};
            memcpy(&notification,notifData.data(),sizeof(notification_t));
            notifCharac->setValue(0);
            //TODO: Do something with the notifiaction
            break;
        }
        default:
            break;
        }
    }
    else{
        ESP_LOGI(UOS_M,"Didn't get an event after .5 seconds. Now checking for button presses");

    }
}

void uOS::handleButtonPress(gpio_num_t button){
    switch (button)
    {
    case BUT_UP_PIN:
    {
        //TODO:do something
        break;
    }
    case BUT_DOWN_PIN:
    {
        //TODO:do something
        break;
    }
    case BUT_LEFT_BACK_PIN:
    {
        //TODO:do something
        break;
    }
    case BUT_RIGHT_SELECT_PIN:
    {
        //TODO:do something
        break;
    }
    default:
        ESP_LOGE(UOS_M,"Got button, yet didn't match any of the predefined button pins");
        break;
    }
}
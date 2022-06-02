#include "uOS.h"
#include "IdleApp.h"
#include "ApplicationContainer.h"
#include "BLECharacteristic.h"
#include "utils.h"
#include "DeviceManager.h"
#include "GlobalsManager.h"
#include "constants.h"


using namespace SmartGlasses;

void uOS::setup(){
    //Upon startup, we want to start the Idle application
    //doing it here insted of in ctor because we need `this` pointer to be created
    //TODO: loading screen beforehand?
    std::shared_ptr<IdleApp> idleApp = std::make_shared<IdleApp>(shared_from_this());
    applications[IDLE] = idleApp;
    ApplicationContainer::getInstance().init(idleApp);
    createTask(T_buttonPress,"Button Handler",4098,UOS_TASK_PRIORITY+1,&m_buttonTask,APP_CPU,this);
    ESP_LOGI(UOS_M,"Finished uOS setup");
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
        switch (eventBuffer.id)
        {
        case BT_DISCONNECT:
        {
            //Just disconnected :
            //Start advertising again 
            ESP_LOGI(UOS_M,"Bluetooth connection lost, starting advertising again");
            GLOBALSMANAGER.getBLEHandler()->startAdvertise();
            //TODO: only for a while: link to timer.
            break;
        }
        case BT_START_ADVERTISING:
        {
            ESP_LOGI(UOS_M,"Got started advertising");
            CURRENTAPP->changeBLE(BLE_ADVERTISING);
            
            break;
        }
        case NOTIFICATION_NEW:
        {
            auto notifCharac = static_cast<BLECharacteristic*>(eventBuffer.sender);
            std::string notifData = notifCharac->getValue();
            const size_t len = notifData.length();
            ESP_LOGI(UOS_M,"Received new notification, length=%d",len);
            notification_t notification{};
            const size_t copySize = len > sizeof(notification_t) ? sizeof(notification_t) : len;
            memcpy(&notification,notifData.data(),copySize);

            ESP_LOGI(UOS_M,"The notification's values are type ordinal =%d, titleTerminated=%d,title=%s,additionalInfoTerminated = %d,addidionalInfo=%s",notification.application,(int)(notification.title.isTerminated),notification.title.text,(int)(notification.additionalInfo.isTerminated),notification.additionalInfo.text);
            notifCharac->setValue("-1");
            notifCharac->notify();
            CURRENTAPP->newNotification(std::move(notification));
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

uOS::~uOS(){
    vTaskDelete(m_buttonTask);
    vQueueDelete(xEventsQueue);
    vQueueDelete(xButtonsQueue);
}

void uOS::T_buttonPress(void* pvParameters){
    uOS* u = static_cast<uOS*>(pvParameters);
    while(1){
        if(xQueueReceive(u->xButtonsQueue,&u->buttonBuffer,portMAX_DELAY) == pdPASS){
            ESP_LOGI(UOS_M,"Got a button press");
            uint32_t temp = (uint32_t)u->buttonBuffer.sender;
            u->handleButtonPress(static_cast<gpio_num_t>(temp));
        }
        else{
            ESP_LOGI(UOS_M,"No pending button presses even after max delay");
        }
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
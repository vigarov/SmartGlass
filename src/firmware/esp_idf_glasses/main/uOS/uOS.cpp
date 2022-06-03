#include "uOS.h"
#include "IdleApp.h"
#include "ApplicationContainer.h"
#include "BLECharacteristic.h"
#include "utils.h"
#include "DeviceManager.h"
#include "GlobalsManager.h"
#include "constants.h"
#include "Navigation.h"


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
            CURRENTAPP->changeBLE(BLE_OFF);
            GLOBALSMANAGER.getBLEHandler()->startAdvertise();
            //TODO: only for a while: link to timer.
            break;
        }
        case BT_CONNECT:
        {
            ESP_LOGI(UOS_M,"Bluetooth connection established");
            CURRENTAPP->changeBLE(BLE_ON);
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
            CURRENTAPP->newNotification(std::move(notification));
            notifCharac->setValue("-1");
            notifCharac->notify();
            break;
        }
        case TIME_UPDATE:
        {
            auto timeCharac = static_cast<BLECharacteristic*>(eventBuffer.sender);
            std::string timeData = timeCharac->getValue();
            const size_t len = timeData.length();
            ESP_LOGI(UOS_M,"Received time update, length=%d",len);
            struct tm t{};
            const size_t copySize = len > sizeof(struct tm) ? sizeof(struct tm) : len;
            memcpy(&t,timeData.data(),copySize);
            ESP_LOGI(UOS_M,"Fetched time: %d:%d",t.tm_hour,t.tm_min);
            updateTime(&t);
            break;
        }
        case NAVIGATION_UPDATE:
        {
            auto navCharac = static_cast<BLECharacteristic*>(eventBuffer.sender);
            std::string navData = navCharac->getValue();
            const size_t len = navData.length();
            ESP_LOGI(UOS_M,"Received navigation update, length=%d",len);
            navigation_t nav{};
            const size_t copySize = len > sizeof(navigation_t) ? sizeof(navigation_t) : len;
            memcpy(&nav,navData.data(),copySize);
            ESP_LOGI(UOS_M,"Got new navigation instruction: start:%u,dir=%u,dist=%u,h=%u,m=%u",(unsigned int)nav.STARTstop,(unsigned int)nav.direction,(unsigned int)nav.distance,(unsigned int)nav.hour,(unsigned int)nav.min);
            //TODO: do something with notification
            CURRENTAPP->getNavigation(nav);
            navCharac->setValue("-1");
            navCharac->notify();
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
#include "utils.h"
#include "constants.h"

#include "TaskManager.h"
#include "GlobalsManager.h"
#include "DeviceManager.h"

using namespace SmartGlasses;


TaskHandle_t* TaskManager::getTaskHandle(task_t taskType){
    if(taskType<NB_TASKS){
        return allTasks[taskType];
    }
    return nullptr;
}

void TaskManager::initAllTasks(){

    int error = createTask(T_HandleBLE,"BLEHandler",10240,configMAX_PRIORITIES-1, allTasks[T_BLE], PRO_CPU); //TODO: Handle errors
    error = createTask(T_HandleDisplay,"DisplayHandler",1024,2,allTasks[T_DISPLAY],APP_CPU);
    // error = createTask(T_HandleGNSS,"GNSSHandler",10240,1,allTasks[T_GNSS], APP_CPU);
}

void TaskManager::setBLEHandler(std::shared_ptr<BLEHandler> bleHandler){
    bHandler = bleHandler;
}

void TaskManager::notifyAllTasks(UBaseType_t notificationIdx){
    for (uint8_t i=0; i<NB_TASKS; i++) {
        TaskHandle_t* taskI = allTasks[i];
        if(taskI != nullptr){
            //xTaskNotifyGeneric is an internal function, not meant to be used (and not documented officially by esp)
            //using xTaskNotifyGiveIndexed, as specified by https://www.freertos.org/xTaskNotifyGive.html
            xTaskNotifyGiveIndexed(*taskI,notificationIdx); 
        }
    }
}

void TaskManager::T_HandleBLE(void *pvParameters){
    std::shared_ptr<BLEHandler> bHandler = std::make_shared<BLEHandler>();
    //The object has been created --> setting it to the TaskManager
    GlobalsManager::getInstance().getTaskManager().setBLEHandler(bHandler);

    while(1){
        //The BLE Task technically does nohting, since the server is event (and callback) driven
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}

/* void TaskManager::T_HandleGNSS(void *pvParameters){
    
} */


void TaskManager::T_HandleDisplay(void* pvParameters){
    DisplayManager* display_mgr;
    {
        GlobalsManager& glob_mgr = GlobalsManager::getInstance();
        display_mgr = &glob_mgr.getDeviceManager().getDisplayManager();
        display_mgr->setDisplayTask(glob_mgr.getTaskManager().getTaskHandle(T_DISPLAY));
    }
    while(1){
        display_mgr->refreshDisplay();
    }
}


#include "utils.h"
#include "constants.h"

#include "TaskManager.h"
#include "GlobalsManager.h"
#include "DeviceManager.h"
#include "esp_heap_trace.h"

using namespace SmartGlasses;


TaskHandle_t TaskManager::getTaskHandle(task_t taskType){
    if(taskType<NB_TASKS){
        return allTasks[taskType];
    }
    return nullptr;
}


void TaskManager::initAllTasks(){
    ESP_LOGI(TASK_M,"Initialising all tasks");
    IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
    int error = createTask(T_HandleBLE,"BLEHandler",5240,BLE_TASK_PRIORITY, &allTasks[T_BLE], PRO_CPU); 
    vTaskDelay(5 / portTICK_PERIOD_MS);
    error = createTask(T_HandleDisplay,"DisplayHandler",50960,DISPLAY_TASK_PRIORITY,&allTasks[T_DISPLAY],APP_CPU);
    // error = createTask(T_HandleGNSS,"GNSSHandler",10240,1,allTasks[T_GNSS], APP_CPU);
    error = createTask(T_HandleUOS,"uOS",5240,UOS_TASK_PRIORITY,&allTasks[T_UOS],APP_CPU,&allTasks[T_BLE]);
    IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
    ESP_LOGI(TASK_M,"Finished initialiing all tasks with error %d",error);
}


void TaskManager::notifyAllTasks(UBaseType_t notificationIdx){
    for (uint8_t i=0; i<NB_TASKS; i++) {
        TaskHandle_t taskI = allTasks[i];
        if(taskI != nullptr){
            //xTaskNotifyGeneric is an internal function, not meant to be used (and not documented officially by esp)
            //using xTaskNotifyGiveIndexed, as specified by https://www.freertos.org/xTaskNotifyGive.html
            xTaskNotifyGiveIndexed(taskI,notificationIdx); 
        }
    }
}

void TaskManager::T_HandleBLE(void *pvParameters){
    ESP_LOGI(TASK_M,"Entering BLE task");
    if(ulTaskNotifyTake(pdTRUE,700/portTICK_PERIOD_MS) == pdFALSE){
        ESP_LOGE(TASK_M,"Did not get updated after uOS task creation, continuing with setting up BLE");
    }
    ESP_LOGI(TASK_M,"Starting BLE task");
    std::shared_ptr<BLEHandler> bHandler = std::make_shared<BLEHandler>();
    //The object has been created --> setting it to the TaskManager
    GLOBALSMANAGER.setBLEHandler(bHandler);

    while(1){
        //The BLE Task technically does nohting, since the server is event (and callback) driven
        vTaskDelay(10/portTICK_PERIOD_MS);
    }
}


void TaskManager::T_HandleDisplay(void* pvParameters){    
    ESP_LOGI(TASK_M,"Starting Display task");
    std::shared_ptr<DisplayManager> display_mgr;
    {
        GlobalsManager& glob_mgr = GlobalsManager::getInstance();
        display_mgr = glob_mgr.getDeviceManager().getDisplayManager();
        display_mgr->setDisplayTask(glob_mgr.getTaskManager().getTaskHandle(T_DISPLAY));
    }
    while(1){
        display_mgr->refreshDisplay();
        vTaskDelay(1/portTICK_PERIOD_MS);
    }
}

void TaskManager::T_HandleUOS(void * pvParameters){
    ESP_LOGI(TASK_M,"Starting uOS task");
    std::shared_ptr<uOS> uOS_p = std::make_shared<uOS>();
    uOS_p->setup();
    GLOBALSMANAGER.setUOS(uOS_p);
    auto th_p = static_cast<TaskHandle_t*>(pvParameters);
    ESP_LOGI(TASK_M,"Finished setting up uOS");
    xTaskNotifyGive(*th_p);
    while(1){
        uOS_p->handleEvent();
        vTaskDelay(5/portTICK_PERIOD_MS);
    }
}
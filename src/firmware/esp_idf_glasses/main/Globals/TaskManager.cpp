#include "utils.h"
#include "constants.h"

#include "TaskManager.h"
#include "GlobalsManager.h"
#include "DeviceManager.h"

using namespace SmartGlasses;


TaskHandle_t TaskManager::getTaskHandle(task_t taskType){
    if(taskType<NB_TASKS){
        return allTasks[taskType];
    }
    return nullptr;
}

#define IMU_TASK_PRIORITY 4
#define DISPLAY_TASK_PRIORITY 4
#define UOS_TASK_PRIORITY 3
#define BLE_TASK_PRIORITY 1

void TaskManager::initAllTasks(){
    esp_log_level_set(TASK_M, ESP_LOG_VERBOSE);
    ESP_LOGI(TASK_M,"Initialising all tasks");
    int error = createTask(T_HandleBLE,"BLEHandler",10240,BLE_TASK_PRIORITY, &allTasks[T_BLE], PRO_CPU); //TODO: Handle errors
    error = createTask(T_HandleDisplay,"DisplayHandler",10240,DISPLAY_TASK_PRIORITY,&allTasks[T_DISPLAY],APP_CPU);
    error = createTask(T_HandleIMU,"IMUHandler",10240,IMU_TASK_PRIORITY,&allTasks[T_IMU],APP_CPU);
    // error = createTask(T_HandleGNSS,"GNSSHandler",10240,1,allTasks[T_GNSS], APP_CPU);
    error = createTask(T_HandleUOS,"uOS",40960,UOS_TASK_PRIORITY,&allTasks[T_UOS],APP_CPU);
    ESP_LOGI(TASK_M,"Finished initialiing all tasks");
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
        display_mgr->init();
        display_mgr->setDisplayTask(glob_mgr.getTaskManager().getTaskHandle(T_DISPLAY));
    }
    ESP_LOGI(TASK_M,"Finished setting up display");
    while(1){
        display_mgr->refreshDisplay();
        vTaskDelay(1/portTICK_PERIOD_MS);
    }
}

void TaskManager::T_HandleIMU(void* pvParameters) {
    ESP_LOGI(TASK_M, "Starting IMU task");
    std::shared_ptr<IMUManager> imu_mgr;
    GlobalsManager& glob_mgr = GlobalsManager::getInstance();
    imu_mgr = glob_mgr.getDeviceManager().getIMUManager();
    imu_mgr->init();
    ESP_LOGI(TASK_M,"Finished setting up IMU");
    while (true) {
        imu_mgr->debug_print_latest_event();

        vTaskDelay(2500/portTICK_PERIOD_MS);
    }
}

void TaskManager::T_HandleUOS(void * pvParameters){
    ESP_LOGI(TASK_M,"Starting uOS task");
    std::shared_ptr<uOS> uOS_p = std::make_shared<uOS>();
    uOS_p->setup();
    GLOBALSMANAGER.setUOS(uOS_p);
    ESP_LOGI(TASK_M,"Finished setting up uOS");

    while(1){
        uOS_p->handleEvent();
        vTaskDelay(50/portTICK_PERIOD_MS); // wait a good while because high priority task = others otherwise can't run.
    }
}
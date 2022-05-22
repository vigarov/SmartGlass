#include "constants.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "Arduino.h"

#include "utils.h"
#include "TaskManager.h"

using namespace SmartGlasses;


TaskHandle_t TaskManager::getTaskHandle(task_t taskType){
    if(taskType<NB_TASKS){
        return allTasks[taskType];
    }
    return nullptr;
}

#define BLE_TASK_PRIORITY 1

void TaskManager::initAllTasks(){
    esp_log_level_set(TASK_M, ESP_LOG_VERBOSE);
    ESP_LOGI(TASK_M,"Initialising all tasks");
    int error = createTask(T_HandleBLE,"BLEHandler",10240,BLE_TASK_PRIORITY, &allTasks[T_BLE], PRO_CPU); //TODO: Handle errors
    ESP_LOGI(TASK_M,"Finished initialiing all tasks");
}

void TaskManager::T_HandleBLE(void *pvParameters){
    ESP_LOGI(TASK_M,"Starting BLE task");
    std::shared_ptr<BLEHandler> bHandler = std::make_shared<BLEHandler>();
    //The object has been created --> setting it to the TaskManager

    while(1){
        //The BLE Task technically does nohting, since the server is event (and callback) driven
        int64_t curr_time = esp_timer_get_time();
        if (curr_time>=14950000 && curr_time<15050000) {
          uint16_t new_granny_status = true;
          bHandler->granny_fallen_char->setValue(new_granny_status);
          bHandler->granny_fallen_char->notify();
        }
        if (curr_time>=29950000 && curr_time<30050000) {
          uint16_t new_imu_power_state = 2;
          bHandler->motion_det_char->setValue(new_imu_power_state);
          bHandler->motion_det_char->notify();
        }
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}

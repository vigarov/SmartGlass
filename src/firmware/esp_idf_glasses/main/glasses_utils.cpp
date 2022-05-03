#include "glasses_utils.h"

void createTask(TaskHandle_t* out_task_handle, TaskFunction_t pvTaskCode, const char *const pcName, const uint32_t usStackDepth, void* const pvParameters, UBaseType_t uxPriority, const BaseType_t xCoreID){
    const char* debug_tag = "Task creation";

    #define PREFIX "Unable to create task "
    #define MID ", error: "
    #define TASK_ERROR_FMT  PREFIX "%s" MID "%d\n"

    int error = pdPASS;
    if((error = xTaskCreatePinnedToCore(pvTaskCode, pcName, usStackDepth, pvParameters,uxPriority,out_task_handle,xCoreID)) != pdPASS)
        // || allTasks[T_BLE] == NULL)
        {
        #if ARDUINO_IDE == 1
        std::cerr<< "-Error- " << debug_tag <<": "<<PREFIX<<idx<<MID<<error<<std::endl;
        #else
        ESP_LOGE(debug_tag, TASK_ERROR_FMT, pcName,error);
        #endif
    }
}
#pragma once

#include <type_traits>

#include "constants.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace SmartGlasses{

    /**
     * @brief Utilitary macro to take a semaphore infinitely
     * 
     */
    #define TAKE_S_INF(semaphore) xSemaphoreTake(semaphore,portMAX_DELAY)

    /**
     * @brief Creates a Task following the same parameters as FreeRTOS. Logs Errors

     * @return int the error code
     */
    int createTask(TaskFunction_t pvTaskCode, const char *const pcName, const uint32_t usStackDepth, UBaseType_t uxPriority, TaskHandle_t* out_task_handle, const BaseType_t xCoreID,  void* const pvParameters = static_cast<void *>(nullptr));

    /**
     * @brief Utilitary function to configure the time of ESP
     * Sets the timezone to Europe/Zurich, and the current time and date according to compile time
     * 
     */
    void resetTime();

};

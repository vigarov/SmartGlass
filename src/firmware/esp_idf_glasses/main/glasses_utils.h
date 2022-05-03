#pragma once
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//Logging
#if ARDUINO_IDE == 0 && CLION_IDE == 0
#include "esp_log.h"
#endif

#if ARDUINO_IDE==1 || CLION_IDE == 1
#define TAKE_S_INF(semaphore) do{}while(xSemaphoreTake(semaphore,portMAX_DELAY)== pdFALSE)
#else
#define TAKE_S_INF(semaphore) xSemaphoreTake(semaphore,portMAX_DELAY)
#endif

void createTask(TaskHandle_t* out_task_handle, TaskFunction_t pvTaskCode, const char *const pcName, const uint32_t usStackDepth, void* const pvParameters, UBaseType_t uxPriority, const BaseType_t xCoreID);
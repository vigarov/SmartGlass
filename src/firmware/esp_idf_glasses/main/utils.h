#pragma once

#include <type_traits>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace SmartGlasses{

    /**
     * @brief Utilitary method to compute constexpr for-loops
     * Is logically equivalent to 
     *  for(int i= Start; i<End; i+=Inc){f(i);}
     * For more info, see: https://artificial-mind.net/blog/2020/10/31/constexpr-for
     * 
     * @tparam Start index to begin the for iteration (included)
     * @tparam End index to end the for iteration (excluded)
     * @tparam Inc increment to add after each index
     * @tparam F Function type
     * @param f function to apply at each step
     */
    template <auto Start, auto End, auto Inc, class F>
    constexpr void constexpr_for(F&& f);

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
};
#pragma once

#include <type_traits>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <algorithm>
#include "Text.h"
#include "constants.h"

namespace SmartGlasses{

    #if DEBUG
    #define IFD(expression) expression
    #else 
    #define IFD(expression)
    #endif

    struct simple_time_t{
        int hour;
        int min;

        inline bool operator!=(const simple_time_t& other)const{
            return min != other.min||hour!=other.hour;
        }
    };


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

    /**
     * @brief Utilitary function to configure the time of ESP
     * Sets the timezone to Europe/Zurich, and the current time and date according to compile time
     * 
     */
    void resetTime();

    void updateTime(struct tm* t);

    struct tm* getCurrentTime();

    /**
     * @brief Utilitary function to transform a timeUnit's value into its corresponding string by appending "0" if needed
     * 
     * @param timeUnit the timeUnit's value
     * @return std::string the translated timeUnit inot a string
     */
    std::string timeToString(unsigned int timeUnit);

    //@see: https://stackoverflow.com/a/896440/8352508 
    template <typename InIt1, typename InIt2, typename OutIt>
    OutIt unordered_set_intersection(InIt1 b1, InIt1 e1, InIt2 b2, InIt2 e2, OutIt out) {
        while (!(b1 == e1)) {
            if (!(std::find(b2, e2, *b1) == e2)) {
                *out = *b1;
                ++out;
            }

            ++b1;
        }

        return out;
    }
};
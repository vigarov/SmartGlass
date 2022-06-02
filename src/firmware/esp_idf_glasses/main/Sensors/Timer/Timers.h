#pragma once

#include "driver/timer.h"
#include <unordered_set>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "Device.h"

namespace SmartGlasses{
    #define SYSTEM_TIMER_GROUP (TIMER_GROUP_0)
    #define TIMER_M "Timer Module"

    #define ONE_S_ID (TIMER_0)
    #define SIXTY_S_ID (TIMER_1)

    
    #define TIMER_DIVIDER         (16)  //  Hardware timer clock divider
    #define TIMER_SCALE           (TIMER_BASE_CLK / TIMER_DIVIDER)  // convert counter value to seconds

    #define RESTART_VALUE 0

    #define TIMER_TASK_UPDATER_PRIORITY 6


    /**
     * @brief Heper class for interacting with a timer
     * 
     * 
     * @tparam GROUP the Group of the timer (0 or 1). @see SYSTEM_TIMER_GROUP
     * @tparam ID the hardware id (0 or 1). @see ONE_S_ID and SIXTY_S_ID
     */
    template<timer_group_t GROUP, timer_idx_t ID>
    class Timer : public Device{
        friend class DeviceManager;
    public: 
        Timer();
        Timer(Timer const&) = delete;
        void operator=(Timer const&) = delete;


        void init() override;

        /**
         * @brief Start the timer with given configuration
         * Must be called before calling any other method.
         * @see See https://github.com/espressif/esp-idf/blob/v4.3/examples/peripherals/timer_group/main/timer_group_example_main.c
         * 
         * 
         * @param auto_reload (bool) specifieces whether is should reload the initial value (0), upon reaching timer_interval_sec
         * @param timer_interval_sec interval of rthe timer in seconds
         */
        void setup(timer_autoreload_t auto_reload, uint64_t timer_interval_sec);

        /**
         * @brief Adds the task referenced to by TaskHandle_t  to the list of 
         * tasks that will get notified when an alarm occurs (a.k.a every timer_interval_sec
         * specified on startup, or later modified)
         * 
         * @param handle handle of the task to get notified
         * @return true iff the task was correctly added
         */
        bool addTaskNotifiedOnAlarm(TaskHandle_t handle);
        /**
         * @brief Removes the specified task from the tasks that are to be notified
         * 
         * @param handle handle of the task to be notified
         * @return true iff the task was correctly notfified
         */
        bool removeTaskNotifiedOnAlarm(TaskHandle_t handle);

    private:        
        TaskHandle_t m_updaterTask = NULL;
        bool m_setup = false;
        void setInterval(uint64_t timer_interval_sec);
        uint64_t m_currentInterval = 0;
        SemaphoreHandle_t xSetSemaphore = xSemaphoreCreateBinary();
        std::unordered_set<TaskHandle_t> m_tasksToNotify;

        static bool alarmISR(void *pvParameters);
        static void T_NotifyAlarmSubscribers(void* pvParameters);
    };

};
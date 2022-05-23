#pragma once


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <memory>
#include "BLEHandler.h"

namespace SmartGlasses{

    enum task_t{
        T_BLE,
        T_DISPLAY,
        T_IMU,
//        T_GNSS,
        T_UOS,
        NB_TASKS
    };

    #define TASK_M "Task Module"

    /**
     * @brief Manager object for of our tasks.
     * Note: Is guaranteed to be created by the GlobalsManager
     * 
     */
    class TaskManager{
        friend class GlobalsManager;
    public:
        /**
         * @brief Get the TaskHandle of the running task
         * 
         * @param taskType the requested task
         * @return (TaskHandle_t) The TaskHandle associated to this task
         */
        TaskHandle_t getTaskHandle(task_t taskType);

        /**
         * @brief Creates and starts all the tasks
         * 
         */
        void initAllTasks();

        /**
         * @brief Notifies all the tasks of an event
         * 
         * @param notification_idx the index of the notification
         */
        void notifyAllTasks(UBaseType_t notificationIdx);

    private:
        TaskManager() = default;

        TaskHandle_t allTasks[NB_TASKS] = {0};


        //---------------------Tasks
        /**
         * @brief Task in charge of handling the bluetooth.
         * @arg pvParameters (void *) pointer to context parameters. Unused
         */
        static void T_HandleBLE( void *pvParameters);
        /**
         * @brief Task in charge of handling the Display.
         * @arg pvParameters (void *) pointer to context parameters. Unused
         */
        static void T_HandleDisplay(void* pvParameters);
        //static void T_HandleGNSS(void *pvParameters);
        static void T_HandleUOS(void* parameters);
        //static void T_HandleIMU(void* parameters);
    };

};
#pragma once


#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <memory>
#include "BLEHandler.h"

namespace SmartGlasses{

    enum task_t{
        T_BLE,
        T_DISPLAY,
        T_GNSS,
        NB_TASKS
    };

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
         * @return (const TaskHandle_t*) The TaskHandle associated to this task
         */
        TaskHandle_t* getTaskHandle(task_t taskType);

        /**
         * @brief Creates and starts all the tasks
         * 
         */
        void initAllTasks();

        /**
         * @brief Sets the BLEHandler pointer (makes a copy of the shared_ptr)
         * 
         * @param bHandler the (copy of) the shared ptr
         */
        void setBLEHandler(std::shared_ptr<BLEHandler> bleHandler);

        /**
         * @brief Notifies all the tasks of an event
         * 
         * @param notification_idx the index of the notification
         */
        void notifyAllTasks(UBaseType_t notification_idx);

    private:
        TaskManager() = default;

        TaskHandle_t* allTasks[NB_TASKS] = {0};
        
        std::shared_ptr<BLEHandler> bHandler; //shared_ptr because there will be two 'holders' the TaskManager, as well as the Task itself (which is static --> not same context)
        

        //---------------------Tasks
        /**
         * @brief Task in charge of handling the bluetooth.
         * @arg pvParameters (void *) pointer to context parameters. Unused
         */
        static void T_HandleBLE( void *pvParameters);
        static void T_HandleDisplay(void* pvParameters);
        static void T_HandleGNSS(void *pvParameters);

    };

};
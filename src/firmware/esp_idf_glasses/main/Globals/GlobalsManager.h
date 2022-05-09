#pragma once

#include "TaskManager.h"
#include "DeviceManager.h"

namespace SmartGlasses{

    /**
     * @brief Singleton manager object for all of our program's globals
     * 
     */
    class GlobalsManager{
    public:
        static GlobalsManager& getInstance();

        GlobalsManager(GlobalsManager const&) = delete;
        void operator=(GlobalsManager const&) = delete;

        /**
         * @brief Get the TaskManager object
         * 
         * @return (TaskManager&) reference to the TaskManager object 
         */
        TaskManager& getTaskManager();

        /**
         * @brief Get the DeviceManager object
         * 
         * @return (DeviceManager&) reference to the DeviceManager object
         */
        DeviceManager& getDeviceManager();


    private:
        GlobalsManager() = default;

        TaskManager taskManager;
        DeviceManager deviceManager;
    };
};
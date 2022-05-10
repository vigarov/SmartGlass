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

        
        /**
         * @brief Sets the BLEHandler pointer (makes a copy of the shared_ptr)
         * 
         * @param bHandler the (copy of) the shared ptr
         */
        void setBLEHandler(std::shared_ptr<BLEHandler> bleHandler);
        /**
         * @brief Get the BLEHandler pointer
         * 
         * @return std::shared_ptr<BLEHandler> the pointer
         */
        std::shared_ptr<BLEHandler> getBLEHandler();
    private:
        GlobalsManager() = default;

        TaskManager taskManager;
        DeviceManager deviceManager;

        std::shared_ptr<BLEHandler> bHandler; //shared_ptr because there will be at least two 'holders' the Globals, as well as the Task itself (which is static --> not same context)
        
        
    };
};
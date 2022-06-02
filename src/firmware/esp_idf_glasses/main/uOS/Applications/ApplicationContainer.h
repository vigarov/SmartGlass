#pragma once

#include "Application.h"

namespace SmartGlasses{


    #define APPCONT_M "Application Container"
    /**
     * @brief Container for the current application object. Thread safe singleton
     * 
     */
    class ApplicationContainer{
    public:
        /**
         * @brief Get the instance of the ApplicationContainer
         * 
         * @return ApplicationContainer& the application Conatiner
         */
        static ApplicationContainer& getInstance(){
            ESP_LOGD(APPCONT_M,"Getting application container instance");
            static ApplicationContainer instance;
            return instance;
        }
        /**
         * @brief Function initializing the application container. Must be called after object construction
         * 
         */
        void init(std::shared_ptr<Application> app);

        ApplicationContainer(ApplicationContainer const&) = delete;
        void operator=(ApplicationContainer const&) = delete;
        
        /**
         * @brief Get the current application object. Thread-safe, singleton. 
         * 
         * @return (Application*) the current application
         */
        std::shared_ptr<Application> getCurrentApplication();
        
        /**
         * @brief Sets the current Application by closing the current one and resuming the new one 
         * 
         * @param app the application
         */
        void setCurrentApplication(std::shared_ptr<Application> app);

        TaskHandle_t getAppTaskHandle();
        
    private:
        ApplicationContainer(){
            ESP_LOGI(APPCONT_M,"Creating application container");
        };
        
        std::shared_ptr<Application> currentApplication;
        
        SemaphoreHandle_t xAppSemaphore = xSemaphoreCreateBinary();
        static void runApplication(void* pvParameters);
        TaskHandle_t appTaskHandler = nullptr;
    };

    #define APPLICATIONCONTAINER (ApplicationContainer::getInstance())
    #define CURRENTAPP ((APPLICATIONCONTAINER).getCurrentApplication())
};
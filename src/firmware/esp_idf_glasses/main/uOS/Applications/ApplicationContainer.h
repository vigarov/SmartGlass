#pragma once

#include "Application.h"

namespace SmartGlasses{
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
            static ApplicationContainer instance;
            return instance;
        }

        ApplicationContainer(ApplicationContainer const&) = delete;
        void operator=(ApplicationContainer const&) = delete;
        
        /**
         * @brief Get the current application object. Thread-safe, singleton. 
         * 
         * @return (Application*) the current application
         */
        Application* getCurrentApplication();
        
        /**
         * @brief Sets the current Application by closing the current one and resuming the new one 
         * 
         * @param app the application
         */
        void setCurrentApplication(Application* app);
        void setCurrentApplication(Application& app);
    private:
        ApplicationContainer(){}
        
        Application* currentApplication;
    };

};
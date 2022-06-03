#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

namespace SmartGlasses{

    class Displayable{
    friend class Container;
    public:
        Displayable(std::string contentName = "Displayable Default Name",bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 1) :
        m_offsets(std::move(offsets)),m_contentName(std::move(contentName)),m_overwrite(overwrites),m_animate(animate),m_priority(priority){}

        virtual void changeTaskToBeUpdated(TaskHandle_t newTask){
            m_taskToNotifyOnDraw = newTask;
        }

        virtual void update() = 0;
        virtual void hide() = 0;

        /**
         * @brief id for each displayable: no time to refactor so that all displayables have an unique one 
         * -> default 0 and this field will be used iff a displayable needs it (e.g.: notification displayable in idleApp)
         * 
         */
        unsigned char id = 0;
    protected:
        pixel_pair_t m_offsets;


        /**
         * @brief Flag indicating whether the pixels have changed since the last update
         *  ! Important Note: children classes are responsible for updating it accordingly when updatePixels() is called
         * 
         */
        bool m_modifiedSinceLastUpdate = true;
        std::string m_contentName;
        bool m_overwrite;
        bool m_animate;
        unsigned char m_priority;

        TaskHandle_t m_taskToNotifyOnDraw = nullptr;
    };
};
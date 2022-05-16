#pragma once
#include <memory>
#include <unordered_set>
#include <string>
#include "Display.h"
#include "esp_log.h"
#include "utils.h"

namespace SmartGlasses{

    #define DISPLAYABLE_UPDATE_PRIORITY 3

    class Container; //Forward Declaration

    class Content {
        
    public:
        Content(std::string contentName = "Default Name",bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char priority = 1,std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction>pixels = std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction>()) : 
        m_pixels(std::move(pixels)),m_offsets(std::move(offsets)),m_contentName(std::move(contentName)),m_overwrite(overwrites), m_priority(priority) {
            ESP_LOGI(m_contentName.c_str(), "Creating displayable object");
        }
        /**
         * @brief Function that must be called upon construction. Creates the task associated to this object
         */
        virtual void setup(); //Must be called after constructor
        /**
         * @brief Function used to wake the task --> new input is ready for the piece of content
         * 
         */
        virtual void update();
        virtual ~Content();

    protected:
        /**
         * @brief Function called every time new content is available. Is in charge of updating the pixels. 
         * 
         */
        virtual void updatePixels() = 0;
        
        /**
         * @brief Utilitary function to both compute the new canvas and update the display
         * 
         */
        void canvasAndUpdate();
        
        /**
         * @brief Function used to compute the canvas = the pixels, which, when overwriting, are to be cleared implicitely
         * This function assumes a square canvas, which it recomputes every time. Bases itself on the state of m_pixels at that time --> must call updatePixels() beforehand
         */
        void computeCanvas();
       
        /**
         * @brief create the task responsible for updatinb the content.
         * Only useful if object is mutable
         * 
         */
        virtual void createUpdateTask();

        std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction> m_pixels;
        std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction> m_canvas;

        border_t m_borders = {{UINT8_MAX,UINT8_MAX},{0,0}};
        const pixel_pair_t m_offsets;

        /**
         * @brief Flag indicating whether the pixels have changed since the last update
         *  ! Important Note: childrent classes are responsible for updating it accordingly when updatePixels() is called
         * 
         */
        bool m_modifiedSinceLastUpdate = false;
    private :
        std::string m_contentName;
        bool m_setup = false;
        
        bool m_overwrite;

        TaskHandle_t m_innerObjectTask = NULL;

        unsigned char m_priority;

        static void T_Update(void* pvParameters);
    };

    class ConstantContent : public Content{
    public:
        ConstantContent(std::string contentName = "Constant Content", bool overwrites = false, pixel_pair_t offsets = {0,0},unsigned char priority = 1) : Content(contentName,overwrites,std::move(offsets),priority){m_modifiedSinceLastUpdate = true;}
        void setup() override {canvasAndUpdate();}
        void update() override {}
    protected:
        void createUpdateTask() override {} //constant --> no update task
        void updatePixels() override{} //constant --> will be no case to update the pixels
    };
};
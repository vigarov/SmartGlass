#pragma once
#include <memory>
#include <unordered_set>
#include <string>
#include "Display.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Displayable.h"

namespace SmartGlasses{

    #define DISPLAYABLE_UPDATE_PRIORITY 3

    class Container; //Forward Declaration

    class Content : public Displayable{
    public:
        Content(std::string contentName = "Default Name",bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 1) : 
        Displayable(std::move(contentName),overwrites,std::move(offsets),animate,priority) {
            ESP_LOGI(m_contentName.c_str(), "Creating displayable object");
        }
        /**
         * @brief Function used to wake the task --> new input is ready for the piece of content
         * 
         */
        void update() override;
        void hide() override;

        /**
         * getter for the borders
         * @return (border_t) the last computed border
         */
        border_t getBorders();
    protected:
        
        void forceDisplay();
        void forceHide();

        /**
         * @brief Function called every time new content is available. Is in charge of updating the pixels. 
         * Is responsible to update m_modifiedSinceLastUpdate whenever the pixels have changed
         */
        virtual std::unique_ptr<pixels_set_t> createPixels() = 0;
        
        /**
         * @brief Utilitary function to both compute the new canvas and update the display
         * 
         */
        void canvasAndUpdate(std::unique_ptr<pixels_set_t> pixels);
        
        /**
         * @brief Function used to compute the canvas = the pixels, which, when overwriting, are to be cleared implicitely
         * This function assumes a square canvas, which it recomputes every time. Bases itself on the state of m_pixels at that time --> must call updatePixels() beforehand
         */
        std::unique_ptr<pixels_set_t> computeCanvas(const pixels_set_t& pixels);
        border_t m_borders = {{UINT8_MAX,UINT8_MAX},{0,0}};
        
        
        unsigned char m_animate = false;
    private :
        std::unique_ptr<pixels_set_t> actuallyComputeCanvas(const pixels_set_t& pixels);
        void actuallyUpdateDisplay(std::unique_ptr<pixels_set_t> pixels,std::unique_ptr<pixels_set_t> canvas);
    };

    class ConstantContent : public Content{
    public:
        ConstantContent(std::string contentName = "Constant Content", bool overwrites = false, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1) : Content(std::move(contentName),overwrites,std::move(offsets),animate,priority){}
        void update() override {forceDisplay();}
    };
};
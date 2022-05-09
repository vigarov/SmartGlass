#pragma once

#include <memory>

#include "HyperDisplay_UG2856KLBAG01.h"

namespace SmartGlasses{
    
    /**
     * @brief a pair of pixels
     * could also use std::pair<unsigned char> instead, but this is clearer
     */
    struct __attribute__((packed)) pixel_pair_t{
        unsigned char x;
        unsigned char y;
    };

    /**
     * @brief A drawable object, defined as a set of pixels at an offset
     * 
     */
    struct __attribute__((packed)) Drawable{
        std::vector<pixel_pair_t> pixels;
        unsigned char offsetX;
        unsigned char offsetY;
        unsigned char overwrite;
    };

    /**
     * @brief the type of the pending object we would like to display
     * 
     */
    struct __attribute__((packed)) display_t{
    unsigned char priority; //TODO: can make it a bitfield to save... one byte if necessary
    Drawable object;
    };
    
    #define CS_PIN 4
    #define DC_PIN 5

    class DisplayManager {
        friend class DeviceManager;
    private:
        UG2856KLBAG01_SPI backend_display;

        SemaphoreHandle_t xDisplayUpdateSemaphore;
        std::unique_ptr<display_t> currentFrames = std::make_unique<display_t>();

        TaskHandle_t* displaySenderTask;

        void init();
    public:
        DisplayManager();

        void update_awaiting_display(std::unique_ptr<display_t> newFrames); //Accepting ownership, call with std::move
        void setDisplayTask(TaskHandle_t* displayTask);
        void refreshDisplay();
    };
};
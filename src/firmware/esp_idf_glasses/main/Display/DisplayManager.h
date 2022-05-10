#pragma once

#include <memory>
#include "HyperDisplay_UG2856KLBAG01.h"
#include "Display.h"

namespace SmartGlasses{

    #define DISPLAY_M "Display Manager Module"
    #define CS_PIN 4
    #define DC_PIN 5

    class DisplayManager {
        friend class DeviceManager;
    private:
        UG2856KLBAG01_SPI backend_display;

        SemaphoreHandle_t xDisplayUpdateSemaphore;
        std::unique_ptr<display_t> currentFrames = std::make_unique<display_t>();

        TaskHandle_t displaySenderTask;

        void init();
    public:
        DisplayManager();

        void update_awaiting_display(std::unique_ptr<display_t> newFrames); //Accepting ownership, call with std::move
        void setDisplayTask(TaskHandle_t displayTask);
        void refreshDisplay();
    };
};
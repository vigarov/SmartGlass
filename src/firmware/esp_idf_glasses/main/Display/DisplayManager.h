#pragma once

#include <memory>
#include "HyperDisplay_UG2856KLBAG01.h"
#include "Display.h"
#include "Device.h"

namespace SmartGlasses{

    #define DISPLAY_M "Display Manager Module"
    #define CS_PIN 5
    #define DC_PIN 19

    class DisplayManager : public Device{
        friend class DeviceManager;
    private:
        UG2856KLBAG01_SPI backend_display;

        SemaphoreHandle_t xDisplayUpdateSemaphore = xSemaphoreCreateBinary();
        std::unique_ptr<display_t> currentFrames = std::make_unique<display_t>();

        TaskHandle_t displaySenderTask = NULL;

        void init() override;
    public:
        DisplayManager() = default;

        void update_awaiting_display(std::unique_ptr<display_t> newFrames); //Accepting ownership, call with std::move
        void setDisplayTask(TaskHandle_t displayTask);
        void refreshDisplay();
    };
};
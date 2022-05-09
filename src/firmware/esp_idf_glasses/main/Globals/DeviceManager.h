#pragma once
#include "Display.h"

namespace SmartGlasses{

    /**
     * @brief Manager objects for our devices, such as the display, GNSS module, ...
     * Note: Is guaranteed to be created by the GlobalsManager
     * 
     */
    class DeviceManager{
        friend class GlobalsManager;
    public:
        DisplayManager& getDisplayManager();
    private:
        DeviceManager() = default;
        DisplayManager displayManager;
    };
};
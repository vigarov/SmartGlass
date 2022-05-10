#pragma once
#include "DisplayManager.h"
#include <memory>

namespace SmartGlasses{

    /**
     * @brief Manager objects for our devices, such as the display, GNSS module, ...
     * Note: Is guaranteed to be created by the GlobalsManager
     * 
     */
    class DeviceManager{
        friend class GlobalsManager;
    public:
        std::shared_ptr<DisplayManager> getDisplayManager();
    private:
        DeviceManager() = default;
        std::shared_ptr<DisplayManager> displayManager = std::make_shared<DisplayManager>();
    };
};
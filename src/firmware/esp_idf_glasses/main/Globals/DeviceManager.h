#pragma once
#include "DisplayManager.h"
#include "IMUManager.h"
#include "GNSSManager.h"
#include "Timers.h"
#include "Device.h"
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
        void initAll();
        std::shared_ptr<DisplayManager> getDisplayManager();
        std::shared_ptr<IMUManager> getIMUManager();
        std::shared_ptr<GNSSManager> getGNSSManager();
        std::shared_ptr<Timer<SYSTEM_TIMER_GROUP,ONE_S_ID>> getOneSecondTimer();
        std::shared_ptr<Timer<SYSTEM_TIMER_GROUP,SIXTY_S_ID>> getSixtySecondTimer();
    private:
        enum device_idx{
            DISPLAY_IDX,
            IMU_IDX,
            GNSS_IDX,
            TIMER_1s_IDX,
            TIMER_60s_IDX,
            //...
            NB_DEVICES
        };

        DeviceManager();

        std::shared_ptr<Device> m_allDevices[NB_DEVICES];
    };
};
#pragma once
#include "uOS.h"
#include "Application.h"
#include <memory>

namespace SmartGlasses{

    class IdleApp : public Application{
        #define IDLE_M "Idle App"
        #define HEADER_POS 0
    public:
        IdleApp(std::shared_ptr<uOS> uOS_p);
        void changeBLE(ble_status_t newStatus) override;
    private:
        ble_status_t m_ble_status = BLE_ON;
        void onClose() override;
        void onResume() override;
        void run() override;
    };

}
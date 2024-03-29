#pragma once
#include "uOS.h"
#include "Application.h"
#include "utils.h"
#include <memory>

namespace SmartGlasses{
    class IdleApp : public Application{
        #define IDLE_M "Idle App"
        #define HEADER_POS 0
        #define MAX_SECONDS_TEMP_DISPLAY 5

        #define NOTIF_OFFSET_X 12
        #define NOTIF_OFFSET_Y 20
    public:
        IdleApp(std::shared_ptr<uOS> uOS_p);
        void changeBLE(ble_status_t newStatus) override;
        void newNotification(notification_t n) override;
        void getNavigation(navigation_t newNavigation) override;

        void onClose() override;
        void onResume() override;
        void run() override;
    private:
        ble_status_t m_ble_status = BLE_ON;
        simple_time_t m_st;
        void updateTime();

        SemaphoreHandle_t m_notifDisplaySemaphore = xSemaphoreCreateBinary();
        TaskHandle_t m_displayTimerTask = nullptr;
        unsigned char m_secondsDisplayedCount = 0;
        static void T_DISPLAY_COUNT(void* pvParameters);

        void eraseDisplayableTask();

        bool m_createdNav = false;
        void showNavigationTask();
        void hideNavigationTask();
        void updateAndShowNav(navigation_t n);
    };

}
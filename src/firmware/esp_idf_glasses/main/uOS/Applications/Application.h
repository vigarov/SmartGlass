#pragma once

#include <memory>
#include "DisplayManager.h"
#include "Content.h"
#include "Container.h"
#include "Notification.h"
#include "Navigation.h"
#include <vector>

namespace SmartGlasses{

    enum APP_ID{
        NONE=-1,
        IDLE,
        //...
        NB_APPS
    };

    
    enum ble_status_t{
        BLE_OFF,
        BLE_ADVERTISING,
        BLE_ON
    };


    class uOS;//Forward declaration

    /**
     * @brief Base class for any application.
     * 
     */
    class Application : public Container{
    public:
        Application(std::shared_ptr<uOS> uOS_p, APP_ID id);

        APP_ID id = NONE;
        /**
         * @brief Function called when closing the application
         * 
         */
        virtual void onClose() = 0;
        /**
         * @brief Function called when resuming the application
         * 
         */
        virtual void onResume() = 0;

        /**
         * @brief Function continuously called to execute (in a while(1) fashion)
         * 
         */
        virtual void run() = 0;

        virtual void changeBLE(ble_status_t newStatus){}
        virtual void getNavigation(navigation_t newNavigation){}

        virtual void newNotification(notification_t n) = 0;
    protected:
        std::shared_ptr<uOS> m_uOS;
        std::shared_ptr<DisplayManager> m_displayManager;
    };

};
#pragma once

#include "Display.h"
#include "Notification.h"
#include "Container.h"
#include "Logos.h"
#include <memory>
#include <string>

namespace SmartGlasses{

    class NotificationContainer : public Container{
        #define NOTIF_LOGO_OFFSET_Y 10
        #define NOTIF_TITLE_OFFSET_X 22
        #define NOTIF_TITLE_OFFSET_Y 7
        #define NOTIF_ADDINFO_OFFSET_X ((NOTIF_TITLE_OFFSET_X)+5)
        #define NOTIF_ADDINFO_OFFSET_Y ((NOTIF_TITLE_OFFSET_Y)+10)
        #define NOTIFICATION_CONTAINER_ID 1
    public:
        NotificationContainer(const std::string& s,notification_t notifcation,bool overwrites = true, pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 2,TaskHandle_t notifyOnDraw = nullptr);
    private:
        notification_t m_notification;

        std::shared_ptr<Logo> getNotificationLogo(app_t n, pixel_pair_t offsets);
        std::string parseTerminated(char* s, bool terminated);
    };

};
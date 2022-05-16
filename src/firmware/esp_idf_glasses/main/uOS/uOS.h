#pragma once

#include "Notification.h"
#include <memory>
#include <array>

#include "Application.h"

namespace SmartGlasses{
    #define MAX_PENDING_EVENTS 5
    #define UOS_M "uOS Module"

    enum uOSEventID{
        NB_EVENTS
    };

    struct uOSEvent{
        uOSEventID id;
    };

    class uOS: public std::enable_shared_from_this<uOS>{
    public:
        uOS() = default;
        void setup();
        void handleEvent();
    private:
        unsigned short nbUnreadNotifications = 0;
        QueueHandle_t xEventsQueue = xQueueCreate(MAX_PENDING_EVENTS,sizeof(uOSEvent));
        uOSEvent eventBuffer = {};

        std::array<std::shared_ptr<Application>, NB_APPS> applications{};
    };

};
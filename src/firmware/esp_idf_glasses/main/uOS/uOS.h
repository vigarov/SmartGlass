#pragma once

#include "Notification.h"
#include <memory>
#include <array>

#include "Application.h"

namespace SmartGlasses{
    #define MAX_PENDING_EVENTS 5
    #define MAX_BUTTON_EVENTS 1
    #define UOS_M "uOS Module"

    enum uOSEventID{
        BT_DISCONNECT,
        BT_START_SEARCHING,
        BT_STOP_SEARCHING,
        BT_CONNECT,
        NOTIFICATION_NEW,
        BUTTON_PRESSED,
        NB_EVENTS
    };

    struct uOSEvent{
        uOSEventID id;
        void* sender;
    };

    class uOS: public std::enable_shared_from_this<uOS>{
    public:
        uOS() = default;
        void setup();
        void handleEvent();
        QueueHandle_t getQueueHandle();
        QueueHandle_t getButtonsQueue();
    private:
        unsigned short nbUnreadNotifications = 0;
        QueueHandle_t xEventsQueue = xQueueCreate(MAX_PENDING_EVENTS,sizeof(uOSEvent));
        QueueHandle_t xButtonsQueue = xQueueCreate(MAX_BUTTON_EVENTS,sizeof(uOSEvent));
        
        uOSEvent eventBuffer = {};
        uOSEvent buttonBuffer = {};

        void handleButtonPress(gpio_num_t button);

        std::array<std::shared_ptr<Application>, NB_APPS> applications{};
    };

};
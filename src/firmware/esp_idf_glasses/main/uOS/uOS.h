#pragma once

#include "Notification.h"
#include <memory>
#include <array>

#include "Application.h"

namespace SmartGlasses{

    class uOS: public std::enable_shared_from_this<uOS>{
    public:
        uOS() = default;
        void setup();
    private:
        unsigned short nbUnreadNotifications = 0;
        
        std::array<std::shared_ptr<SmartGlasses::Application>, NB_APPS> applications{};
    };

};
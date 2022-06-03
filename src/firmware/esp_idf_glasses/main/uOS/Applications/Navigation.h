#pragma once

namespace SmartGlasses{

    enum direction_t : uint8_t{
        FORWARD,
        LEFT,
        RIGHT
    };

    struct __attribute__((packed,aligned(8))) navigation_t{
        unsigned char STARTstop;
        direction_t direction;
        uint32_t distance;
        unsigned char hour;
        unsigned char min;
    };
};
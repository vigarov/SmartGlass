#pragma once

#include <cstdint>

namespace SmartGlasses{
    struct __attribute__((packed)) utc_time_t{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    };
};
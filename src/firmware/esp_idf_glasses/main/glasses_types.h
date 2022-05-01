#pragma once
//Notifications
template<size_t SIZE>
struct __attribute__((packed, aligned(1))) content_t{
    unsigned char terminated;
    char text[SIZE];
};

enum app_t : uint16_t{
    SYSTEM,
    SMS,
    WHATSAPP,
    //...
    OTHER
};

//Make sure to align with the correct amount of bytes
struct __attribute__((packed, aligned(64))) notification_t{
    app_t application;
    content_t<MAX_TITLE_LENGTH> title;
    content_t<MAX_ADD_INFO_LENGTH> additionalInfo;
};

//Tasks
typedef enum{
    T_BLE,
    T_DISPLAY,
  
    NB_TASKS
}task_idx;

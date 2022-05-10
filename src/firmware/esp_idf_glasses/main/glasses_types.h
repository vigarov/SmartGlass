#pragma once
#include <stdint.h>
#include <stddef.h>
#include "glasses_constants.h"

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
    T_GNSS,
    NB_TASKS
}task_idx;


typedef enum{
    NOTIF_BUFFER,
    GNSS_FEATURES_CHAR,
    GNSS_CHAR,
    //...
    BATTERY_LEVEL,
    NB_CHARS
}CHAR_IDX;

typedef enum{
	NOTIF_SERVICE,
	GNSS_SERVICE,
	//IMU_SERVICE,
	BATTERY_SERVICE,
	NB_SERVICES
} svc_idx_e;

typedef enum {
    BLE_INIT_READY,
    DISPLAY_UPDATE,
    NB_TASK_NOTIFICATIONS
} task_notification_idx;

typedef struct __attribute__((packed)){
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
} utc_time_t;

typedef struct __attribute__((packed)){
  // https://www.bluetooth.org/docman/handlers/DownloadDoc.ashx?doc_id=539729#%5B%7B%22num%22%3A335%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C69%2C174%2C0%5D
  uint16_t flags;
  uint16_t instantaneous_speed; // unit is 1/100 of m/s
  uint8_t tot_dist_hi;
  uint16_t tot_dist_lo; // split a uint24_t into hi/lo because uint24_t doesn't exist, base unit 10 cm
  int32_t lat; // note: unit is 10^-7 degrees
  int32_t lon;
  int8_t elev_hi;
  uint16_t elev_lo; // disgusting especially with signed int24_t but this works kind of, base unit 1 cm
  uint16_t heading; // base unit 10^-7 degrees
  uint8_t roll_time;
  utc_time_t utc_time;
} location_data_t;
#pragma once
//----------------------ESP related defines----------------------
#ifndef PRO_CPU
#define PRO_CPU 0
#endif
#ifndef APP_CPU
#define APP_CPU 1
#endif

//----------------------IDE and Programming defines----------------------
#define ARDUINO_IDE 0
#define CLION_IDE 0

#define DEBUG 1

#ifdef DEBUG
#define IFD(x) x
#define CHECK_ERROR(expr,expected) if(expr!=expected) ESP_LOGE(TAG,"Expression %s failed, expected %s", #expr, #expected)
#else
#define IFD(x)
#define CHECK_ERROR(expr,expected)
#endif

#define APP_NAME "Smart Glasses"

#if ARDUINO_IDE
#ifdef LOG_LOCAL_LEVEL
#undef LOG_LOCAL_LEVEL
#endif
#endif
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

#define MAX_TITLE_LENGTH 12
#define MAX_ADD_INFO_LENGTH 48

#define NOTIF_SERVICE_UUID "1e7b14e7-f5d9-4113-b249-d16b6ae7db7f"
#define NOTIF_BUFFER_ATTR_UUID "8d5b53b8-fe04-4509-a689-82ab4c3d2507"

#define BATTERY_SERVICE_UUID 0x180F
#define BATTERY_CHAR_UUID 0x2A19

#define GNSS_SERVICE_UUID 0x1819 // these come from the UUIDs with allocation type=gatt service here: https://btprodspecificationrefs.blob.core.windows.net/assigned-values/16-bit%20UUID%20Numbers%20Document.pdf
#define GNSS_CHAR_UUID 0x2a67 // these come from UUIDs with allocation type=GATT Characteristic and Object Type here: https://btprodspecificationrefs.blob.core.windows.net/assigned-values/16-bit%20UUID%20Numbers%20Document.pdf
#define GNSS_FEATURES_CHAR_UUID 0x2a6a

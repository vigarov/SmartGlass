#pragma once
//----------------------ESP related defines----------------------
#ifndef PRO_CPU
#define PRO_CPU 0
#endif
#ifndef APP_CPU
#define APP_CPU 1
#endif

//----------------------IDE and Programming defines----------------------
#define ARDUINO_IDE 1
#define CLION_IDE 0

#define DEBUG 1

#ifdef DEBUG
#define IFD(x) x
#define CHECK_ERROR(expr,expected) if(expr!=expected) ESP_LOGE(TAG,"Expression %s failed, expected %s", #expr, #expected)
#else
#define IFD(x)
#define CHECK_ERROR(expr,expected)
#endif

#ifdef ARDUINO_IDE
void loop(void){}//No loop, tasks will handle everything
#endif

//----------------------Firmware----------------------

#define APP_NAME "Smart Glasses"

#if ARDUINO_IDE
#ifdef LOG_LOCAL_LEVEL
#undef LOG_LOCAL_LEVEL
#endif
#endif
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE

#define MAX_TITLE_LENGTH 12
#define MAX_ADD_INFO_LENGTH 48

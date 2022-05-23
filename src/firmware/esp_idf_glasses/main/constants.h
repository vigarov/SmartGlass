#pragma once
//----------------------ESP related defines----------------------
#ifndef PRO_CPU
#define PRO_CPU 0
#endif
#ifndef APP_CPU
#define APP_CPU 1
#endif

#define PIN_SDA 23
#define PIN_SCL 19 // these are the same defaults as lolin 32 lite on Arduino IDE
#define PIN_IMU_INT GPIO_NUM_27

#define APP_NAME "SmartGlasses"
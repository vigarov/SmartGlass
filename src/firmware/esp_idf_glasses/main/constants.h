#pragma once
//----------------------ESP related defines----------------------
#ifndef PRO_CPU
#define PRO_CPU 0
#endif
#ifndef APP_CPU
#define APP_CPU 1
#endif

#define APP_NAME "SmartGlasses"

#ifndef DEBUG
#define DEBUG 1
#endif

#define USE_ANIMATIONS 0
#define ANIMATION_DELAY 5

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define PIN_SDA 19
#define PIN_SCL 23 // these are the same defaults as lolin 32 lite on Arduino IDE
#define PIN_IMU_INT GPIO_NUM_27

#pragma once

//----------------------Display----------------------

#include "HyperDisplay_UG2856KLBAG01.h"

typedef struct{
  unsigned char x;
  unsigned char y;
}__attribute__((packed))pixel_pair_t;

typedef struct{
  unsigned char priority; //TODO: can make it a bitfield to save... one byte if necessary
  pixel_pair_t* p;
  size_t len;
  unsigned char overwrite;
}__attribute__((packed)) display_t;

class DisplayManager {
  private:
    UG2856KLBAG01_SPI backend_display;
    const int CS_PIN = 4;
    const int DC_PIN = 5;
    GlobalsManager* const glob_mgr;
    SemaphoreHandle_t xDisplayUpdateSemaphore;
    display_t to_display = {.priority=0,.p=NULL,.len=0,.overwrite=0};
  public:
  DisplayManager(GlobalsManager* glob_mgr);

  void init();

  void update_awaiting_display(GlobalsManager* glob_mgr, display_t* newFrames);

  void refresh_display();
};

#pragma once

//----------------------Display----------------------

#include "HyperDisplay_UG2856KLBAG01.h" 

#define SERIAL_PORT Serial  
#define SPI_PORT SPI        // Used if USE_SPI == 1

#define CS_PIN 4            // Used only if USE_SPI == 1
#define DC_PIN 5            // Used only if USE_SPI == 1
UG2856KLBAG01_SPI myTOLED;  // Declare a SPI-based Transparent OLED object called myTOLED

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

display_t toBeDisplayed = {0}; //TODO: make volatile?

void updateAwaitingDisplay(display_t* newFrames);

void updateAwaitingDisplay(display_t* newFrames){
  TAKE_S_INF(xDisplayUpdateSemaphore); 
  if(newFrames->priority > toBeDisplayed.priority){ 
  //Not >= since if two events with the same priority happen to occur at the same time, it is logical to keep to first and disregard the second
  //This however should be rare (only e.g. I can think of is if you press on a "menu UP/DOWN" button before the menu has actually displayed)
    if(toBeDisplayed.p != NULL){
      //Freeing only if an event is waiting to be displayed but hasn't yet been displyed
      free(toBeDisplayed.p);
      toBeDisplayed.p=NULL;
    }
    toBeDisplayed = *newFrames; //Deep copy
  }
  xSemaphoreGive(xDisplayUpdateSemaphore);
  xTaskNotifyGive(allTasks[T_DISPLAY]);
}

void T_Display(void* pvParameters){
  SPI_PORT.begin();
  myTOLED.begin(CS_PIN, DC_PIN, SPI_PORT);
  
  while(1){
    ulTaskNotifyTake(pdTRUE,portMAX_DELAY); //TODO: RTOS suggests to not wait indefinitely, but rather TO at some point and e.g. log error. Why not, can also refactor infinite semaphore take
    TAKE_S_INF(xDisplayUpdateSemaphore);
    //Make a copy of the context to be displayed, and release semaphore
    //This enable other potentially waiting threads to continue while we are displaying current context
    display_t toDisplay = toBeDisplayed;
    free(toBeDisplayed.p);
    toBeDisplayed = {0};
    xSemaphoreGive(xDisplayUpdateSemaphore);
    //Giving the semaphore back and starting to actually display
    if(toDisplay.overwrite){
      myTOLED.clearDisplay();
    }
    for(size_t i =0; i<toDisplay.len;i++){
      pixel_pair_t* pixels = toDisplay.p+i;
      myTOLED.pixelSet(pixels->x,pixels->y);
    }
    myTOLED.setContrastControl(128); //TODO: needed to be done @ every write?
  }
}

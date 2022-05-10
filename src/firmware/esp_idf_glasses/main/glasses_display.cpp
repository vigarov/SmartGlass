#include "glasses_constants.h"
#include "glasses_types.h"
#include "glasses_utils.h"
#include "glasses_globals_manager.h"
#include "glasses_display.h"

DisplayManager::DisplayManager(GlobalsManager* glob_mgr): glob_mgr(glob_mgr) {
    this->xDisplayUpdateSemaphore =  xSemaphoreCreateBinary();
}

void DisplayManager::init() {
    SPI.begin();
    this->backend_display.begin(this->CS_PIN, this->DC_PIN, SPI);
}

void DisplayManager::update_awaiting_display(GlobalsManager* glob_mgr, display_t* newFrames){
    TAKE_S_INF(this->xDisplayUpdateSemaphore); 
    if(newFrames->priority > this->to_display.priority){ 
    //Not >= since if two events with the same priority happen to occur at the same time, it is logical to keep to first and disregard the second
    //This however should be rare (only e.g. I can think of is if you press on a "menu UP/DOWN" button before the menu has actually displayed)
      if(this->to_display.p != NULL){
        //Freeing only if an event is waiting to be displayed but hasn't yet been displyed
        free(this->to_display.p);
        this->to_display.p=NULL;
      }
      this->to_display = *newFrames; //Deep copy
    }
    xSemaphoreGive(this->xDisplayUpdateSemaphore);
    xTaskGenericNotify(glob_mgr->allTasks[T_DISPLAY],DISPLAY_UPDATE,0,eSetValueWithoutOverwrite,NULL);
    //xTaskNotifyGive(allTasks[T_DISPLAY]); // FreeRTOS will already handle task switching and doing this sounds like a bad idea
}

void DisplayManager::refresh_display() {
    ulTaskNotifyTakeIndexed(DISPLAY_UPDATE, pdTRUE,portMAX_DELAY); //TODO: RTOS suggests to not wait indefinitely, but rather TO at some point and e.g. log error. Why not, can also refactor infinite semaphore take
    TAKE_S_INF(this->xDisplayUpdateSemaphore);
    // the only way to try making the critical part shorter is to make a copy of the pixels but then that takes a lot of time
    if(this->to_display.overwrite){
      this->backend_display.clearDisplay();
    }
    for(size_t i =0; i<this->to_display.len;i++){
      pixel_pair_t* pixels = this->to_display.p+i;
      this->backend_display.pixelSet(pixels->x,pixels->y);
    }
    // the one who set the pixels may be long dead so this is responsible for deleting.
    free(this->to_display.p);
    this->to_display.p=NULL;
    xSemaphoreGive(this->xDisplayUpdateSemaphore);
    this->backend_display.setContrastControl(128); //TODO: needed to be done @ every write?
}
#include "Display.h"
#include "utils.h"
#include "constants.h"

using namespace SmartGlasses;

DisplayManager::DisplayManager(){
    xDisplayUpdateSemaphore = xSemaphoreCreateBinary();
}

void DisplayManager::init() {
    SPI.begin();
    this->backend_display.begin(CS_PIN, DC_PIN, SPI);
}

void DisplayManager::setDisplayTask(TaskHandle_t* displayTask){
    displaySenderTask = displayTask;
}

void DisplayManager::update_awaiting_display(std::unique_ptr<display_t> newFrames){
    TAKE_S_INF(xDisplayUpdateSemaphore); 
    if(newFrames->priority > this->currentFrames->priority){ 
    //Not >= since if two events with the same priority happen to occur at the same time, it is logical to keep to first and disregard the second
    //This however should be rare (only e.g. I can think of is if you press on a "menu UP/DOWN" button before the menu has actually displayed)
      currentFrames = std::move(newFrames);
    }
    xSemaphoreGive(xDisplayUpdateSemaphore);
    xTaskNotifyGive(displaySenderTask);
    //xTaskNotifyGive(allTasks[T_DISPLAY]); // FreeRTOS will already handle task switching and doing this sounds like a bad idea
}

void DisplayManager::refreshDisplay() {
        ulTaskNotifyTake(pdTRUE,portMAX_DELAY); //TODO: RTOS suggests to not wait indefinitely, but rather TO at some point and e.g. log error. Why not, can also refactor infinite semaphore take
        TAKE_S_INF(xDisplayUpdateSemaphore);
        Drawable object = currentFrames->object; //Deep copy of the Drawable
        currentFrames.reset(nullptr);
        xSemaphoreGive(xDisplayUpdateSemaphore);

        //We can now update the display
        if(object.overwrite){
        this->backend_display.clearDisplay();
        }
        for(auto &p : object.pixels){
        this->backend_display.pixelSet(p.x+object.offsetX,p.y+object.offsetY);
        }
        this->backend_display.setContrastControl(128); //TODO: needed to be done @ every write? 
}
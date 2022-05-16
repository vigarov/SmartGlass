#include "DisplayManager.h"
#include "utils.h"
#include "constants.h"
#include "esp_log.h"

using namespace SmartGlasses;


DisplayManager::DisplayManager(){
    xDisplayUpdateSemaphore = xSemaphoreCreateBinary();
}

void DisplayManager::init() {
    SPI.begin();
    backend_display.begin(CS_PIN, DC_PIN, SPI);
    backend_display.buffer(NULL); //set window in buffered mode: we will be doing writes of several pixels each time we write --> might as well only write to the display once per call
}

void DisplayManager::setDisplayTask(TaskHandle_t displayTask){
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
    ESP_LOGI(DISPLAY_M,"Notified to update the display");
    TAKE_S_INF(xDisplayUpdateSemaphore);
    Drawable object = currentFrames->object; //Deep copy of the Drawable
    currentFrames.reset(nullptr);
    xSemaphoreGive(xDisplayUpdateSemaphore);

    //We can now update the display
    for(auto& p: object.border){ //when doesn't overwrite, object.border will be empty --> loop is skipped
        backend_display.pixelClear(p.x+object.offsets.x,p.y+object.offsets.y);
    }
    for(auto &p : object.pixels){
        backend_display.pixelSet(p.x+object.offsets.x,p.y+object.offsets.y);
    }
    backend_display.setContrastControl(128); //TODO: needed to be done @ every write? 
    backend_display.refreshDisplay(); //we're in buffered mode, we must refresh() @ every ... refresh

}
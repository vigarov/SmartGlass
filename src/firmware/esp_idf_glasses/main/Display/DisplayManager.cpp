#include "DisplayManager.h"
#include "utils.h"
#include "constants.h"
#include "esp_log.h"

using namespace SmartGlasses;

void DisplayManager::init() {
    SPI.begin();
    ESP_LOGI(DISPLAY_M,"Began SPI");
    backend_display.begin(CS_PIN, DC_PIN, SPI);
    //backend_display.buffer(NULL); //set window in buffered mode: we will be doing writes of several pixels each time we write --> might as well only write to the display once per call
    xSemaphoreGive(xDisplayUpdateSemaphore);
    ESP_LOGI(DISPLAY_M,"Finished initializing up the display");
}

void DisplayManager::setDisplayTask(TaskHandle_t displayTask){
    displaySenderTask = displayTask;
}

void DisplayManager::update_awaiting_display(std::unique_ptr<display_t> newFrames){
    ESP_LOGI(DISPLAY_M,"Got update request");
    while(xSemaphoreTake(xDisplayUpdateSemaphore,100/portTICK_PERIOD_MS)==pdFALSE){
        ESP_LOGE(DISPLAY_M,"Couldn't get display update semaphore, even after 100 ms");
    } 
    ESP_LOGD(DISPLAY_M,"UAD taking xDisplayUpdateSemaphore");
    if(!this->currentFrames || newFrames->priority > this->currentFrames->priority){ 
    //Not >= since if two events with the same priority happen to occur at the same time, it is logical to keep to first and disregard the second
    //This however should be rare (only e.g. I can think of is if you press on a "menu UP/DOWN" button before the menu has actually displayed)
      currentFrames.reset(nullptr);
      currentFrames = std::move(newFrames);
    }
    IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
    xSemaphoreGive(xDisplayUpdateSemaphore);
    xTaskNotifyGive(displaySenderTask);
    ESP_LOGD(DISPLAY_M,"handled display update request");
}

void DisplayManager::refreshDisplay() {
    ulTaskNotifyTake(pdTRUE,portMAX_DELAY); //TODO: RTOS suggests to not wait indefinitely, but rather TO at some point and e.g. log error. Why not, can also refactor infinite semaphore take
    ESP_LOGI(DISPLAY_M,"Notified to update the display");
    TAKE_S_INF(xDisplayUpdateSemaphore);
    ESP_LOGD(DISPLAY_M,"Refresh taking xDisplayUpdateSemaphore");
    IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
    { //Indented block to easily measure if memory is not freed correcly when debugging
        std::unique_ptr<Drawable> object = std::move(currentFrames->object);
        currentFrames.reset(nullptr);
        xSemaphoreGive(xDisplayUpdateSemaphore);

        IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
        ESP_LOGD(DISPLAY_M,"Drawing using offset (%d,%d)",object->offsets.x,object->offsets.y);
        //We can now update the display
        for(auto& p: *object->canvas){ //when doesn't overwrite, object->border will be empty --> loop is skipped
            ESP_LOGD(DISPLAY_M,"Border pixel (%d,%d)",p.x,p.y);
            backend_display.pixelClear(p.x+object->offsets.x,p.y+object->offsets.y);
            if(object->animate){
                vTaskDelay(ANIMATION_DELAY/portTICK_PERIOD_MS);
            }
        }
        for(auto &p : *object->pixels){
            ESP_LOGD(DISPLAY_M,"Drawing pixel (%d,%d)",p.x,p.y);
            backend_display.pixelSet(p.x+object->offsets.x,p.y+object->offsets.y);
            if(object->animate){
                vTaskDelay(ANIMATION_DELAY/portTICK_PERIOD_MS);
            }
        }
    
        TaskHandle_t taskToNotify = object->notifyOnDraw;
        if(taskToNotify!=NULL){
            xTaskNotifyGive(taskToNotify);
        }

        object.reset(nullptr); //explicitely freeing memory
    }
    ESP_LOGI(DISPLAY_M,"Finished drawing");

    IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
    //The contrast of 128 is too strong imo, see opinions of others
    //Refresh display is useless without buffer
    //backend_display.setContrastControl(128); //TODO: needed to be done @ every write? 
    //backend_display.refreshDisplay(); //we're in buffered mode, we must refresh() @ every ... refresh

}
#include "ApplicationContainer.h"
#include "utils.h"
#include "constants.h"

using namespace SmartGlasses;

std::shared_ptr<Application> ApplicationContainer::getCurrentApplication(){
    return currentApplication; //from ApplicationContainer
}

void ApplicationContainer::setCurrentApplication(std::shared_ptr<Application> app){
    ESP_LOGI(APPCONT_M,"Setting the current application to app with id: %d", app->id);
    // currentApplication->onClose();
    if(xSemaphoreTake(xAppSemaphore, 15/portTICK_PERIOD_MS) == pdTRUE){
        ESP_LOGD(APPCONT_M,"Taking application semaphore to change app");
        currentApplication = app;
        xSemaphoreGive(xAppSemaphore);
    }
    else{
        ESP_LOGW(APPCONT_M,"Couldn't get semaphore after 15 ms");
    }
    // currentApplication->onResume();
}

void ApplicationContainer::init(std::shared_ptr<Application> app){
    ESP_LOGI(APPCONT_M,"Initialiazing App. Container");
    currentApplication = app;
    xSemaphoreGive(xAppSemaphore);
    IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
    createTask(runApplication,"ApplicationRunner",40960,1,&appTaskHandler,APP_CPU,&currentApplication);
    IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
    currentApplication->changeTaskToBeUpdated(appTaskHandler);
    xTaskNotifyGive(appTaskHandler);
    ESP_LOGD(APPCONT_M,"Initialiazed App. Container. app semaphore pointer : %p",xAppSemaphore);
}

void ApplicationContainer::runApplication(void *pvParameters){
    if(ulTaskNotifyTake(pdTRUE,100/portTICK_PERIOD_MS) == pdFALSE){
        ESP_LOGE(APPCONT_M,"Didn't get notified after 100ms, failed to change the task to be update to all the children?");
    }
    ESP_LOGI(APPCONT_M,"Starting application thread");
    std::shared_ptr<Application> usedApp = *(std::shared_ptr<Application>*)pvParameters;
    usedApp->onResume(); // Starting the app for the first time
    ApplicationContainer& ac = ApplicationContainer::getInstance();
    while(1){
        if(xSemaphoreTake(ac.xAppSemaphore, 50/portTICK_PERIOD_MS) == pdTRUE){
            ESP_LOGD(APPCONT_M,"Taking application semaphore to run app");
            std::shared_ptr<Application> currA = ac.getCurrentApplication();
            xSemaphoreGive(ac.xAppSemaphore);
            if(usedApp->id != currA->id){
                usedApp->onClose();
                usedApp = currA;
                usedApp->onResume();
                continue;
            }
            usedApp->run();
        }
        else{
            ESP_LOGW(APPCONT_M, "Couldn't get semaphore to run the application");
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }

}

TaskHandle_t ApplicationContainer::getAppTaskHandle(){
    return appTaskHandler;
}
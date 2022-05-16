#include "ApplicationContainer.h"
#include "utils.h"
#include "constants.h"

using namespace SmartGlasses;

std::shared_ptr<Application> ApplicationContainer::getCurrentApplication(){
    return currentApplication; //from ApplicationContainer
}

void ApplicationContainer::setCurrentApplication(std::shared_ptr<Application> app){
    // currentApplication->onClose();
    if(xSemaphoreTake(xAppSemaphore, 15/portTICK_PERIOD_MS) == pdPASS){
        currentApplication = app;
        xSemaphoreGive(xAppSemaphore);
    }
    else{
        ESP_LOGW(APPCONT_M,"Couldn't get semaphore after 15 ms");
    }
    // currentApplication->onResume();
}

void ApplicationContainer::init(std::shared_ptr<Application> app){
    ESP_LOGI(APPCONT_M,"Initiliazing App. Container");
    currentApplication = app;
    xAppSemaphore = xSemaphoreCreateBinary();
    createTask(runApplication,"ApplicationRunner",10240,1,&appTaskHandler,APP_CPU,&currentApplication);
}

void ApplicationContainer::runApplication(void *pvParameters){
    ESP_LOGI(APPCONT_M,"Starting application thread");
    std::shared_ptr<Application> usedApp = *(std::shared_ptr<Application>*)pvParameters;
    ApplicationContainer& ac = ApplicationContainer::getInstance();
    while(1){
        if(xSemaphoreTake(ac.xAppSemaphore, 5/portTICK_PERIOD_MS) == pdPASS){
            std::shared_ptr<Application> currA = ac.getCurrentApplication();
            xSemaphoreGive(ac.xAppSemaphore);
            if(usedApp->id != currA->id){
                usedApp->onClose();
                usedApp = currA;
                usedApp->onResume();
            }
        }
        else{
            ESP_LOGW("App Thread", "Couldn't get semaphore to update the current application in the thread");
        }
        usedApp->run();
    }

}
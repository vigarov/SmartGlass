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
        ESP_LOGI(APPCONT_M,"Taking application semaphore to change app");
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
    xSemaphoreGive(xAppSemaphore);
    currentApplication = app;
    createTask(runApplication,"ApplicationRunner",10240,1,&appTaskHandler,APP_CPU,&currentApplication);
    ESP_LOGI(APPCONT_M,"Initialiazed App. Container. app semaphore pointer : %p",xAppSemaphore);
}

void ApplicationContainer::runApplication(void *pvParameters){
    ESP_LOGI(APPCONT_M,"Starting application thread");
    std::shared_ptr<Application> usedApp = *(std::shared_ptr<Application>*)pvParameters;
    usedApp->onResume(); // Starting the app for the first time
    ApplicationContainer& ac = ApplicationContainer::getInstance();
    while(1){
        if(xSemaphoreTake(ac.xAppSemaphore, 50/portTICK_PERIOD_MS) == pdTRUE){
            ESP_LOGI(APPCONT_M,"Taking application semaphore to run app");
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
        vTaskDelay(100/portTICK_PERIOD_MS);
    }

}
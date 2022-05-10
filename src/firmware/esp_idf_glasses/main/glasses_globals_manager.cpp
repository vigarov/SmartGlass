#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "glasses_utils.h"
#include "glasses_globals_manager.h"

GlobalsManager::GlobalsManager(): display_manager(this) {}

void GlobalsManager::init_tasks() {
    for (int i = 0; i<NB_TASKS; i++) {
        this->allTasks[i]=NULL;
    }
    createTask(&this->allTasks[T_GNSS], T_GNSS_Task,"T_GNSS",10240,(void* const)this,configMAX_PRIORITIES-3,APP_CPU);
    createTask(&this->allTasks[T_DISPLAY], T_Display,"Display",10240,(void* const)this,configMAX_PRIORITIES-2,APP_CPU);
    createTask(&this->allTasks[T_BLE], T_HandleBLE,"BLEHandler",10240,(void* const)this,configMAX_PRIORITIES-1,PRO_CPU);
}

void GlobalsManager::notify_all_tasks(UBaseType_t uxIndexToNotify, uint32_t ulValue, eNotifyAction eAction, uint32_t* pulPreviousNotificationValue) {
    TaskHandle_t curr_task = xTaskGetCurrentTaskHandle();
    TaskStatus_t curr_task_status;
    vTaskGetInfo(curr_task,&curr_task_status,pdFALSE,eReady); // eReady is actually going to be ignored

    for (uint8_t i=0; i<NB_TASKS; i++) {
        // ESP_LOGE(this->main_module_debug_name, "checking if task idx %d is a candidate for notifying from notify_all_tasks", i);
        // if (this->allTasks[i]!=NULL) {
            TaskStatus_t candidate_task_status;
            vTaskGetInfo(this->allTasks[i],&candidate_task_status,pdFALSE,eReady);
            ESP_LOGD(GlobalsManager::main_module_debug_name, "task idx %d (with xTaskNumber=%d) is candidate, and curr task with xTaskNumber=%d is calling notify_all_tasks", i, candidate_task_status.xTaskNumber, curr_task_status.xTaskNumber);

            // checking curr task num != candidate task num because you need to make sure you're not notifying yourself.
            if (curr_task_status.xTaskNumber!=candidate_task_status.xTaskNumber) {
                ESP_LOGD(GlobalsManager::main_module_debug_name, "Notifying thread %d with index %d", i, uxIndexToNotify);
                xTaskGenericNotify(this->allTasks[i],uxIndexToNotify, ulValue, eAction, pulPreviousNotificationValue);
            }
        // }
    }
}

void GlobalsManager::init_server() {
    //Setting up server
    esp_err_t errRc = ::nvs_flash_init(); // it looks like BLEDevice::init doesn't actually do this for some reason.
    if (errRc != ESP_OK) {
        ESP_LOGE(GlobalsManager::main_module_debug_name, "nvs_flash_init: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
        return;
    }
    BLEDevice::init(APP_NAME);
    this->server = BLEDevice::createServer();
    this->server->setCallbacks(new ServerCB()); //TODO: memory safety?
}

void GlobalsManager::init_services() {
    for (int svc_idx = NOTIF_SERVICE; svc_idx!=NB_SERVICES; svc_idx++) {
        this->services[svc_idx] = server->createService(servicesUUID[svc_idx]);
    }
    this->ble_svcs_initialised=true;
}

BLEService* GlobalsManager::get_svc(svc_idx_e svc_idx) {
    if (!this->ble_svcs_initialised) {
        ESP_LOGE(GlobalsManager::main_module_debug_name, "BLE service not initialised");
    }
    return this->services[svc_idx];
}

void GlobalsManager::start_advertise() {
    //Finished creating services, starting to advertise
    for (int svc_idx = NOTIF_SERVICE; svc_idx!=NB_SERVICES; svc_idx++) {
        this->services[svc_idx]->start();
    }
    BLEAdvertising* advertiser = BLEDevice::getAdvertising();
    for(auto &u : servicesUUID){
        advertiser->addServiceUUID(u);
    }
    advertiser->setScanResponse(true);
    advertiser->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
}

void GlobalsManager::update_location_data(const location_data_t* new_data) {
    this->characteristics[GNSS_CHAR]->setValue((uint8_t*)new_data, sizeof(location_data_t));
}
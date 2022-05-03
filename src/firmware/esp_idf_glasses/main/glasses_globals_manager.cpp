#include "glasses_utils.h"
#include "glasses_globals_manager.h"

GlobalsManager::GlobalsManager(): display_manager(this) {}

void GlobalsManager::init_tasks() {
    createTask(this->allTasks[T_BLE], T_HandleBLE,"BLEHandler",10240,(void* const)this,configMAX_PRIORITIES-1,PRO_CPU);
    createTask(this->allTasks[T_GNSS], T_GNSS_Task,"GNSS_Task",10240,(void* const)this,configMAX_PRIORITIES-1,APP_CPU);
    //createTask(this->allTasks[T_Display], T_Display,"Display",1024,2,APP_CPU);
}

void GlobalsManager::notify_all_tasks(UBaseType_t notification_idx, uint32_t new_val) {
    for (uint8_t i=0; i<NB_TASKS; i++) {
        xTaskGenericNotify(this->allTasks[i],notification_idx,new_val,eSetValueWithoutOverwrite,NULL);
    }
}

void GlobalsManager::init_server() {
    //Setting up server
    esp_err_t errRc = ::nvs_flash_init(); // it looks like BLEDevice::init doesn't actually do this for some reason.
    if (errRc != ESP_OK) {
        ESP_LOGE(main_module_debug_name, "nvs_flash_init: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
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
        ESP_LOGE(main_module_debug_name, "BLE service not initialised");
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
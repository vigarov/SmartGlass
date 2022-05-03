#pragma once
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "GeneralUtils.h" // Also from BLE library

class GlobalsManager; // doing forward declaration as suggested here: https://stackoverflow.com/a/4816751/5708421

#include "glasses_constants.h"
#include "glasses_types.h"
#include "glasses_ble_callbacks.h"
#include "glasses_toplevel_tasks.h"
//#include "glasses_utils.h"
#include "glasses_display.h"

class GlobalsManager {
    private:
    BLEUUID servicesUUID[NB_SERVICES] = {BLEUUID(NOTIF_SERVICE_UUID),BLEUUID((uint16_t)GNSS_SERVICE_UUID),BLEUUID((uint16_t)BATTERY_SERVICE_UUID)};
    BLEService* services[NB_SERVICES];
    BLEServer* server;
    bool ble_svcs_initialised = false;
    const char* main_module_debug_name = "Main module";

    public:
    DisplayManager display_manager;
    BLECharacteristic* characteristics[NB_CHARS];
    TaskHandle_t* allTasks[NB_TASKS];

    GlobalsManager();

    void init_tasks();

    void notify_all_tasks(UBaseType_t notification_idx, uint32_t new_val);

    void init_server();

    void init_services();

    BLEService* get_svc(svc_idx_e svc_idx);

    void start_advertise();

    void update_location_data(const location_data_t* new_data);

};
#include "BLEHandler.h"
#include "constants.h"

#include "nvs_flash.h"
#include "esp_log.h"
#include "GeneralUtils.h"

#include "BLEDevice.h"
#include "callbacks.h"

#include "GNSS.h"

using namespace SmartGlasses;

#define BLE_M "BLEHandler"

BLEHandler::BLEHandler(){
    initServer();
    initServices();
    startAdvertise();
}

void BLEHandler::initServer(){
    ESP_LOGI(BLE_M,"Starting initializing server");
    //Setting up server
    esp_err_t errRc = ::nvs_flash_init(); // it looks like BLEDevice::init doesn't actually do this for some reason.
    if (errRc != ESP_OK) {
        ESP_LOGE(BLE_M, "nvs_flash_init: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
        return;
    }
    BLEDevice::init(APP_NAME);
    server = BLEDevice::createServer();
    server->setCallbacks(new ServerCB()); //TODO: memory safety?
    ESP_LOGI(BLE_M,"Finished initializing server");
}

void BLEHandler::initServices(){
    ESP_LOGI(BLE_M,"Starting initializing services");
    BLEAdvertising* advertiser = BLEDevice::getAdvertising();
    for(uint8_t i = NOTIF_SERVICE; i<NB_SERVICES;i++){
        auto& uuid = servicesUUID[i];
        BLEService* service = server->createService(uuid);
        if(service == nullptr){
            ESP_LOGE(BLE_M, "failed to create service w/ uuid %s",uuid.toString().c_str());
            return;//TODO:Handle error better (propagate back, set flag, ...)
        }
        addCharacteristics(static_cast<services_t>(i),service);
        service->start();
        //Doing this here, because a vector is used --> if we advertise more than once (e.g.: on disconnect), the services would have been added twice
        //(advertiser is a (non-thread safe) singleton)
        advertiser->addServiceUUID(uuid); 
    }
    ESP_LOGI(BLE_M,"Finished initializing services");
}

#define INLINE_CHECK_FOR_ERROR(characteristic, uuid_char_arr) \
    if((characteristic) == nullptr){ \
        ESP_LOGE(BLE_M, "failed to create characteristic w/ uuid %s",(uuid_char_arr)); \
        return; \
    }

void BLEHandler::addCharacteristics(services_t servID, BLEService* service){
    switch(servID){
        case NOTIF_SERVICE:
            {
                auto* characteristic = service->createCharacteristic(NOTIF_BUFFER_ATTR_UUID,BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);
                INLINE_CHECK_FOR_ERROR(characteristic,NOTIF_BUFFER_ATTR_UUID)
                characteristic->setCallbacks(new NotificationBufferCB());
                break;
            }
        case GNSS_SERVICE:
            {
                auto gCharUUID = BLEUUID((uint16_t)GNSS_CHAR_UUID); 
                auto* characteristic = service->createCharacteristic(gCharUUID, BLECharacteristic::PROPERTY_NOTIFY|BLECharacteristic::PROPERTY_READ);
                INLINE_CHECK_FOR_ERROR(characteristic,gCharUUID.toString().c_str())
                gCharUUID = BLEUUID((uint16_t)GNSS_FEATURES_CHAR_UUID); //createCharacteristic takes BLEUUID by copy-->fine
                characteristic = service->createCharacteristic(gCharUUID,BLECharacteristic::PROPERTY_READ);
                INLINE_CHECK_FOR_ERROR(characteristic,gCharUUID.toString().c_str())
                uint32_t ln_feature_val=LN_FEATURE_LOCATION_SUPPORTED|LN_FEATURE_ELEV_SUPPORTED;
                characteristic->setValue((uint8_t*)&ln_feature_val,sizeof(ln_feature_val));
            }
        case BATTERY_SERVICE:
            {
                auto bCharUUID = BLEUUID((uint16_t)BATTERY_CHAR_UUID);
                auto* characteristic = service->createCharacteristic(bCharUUID, BLECharacteristic::PROPERTY_READ|BLECharacteristic::PROPERTY_NOTIFY);
                INLINE_CHECK_FOR_ERROR(characteristic,bCharUUID.toString().c_str())
                #if DEBUG==1
                {
                    int testValue = 67;
                    characteristic->setValue(testValue);
                }
                #endif
                break;
            }
        case NB_SERVICES: //Not using default to force completing this method upon adding new services
        break;
    }
}

void BLEHandler::startAdvertise(){
    BLEDevice::startAdvertising();    
    ESP_LOGI(BLE_M,"Started advertising");
}

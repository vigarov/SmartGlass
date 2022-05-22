#include "BLEHandler.h"
#include "constants.h"

#include "nvs_flash.h"
#include "esp_log.h"
#include "GeneralUtils.h"

#include "BLEDevice.h"
#include "callbacks.h"

using namespace SmartGlasses;

#define MODULE_NAME "BLEHandler"

BLEHandler::BLEHandler(){
    initServer();
    initServices();
    startAdvertise();
}

void BLEHandler::initServer(){
    esp_log_level_set(MODULE_NAME, ESP_LOG_VERBOSE);
    //Setting up server
    esp_err_t errRc = ::nvs_flash_init(); // it looks like BLEDevice::init doesn't actually do this for some reason.
    if (errRc != ESP_OK) {
        ESP_LOGE(MODULE_NAME, "nvs_flash_init: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
        return;
    }
    BLEDevice::init(APP_NAME);
    server = BLEDevice::createServer();
    server->setCallbacks(new ServerCB()); //TODO: memory safety?
}

void BLEHandler::initServices(){
    BLEAdvertising* advertiser = BLEDevice::getAdvertising();
    for(uint8_t i = NOTIF_SERVICE; i<NB_SERVICES;i++){
        auto& uuid = servicesUUID[i];
        BLEService* service = server->createService(uuid);
        if(service == nullptr){
            ESP_LOGE(MODULE_NAME, "failed to create service w/ uuid %s",uuid.toString().c_str());
            return;//TODO:Handle error better (propagate back, set flag, ...)
        }
        addCharacteristics(static_cast<services_t>(i),service);
        service->start();
        //Doing this here, because a vector is used --> if we advertise more than once (e.g.: on disconnect), the services would have been added twice
        //(advertiser is a (non-thread safe) singleton)
        advertiser->addServiceUUID(uuid); 
    }
}

#define INLINE_CHECK_FOR_ERROR(characteristic, uuid_char_arr) \
    if((characteristic) == nullptr){ \
        ESP_LOGE(MODULE_NAME, "failed to create characteristic w/ uuid %s",(uuid_char_arr)); \
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
        case IMU_SERVICE:
            {
              /*
                auto* accel_x_char = service->createCharacteristic(IMU_SERVICE_ACCEL_X_CHAR_UUID,BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
                INLINE_CHECK_FOR_ERROR(accel_x_char,IMU_SERVICE_ACCEL_X_CHAR_UUID)
                auto* accel_y_char = service->createCharacteristic(IMU_SERVICE_ACCEL_Y_CHAR_UUID,BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
                INLINE_CHECK_FOR_ERROR(accel_x_char,IMU_SERVICE_ACCEL_Y_CHAR_UUID)
                auto* accel_z_char = service->createCharacteristic(IMU_SERVICE_ACCEL_Z_CHAR_UUID,BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
                INLINE_CHECK_FOR_ERROR(accel_x_char,IMU_SERVICE_ACCEL_Z_CHAR_UUID)
                auto* gyro_x_char = service->createCharacteristic(IMU_SERVICE_GYRO_X_CHAR_UUID,BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
                INLINE_CHECK_FOR_ERROR(accel_x_char,IMU_SERVICE_GYRO_X_CHAR_UUID)
                auto* gyro_y_char = service->createCharacteristic(IMU_SERVICE_GYRO_Y_CHAR_UUID,BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
                INLINE_CHECK_FOR_ERROR(accel_x_char,IMU_SERVICE_GYRO_Y_CHAR_UUID)
                auto* gyro_z_char = service->createCharacteristic(IMU_SERVICE_GYRO_Z_CHAR_UUID,BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY);
                INLINE_CHECK_FOR_ERROR(accel_x_char,IMU_SERVICE_GYRO_Z_CHAR_UUID)
                // now really should store these somewhere so they can be updated later
                */
                
              granny_fallen_char = service->createCharacteristic(IMU_SERVICE_GRANNY_CHAR_UUID, BLECharacteristic::PROPERTY_READ |BLECharacteristic::PROPERTY_NOTIFY);
              INLINE_CHECK_FOR_ERROR(granny_fallen_char, IMU_SERVICE_GRANNY_CHAR_UUID);
              #if DEBUG==1
              uint16_t granny_status = false;
              granny_fallen_char->setValue(granny_status);
              #endif
              motion_det_char = service->createCharacteristic(IMU_SERVICE_MOTION_CHAR_UUID, BLECharacteristic::PROPERTY_READ |BLECharacteristic::PROPERTY_NOTIFY);
              INLINE_CHECK_FOR_ERROR(motion_det_char, IMU_SERVICE_MOTION_CHAR_UUID);
              #if DEBUG==1
              //uint16_t imu_power_state = 0; // fully on, IMU in high sample rate mode awaiting granny event
              uint16_t imu_power_state = 1; // fully on but got 1 zeromotion interrupt (aka 16 s of insignificant movement), system is preparing to switch to light sleep
              //uint16_t imu_power_state = 2; // light sleep: after the previous state something like 5 minutes elapsed still without a motion trigger, IMU goes to wake cycle mode and granny detection is disabled
              motion_det_char->setValue(imu_power_state);
              #endif
              break;
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
}

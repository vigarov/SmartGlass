#pragma once
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "GeneralUtils.h" // Also from BLE library
#include "GlobalsManager.h"

namespace SmartGlasses{
    class ServerCB : public BLEServerCallbacks{
        #define SCB_M "ServerCallback Module"
        void onConnect(BLEServer* pServer) override {
            QueueHandle_t q = GLOBALSMANAGER.getUOS()->getQueueHandle();
            uOSEvent e = {.id=BT_CONNECT,.sender=static_cast<void*>(pServer)};
            if(xQueueSendToBack(q,(void *)&e,2/portTICK_PERIOD_MS) !=pdTRUE){
                ESP_LOGE(SCB_M,"Connected but couldn't push to queue: it is full");
            }
        }

        void onDisconnect(BLEServer* pServer) override {
            QueueHandle_t q = GLOBALSMANAGER.getUOS()->getQueueHandle();
            uOSEvent e = {.id=BT_DISCONNECT,.sender=static_cast<void*>(pServer)};
            if(xQueueSendToBack(q,(void *)&e,2/portTICK_PERIOD_MS) !=pdTRUE){
                ESP_LOGE(SCB_M,"Disconnected but couldn't push to queue: it is full");
            }
        }

    };

    class NotificationBufferCB : public BLECharacteristicCallbacks {
        #define NOTIFICATIONCB_M "Notification CB"
        void onWrite(BLECharacteristic *pCharacteristic) override {
            ESP_LOGI(NOTIFICATIONCB_M,"Got new notification, sending to uOS");
            QueueHandle_t q = GLOBALSMANAGER.getUOS()->getQueueHandle();
            uOSEvent e = {.id=NOTIFICATION_NEW,.sender=static_cast<void*>(pCharacteristic)};
            if(xQueueSendToBack(q,(void *)&e,10/portTICK_PERIOD_MS) !=pdTRUE){
                ESP_LOGE("BLE Notification CB","New notification but couldn't push to queue: it is full");
            }
        }

        void onNotify(BLECharacteristic* pCharacteristic) override{
            ESP_LOGI(NOTIFICATIONCB_M,"Notification callback: either notified or got notified");
        }
    };

    class TimeCB : public BLECharacteristicCallbacks {
        void onWrite(BLECharacteristic *pCharacteristic) override {
            ESP_LOGI(NOTIFICATIONCB_M,"Got time update, sending to uOS");
            QueueHandle_t q = GLOBALSMANAGER.getUOS()->getQueueHandle();
            uOSEvent e = {.id=TIME_UPDATE,.sender=static_cast<void*>(pCharacteristic)};
            if(xQueueSendToBack(q,(void *)&e,10/portTICK_PERIOD_MS) !=pdTRUE){
                ESP_LOGE("BLE Time CB","New time update but couldn't push to queue: it is full");
            }
        }
    };

    class NavigationCB : public BLECharacteristicCallbacks{
        void onWrite(BLECharacteristic *pCharacteristic) override {
            ESP_LOGI(NOTIFICATIONCB_M,"Got navigation update, sending to uOS");
            QueueHandle_t q = GLOBALSMANAGER.getUOS()->getQueueHandle();
            uOSEvent e = {.id=NAVIGATION_UPDATE,.sender=static_cast<void*>(pCharacteristic)};
            if(xQueueSendToBack(q,(void *)&e,10/portTICK_PERIOD_MS) !=pdTRUE){
                ESP_LOGE("BLE Nav CB","New navigation but couldn't push to queue: it is full");
            }
        }
    };
};

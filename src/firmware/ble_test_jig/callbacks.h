#pragma once
#include <SoftwareSerial.h>
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "GeneralUtils.h" // Also from BLE library

namespace SmartGlasses{
    class ServerCB : public BLEServerCallbacks{
        #define SCB_M "ServerCallback Module"
        void onConnect(BLEServer* pServer) override {
            Serial.println("Got receive event");
        }

        void onDisconnect(BLEServer* pServer) override {
          Serial.println("Got disconnect event");
        }

    };

    class NotificationBufferCB : public BLECharacteristicCallbacks {
        void onWrite(BLECharacteristic *pCharacteristic){
          Serial.print("Got notification write: ");
          Serial.println(pCharacteristic->getValue().c_str());
        }
    };
};

#pragma once
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "GeneralUtils.h" // Also from BLE library

namespace SmartGlasses{
    class ServerCB : public BLEServerCallbacks{
        void onConnect(BLEServer* pServer) override {
            //Notify the uOS to change the header
            //TODO: either taskNotify uOS or semaphore unlock (not preferrable)
            //      AND write to some bitset/flag (atomically) to show what is updated (in that case BT connectivity)

        }

        void onDisconnect(BLEServer* pServer) override {
            //TODO: Opposite, but same as above
        }

    };

    class NotificationBufferCB : public BLECharacteristicCallbacks {
        void onWrite(BLECharacteristic *pCharacteristic){
            //New notification has arrived: "save" it locally and clear the buffer
        }
    };
};

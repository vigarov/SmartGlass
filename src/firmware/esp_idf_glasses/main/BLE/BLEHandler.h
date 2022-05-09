#pragma once

#include "BLEServer.h"
#include "BLEUUID.h"
#include "BLEUtils.h"

namespace SmartGlasses{   

    enum services_t : uint8_t{
	NOTIF_SERVICE,
	GNSS_SERVICE,
	//IMU_SERVICE,
	BATTERY_SERVICE,
	NB_SERVICES
    };

    #define NOTIF_SERVICE_UUID "1e7b14e7-f5d9-4113-b249-d16b6ae7db7f"
    #define NOTIF_BUFFER_ATTR_UUID "8d5b53b8-fe04-4509-a689-82ab4c3d2507"

    #define BATTERY_SERVICE_UUID 0x180F
    #define BATTERY_CHAR_UUID 0x2A19

    #define GNSS_SERVICE_UUID 0x1819 // these come from the UUIDs with allocation type=gatt service here: https://btprodspecificationrefs.blob.core.windows.net/assigned-values/16-bit%20UUID%20Numbers%20Document.pdf
    #define GNSS_CHAR_UUID 0x2a67 // these come from UUIDs with allocation type=GATT Characteristic and Object Type here: https://btprodspecificationrefs.blob.core.windows.net/assigned-values/16-bit%20UUID%20Numbers%20Document.pdf
    #define GNSS_FEATURES_CHAR_UUID 0x2a6a
    

    /**
     * @brief Handler for the BLE connection and interfacing
     * See comment underneath for the profile that is being used
     * 
     */
    class BLEHandler{
        
    public:
        BLEHandler();

        void startAdvertise();
    private:
        /**
         * @brief Utilitary method to setup the BLE state of the ESP32 and BLEServer
         * 
         */
        void initServer();
        /**
         * @brief Utilitary method to setup all services and their characteristics
         * 
         */
        void initServices();

        void addCharacteristics(services_t servID, BLEService* service);

        BLEServer* server;

        BLEUUID servicesUUID[NB_SERVICES] = {
            BLEUUID(NOTIF_SERVICE_UUID),
            BLEUUID((uint16_t)GNSS_SERVICE_UUID),
            BLEUUID((uint16_t)BATTERY_SERVICE_UUID)
        };
    };

    //The profile implemented above is :
    /*
    +-------------------------------------------------------------------------------+
    | Server/Profile                                                                |
    |                                                                               |
    |    +------------------------------------------------------------------------+ |
    |    |  Service 1:Notification Service                                        | |
    |    |  UUID: 1e7b14e7-f5d9-4113-b249-d16b6ae7db7f                            | |
    |    |                                                                        | |
    |    |  +-------------------------------------------------------------------+ | |
    |    |  | Attribute 1: Notification Buffer                                  | | |
    |    |  | UUID: 8d5b53b8-fe04-4509-a689-82ab4c3d2507                        | | |
    |    |  | Properites: WRITE,NOTIFY                                          | | |
    |    |  | Value Type: notification_t (size = 64 bytes)                      | | |
    |    |  +-------------------------------------------------------------------+ | |
    |    |                                                                        | |
    |    +------------------------------------------------------------------------+ |
    |                                                                               |
    |    +------------------------------------------------------------------------+ |
    |    |  Service 2: GNSS                                                       | |
    |    |  UUID: 0x1335 (as per some spec)                                       | |
    |    |                                                                        | |
    |    |                                                                        | |
    |    |                   TBD depending on what values we need                 | |
    |    |                                                                        | |
    |    |                                                                        | |
    |    +------------------------------------------------------------------------+ |
    |                                                                               |
    |    +------------------------------------------------------------------------+ |
    |    |  Srvice 3: IMU-related`                                                | |
    |    |                                                                        | |
    |    |                                                                        | |
    |    |                                                                        | |
    |    |                               TBD                                      | |
    |    |                                                                        | |
    |    |                                                                        | |
    |    +------------------------------------------------------------------------+ |
    |                                                                               |
    |    +------------------------------------------------------------------------+ |
    |    |  Service 4: Battery --> Following spec                                 | |
    |    |  UUID: 0x180F                                                          | |
    |    |  +-------------------------------------------------------------------+ | |
    |    |  | Attribute 1: Battery Level                                        | | |
    |    |  | UUID: 0x2A19                                                      | | |
    |    |  | Properties: READ, NOTIFY                                          | | |
    |    |  | Value Type: unsigned short [0-100] (2 bytes), the battery level   | | |
    |    |  +-------------------------------------------------------------------+ | |
    |    |                                                                        | |
    |    +------------------------------------------------------------------------+ |
    |                                                                               |
    |                                                                               |
    +-------------------------------------------------------------------------------+
     */
};

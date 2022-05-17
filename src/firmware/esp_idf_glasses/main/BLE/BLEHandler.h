#pragma once

#include "BLEServer.h"
#include "BLEUUID.h"
#include "BLEUtils.h"

namespace SmartGlasses{   

    enum services_t : uint8_t{
	NOTIF_SERVICE,
	GNSS_SERVICE,
	IMU_SERVICE,
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
    
    #define IMU_SERVICE_UUID "319d217a-10e6-4cf1-95ea-d011aace7c01"
    #define IMU_SERVICE_ACCEL_X_CHAR_UUID "53e9a03c-eba3-4caf-a9f1-29ce88345644"
    #define IMU_SERVICE_ACCEL_Y_CHAR_UUID "9c84d685-a5be-4733-add7-ea04bb4a9d3b"
    #define IMU_SERVICE_ACCEL_Z_CHAR_UUID "1ec72f79-8809-41f7-a2da-6ffd3e1a0c3a"
    #define IMU_SERVICE_GYRO_X_CHAR_UUID "51056f51-e38a-4be8-a80d-7b7b838a3a56"
    #define IMU_SERVICE_GYRO_Y_CHAR_UUID "6add9f79-ef0d-45fa-bed5-9bdfe4c270b8"
    #define IMU_SERVICE_GYRO_Z_CHAR_UUID "273e3d6a-a507-422f-970b-e389295585b9"

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
            BLEUUID((uint16_t)IMU_SERVICE_UUID),
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
    |    |  UUID: 0x1819                                                          | |
    |    |  Following Spec                                                        | |
    |    |  +-------------------------------------------------------------------+ | |
    |    |  | Attribute 1:GNSS Features Supported                               | | |
    |    |  | UUID: 0x2A6A                                                      | | |
    |    |  |                                                                   | | |
    |    |  +-------------------------------------------------------------------+ | |
    |    |                                                                        | |
    |    |  +-------------------------------------------------------------------+ | |
    |    |  | Attribute 2: GNSS values                                          | | |
    |    |  | UUID: 0x2A67                                                      | | |
    |    |  +-------------------------------------------------------------------+ | |
    |    |                                                                        | |
    |    +------------------------------------------------------------------------+ |
    |                                                                               |
    |    +------------------------------------------------------------------------+ |
    |    |  Service 3: IMU-related                                                | |
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

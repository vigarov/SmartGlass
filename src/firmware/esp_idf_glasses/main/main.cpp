//Includes
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include <memory>
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "GeneralUtils.h"

#include "glasses_constants.h"
#include "glasses_types.h"

#if ARDUINO_IDE
#include <iostream>
#endif
// 123
//Globals and semaphores
SemaphoreHandle_t xDisplayUpdateSemaphore;

#if ARDUINO_IDE==1 || CLION_IDE == 1
#define TAKE_S_INF(semaphore) do{}while(xSemaphoreTake(xDisplayUpdateSemaphore,portMAX_DELAY)== pdFALSE)
#else
#define TAKE_S_INF(semaphore) xSemaphoreTake(xDisplayUpdateSemaphore,portMAX_DELAY)
#endif

TaskHandle_t* allTasks[NB_TASKS] = {0};
static const char* TAG = "Main Module";

#include "glasses_display.h"

//Logging
#if ARDUINO_IDE == 0 && CLION_IDE == 0
#include "esp_log.h"
#endif

void createTask(TaskFunction_t pvTaskCode, const char *const pcName, const uint32_t usStackDepth, UBaseType_t uxPriority, const BaseType_t xCoreID, size_t idx){

    #define PREFIX "Unable to create task "
    #define MID ", error: "
    #define TASK_ERROR_FMT  PREFIX "%d" MID "%d\n"

    int error = pdPASS;
    if((error = xTaskCreatePinnedToCore(pvTaskCode, pcName, usStackDepth, NULL,uxPriority,allTasks[idx],xCoreID)) != pdPASS
        || allTasks[T_BLE] == NULL){
/*        #if ARDUINO_IDE == 1
        std::cerr<< "-Error- " << TAG <<": "<<PREFIX<<idx<<MID<<error<<std::endl;
        #else
        ESP_LOGE(TAG, TASK_ERROR_FMT, idx,error)
        #endif*/
    }
}

void T_HandleBLE( void *pvParameters );
void T_Display( void *pvParameters );



//----------------------Entry point----------------------
/*#if ARDUINO_IDE
void setup (void)
#elif CLION_IDE
int main()
#else //ESP_IDF*/
extern "C" void app_main()
//#endif
{
    IFD(Serial.begin(115200));
    createTask(T_HandleBLE,"BLEHandler",10240,configMAX_PRIORITIES-1,PRO_CPU,T_BLE);
	//createTask(T_Display,"Display",1024,2,APP_CPU,T_DISPLAY);

	xDisplayUpdateSemaphore =  xSemaphoreCreateBinary();
    while (true) {Serial.println("hi 123"); delay(2000);}
    #if CLION_IDE
    return 0;
    #endif
}



//----------------------Bluetooth----------------------

typedef enum{
    NOTIF_BUFFER,
    //...
    BATTERY_LEVEL,
    NB_CHARS
}CHAR_IDX;

typedef enum{
	NOTIF_SERVICE,
	//GNSS_SERVICE,
	//IMU_SERVICE,
	BATTERY_SERVICE,
	NB_SERVICES
}SERVICE_IDX;

#define NOTIF_SERVICE_UUID "1e7b14e7-f5d9-4113-b249-d16b6ae7db7f"
#define NOTIF_BUFFER_ATTR_UUID "8d5b53b8-fe04-4509-a689-82ab4c3d2507"

#define BATTERY_SERVICE_UUID 0x180F
#define BATTERY_CHAR_UUID 0x2A19

static const BLEUUID servicesUUID[NB_SERVICES] = {BLEUUID(NOTIF_SERVICE_UUID),BLEUUID((uint16_t)BATTERY_SERVICE_UUID)};


//Globals
BLECharacteristic* characteristics[NB_CHARS];
std::shared_ptr<notification_t> notifBuffer;

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



//Using this as current profile:
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


/**
 * @brief Task in charge of handling the bluetooth.
 * @arg pvParameters (void *) pointer to context parameters. Unused
 */
void T_HandleBLE( void *pvParameters){
    //Setting up server
    Serial.println("Calling BLEDevice::init");
    esp_err_t errRc = ::nvs_flash_init();
    if (errRc != ESP_OK) {
        ESP_LOGE(TAG, "nvs_flash_init: rc=%d %s", errRc, GeneralUtils::errorToString(errRc));
        return;
    }
    BLEDevice::init(APP_NAME);
    BLEServer* server = BLEDevice::createServer();
    server->setCallbacks(new ServerCB()); //TODO: memory safety?


    //Creating the different services and attributes
    BLECharacteristic* tempP = NULL;

	//Service 1
    BLEService* notificationS = server->createService(servicesUUID[NOTIF_SERVICE]);
    tempP = notificationS->createCharacteristic(NOTIF_BUFFER_ATTR_UUID,BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);
    tempP->setCallbacks(new NotificationBufferCB());
    //Could implement custom descriptor (e.g.: a Characteristic User Description Descriptor ; see https://www.oreilly.com/library/view/getting-started-with/9781491900550/ch04.html#gatt_epd )
    //tempP->setValue("") done on creation
    characteristics[NOTIF_BUFFER] = tempP;
	notificationS->start();

    //TODO: continue setting up service and characteristics

	//Service 4
	BLEService* batteryService = server->createService(servicesUUID[BATTERY_SERVICE]);
	tempP = batteryService->createCharacteristic(BLEUUID((uint16_t)BATTERY_CHAR_UUID), BLECharacteristic::PROPERTY_READ|BLECharacteristic::PROPERTY_NOTIFY);
	#if DEBUG==1
	{
		int testValue = 67;
		tempP->setValue(testValue);
	}
	#endif
	characteristics[BATTERY_LEVEL] = tempP;
	batteryService->start();

	//Finished creating services, starting to advertise
	BLEAdvertising* advertiser = BLEDevice::getAdvertising();
	for(auto &u : servicesUUID){
		advertiser->addServiceUUID(u);
	}
	advertiser->setScanResponse(true);
	advertiser->setMinPreferred(0x12);
	BLEDevice::startAdvertising();

	//Finished setup, notifying all threads
	//TODO: notifyAllThreads();

    while(1){taskYIELD();} //loop infinitely to keep thread alive, explicit needed to not trigger the watchdog timer
}


//----------------------uOS and Applications----------------------

//TODO: do it...

/*
typedef enum{
	NEW_NOTIFICATION,

	NB_EVENTS
}event_t;
*/

/*
void T_uOS(void* pvParameters){

	//Thread safely writes data off from IMU and GPS to corresponding characteristics


}
*/
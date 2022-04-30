//----------------------ESP related defines----------------------
#ifndef PRO_CPU
#define PRO_CPU 0
#endif
#ifndef APP_CPU
#define APP_CPU 1
#endif

//----------------------IDE and Programming defines----------------------
#define ARDUINO_IDE 1
#define CLION_IDE 0

#define DEBUG 1

#ifdef DEBUG
#define IFD(x) x
#define CHECK_ERROR(expr,expected) if(expr!=expected) ESP_LOGE(TAG,"Expression %s failed, expected %s", #expr, #expected)
#else
#define IFD(x)
#define CHECK_ERROR(expr,expected)
#endif

#ifdef ARDUINO_IDE
void loop(void){}//No loop, tasks will handle everything
#endif

//----------------------Firmware----------------------

#define APP_NAME "Smart Glasses"

//Includes
#include <memory>
#if ARDUINO_IDE
#include <iostream>
#endif

//Logging
#if ARDUINO_IDE
#ifdef LOG_LOCAL_LEVEL
#undef LOG_LOCAL_LEVEL
#endif
#endif
#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE
#if ARDUINO_IDE == 0 && CLION_IDE == 0
#include "esp_log.h"
#endif
static const char* TAG = "Main Module";

//Notifications
template<size_t SIZE>
struct __attribute__((packed, aligned(1))) content_t{
    unsigned char terminated;
    char text[SIZE];
};

#define MAX_TITLE_LENGTH 12
#define MAX_ADD_INFO_LENGTH 48

enum app_t : uint16_t{
    SYSTEM,
    SMS,
    WHATSAPP,
    //...
    OTHER
};

//Make sure to align with the correct amount of bytes
struct __attribute__((packed, aligned(64))) notification_t{
    app_t application;
    content_t<MAX_TITLE_LENGTH> title;
    content_t<MAX_ADD_INFO_LENGTH> additionalInfo;
};

//Tasks
typedef enum{
    T_BLE,
    T_DISPLAY,
	
    NB_TASKS
}task_idx;
TaskHandle_t* allTasks[NB_TASKS] = {0};

void createTask(TaskFunction_t pvTaskCode, const char *const pcName, const uint32_t usStackDepth, UBaseType_t uxPriority, const BaseType_t xCoreID, size_t idx){

    #define PREFIX "Unable to create task "
    #define MID ", error: "
    #define TASK_ERROR_FMT  PREFIX "%d" MID "%d\n"

    int error = pdPASS;
    if((error = xTaskCreatePinnedToCore(pvTaskCode, pcName, usStackDepth, NULL,uxPriority,allTasks[idx],xCoreID)) != pdPASS
        || allTasks[T_BLE] == NULL){
        #if ARDUINO_IDE == 1
        std::cerr<< "-Error- " << TAG <<": "<<PREFIX<<idx<<MID<<error<<std::endl;
        #else
        ESP_LOGE(TAG, TASK_ERROR_FMT, idx,error)
        #endif
    }
}

void T_HandleBLE( void *pvParameters );
void T_Display( void *pvParameters );


//Globals and semaphores
SemaphoreHandle_t xDisplayUpdateSemaphore;

#if ARDUINO_IDE==1 || CLION_IDE == 1
#define TAKE_S_INF(semaphore) do{}while(xSemaphoreTake(xDisplayUpdateSemaphore,portMAX_DELAY)== pdFALSE)
#else
#define TAKE_S_INF(semaphore) xSemaphoreTake(xDisplayUpdateSemaphore,portMAX_DELAY)
#endif

//----------------------Entry point----------------------
#if ARDUINO_IDE
void setup (void)
#elif CLION_IDE
int main()
#else //ESP_IDF
void app_main (void)
#endif
{
    IFD(Serial.begin(115200));
    createTask(T_HandleBLE,"BLEHandler",10240,configMAX_PRIORITIES-1,PRO_CPU,T_BLE);
	createTask(T_Display,"Display",1024,2,APP_CPU,T_DISPLAY)

	xDisplayUpdateSemaphore =  xSemaphoreCreateBinary();
    #if CLION_IDE
    return 0;
    #endif
}



//----------------------Bluetooth----------------------

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

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

    while(1){} //loop infinitely to keep thread alive
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

//----------------------Display----------------------

#include "HyperDisplay_UG2856KLBAG01.h" 

#define SERIAL_PORT Serial  
#define SPI_PORT SPI        // Used if USE_SPI == 1

#define CS_PIN 4            // Used only if USE_SPI == 1
#define DC_PIN 5            // Used only if USE_SPI == 1
UG2856KLBAG01_SPI myTOLED;  // Declare a SPI-based Transparent OLED object called myTOLED

typedef struct{
	unsigned char x;
	unsigned char y;
}__attribute__((packed))pixel_pair_t;

typedef struct{
	unsigned char priority; //TODO: can make it a bitfield to save... one byte if necessary
	pixel_pair_t* p;
	size_t len;
	unsigned char overwrite;
}__attribute__((packed)) display_t;

volatile display_t toBeDisplayed = {0};


void updateAwaitingDisplay(display_t* newFrames){
	TAKE_S_INF(xDisplayUpdateSemaphore); 
	if(newFrames->priority > toBeDisplayed.priority){ 
	//Not >= since if two events with the same priority happen to occur at the same time, it is logical to keep to first and disregard the second
	//This however should be rare (only e.g. I can think of is if you press on a "menu UP/DOWN" button before the menu has actually displayed
		if(toBeDisplayed.p != NULL){
			//Freeing only if an event is waiting to be displayed but hasn't yet been displyed
			free(toBeDisplayed.p);
			toBeDisplayed.p=NULL;
		}
		toBeDisplayed = *newFrames; //Deep copy
	}
	xSemaphoreGive(xDisplayUpdateSemaphore);
	xTaskNotifyGive(allTasks[T_DISPLAY]);
	
}

void T_Display(void* pvParameters){
	SPI_PORT.begin();
	myTOLED.begin(CS_PIN, DC_PIN, SPI_PORT);
	
	while(1){
		ulTaskNotifyTake(pdTRUE,portMAX_DELAY); //TODO: RTOS suggests to not wait indefinitely, but rather TO at some point and e.g. log error. Why not, can also refactor infinite semaphore take
		TAKE_S_INF(xDisplayUpdateSemaphore);
		//Make a copy of the context to be displayed, and release semaphore
		//This enable other potentially waiting threads to continue while we are displaying current context
		display_t toDisplay = toBeDisplayed;
		free(toBeDisplayed.p);
		toBeDisplayed = {0};
		xSemaphoreGive(xDisplayUpdateSemaphore);
		//Giving the semaphore back and starting to actually display
		if(toDisplay.overwrite){
			myTOLED.clearDisplay();
		}
		for(size_t i =0; i<toDisplay.len;i++){
			pixel_pair_t* pixels = p+i;
			myTOLED.pixelSet(pixels->x,pixels->y);
		}
		myTOLED.setContrastControl(128); //TODO: needed to be done @ every write?
	}
}




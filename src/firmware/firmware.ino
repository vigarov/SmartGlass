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

//----------------------Application----------------------

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
    T_uOS,
    
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
    

    #if CLION_IDE
    return 0;
    #endif
}



//----------------------Bluetooth----------------------
typedef enum{
    NOTIF_BUFFER,
    
    
    NB_CHARS
}CHAR_IDX;



#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

//Globals
BLECharacteristic* characteristics[NB_CHARS];
std::shared_ptr<notification_t> notifBuffer;

class ServerCB : public BLEServerCallbacks{
    void onConnect(BLEServer* pServer) override {
        //Notify the uOS to change the header
        //TODO: either taskNotify uOS or semaphore unlock (not preferrable)
        //      AND wrtie to some bitset/flag (atomically) to show what is updated (in that case BT connectivity)
        
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
|    |  | Attribute 1: Notificcation Buffer                                 | | |
|    |  | UUID: 8d5b53b8-fe04-4509-a689-82ab4c3d2507                        | | |
|    |  | Properites: WRITE,NOTIFY                                          | | |
|    |  | Value Type: notification_t (size = 64 bytes)                      | | |
|    |  +-------------------------------------------------------------------+ | |
|    |                                                                        | |
|    +------------------------------------------------------------------------+ |
|                                                                               |
|    +------------------------------------------------------------------------+ |
|    |  Service 2: GNSS                                                       | |
|    |                                                                        | |
|    |                                                                        | |
|    |                                                                        | |
|    |                      TBD                                               | |
|    |                                                                        | |
|    |                                                                        | |
|    +------------------------------------------------------------------------+ |
|                                                                               |
|    +------------------------------------------------------------------------+ |
|    |  Srvice 3: IMU-related                                                 | |
|    |                                                                        | |
|    |                                                                        | |
|    |                                                                        | |
|    |                               TBD                                      | |
|    |                                                                        | |
|    |                                                                        | |
|    +------------------------------------------------------------------------+ |
|                                                                               |
+-------------------------------------------------------------------------------+
 */

#define NOTIF_SERVICE_UUID "1e7b14e7-f5d9-4113-b249-d16b6ae7db7f"
#define NOTIF_BUFFER_ATTR_UUID "8d5b53b8-fe04-4509-a689-82ab4c3d2507"
 
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
    
    BLEService* notificationS = server->createService(NOTIF_SERVICE_UUID);
    tempP = notificationS->createCharacteristic(NOTIF_BUFFER_ATTR_UUID,BLECharacteristic:: PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);
    tempP->setCallbacks(new NotificationBufferCB());
    //Could implement custom descriptor (e.g.: a Characteristic User Description Descriptor ; see https://www.oreilly.com/library/view/getting-started-with/9781491900550/ch04.html#gatt_epd )
    //tempP->setValue("") done on creation
    characteristics[NOTIF_BUFFER] = tempP;
    
    //TODO: continue setting up characteristics

    //TODO: start adverising

    while(1){} //loop infinitely to keep thread alive
}

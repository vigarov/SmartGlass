//Includes
#include <memory>
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "GeneralUtils.h" // Also from BLE library

#include "glasses_constants.h"
#include "glasses_types.h"
#include "glasses_globals_manager.h"

#if ARDUINO_IDE
#include <iostream>
#endif

static const char* TAG = "Main Module";

//Globals
std::shared_ptr<notification_t> notifBuffer;

#include "glasses_display.h"

void set_glasses_logging_levels() {
    esp_log_level_set("*", ESP_LOG_INFO); // setting default log level here too just in case although already specified in menuconfig.
    esp_log_level_set(GlobalsManager::main_module_debug_name, ESP_LOG_VERBOSE);
    esp_log_level_set(toplevel_tasks_BLE_tag, ESP_LOG_VERBOSE);
    esp_log_level_set(toplevel_tasks_GNSS_tag, ESP_LOG_VERBOSE);
    esp_log_level_set(toplevel_tasks_Display_tag, ESP_LOG_VERBOSE);
}

//----------------------Entry point----------------------
/*#if ARDUINO_IDE
void setup (void)
#elif CLION_IDE
int main()
#else //ESP_IDF*/
extern "C" void app_main()
//#endif
{
    set_glasses_logging_levels();
    IFD(Serial.begin(115200));
    GlobalsManager glob_mgr;
    vTaskDelay(0); // need to let 0 run too

    glob_mgr.init_tasks();

	
    while (true) {/*Serial.println("hi 123"); */delay(2000);}
    #if CLION_IDE
    return 0;
    #endif
}



//----------------------Bluetooth----------------------




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
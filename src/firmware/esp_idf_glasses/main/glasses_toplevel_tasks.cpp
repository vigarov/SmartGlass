#include "glasses_globals_manager.h"
#include "glasses_ble_callbacks.h"
#include "glasses_location.h"
#include "glasses_toplevel_tasks.h"

/**
 * @brief Task in charge of handling the bluetooth.
 * @arg pvParameters (void *) pointer to context parameters. Unused
 */
void T_HandleBLE( void *pvParameters){

    GlobalsManager* const glob_mgr = (GlobalsManager*)pvParameters;

    glob_mgr->init_server();
    glob_mgr->init_services();

    vTaskDelay(0); // let idle run for a bit

    //Creating the different services and attributes
    BLECharacteristic* tempP = NULL;

	//Service 1
    BLEService* notificationS = glob_mgr->get_svc(NOTIF_SERVICE);
    // BLEService* notificationS = server->createService(servicesUUID[NOTIF_SERVICE]);
    glob_mgr->characteristics[NOTIF_BUFFER] = notificationS->createCharacteristic(NOTIF_BUFFER_ATTR_UUID,BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);
    glob_mgr->characteristics[NOTIF_BUFFER]->setCallbacks(new NotificationBufferCB());
    //Could implement custom descriptor (e.g.: a Characteristic User Description Descriptor ; see https://www.oreilly.com/library/view/getting-started-with/9781491900550/ch04.html#gatt_epd )
    //tempP->setValue("") done on creation

    //TODO: continue setting up service and characteristics

	//Service 4
    BLEService* batteryService = glob_mgr->get_svc(BATTERY_SERVICE);
	tempP = batteryService->createCharacteristic(BLEUUID((uint16_t)BATTERY_CHAR_UUID), BLECharacteristic::PROPERTY_READ|BLECharacteristic::PROPERTY_NOTIFY);
	#if DEBUG==1
	{
		int testValue = 67;
		tempP->setValue(testValue);
	}
	#endif
	glob_mgr->characteristics[BATTERY_LEVEL] = tempP;

    add_gnss_characteristics(glob_mgr);

    glob_mgr->start_advertise();

    

	//Finished setup, notifying all threads
	//TODO: notifyAllThreads();

    while(1){
        vTaskDelay(10/portTICK_PERIOD_MS);
        // taskYIELD();
    } //loop infinitely to keep thread alive, explicit yield needed to not trigger the watchdog timer
}

void T_Display(void* pvParameters){
  GlobalsManager* const glob_mgr = (GlobalsManager*)pvParameters;

  glob_mgr->display_manager.init();
  
  while(1){
      glob_mgr->display_manager.refresh_display();
  }
}

void T_GNSS_Task(void *pvParameters) {
    GlobalsManager* const glob_mgr = (GlobalsManager*)pvParameters;

    xTaskNotifyWaitIndexed(BLE_INIT_READY,0x00,0,NULL,portMAX_DELAY);

    location_data_t loc_data;

    int32_t lat = 0;
    while (true) {
        loc_data.flags = LOCATION_DATA_FLAGS_LOCATION_PRESENT | LOCATION_DATA_FLAGS_POS_STATUS_POS_OK;
        loc_data.lat = lat;
        lat++;
        loc_data.lon = 60000000;
        glob_mgr->characteristics[GNSS_CHAR]->setValue((uint8_t*)&loc_data,sizeof(location_data_t));
        const TickType_t wait_between_updates = 100/portTICK_PERIOD_MS;
        vTaskDelay(wait_between_updates);
    }
}
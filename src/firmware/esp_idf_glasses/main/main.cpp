#include "GlobalsManager.h"
#include "esp_log.h"
#include "constants.h"
#include "utils.h"

//----------------------Entry point----------------------
extern "C" void app_main()
{
    Serial.begin(115200); // handy for cheats
    SmartGlasses::resetTime(); //TODO: rather emulate an SNTP server over BLE with the Arduino Phone
    esp_log_level_set("*", ESP_LOG_INFO); // setting default log level here too just in case although already specified in menuconfig.
    SmartGlasses::GlobalsManager::getInstance().getTaskManager().initAllTasks();
    ESP_LOGI(APP_NAME,"Initialised all tasks, exiting main");
    //The [esp32 application flow](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/startup.html#app-main-task)
    //shows that there is no need for the app_main task to be kept alive
    //all tasks scheduled by it will keep living
}

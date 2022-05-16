#include "GlobalsManager.h"
#include "esp_log.h"
#include "constants.h"
#include "utils.h"

void set_glasses_logging_levels() {
    esp_log_level_set("*", ESP_LOG_INFO); // setting default log level here too just in case although already specified in menuconfig.
    esp_log_level_set(GlobalsManager::main_module_debug_name, ESP_LOG_VERBOSE);
    esp_log_level_set(toplevel_tasks_BLE_tag, ESP_LOG_VERBOSE);
    esp_log_level_set(toplevel_tasks_GNSS_tag, ESP_LOG_VERBOSE);
    esp_log_level_set(toplevel_tasks_Display_tag, ESP_LOG_VERBOSE);
}

//----------------------Entry point----------------------
extern "C" void app_main()
{
    SmartGlasses::resetTime(); //TODO: rather emulate an SNTP server over BLE with the Arduino Phone
    SmartGlasses::GlobalsManager::getInstance().getTaskManager().initAllTasks();
    ESP_LOGI(APP_NAME,"Initialised all tasks, exiting main");
    //The [esp32 application flow](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/startup.html#app-main-task)
    //shows that there is no need for the app_main task to be kept alive
    //all tasks scheduled by it will keep living
}

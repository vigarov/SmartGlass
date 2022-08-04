#include "GlobalsManager.h"
#include "esp_log.h"
#include "esp_heap_trace.h"
#include "constants.h"
#include "utils.h"

//----------------------Entry point----------------------
extern "C" void app_main()
{
    IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
    SmartGlasses::resetTime(); //TODO: rather emulate an SNTP server over BLE with the Arduino Phone
    auto& globMgr = SmartGlasses::GlobalsManager::getInstance();
    globMgr.getDeviceManager().initAll();
    globMgr.getTaskManager().initAllTasks();
    ESP_LOGI(APP_NAME,"Initialised all tasks, exiting main");
    //The [esp32 application flow](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/startup.html#app-main-task)
    //shows that there is no need for the app_main task to be kept alive
    //all tasks scheduled by it will keep living
}

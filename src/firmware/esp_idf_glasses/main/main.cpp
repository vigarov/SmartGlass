#include "GlobalsManager.h"
#include "esp_log.h"
#include "constants.h"

//----------------------Entry point----------------------
extern "C" void app_main()
{
    SmartGlasses::GlobalsManager::getInstance().getTaskManager().initAllTasks();
    ESP_LOGI(APP_NAME,"Initialised all tasks, exiting main");
    //The [esp32 application flow](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/startup.html#app-main-task)
    //shows that there is no need for the app_main task to be kept alive
    //all tasks scheduled by it will keep living
}

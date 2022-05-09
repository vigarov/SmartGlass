//Includes
#include "GlobalsManager.h"

//----------------------Entry point----------------------
extern "C" void app_main() //TODO: why extern "C" ?
{
    SmartGlasses::GlobalsManager& glob_mgr = SmartGlasses::GlobalsManager::getInstance();
    vTaskDelay(0); // need to let 0 run too; TODO:?

    glob_mgr.getTaskManager().initAllTasks();


	
    while (true) {Serial.println("hi 123"); delay(2000);} //TODO: Useless? see application flow of esp32, scheduled atsks should remain alive iirc
}

#include "DeviceManager.h"

using namespace SmartGlasses;

std::shared_ptr<DisplayManager> DeviceManager::getDisplayManager(){
    return displayManager;
}
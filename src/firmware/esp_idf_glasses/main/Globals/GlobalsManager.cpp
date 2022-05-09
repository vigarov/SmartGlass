#include "GlobalsManager.h"

using namespace SmartGlasses;

GlobalsManager& GlobalsManager::getInstance(){
    static GlobalsManager instance;
    return instance;
}

TaskManager& GlobalsManager::getTaskManager(){
    return taskManager;
}

DeviceManager& GlobalsManager::getDeviceManager(){
    return deviceManager;
}

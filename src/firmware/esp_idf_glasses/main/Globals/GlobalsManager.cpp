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

void GlobalsManager::setBLEHandler(std::shared_ptr<BLEHandler> bleHandler){
    bHandler = bleHandler;
}

std::shared_ptr<BLEHandler> GlobalsManager::getBLEHandler(){
    return bHandler;
}
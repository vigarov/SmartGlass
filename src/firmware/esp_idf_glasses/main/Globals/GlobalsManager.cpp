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
    m_bHandler = bleHandler;
}

std::shared_ptr<BLEHandler> GlobalsManager::getBLEHandler(){
    return m_bHandler;
}

void GlobalsManager::setUOS(std::shared_ptr<uOS> uOS_p){
    m_uOS = uOS_p;
}

std::shared_ptr<uOS> GlobalsManager::getUOS(){
    return m_uOS;
}

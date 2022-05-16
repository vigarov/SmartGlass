#include "DeviceManager.h"

using namespace SmartGlasses;

DeviceManager::DeviceManager(){
    m_allDevices[DISPLAY_IDX] = std::make_shared<DisplayManager>();
    m_allDevices[TIMER_1s_IDX] = std::make_shared<Timer<SYSTEM_TIMER_GROUP,ONE_S_ID>>();
    m_allDevices[TIMER_60s_IDX] = std::make_shared<Timer<SYSTEM_TIMER_GROUP,SIXTY_S_ID>>();
}

void DeviceManager::initAll(){
    for(auto& device: m_allDevices){
        device->init();
    }
}

//Note: for the following getters, it would have beend much better/cleanlier/correct do dynamic_cast
//However, this leads to a compile error (see also https://arduino.stackexchange.com/questions/55157/dynamic-cast-not-permitted-with-fno-rtti)
//We therefore static cast (since we have filled m_allDevices, we are sure of the output data type and it OK)
std::shared_ptr<DisplayManager> DeviceManager::getDisplayManager(){
    return std::static_pointer_cast<DisplayManager>(m_allDevices[DISPLAY_IDX]);
}

std::shared_ptr<Timer<SYSTEM_TIMER_GROUP,ONE_S_ID>> DeviceManager::getOneSecondTimer(){
    return std::static_pointer_cast<Timer<SYSTEM_TIMER_GROUP,ONE_S_ID>>(m_allDevices[TIMER_1s_IDX]);
}
std::shared_ptr<Timer<SYSTEM_TIMER_GROUP,SIXTY_S_ID>> DeviceManager::getSixtySecondTimer(){
    return std::static_pointer_cast<Timer<SYSTEM_TIMER_GROUP,SIXTY_S_ID>>(m_allDevices[TIMER_60s_IDX]);
}


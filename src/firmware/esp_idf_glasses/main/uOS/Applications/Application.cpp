#include "Application.h"
#include "GlobalsManager.h"
#include "esp_log.h"

using namespace SmartGlasses;

//Doing this here to avoid circular dependency through GlobalsManager if we were to simply use initialization lists in the .h ctor
Application::Application(std::shared_ptr<uOS> uOS_p, APP_ID id)
: Container(nullptr)
{
    m_uOS = uOS_p;
    m_displayManager = DISPLAYMANAGER;
    this->id = id;
    ESP_LOGI("Base Application","Created application w/ id=%d",id);
}
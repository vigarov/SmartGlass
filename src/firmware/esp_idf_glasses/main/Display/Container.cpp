#include "Container.h"
#include "utils.h"

using namespace SmartGlasses;

void Container::addChild(std::shared_ptr<Displayable> child){
    m_displayables.push_back(child);
    child->m_taskToNotifyOnDraw = m_taskToNotifyOnDraw;
}

void Container::update(){
    ESP_LOGI(m_contentName.c_str(),"Updating");
    updateAllChildren();
}

void Container::hide(){
    hideAllChildren();
}


void Container::changeTaskToBeUpdated(TaskHandle_t newTask){
    Displayable::changeTaskToBeUpdated(newTask);
    for(auto& displayable : m_displayables){
        displayable->changeTaskToBeUpdated(newTask);
    }
}
void Container::updateAllChildren(){
    for(auto& displayable : m_displayables){
        displayable->update();
        if(ulTaskNotifyTake(pdTRUE,50/portTICK_PERIOD_MS) == pdFALSE){
            IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
            ESP_LOGW(("Container"+m_contentName).c_str(),"Didn't get notified, still coninuing with next update");
        }
    }
    ESP_LOGI(("Container"+m_contentName).c_str(),"Finished updating all children");
}

void Container::hideAllChildren(){
    for(auto& displayable : m_displayables){
        displayable->hide();
        if(ulTaskNotifyTake(pdTRUE,100/portTICK_PERIOD_MS) == pdFALSE){
            ESP_LOGE(("Container"+m_contentName).c_str(),"Didn't get notified, still coninuing with next hide");
        }
    }
    ESP_LOGI(("Container"+m_contentName).c_str(),"Finished hiding all children");
}
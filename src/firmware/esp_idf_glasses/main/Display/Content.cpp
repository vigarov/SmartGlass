#include "Content.h"
#include "GlobalsManager.h"
#include "constants.h"

using namespace SmartGlasses;

void Content::update(){
    if(m_setup){
        xTaskNotifyGive(m_innerObjectTask);
    }
}

void Content::setup(){
    createTask(T_Update,(m_contentName.substr(0,configMAX_TASK_NAME_LEN - 4) + "_UT").c_str(),1024,DISPLAYABLE_UPDATE_PRIORITY,&m_innerObjectTask,APP_CPU,this);
    m_setup=true;
    updatePixels();
    ESP_LOGI(m_contentName.c_str(),"Finished Setup");
}

void Content::T_Update(void* pvParameters){
    Content* currentContent = (Content*) pvParameters;
    while(true){
        if(ulTaskNotifyTake(pdTRUE,20000 / portTICK_PERIOD_MS) == pdFALSE){
            ESP_LOGI(currentContent->m_contentName.c_str(),"No new content received after 20 seconds");
        }else{
            currentContent->updatePixels(); 
            currentContent->borderAndUpdate();
        }
    }
}

std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction> Content::computeBorder(std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction>& pixelSet){
    std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction> retSet;
    if(m_overwrite){
        for(auto &p : pixelSet){
            if(p.x<m_borders.topLeft.x){
                m_borders.topLeft.x = p.x;
            }
            if(p.y<m_borders.topLeft.y){
                m_borders.topLeft.y = p.y;
            }
            if(p.x>m_borders.bottomRight.x){
                m_borders.bottomRight.x = p.x;
            }
            if(p.y>m_borders.bottomRight.y){
                m_borders.bottomRight.y = p.y;
            }
        }
        for(unsigned char x=m_borders.topLeft.x ; x<m_borders.bottomRight.x ; x++){
            for(unsigned char y = m_borders.topLeft.y; y<m_borders.bottomRight.y; y++){
                pixel_pair_t p = {x,y};
                if(!pixelSet.count(p)){
                    retSet.insert(std::move(p));
                }
            }
        }
    }
    return std::move(retSet);
}

Content::~Content(){
    if(m_innerObjectTask != NULL){
        vTaskDelete(&m_innerObjectTask);
    }
}

void Content::borderAndUpdate(){
    //Now that the new values for the pixels have been fetch, we can compute the new border
    std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction> notInPixelsSet = std::move(computeBorder(m_pixels));
    //and then update the display
    GlobalsManager::getInstance().getDeviceManager().getDisplayManager()->update_awaiting_display(std::move(std::make_unique<display_t>(display_t{m_priority,{m_pixels,std::move(notInPixelsSet),m_offsets}}))); 
    //We don't move the m_pixels since we might not be updating them each time
}
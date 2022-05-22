#include "Content.h"
#include "GlobalsManager.h"
#include "constants.h"
#include "utils.h"

using namespace SmartGlasses;

void Content::update(){
    ESP_LOGI(m_contentName.c_str(),"Got update request");
    if(m_setup){
        xTaskNotifyGive(m_innerObjectTask);
    }
}

void Content::createUpdateTask(){
    createTask(T_Update,(m_contentName.substr(0,configMAX_TASK_NAME_LEN - 4) + "_UT").c_str(),1024,DISPLAYABLE_UPDATE_PRIORITY,&m_innerObjectTask,APP_CPU,this);
}

void Content::setup(){
    createUpdateTask();
    m_setup=true;
    updatePixels();
    canvasAndUpdate();
    ESP_LOGI(m_contentName.c_str(),"Finished Setup");
}

void Content::T_Update(void* pvParameters){
    Content* currentContent = (Content*) pvParameters;
    while(true){
        if(ulTaskNotifyTake(pdTRUE,20000 / portTICK_PERIOD_MS) == pdFALSE){
            ESP_LOGI(currentContent->m_contentName.c_str(),"No new content received after 20 seconds");
        }else{
            currentContent->updatePixels(); 
            currentContent->canvasAndUpdate();
        }
    }
}

void Content::computeCanvas(){
    ESP_LOGI(m_contentName.c_str(),"Requested canvas update (ow=%d,modif=%d)",m_overwrite,m_modifiedSinceLastUpdate);
    if(m_overwrite && m_modifiedSinceLastUpdate){
        actuallyComputeCanvas();
    }
}

void Content::actuallyComputeCanvas(){
    for(auto &p : m_pixels){
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
        for(unsigned char y = m_borders.topLeft.y; y<=m_borders.bottomRight.y; y++){
            pixel_pair_t p = {x,y};
            if(!m_pixels.count(p)){
                m_canvas.insert(std::move(p));
            }
        }
    }
}

void Content::actuallyUpdateDisplay(){
    DISPLAYMANAGER->update_awaiting_display(std::move(std::make_unique<display_t>(display_t{m_priority,{m_pixels,m_canvas,m_offsets}}))); 
}

void Content::forceDisplay(){
    actuallyComputeCanvas();
    actuallyUpdateDisplay();
}

void Content::forceHide(){
    actuallyComputeCanvas();
    std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction> temp;
    unordered_set_intersection(m_pixels.begin(),m_pixels.end(),
                    m_canvas.begin(),m_canvas.end(),
                    std::inserter(temp, temp.begin()));
    DISPLAYMANAGER->update_awaiting_display(std::move(std::make_unique<display_t>(display_t{m_priority,{temp,temp,m_offsets}}))); 
}

Content::~Content(){
    if(m_innerObjectTask != NULL){
        vTaskDelete(&m_innerObjectTask);
    }
}

void Content::canvasAndUpdate(){
    ESP_LOGI(m_contentName.c_str(),"request canvas recomputation and update");
    if(m_modifiedSinceLastUpdate){
        //Now that the new values for the pixels have been fetched, we can compute the new canvas
        computeCanvas();
        //and then update the display
        actuallyUpdateDisplay();
        //We don't move the m_pixels since we might not be updating them each time
        m_modifiedSinceLastUpdate = false;
    }
}

border_t Content::getBorders() {
    return m_borders;
}

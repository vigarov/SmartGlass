#include "Content.h"
#include "GlobalsManager.h"
#include "constants.h"
#include "utils.h"

using namespace SmartGlasses;

void Content::update(){
    ESP_LOGD(m_contentName.c_str(),"Got update request");
    canvasAndUpdate(std::move(createPixels()));
}

void Content::hide(){
    forceHide();
}

std::unique_ptr<pixels_set_t> Content::computeCanvas(const pixels_set_t& pixels){
    ESP_LOGI(m_contentName.c_str(),"Requested canvas update (ow=%d,modif=%d)",m_overwrite,m_modifiedSinceLastUpdate);
    auto temp = std::make_unique<pixels_set_t>();
    if(m_overwrite && m_modifiedSinceLastUpdate){
        temp.reset(nullptr);
        temp=std::move(actuallyComputeCanvas(pixels));
    }
    return std::move(temp);
    
}

std::unique_ptr<pixels_set_t> Content::actuallyComputeCanvas(const pixels_set_t& pixels){
    
    auto canvas_p = std::make_unique<pixels_set_t>();
    for(auto &p : pixels){
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
            if(!pixels.count(p)){
                canvas_p->insert(std::move(p));
            }
        }
    }
    return std::move(canvas_p);
}

void Content::actuallyUpdateDisplay(std::unique_ptr<pixels_set_t> pixels,std::unique_ptr<pixels_set_t> canvas){
    DISPLAYMANAGER->update_awaiting_display(std::move(std::make_unique<display_t>(display_t{m_priority,
        std::make_unique<Drawable>(std::move(pixels),std::move(canvas),m_offsets,m_animate,m_taskToNotifyOnDraw)}))); 
}

void Content::forceDisplay(){
    auto pixels = std::move(createPixels());
    auto canvas = std::move(actuallyComputeCanvas(*pixels));
    actuallyUpdateDisplay(std::move(pixels),std::move(canvas));
}

void Content::forceHide(){
    auto pixels = std::move(createPixels());
    auto empty = std::make_unique<pixels_set_t>();
    DISPLAYMANAGER->update_awaiting_display(std::move(std::make_unique<display_t>(display_t{m_priority,
    std::make_unique<Drawable>(std::move(empty),std::move(pixels),m_offsets,m_animate,m_taskToNotifyOnDraw)}))); 
    m_modifiedSinceLastUpdate = true; //so calling update will re-show what should be shown
}

void Content::canvasAndUpdate(std::unique_ptr<pixels_set_t> pixels){
    ESP_LOGD(m_contentName.c_str(),"request canvas recomputation and update");
    if(m_modifiedSinceLastUpdate){
        //Now that the new values for the pixels have been fetched, we can compute the new canvas
        auto canvas_p = computeCanvas(*pixels);
        //and then update the display
        actuallyUpdateDisplay(std::move(pixels),std::move(canvas_p));
        //We don't move the m_pixels since we might not be updating them each time
        m_modifiedSinceLastUpdate = false;
    }
}

border_t Content::getBorders() {
    return m_borders;
}

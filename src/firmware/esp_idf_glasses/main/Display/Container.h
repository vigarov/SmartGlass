#pragma once

#include "Content.h"
#include "Display.h"
#include <memory>
#include <vector>
#include "Displayable.h"

namespace SmartGlasses{

    class Container : public Displayable{   
    public:
        Container(TaskHandle_t notifyOnOperation,std::string contentName = "Default Name",bool overwrites = false, pixel_pair_t offsets = {0,0},unsigned char animate = false, unsigned char priority = 1):
        Displayable(std::move(contentName),overwrites,std::move(offsets),animate, priority){
            m_taskToNotifyOnDraw = notifyOnOperation;
        }

        void update() override;
        void hide() override;

        void changeTaskToBeUpdated(TaskHandle_t newTask) override;
        void addChild(std::shared_ptr<Displayable> child);
    protected:
    
        void updateAllChildren();
        void hideAllChildren();
        std::vector<std::shared_ptr<Displayable>> m_displayables;
    };
};
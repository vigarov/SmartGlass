#pragma once
#include <memory>
#include <unordered_set>
#include <string>
#include "Display.h"
#include "esp_log.h"
#include "utils.h"

namespace SmartGlasses{

    #define DISPLAYABLE_UPDATE_PRIORITY 3

    class Container; //Forward Declaration

    class Content {
        
    public:
        Content(std::string contentName = "Default Name",bool overwrites = false, pixel_pair_t offsets = {0,0}, unsigned char priority = 1,std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction>pixels = std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction>()) : 
        m_pixels(std::move(pixels)),m_offsets(std::move(offsets)),m_contentName(std::move(contentName)),m_overwrite(overwrites), m_priority(priority) {
            ESP_LOGI(m_contentName.c_str(), "Creating object");
        }
        virtual void setup(); //Must be called after constructor
        virtual void update();
        virtual ~Content();

    protected:
        virtual void updatePixels() = 0;
        std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction> m_pixels;
        border_t m_borders = {{UINT8_MAX,UINT8_MAX},{0,0}};
        const pixel_pair_t m_offsets;

        void borderAndUpdate();
    private :
        std::string m_contentName;
        bool m_setup = false;
        
        std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction> computeBorder(std::unordered_set<pixel_pair_t,pixel_pair_t::HashFunction>& pixelSet);
        bool m_overwrite;

        TaskHandle_t m_innerObjectTask = NULL;

        unsigned char m_priority;

        static void T_Update(void* pvParameters);
    };

    class ConstantContent : public Content{
    public:
        ConstantContent(std::string contentName = "Constant Content", bool overwrites = false, pixel_pair_t offsets = {0,0},unsigned char priority = 1) : Content(contentName,overwrites,std::move(offsets),priority){}
        void setup() override {updatePixels(); borderAndUpdate();}
        void update() override {}
    };
};
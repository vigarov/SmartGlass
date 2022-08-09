#pragma once

#include "Content.h"
#include "Navigation.h"

namespace SmartGlasses{

    class Arrow : public Content{
    public:
        Arrow(std::string name, direction_t direction, bool overwrites = true,pixel_pair_t offsets = {0,0}, unsigned char animate = false, unsigned char priority = 1)
        : Content(name,overwrites,offsets,animate,priority),m_direction(direction),m_initalOffsets(offsets){}

        void changeDirection(direction_t newDirection);
    protected:
        std::unique_ptr<pixels_set_t> createPixels() override;
    private:
        direction_t m_direction;
        const pixel_pair_t m_initalOffsets;

        std::unique_ptr<pixels_set_t> straightArrow();
        std::unique_ptr<pixels_set_t> leftArrow();
        std::unique_ptr<pixels_set_t> rightArrow();

    };

};
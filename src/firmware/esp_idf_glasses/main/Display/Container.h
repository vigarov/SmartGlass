#pragma once

#include "Content.h"
#include "Display.h"
#include <vector>

namespace SmartGlasses{

    class Container{   
    protected:
        std::vector<std::shared_ptr<Content>> m_contents;
    }
};
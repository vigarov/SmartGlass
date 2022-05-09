#pragma once
#include "Application.h"
#include "uOS.h"

namespace SmartGlasses{

    class IdleApp : public Application{
    public:
        IdleApp(uOS* uOS) : Application(uOS){}
    private:
        void onClose() override;
        void onResume() override;

        void displayHeader();
    };

}
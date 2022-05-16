#pragma once
#include "uOS.h"
#include "Application.h"
#include <memory>

namespace SmartGlasses{

    class IdleApp : public Application{
    public:
        IdleApp(std::shared_ptr<uOS> uOS_p) : Application(uOS_p,IDLE){}
    private:
        void onClose() override;
        void onResume() override;
        void run() override;

        void createAndDisplayHeader(); //TODO: const?
    };

}
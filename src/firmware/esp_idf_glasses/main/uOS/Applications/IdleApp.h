#pragma once
#include "Application.h"
#include <memory>
#include "uOS.h"

namespace SmartGlasses{

    class IdleApp : public Application{
    public:
        IdleApp(std::shared_ptr<uOS> uOS) : Application(uOS){}
    private:
        void onClose() override;
        void onResume() override;

        void displayHeader(); //TODO: const?
    };

}
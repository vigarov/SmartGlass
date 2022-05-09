#pragma once

#include "uOS.h"

namespace SmartGlasses{
    enum APP_ID{
        NONE=-1,
        IDLE,
        //...
        NB_APPS
    };

    /**
     * @brief Base class for any application.
     * 
     */
    class Application{
    friend class ApplicationContainer;
    public:
        Application(uOS* uOS) : uOS_p(uOS){};

        APP_ID id = NONE;
    protected:
        uOS* uOS_p = nullptr;
    private:
        /**
         * @brief Function called when closing the application
         * 
         */
        virtual void onClose() = 0;
        /**
         * @brief Function called when resuming the application
         * 
         */
        virtual void onResume() = 0;
    };

};
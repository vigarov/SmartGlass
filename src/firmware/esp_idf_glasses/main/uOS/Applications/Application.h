#pragma once

#include "uOS.h"
#include <memory>

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
        Application(std::shared_ptr<uOS> uOS_p) : m_uOS(uOS_p){};

        APP_ID id = NONE;
    protected:
        std::shared_ptr<uOS> m_uOS;
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
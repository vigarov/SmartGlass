#pragma once

#include <memory>
#include "DisplayManager.h"

namespace SmartGlasses{

    enum APP_ID{
        NONE=-1,
        IDLE,
        //...
        NB_APPS
    };


    class uOS;//Forward declaration

    /**
     * @brief Base class for any application.
     * 
     */
    class Application{
    friend class ApplicationContainer;
    public:
        Application(std::shared_ptr<uOS> uOS_p);

        APP_ID id = NONE;
    protected:
        std::shared_ptr<uOS> m_uOS;
        std::shared_ptr<DisplayManager> m_displayManager;
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
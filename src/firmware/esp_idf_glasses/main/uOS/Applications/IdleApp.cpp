#include "IdleApp.h"
#include "Header.h"
#include "NavigationContainer.h"
#include "Navigation.h"
#include "utils.h"
#include "constants.h"
#include "NotificationContainer.h"
#include "ApplicationContainer.h"
#include "GlobalsManager.h"



using namespace SmartGlasses;

IdleApp::IdleApp(std::shared_ptr<uOS> uOS_p) : Application(uOS_p,IDLE){
    IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
    {
        auto tm = getCurrentTime();
        m_st = {tm->tm_hour,tm->tm_min};
    }
    std::string s = "Header";
   /*  m_displayables.push_back(std::make_shared<RawText>(s,false));
    m_displayables.push_back(std::make_shared<Battery>(88,false,(pixel_pair_t){100,0},0,3));
    //s = "arrowTop";
    //m_displayables.push_back(std::make_shared<StraightArrow>(s,true,(pixel_pair_t){36,0}));
    s = "arrowLeft";
    IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
    m_displayables.push_back(std::make_shared<LeftArrow>(s,true,(pixel_pair_t){36,15}));
    s = "500 M";
    m_displayables.push_back(std::make_shared<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>>(Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>::textWithDefaultFontFrom("500 m",true,{36,50},USE_ANIMATIONS,1)));
    //s = "arrowRight";*/
    //m_displayables.push_back(std::make_shared<RightArrow>(s,true,(pixel_pair_t){36,20}));
    std::string tempS = s+"Header";
    m_displayables.push_back(std::make_shared<Header>(tempS,m_st.hour,m_st.min));
    //navigation_t nav = {0,LEFT,400,10,30};
    //tempS = s+"NavCont";
    //m_displayables.push_back(std::make_shared<NavigationContainer>(tempS,nav));
    //s="Idle notif";
    //m_displayables.push_back(std::make_shared<NotificationContainer>(s,n,true,(pixel_pair_t){16,22}));
    IFD(heap_caps_print_heap_info(MALLOC_CAP_8BIT);)
    xSemaphoreGive(m_notifDisplaySemaphore);
}

void IdleApp::onClose(){
    ESP_LOGI(IDLE_M,"Closed application");
}

void IdleApp::onResume(){
    ESP_LOGI(IDLE_M,"Resuming application");
    update();
    //vTaskDelay(10000 / portTICK_PERIOD_MS);
    //std::string ns = "hello";
    //static_cast<Text<unsigned char,CHAR_WIDTH_8x8,NB_ASCII_CHARS>*>(m_displayables[m_displayables.size()-1].get())->changeString(ns);
}


void IdleApp::changeBLE(ble_status_t newStatus){
    ESP_LOGI(IDLE_M,"Got change request from %u,to%u",(unsigned int)m_ble_status,(unsigned int)newStatus);
    if(newStatus!=m_ble_status){
        if(newStatus == BLE_ADVERTISING){
            std::static_pointer_cast<Header>(m_displayables[HEADER_POS])->updateBLEBlink(true);
        }
        else{
            std::static_pointer_cast<Header>(m_displayables[HEADER_POS])->updateBLEBlink(false);
            if(newStatus == BLE_OFF){
                size_t i = HEADER_POS+1;
                DEVICEMANAGER.getOneSecondTimer()->removeTaskNotifiedOnAlarm(m_displayTimerTask);
                for(size_t i = 1;i<m_displayables.size();i++){
                    m_displayables[i]->hide();
                }
                m_displayables.erase(m_displayables.begin()+1,m_displayables.end());
            }
        }
        m_ble_status = newStatus;
    }
}

void IdleApp::run(){updateTime();}

void IdleApp::updateTime(){
    auto tm = getCurrentTime();
    simple_time_t st = {tm->tm_hour,tm->tm_min};
    if(st.hour!=m_st.hour){
        m_st.hour = st.hour;
    }
    else{
        st.hour=-1;
    }
    if(st.min!=m_st.min){
        m_st.min = st.min;
    }
    else{
        st.min=-1;
    }
    static_cast<Header*>(m_displayables[HEADER_POS].get())->updateTime(st);
     
}

void IdleApp::newNotification(notification_t n){
    while(xSemaphoreTake(m_notifDisplaySemaphore,30/portTICK_PERIOD_MS) != pdTRUE){
        ESP_LOGW(IDLE_M,"Couldn't take notification update semaphore after 30ms");
    }
    ESP_LOGI(IDLE_M,"Fetched semaphore, can now update notification. Current m_displayTimerTask=%p",m_displayTimerTask);
    m_secondsDisplayedCount = 0;
    if(m_displayTimerTask==nullptr){
        createTask(T_DISPLAY_COUNT,"DisplayUpdate Task",4096,UOS_TASK_PRIORITY+1,&m_displayTimerTask,APP_CPU,static_cast<void*>(this));
        DEVICEMANAGER.getOneSecondTimer()->addTaskNotifiedOnAlarm(m_displayTimerTask);
    }
    else{
        eraseDisplayableTask();
    }
    std::string s = "Idle Notif";
    auto disp = std::make_shared<NotificationContainer>(s,std::move(n),true,(pixel_pair_t){NOTIF_OFFSET_X,NOTIF_OFFSET_Y},false,2);
    m_displayables.push_back(disp);
    hideNavigationTask();
    disp->update();
    xSemaphoreGive(m_notifDisplaySemaphore);
}


void IdleApp::getNavigation(navigation_t newNavigation){
    eraseDisplayableTask();
    if(!m_createdNav){
        std::string temp = "Navigation Container";
        m_displayables.push_back(std::make_shared<NavigationContainer>(temp,newNavigation));
        m_createdNav = true;
    }
    updateAndShowNav(newNavigation);
}

void IdleApp::T_DISPLAY_COUNT(void* pvParameters){
    auto app = static_cast<IdleApp*>(pvParameters);
    while(1){
        if(ulTaskNotifyTake(pdTRUE,1200/portTICK_PERIOD_MS) == pdFALSE){
            ESP_LOGE(IDLE_M,"Did not receive 1 second notification after 1200 mseconds...");
        }
        xSemaphoreTake(app->m_notifDisplaySemaphore,0);

        if(++app->m_secondsDisplayedCount >= MAX_SECONDS_TEMP_DISPLAY){
            app->eraseDisplayableTask();
            app->showNavigationTask();
            app->m_secondsDisplayedCount = 0;
            DEVICEMANAGER.getOneSecondTimer()->removeTaskNotifiedOnAlarm(app->m_displayTimerTask);
            app->m_displayTimerTask = nullptr;
            xSemaphoreGive(app->m_notifDisplaySemaphore);
            vTaskDelete(NULL); //delete self == m_displayTimerTask
        }
        //xSemaphoreGive(app->m_notifDisplaySemaphore);
    }
}

void IdleApp::eraseDisplayableTask(){
    for(size_t i=0;i<m_displayables.size();i++){
        auto& displayable = m_displayables[i];
        if(displayable->id == NOTIFICATION_CONTAINER_ID){
            ESP_LOGI(IDLE_M,"Hiding and erasing");
            displayable->hide();
            m_displayables.erase(m_displayables.begin() + i);
        }
    }
}


void IdleApp::hideNavigationTask(){
    for(auto& displayable:m_displayables){
        if(displayable->id == NAVIGATION_CONTAINER_ID){
            ESP_LOGI(IDLE_M,"Hiding the nav");
            displayable->hide();
        }
    }
}

void IdleApp::showNavigationTask(){
    for(auto& displayable:m_displayables){
        if(displayable->id == NAVIGATION_CONTAINER_ID){
            ESP_LOGI(IDLE_M,"Updating the nav");
            displayable->update();
        }
    }
}


void IdleApp::updateAndShowNav(navigation_t n){
    for(auto& displayable:m_displayables){
        if(displayable->id == NAVIGATION_CONTAINER_ID){
            ESP_LOGI(IDLE_M,"Updating and showing");
            std::static_pointer_cast<NavigationContainer>(displayable)->changeNavigation(n);
            displayable->update();
        }
    }
}
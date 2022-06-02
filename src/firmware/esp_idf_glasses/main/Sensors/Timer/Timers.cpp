#include "Timers.h"
#include "esp_log.h"
#include "constants.h"
#include "utils.h"
#include <algorithm>

using namespace SmartGlasses;

template<timer_group_t GROUP, timer_idx_t ID>
Timer<GROUP,ID>::Timer(){
    ESP_LOGI(TIMER_M,"Creating Timer object: group %d, id %d ",GROUP,ID);
}

template<timer_group_t GROUP, timer_idx_t ID>
void Timer<GROUP,ID>::init(){
    ESP_LOGI(TIMER_M,"Prefer setup(..) for setting up a timer. Using default values ");
    setup(TIMER_AUTORELOAD_EN,ID==ONE_S_ID?1:60);
}

template<timer_group_t GROUP,timer_idx_t ID>
void Timer<GROUP,ID>::setup(timer_autoreload_t auto_reload, uint64_t timer_interval_sec){
    if(!m_setup){
        //Counting up untill reaching the alarm threshold
        timer_config_t config = {
            .alarm_en = TIMER_ALARM_EN,
            .counter_en = TIMER_PAUSE,
            .counter_dir = TIMER_COUNT_UP,
            .auto_reload = auto_reload,
            .divider = TIMER_DIVIDER
        }; // default clock source is APB
        timer_init(GROUP, ID, &config);

        /* Timer's counter will initially start from value below.
        Also, if auto_reload is set, this value will be automatically reload on alarm */
        timer_set_counter_value(GROUP, ID, RESTART_VALUE);

        /* Configure the alarm value and the interrupt on alarm. */
        setInterval(timer_interval_sec);
        timer_enable_intr(GROUP, ID);

        timer_isr_callback_add(GROUP, ID, alarmISR, this, 0);

        xSemaphoreGive(xSetSemaphore);
        m_setup = true;
    }
}

template<timer_group_t GROUP, timer_idx_t ID>
void Timer<GROUP,ID>::setInterval(uint64_t timer_interval_sec){
    ESP_LOGI(TIMER_M,"Setting interval to %llu",timer_interval_sec);
    m_currentInterval = timer_interval_sec * TIMER_SCALE;
    ESP_LOGI(TIMER_M, "which is %llu after scale", m_currentInterval);
    timer_set_alarm_value(GROUP, ID, m_currentInterval);
}


template<timer_group_t GROUP, timer_idx_t ID>
bool Timer<GROUP,ID>::alarmISR(void* pvParameters){
    Timer<GROUP,ID> *t = (Timer<GROUP,ID>*)pvParameters;
    BaseType_t xHigherPriorityTaskWoken = pdTRUE; //directly delegating to updater task
    vTaskNotifyGiveFromISR(t->m_updaterTask,&xHigherPriorityTaskWoken);
    return xHigherPriorityTaskWoken==pdTRUE;
}

template<timer_group_t GROUP, timer_idx_t ID>
void Timer<GROUP,ID>::T_NotifyAlarmSubscribers(void* pvParameters){
    Timer<GROUP,ID> *t = (Timer<GROUP,ID>*)pvParameters;
    //adding a, roughly, 10 percent margin of error (e.g.: other tasks currently running)
    //*1000 for milliseconts
    ESP_LOGI(TIMER_M,"Starting timer task");
    while(1){
        auto timeToWait = (t->m_currentInterval + ((6550*t->m_currentInterval+32768)>>16))*1000; 
        ESP_LOGI(TIMER_M,"Computed ttw=%llu",timeToWait);
        if(ulTaskNotifyTake(pdTRUE,timeToWait / portTICK_PERIOD_MS) == pdPASS){
            ESP_LOGI(TIMER_M,"Got notified (from ISR)");
            //Since we have come to this point from a direct context switch from the ISR,
            //it is definitely possible that a lower priority tak currently handled the semaphore
            //we must therefore take it in a "polling" fashion
            while(xSemaphoreTake(t->xSetSemaphore, 1 / portTICK_PERIOD_MS) != pdTRUE){
                ESP_LOGI(TIMER_M,"Didn't get set semaphore");
                vTaskDelay(5 / portTICK_PERIOD_MS);
            }
            //we have the semaphore, we can now update all tasks needing it
            for(auto &task : t->m_tasksToNotify){
                ESP_LOGI(TIMER_M,"Notifying task %p",task);
                xTaskNotifyGive(task);
            }
            xSemaphoreGive(t->xSetSemaphore);
        }else{
            ESP_LOGW(TIMER_M, "Wasn't notified for a timer event after %llu ms. This is normal if the interval has been changed in between (which should not have been done?)",timeToWait);
        }
    }
}

template<timer_group_t GROUP, timer_idx_t ID>
bool Timer<GROUP,ID>::addTaskNotifiedOnAlarm(TaskHandle_t handle){
    if(!m_setup){
        ESP_LOGE(TIMER_M,"Adding tasks before timer setup!");
        return false;
    }
    ESP_LOGI(TIMER_M,"Adding task %p to timer",handle);
    if(xSemaphoreTake(xSetSemaphore,50 / portTICK_RATE_MS) == pdTRUE){
        bool wasEmpty = m_tasksToNotify.empty();
        m_tasksToNotify.insert(handle);
        xSemaphoreGive(xSetSemaphore);
        if(wasEmpty){
            ESP_LOGI(TIMER_M,"and starting timer");
            createTask(T_NotifyAlarmSubscribers,"Subscriber Updater",4098,TIMER_TASK_UPDATER_PRIORITY,&m_updaterTask,APP_CPU,this);
            timer_set_counter_value(GROUP, ID, RESTART_VALUE);
            timer_start(GROUP,ID);
        }
        return true;
    }
    else{
        ESP_LOGW(TIMER_M, "Couldn't fetch semaphore to add task");
        return false;
    }
}

template<timer_group_t GROUP, timer_idx_t ID>
bool Timer<GROUP,ID>::removeTaskNotifiedOnAlarm(TaskHandle_t handle){
    if(!m_setup){
        ESP_LOGE(TIMER_M,"Removing tasks before timer setup!");
        return false;
    }
    if(m_tasksToNotify.empty()){
        ESP_LOGE(TIMER_M,"Removing tasks in empty set!");
        return false;
    }
    ESP_LOGI(TIMER_M,"Removing task %p to timer",handle);
    if(xSemaphoreTake(xSetSemaphore,50 / portTICK_RATE_MS) == pdTRUE){
        bool removed = m_tasksToNotify.erase(handle);
        bool isEmpty = m_tasksToNotify.empty();
        xSemaphoreGive(xSetSemaphore);
        if(removed && isEmpty){
            ESP_LOGI(TIMER_M,"and stopping timer");
            vTaskDelete(m_updaterTask);
            m_updaterTask = NULL;
            timer_pause(GROUP,ID);
        }
        return removed;
    }
    else{
        ESP_LOGW(TIMER_M, "Couldn't fetch semaphore to remove task");
        return false;
    }
}

template class Timer<SYSTEM_TIMER_GROUP,ONE_S_ID>;
template class Timer<SYSTEM_TIMER_GROUP,SIXTY_S_ID>;
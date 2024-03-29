#include "utils.h"
#include "esp_log.h"
#include <sys/time.h>
#include <time.h>

//using namespace SmartGlasses; Somehow linker doesn't find definition of createTask if it is not explicitely prefixed by the namespace...

int SmartGlasses::createTask(TaskFunction_t pvTaskCode, const char *const pcName, const uint32_t usStackDepth, UBaseType_t uxPriority, TaskHandle_t* out_task_handle, const BaseType_t xCoreID, void* const pvParameters){
    const char* debug_tag = "Task creation";

    #define PREFIX "Unable to create task "
    #define MID ", error: "
    #define TASK_ERROR_FMT  PREFIX "%s" MID "%d\n"

    int error = pdPASS;
    if((error = xTaskCreatePinnedToCore(pvTaskCode, pcName, usStackDepth, pvParameters, uxPriority, out_task_handle,xCoreID)) != pdPASS
        || out_task_handle == nullptr
    ){
        ESP_LOGE(debug_tag, TASK_ERROR_FMT, pcName,error);
    }
    return error;
}

template <auto Start, auto End, auto Inc, class F>
constexpr void SmartGlasses::constexpr_for(F&& f)
{
    if constexpr (Start < End)
    {
        f(std::integral_constant<decltype(Start), Start>());
        constexpr_for<Start + Inc, End, Inc>(f);
    }
}

void SmartGlasses::resetTime(){
    ESP_LOGI("Utils","Setting system time, using " __DATE__ " " __TIME__);
    setenv("TZ","Europe/Zurich",1);
    tzset();

    struct tm t;
    if(strptime(__DATE__ " " __TIME__,"%b %d %Y %H:%M:%S",&t) == NULL){
        ESP_LOGE("Utils Module", "Unable to convert date/time");
    }
    else {
        updateTime(&t);
    }
    ESP_LOGI("Utils","Successfully set system time");
}

void SmartGlasses::updateTime(struct tm* t){
    setenv("TZ","Europe/Zurich",1);
    tzset();
    time_t tt = mktime(t);
    struct timeval tv{tt,0};
    if(tt==-1 || settimeofday(&tv,NULL) == -1){
        ESP_LOGE("Utils Module", "Failed to set date/time");
    }
}

struct tm* SmartGlasses::getCurrentTime(){
    auto t = time(nullptr);
    return localtime(&t);
}

std::string SmartGlasses::timeToString(unsigned int timeUnit){
    std::string ret = std::to_string(timeUnit);
    if(timeUnit < 10) ret = "0"+ret;
    return ret;
}
std::string SmartGlasses::distanceToString(unsigned int dist){
    return std::to_string(dist) + "m";
}
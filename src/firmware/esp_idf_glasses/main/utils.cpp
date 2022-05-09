#include "utils.h"
#include "esp_log.h"

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
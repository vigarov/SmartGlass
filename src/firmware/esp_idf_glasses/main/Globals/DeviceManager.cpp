#include "DeviceManager.h"
#include "GlobalsManager.h"
#include "uOS.h"

using namespace SmartGlasses;

DeviceManager::DeviceManager(){
    m_allDevices[DISPLAY_IDX] = std::make_shared<DisplayManager>();
    m_allDevices[TIMER_1s_IDX] = std::make_shared<Timer<SYSTEM_TIMER_GROUP,ONE_S_ID>>();
    m_allDevices[TIMER_60s_IDX] = std::make_shared<Timer<SYSTEM_TIMER_GROUP,SIXTY_S_ID>>();
}

void DeviceManager::initAll(){
    for(auto& device: m_allDevices){
        device->init();
    }
    initButtons();
}

//see https://github.com/espressif/esp-idf/blob/31b7694551620522cc3fde0623321a38bfea762f/examples/peripherals/gpio/generic_gpio/main/gpio_example_main.c
void DeviceManager::initButtons(){
    gpio_config_t config = {};
    config.intr_type = GPIO_INTR_POSEDGE;
    //bit mask of the pins, use GPIO4/5 here
    config.pin_bit_mask = (1<<BUT_UP_PIN)|(1<<BUT_DOWN_PIN)|(1<<BUT_LEFT_BACK_PIN)|(1<<BUT_RIGHT_SELECT_PIN);
    //set as input mode
    config.mode = GPIO_MODE_INPUT;
    //enable pull-up mode
    config.pull_up_en = GPIO_PULLUP_ENABLE; //TODO: c.f. for pullup: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html
    gpio_config(&config);

    
    //install gpio isr service: no idea what that is honestly
    //and https://www.esp32.com/viewtopic.php?t=5468
    #define ESP_INTR_FLAG_DEFAULT 0
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    
    gpio_isr_handler_add(BUT_UP_PIN, button_pressed_ISR, (void*) BUT_UP_PIN);
    gpio_isr_handler_add(BUT_DOWN_PIN, button_pressed_ISR, (void*) BUT_DOWN_PIN);
    gpio_isr_handler_add(BUT_LEFT_BACK_PIN, button_pressed_ISR, (void*) BUT_LEFT_BACK_PIN);
    gpio_isr_handler_add(BUT_RIGHT_SELECT_PIN, button_pressed_ISR, (void*) BUT_RIGHT_SELECT_PIN);

    ESP_LOGI("Device Manager","Finished setting up interrupts");
}

void DeviceManager::button_pressed_ISR(void* arg){
    QueueHandle_t q = GLOBALSMANAGER.getUOS()->getButtonsQueue();
    uOSEvent e{BUTTON_PRESSED,arg};
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    xQueueSendToFrontFromISR( q, &e, &xHigherPriorityTaskWoken );

    if( xHigherPriorityTaskWoken )
    {
        portYIELD_FROM_ISR ();
    }
}

//Note: for the following getters, it would have beend much better/cleanlier/correct do dynamic_cast
//However, this leads to a compile error (see also https://arduino.stackexchange.com/questions/55157/dynamic-cast-not-permitted-with-fno-rtti)
//We therefore static cast (since we have filled m_allDevices, we are sure of the output data type and it OK)
std::shared_ptr<DisplayManager> DeviceManager::getDisplayManager(){
    return std::static_pointer_cast<DisplayManager>(m_allDevices[DISPLAY_IDX]);
}

std::shared_ptr<Timer<SYSTEM_TIMER_GROUP,ONE_S_ID>> DeviceManager::getOneSecondTimer(){
    return std::static_pointer_cast<Timer<SYSTEM_TIMER_GROUP,ONE_S_ID>>(m_allDevices[TIMER_1s_IDX]);
}
std::shared_ptr<Timer<SYSTEM_TIMER_GROUP,SIXTY_S_ID>> DeviceManager::getSixtySecondTimer(){
    return std::static_pointer_cast<Timer<SYSTEM_TIMER_GROUP,SIXTY_S_ID>>(m_allDevices[TIMER_60s_IDX]);
}


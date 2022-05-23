// this file is heavily adapted off of https://gist.github.com/arvidtp/d0ab689a5c2821a45c31103d7a3e256a
// the library used is here: https://github.com/jrowberg/i2cdevlib/tree/master
// the "motionapps" thing is mostly useful only if one cares about rotating the acceleration vector correctly.
// we just work off the magnitude of the aceleration because it means we save some power by not using the gyro, and more false positives but that's ok.

#include <memory>

#include "freertos/FreeRTOS.h"
#include <driver/gpio.h>
#include "esp_log.h"

#include "constants.h"
#include "utils.h"
#include "GlobalsManager.h"
#include "IMUstatemachine.h" // note: MotionApps is included here and does NOT come as a separately compilable .cpp

#define IMU_HANDLER_TASK_PRIORITY configMAX

namespace SmartGlasses
{
    const char* IMU_state_machine::module_name = "IMU_state_machine";

    void IMU_state_machine::handler_task(void* raw_arg) {
        std::shared_ptr<IMU_state_machine> imu_sm;
        GlobalsManager& glob_mgr = GlobalsManager::getInstance();
        imu_sm = glob_mgr.getDeviceManager().getIMU_state_machine();

        ESP_LOGI(IMU_state_machine::module_name, "task num is %u", uxTaskGetTaskNumber(GlobalsManager::getInstance().getTaskManager().getTaskHandle(T_IMU)));

        // goes to sleep and when either an interrupt or another task needs it he wakes up
        while (true) {
            //vTaskSuspend(NULL);
            //ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
            // once I'm here someone woke me

            if (imu_sm->irq_occurred) {
                imu_sm->irq_occurred = false;

                uint8_t mpuIntStatus = imu_sm->mpu.getIntStatus();
                ESP_LOGI(IMU_state_machine::module_name, "Read intstatus=%x", mpuIntStatus);

                bool motion_int_trig = mpuIntStatus & (1 << MPU6050_INTERRUPT_MOT_BIT);
                // motion detect occurred

                bool zero_mot_int_trig = mpuIntStatus & (1 << MPU6050_INTERRUPT_ZMOT_BIT);
                // zero motion int
                bool now_no_motion = mpuIntStatus & (1 << MPU6050_INTERRUPT_MOT_BIT);

                if (motion_int_trig) {
                    // got a granny event
                    motion_int_trig = true;
                    ESP_LOGI(IMU_state_machine::module_name, "fallen granny");
                    //imu_sm->switch_to_power_state(fall_alerting);
                } else if (zero_mot_int_trig) {
                    if (now_no_motion) {
                        // go to next sleep state
                        ESP_LOGI(IMU_state_machine::module_name, "got a motion-->no motion event");
                        if (imu_sm->curr_power_state == full_on) {
                            //imu_sm->switch_to_power_state(fall_alerting);
                        } else {
                            // this motion-->no motion should only come up during full-on state
                            // in all other states we should get a no motion-->motion
                            ESP_LOGE(IMU_state_machine::module_name, "got a %d", imu_sm->curr_power_state);
                        }
                    } else {
                        // wake from sleep
                        ESP_LOGI(IMU_state_machine::module_name, "got a no motion-->motion event");
                    }
                } else {
                    ESP_LOGI(IMU_state_machine::module_name, "unknown handler_task wakeup");
                }

                if (imu_sm->tnum!=(UBaseType_t)(-1)) {
                    ESP_LOGI(IMU_state_machine::module_name, "ISR found task num %u", imu_sm->tnum);
                }
            }
            vTaskDelay(5000/portTICK_PERIOD_MS);
        }
    }

    void IMU_state_machine::switch_to_power_state(imu_state_t new_state) {
        switch (new_state) {
            case full_on: // in terms of power this is the same to the prepare_sleep
            case full_on_prepare_sleep: {
                mpu.setSleepEnabled(false);
                mpu.setIntZeroMotionEnabled(true);
                mpu.setIntMotionEnabled(true);
                mpu.setWakeCycleEnabled(false);
                break;
            }
            case light_sleep: {
                mpu.setSleepEnabled(false);
                mpu.setIntZeroMotionEnabled(true);
                mpu.setIntMotionEnabled(false);
                mpu.setWakeCycleEnabled(true); // frequency will already have been set during startup
                // TODO: set up timer towards deep sleep
                break;
            }
            case deep_sleep: {
                mpu.setSleepEnabled(true);
                break;
            }
            default: break;
            // fall_alerting isn't a power state exactly
        }
        this->curr_power_state = new_state;
    }

    void IMU_state_machine::isr_handler(void *raw_arg)
    {
        IMU_state_machine *state_machine = (IMU_state_machine *)raw_arg;
        state_machine->irq_occurred = true;

        // wake up real handler, useful explanation: https://stackoverflow.com/a/54658072/5708421
        TaskHandle_t task = GlobalsManager::getInstance().getTaskManager().getTaskHandle(T_IMU);

        BaseType_t higher_priority_task_woken;
        vTaskNotifyGiveFromISR(&task, &higher_priority_task_woken);
        portYIELD_FROM_ISR(higher_priority_task_woken);
        // xTaskResumeFromISR(&task);

        // portYIELD_FROM_ISR();
    }

    void IMU_state_machine::init()
    {
        this->setup_i2c();
        this->setup_isr(PIN_IMU_INT);
        mpu.initialize();
        this->imu_connection_failed = !mpu.testConnection();
        if (this->imu_connection_failed)
        {
            ESP_LOGE(IMU_state_machine::module_name, "Failed IMU i2c connection test");
            return;
        }
        else
        {
            ESP_LOGI(IMU_state_machine::module_name, "IMU i2c connection test passed");
        }

        this->dmp_init_status = mpu.dmpInitialize();
        if (dmp_init_status == 0)
        {
            ESP_LOGI(IMU_state_machine::module_name, "IMU DMP initialisation succeeded");
        }
        else
        {
            ESP_LOGE(IMU_state_machine::module_name, "IMU DMP initialisation failed with code %d", this->dmp_init_status);
            return;
        }

        mpu.setDMPEnabled(true);

        delay(5000); // some time between starting the DMP and actually using it prevents weird quirks
        // also, the filters need a few seconds worth of samples to settle down anyway

        // below are calibrated using MPU6050_raw from the i2cdev library
        // also instructions here help: https://www.i2cdevlib.com/forums/topic/91-how-to-decide-gyro-and-accelerometer-offsett/?do=findComment&comment=257
        mpu.setXAccelOffset(-2730);
        mpu.setYAccelOffset(-35);
        mpu.setZAccelOffset(700);

        mpu.setMotionDetectionThreshold(7500);     // LSB=2mg
        mpu.setMotionDetectionDuration(2);         // so you get an interrupt when falling LSB=1ms
        mpu.setMotionDetectionCounterDecrement(2); // when a sample does not count as falling how much to penalise the counter for this

        mpu.setZeroMotionDetectionThreshold(7500); // LSB=2mg
        mpu.setZeroMotionDetectionDuration(255);   // maximum interval, get an int after 16320 ms.  LSB=64 ms

        // disable unused gyro with setStandbyXGyroEnabled(false) & Y&Z, register map says there's power optimisation like this
        mpu.setStandbyXGyroEnabled(false);
        mpu.setStandbyYGyroEnabled(false);
        mpu.setStandbyZGyroEnabled(false);

        mpu.setInterruptMode(0);                    // aka active high
        mpu.setInterruptLatch(1);                   // latch rather than pulse
        mpu.setInterruptLatchClear(0);              // so reading INT_STATUS clears the interrupt
        mpu.setIntDataReadyEnabled(false);          // in our case we are not interested in raw data so don't bother
        mpu.setIntFIFOBufferOverflowEnabled(false); // again, not reading raw data so this doesn't matter
        mpu.setTempSensorEnabled(false);            // unused and needs to be disabled for accelerator only low power mode

        mpu.setIntZeroMotionEnabled(false);
        mpu.setIntMotionEnabled(false);
        mpu.setIntFreefallEnabled(false);

        mpu.setWakeFrequency(0); // 0: 1.25 Hz, 1: 2.5 Hz, 2: 5 Hz, 3: 10 Hz
        this->switch_to_power_state(full_on);
    }

    void IMU_state_machine::setup_i2c()
    {
        // taken from https://github.com/jrowberg/i2cdevlib/blob/master/ESP32_ESP-IDF/main/example.cpp
        i2c_config_t conf;
        conf.mode = I2C_MODE_MASTER;
        conf.sda_io_num = PIN_SDA;
        conf.scl_io_num = PIN_SCL;
        conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
        conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
        conf.master.clk_speed = 400000; // this is the max frequency the mpu will support
        conf.clk_flags = 0; // requests no capabilities
        ESP_LOGW(IMU_state_machine::module_name, "pre i2c_param_config");
        ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &conf));
        ESP_LOGW(IMU_state_machine::module_name, "post i2c_param_config");
        ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0));
        ESP_LOGW(IMU_state_machine::module_name, "post i2c_driver_install");
    }

    void IMU_state_machine::setup_isr(gpio_num_t pin_number)
    {
        // mostly from https://github.com/nkolban/esp32-snippets/blob/master/gpio/interrupts/test_intr.c
        gpio_config_t gpioConfig;
        gpioConfig.pin_bit_mask = 1 << (int)pin_number;
        gpioConfig.mode = GPIO_MODE_INPUT;
        gpioConfig.pull_up_en = GPIO_PULLUP_DISABLE;
        gpioConfig.pull_down_en = GPIO_PULLDOWN_ENABLE;
        gpioConfig.intr_type = GPIO_INTR_POSEDGE;
        
        ESP_LOGW(IMU_state_machine::module_name, "pre gpio_config");
        gpio_config(&gpioConfig);

        ESP_LOGW(IMU_state_machine::module_name, "pre gpio_install_isr_service");
        gpio_install_isr_service(ESP_INTR_FLAG_EDGE | ESP_INTR_FLAG_LOWMED);    // lowmed is needed because otherwise you need to write assembly
        
        ESP_LOGW(IMU_state_machine::module_name, "pre gpio_isr_handler_add");
        gpio_isr_handler_add(pin_number, IMU_state_machine::isr_handler, this); // want to pass state machine so ISR can set attributes
        
        ESP_LOGW(IMU_state_machine::module_name, "post setup_isr");
    }

    IMU_state_machine::IMU_state_machine()
    {
        // mpu member will be default-constructed
        esp_log_level_set(IMU_state_machine::module_name, ESP_LOG_VERBOSE);
    }
}
#pragma once

#include <memory>

// #define __PGMSPACE_H_ // MotionApps file below looks for this instead of PGMSPACE_INCLUDE as defined in esp-idf
// #define F(x) x // do need to make minor fixes though like for disabling progmem
// #define DEBUG2 DEBUG
// #include "MPU6050_6Axis_MotionApps20.h"
// #define DEBUG DEBUG2
#include "MPU6050.h"

#include "Device.h"

namespace SmartGlasses
{
    
    enum imu_state_t {
        full_on,
        full_on_prepare_sleep,
        light_sleep,
        deep_sleep,
        fall_alerting
    };
    
    // this class is only ever supposed to be used by the imu manager
    // do NOT use this externally

    /*
    the IMU is very important in system power management, because it can switch
    program modes (states inspired from ACPI):
    S5 fully off (battery disconnected) --> run startup asap and switch to full on
    S4 deep sleep --> set IMU to sleep, button press irq triggers wake from eep sleep to full on
    S3 pickup detect sleep --> set to wake cycle, enable motion irq/bttn press to go to full on.  after say 10 min of zeromotion int switch to deep sleep
    S0 full on --> user-configurable IMU frequency, enable motion and zeromotion int.  after 30 s zeromotion int switch to S3.  on motion int trigger a BLE notify.  on user request switch to S4 directly
    */
    class IMU_state_machine : public Device
    {
    private:
        MPU6050 mpu;
        static const char* module_name;
        bool imu_connection_failed = false;
        uint8_t dmp_init_status = 0;
        imu_state_t curr_power_state = full_on;
        UBaseType_t tnum = -1;

        volatile bool irq_occurred = false;

        static void IRAM_ATTR isr_handler(void *raw_arg);
        void setup_isr(gpio_num_t pin_number);
        void setup_i2c();

    public:

        IMU_state_machine();
        void init();
        void switch_to_power_state(imu_state_t new_state);
        static void handler_task(void* imu_state_machine);
    };

}
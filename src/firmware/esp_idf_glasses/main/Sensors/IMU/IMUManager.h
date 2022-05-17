#pragma once

#include <memory>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "Device.h"

namespace SmartGlasses{

    #define IMU_M "IMU Manager Module"

    class IMUManager : public Device{
        friend class DeviceManager;
    private:
        Adafruit_MPU6050 mpu;

    public:
        IMUManager();
        void init() override;
// take interrupt code from https://gist.github.com/arvidtp/d0ab689a5c2821a45c31103d7a3e256a
        void get_latest_event(sensors_event_t *accel, sensors_event_t *gyro, sensors_event_t *temp);

        void debug_print_latest_event();
    };
};
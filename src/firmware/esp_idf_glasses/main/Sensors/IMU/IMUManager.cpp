#include "esp_log.h"

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include "IMUManager.h"
#include "utils.h"
#include "constants.h"

using namespace SmartGlasses;


IMUManager::IMUManager(){
    
}

void IMUManager::init() {
    esp_log_level_set(IMU_M, ESP_LOG_VERBOSE);
    if (!mpu.begin()) {
        ESP_LOGE(IMU_M, "failed IMU initialisation");
    } else {
        ESP_LOGI(IMU_M, "IMU found");
    }
}

void IMUManager::get_latest_event(sensors_event_t *accel, sensors_event_t *gyro, sensors_event_t *temp) {
    /* Get new sensor events with the readings */
    mpu.getEvent(accel, gyro, temp);
}

void IMUManager::debug_print_latest_event() {
    sensors_event_t a, g, temp;
    this->get_latest_event(&a,&g,&temp);
    /* Print out the values */
    ESP_LOGI(IMU_M, "Acceleration X: %f, Y: %f, Z: %f m/s^2\n", a.acceleration.x, a.acceleration.y, a.acceleration.z);

    ESP_LOGI(IMU_M, "Rotation X: %f, Y: %f, Z: %f rad/s\n", a.gyro.x, a.gyro.y, a.gyro.z);

    ESP_LOGI(IMU_M, "Temperature: %f C\n", temp.temperature);
}
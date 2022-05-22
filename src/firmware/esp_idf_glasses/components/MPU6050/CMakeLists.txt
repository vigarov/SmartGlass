idf_component_register(SRCS "MPU6050.cpp" "MPU6050_6Axis_MotionApps20.cpp"
                       INCLUDE_DIRS "."
                       REQUIRES I2Cdev
)
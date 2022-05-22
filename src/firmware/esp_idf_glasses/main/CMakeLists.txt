
#set(COMPONENT_SRCS "glasses_utils.cpp" "glasses_location.cpp" "glasses_toplevel_tasks.cpp" "glasses_globals_manager.cpp" "glasses_display.cpp" "main.cpp")
#set(COMPONENT_ADD_INCLUDEDIRS "")
#set(COMPONENT_REQUIRES )
#set(COMPONENT_PRIV_REQUIRES )
#set(SOURCES "glasses_utils.cpp" "glasses_location.cpp" "glasses_toplevel_tasks.cpp" "glasses_globals_manager.cpp" "glasses_display.cpp" "main.cpp")

set(BLE_DIR BLE)
set(BLE_SRCS ${BLE_DIR}/BLEHandler.cpp)
set(BLE_CALLBACKS_DIR ${BLE_DIR}/callbacks)
set(BLE_DIRS
    ${BLE_DIR}
    ${BLE_CALLBACKS_DIR}
)

set(UOS_DIR uOS)
set(UOS_SRCS 
    ${UOS_DIR}/uOS.cpp
)

set(APP_DIR ${UOS_DIR}/Applications)
set(APP_SRCS 
    ${APP_DIR}/Application.cpp
    ${APP_DIR}/ApplicationContainer.cpp
    ${APP_DIR}/IdleApp.cpp)

set(DISPLAY_DIR Display)
set(FONTS_DIR 
    ${DISPLAY_DIR}/fonts)
set(OBJECTS_DIR ${DISPLAY_DIR}/Objects)

set(SENSORS_DIR Sensors)
#set(GNSS_DIR ${SENSORS_DIR}/GNSS)
set(IMM_O_D ${OBJECTS_DIR}/Immutable)
set(IMU_DIR ${SENSORS_DIR}/IMU)
set(IMM_O_D_SRCS 
    ${IMM_O_D}/RawText.cpp)
set(M_O_D ${OBJECTS_DIR}/Mutable)
set(M_O_D_SRCS 
    ${M_O_D}/BLEIcon.cpp)
set(OBJECTS_DIRS 
    ${OBJECT_DIR}
    ${IMM_O_D}
    ${M_O_D})
set(DISPLAY_DIRS
    ${DISPLAY_DIR}
    ${FONTS_DIR}
    ${OBJECTS_DIRS}
    )
set(IMU_DIRS
    ${IMU_DIR}
    )
#set(GNSS_DIRS
#    ${GNSS_DIR}
#    )
set(FONTS_SRC
    ${FONTS_DIR}/font.cpp)
set(OBJECTS_SRC
    ${IMM_O_D_SRCS}
    ${M_O_D_SRCS})
set(DISPLAY_SRCS 
    ${DISPLAY_DIR}/DisplayManager.cpp
    ${DISPLAY_DIR}/Content.cpp
    ${FONTS_SRC}
    ${OBJECTS_SRC}
    )
set(IMU_SRCS
    ${IMU_DIR}/IMUManager.cpp
    )
    )
#set(GNSS_SRCS
#    ${GNSS_DIR}/GNSSManager.cpp
#    )

set(TIMER_DIR ${SENSORS_DIR}/Timer)
set(TIMER_SRCS ${TIMER_DIR}/Timers.cpp)
set(SENSORS_DIRS
    ${SENSORS_DIR}
#    ${GNSS_DIR}  
    ${TIMER_DIR}  
)
set(SENSOR_SRCS 
#    ${GNSS_SRCS}
    ${IMU_SRCS}
    ${TIMER_SRCS}
)

set(GLOBALS_DIR Globals)
set(GLOBALS_SRCS 
    ${GLOBALS_DIR}/GlobalsManager.cpp
    ${GLOBALS_DIR}/DeviceManager.cpp
    ${GLOBALS_DIR}/TaskManager.cpp
)

set(OTHER_SRCS
    utils.cpp
    main.cpp
)

set(INCLUDES 
    .
    ${BLE_DIRS}
    ${UOS_DIR}
    ${APP_DIR}
    ${DISPLAY_DIRS}
    ${IMU_DIRS}
#    ${GNSS_DIRS}
    ${GLOBALS_DIR}
    ${SENSORS_DIRS}    
)

set(ALL_SRCS 
    ${BLE_SRCS}
    ${UOS_SRCS}
    ${APP_SRCS}
    ${SENSOR_SRCS}
    ${DISPLAY_SRCS}  
    ${GLOBALS_SRCS}
    ${OTHER_SRCS}
)

set(SOURCES ${ALL_SRCS})
set(COMPONENT_ADD_INCLUDEDIRS ${INCLUDES})
set(COMPONENT_ADD_INCLUDEDIRS "")
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

idf_component_register(SRCS ${ALL_SRCS}
                    INCLUDE_DIRS ${INCLUDES})

set(COMPONENT_SRCS "glasses_utils.cpp" "glasses_location.cpp" "glasses_toplevel_tasks.cpp" "glasses_globals_manager.cpp" "glasses_display.cpp" "main.cpp")
set(COMPONENT_ADD_INCLUDEDIRS "")
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )
set(SOURCES "glasses_utils.cpp" "glasses_location.cpp" "glasses_toplevel_tasks.cpp" "glasses_globals_manager.cpp" "glasses_display.cpp" "main.cpp")
idf_component_register(SRCS ${COMPONENT_SRCS}
                    INCLUDE_DIRS ".")
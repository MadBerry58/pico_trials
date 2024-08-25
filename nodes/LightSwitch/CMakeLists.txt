add_subdirectory(lightSwitchSM)

add_executable(LightSwitch 
    LightSwitch_Node.c
    LightSwitch_config.h
    LightSwitch_CanIf.h
    LightSwitch_CanIf.c
    )

target_link_libraries(LightSwitch PUBLIC
    pico_stdlib
    pico_multicore
    lightSwitchSM_lib
)
add_subdirectory(lightController)

add_executable(LightController
    LightController_config.h
    LightController_Node.c
    LightController_CanIf.c
    LightController_CanIf.h
    )

target_link_libraries(LightController PUBLIC
    lightController_lib
    pico_stdlib
    pico_multicore
)
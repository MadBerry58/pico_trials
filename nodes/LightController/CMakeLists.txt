add_subdirectory(lightController)

add_executable(LightController
    LightController_config.h
    LightController_Node.c
    )

target_link_libraries(LightController PUBLIC
    lightController_lib
    pico_stdlib
    pico_multicore
)
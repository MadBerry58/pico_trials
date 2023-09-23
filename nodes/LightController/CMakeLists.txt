add_subdirectory(lightControllerSM)

add_executable(LightController
    LightController_config.h
    LightController_Node.c
    )

target_link_libraries(LightController PUBLIC
    lightControllerSM_lib
    pico_stdlib
    pico_multicore
)
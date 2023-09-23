add_subdirectory(radiatorControllerSM)

add_executable(RadiatorController
    RadiatorController_Node.c
    )

target_link_libraries(RadiatorController PUBLIC
    pico_stdlib
    pico_multicore
    radiatorControllerSM_lib
)
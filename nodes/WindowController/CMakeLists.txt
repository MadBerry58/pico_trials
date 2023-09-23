add_subdirectory(windowControllerSM)

add_executable(WindowController
    WindowController_Node.c
    )

target_link_libraries(WindowController PUBLIC
    pico_stdlib
    pico_multicore
    windowControllerSM_lib
)
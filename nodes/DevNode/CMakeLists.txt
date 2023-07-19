add_subdirectory(devSM)

add_executable(devNode devNode.c)

target_link_libraries(devNode PUBLIC
    picoOS
    devSM_lib
)
add_subdirectory(devSM)

add_executable(devNode devNode.c)

target_link_libraries(devNode
    devSM_lib
)
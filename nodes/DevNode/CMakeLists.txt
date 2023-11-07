add_subdirectory(devSM)

add_executable(devNode 
    dev_config.h
    dev_Node.c
)

target_link_libraries(devNode PUBLIC
    devSM_lib
)

pico_add_extra_outputs(devNode)
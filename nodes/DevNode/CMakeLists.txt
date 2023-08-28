add_subdirectory(devSM)

add_executable(devNode 
    devNode.c
)

target_link_libraries(devNode PUBLIC
    pico_stdlib
    pico_multicore
    
    devSM_lib
)

pico_add_extra_outputs(devNode)
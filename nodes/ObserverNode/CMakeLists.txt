add_subdirectory(ObserverSM)

add_executable(ObserverNode 
    Observer_config.h
    Observer_Node.c
)

target_link_libraries(ObserverNode PUBLIC
    pico_stdlib
    pico_multicore
    
    ObserverSM_lib
)

pico_add_extra_outputs(ObserverNode)
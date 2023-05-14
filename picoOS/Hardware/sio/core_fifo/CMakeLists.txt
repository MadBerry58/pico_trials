add_library(core_fifo
    core_fifo.h
    core_fifo.c
)

target_link_libraries(core_fifo PUBLIC
    pico_stdlib 
)
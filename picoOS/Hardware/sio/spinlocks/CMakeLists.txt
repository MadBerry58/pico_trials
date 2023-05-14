add_library(spinlocks
    spinlocks.h
    spinlocks.c
)

target_link_libraries(spinlocks PUBLIC
    pico_stdlib 
)
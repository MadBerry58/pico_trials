add_library(divider
    divider.h
    divider.c
)

target_link_libraries(divider PUBLIC
    pico_stdlib 
    hardware_divider
)
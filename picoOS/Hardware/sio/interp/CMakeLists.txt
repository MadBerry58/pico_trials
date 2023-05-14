add_library(interp
    interpolators.h
    interpolators.c
)

target_link_libraries(interp PUBLIC
    pico_stdlib 
    hardware_interp
)
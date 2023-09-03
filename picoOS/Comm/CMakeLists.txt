add_library(CommLibrary 
    Comm.h
    Comm.c
    Adresses.h
)

target_link_libraries(CommLibrary PUBLIC 
    pico_stdlib
    hardware_irq
    pio_can
    )
add_library(IRQLibrary 
    interruptHandler.h
    interruptHandler.c
)

target_link_libraries(IRQLibrary PUBLIC 
    pico_stdlib
    hardware_irq
)
add_library(Hardware_irqLibrary
    interrupts.c
    interrupts.h
)

target_link_libraries(Hardware_irqLibrary PUBLIC
    pico_stdlib 
    hardware_irq
)
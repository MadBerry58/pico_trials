add_library(CommLibrary 
    Comm.h
    Comm.c
    commSM/commSM.h
    commSM/commSM.c
    commSM/commSM_functionality.h
    commSM/commSM_functionality.c
    osNetwork_Messages.h
    osInternal_Messages.h
)

target_link_libraries(CommLibrary PUBLIC 
    pico_stdlib
    hardware_irq
    hardware_spi
    hardware_dma
    pio_can
    )
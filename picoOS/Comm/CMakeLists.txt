add_library(CommLibrary 
    Comm.h
    Comm.c
    IPC/ipc.h
    IPC/ipc.c
    CAN/CAN_SM_APIs.h
    CAN/CAN_SM_APIs.c
    CAN/CAN_SM.h
    CAN/CAN_SM.c
)

target_link_libraries(CommLibrary PUBLIC 
    pico_stdlib
    hardware_irq
    hardware_spi
    hardware_dma
    pio_can
    )
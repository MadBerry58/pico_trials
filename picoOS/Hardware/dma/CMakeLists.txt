add_library(Hardware_dmaLibrary
    dma.h
    dma.c
    dma_configs.h
)

target_link_libraries(Hardware_dmaLibrary PUBLIC
    pico_stdlib 
    hardware_dma
)
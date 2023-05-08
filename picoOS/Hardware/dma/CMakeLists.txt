add_library(Hardware_dmaLibrary
    dma.c
    dma.h
    dma_configs.h
)

target_link_libraries(Hardware_dmaLibrary PUBLIC_HEADER
    pico_stdlib 
    hardware_dma
)
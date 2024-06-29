add_library(spi_can
        MCP2515_can.c
        MCP2515_can.h
        icDefinitions.h
        canDefinitions.h
)

target_link_libraries(spi_can PUBLIC
        pico_stdlib
        hardware_spi
        hardware_dma
)


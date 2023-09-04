add_library(spi_can
        icDefinitions.h
        canDefinitions.h
        MCP2515_can.c
        MCP2515_can.h
)

target_link_libraries(spi_can PUBLIC
        pico_stdlib 
        hardware_spi
)


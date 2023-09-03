add_library(spi_can
        canDefinitions.h
        MC2515_can.c
        MC2515_can.h
)

target_link_libraries(spi_can PUBLIC
        pico_stdlib 
        hardware_spi
)


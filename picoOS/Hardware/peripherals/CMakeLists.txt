add_subdirectory(spi_drivers)

add_library(PeripheralsLibrary
    peripherals.c
    peripherals.h
)

target_link_libraries(PeripheralsLibrary PUBLIC
    pico_stdlib 
    SPI_DriversLibrary
)
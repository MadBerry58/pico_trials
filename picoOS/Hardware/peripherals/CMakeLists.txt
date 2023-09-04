add_subdirectory(spi_drivers)

add_library(Hardware_peripheralsLibrary
    peripherals.c
    peripherals.h
)

target_link_libraries(Hardware_peripheralsLibrary PUBLIC
    pico_stdlib 
    SPI_DriversLibrary
)
add_subdirectory(MCP2515_can)

add_library(SPI_DriversLibrary
    spi_drivers.c
    spi_drivers.h
)

target_link_libraries(SPI_DriversLibrary PUBLIC
    spi_can
)
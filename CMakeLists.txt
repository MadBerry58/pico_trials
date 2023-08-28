cmake_minimum_required(VERSION 3.13)
# Enable debug symbols
set(CMAKE_BUILD_TYPE Debug)
set(DCMAKE_C_FLAGS "-Og -g3")
set(DPICO_DEOPTIMIZED_DEBUG 1)

include(pico_sdk_import.cmake)
# include(pico_extras_import_optional.cmake)

project(Pico_Trials C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_USE_STACK_GUARDS 1)

pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        )

message("Build type is ${CMAKE_BUILD_TYPE}")
if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        if (PICO_DEOPTIMIZED_DEBUG)
        message("Using fully de-optimized debug build (set PICO_DEOPTIMIZED_DEBUG=0 to optimize)")
        else()
        message("Using regular optimized debug build (set PICO_DEOPTIMIZED_DEBUG=1 to de-optimize)")
        endif()
endif()

add_subdirectory(picoOS)
add_subdirectory(nodes)

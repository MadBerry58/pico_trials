add_library(ErrorLibrary
    ErrorCodes.h
    ErrorHandling.h
    ErrorHandling.c
)

target_link_libraries(ErrorLibrary PUBLIC 
    pico_stdlib 
)
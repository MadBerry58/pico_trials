add_subdirectory(external)
add_subdirectory(internal)

add_library(CommLibrary 
    Comm.h
    Comm.c
    Adresses.h
)

target_include_directories(CommLibrary PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/external
    ${CMAKE_CURRENT_SOURCE_DIR}/internal
    )
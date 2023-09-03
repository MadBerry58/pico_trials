add_subdirectory(mosfetControl)

add_library(TemplateLibrary
    Templates.h
    Templates.c
)

target_link_libraries(TemplateLibrary PUBLIC
    MosfetControlLibrary
)
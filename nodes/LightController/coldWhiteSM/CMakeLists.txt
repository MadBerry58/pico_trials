add_library(coldWhiteSM_lib
    coldWhiteSM.h
    coldWhiteSM.c
)

target_link_libraries(coldWhiteSM_lib PUBLIC
    picoOS
    )
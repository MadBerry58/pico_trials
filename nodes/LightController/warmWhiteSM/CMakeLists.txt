add_library(warmWhiteSM_lib
    warmWhiteSM.h
    warmWhiteSM.c
)

target_link_libraries(warmWhiteSM_lib PUBLIC
    picoOS
    )
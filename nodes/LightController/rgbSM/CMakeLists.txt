add_library(rgbSM_lib
    rgbSM.h
    rgbSM.c
)

target_link_libraries(rgbSM_lib PUBLIC
    picoOS
    )
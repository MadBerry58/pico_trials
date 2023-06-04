add_library(devSM_lib
    devSM.h
    devSM.c
)

target_link_libraries(devSM_lib
    picoOS
)
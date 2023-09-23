add_library(lightControllerSM_lib
    lightControllerSM.h
    lightControllerSM.c
    # configuration.h

    nodeSWC/controlLogic/controlLogic.h
    nodeSWC/controlLogic/controlLogic.c

    nodeSWC/ledSM/ledSM.h
    nodeSWC/ledSM/ledSM.c

    nodeSWC/rgbSM/rgbSM.h
    nodeSWC/rgbSM/rgbSM.c
)

target_link_libraries(lightControllerSM_lib PUBLIC
    picoOS
)
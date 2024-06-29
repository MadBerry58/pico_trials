add_library(lightController_lib
    lightController.h
    lightController.c
    lightController_data.h
    # configuration.h

    nodeSWC/controlLogic/controlLogic.h
    nodeSWC/controlLogic/controlLogic.c

    nodeSWC/warmLedSM/warmLedSM.h
    nodeSWC/warmLedSM/warmLedSM.c

    nodeSWC/coldLedSM/coldLedSM.h
    nodeSWC/coldLedSM/coldLedSM.c

    nodeSWC/rgbSM/rgbSM.h
    nodeSWC/rgbSM/rgbSM.c
)

target_link_libraries(lightController_lib PUBLIC
    picoOS
)
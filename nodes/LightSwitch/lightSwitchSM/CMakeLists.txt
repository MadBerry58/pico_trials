add_library(lightSwitchSM_lib
    lightSwitchSM.h
    lightSwitchSM.c
    # configuration.h

    nodeSWC/controlLogic/controlLogic.h
    nodeSWC/controlLogic/controlLogic.c

    nodeSWC/encoderSM/encoderSM.h
    nodeSWC/encoderSM/encoderSM.c

    nodeSWC/rgbSM/rgbSM.h
    nodeSWC/rgbSM/rgbSM.c
)

target_link_libraries(lightSwitchSM_lib PUBLIC
    picoOS
)
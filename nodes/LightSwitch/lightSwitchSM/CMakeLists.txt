add_library(lightSwitchSM_lib
    lightSwitchSM.h
    lightSwitchSM.c
    lightSwitch_data.h

    nodeSWC/controlLogic/controlLogic.h
    nodeSWC/controlLogic/controlLogic.c

    nodeSWC/encoderSM/encoderSM.h
    nodeSWC/encoderSM/encoderSM.c

    nodeSWC/pushButtonSM/pushButtonSM.h
    nodeSWC/pushButtonSM/pushButtonSM.c
)

target_link_libraries(lightSwitchSM_lib PUBLIC
    picoOS
)
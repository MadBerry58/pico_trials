#include "controlLogic.h"

#include "../../lightController_data.h"

#include "../warmLedSM/warmLedSM.h"
#include "../coldLedSM/coldLedSM.h"
#include "../rgbSM/rgbSM.h"

#include <stdio.h>

extern struct lightParameters_Rx_Frame_t lightParameters_Rx_Frame;
extern struct lightParameters_Tx_Frame_t lightParameters_Tx_Frame;
extern                           uint8_t current_rgbPatternIndex;
extern                           uint8_t current_warmWhiteIntensity;
extern                           uint8_t current_coldWhiteIntensity;

void controlLogic_Init()
{
    /* Initialize local containers */
}

void reportError()
{
    /* Temporary placeholder */
}

void controlLogic_Run()
{
    if(current_rgbPatternIndex != 
        lightParameters_Rx_Frame.lightParameters.rgb_pattern_index)
    {
        rgmSM_Update();

        /* Check if the SM state updated */
        if(current_rgbPatternIndex != 
            lightParameters_Rx_Frame.lightParameters.rgb_pattern_index)
        {
            reportError();
        }
    }

    if(current_warmWhiteIntensity != 
        lightParameters_Rx_Frame.lightParameters.warmWhite_intensity)
    {
        warmLedSM_Update();

        /* Check if the SM state updated */
        if(current_warmWhiteIntensity != 
            lightParameters_Rx_Frame.lightParameters.warmWhite_intensity)
        {
            reportError();
        }
    }

    if(current_coldWhiteIntensity != 
        lightParameters_Rx_Frame.lightParameters.coldWhite_intensity)
    {
        coldLedSM_Update();

        /* Check if the SM state updated */
        if(current_coldWhiteIntensity != 
            lightParameters_Rx_Frame.lightParameters.coldWhite_intensity)
        {
            reportError();
        }
    }
}
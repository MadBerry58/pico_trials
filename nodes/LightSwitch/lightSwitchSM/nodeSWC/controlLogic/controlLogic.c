#include "controlLogic.h"
#include "../../../LightSwitch_config.h"

#define DEFAULT_PRESS_NO    2
#define NEXT_MODE_PRESS_NO  2

extern uint8_t white_color;
extern uint8_t white_intensity;

extern uint8_t press_number;
extern uint8_t encoder_position;
extern uint8_t press_time;
extern bool    userInputAvailable;

uint8_t encoder_position_old;

/* Local types */
enum LightState_e
{
    OFF,
    WHITE,
    WHITE_RGB,
    RGB,

    SUBMENU,

    NO_OF_STATES,
} LightState;

enum InputType_e
{
    NONE,
    PRESS_SHORT,
    PRESS_LONG,
    PRESS_MULTI,
    ROTATE,
    NO_OF_INPUTS
} InputType;

enum SubMenu_e
{
    WHITE_TEMPERATURE,
    
};

/* State machine functionality */
uint8_t controlLogic_lightSwitchSM_init()
{
    uint8_t retVal = 0;
    /* Check if all the SWC are initialized */
    return retVal;
}

uint8_t controlLogic_lightSwitchSM_run()
{
    /* Logic inferance functionality */
    uint8_t retVal = 0;
    if(userInputAvailable)
    {
        // getInputType();

        switch(LightState)
        {
            case OFF: /* Lights are off */
            {
                switch(InputType)
                {
                    case NONE:
                        /* No action */
                    break;

                    case PRESS_SHORT:
                        // turnOn();
                    break;

                    case PRESS_LONG:
                        /* Unimplemented */
                    break;

                    case PRESS_MULTI:
                        switch(press_number)
                        {
                            case DEFAULT_PRESS_NO:
                                // turnOn_default();
                            break;

                            default:
                                /* Unimplemented */
                        }
                    break;

                    case ROTATE:
                        /* Unimplemented */
                    break;

                    default:
                        /* Unimplemented */
                }
            }
            break;

            case WHITE:
            {
                switch(InputType)
                {
                    case NONE:
                        /* No action */
                    break;

                    case PRESS_SHORT:
                        // turnOff();
                    break;

                    case PRESS_LONG:
                        // submenu_whiteTemperature();
                    break;

                    case PRESS_MULTI:
                        switch(press_number)
                        {
                            case NEXT_MODE_PRESS_NO:
                                LightState = WHITE_RGB;
                            break;

                            default:
                                /* Unimplemented */
                        }
                    break;

                    case ROTATE:
                        // change_whiteIntensity();
                        LightState = WHITE;
                    break;

                    default:
                        /* Unimplemented */
                }
            }
            break;

            case WHITE_RGB:
            {
                switch(InputType)
                {
                    case NONE:
                        /* No action */
                    break;

                    case PRESS_SHORT:
                        // turnOff();
                    break;

                    case PRESS_LONG:
                        /* Unimplemented */
                    break;

                    case PRESS_MULTI:
                        switch(press_number)
                        {
                            case NEXT_MODE_PRESS_NO:
                                LightState = RGB;
                            break;

                            default:
                                /* Unimplemented */
                        }
                    break;

                    case ROTATE:
                        /* Unimplemented */
                    break;

                    default:
                        /* Unimplemented */
                }
            }
            break;

            case RGB:
            {
                switch(InputType)
                {
                    case NONE:
                        /* No action */
                    break;

                    case PRESS_SHORT:
                        // turnOff();
                    break;

                    case PRESS_LONG:
                        // submenu_whiteTemperature();
                    break;

                    case PRESS_MULTI:
                        switch(press_number)
                        {
                            case NEXT_MODE_PRESS_NO:
                                LightState = WHITE;
                            break;

                            default:
                                /* Unimplemented */
                        }
                    break;

                    case ROTATE:
                        // change_rgbIntensity();
                        LightState = RGB;
                    break;

                    default:
                        /* Unimplemented */
                }
            }
            break;

            case SUBMENU:

            break;

            default:
                
        }
    }

    return retVal;
}
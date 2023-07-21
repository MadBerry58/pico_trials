#include "RGBws2812SM.h"
#include "RGBws2812_Internal.h"

RGBws2812_SM_State SM_state = rgbSM_UNININIALISED;
bool SM_loop_control = false;
//rgb_error = none;

uint8_t RGBws2812SM_init()
{
    //Bind RGB control pin
}

uint8_t RGBws2812SM_run()
{
    while(SM_loop_control)
    {
        switch (SM_state)
        {
            case rgbSM_UNININIALISED:
                //rgb_error = NOT_INITIALIZED;
            break;
            
            case rgbSM_INITIALISED:
                if(){

                }
                else
                if()
                {

                }
                else
                if()
                {

                }
                else
                {

                }
            break;

            case rgbSM_IDLE:
                if(update_staticPattern())
                {

                }
                else
                if (update_dynamicPattern())
                {
                    
                }
                else
                {

                }
            break;

            case rgbSM_UPDATE_DYNAMIC_PATTERN:
                

            default:
                break;
            }
        }
}
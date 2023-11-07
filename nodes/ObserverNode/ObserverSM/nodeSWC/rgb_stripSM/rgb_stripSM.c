#include "rgb_stripSM.h"
#include "../../../Observer_config.h"

/**
 * @brief 
 * 
 */
ws2812_sm ws2812SM = {
    .smID               = 1,
    .pin                = RGB_RING_PIN,
    .patternLocation    = NULL,
    .notificationFlag   = SM_WS2812_N_NONE,
    .sm_state           = SM_WS2812_UNINIT,
    .sm_request         = SM_WS2812_R_NONE
};

uint8_t rgb_stripSM_init()
{
  uint8_t retVal = 0u;
  if(SM_WS2812_E_OK       != init_ws2812(&ws2812SM))
  {
    printf("RGB PIO init error %d\n", retVal);
    retVal = 1u;
  }
  else
  {
    printf("RGB PIO init ok %d\n", retVal);
    retVal = 0u;
  }

  return retVal;
}

uint8_t rgb_stripSM_run()
{
  bool    loopControl = false;
  uint8_t retVal      = SM_WS2812_E_OK;

  do{
    switch (ws2812SM.sm_state)
    {
      case SM_WS2812_UNINIT: /* SM not initialized. return fault */
        retVal = SM_WS2812_E_UNINITIALIZED;
      break;

      case SM_WS2812_STATIC:
      /* if(pattern_dynamic) */
        ws2812_loadPattern(
          ws2812SM.smID, 
          ws2812SM.patternLocation->patternList[ws2812SM.currentPatternIndex], 
          ws2812SM.patternLocation->patternSize
        );
        /* else 
            do_nothing
        */
        break;
    
    case SM_WS2812_STOPPED:
        /* Stop SM */
        if(SM_WS2812_R_NONE != ws2812SM.sm_request)
        {
          switch(ws2812SM.sm_request)
          {
            case SM_WS2812_R_RESET:
              ws2812SM.sm_state         = SM_WS2812_UNINIT;
              loopControl      = false;
            break;

            case SM_WS2812_R_STOP:
              ws2812SM.notificationFlag = SM_WS2812_N_LOW_PRIO_ERROR;
              ws2812SM.sm_state         = SM_WS2812_STOPPED;
              loopControl      = false;
              retVal                    = SM_WS2812_E_REQUEST_SEQUENCE;
            break;
            
            default:
              ws2812SM.sm_state         = SM_WS2812_STOPPED;
              loopControl      = false;
              ws2812SM.notificationFlag = SM_WS2812_N_MEDIUM_PRIO_ERROR;
              retVal                    = SM_WS2812_E_UNKNOWN_REQUEST;
            break;
          }
          /* Clear out host request */
          ws2812SM.sm_request     = SM_WS2812_R_NONE;
        }
        else
        {
            /* SM remains stopped */
            ws2812SM.sm_state     = SM_WS2812_STOPPED;
            loopControl  = false;
            retVal                = SM_WS2812_E_OK;
        }
        break;

    case SM_WS2812_FAULT:
        /* return error message */
        if(SM_WS2812_R_NONE != ws2812SM.sm_request)
        {
          switch(ws2812SM.sm_request)
              {
                case SM_WS2812_R_RESET:
                  ws2812SM.sm_state         = SM_WS2812_UNINIT;
                  loopControl      = false;
                break;

                case SM_WS2812_R_STOP:
                  ws2812SM.sm_state         = SM_WS2812_FAULT;
                  loopControl      = false;
                  ws2812SM.notificationFlag = SM_WS2812_N_LOW_PRIO_ERROR;
                  retVal                    = SM_WS2812_E_REQUEST_SEQUENCE;
                break;
                
                default:
                  ws2812SM.sm_state         = SM_WS2812_STOPPED;
                  loopControl      = false;
                  ws2812SM.notificationFlag = SM_WS2812_N_MEDIUM_PRIO_ERROR;
                  retVal                    = SM_WS2812_E_UNKNOWN_REQUEST;
                break;
              }
        }
        else
        {
          ws2812SM.sm_state         = SM_WS2812_FAULT;
          loopControl      = false;
          ws2812SM.notificationFlag = SM_WS2812_N_LOW_PRIO_ERROR;
          retVal                    = SM_WS2812_E_FAULT_NOT_RESOLVED;            
        }
        break;

    default:
      /* Unknown request  */
      loopControl      = false;
      ws2812SM.notificationFlag = SM_WS2812_N_HIGH_PRIO_ERROR;
      ws2812SM.sm_state         = SM_WS2812_FAULT;
      retVal                    = SM_WS2812_E_UNKNOWN_STATE;
    break;

    }

  }while(loopControl);

  return retVal;
}
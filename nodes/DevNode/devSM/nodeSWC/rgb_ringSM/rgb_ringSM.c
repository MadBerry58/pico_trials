#include "rgb_ringSM.h"
#include "../../../dev_config.h"

uint32_t rgbPatterns[][RGB_RING_PIXEL_NUMBER] = {
    {
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000
    },
    {
        0xaa000000,
        0xaa110000,
        0x99220000,
        0x99331100,
        0x88442200,
        0x88553300,
        0x77664400,
        0x77775500,
        0x66886600,
        0x66997700,
        0x44aa8800,
        0x33bb9900,
        0x22ccaa00,
        0x22ddbb00,
        0x11eecc00,
        0x11ffdd00
    },
    {
        0x00000000,
        0x11111100,
        0x22222200,
        0x33333300,
        0x44444400,
        0x55555500,
        0x66666600,
        0x77777700,
        0x88888800,
        0x99999900,
        0xaaaaaa00,
        0xbbbbbb00,
        0xcccccc00,
        0xdddddd00,
        0xeeeeee00,
        0xffffff00
    },
    {
        0xffffff00,
        0xeeeeee00,
        0xdddddd00,
        0xcccccc00,
        0xbbbbbb00,
        0xaaaaaa00,
        0x99999900,
        0x88888800,
        0x77777700,
        0x66666600,
        0x55555500,
        0x44444400,
        0x33333300,
        0x22222200,
        0x11111100,
        0x00000000
    },
    {
        0x09fdda00,
        0x22eecc00,
        0x44ccaa00,
        0xee220000,
        0xbb553300,
        0x55bb9900,
        0x99775500,
        0xaa664400,
        0x88886600,
        0x77997700,
        0x66aa8800,
        0xcc442200,
        0xdd331100,
        0x33ddbb00,
        0xff110000,
        0xff000000
    }
};


ws2812_sm_pattern patterns[] = 
{
    {/* blank pattern */
        .patternSize        = RGB_RING_PIXEL_NUMBER,
        .patternNumber      = 1,
        .refreshRate        = 0,
        .patternList        = (uint32_t**)(&(rgbPatterns)[0])
    },
    {
        .patternSize        = RGB_RING_PIXEL_NUMBER,
        .patternNumber      = 1,
        .refreshRate        = 0,
        .patternList        = (uint32_t**)(&(rgbPatterns[1]))
    },
    {
        .patternSize        = RGB_RING_PIXEL_NUMBER,
        .patternNumber      = 1,
        .refreshRate        = 0,
        .patternList        = (uint32_t**)(&(rgbPatterns[2]))
    },
    {
        .patternSize        = RGB_RING_PIXEL_NUMBER,
        .patternNumber      = 4,
        .refreshRate        = 1000,
        .patternList        = (uint32_t**)(&(rgbPatterns[1]))
    }
};
const uint8_t RGB_patternNumber = sizeof(patterns) / sizeof(patterns[0]);

ws2812_sm ws2812SM = {
    .smID                = 1,
    .pin                 = RGB_RING_PIN,
    .patternLocation     = NULL,
    .currentPatternIndex = 0u,
    .notificationFlag    = SM_WS2812_N_NONE,
    .sm_state            = SM_WS2812_UNINIT,
    .sm_request          = SM_WS2812_R_NONE
};

uint8_t rgb_ringSM_init()
{
  uint8_t retVal = 0u;
  if(SM_WS2812_E_OK       != init_ws2812(&ws2812SM))
  {
    printf("RGB PIO init error %d\n", retVal);
    retVal = 1;
  }

  return retVal;
}

uint8_t rgb_ringSM_run()
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
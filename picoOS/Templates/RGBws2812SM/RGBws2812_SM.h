#include "PatternTemplates.h"

typedef enum RGBws2812_SM_State{
    rgbSM_UNININIALISED,
    rgbSM_INITIALISED,
    rgbSM_IDLE,
    rgbSM_UPDATE_DYNAMIC_PATTERN,
    rgbSM_UPDATE_STATIC_PATTERN,
    rgbSM_FAULT
};

uint8_t RGBws2812SM_init();
uint8_t RGBws2812SM_run();

#ifndef RGB_TYPES
#define RGB_TYPES

#include <stdio.h>

typedef struct{
    uint8_t red   = 0u;
    uint8_t green = 0u;
    uint8_t blue  = 0u;
} Color_t;

typedef struct{
    bool patternDynamic;
    uint16_t timing_ms;
    Color_t *pattern;
} Pattern_t;

typedef enum {
    rgbSM_UNININIALISED,
    rgbSM_INITIALISED,
    rgbSM_IDLE,
    rgbSM_UPDATE_PATTERN,
    rgbSM_STOPPED,
    rgbSM_FAULT
}RGBws2812_SM_State;

typedef enum {
    NONE,
    STATIC,
    DYNAMIC
}RGBws2812_SM_Pattern_Type;

#endif
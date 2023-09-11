#ifndef INTERPOLATORS_H
#define INTERPOLATORS_H

#include <pico/stdlib.h>

typedef enum
{
    NONE,
    ACCUMULATOR,
    INTERPOLATOR,
    CLAMPER
}interpRole;


typedef struct
{
    bool        coreID;
    bool        interpolatorID;
    bool        concurrentAccess;
    interpRole  interpolatorRole;
}interpConfig;


#endif
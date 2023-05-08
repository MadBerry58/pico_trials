#ifndef OS_PORT_TYPES_H
#define OS_PORT_TYPES_H

#include <stdio.h>

typedef struct 
{
    bool        modifiedThisCycle;
    uint32_t    *dataElement;
} osPort_dataElement;

typedef struct 
{
    /* data */
} osPort_softwarePort;


#endif
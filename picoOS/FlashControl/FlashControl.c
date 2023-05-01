#include "FlashControl.h"

uint8 generateChecksum(uint32 *source, uint16 size, uint32 *result)
{
    return 0u;
}


uint8 writeArea(uint32 *destination, uint16 size, uint32 *source)
{
    return 0u;
}

uint8 readArea(uint32 *source, uint16 size, uint32 *destination)
{
    return 0u;
}

uint8 writeArea_WithBackup(uint32 *backup, uint32 *destination, uint16 size, uint32 *source)
{
    return 0u;
}

#if USE_DMA true

uint8 writeAreaDMA(uint32 *destination, uint16 size, uint32 *source)
{
    return 0u;
}

uint8 readAreaDMA(uint32 *source, uint16 size, uint32 *destination)
{
    return 0u;
}

uint8 writeAreaDMA_WithBackup(uint32 *backup, uint32 *destination, uint16 size, uint32 *source)
{
    return 0u;
}

#endif

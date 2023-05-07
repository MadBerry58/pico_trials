#include "FlashControl.h"

///TODO: use Fast Bulk Memoryu Fill/ Copy functionality
///TODO: add XIP support functionality (for something...)
uint8_t generateChecksum(uint32_t *source, uint16_t size, uint32_t *result)
{
    return 0u;
}


uint8_t writeArea(uint32_t *destination, uint16_t size, uint32_t *source)
{
    return 0u;
}

uint8_t readArea(uint32_t *source, uint16_t size, uint32_t *destination)
{
    return 0u;
}

uint8_t writeArea_WithBackup(uint32_t *backup, uint32_t *destination, uint16_t size, uint32_t *source)
{
    return 0u;
}

#if USE_DMA == true

uint8_t writeAreaDMA(uint32_t *destination, uint16_t size, uint32_t *source)
{
    return 0u;
}

uint8_t readAreaDMA(uint32_t *source, uint16_t size, uint32_t *destination)
{
    return 0u;
}

uint8_t writeAreaDMA_WithBackup(uint32_t *backup, uint32_t *destination, uint16_t size, uint32_t *source)
{
    return 0u;
}

#endif

#ifndef FLASH_CONTROL_H
#define FLASH_CONTROL_H

#include <stdio.h>

#define USE_DMA true

uint8_t generateChecksum(uint32_t *source, uint16_t size, uint32_t *result);


uint8_t writeArea(uint32_t *destination, uint16_t size, uint32_t *source);

uint8_t readArea(uint32_t *source, uint16_t size, uint32_t *destination);

uint8_t writeArea_WithBackup(uint32_t *backup, uint32_t *destination, uint16_t size, uint32_t *source);



 #if USE_DMA == true

uint8_t writeAreaDMA(uint32_t *destination, uint16_t size, uint32_t *source);

uint8_t readAreaDMA(uint32_t *source, uint16_t size, uint32_t *destination);

uint8_t writeAreaDMA_WithBackup(uint32_t *backup, uint32_t *destination, uint16_t size, uint32_t *source);

 #endif

#endif
#ifndef FLASH_CONTROL_H
#define FLASH_CONTROL_H

#define USE_DMA true

uint8 generateChecksum(uint32 *source, uint16 size, uint32 *result);


uint8 writeArea(uint32 *destination, uint16 size, uint32 *source);

uint8 readArea(uint32 *source, uint16 size, uint32 *destination);

uint8 writeArea_WithBackup(uint32 *backup, uint32 *destination, uint16 size, uint32 *source);



 #if USE_DMA true

uint8 writeAreaDMA(uint32 *destination, uint16 size, uint32 *source);

uint8 readAreaDMA(uint32 *source, uint16 size, uint32 *destination);

uint8 writeAreaDMA_WithBackup(uint32 *backup, uint32 *destination, uint16 size, uint32 *source);

 #endif

#endif
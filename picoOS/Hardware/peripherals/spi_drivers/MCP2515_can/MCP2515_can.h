#ifndef MCP2515_H
#define MCP2515_H

#include "canDefinitions.h"
#include "icDefinitions.h"
#include "hardware/spi.h"
#include "pico/time.h"
#include "pico/stdlib.h"
#include "boards/pico.h"

typedef enum {
    MCP2515_E_OK              ,
    MCP2515_E_DMA_UNAVAILABLE ,
    MCP2515_E_FAIL            ,
    MCP2515_E_ALLTXBUSY       ,
    MCP2515_E_FAILINIT        ,
    MCP2515_E_FAILTX          ,
    MCP2515_E_NOMSG           ,
    MCP2515_E_MSGTOOBIG       ,
    MCP2515_E_TOOBIG          ,
    MCP2515_E_MALFORMED_INPUT ,

    MCP2515_E_UNKNOWN
} MCP2515_Error;

typedef struct  {
    spi_inst_t   *SPI_CHANNEL;
    uint8_t       CS_PIN;
    uint8_t       TX_PIN;
    uint8_t       RX_PIN;
    uint8_t       SCK_PIN;
    uint32_t      SPI_CLOCK;

    MCP2515_Error  error;
}MCP2515_instance;

/* API functionality */
MCP2515_Error MCP2515_init              (MCP2515_instance *instance);
MCP2515_Error MCP2515_reset             (MCP2515_instance *instance);
MCP2515_Error MCP2515_setConfigMode     (MCP2515_instance *instance);
MCP2515_Error MCP2515_setListenOnlyMode (MCP2515_instance *instance);
MCP2515_Error MCP2515_setSleepMode      (MCP2515_instance *instance);
MCP2515_Error MCP2515_setLoopbackMode   (MCP2515_instance *instance);
MCP2515_Error MCP2515_setNormalMode     (MCP2515_instance *instance);
MCP2515_Error MCP2515_setClkOut         (MCP2515_instance *instance, const CAN_CLKOUT divisor);
MCP2515_Error MCP2515_setBitrate        (MCP2515_instance *instance, const CAN_SPEED  canSpeed,  const CAN_CLOCK canClock                       );
MCP2515_Error MCP2515_setFilterMask     (MCP2515_instance *instance, const MASK       num,       const bool ext,         const uint32_t ulData  );
MCP2515_Error MCP2515_setFilter         (MCP2515_instance *instance, const RXF        num,       const bool ext,         const uint32_t ulData  );
MCP2515_Error MCP2515_sendMessage_Buff  (MCP2515_instance *instance, const TXBn       txbn,      const can_frame *frame                         );
MCP2515_Error MCP2515_sendMessage       (MCP2515_instance *instance,                             const can_frame *frame                         );
MCP2515_Error MCP2515_readMessage_Buff  (MCP2515_instance *instance, const RXBn       rxbn,            can_frame *frame                         );
MCP2515_Error MCP2515_readMessage       (MCP2515_instance *instance,                                   can_frame *frame                         );

MCP2515_Error MCP2515_sendStaticFrame   (MCP2515_instance *instance, const TXBn       txbn,            can_frame *frame                         );
#endif
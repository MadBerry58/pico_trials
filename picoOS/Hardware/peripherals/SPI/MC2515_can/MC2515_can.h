#ifndef _MCP2515_H_MC2515_E
#define _MCP2515_H_

#include "canDefinitions.h"

#include "hardware/spi.h"
#include "pico/time.h"
#include "pico/stdlib.h"
#include "boards/pico.h"

typedef enum {
    MC2515_E_OK        = 0,
    MC2515_E_FAIL      = 1,
    MC2515_E_ALLTXBUSY = 2,
    MC2515_E_FAILINIT  = 3,
    MC2515_E_FAILTX    = 4,
    MC2515_E_NOMSG     = 5
} MC2515_ERROR;

typedef struct TXBn_REGS {
    MC2515_reg  CTRL;
    MC2515_reg  SIDH;
    MC2515_reg  DATA;
};

typedef struct RXBn_REGS {
    MC2515_reg  CTRL;
    MC2515_reg  SIDH;
    MC2515_reg  DATA;
    CANINTF     CANINTF_RXnIF;
};

enum MASK {
    MASK0,
    MASK1
};

enum STAT{
    STAT_RX0IF = (1<<0),
    STAT_RX1IF = (1<<1)
};

static const uint8_t STAT_RXIF_MASK     = STAT_RX0IF | STAT_RX1IF;

static const uint8_t EFLG_MC2515_EMASK  = EFLG_RX1OVR
                                        | EFLG_RX0OVR
                                        | EFLG_TXBO
                                        | EFLG_TXEP
                                        | EFLG_RXEP;

#define DEFAULT_SPI_CLOCK 10 000 000u // 10MHz
#define N_TXBUFFERS                3u
#define N_RXBUFFERS                2u

typedef struct MCP2515_instance {
    spi_inst_t   *CHANNEL;
    uint8_t       CS_PIN;
    uint8_t       TX_PIN;
    uint8_t       RX_PIN;
    uint8_t       SCK_PIN;
    uint32_t      SPI_CLOCK;

    MC2515_ERROR  error;
};

/* API functionality */
MC2515_E MCP2515_init              (MCP2515_instance *data);
MC2515_E MCP2515_reset             (MCP2515_instance *data);
MC2515_E MCP2515_setConfigMode     (MCP2515_instance *data);
MC2515_E MCP2515_setListenOnlyMode (MCP2515_instance *data);
MC2515_E MCP2515_setSleepMode      (MCP2515_instance *data);
MC2515_E MCP2515_setLoopbackMode   (MCP2515_instance *data);
MC2515_E MCP2515_setNormalMode     (MCP2515_instance *data);
MC2515_E MCP2515_setClkOut         (MCP2515_instance *data, const CAN_CLKOUT divisor);
MC2515_E MCP2515_setBitrate        (MCP2515_instance *data, const CAN_SPEED  canSpeed                                                  );
MC2515_E MCP2515_setBitrate        (MCP2515_instance *data, const CAN_SPEED  canSpeed,  const CAN_CLOCK canClock                       );
MC2515_E MCP2515_setFilterMask     (MCP2515_instance *data, const MASK       num,       const bool ext,         const uint32_t ulData  );
MC2515_E MCP2515_setFilter         (MCP2515_instance *data, const RXF        num,       const bool ext,         const uint32_t ulData  );
MC2515_E MCP2515_sendMessage       (MCP2515_instance *data, const TXBn       txbn,      const can_frame *frame                         );
MC2515_E MCP2515_sendMessage       (MCP2515_instance *data,                             const can_frame *frame                         );
MC2515_E MCP2515_readMessage       (MCP2515_instance *data, const RXBn       rxbn,            can_frame *frame                         );
MC2515_E MCP2515_readMessage       (MCP2515_instance *data,                                   can_frame *frame                         );

#endif
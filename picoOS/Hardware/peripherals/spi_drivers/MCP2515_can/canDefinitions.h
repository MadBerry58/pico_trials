#ifndef SPI_CAN_DEFS_H
#define SPI_CAN_DEFS_H

#include <stdint.h>

/* special address description flags for the CAN_ID */
#define CAN_EFF_FLAG 0x80000000UL /* EFF/SFF is set in the MSB */
#define CAN_RTR_FLAG 0x40000000UL /* remote transmission request */
#define CAN_ERR_FLAG 0x20000000UL /* error message frame */

/* valid bits in CAN ID for frame formats */
#define CAN_SFF_MASK 0x000007FFUL /* standard frame format (SFF) */
#define CAN_EFF_MASK 0x1FFFFFFFUL /* extended frame format (EFF) */
#define CAN_ERR_MASK 0x1FFFFFFFUL /* omit EFF, RTR, ERR flags */

/*
 * Controller Area Network Identifier structure
 *
 * bit 0-28 : CAN identifier (11/29 bit)
 * bit 29   : error message frame flag (0 = data frame, 1 = error message)
 * bit 30   : remote transmission request flag (1 = rtr frame)
 * bit 31   : frame format flag (0 = standard 11 bit, 1 = extended 29 bit)
 */
typedef uint32_t canid_t;

#define CAN_SFF_ID_BITS     11
#define CAN_EFF_ID_BITS     29

/* CAN payload length and DLC definitions according to ISO 11898-1 */
#define CAN_MAX_DLC 8
#define CAN_MAX_DLEN 8

typedef struct {
    canid_t can_id;  /* 32 bit CAN_ID + EFF/RTR/ERR flags */
    uint8_t can_dlc; /* frame payload length in byte (0 .. CAN_MAX_DLEN) */
    uint8_t data[CAN_MAX_DLEN];
} can_frame;

#define CANCTRL_REQOP  0xE0
#define CANCTRL_ABAT   0x10
#define CANCTRL_OSM    0x08
#define CANCTRL_CLKEN  0x04
#define CANCTRL_CLKPRE 0x03

#define CANSTAT_OPMOD  0xE0
#define CANSTAT_ICOD   0x0E

#define CNF3_SOF       0x80

#define TXB_EXIDE_MASK 0x08
#define DLC_MASK       0x0F
#define RTR_MASK       0x40

typedef enum  {
    MCP_20MHZ,
    MCP_16MHZ,
    MCP_8MHZ
} CAN_CLOCK;

typedef enum  {
    CAN_5KBPS,
    CAN_10KBPS,
    CAN_20KBPS,
    CAN_31K25BPS,
    CAN_33KBPS,
    CAN_40KBPS,
    CAN_50KBPS,
    CAN_80KBPS,
    CAN_83K3BPS,
    CAN_95KBPS,
    CAN_100KBPS,
    CAN_125KBPS,
    CAN_200KBPS,
    CAN_250KBPS,
    CAN_500KBPS,
    CAN_1000KBPS
} CAN_SPEED;

typedef enum  {
    CLKOUT_DISABLE  = -1,
    CLKOUT_DIV1     = 0x0,
    CLKOUT_DIV2     = 0x1,
    CLKOUT_DIV4     = 0x2,
    CLKOUT_DIV8     = 0x3,
} CAN_CLKOUT;

typedef enum  {
    CANINTF_RX0IF = 0x01,
    CANINTF_RX1IF = 0x02,
    CANINTF_TX0IF = 0x04,
    CANINTF_TX1IF = 0x08,
    CANINTF_TX2IF = 0x10,
    CANINTF_ERRIF = 0x20,
    CANINTF_WAKIF = 0x40,
    CANINTF_MERRF = 0x80
} CANINTF;

typedef enum  {
    EFLG_RX1OVR = (1<<7),
    EFLG_RX0OVR = (1<<6),
    EFLG_TXBO   = (1<<5),
    EFLG_TXEP   = (1<<4),
    EFLG_RXEP   = (1<<3),
    EFLG_TXWAR  = (1<<2),
    EFLG_RXWAR  = (1<<1),
    EFLG_EWARN  = (1<<0)
} EFLG;

typedef enum {
    CANCTRL_REQOP_NORMAL     = 0x00,
    CANCTRL_REQOP_SLEEP      = 0x20,
    CANCTRL_REQOP_LOOPBACK   = 0x40,
    CANCTRL_REQOP_LISTENONLY = 0x60,
    CANCTRL_REQOP_CONFIG     = 0x80,
    CANCTRL_REQOP_POWERUP    = 0xE0
} CANCTRL_REQOP_MODE;

#endif /* CAN_H_ */
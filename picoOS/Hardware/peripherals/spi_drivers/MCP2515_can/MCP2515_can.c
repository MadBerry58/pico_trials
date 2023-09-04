#include "MCP2515_can.h"

#define DEFAULT_SPI_CLOCK 10 000 000u // 10MHz
#define N_TXBUFFERS                3u
#define N_RXBUFFERS                2u
#define SET_MODE_TIMEOUT          10u // 10ms

#define STAT_RXIF_MASK      STAT_RX0IF  |\
                            STAT_RX1IF

#define EFLG_ERRORMASK      EFLG_RX1OVR |\
                            EFLG_RX0OVR |\
                            EFLG_TXBO   |\
                            EFLG_TXEP   |\
                            EFLG_RXEP

struct TXBn_REGS {
    MCP2515_reg  CTRL;
    MCP2515_reg  SIDH;
    MCP2515_reg  DATA;
} TXB[N_TXBUFFERS] = {
    {MCP_TXB0CTRL, MCP_TXB0SIDH, MCP_TXB0DATA},
    {MCP_TXB1CTRL, MCP_TXB1SIDH, MCP_TXB1DATA},
    {MCP_TXB2CTRL, MCP_TXB2SIDH, MCP_TXB2DATA}
};
TXBn txBuffers[N_TXBUFFERS] = {TXB0, TXB1, TXB2};

struct RXBn_REGS {
    MCP2515_reg  CTRL;
    MCP2515_reg  SIDH;
    MCP2515_reg  DATA;
    CANINTF      CANINTF_RXnIF;
} RXB[N_RXBUFFERS] = {
    {MCP_RXB0CTRL, MCP_RXB0SIDH, MCP_RXB0DATA, CANINTF_RX0IF},
    {MCP_RXB1CTRL, MCP_RXB1SIDH, MCP_RXB1DATA, CANINTF_RX1IF}
};

MASK    masks  [] = {MASK0, MASK1};
RXF     filters[] = {RXF0, RXF1, RXF2, RXF3, RXF4, RXF5};
uint8_t zeros[14] = {0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u, 0u};
uint8_t resetMask = (CANINTF_RX0IF | CANINTF_RX1IF | CANINTF_ERRIF | CANINTF_MERRF);
uint8_t tempMsg   = 0u;

void          prepareId           (uint8_t          *buffer,   const bool        ext,    const uint32_t id   );
MCP2515_Error setMode             (MCP2515_instance *instance, const CANCTRL_REQOP_MODE mode);
void          readRegisters       (MCP2515_instance *instance, const MCP2515_reg  reg, uint8_t *values,   const uint8_t  dataLength);
void          setRegisters        (MCP2515_instance *instance, const MCP2515_reg  reg, uint8_t *values,   const uint8_t  dataLength);
void          modifyRegister      (MCP2515_instance *instance, const MCP2515_reg  reg, uint8_t  mask,     const uint8_t  data);

/* Internal Functionality */
void          clearRXnOVRFlags    (MCP2515_instance *instance);
void          clearInterrupts     (MCP2515_instance *instance);
void          clearTXInterrupts   (MCP2515_instance *instance);
void          clearRXnOVR         (MCP2515_instance *instance);
void          clearMERR           (MCP2515_instance *instance);
void          clearERRIF          (MCP2515_instance *instance);
bool          checkError          (MCP2515_instance *instance);
bool          checkReceive        (MCP2515_instance *instance);
uint8_t       errorCountRX        (MCP2515_instance *instance);
uint8_t       errorCountTX        (MCP2515_instance *instance);
uint8_t       getErrorFlags       (MCP2515_instance *instance);
uint8_t       getInterrupts       (MCP2515_instance *instance);
uint8_t       getInterruptMask    (MCP2515_instance *instance);
uint8_t       getStatus           (MCP2515_instance *instance);

/* Helper Functions */
static inline void  startSPI      (MCP2515_instance *instance);
static inline void  endSPI        (MCP2515_instance *instance);

static inline void     startSPI         (MCP2515_instance *instance)
{
    asm volatile("nop \n nop \n nop");
    gpio_put(instance->CS_PIN, 0);
    asm volatile("nop \n nop \n nop");
}

static inline void     endSPI           (MCP2515_instance *instance)
{
    asm volatile("nop \n nop \n nop");
    gpio_put(instance->CS_PIN, 1);
    asm volatile("nop \n nop \n nop");
}

MCP2515_Error MCP2515_init(MCP2515_instance *instance)
{
    MCP2515_Error retVal = MCP2515_E_OK;

    spi_init            (instance->SPI_CHANNEL, instance->SPI_CLOCK);
    gpio_set_dir        (instance->CS_PIN,      GPIO_OUT);
    gpio_set_function   (instance->TX_PIN,      GPIO_FUNC_SPI);
    gpio_set_function   (instance->RX_PIN,      GPIO_FUNC_SPI);
    gpio_set_function   (instance->SCK_PIN,     GPIO_FUNC_SPI);
    spi_set_format      (instance->SPI_CHANNEL, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    gpio_init           (instance->CS_PIN);

    endSPI(instance);

    return retVal;
}

MCP2515_Error MCP2515_reset(MCP2515_instance *instance)
{
    startSPI(instance);

    uint8_t instruction = INSTRUCTION_RESET;
    spi_write_blocking(instance->SPI_CHANNEL, &instruction, 1);

    endSPI  (instance);

    //Depends on oscillator & capacitors used
    sleep_ms(10);

    setRegisters    (instance, MCP_TXB0CTRL, zeros,     14);
    setRegisters    (instance, MCP_TXB1CTRL, zeros,     14);
    setRegisters    (instance, MCP_TXB2CTRL, zeros,     14);
    setRegisters    (instance, MCP_RXB0CTRL, zeros,     1 );
    setRegisters    (instance, MCP_RXB1CTRL, zeros,     1 );
    setRegisters    (instance, MCP_CANINTE, &resetMask, 1 );

    // receives all valid messages using either Standard or Extended Identifiers that
    // meet filter criteria. RXF0 is applied for RXB0, RXF1 is applied for RXB1
    modifyRegister  (instance, MCP_RXB0CTRL,
                    RXBnCTRL_RXM_MASK   | RXB0CTRL_BUKT | RXB0CTRL_FILHIT_MASK,
                    RXBnCTRL_RXM_STDEXT | RXB0CTRL_BUKT | RXB0CTRL_FILHIT);

    modifyRegister  (instance, MCP_RXB1CTRL,
                    RXBnCTRL_RXM_MASK   | RXB1CTRL_FILHIT_MASK,
                    RXBnCTRL_RXM_STDEXT | RXB1CTRL_FILHIT);

    // clear filters and masks
    // do not filter any standard frames for RXF0 used by RXB0
    // do not filter any extended frames for RXF1 used by RXB1
    for (int i = 0; i < 6; ++i) 
    {
        bool ext = (i == 1);
        MCP2515_Error result = MCP2515_setFilter(instance, filters[i], ext, 0);
        if (result != MCP2515_E_OK) 
        {
            return result;
        }
    }

    for (int i = 0; i < 2; ++i) 
    {
        MCP2515_Error result = MCP2515_setFilterMask(instance, masks[i], true, 0);
        if (result != MCP2515_E_OK) {
            return result;
        }
    }

    return MCP2515_E_OK;
}

void readRegisters(MCP2515_instance *instance, const MCP2515_reg reg, uint8_t *values, const uint8_t data_length)
{///INFO: single registry read has been removed. same functionality can be used with data_length == 1u

    uint8_t data[2] = { INSTRUCTION_READ, reg};
    startSPI(instance);

    spi_write_blocking  (instance->SPI_CHANNEL, data, 2);
    spi_read_blocking   (instance->SPI_CHANNEL, 0x00, values, data_length);

    endSPI(instance);
}

void setRegisters(MCP2515_instance *instance, const MCP2515_reg  reg, uint8_t *values,   const uint8_t  data_length)
{
    /* Build write instruction */
    uint8_t data[2] = { INSTRUCTION_WRITE, reg };
    startSPI(instance);

    /* Send write instruction */
    spi_write_blocking(instance->SPI_CHANNEL, data, 2);
    
    /* Send new values */
    spi_write_blocking(instance->SPI_CHANNEL, values, data_length);

    endSPI(instance);
}

/**
 * @brief Perform a masked write to a register
 * 
 * @param instance  The MCP2515 hardware instance data
 * @param reg       The target registry
 * @param mask      The mask used to define the modified bits
 * @param data      The data used to write to the registry
 */
void modifyRegister(MCP2515_instance *instance, const MCP2515_reg reg, const uint8_t mask, const uint8_t data)
{
    /* Build bit modification instruction */
    uint8_t instructions[4] = { INSTRUCTION_BITMOD, reg, mask, data };

    startSPI(instance);

    spi_write_blocking(instance->SPI_CHANNEL, instructions, 4);

    endSPI(instance);
}

uint8_t getStatus(MCP2515_instance *instance)
{
    uint8_t ret;

    startSPI(instance);

    uint8_t instruction = INSTRUCTION_READ_STATUS;
    spi_write_blocking  (instance->SPI_CHANNEL, &instruction, 1);
    spi_read_blocking   (instance->SPI_CHANNEL, 0x00, &ret, 1);

    endSPI  (instance);

    return ret;
}

MCP2515_Error MCP2515_setConfigMode(MCP2515_instance *instance)
{
    return setMode(instance, CANCTRL_REQOP_CONFIG);
}

MCP2515_Error MCP2515_setListenOnlyMode(MCP2515_instance *instance)
{
    return setMode(instance, CANCTRL_REQOP_LISTENONLY);
}

MCP2515_Error MCP2515_setSleepMode(MCP2515_instance *instance)
{
    return setMode(instance, CANCTRL_REQOP_SLEEP);
}

MCP2515_Error MCP2515_setLoopbackMode(MCP2515_instance *instance)
{
    return setMode(instance, CANCTRL_REQOP_LOOPBACK);
}

MCP2515_Error MCP2515_setNormalMode(MCP2515_instance *instance)
{
    return setMode(instance, CANCTRL_REQOP_NORMAL);
}

bool            checkReceive     (MCP2515_instance *instance)
{
    return (0 < (STAT_RXIF_MASK & (getStatus(instance))));
}

bool            checkError       (MCP2515_instance *instance)
{
    return (0 < (EFLG_ERRORMASK & (getErrorFlags(instance))));
}

uint8_t         getErrorFlags    (MCP2515_instance *instance)
{
    readRegisters(instance, MCP_EFLG, &tempMsg, 1);
    return tempMsg;
}

void            clearRXnOVRFlags (MCP2515_instance *instance)
{
	modifyRegister(instance, MCP_EFLG, EFLG_RX0OVR | EFLG_RX1OVR, 0);
}

uint8_t         getInterrupts    (MCP2515_instance *instance)
{
    readRegisters(instance, MCP_CANINTF, &tempMsg, 1);
    return tempMsg;
}

void            clearInterrupts  (MCP2515_instance *instance)
{
    setRegisters(instance, MCP_CANINTF, zeros, 1);
}

uint8_t         getInterruptMask (MCP2515_instance *instance)
{
    readRegisters(instance, MCP_CANINTE, &tempMsg, 1);
    return tempMsg;
}

void            clearTXInterrupts(MCP2515_instance *instance)
{
    modifyRegister(instance, MCP_CANINTF, (CANINTF_TX0IF | CANINTF_TX1IF | CANINTF_TX2IF), 0);
}

void            clearRXnOVR      (MCP2515_instance *instance)
{
	uint8_t eflg = getErrorFlags(instance);
	if (eflg != 0) {
		clearRXnOVRFlags(instance);
		clearInterrupts (instance);
		//modifyRegister(MCP_CANINTF, CANINTF_ERRIF, 0);
	}
}

void            clearMERR        (MCP2515_instance *instance)
{
	//modifyRegister(MCP_EFLG, EFLG_RX0OVR | EFLG_RX1OVR, 0);
	//clearInterrupts();
	modifyRegister(instance, MCP_CANINTF, CANINTF_MERRF, 0);
}

void            clearERRIF       (MCP2515_instance *instance)
{
    //modifyRegister(MCP_EFLG, EFLG_RX0OVR | EFLG_RX1OVR, 0);
    //clearInterrupts();
    modifyRegister(instance, MCP_CANINTF, CANINTF_ERRIF, 0);
}

uint8_t         errorCountRX     (MCP2515_instance *instance)
{
    readRegisters(instance, MCP_REC, &tempMsg, 1);
    return tempMsg;
}

uint8_t         errorCountTX     (MCP2515_instance *instance)
{
    readRegisters(instance, MCP_TEC, &tempMsg, 1);
    return tempMsg;
}

void prepareId(uint8_t *buffer, const bool ext, const uint32_t id)
{
    uint16_t canid = (uint16_t)(id & 0x0FFFF);

    if (ext) 
    {
        buffer[MCP_EID0]  = (uint8_t )( canid & 0xFF        );
        buffer[MCP_EID8]  = (uint8_t )( canid >> 8          );
        canid             = (uint16_t)( id    >> 16         );
        buffer[MCP_SIDL]  = (uint8_t )( canid & 0x03        );
        buffer[MCP_SIDL] += (uint8_t )((canid & 0x1C) << 3  );
        buffer[MCP_SIDL] |= (uint8_t )( TXB_EXIDE_MASK      );
        buffer[MCP_SIDH]  = (uint8_t )( canid >> 5          );
    } 
    else 
    {
        buffer[MCP_SIDH]  = (uint8_t )( canid >> 3          );
        buffer[MCP_SIDL]  = (uint8_t )((canid & 0x07 ) << 5 );
        buffer[MCP_EID0]  = (uint8_t )( 0                   );
        buffer[MCP_EID8]  = (uint8_t )( 0                   );
    }
}

MCP2515_Error setMode(MCP2515_instance *instance, const CANCTRL_REQOP_MODE mode)
{
    MCP2515_Error retVal = MCP2515_E_UNKNOWN;
    modifyRegister(instance, MCP_CANCTRL, CANCTRL_REQOP, mode);

    unsigned long endTime = to_ms_since_boot(get_absolute_time()) + SET_MODE_TIMEOUT;

    /* Remodel to deterministic FOR loop */
    while (to_ms_since_boot(get_absolute_time()) < endTime) 
    {
        uint8_t newmode = 0;
        readRegisters(instance, MCP_CANSTAT, &newmode, 1);
        newmode &= CANSTAT_OPMOD;
        if(newmode == mode)
        {
            retVal = MCP2515_E_OK;
            break;
        }
        else
        {

        }
    }

    return retVal;
}

MCP2515_Error MCP2515_setBitrate(MCP2515_instance *instance, const CAN_SPEED canSpeed, CAN_CLOCK canClock)
{
    MCP2515_Error retVal = MCP2515_setConfigMode(instance);
    if (MCP2515_E_OK == retVal) 
    {
        uint8_t cfg1, cfg2, cfg3;
        bool set = true;
        switch (canClock)
        {
            case (MCP_8MHZ):
            switch (canSpeed)
            {
                case (CAN_5KBPS):  //   5KBPS
                cfg1 = MCP_8MHz_5kBPS_CFG1;
                cfg2 = MCP_8MHz_5kBPS_CFG2;
                cfg3 = MCP_8MHz_5kBPS_CFG3;
                break;

                case (CAN_10KBPS): //  10KBPS
                cfg1 = MCP_8MHz_10kBPS_CFG1;
                cfg2 = MCP_8MHz_10kBPS_CFG2;
                cfg3 = MCP_8MHz_10kBPS_CFG3;
                break;

                case (CAN_20KBPS)://  20KBPS
                cfg1 = MCP_8MHz_20kBPS_CFG1;
                cfg2 = MCP_8MHz_20kBPS_CFG2;
                cfg3 = MCP_8MHz_20kBPS_CFG3;
                break;

                case (CAN_31K25BPS):// 31.25KBPS
                cfg1 = MCP_8MHz_31k25BPS_CFG1;
                cfg2 = MCP_8MHz_31k25BPS_CFG2;
                cfg3 = MCP_8MHz_31k25BPS_CFG3;
                break;

                case (CAN_33KBPS):// 33.333KBPS
                cfg1 = MCP_8MHz_33k3BPS_CFG1;
                cfg2 = MCP_8MHz_33k3BPS_CFG2;
                cfg3 = MCP_8MHz_33k3BPS_CFG3;
                break;

                case (CAN_40KBPS)://  40Kbps
                cfg1 = MCP_8MHz_40kBPS_CFG1;
                cfg2 = MCP_8MHz_40kBPS_CFG2;
                cfg3 = MCP_8MHz_40kBPS_CFG3;
                break;

                case (CAN_50KBPS)://  50Kbps
                cfg1 = MCP_8MHz_50kBPS_CFG1;
                cfg2 = MCP_8MHz_50kBPS_CFG2;
                cfg3 = MCP_8MHz_50kBPS_CFG3;
                break;

                case (CAN_80KBPS)://  80Kbps
                cfg1 = MCP_8MHz_80kBPS_CFG1;
                cfg2 = MCP_8MHz_80kBPS_CFG2;
                cfg3 = MCP_8MHz_80kBPS_CFG3;
                break;

                case (CAN_100KBPS):// 100Kbps
                cfg1 = MCP_8MHz_100kBPS_CFG1;
                cfg2 = MCP_8MHz_100kBPS_CFG2;
                cfg3 = MCP_8MHz_100kBPS_CFG3;
                break;

                case (CAN_125KBPS):// 125Kbps
                cfg1 = MCP_8MHz_125kBPS_CFG1;
                cfg2 = MCP_8MHz_125kBPS_CFG2;
                cfg3 = MCP_8MHz_125kBPS_CFG3;
                break;

                case (CAN_200KBPS):// 200Kbps
                cfg1 = MCP_8MHz_200kBPS_CFG1;
                cfg2 = MCP_8MHz_200kBPS_CFG2;
                cfg3 = MCP_8MHz_200kBPS_CFG3;
                break;

                case (CAN_250KBPS):// 250Kbps
                cfg1 = MCP_8MHz_250kBPS_CFG1;
                cfg2 = MCP_8MHz_250kBPS_CFG2;
                cfg3 = MCP_8MHz_250kBPS_CFG3;
                break;

                case (CAN_500KBPS):// 500Kbps
                cfg1 = MCP_8MHz_500kBPS_CFG1;
                cfg2 = MCP_8MHz_500kBPS_CFG2;
                cfg3 = MCP_8MHz_500kBPS_CFG3;
                break;

                case (CAN_1000KBPS)://   1Mbps
                cfg1 = MCP_8MHz_1000kBPS_CFG1;
                cfg2 = MCP_8MHz_1000kBPS_CFG2;
                cfg3 = MCP_8MHz_1000kBPS_CFG3;
                break;

                default:
                set = false;
                break;
            }
            break;

            case (MCP_16MHZ):
            switch (canSpeed)
            {
                case (CAN_5KBPS):  //   5Kbps
                cfg1 = MCP_16MHz_5kBPS_CFG1;
                cfg2 = MCP_16MHz_5kBPS_CFG2;
                cfg3 = MCP_16MHz_5kBPS_CFG3;
                break;

                case (CAN_10KBPS): //  10Kbps
                cfg1 = MCP_16MHz_10kBPS_CFG1;
                cfg2 = MCP_16MHz_10kBPS_CFG2;
                cfg3 = MCP_16MHz_10kBPS_CFG3;
                break;

                case (CAN_20KBPS): //  20Kbps
                cfg1 = MCP_16MHz_20kBPS_CFG1;
                cfg2 = MCP_16MHz_20kBPS_CFG2;
                cfg3 = MCP_16MHz_20kBPS_CFG3;
                break;

                case (CAN_33KBPS): //  33.333Kbps
                cfg1 = MCP_16MHz_33k3BPS_CFG1;
                cfg2 = MCP_16MHz_33k3BPS_CFG2;
                cfg3 = MCP_16MHz_33k3BPS_CFG3;
                break;

                case (CAN_40KBPS): //  40Kbps
                cfg1 = MCP_16MHz_40kBPS_CFG1;
                cfg2 = MCP_16MHz_40kBPS_CFG2;
                cfg3 = MCP_16MHz_40kBPS_CFG3;
                break;

                case (CAN_50KBPS): //  50Kbps
                cfg1 = MCP_16MHz_50kBPS_CFG1;
                cfg2 = MCP_16MHz_50kBPS_CFG2;
                cfg3 = MCP_16MHz_50kBPS_CFG3;
                break;

                case (CAN_80KBPS): //  80Kbps
                cfg1 = MCP_16MHz_80kBPS_CFG1;
                cfg2 = MCP_16MHz_80kBPS_CFG2;
                cfg3 = MCP_16MHz_80kBPS_CFG3;
                break;

                case (CAN_83K3BPS)://  83.333Kbps
                cfg1 = MCP_16MHz_83k3BPS_CFG1;
                cfg2 = MCP_16MHz_83k3BPS_CFG2;
                cfg3 = MCP_16MHz_83k3BPS_CFG3;
                break; 

                case (CAN_100KBPS):// 100Kbps
                cfg1 = MCP_16MHz_100kBPS_CFG1;
                cfg2 = MCP_16MHz_100kBPS_CFG2;
                cfg3 = MCP_16MHz_100kBPS_CFG3;
                break;

                case (CAN_125KBPS):// 125Kbps
                cfg1 = MCP_16MHz_125kBPS_CFG1;
                cfg2 = MCP_16MHz_125kBPS_CFG2;
                cfg3 = MCP_16MHz_125kBPS_CFG3;
                break;

                case (CAN_200KBPS):// 200Kbps
                cfg1 = MCP_16MHz_200kBPS_CFG1;
                cfg2 = MCP_16MHz_200kBPS_CFG2;
                cfg3 = MCP_16MHz_200kBPS_CFG3;
                break;

                case (CAN_250KBPS):// 250Kbps
                cfg1 = MCP_16MHz_250kBPS_CFG1;
                cfg2 = MCP_16MHz_250kBPS_CFG2;
                cfg3 = MCP_16MHz_250kBPS_CFG3;
                break;

                case (CAN_500KBPS):// 500Kbps
                cfg1 = MCP_16MHz_500kBPS_CFG1;
                cfg2 = MCP_16MHz_500kBPS_CFG2;
                cfg3 = MCP_16MHz_500kBPS_CFG3;
                break;

                case (CAN_1000KBPS)://   1Mbps
                cfg1 = MCP_16MHz_1000kBPS_CFG1;
                cfg2 = MCP_16MHz_1000kBPS_CFG2;
                cfg3 = MCP_16MHz_1000kBPS_CFG3;
                break;

                default:
                set = false;
                break;
            }
            break;

            case (MCP_20MHZ):
            switch (canSpeed)
            {
                case (CAN_33KBPS): //  33.333Kbps
                cfg1 = MCP_20MHz_33k3BPS_CFG1;
                cfg2 = MCP_20MHz_33k3BPS_CFG2;
                cfg3 = MCP_20MHz_33k3BPS_CFG3;
            break;

                case (CAN_40KBPS): //  40Kbps
                cfg1 = MCP_20MHz_40kBPS_CFG1;
                cfg2 = MCP_20MHz_40kBPS_CFG2;
                cfg3 = MCP_20MHz_40kBPS_CFG3;
                break;

                case (CAN_50KBPS): //  50Kbps
                cfg1 = MCP_20MHz_50kBPS_CFG1;
                cfg2 = MCP_20MHz_50kBPS_CFG2;
                cfg3 = MCP_20MHz_50kBPS_CFG3;
                break;

                case (CAN_80KBPS): //  80Kbps
                cfg1 = MCP_20MHz_80kBPS_CFG1;
                cfg2 = MCP_20MHz_80kBPS_CFG2;
                cfg3 = MCP_20MHz_80kBPS_CFG3;
                break;

                case (CAN_83K3BPS): //  83.333Kbps
                cfg1 = MCP_20MHz_83k3BPS_CFG1;
                cfg2 = MCP_20MHz_83k3BPS_CFG2;
                cfg3 = MCP_20MHz_83k3BPS_CFG3;
            break;

                case (CAN_100KBPS): // 100Kbps
                cfg1 = MCP_20MHz_100kBPS_CFG1;
                cfg2 = MCP_20MHz_100kBPS_CFG2;
                cfg3 = MCP_20MHz_100kBPS_CFG3;
                break;

                case (CAN_125KBPS): // 125Kbps
                cfg1 = MCP_20MHz_125kBPS_CFG1;
                cfg2 = MCP_20MHz_125kBPS_CFG2;
                cfg3 = MCP_20MHz_125kBPS_CFG3;
                break;

                case (CAN_200KBPS): // 200Kbps
                cfg1 = MCP_20MHz_200kBPS_CFG1;
                cfg2 = MCP_20MHz_200kBPS_CFG2;
                cfg3 = MCP_20MHz_200kBPS_CFG3;
                break;

                case (CAN_250KBPS): // 250Kbps
                cfg1 = MCP_20MHz_250kBPS_CFG1;
                cfg2 = MCP_20MHz_250kBPS_CFG2;
                cfg3 = MCP_20MHz_250kBPS_CFG3;
                break;

                case (CAN_500KBPS): // 500Kbps
                cfg1 = MCP_20MHz_500kBPS_CFG1;
                cfg2 = MCP_20MHz_500kBPS_CFG2;
                cfg3 = MCP_20MHz_500kBPS_CFG3;
                break;

                case (CAN_1000KBPS): //   1Mbps
                cfg1 = MCP_20MHz_1000kBPS_CFG1;
                cfg2 = MCP_20MHz_1000kBPS_CFG2;
                cfg3 = MCP_20MHz_1000kBPS_CFG3;
                break;

                default:
                set = false;
                break;
            }
            break;

            default:
            set = false;
            break;
        }

        if (set) 
        {
            setRegisters(instance, MCP_CNF1, &cfg1, 1u);
            setRegisters(instance, MCP_CNF2, &cfg2, 1u);
            setRegisters(instance, MCP_CNF3, &cfg3, 1u);
            retVal = MCP2515_E_OK;
        }
        else 
        {
            retVal = MCP2515_E_FAIL;
        }
    }
    else
    {

    }

    return retVal;
}

MCP2515_Error MCP2515_setClkOut(MCP2515_instance *instance, const CAN_CLKOUT divisor)
{
    MCP2515_Error retVal = MCP2515_E_UNKNOWN;

    if (divisor == CLKOUT_DISABLE) 
    {
        /* Turn off CLKEN */
        modifyRegister(instance, MCP_CANCTRL, CANCTRL_CLKEN, 0x00);

        /* Turn on CLKOUT for SOF */
        modifyRegister(instance, MCP_CNF3, CNF3_SOF, CNF3_SOF);

        retVal = MCP2515_E_OK;
    }
    else
    {
        /* Set the prescaler (CLKPRE) */
        modifyRegister(instance, MCP_CANCTRL, CANCTRL_CLKPRE, divisor);

        /* Turn on CLKEN */
        modifyRegister(instance, MCP_CANCTRL, CANCTRL_CLKEN, CANCTRL_CLKEN);

        /* Turn off CLKOUT for SOF */
        modifyRegister(instance, MCP_CNF3, CNF3_SOF, 0x00);

        retVal = MCP2515_E_OK;
    }
    return retVal;
}

MCP2515_Error MCP2515_setFilterMask(MCP2515_instance *instance, const MASK num, const bool ext, const uint32_t ulData)
{
    MCP2515_Error res = MCP2515_E_UNKNOWN;
    res = MCP2515_setConfigMode(instance);
    
    if (res == MCP2515_E_OK) 
    {
        uint8_t tbufdata[4];
        prepareId(tbufdata, ext, ulData);

        switch (num)
        {
            case MASK0:
                setRegisters(instance, MCP_RXM0SIDH, tbufdata, 4);
                break;
            case MASK1:
                setRegisters(instance, MCP_RXM1SIDH, tbufdata, 4);
                break;
            default:
                res = MCP2515_E_MALFORMED_INPUT;
        }
    }
    else
    {
        /* res contains the error from the setConfigMode API call */
    }

    return res;
}

MCP2515_Error MCP2515_setFilter(MCP2515_instance *instance, const RXF num, const bool ext, const uint32_t ulData)
{
    MCP2515_Error res = MCP2515_E_UNKNOWN;

    res = setConfigMode(instance);

    if (res == MCP2515_E_OK) 
    {
        uint8_t tbufdata[4];
        prepareId   (tbufdata, ext, ulData);

        switch (num) {
            case RXF0: 
                setRegisters(instance, MCP_RXF0SIDH, tbufdata, 4);
                break;
            case RXF1: 
                setRegisters(instance, MCP_RXF1SIDH, tbufdata, 4);
                break;
            case RXF2: 
                setRegisters(instance, MCP_RXF2SIDH, tbufdata, 4);
                break;
            case RXF3: 
                setRegisters(instance, MCP_RXF3SIDH, tbufdata, 4);
                break;
            case RXF4: 
                setRegisters(instance, MCP_RXF4SIDH, tbufdata, 4);
                break;
            case RXF5: 
                setRegisters(instance, MCP_RXF5SIDH, tbufdata, 4);
                break;
            default:
                res = MCP2515_E_MALFORMED_INPUT;
        }
    }
    else
    {
        /* res contains the error from the setConfigMode API call */
    }
    return res;
}

MCP2515_Error MCP2515_sendMessage_Buff(MCP2515_instance *instance, const TXBn txbn, const can_frame *frame)
{
    MCP2515_Error retVal = MCP2515_E_UNKNOWN;
    uint8_t ctrl;

    if(frame->can_dlc > CAN_MAX_DLEN) 
    {
        retVal = MCP2515_E_MSGTOOBIG;
    }
    else
    {
        const struct TXBn_REGS *txbuf = &TXB[txbn];

        uint8_t data[13];

        bool     ext = (frame->can_id & CAN_EFF_FLAG);
        bool     rtr = (frame->can_id & CAN_RTR_FLAG);
        uint32_t id  = (frame->can_id & (ext ? CAN_EFF_MASK : CAN_SFF_MASK));

        prepareId(data, ext, id);

        data[MCP_DLC] = rtr ? (frame->can_dlc | RTR_MASK) : frame->can_dlc;

        memcpy(&data[MCP_DATA], frame->data, frame->can_dlc);

        setRegisters(instance, txbuf->SIDH, data, 5 + frame->can_dlc);

        modifyRegister(instance, txbuf->CTRL, TXB_TXREQ, TXB_TXREQ);

        readRegisters(instance, txbuf->CTRL, &ctrl, 1);

        if ((ctrl & (TXB_ABTF | TXB_MLOA | TXB_TXERR)) != 0) 
        {
            retVal = MCP2515_E_FAILTX;
        }
        else
        {
            retVal = MCP2515_E_OK;
        }
    }
    return retVal;
}

MCP2515_Error MCP2515_sendMessage(MCP2515_instance *instance, const can_frame *frame)
{
    MCP2515_Error retVal = MCP2515_E_ALLTXBUSY;
    uint8_t index;
    uint8_t ctrlval;
    

    if (CAN_MAX_DLEN < frame->can_dlc) 
    {/* Data payload bigger than the max value */
        retVal = MCP2515_E_FAILTX;
    }
    else
    {
        for (index = 0; index < N_TXBUFFERS; ++index) 
        {
            const struct TXBn_REGS *txbuf = &TXB[txBuffers[index]];
            readRegisters(instance, txbuf->CTRL, &ctrlval, 1);
            if ( (ctrlval & TXB_TXREQ) == 0 ) 
            {
                retVal = MCP2515_sendMessage_Buff(instance, txBuffers[index], frame);
                break;
            }
            else
            {
                /* Check the next TX buffer */
            }
        }
    }


    return retVal;
}

MCP2515_Error MCP2515_readMessage_Buff(MCP2515_instance *instance, const RXBn rxbn, can_frame *frame)
{
    MCP2515_Error retVal = MCP2515_E_UNKNOWN;
    uint8_t      dlc    = 0u;
    uint32_t     id     = 0u;
    
    uint8_t      tbufdata[5];

    /* Bind selected buffer register array*/
    const struct RXBn_REGS *rxb = &RXB[rxbn];

    /* Read selected SIDH buffer */
    readRegisters (instance, rxb->SIDH, tbufdata, 5u);
 
    id = (tbufdata[MCP_SIDH] << 3u) + (tbufdata[MCP_SIDL] >> 5u);

    if(TXB_EXIDE_MASK == (tbufdata[MCP_SIDL] & TXB_EXIDE_MASK))
    {
        id  = (id << 2) + (tbufdata[MCP_SIDL] & 0b11 );
        id  = (id << 8) + (tbufdata[MCP_EID8]        );
        id  = (id << 8) + (tbufdata[MCP_EID0]        );
        id |= CAN_EFF_FLAG;
    }

    dlc = (tbufdata[MCP_DLC] & DLC_MASK);

    if (CAN_MAX_DLEN < dlc )
    {/* Message size is bigger than the supported size */
        retVal = MCP2515_E_MSGTOOBIG;
    }
    else
    {
        /* Set Remote Transfer Request bit */
        readRegisters(instance, rxb->CTRL, &tempMsg, 1);
        id |= (CAN_RTR_FLAG * (RXBnCTRL_RTR & tempMsg));
        
        /* Construct frame */
        frame->can_id  = id;
        frame->can_dlc = dlc;

        /* Read frame data */
        readRegisters (instance, rxb->DATA,   frame->data,        dlc);
        
        /* Notify the buffer that the message has been read */
        modifyRegister(instance, MCP_CANINTF, rxb->CANINTF_RXnIF, 0  );

        retVal = MCP2515_E_OK;
    }

    return retVal;
}

MCP2515_Error MCP2515_readMessage(MCP2515_instance *instance, can_frame *frame)
{
    MCP2515_Error retVal = MCP2515_E_UNKNOWN;

    /* Check if there is new data received */
    uint8_t status = getStatus(instance);

    if(status & STAT_RX0IF)
    {/* Buffer 0 has a new message */
        retVal = MCP2515_readMessage_Buff(instance, RXB0, frame);
    }
    else
    if(status & STAT_RX1IF)
    {/* Buffer 1 has a new message */
        retVal = MCP2515_readMessage_Buff(instance, RXB1, frame);
    }
    else
    {/* No new messages present */
        retVal = MCP2515_E_NOMSG;
    }

    return retVal;
}


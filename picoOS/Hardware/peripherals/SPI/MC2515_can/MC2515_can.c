#include "mcp2515_can.h"
#include 
uint8_t zeros[14] = {0};

void        prepareId           (      uint8_t *buffer,    const bool    ext,        const uint32_t id   );
MC2515_E    setMode             (const CANCTRL_REQOP_MODE mode);
void        readRegisters       (const MC2515_reg  reg,          uint8_t values[],   const uint8_t  n    );
void        setRegister         (const MC2515_reg  reg,    const uint8_t value                           );
void        setRegisters        (const MC2515_reg  reg,    const uint8_t values[],   const uint8_t  n    );
void        modifyRegister      (const MC2515_reg  reg,    const uint8_t mask,       const uint8_t  data );

/* Internal Functionality */
void        clearRXnOVRFlags    (MCP2515_instance *instance);
void        clearInterrupts     (MCP2515_instance *instance);
void        clearTXInterrupts   (MCP2515_instance *instance);
void        clearRXnOVR         (MCP2515_instance *instance);
void        clearMERR           (MCP2515_instance *instance);
void        clearERRIF          (MCP2515_instance *instance);
bool        checkError          (MCP2515_instance *instance);
bool        checkReceive        (MCP2515_instance *instance);
uint8_t     readRegister        (MCP2515_instance *instance, const MC2515_reg reg);
uint8_t     errorCountRX        (MCP2515_instance *instance);
uint8_t     errorCountTX        (MCP2515_instance *instance);
uint8_t     getErrorFlags       (MCP2515_instance *instance);
uint8_t     getInterrupts       (MCP2515_instance *instance);
uint8_t     getInterruptMask    (MCP2515_instance *instance);
uint8_t     getStatus           (MCP2515_instance *instance);

/* Helper Functions */
inline void startSPI            (MCP2515_instance *instance);
inline void endSPI              (MCP2515_instance *instance);

const struct TXBn_REGS TXB[N_TXBUFFERS] = {
    {MCP_TXB0CTRL, MCP_TXB0SIDH, MCP_TXB0DATA},
    {MCP_TXB1CTRL, MCP_TXB1SIDH, MCP_TXB1DATA},
    {MCP_TXB2CTRL, MCP_TXB2SIDH, MCP_TXB2DATA}
};

const struct RXBn_REGS RXB[N_RXBUFFERS] = {
    {MCP_RXB0CTRL, MCP_RXB0SIDH, MCP_RXB0DATA, CANINTF_RX0IF},
    {MCP_RXB1CTRL, MCP_RXB1SIDH, MCP_RXB1DATA, CANINTF_RX1IF}
};

init_MCP2515(MCP2515_instance *instance)
{
    spi_init            (instance->SPI_CHANNEL, instance->SPI_CLOCK);
    gpio_set_dir        (instance->CS_PIN,      GPIO_OUT);
    gpio_set_function   (instance->TX_PIN,      GPIO_FUNC_SPI);
    gpio_set_function   (instance->RX_PIN,      GPIO_FUNC_SPI);
    gpio_set_function   (instance->SCK_PIN,     GPIO_FUNC_SPI);
    spi_set_format      (instance->SPI_CHANNEL, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);

    gpio_init           (instance->CS_PIN);

    endSPI(instance);
}

MC2515_ERROR reset(MCP2515_instance *instance)
{
    startSPI(instance);

    uint8_t instruction = INSTRUCTION_RESET;
    spi_write_blocking(&(instance->SPI_CHANNEL), &instruction, 1);

    endSPI(instance);

    //Depends on oscillator & capacitors used
    sleep_ms(10);

    setRegisters    (instance, MCP_TXB0CTRL, zeros, 14);
    setRegisters    (instance, MCP_TXB1CTRL, zeros, 14);
    setRegisters    (instance, MCP_TXB2CTRL, zeros, 14);
    setRegister     (instance, MCP_RXB0CTRL, 0);
    setRegister     (instance, MCP_RXB1CTRL, 0);
    setRegister     (instance, MCP_CANINTE, 
                    CANINTF_RX0IF | CANINTF_RX1IF | 
                    CANINTF_ERRIF | CANINTF_MERRF);

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
    RXF filters[] = {RXF0, RXF1, RXF2, RXF3, RXF4, RXF5};
    for (int i=0; i<6; i++) {
        bool ext = (i == 1);
        MC2515_ERROR result = setFilter(filters[i], ext, 0);
        if (result != ERROR_OK) {
            return result;
        }
    }

    MASK masks[] = {MASK0, MASK1};
    for (int i=0; i<2; i++) {
        MC2515_ERROR result = setFilterMask(masks[i], true, 0);
        if (result != ERROR_OK) {
            return result;
        }
    }

    return ERROR_OK;
}

uint8_t readRegister(MCP2515_instance *instance, const MC2515_reg reg)
{
    uint8_t ret;
    /* Build read request on desired registry */
    uint8_t data[2] = {INSTRUCTION_READ, reg };

    startSPI(instance);

    /* Send request data over SPI */
    spi_write_blocking(&(instance->SPI_CHANNEL), data, 2);
    /* Read response data */
    spi_read_blocking (&(instance->SPI_CHANNEL), 0x00, &ret, 1);

    endSPI(instance);

    return ret;
}

void readRegisters(MCP2515_instance *instance, const MC2515_reg reg, uint8_t values[], const uint8_t data_length)
{
    startSPI();

    uint8_t data[2] = {
        INSTRUCTION_READ,
        reg
    };
    spi_write_blocking  (&(instance->SPI_CHANNEL), data, 2);
    spi_read_blocking   (&(instance->SPI_CHANNEL), 0x00, values, data_length);

    endSPI();
}

void setRegister(MCP2515_instance *instance, const MC2515_reg reg, const uint8_t value)
{
    startSPI();

    uint8_t data[3] = {
        INSTRUCTION_WRITE,
        reg,
        value
    };
    spi_write_blocking(&(instance->SPI_CHANNEL), data, 3);

    endSPI();
}

void setRegisters(MCP2515_instance *instance, const MC2515_reg reg, const uint8_t values[], const uint8_t n)
{
    startSPI();

    uint8_t data[2] = {
        INSTRUCTION_WRITE,
        reg
    };
    spi_write_blocking(&(instance->SPI_CHANNEL), data, 2);

    spi_write_blocking(&(instance->SPI_CHANNEL), values, n);

    endSPI();
}

void modifyRegister(MCP2515_instance *instance, const MC2515_reg reg, const uint8_t mask, const uint8_t data)
{
    startSPI(instance);

    uint8_t d[4] = {
        INSTRUCTION_BITMOD,
        reg,
        mask,
        data
    };

    spi_write_blocking(&(instance->SPI_CHANNEL), d, 4);

    endSPI(instance);
}

uint8_t getStatus(MCP2515_instance *instance)
{
    startSPI(instance);

    uint8_t instruction = INSTRUCTION_READ_STATUS;
    spi_write_blocking  (&(instance->SPI_CHANNEL), &instruction, 1);

    uint8_t ret;
    spi_read_blocking   (&(instance->SPI_CHANNEL), 0x00, &ret, 1);

    endSPI  (instance);

    return ret;
}

MC2515_ERROR setConfigMode(MCP2515_instance *instance)
{
    return setMode(instance, CANCTRL_REQOP_CONFIG);
}

MC2515_ERROR setListenOnlyMode(MCP2515_instance *instance)
{
    return setMode(instance, CANCTRL_REQOP_LISTENONLY);
}

MC2515_ERROR setSleepMode(MCP2515_instance *instance)
{
    return setMode(instance, CANCTRL_REQOP_SLEEP);
}

MC2515_ERROR setLoopbackMode(MCP2515_instance *instance)
{
    return setMode(instance, CANCTRL_REQOP_LOOPBACK);
}

MC2515_ERROR setNormalMode(MCP2515_instance *instance)
{
    return setMode(instance, CANCTRL_REQOP_NORMAL);
}

MC2515_ERROR setMode(MCP2515_instance *instance, const CANCTRL_REQOP_MODE mode)
{
    modifyRegister(instance, MCP_CANCTRL, CANCTRL_REQOP, mode);

    unsigned long endTime = to_ms_since_boot(get_absolute_time()) + 10;
    bool modeMatch = false;
    while (to_ms_since_boot(get_absolute_time()) < endTime) {
        uint8_t newmode = readRegister(MCP_CANSTAT);
        newmode &= CANSTAT_OPMOD;

        if (newmode == mode) {
            break;
        }
    }

    return modeMatch 
        ? ERROR_OK
        : ERROR_FAIL;
}

MC2515_ERROR setBitrate(const CAN_SPEED canSpeed)
{
    return setBitrate(canSpeed, MCP_16MHZ);
}

MC2515_ERROR setBitrate(const CAN_SPEED canSpeed, CAN_CLOCK canClock)
{
    MC2515_ERROR error = setConfigMode();
    if (error != ERROR_OK) {
        return error;
    }

    uint8_t set, cfg1, cfg2, cfg3;
    set = 1;
    switch (canClock)
    {
        case (MCP_8MHZ):
        switch (canSpeed)
        {
            case (CAN_5KBPS):                                               //   5KBPS
            cfg1 = MCP_8MHz_5kBPS_CFG1;
            cfg2 = MCP_8MHz_5kBPS_CFG2;
            cfg3 = MCP_8MHz_5kBPS_CFG3;
            break;

            case (CAN_10KBPS):                                              //  10KBPS
            cfg1 = MCP_8MHz_10kBPS_CFG1;
            cfg2 = MCP_8MHz_10kBPS_CFG2;
            cfg3 = MCP_8MHz_10kBPS_CFG3;
            break;

            case (CAN_20KBPS):                                              //  20KBPS
            cfg1 = MCP_8MHz_20kBPS_CFG1;
            cfg2 = MCP_8MHz_20kBPS_CFG2;
            cfg3 = MCP_8MHz_20kBPS_CFG3;
            break;

            case (CAN_31K25BPS):                                            //  31.25KBPS
            cfg1 = MCP_8MHz_31k25BPS_CFG1;
            cfg2 = MCP_8MHz_31k25BPS_CFG2;
            cfg3 = MCP_8MHz_31k25BPS_CFG3;
            break;

            case (CAN_33KBPS):                                              //  33.333KBPS
            cfg1 = MCP_8MHz_33k3BPS_CFG1;
            cfg2 = MCP_8MHz_33k3BPS_CFG2;
            cfg3 = MCP_8MHz_33k3BPS_CFG3;
            break;

            case (CAN_40KBPS):                                              //  40Kbps
            cfg1 = MCP_8MHz_40kBPS_CFG1;
            cfg2 = MCP_8MHz_40kBPS_CFG2;
            cfg3 = MCP_8MHz_40kBPS_CFG3;
            break;

            case (CAN_50KBPS):                                              //  50Kbps
            cfg1 = MCP_8MHz_50kBPS_CFG1;
            cfg2 = MCP_8MHz_50kBPS_CFG2;
            cfg3 = MCP_8MHz_50kBPS_CFG3;
            break;

            case (CAN_80KBPS):                                              //  80Kbps
            cfg1 = MCP_8MHz_80kBPS_CFG1;
            cfg2 = MCP_8MHz_80kBPS_CFG2;
            cfg3 = MCP_8MHz_80kBPS_CFG3;
            break;

            case (CAN_100KBPS):                                             // 100Kbps
            cfg1 = MCP_8MHz_100kBPS_CFG1;
            cfg2 = MCP_8MHz_100kBPS_CFG2;
            cfg3 = MCP_8MHz_100kBPS_CFG3;
            break;

            case (CAN_125KBPS):                                             // 125Kbps
            cfg1 = MCP_8MHz_125kBPS_CFG1;
            cfg2 = MCP_8MHz_125kBPS_CFG2;
            cfg3 = MCP_8MHz_125kBPS_CFG3;
            break;

            case (CAN_200KBPS):                                             // 200Kbps
            cfg1 = MCP_8MHz_200kBPS_CFG1;
            cfg2 = MCP_8MHz_200kBPS_CFG2;
            cfg3 = MCP_8MHz_200kBPS_CFG3;
            break;

            case (CAN_250KBPS):                                             // 250Kbps
            cfg1 = MCP_8MHz_250kBPS_CFG1;
            cfg2 = MCP_8MHz_250kBPS_CFG2;
            cfg3 = MCP_8MHz_250kBPS_CFG3;
            break;

            case (CAN_500KBPS):                                             // 500Kbps
            cfg1 = MCP_8MHz_500kBPS_CFG1;
            cfg2 = MCP_8MHz_500kBPS_CFG2;
            cfg3 = MCP_8MHz_500kBPS_CFG3;
            break;

            case (CAN_1000KBPS):                                            //   1Mbps
            cfg1 = MCP_8MHz_1000kBPS_CFG1;
            cfg2 = MCP_8MHz_1000kBPS_CFG2;
            cfg3 = MCP_8MHz_1000kBPS_CFG3;
            break;

            default:
            set = 0;
            break;
        }
        break;

        case (MCP_16MHZ):
        switch (canSpeed)
        {
            case (CAN_5KBPS):                                               //   5Kbps
            cfg1 = MCP_16MHz_5kBPS_CFG1;
            cfg2 = MCP_16MHz_5kBPS_CFG2;
            cfg3 = MCP_16MHz_5kBPS_CFG3;
            break;

            case (CAN_10KBPS):                                              //  10Kbps
            cfg1 = MCP_16MHz_10kBPS_CFG1;
            cfg2 = MCP_16MHz_10kBPS_CFG2;
            cfg3 = MCP_16MHz_10kBPS_CFG3;
            break;

            case (CAN_20KBPS):                                              //  20Kbps
            cfg1 = MCP_16MHz_20kBPS_CFG1;
            cfg2 = MCP_16MHz_20kBPS_CFG2;
            cfg3 = MCP_16MHz_20kBPS_CFG3;
            break;

            case (CAN_33KBPS):                                              //  33.333Kbps
            cfg1 = MCP_16MHz_33k3BPS_CFG1;
            cfg2 = MCP_16MHz_33k3BPS_CFG2;
            cfg3 = MCP_16MHz_33k3BPS_CFG3;
            break;

            case (CAN_40KBPS):                                              //  40Kbps
            cfg1 = MCP_16MHz_40kBPS_CFG1;
            cfg2 = MCP_16MHz_40kBPS_CFG2;
            cfg3 = MCP_16MHz_40kBPS_CFG3;
            break;

            case (CAN_50KBPS):                                              //  50Kbps
            cfg1 = MCP_16MHz_50kBPS_CFG1;
            cfg2 = MCP_16MHz_50kBPS_CFG2;
            cfg3 = MCP_16MHz_50kBPS_CFG3;
            break;

            case (CAN_80KBPS):                                              //  80Kbps
            cfg1 = MCP_16MHz_80kBPS_CFG1;
            cfg2 = MCP_16MHz_80kBPS_CFG2;
            cfg3 = MCP_16MHz_80kBPS_CFG3;
            break;

            case (CAN_83K3BPS):                                             //  83.333Kbps
            cfg1 = MCP_16MHz_83k3BPS_CFG1;
            cfg2 = MCP_16MHz_83k3BPS_CFG2;
            cfg3 = MCP_16MHz_83k3BPS_CFG3;
            break; 

            case (CAN_100KBPS):                                             // 100Kbps
            cfg1 = MCP_16MHz_100kBPS_CFG1;
            cfg2 = MCP_16MHz_100kBPS_CFG2;
            cfg3 = MCP_16MHz_100kBPS_CFG3;
            break;

            case (CAN_125KBPS):                                             // 125Kbps
            cfg1 = MCP_16MHz_125kBPS_CFG1;
            cfg2 = MCP_16MHz_125kBPS_CFG2;
            cfg3 = MCP_16MHz_125kBPS_CFG3;
            break;

            case (CAN_200KBPS):                                             // 200Kbps
            cfg1 = MCP_16MHz_200kBPS_CFG1;
            cfg2 = MCP_16MHz_200kBPS_CFG2;
            cfg3 = MCP_16MHz_200kBPS_CFG3;
            break;

            case (CAN_250KBPS):                                             // 250Kbps
            cfg1 = MCP_16MHz_250kBPS_CFG1;
            cfg2 = MCP_16MHz_250kBPS_CFG2;
            cfg3 = MCP_16MHz_250kBPS_CFG3;
            break;

            case (CAN_500KBPS):                                             // 500Kbps
            cfg1 = MCP_16MHz_500kBPS_CFG1;
            cfg2 = MCP_16MHz_500kBPS_CFG2;
            cfg3 = MCP_16MHz_500kBPS_CFG3;
            break;

            case (CAN_1000KBPS):                                            //   1Mbps
            cfg1 = MCP_16MHz_1000kBPS_CFG1;
            cfg2 = MCP_16MHz_1000kBPS_CFG2;
            cfg3 = MCP_16MHz_1000kBPS_CFG3;
            break;

            default:
            set = 0;
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
            set = 0;
            break;
        }
        break;

        default:
        set = 0;
        break;
    }

    if (set) {
        setRegister(MCP_CNF1, cfg1);
        setRegister(MCP_CNF2, cfg2);
        setRegister(MCP_CNF3, cfg3);
        return ERROR_OK;
    }
    else {
        return ERROR_FAIL;
    }
}

MC2515_ERROR setClkOut(const CAN_CLKOUT divisor)
{
    if (divisor == CLKOUT_DISABLE) {
	/* Turn off CLKEN */
	modifyRegister(MCP_CANCTRL, CANCTRL_CLKEN, 0x00);

	/* Turn on CLKOUT for SOF */
	modifyRegister(MCP_CNF3, CNF3_SOF, CNF3_SOF);
        return ERROR_OK;
    }

    /* Set the prescaler (CLKPRE) */
    modifyRegister(MCP_CANCTRL, CANCTRL_CLKPRE, divisor);

    /* Turn on CLKEN */
    modifyRegister(MCP_CANCTRL, CANCTRL_CLKEN, CANCTRL_CLKEN);

    /* Turn off CLKOUT for SOF */
    modifyRegister(MCP_CNF3, CNF3_SOF, 0x00);
    return ERROR_OK;
}

void prepareId(uint8_t *buffer, const bool ext, const uint32_t id)
{
    uint16_t canid = (uint16_t)(id & 0x0FFFF);

    if (ext) {
        buffer[MCP_EID0] = (uint8_t) (canid & 0xFF);
        buffer[MCP_EID8] = (uint8_t) (canid >> 8);
        canid = (uint16_t)(id >> 16);
        buffer[MCP_SIDL] = (uint8_t) (canid & 0x03);
        buffer[MCP_SIDL] += (uint8_t) ((canid & 0x1C) << 3);
        buffer[MCP_SIDL] |= TXB_EXIDE_MASK;
        buffer[MCP_SIDH] = (uint8_t) (canid >> 5);
    } else {
        buffer[MCP_SIDH] = (uint8_t) (canid >> 3);
        buffer[MCP_SIDL] = (uint8_t) ((canid & 0x07 ) << 5);
        buffer[MCP_EID0] = 0;
        buffer[MCP_EID8] = 0;
    }
}

MC2515_ERROR setFilterMask(const MASK mask, const bool ext, const uint32_t ulData)
{
    MC2515_ERROR res = setConfigMode();
    if (res != ERROR_OK) {
        return res;
    }
    
    uint8_t tbufdata[4];
    prepareId(tbufdata, ext, ulData);

    MC2515_reg reg;
    switch (mask) {
        case MASK0: reg = MCP_RXM0SIDH; break;
        case MASK1: reg = MCP_RXM1SIDH; break;
        default:
            return ERROR_FAIL;
    }

    setRegisters(reg, tbufdata, 4);
    
    return ERROR_OK;
}

MC2515_ERROR setFilter(const RXF num, const bool ext, const uint32_t ulData)
{
    MC2515_ERROR res = setConfigMode();
    if (res != ERROR_OK) {
        return res;
    }

    MC2515_reg reg;

    switch (num) {
        case RXF0: reg = MCP_RXF0SIDH; break;
        case RXF1: reg = MCP_RXF1SIDH; break;
        case RXF2: reg = MCP_RXF2SIDH; break;
        case RXF3: reg = MCP_RXF3SIDH; break;
        case RXF4: reg = MCP_RXF4SIDH; break;
        case RXF5: reg = MCP_RXF5SIDH; break;
        default:
            return ERROR_FAIL;
    }

    uint8_t tbufdata[4];
    prepareId(tbufdata, ext, ulData);
    setRegisters(reg, tbufdata, 4);

    return ERROR_OK;
}

MC2515_ERROR sendMessage(const TXBn txbn, const struct can_frame *frame)
{
    if (frame->can_dlc > CAN_MAX_DLEN) {
        return ERROR_FAILTX;
    }

    const struct TXBn_REGS *txbuf = &TXB[txbn];

    uint8_t data[13];

    bool ext = (frame->can_id & CAN_EFF_FLAG);
    bool rtr = (frame->can_id & CAN_RTR_FLAG);
    uint32_t id = (frame->can_id & (ext ? CAN_EFF_MASK : CAN_SFF_MASK));

    prepareId(data, ext, id);

    data[MCP_DLC] = rtr ? (frame->can_dlc | RTR_MASK) : frame->can_dlc;

    memcpy(&data[MCP_DATA], frame->data, frame->can_dlc);

    setRegisters(txbuf->SIDH, data, 5 + frame->can_dlc);

    modifyRegister(txbuf->CTRL, TXB_TXREQ, TXB_TXREQ);

    uint8_t ctrl = readRegister(txbuf->CTRL);
    if ((ctrl & (TXB_ABTF | TXB_MLOA | TXB_TXERR)) != 0) {
        return ERROR_FAILTX;
    }
    return ERROR_OK;
}

MC2515_ERROR sendMessage(const struct can_frame *frame)
{
    if (frame->can_dlc > CAN_MAX_DLEN) {
        return ERROR_FAILTX;
    }

    TXBn txBuffers[N_TXBUFFERS] = {TXB0, TXB1, TXB2};

    for (int i=0; i<N_TXBUFFERS; i++) {
        const struct TXBn_REGS *txbuf = &TXB[txBuffers[i]];
        uint8_t ctrlval = readRegister(txbuf->CTRL);
        if ( (ctrlval & TXB_TXREQ) == 0 ) {
            return sendMessage(txBuffers[i], frame);
        }
    }

    return ERROR_ALLTXBUSY;
}

MC2515_ERROR readMessage(MCP2515_instance *instance, const RXBn rxbn, struct can_frame *frame)
{
    const struct RXBn_REGS *rxb = &RXB[rxbn];

    uint8_t tbufdata[5];

    readRegisters(instance, rxb->SIDH, tbufdata, 5u);
 
    uint32_t id = (tbufdata[MCP_SIDH] << 3u) + (tbufdata[MCP_SIDL] >> 5u);

    if (TXB_EXIDE_MASK == (tbufdata[MCP_SIDL] & TXB_EXIDE_MASK)) 
    {
        id  = (id << 2) + (tbufdata[MCP_SIDL] & 0b11 );
        id  = (id << 8) + (tbufdata[MCP_EID8]        );
        id  = (id << 8) + (tbufdata[MCP_EID0]        );
        id |= CAN_EFF_FLAG;
    }

    uint8_t dlc = (tbufdata[MCP_DLC] & DLC_MASK);
    if (dlc > CAN_MAX_DLEN)
    {
        return ERROR_FAIL;
    }

    uint8_t ctrl = readRegister(instance, rxb->CTRL);
    if (ctrl & RXBnCTRL_RTR) 
    {
        id |= CAN_RTR_FLAG;
    }

    frame->can_id  = id;
    frame->can_dlc = dlc;

    readRegisters (instance, rxb->DATA,   frame->data,        dlc);
    modifyRegister(instance, MCP_CANINTF, rxb->CANINTF_RXnIF, 0  );

    return ERROR_OK;
}

MC2515_ERROR    readMessage      (MCP2515_instance *instance, struct can_frame *frame)
{
    MC2515_ERROR rc;
    uint8_t stat = getStatus(instance);

    if(stat & STAT_RX0IF)
    {
        rc = readMessage(RXB0, frame);
    }
    else
    if(stat & STAT_RX1IF)
    {
        rc = readMessage(RXB1, frame);
    }
    else
    {
        rc = ERROR_NOMSG;
    }

    return rc;
}

bool            checkReceive     (MCP2515_instance *instance)
{
    bool retVal;
    uint8_t res = getStatus(instance);

    if ( res & STAT_RXIF_MASK )
    {
        return true;
    }
    else
    {
        return false;
    }

    return retVal;
}

bool            checkError       (MCP2515_instance *instance)
{
    bool retVal;
    uint8_t eflg = getErrorFlags(instance);

    if ( eflg & EFLG_ERRORMASK ) {
        retVal = true;
    } 
    else 
    {
        retVal = false;
    }

    return retVal;
}

uint8_t         getErrorFlags    (MCP2515_instance *instance)
{
    return readRegister(instance, MCP_EFLG);
}

void            clearRXnOVRFlags (MCP2515_instance *instance)
{
	modifyRegister(instance, MCP_EFLG, EFLG_RX0OVR | EFLG_RX1OVR, 0);
}

uint8_t         getInterrupts    (MCP2515_instance *instance)
{
    return readRegister(instance, MCP_CANINTF);
}

void            clearInterrupts  (MCP2515_instance *instance)
{
    setRegister(instance, MCP_CANINTF, 0);
}

uint8_t         getInterruptMask (MCP2515_instance *instance)
{
    return readRegister(instance, MCP_CANINTE);
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
    return readRegister(instance, MCP_REC);
}

uint8_t         errorCountTX     (MCP2515_instance *instance)
{
    return readRegister(instance, MCP_TEC);
}

inline void     startSPI         (MCP2515_instance *instance)
{
    asm volatile("nop \n nop \n nop");
    gpio_put(instance->CS_PIN, 0);
    asm volatile("nop \n nop \n nop");
}

inline void     endSPI           (MCP2515_instance *instance)
{
    asm volatile("nop \n nop \n nop");
    gpio_put(instance->CS_PIN, 1);
    asm volatile("nop \n nop \n nop");
}
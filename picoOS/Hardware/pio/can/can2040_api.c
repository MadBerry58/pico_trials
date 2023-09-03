#include "can2040_api.h"
#include "can2040.h"


#define TX_BUFFER_SIZE  16u
#define TX_MSG_BURST     4u /* Number of TX messages processed per cycle */
#define RX_BUFFER_SIZE  16u
#define TX_MSG_BURST     4u /* Number of RX messages processed per cycle */

#define CAN_PIO_BLOCK    0u
#define CAN_RX           4u
#define CAN_TX           5u

/* Helper function definitions */
static inline uint8_t dataToCAN(uint32_t *data, struct can2040_msg *msg);
static inline uint8_t CANtoData(uint32_t *data, struct can2040_msg *msg);

static struct can2040_msg txBuffer[TX_BUFFER_SIZE];
static uint8_t txBufferIndex;

static struct can2040_msg rxBuffer[RX_BUFFER_SIZE];
static uint8_t rxBufferIndex;

uint32_t sys_clock = 125000000, bitrate = 500000;
static struct can2040 cbus;

/**
 * @brief Notification callback given to the CAN state mechine.
 *        Callback will be invoked when a message has been sent, received or an error has arrised
 * 
 * @param cd        CAN SM data structure
 * @param notify    Callback notification time
 * @param msg       Sent/Received message container
 * @return          None
 */
static void can2040_cb(struct can2040 *cd, uint32_t notify, struct can2040_msg *msg)
{
    switch(notify)
    {
        case CAN2040_NOTIFY_RX:
        /* Event indicates a message has been successfully read. 
        The message contents will be in the msg parameter. */
        
        /* Check if the message is meant for the current node */
        /* If yes, copy message into canMsgBuffer */
        
        break;

        case CAN2040_NOTIFY_TX:
        /* Event indicates a message has been successfully transmitted on the CAN bus. 
        The transmitted message contents will be in the msg parameter. */

        /* Check if the message is the same as the source message */

        break;

        case CAN2040_NOTIFY_ERROR:
        /* A CAN2040_NOTIFY_ERROR event indicates that the internal receive buffers 
        have overflowed and that some number of CAN bus messages may have been lost. 
        The msg parameter will point to an allocated but otherwise 
        empty struct can2040_msg in this event. */

        /* Handle transmission error */

        break;

        default:

        break;
    }
}

/* Callback wrapper used to remove the need for an argument */
static void PIO0_IRQHandler(void)
{
    can2040_pio_irq_handler(&cbus);
}

init_can2040_api()
{
    // Setup canbus
    can2040_setup(&cbus, CAN_PIO_BLOCK);
    can2040_callback_config(&cbus, can2040_cb);

    // Enable irqs
    irq_set_exclusive_handler(PIO0_IRQ_0_IRQn, PIO0_IRQHandler);
    NVIC_SetPriority(PIO0_IRQ_0_IRQn, 1);
    NVIC_EnableIRQ(PIO0_IRQ_0_IRQn);

    txBufferIndex = 0u;
    rxBufferIndex = 0u;

    // Start canbus
    can2040_start(&cbus, sys_clock, bitrate, CAN_RX, CAN_TX);
}

run_can2040_api_processMessages()
{
    /* Parse messages present in the RX and TX buffers */

    /* TX_Buffer */
    if(
        (0u < txBufferIndex) &&
        (can2040_check_transmit(&cbus))
    )
    {/* Message present in the tx buffer */
        can2040_transmit(&cbus, &(txBuffer[txBufferIndex]));
        --txBufferIndex;
    }
    else
    {
        /* 
        No messages in the tx buffer or
        the transmitter is busy
        */
    }

    if(0u < rxBufferIndex)
    {/* Message present in the rx buffer */

    }
    else
    {/* No messages in the rx buffer */
        
    }
}

/* Helper functions */
static inline uint8_t dataToCAN(uint32_t *data, struct can2040_msg *msg)
{
    uint8_t retVal = 0u;

    return retVal;
}
static inline uint8_t CANtoData(uint32_t *data, struct can2040_msg *msg)
{
    uint8_t retVal = 0u;

    return retVal;
}
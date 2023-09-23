#ifndef DMA_CFG_H
#define DMA_CFG_H

/* Compile-time DMA configuration registers */
#include <stdio.h>
#include "hardware/dma.h"

/* DMA 32bit control register structure: (redefined SDK bit values for generalized use) */
    // 0x80000000 [31]    : AHB_ERROR (0): Logical OR of the READ_ERROR and WRITE_ERROR flags. The channel
    //                      halts when it encounters any bus error, and always raises its
    //                      channel IRQ flag.
    #define DMA_AHB_ERROR     _u(0x80000000)

    // 0x40000000 [30]    : READ_ERROR (0): If 1, the channel received a read bus error. Write one to
    //                      clear.
    //                      READ_ADDR shows the approximate address where the bus error was
    //                      encountered (will not be earlier, or more than 3 transfers
    //                      later)
    #define DMA_READ_ERROR    _u(0x40000000)

    // 0x20000000 [29]    : WRITE_ERROR (0): If 1, the channel received a write bus error. Write one to
    //                      clear.
    //                      WRITE_ADDR shows the approximate address where the bus error
    //                      was encountered (will not be earlier, or more than 5 transfers
    //                      later)
    #define DMA_WRITE_ERROR   _u(0x20000000)

    // 0x01000000 [24]    : BUSY (0): This flag goes high when the channel starts a new transfer
    //                      sequence, and low when the last transfer of that sequence
    //                      completes. Clearing EN while BUSY is high pauses the channel,
    //                      and BUSY will stay high while paused.
    //      
    //                      To terminate a sequence early (and clear the BUSY flag), see
    //                      CHAN_ABORT.
    #define DMA_TRIG_BUSY   _u(0x01000000)

    // 0x00800000 [23]    : SNIFF_EN (0): If 1, this channel's data transfers are visible to the sniff
    //                      hardware, and each transfer will advance the state of the
    //                      checksum. This only applies if the sniff hardware is enabled,
    //                      and has this channel selected.
    //      
    //                      This allows checksum to be enabled or disabled on a
    //                      per-control- block basis.
    #define DMA_SNIFF_EN   _u(0x00800000)

    // 0x00400000 [22]    : BSWAP (0): Apply byte-swap transformation to DMA data.
    //                      For byte data, this has no effect. For halfword data, the two
    //                      bytes of each halfword are swapped. For word data, the four
    //                      bytes of each word are swapped to reverse order.
    #define DMA_BSWAP   _u(0x00400000)

    // 0x00200000 [21]    : IRQ_QUIET (0): In QUIET mode, the channel does not generate IRQs at the end of
    //                      every transfer block. Instead, an IRQ is raised when NULL is
    //                      written to a trigger register, indicating the end of a control
    //                      block chain.
    //      
    //                      This reduces the number of interrupts to be serviced by the CPU
    //                      when transferring a DMA chain of many small control blocks.
    #define DMA_IRQ_QUIET   _u(0x00200000)
    
    // 0x001f8000 [20:15] : TREQ_SEL (0): Select a Transfer Request signal.
    //                      The channel uses the transfer request signal to pace its data
    //                      transfer rate. Sources for TREQ signals are internal (TIMERS)
    //                      or external (DREQ, a Data Request from the system).
    //                      0x0 to 0x3a -> select DREQ n as TREQ
    //                      0x3b -> Select Timer 0 as TREQ
    //                      0x3c -> Select Timer 1 as TREQ
    //                      0x3d -> Select Timer 2 as TREQ (Optional)
    //                      0x3e -> Select Timer 3 as TREQ (Optional)
    //                      0x3f -> Permanent request, for unpaced transfers.
    #define DMA_TREQ_SEL   _u(0x001f8000)
    #define DMA_TREQ_SEL_LSHIFT (15u)
    
    // 0x00007800 [14:11] : CHAIN_TO (0): When this channel completes, it will trigger the channel
    //                      indicated by CHAIN_TO. Disable by setting CHAIN_TO = _(this
    //                      channel)_.
    #define DMA_CHAIN_TO   _u(0x00007800)

    // 0x00000400 [10]    : RING_SEL (0): Select whether RING_SIZE applies to read or write addresses.
    //                      If 0, read addresses are wrapped on a (1 << RING_SIZE)
    //                      boundary. If 1, write addresses are wrapped.
    #define DMA_RING_SEL   _u(0x00000400)

    // 0x000003c0 [9:6]   : RING_SIZE (0): Size of address wrap region. If 0, don't wrap. For values n >
    //                      0, only the lower n bits of the address will change. This wraps
    //                      the address on a (1 << n) byte boundary, facilitating access to
    //                      naturally-aligned ring buffers.
    //      
    //                      Ring sizes between 2 and 32768 bytes are possible. This can
    //                      apply to either read or write addresses, based on value of
    //                      RING_SEL.
    //                      0x0 -> RING_NONE
    #define DMA_RING_SIZE    _u(0x000003c0)
    #define DMA_RING_SIZE_LSHIFT (6u)

    // 0x00000020 [5]     : INCR_WRITE (0): If 1, the write address increments with each transfer.If 0,
    //                      each write is directed to the same, initial address.
    //
    //                      Generally this should be disabled for memory-to-peripheral
    //                      transfers.
    #define DMA_INCR_WRITE   _u(0x00000020)
    // 0x00000010 [4]     : INCR_READ (0): If 1, the read address increments with each transfer
    //                      If 1, the read address increments with each transfer. If 0,
    //                      each read is directed to the same, initial address.
    //
    //                      Generally this should be disabled for peripheral-to-memory
    //                      transfers.
    #define DMA_INCR_READ   _u(0x00000010)
    // 0x0000000c [3:2]   : DATA_SIZE (0): Set the size of each bus transfer (byte/halfword/word)
    //                      Set the size of each bus transfer (byte/halfword/word).
    //                      READ_ADDR and WRITE_ADDR advance by this amount (1/2/4 bytes)
    //                      with each transfer.
    //                      0x0 -> SIZE_BYTE
    //                      0x1 -> SIZE_HALFWORD
    //                      0x2 -> SIZE_WORD
    #define DMA_DATA_SIZE       _u(0x0000000c)
    #define DMA_DATA_SIZE_LSHIFT (2u)

    // 0x00000002 [1]     : HIGH_PRIORITY gives a channel preferential treatment in issue
    //                      scheduling: in each scheduling round, all high priority
    //                      channels are considered first, and then only a single low
    //                      priority channel, before returning to the high priority
    //                      channels.
    //                      This only affects the order in which the DMA schedules
    //                      channels. The DMA's bus priority is not changed. If the DMA is
    //                      not saturated then a low priority channel will see no loss of
    //                      throughput.
    #define DMA_HIGH_PRIORITY   _u(0x00000002)
    // 0x00000001 [0]     : EN (0): DMA Channel Enable
    //                      When 1, the channel will respond to triggering events, which
    //                      will cause it to become BUSY and start transferring data. When
    //                      0, the channel will ignore triggers, stop issuing transfers,
    //                      and pause the current transfer sequence (i.e. BUSY will remain
    //                      high if already high)
    #define DMA_EN              _u(0x00000001)



/* DMA configuration templates
    Each template is generated at compile time, reducing runtime load.
    Each configuration takes 4 bytes (32bits)
    Structure is not portable, but then again, it is made specifically for the pico DMA
*/
typedef struct {
    uint8_t channel_enabled         :1; //[0]
    uint8_t high_priority           :1; //[1]
    uint8_t data_size               :2; //[3-2]
    uint8_t increment_read_adress   :1; //[4]
    uint8_t increment_write_adress  :1; //[5]
    uint8_t ring_size               :4; //[9-6]
    uint8_t read_write_ring         :1; //[10]
    uint8_t chain_to                :4; //[14-11]
    uint8_t TREQ_select             :6; //[20-15]
    uint8_t irq_quiet               :1; //[21]
    uint8_t byte_swap               :1; //[22]
    uint8_t sniff_enabled           :1; //[23]
    uint8_t dma_busy                :1; //[24]
    uint8_t RESERVED                :4; //[28-25]
    uint8_t WRITE_ERROR             :1; //[29]
    uint8_t READ_ERROR              :1; //[30]
    uint8_t AHB_ERROR               :1; //[31]
} dma_channel_bitwise_config;

typedef struct
{
    dma_channel_config config;
    uint32_t *readSource;
    uint32_t *writeDestination;
    uint32_t  dataCount;
} dmaTemplate_t;

/* Data sequence is transfered all at once, with IRQ being generated at the end */
// dmaTemplate_t bulkData_quiet = 
// { 
//     .config =   {0x00000000 | 
//                     (
//                         DMA_INCR_WRITE  |
//                         DMA_INCR_READ   |
//                         DMA_DATA_SIZE   |
//                         DMA_HIGH_PRIORITY
//                     )
//                 },
//     .readSource = 0u,
//     .writeDestination = 0u,
//     .dataCount = 0u
// };


/* Data transfers sequences are spaced with null triggers in order to generate IRQs periodically */
// dma_channel_config bulkData_segmented_ctrl = { 0x00000000 | 
//     (
//         (16u << DMA_RING_SIZE_LSHIFT) | //wrap around 4 configuration registers
//         DMA_RING_SEL    |
//         DMA_INCR_WRITE  |
//         DMA_INCR_READ   |
//         DMA_DATA_SIZE   |
//         DMA_HIGH_PRIORITY
//     )
// };

// dma_channel_config bulkData_segmented_data = { 0x00000000 | 
//     (
//         DMA_INCR_WRITE  |
//         DMA_INCR_READ   |
//         DMA_DATA_SIZE   |
//         DMA_HIGH_PRIORITY
//         // DMA_CHAIN_TO - dma chain has to be set after knowing the control channel ID
//     )

// /* add adress list template for periodic interrupts */
// };


/* Peripheral handler configurations */
///TODO: Module buffers must be defined at compile time
///TODO: Define ADC buffer size
// dma_channel_config adc_dreq_handler = { 0x00000000 | 
//     (
//         DMA_INCR_WRITE  |
//         (8u << DMA_RING_SIZE_LSHIFT) |  //circular buffer composed of a 8 byte adress wrap
//         (DREQ_ADC << DMA_TREQ_SEL_LSHIFT )    //adc data pacing 
//     )
// };

///TODO: find a way to properly expose the dreq RX/TX functionality
// dma_channel_config pio_dreq_handler = { 0x00000000 | 
//     (
//         DMA_INCR_WRITE  |
//         (8u << DMA_RING_SIZE_LSHIFT) |  //circular buffer composed of a 8 byte adress wrap
//         (DREQ_ADC << DMA_TREQ_SEL_LSHIFT )    //adc data pacing 
//     )
// };

// dma_channel_config i2c_dreq_handler = { 0x00000000 | 
//     (
//         DMA_INCR_WRITE  |
//         DMA_INCR_READ   |
//         DMA_DATA_SIZE   |
//         DMA_HIGH_PRIORITY
//     )
// };

// dma_channel_config uart_dreq_handler = { 0x00000000 | 
//     (
//         DMA_INCR_WRITE  |
//         DMA_INCR_READ   |
//         DMA_DATA_SIZE   |
//         DMA_HIGH_PRIORITY
//     )
// };

#endif
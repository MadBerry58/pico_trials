/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/dma.h"
#include "ws2812.pio.h"
#include "ws2812.h"

/* Dedicate transfer channel for RGB SM */
static int dma_chan = -1;

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return  ((uint32_t) (0) << 24) |
            ((uint32_t) (g) << 16) |
            ((uint32_t) (r) << 8 ) |
            ((uint32_t) (b) << 0 ) ;
} 

ws2812_sm_error init_ws2812(ws2812_sm* sm_data) 
{
    //set_sys_clock_48();
    ///TODO: check if PIO SM clock needs explicit 48MHz initialization
    
    ///TODO: add explicit error values
    ws2812_sm_error retVal = SM_WS2812_E_OK;
    ///TODO: bind offset for pio size compile time checking
    uint8_t offset;

    if(pio_can_add_program(pio1, &ws2812_program))
    {
        offset = pio_add_program(pio1, &ws2812_program);
        ///TODO: find the advantages of having control over frequency
        ws2812_program_init(pio1, sm_data->smID, offset, sm_data->pin, 800000, false);

        ///TODO: create template DMA configuration
        /* Configure DMA channel */
        dma_chan = dma_claim_unused_channel(true);
        dma_channel_config c = dma_channel_get_default_config(dma_chan);
        /* Transfer 32 bits of RGBW data (8 LSB are 0 for the RGB version) */
        channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
        /* Increment read pixel values */
        channel_config_set_read_increment(&c, true);
        /* PIO0 will be always occupied by core0 CAN. PIO1 TX numbers from 0 to 3, depend on sm number */
        /* Pace the data transfer for the receiving SM */
        channel_config_set_dreq(&c, DREQ_PIO1_TX0 + sm_data->smID);
        /* Always write to the same SM RX FIFO */
        channel_config_set_write_increment(&c, false);

        ///INFO: given a need for multiple low volume DMA operations, a dma control channel can be used to reprogram channels on the fly
        dma_channel_configure(
            dma_chan,
            &c,
            &pio1_hw->txf[sm_data->smID],  // Write address (only need to set this once)
            NULL,               // Don't provide a read address yet
            0,                  // As the same DMA channel will be used for multiple RGBs, allow for a different LED number
            false               // Don't start yet
        );
    }
    else
    {
        retVal = SM_WS2812_E_PIO_PROGRAM;
    }

    return retVal;
}

void ws2812_loadPattern(int sm, uint32_t *pattern, uint16_t pixelNumber)
{
    ///TODO: add handling for transfer in progress cases
    /* Dedicate DMA channels */
    dma_channel_set_read_addr   (dma_chan, pattern,             false);
    dma_channel_set_write_addr  (dma_chan, &pio1_hw->txf[sm],   false);
    dma_channel_set_trans_count (dma_chan, pixelNumber,         true );
    // pio_sm_put_blocking(pio, sm, pattern[i]);
}
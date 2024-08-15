#ifndef CAN_SM_API_H
#define CAN_SM_API_H

#include "../../../SystemServices/ErrorHandling/ErrorCodes.h"
#include "../../Hardware/peripherals/spi_drivers/MCP2515_can/MCP2515_can.h"
#include "../IPC/ipc.h"

/**
 * @brief Initialize the SPI peripheral and MCP2515 module
 * 
 * @param canInterface Structure containing the CAN bus interface data
 */
void init_CAN_Hardware  (CanIf_t *canInterface);

/**
 * @brief Read the status of the MCP2515 module
 * 
 * @param canInterface Structure containing the CAN bus interface data
 */
void update_HW_data     (CanIf_t *canInterface);

/**
 * @brief Read the received CAN frames
 * 
 * @param canInterface Structure containing the CAN bus interface data
 */
void receiveFrames      (CanIf_t *canInterface);

/**
 * @brief Send the updated CAN frames
 * 
 * @param canInterface Structure containing the CAN bus interface data
 */
void transmitFrames     (CanIf_t *canInterface);

/* Transition checks */

/**
 * @brief   Check if any new CAN frame is present in the MCP2515 Rx buffers
 * 
 * @param   canInterface 
 * @return  true 
 * @return  false 
 */
bool framesReceived     (CanIf_t *canInterface);

/**
 * @brief   Check if CAN frame transmission is required
 * 
 * @param   canInterface 
 * @return  true 
 * @return  false 
 */
bool transmitRequired   (CanIf_t *canInterface);

#endif
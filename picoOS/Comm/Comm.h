#ifndef COMM_H
#define COMM_H

#include <stdio.h>
#include "pico/stdlib.h"

#include "commSM/commSM.h"
#include "../SystemServices/ErrorHandling/ErrorCodes.h"
#include "../Hardware/peripherals/spi_drivers/MCP2515_can/MCP2515_can.h"
/******************************************************************/
/****************** CAN specific structures ***********************/

typedef struct
{
  can_frame frame;
  uint16_t  updateTimeMS;
  uint16_t  nextUpdate;
} NodeTxFrameData;

typedef struct
{
  can_frame frame;
  uint16_t  timeoutMS;
  uint16_t  nextExpectedUpdate;
} NodeRxFrameData;

/****************** CAN specific structures ***********************/
/******************************************************************/

Errors_OS_e init_Comms  ();

/* Network interfaces */
bool    network_connected();

uint8_t network_connect (uint8_t  nodeType,      uint8_t  nodeID);
uint8_t network_send    (uint8_t *message,       uint8_t  messageLength);
uint8_t network_read    (uint8_t *messageBuffer, uint8_t *messageSize);


uint8_t network_send_canFrame(const can_frame *frameBuffer);
uint8_t network_read_canFrame(can_frame *frameBuffer);

uint8_t network_processMessages(NodeTxFrameData txList, NodeRxFrameData rxList);

/* Internal communication interfaces */
uint8_t port_read       ();
uint8_t port_write      ();

#endif
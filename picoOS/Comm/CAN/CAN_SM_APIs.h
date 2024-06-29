#ifndef CAN_SM_API_H
#define CAN_SM_API_H

#include "../../../SystemServices/ErrorHandling/ErrorCodes.h"
#include "../../Hardware/peripherals/spi_drivers/MCP2515_can/MCP2515_can.h"
#include "../IPC/ipc.h"

typedef struct {
    can_frame       canFrame;

    void           *frameRxCallback;

    Rxframe_IPC    *IPC_variables;
    uint8_t         frameSignalNo;
} canIf_Rxframe;

void init_CAN_Hardware  (void);
void update_HW_data     (void);

bool processRequest     (uint8_t);


/* Transition checks */
bool framesReceived     (void);
bool transmitRequired   (void);

#endif
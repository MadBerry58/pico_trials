#ifndef OS_NETWORK_MSG_TYPES_H
#define OS_NETWORK_MSG_TYPES_H

/******************************************************************/
/****************** CAN specific definitions **********************/

/* Frame types */
typedef enum
{
  FRAME_TYPE_SYSTEM_DATA_UPDATE , /* Periodic system wide data update, <e.g. Real time clock resync, general status broadcasting> */
  FRAME_TYPE_NODE_DATA_UPDATE   , /* Periodic node specific data update, <e.g. Controller updates network of current pattern and temperatures> */
  FRAME_TYPE_SYSTEM_COMMAND     , /*  */
  FRAME_TYPE_NODE_COMMAND
} Frame_Type;


/* Node types */
typedef enum
{
  NODE_TYPE_OBSERVER,
  NODE_TYPE_LIGHT_SWITCH,
  NODE_TYPE_LIGHT_CONTROLLER,
  NODE_TYPE_RADIATOR_CONTROLLER,
  NODE_TYPE_WINDOW_CONTROLLER,
  NODE_TYPE_RESERVED0,
  NODE_TYPE_RESERVED1,
  NODE_TYPE_DEV,
} Node_Type;

/****************** CAN specific definitions **********************/ 
/******************************************************************/

typedef enum
{
    OS_M_CONFIRM,
    OS_M_SYNC_TIME,
    OS_M_UPDATE,
    OS_M_ID,
} osMessage_e;

#endif
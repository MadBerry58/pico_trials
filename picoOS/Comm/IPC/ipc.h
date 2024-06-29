#ifndef IPC_H
#define IPC_H
#include "../../../picoOS/picoOS.h"

typedef enum
{
    IPC_BOOL  ,
    IPC_UINT8 ,
    IPC_UINT16,
    IPC_UINT32,
    IPC_UINT64,
}   varType;

typedef struct
{
    void     *IPC_Variable;
    uint8_t   bitSize;
    uint8_t   bitPosition;
    varType   type;
    void     *signalCallback;
    uint32_t  updateTime;
}   Rxframe_IPC;

typedef struct
{
    void     *IPC_Variable;
    uint8_t   bitSize;
    uint32_t  bitPosition;
    varType   type;
    uint32_t  ownerFrameID;
}   Txframe_IPC;

void receiveFrames();

#endif
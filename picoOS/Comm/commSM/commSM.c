#include "commSM.h"
#include "pico/stdlib.h"

#include "commSM_functionality.h"

enum commSM_state_e
{
    COMM_SM_S_UNINITIALIZED,
    COMM_SM_S_INITIALIZED,
    COMM_SM_S_IDLE,
    COMM_SM_S_READING,
    COMM_SM_S_WRITING,
    COMM_SM_S_REQUEST_RECEIVED,

    COMM_SM_S_FAULT
} 
commSM_state     = COMM_SM_S_UNINITIALIZED, 
commSM_state_old = COMM_SM_S_UNINITIALIZED;

uint8_t SM_request  = 0;

CommSM_Error commSM_init(void)
{
    CommSM_Error retVal = COMM_SM_E_OK;
    

    /* check if hardware is initialized - initialize int pin with dma handler

    check if CAN hardware is connected

    broadcast identification frame

    if(broadcast response is received)
        networkStatus = connected
    */

   return retVal;
}

CommSM_Error commSM_run(void)
{
    CommSM_Error retVal = COMM_SM_E_OK;
    bool loop = true;
    while(loop)
    {
        switch(commSM_state)
        {
            case COMM_SM_S_UNINITIALIZED:               /* SM was not initialized before running */
                commSM_state = COMM_SM_S_FAULT;         /* Change SM state to FAULT */
                retVal = COMM_SM_E_UNINIT;              /* Indicate the uninitialized error code */
                loop = true;                            /* Allow SM to transition to fault state */
                break;

            case COMM_SM_S_INITIALIZED:                 /* SM was correctly initialized */
                commSM_state = COMM_SM_S_IDLE;     /* Change SM state to LISTENING */
                retVal = COMM_SM_E_OK;                  /* Indicate no error has occured */
                loop = true;                            /* Allow SM to transition to listening state */
                break;

            case COMM_SM_S_IDLE:                   /* SM is waiting for an incomming message */
                if(messageReceived())                   /* Check if any messages have been received */
                {
                    commSM_state = COMM_SM_S_READING;   /* Change SM state to READING */
                    loop = true;                        /* Allow SM to transition to reading state */
                }
                else
                if (sendingRequested())                 /* Check if any send requests have been received */
                {
                    commSM_state = COMM_SM_S_WRITING;   /* Change SM state to WRITING */
                    loop = true;                        /* Allow SM to transition to writing state */
                }
                else
                {
                    commSM_state = COMM_SM_S_IDLE; /* Remain in LISTENING state */
                    retVal = COMM_SM_E_OK;              /* Indicate no error has occured */
                    loop = false;                       /* Exit sm loop */
                }
                break;

            case COMM_SM_S_READING:                     /* SM is in the process of reading a message */
                if(readDataAvailable())                 /* Check if there is more data to read */
                {
                    readData();                         /* Read received data */
                    commSM_state = COMM_SM_S_READING;   /* Remain in READING state */
                    retVal = COMM_SM_E_READ;            /* Indicate no error has occured */
                    loop = false;                       /* Exit sm loop */
                }
                else
                if(readingError())                      /* Check if any errors occured while reading data */
                {
                    commSM_state = COMM_SM_S_FAULT;     /* Change SM state to FAULT */
                    retVal = COMM_SM_E_READ;            /* Indicate the read error code */
                    loop = true;                        /* Allow SM to transition to fault state */
                }
                else                                    /* Reading has finished successfully */
                {
                    commSM_state = COMM_SM_S_IDLE; /* Change SM state to LISTENING */
                    retVal = COMM_SM_E_READ;            /* Indicate no error has occured */
                    loop = false;                       /* Exit sm loop */
                }
                break;

            case COMM_SM_S_WRITING:                     /* SM is in the process of sending a message */
                if(writeDataLeft())                     /* Check if there is more data to send */
                {
                    writeData();
                    commSM_state = COMM_SM_S_WRITING;   /* Remain in SENDING state */
                    retVal = COMM_SM_E_OK;              /* Indicate no error has occured */
                    loop = false;                       /* Exit sm loop */
                }
                else
                if(writingError())                      /* Check if any errors occured while sending data */
                {
                    commSM_state = COMM_SM_S_FAULT;     /* Change SM state to FAULT */
                    retVal = COMM_SM_E_WRITE;           /* Indicate the write error code */
                    loop = true;                        /* Allow SM to transition to fault state */
                }
                else
                {
                    commSM_state = COMM_SM_S_IDLE; /* Change SM state to LISTENING */
                    retVal = COMM_SM_E_READ;            /* Indicate no error has occured */
                    loop = false;                       /* Exit sm loop */
                }
                break;

            case COMM_SM_S_REQUEST_RECEIVED:            /* User request has been received */
                if(processRequest(SM_request))          /* Request processing was successful */
                {
                    commSM_state = commSM_state_old;    /* Change SM state to last state */
                    retVal = COMM_SM_E_OK;              /* Indicate no error has occured */
                    loop = false;                       /* Exit sm loop */
                }
                else                                    /* Request processing was unsuccessful */
                {
                    commSM_state = COMM_SM_S_FAULT;     /* Change SM state to FAULT */
                    retVal = COMM_SM_E_UNKNOWN_REQUEST; /* Indicate the unknown request error code */
                    loop = true;                        /* Allow SM to transition to fault state */
                }
                break;

            case COMM_SM_S_FAULT:                       /* SM has transitioned into a safe fault state */
                notifyHost();
                commSM_state = COMM_SM_S_FAULT;         /* Remain in FAULT state */
                // retVal = COMM_SM_E_OK;               /* retVal is set by the state the SM is transitioning from */
                loop = false;                           /* Exit sm loop */
                break;
            
            default:
                commSM_state = COMM_SM_S_FAULT;         /* Remain in FAULT state */
                retVal = COMM_SM_E_UNKNOWN_STATE;       /* retVal is set by the state the SM is transitioning from */
                loop = true;                            /* Exit sm loop */
                break;
        }
    }

   return retVal;
}

CommSM_Error commSM_request(uint8_t request)
{
    SM_request = request;
    commSM_state_old = commSM_state;
    commSM_state = COMM_SM_S_REQUEST_RECEIVED;
}
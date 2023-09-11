#include "ErrorHandling.h"

Error_t errorBuffer[ERROR_BUFFER_SIZE];

uint8_t checkErrorBuffer()
{
    return 0u;
}

void registerError(Error_Source_e source, Error_Priority_e priority, uint32_t errorCode)
{

}

Error_Response_e handleError(Error_t error)
{
    Error_Response_e handledResponse = E_R_CONTINUE;

    
    return handledResponse;
}


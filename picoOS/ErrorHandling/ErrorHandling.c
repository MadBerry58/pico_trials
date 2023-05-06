#include "ErrorHandling.h"

Error_t errorBuffer[ERROR_BUFFER_SIZE];

Error_t checkErrorBuffer()
{
    return NULL;
}

void registerError(Error_Source source, Error_Priority priority, uint32_t errorCode)
{

}

Error_Response handleError(Error_t error)
{
    Error_Response handledResponse = E_R_CONTINUE;

    
    return handledResponse;
}


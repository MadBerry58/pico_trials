#include "ObserverSM.h"
#include "../Observer_config.h"

void core_ObserverNodeSM()
{    
    
    /* Main sequence */
    while (1) 
    {
        
    }
    
    /* IDEA: inter-component comm: data+update_notification
        -consume notification   - reader resets the update notification flag on reading data
        -cycle reset            - notification flags are reset at the end of the cycle
        -persist                - notification flag is reset by the emmiter when value remains unchanged
    */
}
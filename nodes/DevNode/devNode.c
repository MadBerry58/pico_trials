#include "devSM/devSM.h"
#include "../../picoOS/picoOS.h"

void main()
{
    /* Initialize base OS functionality */
    if(init_OS())
    {
        /* Handle initialization error */
    }

    /* Initialize node-specific functionality on core 1 */
    if(init_devNodeSM())
    {
        /*  */
    }

    /* initialize Node */

    /* prime Node (Core1) */

    /* start OS (Core0) */
        /* send Node start message */
}
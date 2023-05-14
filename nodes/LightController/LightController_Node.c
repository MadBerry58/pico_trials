#include "../../picoOS/picoOS.h"
#include "coldWhiteSM/coldWhiteSM.h"
#include "warmWhiteSM/warmWhiteSM.h"
#include "rgbSM/rgbSM.h"

void main()
{
    ///TODO: automate initialization/run using scheduler functionality
    /* Initialize OS */
    if(init_OS())
    {
        /* handle OS init errors */
    }

    /* Initialize local State machines */
    if(coldWhiteSM_init())
    {
        /* Handle SM initialization errors */
    }
    else
    if(warmWhiteSM_init())
    {
        /* Handle SM initialization errors */
    }
    else
    if(rgbSM_init())
    {
        /* Handle SM initialization errors */
    }
}
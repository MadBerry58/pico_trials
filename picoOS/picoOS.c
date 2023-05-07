
#include "picoOS.h"

/**
 * @brief picoOS core loop
 * 
 * 
 */
void main()
{
    stdio_init_all();
    
    /* Initialize  */
    if (watchdog_caused_reboot()) 
    {
        ///OPTIMIZATION: check the reboot cause. in case of impactless soft reboot, skip writing configs to peripherals
        printf("Rebooted by Watchdog!\n");
        ///TODO: parse error
    }
    else 
    {
        printf("Clean boot\n");
    }

    //Send Comm broadcast (Network ID + checksum)
    //Check for response
        //Handle errors

    /* Start Core1 */
        //Refresh watchdog
        //Start Core1

    /* Start Core0 scheduler */
        //Check comm
        //

            
}
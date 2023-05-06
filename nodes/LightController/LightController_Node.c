#include "LightController_Node.h"
#include "../../picoOS/picoOS.h"

int lightController_init()
{
    coldWhiteSM_init();
    warmWhiteSM_init();
    rgbSM_init();
    return 0ul;
}

int lightController_start()
{

    return 0ul;
}

int lightController_stop()
{

    return 0ul;
}
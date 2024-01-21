#ifndef LED_TESTER_SM_H
#define LED_TESTER_SM_H

#include <stdio.h>
#include "pico/stdlib.h"

/* Node SWC */
#include "nodeSWC/coldLedSM/coldLedSM.h"
#include "nodeSWC/controlLogicSM/controlLogicSM.h"
#include "nodeSWC/warmLedSM/warmLedSM.h"
#include "nodeSWC/pushButtonSM/pushButtonSM.h"
#include "nodeSWC/encoderSM/encoderSM.h"

void core_ledTesterNodeSM();

#endif
#include "servoControlSM.h"

#include "../../../picoOS/Templates/servoControl/servoControl.h"

servoObject radiatorServo = 
{
  .pin          = 13,
  .angleRange   = 360,
  .maxPulse_uS  = 2400,
  .minPulse_uS  = 500,
};


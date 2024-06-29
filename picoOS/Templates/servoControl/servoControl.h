#ifndef SERVO_CONTROL_H
#define SERVO_CONTROL_H

#include <stdbool.h>
#include "stdio.h"

typedef struct
{
  uint8_t   pin;
  uint16_t  angle;
  uint16_t  angleRange;
  bool      constrained;
  uint32_t  controlPeriod_uS;
  uint32_t  controlFrequencyHz;
  uint16_t  minPulse_uS;
  uint16_t  maxPulse_uS;

  uint8_t   pwmSliceNo;
  bool      pwmSliceChannel;
  float     divisor;
  uint16_t  pwmWrap;
  uint16_t  timePerAngle_uS;
  bool      pwmRunning;
} 
servoObject;

uint8_t init_servo  (servoObject *servo);

uint8_t set_servo   (servoObject *servo, uint8_t angle);

uint8_t deinit_servo(servoObject *servo);

#endif
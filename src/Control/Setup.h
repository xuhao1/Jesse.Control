#ifndef __JESSE_CONTROL_SETUP__H__
#define __JESSE_CONTROL_SETUP__H__

#include <Servo.h>
#include "config.h"
#include "motor.h"
#include "montior.h"
//Servo motors;
motor **motors;
void SetupServo();
void SetupSensors();
montior *moon;

#endif

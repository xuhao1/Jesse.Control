#ifndef __JESSE__CONTROL_MOTOR_H__
#define __JESSE__CONTROL_MOTOR_H__
#include <Servo.h>

class motor
{
public:    
    Servo ser;
    motor(int k);
    void calibrate();
    void setValue(float k);
};

#endif
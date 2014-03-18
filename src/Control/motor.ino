#include <Servo.h>
#include "motor.h"
#include "math.h"

motor::motor(int k)
{
    ser.attach(k);
    ser.write(0);
}
void motor::setValue(float k)
{
    ser.write(round(k*180));
    Serial.println(round(k*180));
}
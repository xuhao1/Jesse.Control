#include "Setup.h"
#include "config.h"
#include <Servo.h>

void SetupServo()
{
    motors=new motor*[4];
    motors[0]=new motor(4);
    motors[1]=new motor(5);
    motors[2]=new motor(6);
    motors[3]=new motor(7);
}

void SetupSensors()
{
    //TODO 初始化各路传感器
}

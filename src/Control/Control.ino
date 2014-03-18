#include "Setup.h"
#include "test.h"
#include <Servo.h>
Servo se0;
void setup()
{
    moon=new montior();
    SetupSensors();
    Serial.println("Setup Motors");
    SetupServo();
    Serial.println("Setup Finished");
    se0.attach(9);
}

void loop()
{
    moon->work(); 
    se0.write(100);
}

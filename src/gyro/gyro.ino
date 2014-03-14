#include <Wire.h>  
#include "gyro.h"  
  
Gyro gyro; 

void setup() {  
  Serial.begin(9600);  
  Wire.begin();  
  gyro.enableDefault();  
}  
  
void loop() {  
  gyro.read();  
  
  Serial.print("G ");  
  Serial.print("X: ");  
  Serial.print((int)gyro.g.x);  
  Serial.print(" Y: ");  
  Serial.print((int)gyro.g.y);  
  Serial.print(" Z: ");  
  Serial.println((int)gyro.g.z);  
  
  delay(1000);  
}
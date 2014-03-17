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
  Serial.print(gyro.g.x, 4); 
  Serial.print(" Y: ");  
  Serial.print(gyro.g.y, 4);  
  Serial.print(" Z: ");  
  Serial.println(gyro.g.z, 4);  
  
  delay(1000);  
}
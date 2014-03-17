#include <Wire.h>
#include "adxl.h"

Adxl adxl; 

void setup() {  
  Serial.begin(9600);  
  Wire.begin();  
  adxl.enable();  
}  
  
void loop() {  
  adxl.read();  
  
  Serial.print("A ");  
  Serial.print("X: ");  
  Serial.print((int)adxl.a.x);  
  Serial.print(" Y: ");  
  Serial.print((int)adxl.a.y);  
  Serial.print(" Z: ");  
  Serial.println((int)adxl.a.z);  
  
  delay(1000);  
}
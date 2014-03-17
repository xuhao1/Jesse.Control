#include <Wire.h>
#include "hmc.h"

HMC hmc;

void setup() {  
  Serial.begin(9600);  
  Wire.begin();  
  hmc.enabled();  
}  
  
void loop() {  
  hmc.read();  
  
  Serial.print("A ");  
  Serial.print("X: ");  
  Serial.print((int)hmc.h.x);  
  Serial.print(" Y: ");  
  Serial.print((int)hmc.h.y);  
  Serial.print(" Z: ");  
  Serial.println((int)hmc.h.z);  
  
  delay(1000);  
}
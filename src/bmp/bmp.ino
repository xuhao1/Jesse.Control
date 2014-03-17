#include <Wire.h>
#include "bmp.h"

BMP bmp; 

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  bmp.enabled();
}
 
void loop()
{
  bmp.read_t();
  bmp.read_p();

  Serial.print("Temperature: ");
  Serial.print(bmp.t, DEC);
  Serial.println(" *0.1 deg C");
  Serial.print("Pressure: ");
  Serial.print(bmp.p, DEC);
  Serial.println(" Pa");
  Serial.println();
  delay(1000);
}
 

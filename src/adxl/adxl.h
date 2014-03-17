#include <Wire.h>
#include <Arduino.h>
#include <math.h>                //Triaxial accelerometer

#define Register_ID 0
#define Register_2D 0x2D
#define Register_X0 0x32
#define Register_X1 0x33
#define Register_Y0 0x34
#define Register_Y1 0x35
#define Register_Z0 0x36
#define Register_Z1 0x37

#define ADXL_ADRESS ( 0xA7 >> 1 )

class Adxl
 {
 public:
 	    typedef struct vector  
        {  
            signed int x, y, z;  
        } vector;  
  
        vector a;

        void read (void);

        void enable (void);

        void writereg (byte reg, byte val);
 }; 

 void Adxl::enable (void)
 {
 	writereg(Register_2D, 0x08);  
 } 

 void Adxl::writereg(byte reg, byte val)
 {
 	Wire.beginTransmission(ADXL_ADRESS);
 	Wire.write(reg);
 	Wire.write(val);
 	Wire.endTransmission();
 }

 void Adxl::read(void)
 {
    Wire.beginTransmission(ADXL_ADRESS);   
    Wire.write(Register_X0 | (1 << 7));   
    Wire.endTransmission();  

    Wire.requestFrom(ADXL_ADRESS, 6); 

    while (Wire.available() < 6);  
  
    uint8_t xla = Wire.read();  
    uint8_t xha = Wire.read();  
    uint8_t yla = Wire.read();  
    uint8_t yha = Wire.read();  
    uint8_t zla = Wire.read();  
    uint8_t zha = Wire.read();  
  
    a.x = xha << 8 | xla;  
    a.y = yha << 8 | yla;  
    a.z = zha << 8 | zla;  
  }
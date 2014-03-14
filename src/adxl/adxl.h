#include <wire.h>
#include <Arduino.h>
#include <math.h>

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

 void Adxl::read (void)
 {
 	Wire.beginTransmission(Adxl_adress);
 	Wire
 }
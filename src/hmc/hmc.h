#include <Wire.h>
#include <Arduino.h>
#include <math.h> 

#define Register_A  0x00
#define Register_B  0x01
#define mode        0x02
#define X_MSB       0x03           // MSB is high, while LSB is low.
#define X_LSB		0x04
#define Z_MSB		0x05
#define Z_LSB		0x06  
#define Y_MSB       0x07
#define Y_LSB		0x08
#define status      0x09
#define match_A     0x0A
#define match_B		0x0B
#define match_C		0x0C

#define HMC_ADRESS  (0x3C >> 1)

class HMC
{
public:
	 typedef struct vector
	 {
	 	signed int x, y, z;
	 }vector;
	
	vector h;

	void read(void);

	void enabled(void);

	void writereg(byte reg, byte val); 
};

void HMC::enabled(void)
{
	writereg(mode, 0x00);
}

void HMC::writereg(byte reg, byte val)
{
	Wire.beginTransmission(HMC_ADRESS);
	Wire.write(reg);
	Wire.write(val);
	Wire.endTransmission();
}

void HMC::read(void)
{
	Wire.beginTransmission(HMC_ADRESS);
	Wire.write(X_MSB | 1 << 7);
	Wire.endTransmission();

	Wire.requestFrom(HMC_ADRESS, 6);

	while(Wire.available() < 6);

	uint8_t xha = Wire.read();  
    uint8_t xla = Wire.read();  
    uint8_t zha = Wire.read();  
    uint8_t zla = Wire.read();  
    uint8_t yha = Wire.read();  
    uint8_t yla = Wire.read();  
  
    h.x = xha << 8 | xla;  
    h.y = yha << 8 | yla;  
    h.z = zha << 8 | zla; 
}
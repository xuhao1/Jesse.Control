#include <Wire.h>
#include <Arduino.h>
#include <math.h>

#define BMP085_ADDRESS 0x77  // I2C address of BMP085
 
const unsigned char OSS = 0;  // Oversampling Setting

// Calibration values
int ac1;
int ac2;
int ac3;
unsigned int ac4;
unsigned int ac5;
unsigned int ac6;
int b1;
int b2;
int mb;
int mc;
int md;
 
 // b5 is calculated in bmp085GetTemperature(...), this variable is also used in bmp085GetPressure(...)
// so ...Temperature(...) must be called before ...Pressure(...).
long b5;

 class BMP
 {
 	public:
 		short t;
 		long  p;
 		
 		void enabled(void);

 		void read_t();
 		void read_p();

 		short GetTemperature(unsigned int ut);
 		long GetPressure(unsigned long up);

 		int ReadInt(unsigned char address);
 		char Read(unsigned char address);

 		unsigned long ReadUP();
 		unsigned int ReadUT();
 };
 
 void BMP::read_p()
 {
 	p = GetPressure(ReadUP()); 
 }

 void BMP::read_t()
 {
 	t = GetTemperature(ReadUT());
 }
// Stores all of the bmp085's calibration values into global variables
// Calibration values are required to calculate temp and pressure
// This function should be called at the beginning of the program
void BMP::enabled()
{
  ac1 = ReadInt(0xAA);
  ac2 = ReadInt(0xAC);
  ac3 = ReadInt(0xAE);
  ac4 = ReadInt(0xB0);
  ac5 = ReadInt(0xB2);
  ac6 = ReadInt(0xB4);
  b1 = ReadInt(0xB6);
  b2 = ReadInt(0xB8);
  mb = ReadInt(0xBA);
  mc = ReadInt(0xBC);
  md = ReadInt(0xBE);
}
short BMP::GetTemperature(unsigned int ut)
{
  long x1, x2;
 
  x1 = (((long)ut - (long)ac6)*(long)ac5) >> 15;
  x2 = ((long)mc << 11)/(x1 + md);
  b5 = x1 + x2;
 
  return ((b5 + 8)>>4); 
}
 
// Calculate pressure given up
// calibration values must be known
// b5 is also required so bmp085GetTemperature(...) must be called first.
// Value returned will be pressure in units of Pa.
long BMP::GetPressure(unsigned long up)
{
  long x1, x2, x3, b3, b6, p;
  unsigned long b4, b7;
 
  b6 = b5 - 4000;
  // Calculate B3
  x1 = (b2 * (b6 * b6)>>12)>>11;
  x2 = (ac2 * b6)>>11;
  x3 = x1 + x2;
  b3 = (((((long)ac1)*4 + x3)<<OSS) + 2)>>2;
 
  // Calculate B4
  x1 = (ac3 * b6)>>13;
  x2 = (b1 * ((b6 * b6)>>12))>>16;
  x3 = ((x1 + x2) + 2)>>2;
  b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;
 
  b7 = ((unsigned long)(up - b3) * (50000>>OSS));
  if (b7 < 0x80000000)
    p = (b7<<1)/b4;
  else
    p = (b7/b4)<<1;
   
  x1 = (p>>8) * (p>>8);
  x1 = (x1 * 3038)>>16;
  x2 = (-7357 * p)>>16;
  p += (x1 + x2 + 3791)>>4;
 
  return p;
}
 
// Read 1 byte from the BMP085 at 'address'
char BMP::Read(unsigned char address)
{
  unsigned char data;
 
  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
 
  Wire.requestFrom(BMP085_ADDRESS, 1);
  while(!Wire.available())
    ;
   
  return Wire.read();
}
 
// Read 2 bytes from the BMP085
// First byte will be from 'address'
// Second byte will be from 'address'+1
int BMP::ReadInt(unsigned char address)
{
  unsigned char msb, lsb;
 
  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(address);
  Wire.endTransmission();
 
  Wire.requestFrom(BMP085_ADDRESS, 2);
  while(Wire.available()<2)
    ;
  msb = Wire.read();
  lsb = Wire.read();
 
  return (int) msb<<8 | lsb;
}
 
// Read the uncompensated temperature value
unsigned int BMP::ReadUT()
{
  unsigned int ut;
 
  // Write 0x2E into Register 0xF4
  // This requests a temperature reading
  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(0xF4);
  Wire.write(0x2E);
  Wire.endTransmission();
 
  // Wait at least 4.5ms
  delay(5);
 
  // Read two bytes from registers 0xF6 and 0xF7
  ut = ReadInt(0xF6);
  return ut;
}
 
// Read the uncompensated pressure value
unsigned long BMP::ReadUP()
{
  unsigned char msb, lsb, xlsb;
  unsigned long up = 0;
 
  // Write 0x34+(OSS<<6) into register 0xF4
  // Request a pressure reading w/ oversampling setting
  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(0xF4);
  Wire.write(0x34 + (OSS<<6));
  Wire.endTransmission();
 
  // Wait for conversion, delay time dependent on OSS
  delay(2 + (3<<OSS));
 
  // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
  Wire.beginTransmission(BMP085_ADDRESS);
  Wire.write(0xF6);
  Wire.endTransmission();
  Wire.requestFrom(BMP085_ADDRESS, 3);
 
  // Wait for data to become available
  while(Wire.available() < 3)
    ;
  msb = Wire.read();
  lsb = Wire.read();
  xlsb = Wire.read();
 
  up = (((unsigned long) msb << 16) | ((unsigned long) lsb << 8) | (unsigned long) xlsb) >> (8-OSS);
 
  return up;
}
#include <Wire.h>
#include <math.h>
#include <Arduino.h>                 //Three-axis gyroscope

#define L3G4200D_WHO_AM_I      0x0F  

#define L3G4200D_CTRL_REG1     0x20  
#define L3G4200D_CTRL_REG2     0x21  
#define L3G4200D_CTRL_REG3     0x22  
#define L3G4200D_CTRL_REG4     0x23  
#define L3G4200D_CTRL_REG5     0x24  
#define L3G4200D_REFERENCE     0x25  
#define L3G4200D_OUT_TEMP      0x26  
#define L3G4200D_STATUS_REG    0x27  
  
#define L3G4200D_OUT_X_L       0x28  
#define L3G4200D_OUT_X_H       0x29  
#define L3G4200D_OUT_Y_L       0x2A  
#define L3G4200D_OUT_Y_H       0x2B  
#define L3G4200D_OUT_Z_L       0x2C  
#define L3G4200D_OUT_Z_H       0x2D  
  
#define L3G4200D_FIFO_CTRL_REG 0x2E  
#define L3G4200D_FIFO_SRC_REG  0x2F  
  
#define L3G4200D_INT1_CFG      0x30  
#define L3G4200D_INT1_SRC      0x31  
#define L3G4200D_INT1_THS_XH   0x32  
#define L3G4200D_INT1_THS_XL   0x33  
#define L3G4200D_INT1_THS_YH   0x34  
#define L3G4200D_INT1_THS_YL   0x35  
#define L3G4200D_INT1_THS_ZH   0x36  
#define L3G4200D_INT1_THS_ZL   0x37  
#define L3G4200D_INT1_DURATION 0x38  

#define GYR_ADDRESS (0xD2 >> 1)  

class Gyro  
{
    public:  
        typedef struct vector  
        {  
            float x, y, z;  
        } vector;  
  
        vector g; // gyro angular velocity reading
        
        void read (void);

        void enableDefault(void);

        void writeReg(byte reg, byte value);
        byte readReg(byte reg);

};

void Gyro::read()  
{  
    Wire.beginTransmission(GYR_ADDRESS);   
    Wire.write(L3G4200D_OUT_X_L | (1 << 7));   
    Wire.endTransmission();  
    Wire.requestFrom(GYR_ADDRESS, 6);   
    while (Wire.available() < 6);  
  
    uint8_t xla = Wire.read();  
    uint8_t xha = Wire.read();  
    uint8_t yla = Wire.read();  
    uint8_t yha = Wire.read();  
    uint8_t zla = Wire.read();  
    uint8_t zha = Wire.read();  
  
    g.x = (signed int)(xha << 8 | xla) * 0.00875;  
    g.y = (signed int)(yha << 8 | yla) * 0.00875;  
    g.z = (signed int)(zha << 8 | zla) * 0.00875;  
} 
// Turns on the L3G4200D's gyro and places it in normal mode.  
void Gyro::enableDefault(void)  
{  
    // 0x0F = 0b00001111  
    // Normal power mode, all axes enabled  
    writeReg(L3G4200D_CTRL_REG1, 0x0F);  
}  
  
// Writes a gyro register  
void Gyro::writeReg(byte reg, byte value)  
{  
    Wire.beginTransmission(GYR_ADDRESS);  
    Wire.write(reg);  
    Wire.write(value);  
    Wire.endTransmission();  
}  
  
// Reads a gyro register  
byte Gyro::readReg(byte reg)  
{  
    byte value;  
  
    Wire.beginTransmission(GYR_ADDRESS);  
    Wire.write(reg);  
    Wire.endTransmission();  
    Wire.requestFrom(GYR_ADDRESS, 1);  
    value = Wire.read();  
    Wire.endTransmission();  
  
    return value;  
}  
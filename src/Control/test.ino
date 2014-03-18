#include "test.h"
void TestMotors()
{
    //for(int j =0 ;j<4;j++)
    {
        for(float i=0;i<1;i+=0.01)
        {
            motors[0]->setValue(i);
            motors[1]->setValue(i);
            motors[2]->setValue(i);
            motors[3]->setValue(i);
            delay(10);
        }   
        motors[0]->setValue(0);
    }  
}

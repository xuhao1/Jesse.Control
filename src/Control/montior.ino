#include "montior.h"
#include "test.h"
#include "Setup.h"
#define DEBUG_MODE

montior::montior()
{
    sel.begin(9600);
    sel.println("Hi,I'm Jesse\n");
    sel.flush();
}
void montior::work()
{
    sel.flush();
    if(sel.available()>0)
    {
        int k=sel.read();
        #ifdef DEBUG_MODE
        sel.print(k);
        #endif
        if(k=='t')
        {
            sel.println("Starting Motor Test");
            TestMotors(); 
        }
        else if(k=='b')
        {
            sel.println("Cail Motor Big");
            motors[0]->setValue(1);
            motors[1]->setValue(1);
            motors[2]->setValue(1);
            motors[3]->setValue(1);
            delay(5);
            sel.println("Finish Motor Big");
        }

        sel.flush();
    }
}
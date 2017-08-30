/** Liest die analoge Spannung an einem Pin.
    Hier der Lichtsensor auf A1.
*/
#include "mbed.h"

AnalogIn licht( A1 );
DigitalOut led1 ( D10 );

int main()
{
    while   ( 1 )
    {
        if  ( licht.read() < 0.8f )          // in Prozent
            led1 = 1;
        else
            led1 = 0;
        wait ( 1.0 );
    }
}

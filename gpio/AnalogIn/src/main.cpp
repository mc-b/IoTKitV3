/** Liest die analoge Spannung an einem Pin.
    Hier das Poti an A0
*/
#include <mbed.h>

AnalogIn poti( PTC0 );
DigitalOut led1 ( D10 );

int main()
{
    while   ( 1 )
    {
        printf("Hall %4.2f\n", poti.read() );
        if  ( poti.read() < 0.5f )          // in Prozent
            led1 = 1;
        else
            led1 = 0;
            
        wait ( 1.0 );   
        //if  ( licht.read_u16() > 32767 )    // als short Ganzzahl
        //    ....;   
    }     
}
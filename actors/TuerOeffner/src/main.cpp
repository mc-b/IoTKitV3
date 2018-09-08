/** Tueroeffner Beispiel
    Tueroffner an den oberen zwei FET Pins enstecken.
*/ 
#include "mbed.h"

DigitalIn button( PTC13 , PullUp );
DigitalOut door( D5 );

int main()
{
    while ( 1 ) 
    {
        if  ( button == 0 )
        {
            door = 1;
            wait( 3.0 );
            door = 0;
        }
        wait( 0.2 );
    }
}

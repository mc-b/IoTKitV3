/** 3.1 Neues Programm mittels Assistenten erstellen
 *  Variante b: ohne Shield
*/

#include "mbed.h"

DigitalIn   button1( SW2 );         // Rechter Button auf Board
DigitalOut  led( LED1 );

int main()
{
    led = 1;                        // rot (RGB LED arbeiten mit inverter Logik 1 = OFF, 0 = ON)

    while ( true )
    {
        if  ( button1 == 0 )        // Button gedrueckt
            led = 0;
        else
            led = 1;
    }
}

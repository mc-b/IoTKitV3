/** 3.1 Neues Programm mittels Assistenten erstellen
 *  Variante b: ohne Shield
*/

#include "mbed.h"

DigitalIn   button1( USER_BUTTON );         // Rechter Button auf Board
DigitalOut  led( LED1 );

int main()
{
    led = 0;                        // auf Board und Shield auf D13, Normale Logik

    while ( true )
    {
        if  ( button1 == 0 )        // Button gedrueckt
            led = 1;
        else
            led = 0;
    }
}

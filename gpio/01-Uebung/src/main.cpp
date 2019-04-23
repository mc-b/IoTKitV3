/** 1. LED x Sekunden aufleuchten bei Tastendruck (if, wait)
*/
 
#include "mbed.h"
 
DigitalIn   button1( MBED_CONF_IOTKIT_BUTTON1 );        // User Button
DigitalOut  led( MBED_CONF_IOTKIT_LED1 );     			// 1. LED
 
int main()
{
    while ( true ) 
    {
        if  ( button1 == 0 )        // Button gedrueckt
        {
            led = 1;
            wait ( 3.0 );
            led = 0;
        }
    }
}

/** DigitalIn liest den Status eines Pins aus.
*/
#include "mbed.h"

DigitalIn button1( MBED_CONF_IOTKIT_BUTTON1, PullUp );
DigitalOut led1( MBED_CONF_IOTKIT_LED2 );

int main()
{
    while   ( 1 ) 
    {
        led1 = 0;
        if  ( button1 == 0 ) 
        {
            led1 = 1;
            wait( 1.0 );
        }

    }
}
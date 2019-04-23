/** Tueroeffner */

#include "mbed.h"

DigitalIn button1( MBED_CONF_IOTKIT_BUTTON1 );
DigitalOut mosfet( MBED_CONF_IOTKIT_MOSFET1 );
DigitalOut led( MBED_CONF_IOTKIT_LED1 );

int main()
{
    while   ( 1 ) 
    {
        led = 0;
        mosfet = 0;
        if  ( button1 == 0 ) 
        {
            led = 1;
            mosfet = 1;
            wait( 3.0 );
        }

    }
}
/** 4.4 Melodie visualisieren (for Verschachtelt, wait, Array's)
*/
#include "mbed.h"

DigitalOut led[] =  { DigitalOut( MBED_CONF_IOTKIT_LED1 ), DigitalOut( MBED_CONF_IOTKIT_LED2 ), DigitalOut( MBED_CONF_IOTKIT_LED3 ), DigitalOut( MBED_CONF_IOTKIT_LED4 ) };

int m[15][4] = {
                { 1, 0, 0, 1 },
                { 1, 1, 1, 1 },
                { 1, 1, 0, 0 },
                { 0, 1, 0, 1 },
                { 1, 1, 1, 1 },
                { 1, 1, 0, 1 },
                { 1, 0, 0, 1 },
                { 1, 1, 0, 1 },
                { 1, 0, 1, 1 },
                { 0, 0, 0, 1 },
                { 1, 0, 0, 1 },
                { 1, 1, 0, 0 },
                { 1, 0, 0, 1 },
                { 1, 0, 0, 1 },
                { 1, 0, 0, 1 }
            };
                

int main()
{
    while (true) 
    {
        // row
        for ( int r = 0; r < 15; r++ )
        {
            // column
            for ( int c = 0; c < 5; c++ )
                led[c] = m[r] [c];
            wait( 0.2 );
        }
    }
    

}

/** Pulsweitenmodulation
*/
#include "mbed.h"

PwmOut led( MBED_CONF_IOTKIT_LED4 );

int main()
{
    for ( float i  = 0.0; i < 1.0f; i += 0.01f )
    {
        led = i;
        wait    ( 0.1 );
    }
}
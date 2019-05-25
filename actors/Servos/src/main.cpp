#include "mbed.h"
#include "Servo.h"

Servo servo1( MBED_CONF_IOTKIT_SERVO1 );
Servo servo2( MBED_CONF_IOTKIT_SERVO2 );
Servo servo3( MBED_CONF_IOTKIT_SERVO3 );
Servo servo4( MBED_CONF_IOTKIT_SERVO4 );

int main()
{
    while (1) 
    {
        for ( float offset = 0.0f; offset < 1.0f; offset += 0.05f )
        {
            servo1.write( offset);
            servo2.write( offset);
            servo3.write( offset);
            servo4.write( offset);
            wait( 0.25f );
        }
        for ( float offset = 1.0f; offset > 0.0f; offset -= 0.05f )
        {
            servo1.write( offset);
            servo2.write( offset);
            servo3.write( offset);
            servo4.write( offset);
            wait( 0.25f );
        }        
    }
}

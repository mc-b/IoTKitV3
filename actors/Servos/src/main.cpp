#include "mbed.h"


PwmOut servo1( MBED_CONF_IOTKIT_SERVO1 );
PwmOut servo2( MBED_CONF_IOTKIT_SERVO2 );
PwmOut servo3( MBED_CONF_IOTKIT_SERVO3 );
PwmOut servo4( MBED_CONF_IOTKIT_SERVO4 );


int main()
{
    servo1.period(0.020);          // servo requires a 20ms period
    servo2.period(0.020);          // servo requires a 20ms period
    servo3.period(0.020);          // servo requires a 20ms period
    servo4.period(0.020);          // servo requires a 20ms period
    
    while (1) 
    {
        for(float offset=0.0; offset<0.001; offset+=0.0001) 
        {
            servo1.pulsewidth(0.001 + offset); // servo position determined by a pulsewidth between 1-2ms
            servo2.pulsewidth(0.001 + offset); // servo position determined by a pulsewidth between 1-2ms
            servo3.pulsewidth(0.001 + offset); // servo position determined by a pulsewidth between 1-2ms
            servo4.pulsewidth(0.001 + offset); // servo position determined by a pulsewidth between 1-2ms
            wait(0.25);
        }
        for(float offset=0.001; offset>0.000; offset-=0.0001) 
        {
            servo1.pulsewidth(0.001 + offset); // servo position determined by a pulsewidth between 1-2ms
            servo2.pulsewidth(0.001 + offset); // servo position determined by a pulsewidth between 1-2ms
            servo3.pulsewidth(0.001 + offset); // servo position determined by a pulsewidth between 1-2ms
            servo4.pulsewidth(0.001 + offset); // servo position determined by a pulsewidth between 1-2ms
            wait(0.25);
        }        
    }
}

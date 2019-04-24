/** Motor Beispiel
    Motor an den oberen 2 Pins einstecken.
*/
#include "mbed.h"
#include "Motor.h"

Motor m1( MBED_CONF_IOTKIT_MOTOR1_PWM, MBED_CONF_IOTKIT_MOTOR1_FWD, MBED_CONF_IOTKIT_MOTOR1_REV ); // PWM, Vorwaerts, Rueckwarts
Motor m2( MBED_CONF_IOTKIT_MOTOR2_PWM, MBED_CONF_IOTKIT_MOTOR2_FWD, MBED_CONF_IOTKIT_MOTOR2_REV ); // PWM, Vorwaerts, Rueckwarts

int main() 
{
    printf( "Motor Test\n" );
    while   ( 1 )
    {
        // rueckwaerts
        printf( "rueckwaerts\n" );
        for (float s = 0.7f; s < 1.0f ; s += 0.01f ) 
        {
           m1.speed(s * -1); 
           m2.speed(s);            
           wait(0.2);
        }
        m1.speed( 0 );
        wait( 1.0 );
        
        printf( "vorwaerts\n" );        
        for (float s = 0.7f; s < 1.0f ; s += 0.01f ) 
        {
           m1.speed(s); 
           m2.speed(s * -1); 
           wait(0.2);
        }
        m1.speed( 0 );
        m2.speed( 0 );
        wait( 1.0 );   
    }
}
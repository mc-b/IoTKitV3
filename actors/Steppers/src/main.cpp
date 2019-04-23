/** Schrittmotor Beispiel 
    Schrittmotor an den mit STEPPER1 und STEPPER2 Steckern mit rotem Kabel nach + einstecken.
*/
#include "mbed.h"

// Stepper 1
DigitalOut s1( MBED_CONF_IOTKIT_STEPPER1_1 );
DigitalOut s2( MBED_CONF_IOTKIT_STEPPER1_2 );
DigitalOut s3( MBED_CONF_IOTKIT_STEPPER1_3 );
DigitalOut s4( MBED_CONF_IOTKIT_STEPPER1_4 );

// Stepper 2
DigitalOut s5( MBED_CONF_IOTKIT_STEPPER2_1 );
DigitalOut s6( MBED_CONF_IOTKIT_STEPPER2_2 );
DigitalOut s7( MBED_CONF_IOTKIT_STEPPER2_3 );
DigitalOut s8( MBED_CONF_IOTKIT_STEPPER2_4 );

static float s = 0.005f;

int main()
{
    // Motordrehzahl
    printf( "Schrittmotor Test\n" );

    while ( 1 ) 
    {
        printf( "vorwaerts\n" );
        for ( int i = 0; i < 1024/4; i++ )
        {
            s1 = 1; s2 = 0; s3 = 0; s4 = 0;
            s5 = 1; s6 = 0; s7 = 0; s8 = 0;
            wait( s );
            s1 = 0; s2 = 1;
            s5 = 0; s6 = 1;
            wait( s );
            s2 = 0; s3 = 1;
            s6 = 0; s7 = 1;
            wait( s );
            s3 = 0; s4 = 1;
            s7 = 0; s8 = 1;
            wait( s );
        }
        wait( 0.5f );
        printf( "rueckwaerts\n" );
        for ( int i = 0; i < 1024/4; i++ )
        {
            s4 = 1; s3 = 0; s2 = 0; s1 = 0;
            wait( s );
            s4 = 0; s3 = 1;
            wait( s );
            s3 = 0; s2 = 1;
            wait( s );
            s2 = 0; s1 = 1;
            wait( s );
        }
        wait( 0.5f );
    }
}

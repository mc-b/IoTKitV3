/** Schrittmotor Beispiel 
    Schrittmotor am oberen Stecker mit rotem Kabel nach unten einstecken.
*/
#include "mbed.h"
#include "StepperMotorUni.h"

StepperMotorUni motor1( PTB20, PTB21, PTB1, PTB0 );
StepperMotorUni motor2( PTB18, PTB19, PTC8, PTC9 );

int main()
{
    // Motordrehzahl
    printf( "Schrittmotor Test\n" );
    motor1.set_pps( 300 );
    motor2.set_pps( 300 );

    while ( 1 ) 
    {
        printf( "vorwaerts\n" );
        motor1.move_steps( 1024 );   // halbe Umdrehung (180°)
        motor2.move_steps( -1024 );   // halbe Umdrehung (180°)
        wait( 6.0 );

        printf( "rueckwaerts\n" );
        motor1.move_steps( -1024 );
        motor2.move_steps( 1024 );
        wait( 6.0 );
    }
}
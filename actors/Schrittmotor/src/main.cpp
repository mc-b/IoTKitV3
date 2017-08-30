/** Schrittmotor Beispiel 
    Schrittmotor an Stepper 1 mit rotem Kabel nach unten (+) einstecken.
*/
#include "mbed.h"
#include "StepperMotorUni.h"

StepperMotorUni motor( D5, D4, D3, D2 );

int main()
{
    // Motordrehzahl
    printf( "Schrittmotor Test\n" );
    motor.set_pps( 150 );

    while ( 1 ) 
    {
        printf( "vorwaerts\n" );
        motor.move_steps( 1024 );   // halbe Umdrehung (180°)
        wait( 7.5 );

        printf( "rueckwaerts\n" );
        motor.move_steps( -1024 );
        wait( 7.5 );
    }
}
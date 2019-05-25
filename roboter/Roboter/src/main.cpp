/** Roboter Beispiele mit Motor und Servos
*/

#include "mbed.h"
#include "Motor.h"
#include "Servo.h"

// Geschwindigkeit
AnalogIn poti ( MBED_CONF_IOTKIT_HALL_SENSOR );

// Motor an M01
Motor m1( MBED_CONF_IOTKIT_MOTOR1_PWM, MBED_CONF_IOTKIT_MOTOR1_FWD, MBED_CONF_IOTKIT_MOTOR1_REV ); // PWM, Vorwaerts, Rueckwarts

// Servos
Servo foot( MBED_CONF_IOTKIT_SERVO1 );
Servo base( MBED_CONF_IOTKIT_SERVO2 );
Servo arm( MBED_CONF_IOTKIT_SERVO3 );
Servo pincer( MBED_CONF_IOTKIT_SERVO4 );

// Move Positionen
float footLeft = 0.2f;
float footRight = 0.8f;
float baseUp = 0.5f;
float baseDown = 0.15f;
float armUp = 0.5f;
float armDown = 0.25f;
float pincerOpen = 0.3f;
float pincerClose = 0.04f;

/** Servo langsam bewegen */
void servoMove( Servo &servo, float start, float end )
{
    if  ( start < end )
    {
        for ( float i = start; i < end; i += 0.0005f )
        {
            servo = i;
            wait    ( 0.005f );
        }
    }
    else
    {
        for ( float i = start; i > end; i -= 0.0005f )
        {
            servo = i;
            wait    ( 0.005f );
        }        
    }
}

/** Hauptprogramm */
int main()
{

    while   ( 1 )
    {
        m1.speed( poti );
        servoMove( foot, footLeft, footRight );
        servoMove( base, baseUp, baseDown );        
        servoMove( arm, armUp, armDown );
        servoMove( pincer, pincerOpen, pincerClose );    // close
        wait( 1.0f );
        servoMove( base, baseDown, baseUp );        
        servoMove( arm, armDown, armUp );
        m1.speed( 0.0f );
        wait( 1.0f );
        
        m1.speed( poti * -1.0f );
        servoMove( foot, footRight, footLeft );
        servoMove( base, baseUp, baseDown );        
        servoMove( arm, armUp, armDown );
        servoMove( pincer, pincerClose, pincerOpen );    // open
        wait( 1.0f );
        servoMove( base, baseDown, baseUp );        
        servoMove( arm, armDown, armUp );
        m1.speed( 0.0f );        
        wait( 1.0f );
     }
}

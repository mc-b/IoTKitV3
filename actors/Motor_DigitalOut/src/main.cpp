/** Motor und LED Beispiel aus IoT fuer Integratoren
    Motor an den unteren 2 Pins einstecken.
*/
#include "mbed.h"
#include "Motor.h"

DigitalOut led1( D10 );
DigitalOut led2( D11 );
Motor m1( D3, D2, D4 ); // PWM, Vorwaerts, Rueckwarts

int main() 
{
    printf( "Motor Test...\n" );
    while   ( 1 )
    {
        // rueckwaerts
        printf( "rueckwaerts\n" );
        led1 = 0;
        led2 = 1;
        for (float s = 0.5f; s < 1.0f ; s += 0.05f ) 
        {
           m1.speed(s * -1); 
           wait(0.4);
        }
        led1 = 0;
        led2 = 0;
        m1.speed( 0 );
        wait( 1.0 );
        
        printf( "vorwaerts\n" );  
        led1 = 1;
        led2 = 0;      
        for (float s = 0.5f; s < 1.0f ; s += 0.05f ) 
        {
           m1.speed(s); 
           wait(0.4);
        }
        led1 = 0;
        led2 = 0;
        m1.speed( 0 );
        wait( 1.0 );   
    }
}
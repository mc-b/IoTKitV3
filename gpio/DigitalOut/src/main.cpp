/** Mittels DigitalOut kann eine Positive Spannung an einem Pin erzeugt werden.
*/
#include "mbed.h"

DigitalOut led1( MBED_CONF_IOTKIT_LED1 );
DigitalOut led2( MBED_CONF_IOTKIT_LED2 );
DigitalOut led3( MBED_CONF_IOTKIT_LED3 );
DigitalOut led4( MBED_CONF_IOTKIT_LED4 );

// optimiert float statt double wenn ohne "f"
float warte = 0.5f;

int main()
{
    while(1) 
    {
        // kurze Schreibweise, operator= ist ueberschrieben
        led1 = 1;
        led2 = 0;
        led3 = 0;
        led4 = 0; 
        wait( warte  );
        
        // Aufruf der Methode
        led1.write( 0 );
        led2.write( 1 );
        led3.write( 0 );
        led4.write( 0 ); 
        wait( warte );
        
        led1 = 0;
        led2 = 0;
        led3 = 1;
        led4 = 0; 
        wait( warte );
        
        led1 = 0;
        led2 = 0;
        led3 = 0;
        led4 = 1; 
        wait( warte );        
                
    }
}  
/** Mittels DigitalOut kann eine Positive Spannung an einem Pin erzeugt werden.
*/
#include "mbed.h"

DigitalOut led1( D10 );
DigitalOut led2( D11 );
DigitalOut led3( D12 );
DigitalOut led4( D13 );

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

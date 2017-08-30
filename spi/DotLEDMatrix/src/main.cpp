/** Beispiel fuer die Dot LED Matrix Ansteuerung
*/
#include "mbed.h"
#include "Driver.h"

// Dot LED Matrix Driver (SPI-2 Anschluss)
LMDriver matrix( D11, D12, D13, D9 );

int main()
{
    matrix.Setup();
    // Scrollgeschwindigkeit
    matrix.SetWaitTime( 0.4f );

    while   ( 1 )
    {
        // String welcher scrollend dargestellt wird.
        matrix.DisplayString( "Das ist ein Test mit 26.3C" );
        wait( 1.0f );
        
        // Alfabet anzeigen
        for ( unsigned char i = '0'; i <= 'z'; i++ )
        {
            matrix.DisplayChar( i );
            wait( 0.5f );
        }
    }
}



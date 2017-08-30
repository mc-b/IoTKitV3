/** Zahlfallszahlen erzeugen und damit Fernsehsimulator fuettern
*/
#include "mbed.h"
#include <time.h>

SPI spi(D11, NC, D13); // mosi, miso, sclk
AnalogIn poti( A0 );

/** 3 x 3 Werte */
unsigned int strip[9];

void writeLED()
{
    for ( int p = 0; p < 9; p++ )
        spi.write( strip[p] );
}

void clearLED()
{
    for ( int p = 0; p < 9; p++ ) 
    {
        strip[p] = 0;
        spi.write( strip[p] );
    }
}

int main()
{
    printf( "LED Strip Test \n" );
     
    spi.format( 8,0 );
    spi.frequency( 800000 );

    clearLED();
    time_t t;
    time(&t);
    srand( (unsigned int)t );              /* Zufallsgenerator initialisieren */

    while   ( 1 )
    {
        for ( int i = 0; i < 9; i++ )
            strip[i] = rand() % 64 + 1;
            
        writeLED();
        wait( poti.read() );          
    }
}
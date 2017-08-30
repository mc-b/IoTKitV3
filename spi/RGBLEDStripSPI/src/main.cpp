/** RGB LED Strip (SPI)
*/
#include "mbed.h"

SPI spi(D11, NC, D13); // mosi, miso, sclk

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
    
    while (true) 
    {
        // Gruen, Rot, Blau - von Dunkel bis Hell
        for ( int i = 0; i < 128; i+=32 )
        {
                // LED 1
                strip[0] = i;
                strip[1] = 0;
                strip[2] = 0;
                // LED 2
                strip[3] = 0;
                strip[4] = i;
                strip[5] = 0;
                // LED 3
                strip[6] = 0;
                strip[7] = 0;
                strip[8] = i;
                writeLED();
                wait( 0.1 );
        }
        wait( 1.0 );
        clearLED();

        // Lauflicht (5 x 4 Zustaende)
        int p = 0;
        for ( int i = 0; i < 20; i++ )
        {
            p++;
            switch  ( p )
            {
                case 1:
                    strip[0] = strip[1] = strip[2] = 32;
                    break;
                case 2:
                    strip[0] = strip[1] = strip[2] = 0;
                    strip[3] = strip[4] = strip[5] = 32;
                    break;
                case 3:
                    strip[3] = strip[4] = strip[5] = 0;
                    strip[6] = strip[7] = strip[8] = 32;
                    break;
                default:
                    clearLED();
                    p = 0;
                    break;
            }
            writeLED();
            wait( 0.2 );                    
        }
    }
}
      
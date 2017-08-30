/** Ausgabe auf allen Seriellen Schnttstellen auf dem FRDM-K64F
 *  Umbau ohne Array wegen Problemen mit Serial
*/
#include "mbed.h"

// 4 x UART: USB, A2+A3, I2C Bus (Doppelbelegung), Bluetooth Header. PTD6+PTD7 nicht ansprechbar
Serial usb( USBTX, USBRX );
Serial modem( A3, A2 );
Serial i2c( D15, D14 );
Serial bluetooth( PTC15, PTC14 );

char id[4] [10]  = { "usb", "modem", "i2c", "bluetooth" };

int main()
{
	usb.printf( "SerialAll auf Serial - %ds\n", id[0] );
	modem.printf( "SerialAll auf Serial - %ds\n", id[1] );
	i2c.printf( "SerialAll auf Serial - %ds\n", id[2] );
	bluetooth.printf( "SerialAll auf Serial - %ds\n", id[3] );
     
    int count = 0;    
    while   ( 1 )
    {
        for ( int i = 0; i < 4; i++ )
        {
            usb.printf( "Counter %d auf Serial %s\n", count, id[i] );
            modem.printf( "Counter %d auf Serial %s\n", count, id[i] );
            i2c.printf( "Counter %d auf Serial %s\n", count, id[i] );
            bluetooth.printf( "Counter %d auf Serial %s\n", count, id[i] );
        }
        count++;
        wait( 2.0 );            
    }
}                   

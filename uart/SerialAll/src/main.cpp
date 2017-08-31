/** Ausgabe auf allen Seriellen Schnttstellen auf dem FRDM-K64F
 *  Umbau ohne Array wegen Problemen mit Serial
*/
#include "mbed.h"

// 4 x UART: USB, A2+A3, I2C Bus (Doppelbelegung), Bluetooth Header. PTD6+PTD7 nicht ansprechbar
Serial usb( USBTX, USBRX );
Serial arduino( D1, D0 );
Serial serial3( A1, A0 );
Serial serial2( D10, D4 );

DigitalOut led( LED2 );

char id[4] [10]  = { "usb", "mbed", "serial3", "serial2" };

int main()
{
	usb.printf( "SerialAll auf Serial - %ds\n", id[0] );
	arduino.printf( "SerialAll auf Serial - %ds\n", id[1] );
	serial3.printf( "SerialAll auf Serial - %ds\n", id[2] );
	serial2.printf( "SerialAll auf Serial - %ds\n", id[3] );
     
    int count = 0;    
    while   ( 1 )
    {
    	led = 1;
    	wait( 1.0 );

		usb.printf( "Counter %d auf Serial %s\n", count, id[0] );
		arduino.printf( "Counter %d auf Serial %s\n", count, id[1] );
		serial3.printf( "Counter %d auf Serial %s\n", count, id[2] );
		serial2.printf( "Counter %d auf Serial %s\n", count, id[3] );
		count++;

        led = 0;
        wait( 1.0 );
    }
}                   

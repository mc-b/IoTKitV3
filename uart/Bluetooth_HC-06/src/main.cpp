/** Bluetooth (HC-06 Modul) Testprogramm 
 *  in Verbindung mit der Android APP BlueTerm
*/
#include "mbed.h"

DigitalOut led[] = { DigitalOut( D10 ), DigitalOut( D11 ), DigitalOut( D12 ) };
 
// Serial Header auf SMD Shield
Serial hc06( D1, D0 );
// Bluetooth (gleiche wie WLAN) Header
//Serial hc06( A3, A2 );
// Bluetooth Header auf FRDM-K64F Board 
// Serial hc06( PTC15, PTC14 );
 
int main() 
{
    hc06.baud( 9600 );
    hc06.printf( "1, 2 oder 3 druecken (Meldung von HC05-x)\n\r" );
    while (1) 
    {
        // Trick: '0' - '0' ergibt int 0.
        char c = hc06.getc() - '0';
        
        // Wert innerhalb der Array's
        if  ( c > 0 && c < 4 )
        {
            led[c-1] = ! led[c-1];
            hc06.printf( "LED %d ist %d\r\n", c, led[c-1].read() );
        }
    }
}
/** Ausgabe auf allen Seriellen Schnttstellen auf dem IoTKit V3
*/
#include "mbed.h"

// 4 x UART: USB, A2+A3, I2C Bus (Doppelbelegung), Serial auf IoTKit V3, PTC14+PTC15 an ESP8266, Bluetooth Header: PTD6+PTD7 nicht ansprechbar
Serial serial[] = { Serial( USBTX, USBRX ), Serial( A3, A2 ), Serial( D15, D14 ), Serial( MBED_CONF_IOTKIT_ESP8266_TX, MBED_CONF_IOTKIT_ESP8266_RX ) };

int main()
{
    for ( int i = 0; i < 4; i++ )
        serial[i].printf( "SerialAll auf Serial %d\r\n", i );
     
    int count = 0;    
    while   ( 1 )
    {
        for ( int i = 0; i < 4; i++ )
            serial[i].printf( "Counter %d auf Serial %d\r\n", count, i );
        count++;
        wait( 2.0 );            
    }
}                   

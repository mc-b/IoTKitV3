/** OLED Display Test
*/
#include "mbed.h"
#include "OLEDDisplay.h"

DigitalOut led( D10 );
OLEDDisplay oled( PTE26, PTE0, PTE1 );

int main()
{
    int i = 0;
    oled.clear();
    oled.printf( "Test OLED Display\r\n" );

    while (true)
    {
        oled.cursor( 1, 0 );
        oled.printf( "ON %d, %d\n", led.read(), i );
        led = 1;
        wait( 1.0f );

        oled.cursor( 2, 0 );
        oled.printf( "OFF %d, %d\n", led.read(), i );
        led = 0;
        i++;
        wait( 1.0f );
    }
}

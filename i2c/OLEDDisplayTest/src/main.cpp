/** OLED Display Test 
*/
#include "mbed.h"
#include "OLEDDisplay.h"

DigitalOut led( MBED_CONF_IOTKIT_LED1 );
OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );

int main()
{
    int i = 0;
    oled.clear();
    oled.printf( "OLED Test\n" );
    
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
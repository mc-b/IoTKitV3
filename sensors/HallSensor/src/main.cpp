/** Hall Sensor 
*/
#include "mbed.h"
#include "OLEDDisplay.h"

// UI
OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );

AnalogIn hallSensor( MBED_CONF_IOTKIT_HALL_SENSOR );
DigitalOut led1( MBED_CONF_IOTKIT_LED1 );
DigitalOut led2( MBED_CONF_IOTKIT_LED2 );

int main()
{
    oled.clear();
    oled.printf( "Hall Sensor\n" );
    
    while(1) 
    {
        led1 = led2 = 0;
        
        float value = hallSensor.read();
        oled.cursor( 1, 0 );
        oled.printf( "value %1.4f\r\n", value );
        printf( "Hall Sensor %f\r\n", value );
        if  ( value < 0.4f )
            led1 = 1;
        else if ( value > 0.6f )
            led2 = 1;
        wait(1.0);
    }
}                                       
    
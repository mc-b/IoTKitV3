/** Hall Sensor 
*/
#include "mbed.h"
#include "OLEDDisplay.h"

AnalogIn hallSensor( PTC0 );
DigitalOut led1( D10 );
DigitalOut led2( D11 );

// UI
OLEDDisplay oled( PTE26, PTE0, PTE1);

int main()
{
    oled.clear();
    oled.printf( "Hall Sensor\n" );

    while(1) 
    {
        led1 = led2 = 0;
        
        float value = hallSensor.read();
        oled.cursor( 1, 0 );
        oled.printf( "Hall %1.4f\r\n", value );
        printf( "Hall Sensor %f\r\n", value );
        if  ( value < 0.4f )
            led1 = 1;
        else if ( value > 0.6f )
            led2 = 1;
        wait(1.0);
    }
}                                       
    

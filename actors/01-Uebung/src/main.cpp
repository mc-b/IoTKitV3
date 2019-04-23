/** Servo nach links oder rechts bewegen mittels Encoder.
*/
 
#include "mbed.h"
#include "QEI.h"
#include "OLEDDisplay.h"

// UI
OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );

// Servo
PwmOut servo1( MBED_CONF_IOTKIT_SERVO1 );

// Encoder bestimmt die Position
QEI wheel (MBED_CONF_IOTKIT_BUTTON2, MBED_CONF_IOTKIT_BUTTON3, NC, 624);
 
int main()
{
    float value = 0;
    float offset;
    oled.clear();
    oled.printf( "Servo\n" );

    servo1.period(0.020);          // servo requires a 20ms period

    while(1)
    {
        oled.cursor( 1, 0 );
        value = (float) wheel.getPulses();
		oled.printf("Value: %4.0f\n", value );

		// 0 = rechts, > 0 geht nach links
        if	( value >  0.0f )
        	offset = value / 100000.0f;
        else
        	offset = 0.0f;
    	servo1.pulsewidth(0.001f + offset);

        oled.cursor( 2, 0 );
		oled.printf("Pos  : %0.6f\n", offset );

        wait( 0.1f );
    }
}

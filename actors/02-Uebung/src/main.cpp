/** Servo nach links oder rechts bewegen mittels Encoder.
*/

#include "mbed.h"
#include "QEI.h"
#include "OLEDDisplay.h"
#include "Motor.h"

// UI
OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );

// Motor
Motor m1( MBED_CONF_IOTKIT_MOTOR1_PWM, MBED_CONF_IOTKIT_MOTOR1_FWD, MBED_CONF_IOTKIT_MOTOR1_REV ); // PWM, Vorwaerts, Rueckwarts

// Encoder bestimmt die Position
QEI wheel (MBED_CONF_IOTKIT_BUTTON2, MBED_CONF_IOTKIT_BUTTON3, NC, 624);
// Button - Stop
DigitalIn button1( MBED_CONF_IOTKIT_BUTTON1 );

int main()
{
    float value = 0;
    float offset;
    oled.clear();
    oled.printf( "Motor\n" );

    while(1)
    {
        oled.cursor( 1, 0 );

        // Stop
		if	( button1 == 0 )
			wheel.reset();

		// aktuelle Position
        value = (float) wheel.getPulses();

		oled.printf("Speed: %2.2f\n", value );

		m1.speed( value / 10.0f );
        wait( 0.1f );
    }
}

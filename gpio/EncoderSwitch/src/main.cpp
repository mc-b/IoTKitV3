/** EncoderSwitch - zaehlt die Impulse am Encoder und schalter Zaehler vor und zurueck
*/
#include "mbed.h"
#include "QEI.h"
#include "OLEDDisplay.h"

OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );

//Use X4 encoding.
//QEI wheel(p29, p30, NC, 624, QEI::X4_ENCODING);
//Use X2 encoding by default.
QEI wheel (MBED_CONF_IOTKIT_BUTTON2, MBED_CONF_IOTKIT_BUTTON3, NC, 624);
 
int main() 
{
    int value, old = 0;
    oled.clear();
    oled.printf( "Encoder Test\n" );
 
    while(1)
    {
        oled.cursor( 1, 0 );
        value = wheel.getPulses(); 
        if  ( value != old )
            oled.printf("Pulses: %6i\n", value );
        old = value;
        wait( 0.1f );
    }
 
}
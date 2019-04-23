/** Pulsweitenmodulation - Generieren eines x Hz Tones mittels PWM
 *  Dip Switch SW4 aktivieren (nach oben)
*/
#include "mbed.h"

PwmOut speaker( MBED_CONF_IOTKIT_BUZZER );

int main()
{
    while   ( 1 ) 
    {
        // Polizei Sirene
        speaker.period( 1.0 / 3969.0 );      // 3969 = Tonfrequenz in Hz
        speaker = 0.5f;
        wait( 0.5f );
        speaker.period( 1.0 / 2800.0 );
        wait( 0.5f );
    }
}
/** EncoderSwitch - zaehlt die Impulse am Encoder und schalter Zaehler vor und zurueck
*/
#include "mbed.h"
#include "QEI.h"

//Use X4 encoding.
//QEI wheel(p29, p30, NC, 624, QEI::X4_ENCODING);
//Use X2 encoding by default.
QEI wheel (PTC6, PTA4, NC, 624);

int main()
{
    int value, old = 0;

    while(1)
    {
        value = wheel.getPulses();
        if  ( value != old )
            printf("Pulses is: %i\n", value );
        old = value;
        wait( 0.1f );
    }

}

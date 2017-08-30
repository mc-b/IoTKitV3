/** Temperatursensor TMP75 auf SMD Shield
*/
#include "mbed.h"
#include "TMP175.h"

TMP175 mySensor( D14, D15 );

int main()
{
    mySensor.vSetConfigurationTMP175( SHUTDOWN_MODE_OFF | COMPARATOR_MODE | POLARITY_0 |FAULT_QUEUE_6 | RESOLUTION_12, 0x48 );
    mySensor.vSetTemperatureLowTMP175( 0.0 );
    mySensor.vSetTemperatureHighTMP175( 60.0 );

    while   ( 1 ) 
    {
        printf( "Temperature: %f C\n", mySensor.fReadTemperatureTMP175() );
        wait( 1.0f );
    }
}

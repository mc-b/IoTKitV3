/** Liest die analoge Spannung an einem Pin.
    Hier das Poti an A0
*/
#include <mbed.h>

AnalogIn hallSensor( MBED_CONF_IOTKIT_HALL_SENSOR );
DigitalOut led1( MBED_CONF_IOTKIT_LED1 );

int main()
{
    while   ( 1 )
    {
        printf("Hall %4.2f\n", hallSensor.read() );
        if  ( hallSensor.read() < 0.5f )          // in Prozent
            led1 = 1;
        else
            led1 = 0;
            
        wait ( 1.0 );   
    }     
}

/** Veraendert die Helligkeit je nach Abstand von VL53L0X
 */
#include "mbed.h"

// DigitalIn button( USER_BUTTON1 );
// DigitalOut buzzer( D3 );

// Sensoren
#include "VL53L0X.h"

DevI2C devI2c( PB_11, PB_10 );
DigitalOut shutdown_pin( PC_6 );
VL53L0X range( &devI2c, &shutdown_pin, PC_7 );
PwmOut led1( LED2 );

/**
 *  Hauptprogramm
 */
int main()
{
    range.init_sensor( VL53L0X_DEFAULT_ADDRESS );
    led1 = 0.0f;

    while ( true )
    {
        uint32_t distance;
        int status = range.get_distance( &distance );
        // Methode macht keinen Check ob Sensore Ready, deshalb nur gueltige Werte auswerten
        if ( status == VL53L0X_ERROR_NONE )
        {
            printf( "VL53L0X [mm]:            %6ld\r\n", distance );
            led1 = distance * 0.0005;

        }
        else
        {
            printf( "VL53L0X [mm]:                --\r\n" );
        }
        wait( 0.1f );
    }
}

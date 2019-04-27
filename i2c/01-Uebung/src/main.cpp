/**
 * 6D Lagesensor und Servo steuert mit dem 6 Lagensensor die Position des Servos<br>
 * Anwendungen: Ausgleich der Lage z.B. bei einem Zug.
 */

#include "mbed.h"
#include "OLEDDisplay.h"
#include "LSM6DSLSensor.h"

// UI
OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );

static DevI2C devI2c( MBED_CONF_IOTKIT_I2C_SDA, MBED_CONF_IOTKIT_I2C_SCL );
static LSM6DSLSensor acc(&devI2c,LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW); // low address

PwmOut servo1( MBED_CONF_IOTKIT_SERVO1 );

int main()
{
    uint8_t id;
    uint8_t xl = 0;
    uint8_t xh = 0;
    uint8_t yl = 0;
    uint8_t yh = 0;
    uint8_t zl = 0;
    uint8_t zh = 0;
    char report[256];
    float offset = 0.0f;

    oled.clear();
    oled.printf( "6D Servo Pos\n" );

    /* Init all sensors with default params */
    acc.init(NULL);
    acc.enable_g();
    acc.enable_x();
    acc.enable_6d_orientation();

    acc.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

    servo1.period(0.020);          // servo requires a 20ms period

    while (true)
    {
        oled.clear();

        acc.get_6d_orientation_xl(&xl);
        acc.get_6d_orientation_xh(&xh);
        acc.get_6d_orientation_yl(&yl);
        acc.get_6d_orientation_yh(&yh);
        acc.get_6d_orientation_zl(&zl);
        acc.get_6d_orientation_zh(&zh);

        printf( "\nxl %d, xh %d, yl %d, yh %d, zl %d, zh %d\n", xl, xh, yl, yh, zl, zh );

        if ( xh )
        {
          sprintf( report, "    _____________\n" \
                           " * |_____________|\n" );
          offset = 25.0f;
        }

        else if ( xl )
        {
          sprintf( report, " _____________\n" \
                           "|_____________| *\n" );
          offset = 75.0f;
        }
        else if ( yh)
        {
          sprintf( report, " _____________\n" \
                           "|______v______|\n" );
          offset = 100.0f;
        }
        else if ( yl )
        {
          sprintf( report, " _____________\n" \
                           "|______^______|\n" );
         offset = 0.0f;

        }
        else if ( zh )
        {
          sprintf( report, " ______*______ \n" \
                           "|_____________|\n" );
          offset = 50.0f;
        }

        else if ( zl )
        {
          sprintf( report,  " ____________\n" \
                            "|____________|\n" \
                            "      *       \n" );
          offset = 50.0f;
        }
        else
        {
          sprintf( report, "None of the 6D orientation axes is set in LSM6DSL - accelerometer.\r\n" );
        }
        oled.printf( report );
        printf( report );
        servo1.pulsewidth(0.001 + (offset / 100000.0f) ); // servo position determined by a pulsewidth between 1-2ms
        wait( 1.0f );
    }
}

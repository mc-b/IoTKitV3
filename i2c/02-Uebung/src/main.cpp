/**
 * 6D Lagsensor und Schrittmotor bringt mit dem 6 Lagesensor den ersten oder zweiten Schrittmotor vor- oder rückwärts zum laufen.
 */

#include "mbed.h"
#include "OLEDDisplay.h"
#include "LSM6DSLSensor.h"

// UI
OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );

static DevI2C devI2c( MBED_CONF_IOTKIT_I2C_SDA, MBED_CONF_IOTKIT_I2C_SCL );
static LSM6DSLSensor acc(&devI2c,LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW); // low address

// Stepper 1
DigitalOut s1( MBED_CONF_IOTKIT_STEPPER1_1 );
DigitalOut s2( MBED_CONF_IOTKIT_STEPPER1_2 );
DigitalOut s3( MBED_CONF_IOTKIT_STEPPER1_3 );
DigitalOut s4( MBED_CONF_IOTKIT_STEPPER1_4 );

// Stepper 2
DigitalOut s5( MBED_CONF_IOTKIT_STEPPER2_1 );
DigitalOut s6( MBED_CONF_IOTKIT_STEPPER2_2 );
DigitalOut s7( MBED_CONF_IOTKIT_STEPPER2_3 );
DigitalOut s8( MBED_CONF_IOTKIT_STEPPER2_4 );

static float s = 0.005f;

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

    oled.clear();
    oled.printf( "6D Servo Pos\n" );

    /* Init all sensors with default params */
    acc.init(NULL);
    acc.enable_g();
    acc.enable_x();
    acc.enable_6d_orientation();

    acc.read_id(&id);
    printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);

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
          for ( int i = 0; i < 20/4; i++ )
          {
              s1 = 1; s2 = 0; s3 = 0; s4 = 0;
              wait( s );
              s1 = 0; s2 = 1;
              wait( s );
              s2 = 0; s3 = 1;
              wait( s );
              s3 = 0; s4 = 1;
              wait( s );
          }
        }

        else if ( xl )
        {
          sprintf( report, " _____________\n" \
                           "|_____________| *\n" );
          for ( int i = 0; i < 20/4; i++ )
          {
              s4 = 1; s3 = 0; s2 = 0; s1 = 0;
              wait( s );
              s4 = 0; s3 = 1;
              wait( s );
              s3 = 0; s2 = 1;
              wait( s );
              s2 = 0; s1 = 1;
              wait( s );
          }
        }
        else if ( yh)
        {
          sprintf( report, " _____________\n" \
                           "|______v______|\n" );
          for ( int i = 0; i < 20/4; i++ )
          {
              s5 = 1; s6 = 0; s7 = 0; s8 = 0;
              wait( s );
              s5 = 0; s6 = 1;
              wait( s );
              s6 = 0; s7 = 1;
              wait( s );
              s7 = 0; s8 = 1;
              wait( s );
          }
        }
        else if ( yl )
        {
          sprintf( report, " _____________\n" \
                           "|______^______|\n" );
          for ( int i = 0; i < 20/4; i++ )
          {
              s8 = 1; s7 = 0; s6 = 0; s5 = 0;
              wait( s );
              s8 = 0; s7 = 1;
              wait( s );
              s7 = 0; s6 = 1;
              wait( s );
              s6 = 0; s5 = 1;
              wait( s );
          }
        }
        else if ( zh )
        {
          sprintf( report, " ______*______ \n" \
                           "|_____________|\n" );
        }

        else if ( zl )
        {
          sprintf( report,  " ____________\n" \
                            "|____________|\n" \
                            "      *       \n" );
        }
        else
        {
          sprintf( report, "None of the 6D orientation axes is set in LSM6DSL - accelerometer.\r\n" );
        }
        oled.printf( report );
        printf( report );
        wait( 0.2f );
    }
}

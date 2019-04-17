#include "mbed.h"
#include "OLEDDisplay.h"
#include "LSM6DSLSensor.h"

// UI
OLEDDisplay oled( PTE26, PTE0, PTE1);

static DevI2C devI2c(PTE0,PTE1);
static LSM6DSLSensor acc(&devI2c,LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW); // low address

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
    oled.printf( "6D Orientation\n" );

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
        }

        else if ( xl )
		{
		  sprintf( report, " _____________\n" \
						   "|_____________| *\n" );
		}
        else if ( yh)
		{
		  sprintf( report, " _____________\n" \
						   "|______v______|\n" );
		}
        else if ( yl )
		{
		  sprintf( report, " _____________\n" \
						   "|______^______|\n" );
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
        wait( 1.0f );
    }
}

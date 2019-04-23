#include "mbed.h"
#include "lis3mdl_class.h"
#include "OLEDDisplay.h"

// UI
OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );

static DevI2C devI2c( MBED_CONF_IOTKIT_I2C_SDA, MBED_CONF_IOTKIT_I2C_SCL );
static LIS3MDL magnetometer(&devI2c);

int main()
{
    uint8_t id;
    int32_t axes[3];
    float heading;

    /* Init all sensors with default params */
    magnetometer.init(NULL);
    magnetometer.read_id(&id);
    oled.clear();
    oled.printf("LIS3MDL = 0x%X\n", id);

    while (true)
    {
    	oled.cursor( 1, 0 );
        magnetometer.get_m_axes( axes );
        printf( "LIS3DML [mag/mgauss] x=%6ld, y=%6ld, z=%6ld, diff=%6ld\n", axes[0], axes[1], axes[2], axes[0] + axes[1] );

        // Magnet mit North oder South anliegend
        if	( axes[0] > 2000  )
        {
        	oled.printf( "Magnet north" );
        	continue;
        }
        if ( axes[0] < -2000 )
        {
        	oled.printf( "Magnet south" );
        	continue;
        }

/*		Berechnung Winkel @see https://learn.adafruit.com/lsm303-accelerometer-slash-compass-breakout/coding (fehlerhaft)
        heading = atan2f(axes[1], axes[0]) * 180.0f / M_PI;
        heading = floorf( heading * 100.0f + 0.5f) / 100.0f;       // Rounds number to two decimal digits
        heading = (heading < 0.0f) ? (heading + 360.0f) : heading; // Change negative value to be in range <0,360)
*/
        // Vereinfachte Variante  eCompass: basiert auf Differenz axes[0]=East=x, axes=[1]=North=y
        int diff = axes[0] + axes[1];
        diff = (diff < 0) ? diff * -1 : diff;
        if	( diff > 350 && diff < 370 )
        	oled.printf( "north %6ld", diff );
        else if ( diff > 450 && diff < 470 )
        	oled.printf( "west  %6ld", diff );
        else if ( diff > 50 && diff < 70 )
        	oled.printf( "east  %6ld", diff );
        else if ( diff > 130 && diff < 150 )
        	oled.printf( "south %6ld", diff );
        else
        	oled.printf( "      %6ld", diff );

        wait( 0.5f );
    }
}

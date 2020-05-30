/**
 * Bosch BMP180 Digital Pressure Sensor
 *
 * Der Sensor liefert keinen Wert fuer Luftfeuchtigkeit, deshalb wird der Luftdruck in kPa geliefert.
 */

#include "mbed.h"
#include <BMP180Wrapper.h>
#include "OLEDDisplay.h"

// UI
OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );

static DevI2C devI2c( MBED_CONF_IOTKIT_I2C_SDA, MBED_CONF_IOTKIT_I2C_SCL );
static BMP180Wrapper hum_temp(&devI2c);

int main()
{
    uint8_t id;
    float value1, value2;

    oled.clear();
    oled.printf( "Temp/Pressure Sensor\n" );

    /* Init all sensors with default params */
    hum_temp.init(NULL);
    hum_temp.enable();

    hum_temp.read_id(&id);
    printf("humidity & air pressure    = 0x%X\r\n", id);

    while (true)
    {
        hum_temp.get_temperature(&value1);
        hum_temp.get_humidity(&value2);
        printf("BMP180:  [temp] %.2f C, [kPa]   %.2f%%\r\n", value1, value2);
        oled.cursor( 1, 0 );
        oled.printf( "temp: %3.2f\nkPa : %3.2f", value1, value2 );
        wait( 1.0f );
    }
}

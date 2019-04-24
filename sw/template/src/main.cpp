/** IOTKit V3 Template
*/
#include "mbed.h"
#include "network-helper.h"

// UI, Input und Output
#include "OLEDDisplay.h"
#include "QEI.h"

// UI
OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );
// DigitalIn button( MBED_CONF_IOTKIT_BUTTON1 );
// QEI wheel ( MBED_CONF_IOTKIT_BUTTON2, MBED_CONF_IOTKIT_BUTTON3, NC, 624 );
// DigitalOut buzzer( MBED_CONF_IOTKIT_BUZZER );

// Sensoren
#include "MFRC522.h"
#include "HTS221Sensor.h"
#include "ISL29125.h"
#include "lis3mdl_class.h"
#include "LSM6DSLSensor.h"
#ifdef TARGET_K64F
#include "VL6180x.h"
#endif
#ifdef TARGET_DISCO_L475VG_IOT01A
#include "VL53L0X.h"
#endif

static DevI2C devI2c( MBED_CONF_IOTKIT_I2C_SDA, MBED_CONF_IOTKIT_I2C_SCL );
// HTS221Sensor hum_temp( &devI2c );
// ISL29125 RGBsensor( MBED_CONF_IOTKIT_I2C_SDA, MBED_CONF_IOTKIT_I2C_SCL );
// LIS3MDL magnetometer(&devI2c);
// LSM6DSLSensor acc_gyro( &devI2c, LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW );
#ifdef TARGET_K64F
// VL6180x sensor( MBED_CONF_IOTKIT_I2C_SDA, MBED_CONF_IOTKIT_I2C_SCL, 0x52 );
#endif
#ifdef TARGET_DISCO_L475VG_IOT01A
// DigitalOut shutdown_pin(PC_6);
// VL53L0X range(&devI2c, &shutdown_pin, PC_7);
#endif
// MFRC522    rfidReader( MBED_CONF_IOTKIT_RFID_MOSI, MBED_CONF_IOTKIT_RFID_MISO, MBED_CONF_IOTKIT_RFID_SCLK, MBED_CONF_IOTKIT_RFID_SS, MBED_CONF_IOTKIT_RFID_RST );
// AnalogIn hallSensor( MBED_CONF_IOTKIT_HALL_SENSOR );

// Kommunikation
#include "TCPSocket.h"
#include "NTPClient.h"

/**
 *  Hauptprogramm
 */
int main()
{
    oled.clear();
    oled.printf( "IoTKit V3 Template\n" );

#ifdef MBED_MAJOR_VERSION
    oled.printf("Mbed OS V: %d.%d.%d\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
#endif

    // Wifi Verbinden
    oled.printf("Con to %s\n", MBED_CONF_APP_WIFI_SSID);
    // Connect to the network with the default networking interface
    // if you use WiFi: see mbed_app.json for the credentials
    NetworkInterface* network = connect_to_default_network_interface();

    if (!network) {
        printf("Cannot connect to the network, see serial output\n");
        return 1;
    }

    // hole und setze Zeit vom Internet
    NTPClient ntp( network ) ;
    time_t timestamp = ntp.get_timestamp();
    if ( timestamp < 0 )
        return ( -1 );
    set_time( timestamp );

    while (true)
    {
       time_t seconds = time(NULL);
       oled.cursor( 2, 0 );
       oled.printf( "Date/Time %s UTC", ctime(&seconds) );

       wait( 1.0f );
    }
}

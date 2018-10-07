/** IOTKit V3 Template
*/
#include "mbed.h"

// UI, Input und Output
#include "OLEDDisplay.h"
#include "QEI.h"

OLEDDisplay oled( PTE26, PTE0, PTE1 );
// DigitalIn button( PTC13 );
// QEI wheel ( PTC6, PTA4, NC, 624 );
// DigitalOut buzzer( D12 );

// Sensoren
#include "HTS221Sensor.h"
#include "ISL29125.h"
#include "lis3mdl_class.h"
#include "LSM6DSLSensor.h"
#include "VL6180x.h"
#include "MFRC522.h"

DevI2C devI2c( PTE0, PTE1 );
// HTS221Sensor hum_temp( &devI2c );
// ISL29125 RGBsensor( PTE0, PTE1 );
// LIS3MDL magnetometer(&devI2c);
// LSM6DSLSensor acc_gyro( &devI2c, LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW );
// VL6180x sensor( PTE0, PTE1, 0x52 );
// MFRC522 rfidReader( PTA16, PTC7, PTC5, D10, D8 );
// AnalogIn hallSensor( PTC0 );

// Kommunikation
#include "ESP8266Interface.h"
#include "TCPSocket.h"
#include "NTPClient.h"

ESP8266Interface wifi( MBED_CONF_APP_WIFI_TX, MBED_CONF_APP_WIFI_RX );

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
    if  ( wifi.connect( MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2 ) != 0 )
        return ( -1 );

    // hole und setze Zeit vom Internet
    NTPClient ntp( &wifi) ;
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

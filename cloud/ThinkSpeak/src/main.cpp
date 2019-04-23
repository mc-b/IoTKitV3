/** Beispiel Senden von Sensordaten an ThingSpeak
 */
#include "mbed.h"
#include "HTS221Sensor.h"
#include "http_request.h"
#include "network-helper.h"
#include "OLEDDisplay.h"

// UI
OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );

static DevI2C devI2c( MBED_CONF_IOTKIT_I2C_SDA, MBED_CONF_IOTKIT_I2C_SCL );
static HTS221Sensor hum_temp(&devI2c);

/** ThingSpeak URL und API Key ggf. anpassen */
char host[] = "http://api.thingspeak.com/update";
char key[] = "A2ABBMDJYRAMA6JM";

// I/O Buffer
char message[1024];

DigitalOut myled(D10);

int main()
{
    uint8_t id;
    float value1, value2;

    printf("\tThingSpeak\n");

    /* Init all sensors with default params */
    hum_temp.init(NULL);
    hum_temp.enable();

    hum_temp.read_id(&id);
    printf("HTS221  humidity & temperature    = 0x%X\r\n", id);

    // Connect to the network with the default networking interface
    // if you use WiFi: see mbed_app.json for the credentials
    NetworkInterface* network = connect_to_default_network_interface();
    
    if (!network) {
        printf("Cannot connect to the network, see serial output\n");
        return 1;
    }

    while( 1 )
    {
        hum_temp.get_temperature(&value1);
        hum_temp.get_humidity(&value2);

        sprintf( message, "%s?key=%s&field1=%f&field2=%f", host, key, value1, value2 );
        printf( "%s\n", message );
        oled.cursor( 1, 0 );
        oled.printf( "temp: %3.2f\nhum : %3.2f", value1, value2 );

        myled = 1;
        HttpRequest* get_req = new HttpRequest( network, HTTP_GET, message );

        HttpResponse* get_res = get_req->send();
        if (!get_res)
        {
            printf("HttpRequest failed (error code %d)\n", get_req->get_error());
            return 1;
        }
        delete get_req;
        myled = 0;
        wait(10);
    }
}

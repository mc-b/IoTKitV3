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

// I/O Buffer
char message[1024];

void dump_response(HttpResponse* res)
{
    printf("Status: %d - %s\n", res->get_status_code(), res->get_status_message().c_str());

    printf("Headers:\n");
    for (size_t ix = 0; ix < res->get_headers_length(); ix++)
    {
        printf("\t%s: %s\n", res->get_headers_fields()[ix]->c_str(), res->get_headers_values()[ix]->c_str());
    }
    printf("\nBody (%d bytes):\n\n%s\n", res->get_body_length(), res->get_body_as_string().c_str());
}

DigitalOut myled( MBED_CONF_IOTKIT_LED1 );

int main()
{
    uint8_t id;
    float value1, value2;

    oled.printf("HTTP POST\n");

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

        oled.cursor( 1, 0 );
        oled.printf( "temp: %3.2f\nhum : %3.2f", value1, value2 );

        myled = 1;
        HttpRequest* post_req = new HttpRequest( network, HTTP_POST, "http://myserver/cgi-bin/rest" );

        sprintf( message, "temp=%3.2f&hum=%3.2f", value1, value2 );

        HttpResponse* post_res = post_req->send(message, strlen(message));
        if (!post_res) {
            printf("HttpRequest failed (error code %d)\n", post_req->get_error());
            return 1;
        }

        printf("\n----- HTTP POST response -----\n");
        dump_response(post_res);

        delete post_req;
        myled = 0;
        wait(10);
    }
}

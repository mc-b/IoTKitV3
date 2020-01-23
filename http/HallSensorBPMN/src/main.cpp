/** Beispiel Abfrage Cloud Dienst Sunrise / Sunset
 */
#include "mbed.h"
#include "http_request.h"
#include "network-helper.h"
#include "OLEDDisplay.h"

// UI
OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );

AnalogIn hallSensor( MBED_CONF_IOTKIT_HALL_SENSOR );
DigitalOut led1( MBED_CONF_IOTKIT_LED1 );
DigitalOut led2( MBED_CONF_IOTKIT_LED2 );
DigitalIn reset( MBED_CONF_IOTKIT_BUTTON1 );

// I/O Buffer
char message[256];

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

int main()
{
    oled.clear();
    oled.printf( "H-Sensor BPMN\n" );
    printf("\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID);
    oled.printf( "SSID: %s\r\n", MBED_CONF_APP_WIFI_SSID );
    
    // Connect to the network with the default networking interface
    // if you use WiFi: see mbed_app.json for the credentials
    NetworkInterface* network = connect_to_default_network_interface();
    
    if (!network) {
        printf("Cannot connect to the network, see serial output\n");
        return 1;
    }

    led1 = 0;
    led2 = 1;
    int count = 1;
        
    while(1) 
    {
        // Alarm scharf
        if  ( led1 == 0 )
        {
            oled.cursor( 3, 0 );
            oled.printf( "scharf      " );
            float value = hallSensor.read();
            if  ( value > 0.6f )
            {
                oled.cursor( 3, 0 );
                oled.printf( "ALARM !!!" );
                HttpRequest* post_req = new HttpRequest( network, HTTP_POST, "http://192.168.178.12:30880/engine-rest/process-definition/key/RechnungStep3/start" );
                post_req->set_header("Content-Type", "application/json");

                sprintf( message, "{\"variables\":{\"rnr\":{\"value\":\"%d\",\"type\":\"long\"},\"rbetrag\":{\"value\":\"%f\",\"type\":\"String\"}}}", count, count * 100.0f );

                HttpResponse* post_res = post_req->send(message, strlen(message));
                if (!post_res) {
                    printf("HttpRequest failed (error code %d)\n", post_req->get_error());
                    return 1;
                }

                printf("\n----- HTTP POST response -----\n");
                dump_response(post_res);

                delete post_req;
                led1 = 1;
                led2 = 0;
                count++;
            }
        }
        else
        {
            if  ( reset == 0 )
            {
                oled.cursor( 3, 0 );
                oled.printf( "reset       " );                
                led1 = 0;
                led2 = 1;
            }
        }
        wait( 0.2f );
    }
}

/** Beispiel Abfrage Cloud Dienst Sunrise / Sunset
 */
#include "mbed.h"
#include "http_request.h"
#include "network-helper.h"
#include "MbedJSONValue.h"
#include <string>

// I/O Buffer
char message[6000];

DigitalOut myled( D10 );

int main()
{
    printf("\tSunriseSunset Cloud Dienst\n");
    // Connect to the network with the default networking interface
    // if you use WiFi: see mbed_app.json for the credentials
    NetworkInterface* network = connect_to_default_network_interface();

    if (!network) {
        printf("Cannot connect to the network, see serial output\n");
        return 1;
    }

    while( 1 )
    {
        myled = 1;
        // By default the body is automatically parsed and stored in a buffer, this is memory heavy.
        // To receive chunked response, pass in a callback as last parameter to the constructor.
        HttpRequest* get_req = new HttpRequest(network, HTTP_GET, "http://api.sunrise-sunset.org/json?lat=47.3686498&lng=8.5391825");

        HttpResponse* get_res = get_req->send();
        // OK
        if ( get_res )
        {
            MbedJSONValue parser;
            // HTTP GET (JSON) parsen  
            parse( parser, get_res->get_body_as_string().c_str() );
            
            std::string sunrise;
            std::string sunset;            
            
            sunrise = parser["results"]["sunrise"].get<std::string>();
            sunset  = parser["results"]["sunset"] .get<std::string>(); 
            
            // Umwandlung nach int. Damit die Zeiten besser verglichen werden können.
            int rh, rm, rs, sh, sm, ss;
            sscanf( sunrise.c_str(), "%d:%d:%d AM", &rh, &rm, &rs );
            sscanf( sunset .c_str(), "%d:%d:%d PM", &sh, &sm, &ss );
            
            printf( "Sonnenauf- %02d.%02d.%02d und untergang %02d.%02d.%02d\n", rh+2, rm, rs, sh+2+12, sm, ss );
        }
        // Error
        else
        {
            printf("HttpRequest failed (error code %d)\n", get_req->get_error());
            return 1;
        }
        delete get_req;
        myled = 0;

        wait(10);
    }
}

/** Beispiel Abfrage Cloud Dienst Sunrise / Sunset
 */
#include "mbed.h"
#include "HTTPClient.h"
#include "data/HTTPText.h"
#include "EthernetInterface.h"
#include "MbedJSONValue.h"
#include <string>

EthernetInterface eth;
// HTTPClient Hilfsklasse
HTTPClient http;
// I/O Buffer
char message[6000];

DigitalOut myled(LED1);

int main()
{
    printf("\tSunriseSunset Cloud Dienst\n");
    eth.init();
    eth.connect();

    while(1) 
    {
        myled = 1;
        int ret = http.get("http://api.sunrise-sunset.org/json?lat=47.3686498&lng=8.5391825", message, sizeof(message));
        if ( !ret ) 
        {
            MbedJSONValue parser;
            // HTTP GET (JSON) parsen  
            parse( parser, message );  
            
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
        else
            printf("Error - ret = %d - HTTP return code = %d\n", ret, http.getHTTPResponseCode());
        
        myled = 0;

        wait(10);
    }
    //eth.disconnect();
}

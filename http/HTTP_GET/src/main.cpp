/** Beispiel HTTP GET
 */
#include "mbed.h"
#include "HTTPClient.h"
#include "data/HTTPText.h"
#include "EthernetInterface.h"

EthernetInterface eth;
// HTTPClient Hilfsklasse
HTTPClient http;
// I/O Buffer
char message[6000];

DigitalOut myled(LED1);

int main()
{
    printf("HTTP Client - GET\n");
    eth.init();
    eth.connect();

    while(1) 
    {
        myled = 1;
        
        int ret = http.get("http://developer.mbed.org/media/uploads/mbed_official/hello.txt", message, sizeof(message));
        // lokale Variante mit CGI-Script auf IoT USB Stick. Wenn nicht Funktioniert: iot-stick durch IP-Adresse ersetzen
        //int ret = http.get("http://iot-stick/rest/cgi-bin/rest/timestamp", message, sizeof(message));
        if ( !ret ) 
        {
            printf("Success - read %d characters.\r\n", strlen(message));
            printf("%s\r\n", message);
        }
        else
            printf("Error - ret = %d - HTTP return code = %d\n", ret, http.getHTTPResponseCode());
        
        myled = 0;

        wait(10);
    }
    eth.disconnect();
}

/** Wifi / Ethernet HTTP Get Beispiel
*/
#include "mbed.h"
#include "HTTPClient.h"

#define ETHERNET 1
#ifdef ETHERNET
#include "EthernetInterface.h"
EthernetInterface eth;
#else
#include "ESP8266Interface.h"
ESP8266Interface eth( A3, A2, D10, "mcbmobile_2EX", "android%123", 115200 ); // TX,RX,Reset,SSID,Password,Baud
#endif

// HTTP Client und I/O Buffer
HTTPClient http;
char str[512];

int main()
{
    printf( "WiFi HTTP GET\n" );   
    eth.init(); //Reset
    eth.connect(); //Use DHCP
    printf("IP Address is %s\n", eth.getIPAddress());    

    for ( int i = 0; i < 10; i++ ) 
    {
        //GET
        printf("\nTrying to fetch page using GET...\n\r");
        int ret = http.get("http://54.175.219.8/get", str, 512);//IP address is httpbin.org/get
        if (!ret) 
        {
            printf("Page fetched successfully - read %d characters\n\r", strlen(str));
            printf("Result: %s\n\r", str);
        } else 
        {
            printf("Error - ret = %d - HTTP return code = %d\n\r", ret, http.getHTTPResponseCode());
        }
    }
}

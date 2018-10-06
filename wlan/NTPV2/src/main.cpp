/** NTP: Zeit von einem Time Server aus dem Internet holen und setzen
*/
#include "mbed.h"
#include "TCPSocket.h"

#include "ESP8266Interface.h"
#include "NTPClient.h"
#include "OLEDDisplay.h" 

ESP8266Interface wifi(MBED_CONF_APP_WIFI_TX, MBED_CONF_APP_WIFI_RX);
OLEDDisplay oled( PTE26, PTE0, PTE1 );

DigitalOut led( D10 );
 
int main() 
{
	printf("NTP Client example (using WiFi)\r\n");

#ifdef MBED_MAJOR_VERSION
    printf("Mbed OS version %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
#endif

    printf("\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID);
    int ret = wifi.connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
    if (ret != 0)
    {
        printf("\nConnection error: %d\n", ret);
        return -1;
    }
   
    // hole Zeit vom Internet
    NTPClient ntp( &wifi) ;
	time_t timestamp = ntp.get_timestamp();
	if (timestamp < 0)
		printf("An error occurred when getting the time. Code: %ld\r\n", timestamp);
	else
		printf("Current time is %s\r\n", ctime(&timestamp));
	wifi.disconnect();

	// set the time
	set_time( timestamp );
 
    while(1) 
    {
       time_t seconds = time(NULL);
       oled.clear(); 
       oled.printf( "\rDate & Time: \r\n%s", ctime(&seconds) );
        
       led=!led;
       wait(0.8);
    }
}                 

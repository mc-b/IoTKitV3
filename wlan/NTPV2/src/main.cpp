/** NTP: Zeit von einem Time Server aus dem Internet holen und setzen
*/
#include "mbed.h"
#include "TCPSocket.h"
#include "network-helper.h"
#include "NTPClient.h"
#include "OLEDDisplay.h" 

// UI
OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );

DigitalOut led( MBED_CONF_IOTKIT_LED1 );
 
int main() 
{
	printf("NTP Client example (using WiFi)\r\n");

#ifdef MBED_MAJOR_VERSION
    printf("Mbed OS version %d.%d.%d\n\n", MBED_MAJOR_VERSION, MBED_MINOR_VERSION, MBED_PATCH_VERSION);
#endif

    printf("\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID);
    // Connect to the network with the default networking interface
    // if you use WiFi: see mbed_app.json for the credentials
    NetworkInterface* wifi = connect_to_default_network_interface();

    if ( !wifi )
    {
        printf("Cannot connect to the network, see serial output\n");
        return 1;
    }
   
    // hole Zeit vom Internet
    NTPClient ntp( wifi) ;
	time_t timestamp = ntp.get_timestamp();
	if (timestamp < 0)
		printf("An error occurred when getting the time. Code: %ld\r\n", timestamp);
	else
		printf("Current time is %s\r\n", ctime(&timestamp));
	wifi->disconnect();

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

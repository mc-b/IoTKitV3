Einfaches HTTP-Beispiel
-----------------------

Basiert auf: [http://os.mbed.com/teams/sandbox/code/http-example/](http://os.mbed.com/teams/sandbox/code/http-example/).

Angepasst an IoTKit V3:
* easy-connect entfernt
* Update auf mbed OS V5.10
* Import `ESP8266Interface.h` und Instanzierung `ESP8266Interface` und `wifi.connect` statt easy-connect Abhandlung.
* `mbed_app.json` ersetzt durch `ESP8266Interface` kompatible Einstellungen.

Änderungen in `main.cpp`

	#include "ESP8266Interface.h"
	...
	
	ESP8266Interface wifi(MBED_CONF_APP_WIFI_TX, MBED_CONF_APP_WIFI_RX);
	
	int main() 
	{
	    printf("\nConnecting to %s...\n", MBED_CONF_APP_WIFI_SSID);
	    int ret = wifi.connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
	    if (ret != 0) {
	        printf("\nConnection error: %d\n", ret);
	        return -1;
	    }
	
	    // Do a GET request to httpbin.org
	    {
			// network durch &wifi ersetzt 
	       HttpRequest* get_req = new HttpRequest(&wifi, HTTP_GET, "http://httpbin.org/status/418");	
	       
	       
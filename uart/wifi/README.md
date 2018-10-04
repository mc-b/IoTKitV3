ESP8266
-------

![](https://upload.wikimedia.org/wikipedia/commons/thumb/8/84/ESP-01.jpg/440px-ESP-01.jpg) 

Handelsübliches ESP8266-Modul mit Prozessor-Chip (links) und externen Flash-Speicher (rechts) für die Firmware. Im oberen Bildbereich die gedruckte WLAN-Antenne

- - -

Der ESP8266 ist ein kostengünstiger und mit geringem Leistungsbedarf ausgeführter 32-Bit-Mikrocontroller der chinesischen Firma espressif und ermöglicht durch seine offene Bauweise den Aufbau von WLAN-gesteuerten Aktuatoren und Sensoren.

Der IoTKit V3 wird mittels dem [ESP8266 WLAN Modem](https://de.wikipedia.org/wiki/ESP8266) ans Internet angeschlossen.

Der IoTKit V3 kommuniziert mittels UART mit dem [ESP8266](https://de.wikipedia.org/wiki/ESP8266) dabei werden folgende Pins verwendet:
* TX - PTC15
* RX = PTC14

Die eigentliche Konfiguration der Schnittstelle erfolgt in der Datei `mbed_app.json`. Bei der Verwendung des [esp8266 Drivers](https://github.com/ARMmbed/esp8266-driver.git) sehen die Einträge wie folgt aus:

	{
	    "config": {
	        "wifi-shield": {
	            "help": "Options are internal, WIFI_ESP8266, WIFI_ISM43362, WIFI_IDW0XX1",
	            "value": "WIFI_ESP8266"
	        },
	        "wifi-ssid": {
	            "help": "WiFi SSID",
	            "value": "\"LERNKUBE\""
	        },
	        "wifi-password": {
	            "help": "WiFi Password",
	            "value": "\"l3rnk4b3\""
	        },
	        "wifi-tx": {
	            "help": "TX pin for serial connection to external device",
	            "value": "PTC15"
	        },
	        "wifi-rx": {
	            "help": "RX pin for serial connection to external device",
	            "value": "PTC14"
	        },
	        "wifi-debug": {
	            "value": true
	        }
	    }
	}

Das Verwendete [ESP8266 WLAN Modem](https://de.wikipedia.org/wiki/ESP8266) beinhaltet noch die Firmware Version 1.5 weshalb, je nach mbed OS Version
die Firmware Abfrage im Sourcecode des Drivers geändert werden muss:

	sed -i -e"s/ESP8266_VERSION 2/ESP8266_VERSION 1/" esp8266-driver/ESP8266Interface.cpp
	
	sed -i -e"s/ESP8266_SDK_VERSION 2000000/ESP8266_SDK_VERSION 1000000/" esp8266-driver/ESP8266/ESP8266.h
	
Fehlende oder nicht funktionierte Methoden konnten nicht festgestellt werden.	

### Links

*  [Arm Mbed Online Compiler](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/wifi/)
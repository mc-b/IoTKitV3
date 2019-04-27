## WLAN (WiFi)
***

> [⇧ **Home**](../README.md)

![](../images/ESP8266.png) 

Handelsübliches ESP8266-Modul. Im oberen Bildbereich die gedruckte WLAN-Antenne

- - -

[Wireless Local Area Network](https://de.wikipedia.org/wiki/Wireless_Local_Area_Network) (Wireless LAN bzw. W-LAN, meist WLAN; deutsch drahtloses lokales Netzwerk) bezeichnet ein lokales Funknetz, wobei meist ein Standard der IEEE-802.11-Familie gemeint ist. Für diese engere Bedeutung ist in manchen Ländern (z. B. USA, Großbritannien, Kanada, Niederlande, Spanien, Frankreich, Italien) weitläufig beziehungsweise auch synonym der Begriff Wi-Fi gebräuchlich. 

Das IoTKit K64F Board wird mittels dem [ESP8266 WLAN Modem](https://de.wikipedia.org/wiki/ESP8266) ans Internet angeschlossen. Die Verbindung erfolgt mittels Serieller Schnittstelle ([UART](../uart/)).

Das DISCO_L475VG_IOT01A Boards wird mittels dem [Wi-Fi® module Inventek ISM43362-M3G-L44](https://www.inventeksys.com/wifi/wifi-modules/ism4336-m3g-l44-e-embedded-serial-to-wifi-module/) ans Internet angeschlossen. Die Verbindung erfolgt mittels [SPI-Bus](../spi/).

Die benötigten Libraries befinden sich, entweder direkt in der [mbed-os](https://github.com/ARMmbed/mbed-os/) oder der [IoTKit](https://os.mbed.com/teams/IoTKitV3/code/IoTKit/)-Library. Die Konfiguration erfolgen in `mbed_app.conf`.

Um mit dem Internet zu kommunizieren ist die `"network-helper.h"` Datei aus der [IoTKit](https://os.mbed.com/teams/IoTKitV3/code/IoTKit/)-Library zu inkluden und die Funktion `connect_to_default_network_interface` aufzurufen.

**Beispiel:**

```cpp

    #include "mbed.h"
    #include "network-helper.h"
    
    int main() 
    {
        NetworkInterface* wifi = connect_to_default_network_interface();
        if ( !wifi )
        {
            printf("Cannot connect to the network, see serial output\n");
            return 1;
        }
```

Je nach Board wird dann das entsprechende WLAN Modem initialisert und eine IP-Adresse gelöst. Ab dort ist die Kommunikation mit dem Internet möglich.

Die WLAN SSID und Password steht in der Datei `mbed_app.json`.

**Beispiel**:

```js

    "config": {
        "wifi-ssid": {
            "help": "WiFi SSID",
            "value": "\"LERNKUBE\""
        },
        "wifi-password": {
            "help": "WiFi Password",
            "value": "\"l3rnk4b3\""
        },
```        

### Beispiel(e)

* [Network Time Protocol (NTP)](#network-time-protokoll-ntp) - holt die Zeit vom Internet und setzt die interne Uhr des Boards.
* [LowLevel Wifi Zugriff](wifi/src/main.cpp) - WLAN Zugriff, ohne `"network-helper.h"` Datei.

### Links

* [Konfiguration ESP8266](../uart#konfiguration-esp8266)
* [Gegenüberstellung HTTP, MQTT, CoAP](https://os.mbed.com/blog/entry/Using-HTTP-HTTPS-MQTT-and-CoAP-from-mbed/)

## Network Time Protocol (NTP)
***

> [⇧ **Nach oben**](#)

![](../images/NTPArchitecture.png) 

NTP Hierarchie, Quelle: [Wikipedia](http://de.wikipedia.org/wiki/Network_Time_Protocol)

- - -

Das Network Time Protocol (NTP) ist ein Standard zur Synchronisierung von Uhren in Computersystemen über paketbasierte Kommunikationsnetze. NTP verwendet das verbindungslose Transportprotokoll UDP. NTP wurde speziell entwickelt, um eine zuverlässige Zeitangabe über Netzwerke mit variabler Paketlaufzeit zu ermöglichen.

Im allgemeinen Sprachgebrauch bezeichnet NTP sowohl das Protokoll als auch die Software-Referenzimplementierung.

NTP nutzt ein hierarchisches System verschiedener Strata (Plural von Stratum). Als Stratum 0 bezeichnet man das Zeitnormal, beispielsweise eine Atomuhr oder eine Funkuhr (genauer: Zeitzeichenempfänger) (GNSS, DCF77). Die unmittelbar mit ihm gekoppelten NTP-Server heißen Stratum 1. Jede weitere abhängige Einheit erhält bei der Bezeichnung eine höhere Nummer (Stratum 2, Stratum 3 …).

Das Network Time Protocol ist in der [NTP Library](https://os.mbed.com/users/donatien/code/NTPClient/) abgebildet.

### Anwendungen 

*   Alle Arten von Zeit basierenden Anwendungen, wie Zeitschaltuhren etc.

### Beispiel(e)

Das Beispiel [NTPV2](NTPV2/src/main.cpp) holt die Zeit vom Internet und setzt die interne Uhr des Boards.

**Compilieren**

| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler           | [template](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/template/) enthält das NTP Beispiel |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/wlan/NTPV2; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/wlan/NTPV2` |


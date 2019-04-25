## UART (Universal Asynchronous Receiver Transmitter)
***

> [⇧ **Home**](../README.md)

![](../images/UART.png)

- - - 

Der asynchrone serielle Datenstrom, wie ihn ein sog. CMOS-UART erzeugt (logisch 0 und 1). Das untere Diagramm zeigt die dazu invertierten Spannungspegel auf der RS-232-Schnittstelle. [Quelle Wikipedia](http://de.wikipedia.org/wiki/Universal_Asynchronous_Receiver_Transmitter)

Universal Asynchronous Receiver Transmitter, kurz UART, ist eine elektronische Schaltung, die zur Realisierung digitaler serieller Schnittstellen dient. Dabei kann es sich sowohl um ein eigenständiges elektronisches Bauelement (ein UART-Chip bzw. -Baustein) oder um einen Funktionsblock eines höherintegrierten Bauteils (z. B. eines Mikrocontrollers) handeln.

Eine UART-Schnittstelle dient zum Senden und Empfangen von Daten über eine Datenleitung und bildet den Standard der seriellen Schnittstellen an PCs und Mikrocontrollern. Auch im industriellen Bereich ist die Schnittstelle mit verschiedenen Interfaces (z. B. [RS-232](http://de.wikipedia.org/wiki/RS-232) oder [EIA-485](http://de.wikipedia.org/wiki/EIA-485)) sehr verbreitet.

Die Daten werden als serieller digitaler Datenstrom mit einem fixen Rahmen übertragen, der aus einem Start-Bit, fünf bis maximal neun Datenbits, einem optionalen Parity-Bit zur Erkennung von Übertragungsfehlern und einem Stopp-Bit besteht. Um dem Empfänger eine Synchronisationszeit auf den Takt der empfangenen Daten einzuräumen, kann das Stopp-Bit auf das 1,5 oder 2-fache der normalen Übertragungszeit eines Bits verlängert werden. Das wird als 1,5 bzw. 2 Stopp-Bits bezeichnet.

**In einfachen Mikrocontroller-Systemen werden Daten häufig über UART-Schnittstellen ausgetauscht, die ohne Handshake, nur über Rx und Tx, verwirklicht sind. Diese für kurze Entfernungen geeignete, auch [CMOS-UART bzw. TTL-UART](http://de.wikipedia.org/wiki/Logikpegel) genannte Implementierung wird von praktisch allen Mikrocontrollern unterstützt und kann bei entsprechend geringen Übertragungsraten auch über Software realisiert werden.**

Um den [CMOS-UART bzw. TTL-UART](http://de.wikipedia.org/wiki/Logikpegel) Pegel für den USB Bus verfügbar zu machen, kann ein [USB Serial Adapter](http://arduino.cc/en/Main/USBSerial) verwendet werden. Boards haben diesen, in der Regel, integriert (mbed - Ja, Arduino UNO - Ja, [Arduino Mini - Nein](http://www.arduino.cc/en/Main/ArduinoBoardMini) )

Die Standardeinstellungen für den Seriellen Port (USB) sind 9600 baud, 8 bits, 1 stop bit, no parity (aka 9600-8-N-1).

Um Daten auf die Serielle Schnittstelle auszugeben, sind keine zusätzlichen Objekte erforderlich. Die Serielle Schnittstelle wird automatisch geöffnet und Daten können mittels [printf](http://www.cplusplus.com/reference/cstdio/printf/) ausgegeben und mittels [scanf](http://www.cplusplus.com/reference/cstdio/scanf/) ausgelesen werden.

### Anwendungen 

* Ausgabe von Debug Informationen
* Fernsteuerung des Gerätes z.B. wie bei 3D Druckern
* Board - PC Kommunikation
* Ansprechen von Modems wie [Bluetooth](http://developer.mbed.org/platforms/FRDM-K64F/#features), [WLAN](https://os.mbed.com/questions/4993/How-to-interface-esp8266-wifi-module/), [GPS](http://developer.mbed.org/cookbook/GlobalSat-EM-406-GPS-Module)

### Beispiel(e)

* [Serielle Ausgabe](Serialprintf/src/main.cpp) - demonstriert die verschiedenen Ausgabemöglichkeiten mit `printf`.
* [Serielle Eingabe](Serialscanf/src/main.cpp) - demonstriert die verschiedenen Eingabemöglichkeiten mit `scanf`. 
* [Serielle Schnittstelle](SerialAll/src/main.cpp) - Ausgabe, mittels `printf` auf allen Seriellen Schnittstelle des Boards. Muss für DISCO_L475VG_IOT01A angepasst werden.
* [Serial Master](SerialMaster/src/main.cpp), [Serial Slave](SerialSlave/src/main.cpp) - Kommunikation zwischen zwei Boards über die Serielle Schnittelle.
* [WLAN Modem ESP8266 lowlevel](ESP8266/) - Ansprechen des ESP8266 WLAN Modems via AT-Befehlen (nur IoTKit K64F Board).

Für die Beispiele muss ein Terminalemulations Programm (siehe [Links](#links)) und für Windows 10 zusätzlich ein Treiber installiert werden. 

**Compilieren**

| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [Serialprintf](https://developer.mbed.org/teams/smdiotkitch/code/Serialprintf/) |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/uart/Serialprintf; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/uart/Serialprintf` |
- - -
| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [Serialscanf](https://developer.mbed.org/teams/smdiotkitch/code/Serialscanf/) |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/uart/Serialscanf; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/uart/Serialscanf` |
- - -
| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [SerialAll](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/SerialAll/) |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/uart/SerialAll; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/uart/SerialAll` |
- - -
| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [ESP8266](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/ESP8266/) |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/uart/ESP8266; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/uart/ESP8266` |

### Links

* Terminalemulations Programme: [Windows](http://sourceforge.jp/projects/ttssh2/releases/), [Mac](http://freeware.the-meiers.org/), [Linux](http://manpages.ubuntu.com/manpages/vivid/man8/picocom.8.html)
* [PC Driver (nur Windows)](https://os.mbed.com/handbook/Windows-serial-configuration)
* [printf Reference](http://www.cplusplus.com/reference/cstdio/printf/)
* [scanf Reference](http://www.cplusplus.com/reference/cstdio/scanf/)

Software
--------

## Betriebssystem

Der IoTKit V2 verwendet [ARM mbed OS](https://www.mbed.com/en/platform/mbed-os/).

ARM mbed OS ist ein Open-Source-Embedded-Betriebssystem, das speziell für die "Dinge" im Internet der Dinge entwickelt wurde.

Es enthält alle Funktionen, die benötigt werden, um ein angeschlossenes Produkt auf Basis eines ARM Cortex-M Mikrocontrollers zu entwickeln, einschliesslich Sicherheit, Konnektivität, RTOS und Treiber für Sensoren und E / A-Geräte.

## Compiler

Als Compiler wird [PlatformIO Core](http://platformio.org/get-started/cli) verwendet.

PlatformIO unterstützt neben mbed eine Vielzahl von weiteren Boards und hat den Vorteil, dass die weiteren Komponenten wie
* C/C++ Compiler
* mbed Libraries

automatisch, bei der ersten Compilierung, installiert werden.

## Installation

Zuerst muss [Python 2.7](https://www.python.org/downloads/) installiert werden.

Anschliessend Bash Umgebung starten und Repository clonen

    git clone https://github.com/mc-b/IoTKitV2.git

Mittels dem Python Packetmanager PlatformIO 

	pip install -U platformio
	
und zum Schluss den Compiler für mbed Installieren

	pio platform install https://github.com/platformio/platform-freescalekinetis.git#release/v1.4.0

Die volle Dokumentation ist auf [PlatformIO](http://docs.platformio.org/en/latest/installation.html) zu finden.

**ACHTUNG**: die Beispiele sind nur mit dieser Version getestest.

Um die mbedRPC Beispiele compilieren zu können ist die Datei `platformio/packages/framework-mbed/libraries/rpc/RpcClasses.h` wie folgt zu patchen: überflüssigen Methodenaufruf nach read_u16 entfernen:

	117c117
	<             {"read_u16", rpc_method_caller<unsigned short, RpcAnalogIn, &RpcAnalogIn::read_u16>},
	---
	>             //{"read_u16", rpc_method_caller<unsigned short, RpcAnalogIn, &RpcAnalogIn::read_u16>},	

Für Windows wird [Git Bash](https://git-scm.com/) benötigt. **Wichtig:** Git ohne Umwandlung CR/LF Option installieren, bzw. diese nicht aktiveren bei der Installation.

## Programme compilieren und uploaden

Vor dem ersten Aufruf des Compilier sind die `lib` Unterverzeichnisse nach `<PlatformIO-Installation>/platformio/lib` zu kopieren.

Anschliessend kann in ein beliebiges Verzeichnis gewechselt werden und der Compiler aufgerufen werden, z.B.:

	cd gpio/DigitalOut
	pio run
	
Compilieren mittels anschliessend Upload auf das Board:

	pio run -t upload
	
Anschliessend ist der Reset Button auf dem Board zu drücken.

### Serielle Console

PlatformIO beinhaltet ein Terminalprogramm um die Ausgabe via Serieller Schnittstelle des mbed Boards auszugeben. 

Dieses kann wie folgt getestet werden:

	cd uart/SerialAll
	pio run -t upload
	pio device monitor





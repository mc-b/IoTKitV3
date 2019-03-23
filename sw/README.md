Software
--------

## Betriebssystem

Der IoTKit V3 verwendet [ARM mbed OS](https://www.mbed.com/en/platform/mbed-os/).

ARM mbed OS ist ein Open-Source-Embedded-Betriebssystem, das speziell für die "Dinge" im Internet der Dinge entwickelt wurde.

Es enthält alle Funktionen, die benötigt werden, um ein angeschlossenes Produkt auf Basis eines ARM Cortex-M Mikrocontrollers zu entwickeln, einschliesslich Sicherheit, Konnektivität, RTOS und Treiber für Sensoren und E / A-Geräte.

## Entwicklungsumgebung

Als Entwicklungsumgebung kann
* der [Arm Mbed Online Compiler (empfohlen)](https://os.mbed.com/compiler/)
* das [mbed CLI](https://github.com/ARMmbed/mbed-cli)

Wird der [Arm Mbed Online Compiler](https://os.mbed.com/compiler/) verwendet, ist der Sourcecode bzw. Link unten an der jeweiligen Seite, gekennzeichnet mit **Arm Mbed Online Compiler**, zu verwenden.

Ist kein Link **Arm Mbed Online Compiler** vorhanden, kann das [IoTKit V3 Template](https://os.mbed.com/teams/IoTKitV3/code/template/) verwendet werden. Dabei ist der Inhalt von `main.cpp` mit dem Inhalt des Beispiels zu ersetzen.

**ACHTUNG**: kann der IoTKit V3 nicht mehr Programmiert werden, Upload endet sofort und es erscheint eine Datei `FAIL.TXT`, ist leicht am Encoder zu drehen und das Board ein- und auszustecken.

### Installation und Quick Start mbed-cli 

[mbed cli](https://github.com/ARMmbed/mbed-cli) mit allen Abhängigkeiten (Python, GCC_ARM) wie unter [Installation](https://github.com/ARMmbed/mbed-cli#installation) beschrieben, installieren.

Globale Konfigurationen für Board und Compiler setzen.

	mbed config --global TARGET K64F
	mbed config --global TOOLCHAIN GCC_ARM

[IoTKit V3 Template](https://os.mbed.com/teams/IoTKitV3/code/template/) importieren und compilieren

	mbed import http://os.mbed.com/teams/IoTKitV3/code/template/
	cd template
	mbed compile
	
Das compilierte Programm befindet sich im Verzeichnis `BUILD/K64F/GCC_ARM` mit Namen `template.bin`. Dieses ist auf das Laufwerk `DAPLINK` zu kopieren und der `Reset`-Button zu drücken.

Das Compilierte Programm baut eine Verbindung mit dem Internet auf (WLAN Einstellungen siehe `mbed_app.json`) und zeigt die aktuelle Zeit auf dem OLED Display an.
	
Kopieren in z.B. in PowerShell, wenn das Laufwerk DAPLINK D: ist.
	
	copy BUILD\K64F\GCC_ARM\template.bin D:\

Oder in der Git/Bash unter Windows

	cp BUILD/K64F/GCC_ARM/template.bin /d/
	
Um die IoTKitV3 Beispiele zu compilieren ist das `src` Verzeichnis im `template` Verzeichnis wegzulöschen (wegen Fehler doppelter `main`) und das IoTKitV3 Repository zu clonen.

Z.B. in der PowerShell

	del src
	cd ..
	git clone https://github.com/mc-b/IoTKitV3.git
	
Die jeweiligen Beispiele können dann wie folgt compiliert werden, z.B. DigitalOut, HallSensorAlarm

	cd template
	mbed compile --source . --source ../IoTKitV3/gpio/DigitalOut/src
	
oder 
	
	mbed compile --source . --source ../IoTKitV3/cloud/HallSensorAlarm/src
	
Und dann wie, oben beschrieben, auf das Board zu kopieren und dieses zu Resetten.

**Optional** Beispiele für Eclipse aufbereiten

	mbed export -i eclipse_gcc_arm
	
Anschliessend mittels File -> Import -> Existing Projects `template` Projekt in Workspace importieren.	

**Hinweise**:
* Ab mbed OS V5.10 ist die ESP8266 Driver Library Bestandteil von mbed OS.
* Als Nachteil für das schnellere Compilieren, ist zu Erwähnen, dass die Programme grösser sind als normal, weil alle Libraries mit verlinkt werden.

#### Serielle Console

Die mbed CLI beinhaltet ein Terminalprogramm um die Ausgabe via Serieller Schnittstelle des mbed Boards auszugeben.

	mbed sterm

Damit es Funktioniert muss, auf Windows, zuerst der [Windows Serial Driver](https://os.mbed.com/handbook/Windows-serial-configuration) installiert werden.

Siehe auch [UART (Universal Asynchronous Receiver Transmitter)](../uart/) 

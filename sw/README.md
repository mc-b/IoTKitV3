Software
--------

## Betriebssystem

Der IoTKit V3 verwendet [ARM mbed OS](https://www.mbed.com/en/platform/mbed-os/).

ARM mbed OS ist ein Open-Source-Embedded-Betriebssystem, das speziell für die "Dinge" im Internet der Dinge entwickelt wurde.

Es enthält alle Funktionen, die benötigt werden, um ein angeschlossenes Produkt auf Basis eines ARM Cortex-M Mikrocontrollers zu entwickeln, einschliesslich Sicherheit, Konnektivität, RTOS und Treiber für Sensoren und E / A-Geräte.

## Compiler

Als Entwicklungsumgebung wird [Visual Studio Code](https://code.visualstudio.com/) mit der [PlatformIO](https://platformio.org/) Erweiterungen verwendet.

PlatformIO unterstützt neben mbed eine Vielzahl von weiteren Boards und hat den Vorteil, dass die weiteren Komponenten wie
* C/C++ Compiler
* mbed Libraries

automatisch, bei der ersten Compilierung, installiert werden.

**Installation und Quick Start **

Siehe:
* [PlatformIO IDE for VSCode](https://platformio.org/install/ide?install=vscode)
* [Quick Start Guide](https://docs.platformio.org/en/latest/ide/vscode.html#quick-start)

Anschliessend muss das Repository [https://github.com/mc-b/IoTKitV3](https://github.com/mc-b/IoTKitV3) in VSCode [geklont](https://code.visualstudio.com/docs/editor/versioncontrol#_cloning-a-repository) werden.

Zu Testzwecken kann das Programm `gpio/DigitalOut` verwendet werden.

Dazu muss der **PIO Home** Tab geöffnet werden und mittels **Open Project** das Verzeichnis `gpio/DigitalOut` der Workspace hinzugefügt werden.

Mittels den untereren Buttons (Pfeil nach links) kann das Programm compiliert und auf das Board uploadet werden.
	
Anschliessend ist der Reset Button auf dem Board zu drücken.

### Serielle Console

Die PlatformIO IDE beinhaltet ein Terminalprogramm um die Ausgabe via Serieller Schnittstelle des mbed Boards auszugeben.

Der Serial Monitor Button (Steckersymbol) ist unten auf der Statusleiste.
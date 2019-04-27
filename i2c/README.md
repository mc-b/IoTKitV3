## I²C/TWI (Inter-Integrated Circuit, bzw. Two-Wire-Interface)
***

> [⇧ **Home**](../README.md)

![](../images/I2C.png) 

[I²C-Bus mit einem Master und drei Slaves](http://de.wikipedia.org/wiki/I%C2%B2C)

- - -

I²C, für englisch Inter-Integrated Circuit, im Deutschen gesprochen als I-Quadrat-C oder englisch I-Squared-C oder I-2-C, ist ein von Philips Semiconductors (heute NXP Semiconductors) entwickelter serieller Datenbus.

Der Bus wurde 1982 von Philips eingeführt zur Geräte internen Kommunikation zwischen ICs in z.B. CD-Spielern und Fernsehgeräten.

I²C ist als **Master-Slave-Bus** konzipiert. Ein Datentransfer wird immer durch einen Master (die MCU auf dem Board) initiiert; der über eine Adresse angesprochene Slave (die Sensoren auf dem Board) reagiert darauf. Mehrere Master sind möglich (Multimaster-Mode). Im Multimaster-Mode können zwei Master-Geräte direkt miteinander kommunizieren, dabei arbeitet ein Gerät als Slave.

Der **Bustakt** wird immer vom Master ausgegeben. Für die verschiedenen Modi ist jeweils ein maximal erlaubter Bustakt vorgegeben. In der Regel können aber auch beliebig langsamere Taktraten verwendet werden, falls diese vom Master-Interface unterstützt werden. Bestimmte ICs (z.B. Analog-Digital-Umsetzer) benötigen jedoch eine bestimmte, minimale Taktfrequenz, um ordnungsgemäss zu funktionieren.

Eine **Standard-I²C-Adresse ist das erste vom Master gesendete Byte**, wobei die ersten sieben Bit die eigentliche Adresse darstellen und das achte Bit (R/W-Bit) dem Slave mitteilt, ob er Daten vom Master empfangen soll (LOW), oder Daten an den Master zu übertragen hat (HIGH). I²C nutzt daher einen Adressraum von 7 Bit, was bis zu **112 Knoten auf einem Bus** erlaubt (16 der 128 möglichen Adressen sind für Sonderzwecke reserviert).

Das Protokoll des I²C-Bus ist von der Definition her recht einfach, aber physikalisch auch recht störanfällig. Auch ist er **ungeeignet zur Überbrückung größerer Entfernungen**. Der Bus kann jedoch mit speziellen Treibern auf ein höheres Strom- und/oder Spannungslevel umgesetzt werden, wodurch der Störabstand und die mögliche Leitungslänge steigen.

Der Bus braucht zur Terminierung zwei Widerstände von ca. 2.2K - 4.7K Ohm (je nach Länge der Kabel, siehe 6-Achsen-Sensor) und alle Geräte müssen an der gleichen Ground Leitung angeschlossen sein.

**Die I2C Sensoren und Aktoren auf dem Board sind anhand der Hexadecimalen Nummer, z.B. 0x78 neben dem OLED Display, zu erkennen.**

### Anwendungen 

*   Ansprechen von Peripherie Bausteinen wie Temperatursensor, [3-axis Beschleunigungsmesser (Accelerometer) and Magnetfeldstärkenmessgerät (Magnetometer)](http://developer.mbed.org/users/JimCarver/code/FXOS8700Q/)
*   Ansprechen von Analog/Digital and Digital/Analog IC&#039;s, z.B. [PCF8591](http://developer.mbed.org/users/wim/notebook/pcf8591-i2c-4-channel-8-bit-ad-and-1-channel-8-bit/)
*   Verbinden von Boards, auch über grössere Distanzen. Siehe [www.mikrokontroller.net](http://www.mikrocontroller.net/articles/I%C2%B2C) und [RocNet](http://wiki.rocrail.net/doku.php?id=rocnet:rocnet-prot-de)

## Beispiele

**IoTKit K64F Board**

* [Proximity sensor, gesture and ambient light sensing (ALS) module (VL6180X)](#vl6180x)
* [low power, high sensitivity, RED, GREEN and BLUE color light sensor (RGB)](#ISL29125)

**DISCO_L475VG_IOT01A Board** - Anordnung der Sensoren siehe [Hardware](../hw#disco-l475vg-iot01a)

* [Time-of-Flight and gesture-detection sensor (VL53L0X)](#vl53l0x)

**Beide Boards**

* [Capacitive digital sensor for relative humidity and temperature (HTS221)](#HTS221)
* [High-performance 3-axis magnetometer (LIS3MDL)](#LIS3MDL)
* [3D accelerometer and 3D gyroscope (LSM6DSL)](#LSM6DSL)
* [mbed - Arduino Kommunikation](#mbed---Arduino-Kommunikation)

## VL6180X
***

> [⇧ **Nach oben**](#beispiele)

Der VL6180X ist das neueste Produkt, das auf der patentierten FlightSense ™ -Technologie von ST basiert . Dies ist eine bahnbrechende Technologie, die es ermöglicht, die absolute Entfernung unabhängig von der Zielreflektion zu messen. Anstatt die Entfernung durch Messung der vom Objekt reflektierten Lichtmenge zu messen (die maßgeblich von Farbe und Oberfläche beeinflusst wird), misst der VL6180X genau die Zeit, die das Licht braucht, um zum nächsten Objekt zu gelangen und zum Sensor zurückzusenden (Zeit Flug).

Der VL6180X kombiniert einen IR-Strahler, einen Bereichssensor und einen Umgebungslichtsensor in einem gebrauchsfertigen 3-in-1-Reflow-Gehäuse. Der VL6180X ist einfach zu integrieren und erspart dem Endprodukthersteller lange und kostspielige optische und mechanische Designoptimierungen.

Das Modul ist für den Betrieb mit geringer Leistung ausgelegt. Entfernungs- und ALS-Messungen können automatisch in benutzerdefinierten Intervallen durchgeführt werden. Mehrere Schwellenwert- und Interrupt-Schemata werden unterstützt, um Host-Operationen zu minimieren.


### Beispiel(e)

Das Beispiel [VL6180X](VL6180X/src/main.cpp) zeigt die Lichtstärke in LUX und die Entfernung eines Gegenstandes, z.B. der Hand, zum VL6180X an.

**Compilieren**

| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [VL6180X nur IoTKit K64F](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/VL6180X/) |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/i2c/VL6180X; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |

### Links

* [Produktseite](https://www.st.com/en/imaging-and-photonics-solutions/vl6180x.html)

## VL53L0X
***

> [⇧ **Nach oben**](#beispiele)

Das VL53L0X ist ein Time-of-Flight (ToF)  -Laser-Entfernungsmodul der neuen Generation.

Es bietet eine genaue Abstandsmessung unabhängig von den Zielreflexionen im Gegensatz zu herkömmlichen Technologien. 

Es misst absolute Distanzen bis zu 2 m und setzt damit neue Maßstäbe in Bezug auf das Leistungsspektrum und öffnet die Tür für verschiedene neue Anwendungen.

### Beispiel(e)

Das Beispiel [VL53L0X](VL53L0X/src/main.cpp) zeigt die Entfernung eines Gegenstandes, z.B. der Hand, zum VL53L0X an.

**Compilieren**

| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [VL53L0X](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/VL53L0X/) |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/i2c/VL53L0X` |

### Links

* [Produktseite](https://www.st.com/en/imaging-and-photonics-solutions/vl53l0x.html)

## ISL29125
***

> [⇧ **Nach oben**](#beispiele)

Der ISL29125 ist ein ROT, GRÜN und BLAUER Farblichtsensor (RGB) mit einer I2C Schnittstelle. 

Das hochmoderne Photodioden-Array bietet eine genaue RGB-Spektralantwort und hervorragende Lichtquelle zu Lichtquellenvariation (LS2LS). 

Der ISL29125 wurde entwickelt um IR in Lichtquellen zu melden und das vom Sonnenlicht bis zu dunklen Räumen. 

Das integrierte ADC meldet 50 Hz und 60 Hz Flimmern durch künstliches Licht zurück. 

Ein wählbarer Bereich ermöglicht dem Benutzer die Optimierung der Empfindlichkeit für spezifische Anwendungen.

### Beispiel(e)

Das Beispiel [ISL29125](ISL29125/src/main.cpp) gibt die Lichtwerte aus.

**Compilieren**

| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [ISL29125](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/ISL29125/) |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/i2c/ISL29125; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |

### Links

* [Produktseite](https://www.intersil.com/content/dam/Intersil/documents/isl2/isl29125.pdf)

## HTS221
***

> [⇧ **Nach oben**](#beispiele)

Der HTS221 ist ein ultrakompakter Sensor für relative Feuchte und Temperatur. Es enthält ein Sensorelement und einen Mischsignal-ASIC, um die Messinformationen über digitale serielle Schnittstellen bereitzustellen.

Das Sensorelement besteht aus einer Polymer-Dielektrikum-Planar-Kondensatorstruktur, die in der Lage ist, Schwankungen der relativen Feuchtigkeit zu detektieren, und wird unter Verwendung eines speziellen ST-Prozesses hergestellt.

### Beispiel(e)

Das Beispiel [HTS221](HTS221/src/main.cpp) gibt Temperatur und Luftfeuchtigkeit aus.

**Compilieren**

| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [HTS221](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/HTS221/) |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/i2c/HTS221; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/i2c/HTS221` |

### Links

* [Produktseite](https://www.st.com/en/mems-and-sensors/hts221.html)

## LIS3MDL
***

> [⇧ **Nach oben**](#beispiele)

Der LIS3MDL ist ein ultra-low-power Hochleistungs-Drei-Achsen-Magnetsensor.

Der LIS3MDL hat vom Benutzer wählbare Vollskalen von ± 4 / ± 8 / ± 12 / ± 16 Gauss.

Die Vorrichtung kann konfiguriert werden, um Unterbrechungssignale für die Magnetfelderfassung zu erzeugen.

Der LIS3MDL enthält eine serielle I2C-Busschnittstelle, die Standard und Fast Mode (100 kHz und 400 kHz) und SPI serielle Standardschnittstelle unterstützt.

### Beispiel(e)

Das Beispiel [LIS3MDL](LIS3MDL/src/main.cpp) erkennt den Nord- oder Südpool eines Magneten und fungiert als einfacher eCompass welcher die Himmelsrichtungen anzeigt. 

**Compilieren**

| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [LIS3MDL](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/LIS3MDL/) |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/i2c/LIS3MDL; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/i2c/LIS3MDL` |

### Links

* [Produktseite](https://www.st.com/en/mems-and-sensors/lis3mdl.html)

## LSM6DSL
 ***

> [⇧ **Nach oben**](#beispiele)

Das LSM6DSL ist ein System-in-Package mit einem digitalen 3D-Beschleunigungssensor und einem digitalen 3D-Gyroskop mit einer Leistung von 0,65 mA im Hochleistungsmode und ermöglicht durchgehend Low-Power-Funktionen für ein optimales Bewegungserlebnis für den Verbraucher.

Das LSM6DSL unterstützt die wichtigsten Betriebssystemanforderungen und bietet reale, virtuelle und Batch-Sensoren mit 4 kByte für die dynamische Datenaufzeichnung.

Die ST-Familie von MEMS-Sensormodulen nutzt die robusten und ausgereiften Fertigungsprozesse, die bereits für die Herstellung von mikrobearbeiteten Beschleunigungssensoren und Gyroskopen verwendet werden.

Das LSM6DSL verfügt über einen vollständigen Beschleunigungsbereich von ± 2 / ± 4 / ± 8 / ± 16 g und einen Winkelgeschwindigkeitsbereich von ± 125 / ± 245 / ± 500 / ± 1000 / ± 2000 dps.

Hohe Robustheit gegenüber mechanischen Schocks macht den LSM6DSL zur bevorzugten Wahl von Systementwicklern für die Herstellung und Herstellung von zuverlässigen Produkten.

### Beispiel(e)

* [LSM6DSL](LSM6DSL/src/main.cpp) erkennt den jeweiligen Neigungswinkel und zeigt diesen auf dem Display an.
* [LSM6DSL_Pedometer](LSM6DSL_Pedometer/src/main.cpp) zählt die Schritte und zeigt diese auf dem Display an.
* [LSM6DSL_Tilt](LSM6DSL_Tilt/src/main.cpp) erkennt wenn das Board schief gehalten wird.
* [LSM6DSL_SingleTap](LSM6DSL_SingleTap/src/main.cpp) erkennt wenn jemand auf das Board tippt.

**Compilieren**

| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [LSM6DSL](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/LSM6DSL/) |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/i2c/LSM6DSL; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/i2c/LSM6DSL` |
- - -
| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [LSM6DSL_Pedometer](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/LSM6DSL_Pedometer/) |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/i2c/LSM6DSL_Pedometer; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/i2c/LSM6DSL_Pedometer` |
- - -
| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [LSM6DSL_Tilt](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/LSM6DSL_Tilt/) |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/i2c/LSM6DSL_Tilt; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/i2c/LSM6DSL_Tilt` |
- - -
| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [LSM6DSL_SingleTap](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/LSM6DSL_Tilt/) |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/i2c/LSM6DSL_SingleTap; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/i2c/LSM6DSL_SingleTap` |

### Links

* [Produktseite](https://www.st.com/en/mems-and-sensors/hts221.html)
* [Weitere Beispiele](https://github.com/stm32duino/LSM6DSL/tree/master/examples)

##  mbed - Arduino Kommunikation
 ***

> [⇧ **Nach oben**](#beispiele)

Arduino sind weit verbreitet und Verfügen, in der Regel, über keinen direkten Ethernet Anschluss. Mittels dem I2C Bus können bestehende Arduino in das Internet der Dinge eingebunden werden.

Das mbed Board übernimmt dabei die Verbindung zum Internet und die Feinverteilung der Aufgaben auf die Arduinos mittels dem I2C Bus.

### Anwendungen 

*   Verbinden von Boards, über kleinere (1 Meter) oder grössere Distanzen. Siehe [www.mikrokontroller.net](http://www.mikrocontroller.net/articles/I%C2%B2C) und [RocNet](http://wiki.rocrail.net/doku.php?id=rocnet:rocnet-prot-de)
*   Verbindung mbed mit [Arduino](http://www.bot-thoughts.com/2011/09/i2c-mbed-reading-from-arduino.html)

### Beispiel(e)

* Das Beispiel [mbed2Arduino](mbed2Arduino/src/main.cpp) stellt eine Verbindung, über den Standard I2C Bus, zu einem Arduino Board her. Dazu der Sketch (auskommentierter Code am Ende des Programmes) auf den Arduino geladen werden.

**Compilieren**

| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler | [mbed2Arduino](https://developer.mbed.org/compiler/#import:/teams/smdiotkit1ch/code/mbed2Arduino/) |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/i2c/mbed2Arduino; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/i2c/mbed2Arduino` |

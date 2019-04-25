## Wearables
***

> [⇧ **Home**](../README.md)

Wearables (Tragbare Computer), z.B. Armbanduhren, die ständig den Puls messen, Brillen, deren Innenseiten als Bildschirm dienen oder Kleidungsstücke, in die elektronische Hilfsmittel zur Kommunikation und Musikwiedergabe eingearbeitet sind.

Diese Wearables verwenden sehr oft das Bluetooth Protokoll. Auf dem IoTKit K64F und auf dem DISCO-L475VG-IOT01A Board befindet sich ein Bluetooth Modem, um ein Wearable zu simulieren.

## Beispiele

* [Herzfrequenzmesser](#herzfrequenzmesser)
* [Beacon](#beacons)

## Herzfrequenzmesser
***

> [⇧ **Nach oben**](#beispiele)

![](../images/BLEHeartRate.png)

nRF Connect App Printscreen

- - -

**Material:**
* mbed Bluetooth kompatibles Board oder Shield wie
    * [IoTKit K64F Board](git@github.com:mc-b/IoTKitV3.git)
    * [DISCO-L475VG-IOT01A Board](https://os.mbed.com/platforms/ST-Discovery-L475E-IOT01A/)
    * [micro:bit](https://os.mbed.com/platforms/Microbit/)
    * [Seeed Arch BLE Shield](https://os.mbed.com/platforms/Seeed-Arch-BLE/)
* Smartphone mit nRF Connect App

**Installation**

* mbed Programm [BLE_HeartRate](https://os.mbed.com/teams/ST/code/mbed-os-example-ble-HeartRate/) in Online Compiler importieren und, beim IoTKit K64F, Board (rechts open) auf FRDM-K64F umstellen. Für das DISCO-L475VG-IOT01A Board oder den micro:bit sind keine Anpassungen nötig.
* nRF Connect App auf Smartphone installieren und starten.
* Nach neuen Geräten scannen.
* `HRM...` Gerät Verbinden und Herzfrequenz auslesen. 

### Beispiel(e)

* [HeartRate](HeartRate/src/main.cpp) simuliert die Herzfequenz und überträgt diese mittels Bluetooth auf das Smartphone.

**Compilieren**

| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler           | [HeartRate](https://os.mbed.com/teams/ST/code/mbed-os-example-ble-HeartRate/)  |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/bluetooth/HeartRate; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/bluetooth/HeartRate` |

### Code Anpassungen für IoTKit K64F Board (nur mbed Online Compiler)

Um dieses Verwenden zu können, müssen im Ordner `shields/TARGET_ST_BLUENRG/` in der Datei `mbed_lib.json` die Pin's wie folgt ergänzt werden:

        "K64F": {
            "target.macros_add": ["BLUENRG_PIN_SPI_MOSI=PTA16",
                                  "BLUENRG_PIN_SPI_MISO=PTC7",
                                  "BLUENRG_PIN_SPI_nCS=PTA14",
                                  "BLUENRG_PIN_SPI_RESET=PTA12",
                                  "BLUENRG_PIN_SPI_IRQ=PTA13",
                                  "BLUENRG_PIN_SPI_SCK=PTC5"]            
        },

Die Pins entsprechen dem SPI-0 auf dem IoTKit K64F.

### Links

* Weitere Beispiele (rechts unten) auf [Board Overview Site](https://os.mbed.com/platforms/ST-Discovery-L475E-IOT01A/). Müssen, für das IoTKit K64F Board wie oben Beschrieben, angepasst werden.
* [mbed Bluetooth Team](https://os.mbed.com/teams/Bluetooth-Low-Energy/)
* [Bluetooth Home Page](https://www.bluetooth.com/)
* [YouTube Mbed Office Hours - Bluetooth Low Energy](https://www.youtube.com/watch?v=j5RJ6UfkylA)

## Beacons
***

> [⇧ **Nach oben**](#beispiele)


Das Wort [Beacon](https://de.wikipedia.org/wiki/IBeacon) leitet sich von dem englischen Begriff für Leuchtfeuer ab und beschreibt recht genau das Funktionsprinzip. 

Beacon basiert auf einem Sender-Empfänger-Prinzip. Dazu werden im Raum kleine Sender (Beacons) als Signalgeber platziert, die in festen Zeitintervallen Signale senden. Kommt ein Empfänger – z. B. ein Smartphone mit einer installierten Mobile App, die für den Empfang von Beacon Signalen konfiguriert ist – in die Reichweite eines Senders, kann die Universally Unique Identifier (UUID) des Senders identifiziert und seine Signalstärke gemessen werden. 

Sind mindestens drei Beacons in Reichweite des Endgeräts, lässt sich z. B. durch Trilateration oder das Fingerprinting-Verfahren die Position des Empfängers im zweidimensionalen Raum errechnen. Zur Ermittlung eines Standortes in einem dreidimensionalen Raum sind vier Beacons in Reichweite erforderlich.

**Installation**

* Eines der Beacon Beispiel in Online Compiler importieren und, beim IoTKit K64F, Board (rechts open) auf FRDM-K64F umstellen. Für das DISCO-L475VG-IOT01A Board oder den micro:bit sind keine Anpassungen nötig.
* Beacon Scanner App auf Smartphone installieren und starten.
* Nach neuen Geräten scannen.
* Pro Gerät wird die Major und Minor Nummer oder bei den Eddystone Beispielen ein URL angezeigt.

Die Nummern bzw. der URL können in den entsprechenden Programmen angepasst werden, z.B. 
  
    uint16_t majorNumber = 1234;
    uint16_t minorNumber = 3344;

### Beispiel(e)

* [Beacon](Beacon/src/main.cpp) sendet ein Funkfeuer via Bluetooth aus, welches von einem Smartphone empfangen werden kann.

**Compilieren**

| Umgebung/Board    | Link/Befehl                      |
| ----------------- | -------------------------------- |
| Online Compiler           | [mbed-os-example-ble-Beacon](https://os.mbed.com/teams/ST/code/mbed-os-example-ble-Beacon/)  |
| CLI (IoTKit K64F) | `mbed compile -m K64F --source . --source ../IoTKitV3/bluetooth/Beacon; ` <br> `cp BUILD/K64F/GCC_ARM/template.bin $DAPLINK` |
| CLI (DISCO_L475VG_IOT01A) | `mbed compile -m DISCO_L475VG_IOT01A -f --source . --source ../IoTKitV3/bluetooth/Beacon` |

### Links

* Weitere Beispiele (rechts unten) auf [Board Overview Site](https://os.mbed.com/platforms/ST-Discovery-L475E-IOT01A/). Müssen, für das IoTKit K64F Board wie oben Beschrieben, angepasst werden.



Wearables
---------

Wearables (Tragbare Computer), z.B. Armbanduhren, die ständig den Puls messen, Brillen, deren Innenseiten als Bildschirm dienen oder Kleidungsstücke, in die elektronische Hilfsmittel zur Kommunikation und Musikwiedergabe eingearbeitet sind.

Diese Wearables verwenden sehr oft das Bluetooth Protokoll. Auf dem IoTKit V3 befindet sich ein Bluetooth Modem, um ein Wearable zu simulieren.

### Beispiel Herzfrequenzmesser

![](../images/BLEHeartRate.png)

nRF Connect App Printscreen

- - -

**Material:**
* mbed Bluetooth kompatibles Board wie
    * [IoTKit V3](git@github.com:mc-b/IoTKitV3.git)
    * [micro:bit](https://os.mbed.com/platforms/Microbit/)
    * [Seeed Arch BLE](https://os.mbed.com/platforms/Seeed-Arch-BLE/)
* Smartphone mit nRF Connect App

**Installation**
* mbed Programm [BLE_HeartRate ](https://os.mbed.com/teams/ST/code/mbed-os-example-ble-HeartRate/) auf IoTKit V3 laden und Board (rechts open) auf FRDM-K64F umstellen.
* nRF Connect App auf Smartphone starten und nRF Connect App starten.
* Nach neuen Geräten scannen.
* `HRM...` Gerät Verbinden und Herzfrequenz auslesen. 

#### Code Anpassungen für IoTKit V3

Um dieses Verwenden zu können, müssen im Ordner `shields/TARGET_ST_BLUENRG/` in der Datei `mbed_lib.json` die Pin's wie folgt ergänzt werden:

        "K64F": {
            "target.macros_add": ["BLUENRG_PIN_SPI_MOSI=PTA16",
                                  "BLUENRG_PIN_SPI_MISO=PTC7",
                                  "BLUENRG_PIN_SPI_nCS=PTA14",
                                  "BLUENRG_PIN_SPI_RESET=PTA12",
                                  "BLUENRG_PIN_SPI_IRQ=PTA13",
                                  "BLUENRG_PIN_SPI_SCK=PTC5"]            
        },

Die Pins entsprechen dem SPI0 auf dem IoTKit V3.

### Links

* Weitere Beispiele (rechts unten) auf [Board Overview Site](https://os.mbed.com/platforms/ST-Discovery-L475E-IOT01A/). Müssen, wie oben Beschrieben, angepasst werden.
* [mbed Bluetooth Team](https://os.mbed.com/teams/Bluetooth-Low-Energy/)
* [Bluetooth Home Page](https://www.bluetooth.com/)

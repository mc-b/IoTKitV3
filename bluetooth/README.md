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
* mbed Programm [BLE_HeartRate ](https://os.mbed.com/teams/IoTKitV3/code/BLE_HeartRate/) auf IoTKit V3 laden.
* nRF Connect App auf Smartphone starten und nRF Connect App starten.
* Nach neuen Geräten scannen.
* `HRM1` Gerät Verbinden und Herzfrequenz auslesen. 

#### Code Anpassungen für IoTKit V3


Um dieses Verwenden zu können, müssen im Ordner `shields/TARGET_ST_BLUENRG/x-nucleo-idb0xa1` in der Datei `x_nucleo_idb0xa1_targets.h` die Pin's wie folgt angepasst werden:

	/* Use Arduino I2C Connectors */
	#define IDB0XA1_PIN_SPI_MOSI   (PTA16)
	#define IDB0XA1_PIN_SPI_MISO   (PTC7)
	#define IDB0XA1_PIN_SPI_nCS    (PTA14)
	#define IDB0XA1_PIN_SPI_RESET  (PTA12)
	#define IDB0XA1_PIN_SPI_IRQ    (PTA13)
	 
	/* NOTE: Define macro 'IDB0XA1_D13_PATCH' if you want to compile for a specifically
	         modified version of the X_NUCLEO_IDB0XA1 expansion board in
	         which pin 'D13' (rather than the standard pin 'D3') is used 
	         in order to provide the SPI serial clock.
	     Expansion boards modified in this way allow to be used on almost
	     any Arduino-compliant base board.
	*/
	#if defined(IDB0XA1_D13_PATCH)
	#define IDB0XA1_PIN_SPI_SCK    (PTC5)
	#else // !defined(IDB0XA1_D13_PATCH)
	#define IDB0XA1_PIN_SPI_SCK    (PTC5)
	#endif // !defined(IDB0XA1_D13_PATCH)

Die Pins entsprechen dem SPI0 auf dem IoTKit V3.

### Links

* [mbed Bluetooth Team](https://os.mbed.com/teams/Bluetooth-Low-Energy/)
* [Bluetooth Home Page](https://www.bluetooth.com/)

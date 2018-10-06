## IoTKit V3

Der Internet der Dinge Kit V3 besteht aus den nachfolgenden Komponenten.

## Internet der Dinge Board 

![](../images/IoTKit.png)

Internet der Dinge Board

- - -

Der IoTKit ist ein [NXP FRDM-K64F Board](https://os.mbed.com/platforms/FRDM-K64F/) kompatibles Board.
 
Entstanden ist das Board durch die Kombination des [NXP FRDM-K64F Board](https://os.mbed.com/platforms/FRDM-K64F/) und einzelner Shields (z.B. Erweiterungsshield, Motorshield etc.). Dadurch sind Pin&#039;s doppelt belegt. Überall wo dies der Fall ist, kann immer nur eine Funktion gleichzeitig genutzt werden. Beispiel ist ein Gleichstrom Motor, am 2\. Anschluss angeschlossen, kann nicht gleichzeitig die MOSFET Verstärkerschaltung genutzt werden, weil sich diese die Pin&#039;s D5 - D7 teilen

* [Schaltplan](IoTKitV3.pdf) 

#### Board features

* [Bluetooth® V4.1 module (SPBTLE-RF)](../wearables/)
* [Proximity sensor, gesture and ambient light sensing (ALS) module (VL6180X)](../i2c/)
* [low power, high sensitivity, RED, GREEN and BLUE color light sensor (RGB)](../i2c/)
* [Hall Sensor](../sensors/HallSensor/)
* [NFC/RFID Reader](../rfid/)
* [Capacitive digital sensor for relative humidity and temperature (HTS221)](../i2c/)
* [High-performance 3-axis magnetometer (LIS3MDL)](../i2c/)
* [3D accelerometer and 3D gyroscope (LSM6DSL)](../i2c/)
* [Wi-Fi® module ESP8266](../wlan)


* OpenSDA USB Debug and Programming adapter
* Reset Button
* [SPI Header](../spi/)
* [GND/5V/Signal Arduino Pins D13 - D2](../gpio/)
* [I2C Header](../i2c/)
* [MOSFet](../actors)
* Expansion connectors: Arduino™ Uno V3
* [SWDAP](https://os.mbed.com/teams/mbed/wiki/SWDAP)
* [ARM Cortex M4 K64F MCU](https://www.nxp.com/products/processors-and-microcontrollers/arm-based-processors-and-mcus/kinetis-cortex-m-mcus/k-seriesperformancem4/k6x-ethernet/kinetis-k64-120-mhz-256kb-sram-microcontrollers-mcus-based-on-arm-cortex-m4-core:K64_120)
* [Grove Header](http://wiki.seeedstudio.com/Grove_System/)
* [OLED Display](../i2c/OLEDDisplayTest/)


* [H-Bridge](../actors/)
* [Buzzer](../gpio/PwmOutPeriod/)
* [Stepper Driver](../actors/)


* 12 Volt Power Supply
* Charger 5V from batt.
* [GND/5V/Signal Arduino Pins A0 - A5](../gpio/)
* [UART Header](../uart/)

* [Encoder Switch](../gpio)

## Zubehör

*   **Sensoren** RFID Reader (MFRC-522), PIR Sensor (SR501), Ultrasonic Wave Detector Ranging Module (HC-SR04), Digital Temperature and Humidity Sensor (DHT11), Microswitch Limit Switch: [AliExpress](http://www.aliexpress.com/), [EBay](http://www.ebay.ch/), [Conrad](http://www.conrad.ch/) (teilweise)
*   **Aktoren** 5V Stepper Motor (28BYJ-48), DC Motor, Wheels, 9g Mini Micro Servo (SG90): [AliExpress](http://www.aliexpress.com/), [EBay](http://www.ebay.ch/), [Conrad](http://www.conrad.ch/) (teilweise)
*   **LED Strip&#039;s, Matrix** Led Pixel Strip (WS2801 - Variante mit 4 Adern beachten!), Dot LED Matrix: [AliExpress](http://www.aliexpress.com/), [EBay](http://www.ebay.ch/)
*   **Modems** USB To RS232 TTL Konverterkabel: [AliExpress](http://www.aliexpress.com/), [EBay](http://www.ebay.ch/)
*   **IC&#039;s, Transistoren, Widerstände, Kabel, Stecker (Crimp) etc.** [http://www.distrelec.ch/](http://www.distrelec.ch/), [https://www.reichelt.de/](https://www.reichelt.de/), [Pusterla (Ladengeschäft in Zürich)](http://www.pusterla.ch/)

Die restlichen Teile zum Drucken, mittels 3D Drucker, sind auf [http://www.thingiverse.com/](http://www.thingiverse.com/thing:805047) zu finden. Dort befindet sich auch die Dateien um die IoTKit Box, mittels einer CNC Maschine, zu fräsen. Zum Befestigen der Teile werden 2 x M3x20 Linsenschrauben mit Muttern (Schrittmotor ), 1 x M3x30 Linsenschraube mit Mutter (Motorklammer) und zwei Drahtstife (Nägel) mit Durchmesser 1.5mm o.ä. für den Endschalter benötigt.
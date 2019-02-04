GPIO
----

Allzweckeingabe/-ausgabe (engl. GPIO - General Purpose Input/Output) ist ein allgemeiner Kontaktstift (Pin) an einem Mikrocontroller, dessen Verhalten, unabhängig, ob als Eingabe- oder Ausgabekontakt, durch logische Programmierung frei bestimmbar ist. GPIO-Kontakten ist kein Zweck vorgegeben, sie sind daher standardmäßig unbelegt.

Mittels folgender Grundklassen kann den GPIO Pins ein Zweck vorgegeben werden:

* [DigitalOut](DigitalOut/) -  Pin zwischen 0 (0 Volt) und 1 (3.3 Volt) hin und her schalten.
* [DigitalIn](DigitalIn/)  - liefert je nach Spannung: 0 Volt eine 0 oder 3.3 - 5 Volt eine 1.
* [AnalogIn](AnalogIn/)    - Umsetzung eines Analogssignals in einen Wert.
* [PwmOut](PwmOut/) und [PwmOutPeriod](PwmOutPeriod/) - Pulsweitenmodulation für die Erzeugung einer elektrische Spannung zwischen Ground (0 Volt) und 3.3 Volt.
* [Encoder Switch](EncoderSwitch/) - zählt die Impulse am Encoder und schaltet einen Zähler vor und zurück.

Standard Pins sind mit **D0 - D15**, **A0 - A5** (analog Arduino) oder **PTxx** gekennzeichnet. **RX/TX**, **SDA,SCL** und **SS, MOSI, MISO, SLCK** sind Pins für Bussysteme. 
Daneben sind  Pin mit Ground (**GND**) und +5 Volt (**+5V**) vorhanden um die Verkabelung von externen Sensoren und Aktoren zu vereinfachen.
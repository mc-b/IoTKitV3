## 12V RGB LED Strip (Aktor) 

![](../../images/actors/LEDStripsTreppe.png)

[Beispiel Treppenbeleuchtung](http://developer.mbed.org/users/4180_1/notebook/relays1/)

- - - 

 ![](../../images/actors/LedStrips12V.png) |

[RGB LED Strip, siehe Wiki LadyAda](http://www.ladyada.net/wiki/products/ledstrip/index.html) 

- - -

LED Strips (RGB LED Streifen) eröffnen neue Möglichkeiten für die Dekorative Beleuchtungen von Gegenständen und Räumen.

LED Strips werden in Laufmetern mit einer definierten Anzahl von RGB LED&#039;s pro Meter verkauft.

Es gibt unterschiedliche Arten der Ansteuerung, alle LED einer Farbe, jedes RGB LED einzeln.

Im aktuellen Beispiel verwenden wird ein 5V LED Strip mit einem Anschluss pro Farbe. Diese brauchen einen Verstärker, z.B. [MOSFET](http://de.wikipedia.org/wiki/Metall-Oxid-Halbleiter-Feldeffekttransistor).

Die LED Strip wird an den FET D5-D7) Header (+ ist oben) angeschlossen und benötigen für jede Farbe ein DigitalOut (An/Aus) oder PwmOut (Dimming).

### Anwendungen 

*   Raumbeleuchtung
*   Dekorative Ausleuchtung von Gegenständen

### Links

*  [Arm Mbed Online Compiler](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/RGBLEDStrip/)

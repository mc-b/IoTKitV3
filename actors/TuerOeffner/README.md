## Türöffner (Aktor) 

![](../../images/actors/DoorOpener.png)

[Elektromagnetischer Türöffner](http://de.wikipedia.org/wiki/T%C3%BCrschloss)

- - -

![](../../images/actors/DoorOpenerWiring.png)

[Leistungsstufe (MOSFET o.ä.)](http://developer.mbed.org/users/4180_1/notebook/relays1/)

- - -

Türöffner gibt es auch als elektrisches Bauteil. Der Riegel wird durch einen elektromagnetischen Magnet geöffnet.

Ein Türöffner braucht eine höhere Spannung (12 Volt) als das Board zur Verfügung stellen kann. Deshalb ist eine Leistungsstufe, z.B. [MOSFET](http://de.wikipedia.org/wiki/Metall-Oxid-Halbleiter-Feldeffekttransistor), vorzuschalten.

Der Türöffner wird an den FET(D5-D7) Header (oben) angeschlossen und mittels DigitalOut angesprochen.

### Anwendungen 

*   Elektrische Türöffner
*   Schliesssysstem, z.B. in Verbindung mit [RFID Reader](http://de.wikipedia.org/wiki/RFID)

### Links

*  [mbed OS V2 Variante](https://developer.mbed.org/compiler/#import:/teams/smdiotkit1ch/code/TuerOeffner/)

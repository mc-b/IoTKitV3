Industrie V4
------------


Das Ziel von [Industrie 4.0](http://de.wikipedia.org/wiki/Industrie_4.0) ist die „intelligente Fabrik“ (Smart Factory), welche sich durch Wandlungsfähigkeit, Ressourceneffizienz, ergonomische Gestaltung sowie die Integration von Kunden und Geschäftspartnern in Geschäfts- und Wertschöpfungsprozesse auszeichnet. Technologische Grundlage sind cyber-physische Systeme (Verbund informatischer, softwaretechnischer Komponenten mit mechanischen und elektronischen Teilen) und das „Internet der Dinge“. [Umsetzungsstrategie Industrie 4.0 (Deutschland)](http://www.plattform-i40.de/I40/Navigation/DE/Plattform/Ergebnisse/ergebnisse.html)

### Beispiele

* [Siehe CoAP](../coap/)
* [Eclipse Kura](http://www.eclipse.org/kura/)

### mbed CoAP Beispiel (mbed OS 5)

* [mbed Account erstellen](https://os.mbed.com/).
* [mbed Compiler](https://os.mbed.com/compiler/) aufrufen.
* Mittels rechter Maustaste `Import Program` -> `Import URL` und URL [https://github.com/ARMmbed/mbed-os-example-client/](https://github.com/ARMmbed/mbed-os-example-client/) das mbed os client Beispiel importieren.
* `mbed_app.json` wie in [Wifi](../uart/wifi/README.md) Anpassen.
* [mbed Connector](https://connector.mbed.com/) und `Security Credentials` Datei erstellen. 
* In [mbed Compiler](https://os.mbed.com/compiler/): Inhalt von `security.h` mit Erstellen Inhalt ersetzen.
* In [mbed Connector](https://connector.mbed.com/): `Connected Devices` überprüfen, es muss 1 Gerät sichtbar sein.
* In der `API Console` Werte mittels UI abfragen.  

Ein Alternatives Beispiel ist [CoAP Example on os.mbed.com](https://os.mbed.com/teams/sandbox/code/coap-example/). Das Vorgehen ist das Gleiche bis auf den Import.

### Links

* [Vortrag Industrie V4.0 und Open Source](http://www.hightechzentrum.ch/images/seiteninhalte/veranstaltungen/2016/normen_standards/Hightech_Zentrum_Aargau_Normen_Standards_CHopen_Bernet.pdf)
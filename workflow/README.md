Workflow
--------

![](../images/NodeRED.png)

- - -

Mittels [Node-RED](https://nodered.org/) lassen sich einfache Workflows realisieren und die HTTP und MQTT Protokolle testen.

### Node-RED HTTP Workflow

![](../images/NodeREDHTTP.png)

- - -

* [Node-RED](https://nodered.org/) installieren.
* In Node-RED
    * `http` Input Node auf Flow 1 platzieren, mit als Methode `POST` und als URL `post` eintragen.
    * `debug` Output Node auf Flow 1 platzieren, Output auf "complete msg.object" ändern und mit Input Node verbinden.
    * Programm mittels `Deploy` veröffentlichen.
* mbed Teil
    * [HTTP ThingSpeak](../cloud/ThinkSpeak/) Beispiel (main.cpp) editieren, ca. auf Zeile 16 die URL mit dem Server ersetzen wo Node-RED läuft, z.B. `http://192.168.178.200:1880/post` und ca. auf Zeile 58 HTTP Methode auf HTTP_POST setzen.
    * Programm Compilieren und auf Board laden.

Im Node-RED Fenster auf der Node `debug`, sollten jetzt alle 10 Sekunden neue Meldungen vom IoTKitV3 erscheinen.   

### Node-RED MQTT Workflow

![](../images/NodeREDMQTT.png)

- - -

* [Mosquitto](https://mosquitto.org/) installieren.
* [Node-RED](https://nodered.org/) installieren.
* In Node-RED
    * `mqtt` Input Node auf Flow 1 platzieren, mit Mosquitto Server verbinden und als Topic `iotkit` eintragen.
    * `debug` Output Node auf Flow 1 platzieren und mit Input Node verbinden.
    * Programm mittels `Deploy` veröffentlichen.
* mbed Teil
    * [MQTTPublish](../mqtt/MQTTPublish) Beispiel in mbed Compiler importieren und ca. auf Zeile 21 den `hostname` mit der IP-Adresse auswechseln wo der Mosquitto Server läuft. 
    * Programm Compilieren und auf Board laden.


### Links
 
 * [Home Page](https://nodered.org/)
 * [Node-RED Einführung](https://www.youtube.com/watch?v=f5o4tIz2Zzc)
 
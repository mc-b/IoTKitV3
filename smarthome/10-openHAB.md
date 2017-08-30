## openHAB

![](../images/openHAB.png)

- - -

[openHAB (open Home Automation Bus)](http://www.openhab.org/) ist eine in Java entwickelte Softwarelösung, die Komponenten zur Gebäudeautomatisierung, Hersteller- und Protokollneutral in einer Plattform miteinander verbindet. Dadurch läuft openHAB Betriebssystemunabhängig und ist durch Hinzufügen weiterer Bindings um zusätzliche Technologien/Protokolle erweiterbar.

Entwickelt wird openHAB unter der Eclipse Public License und ist Open Source. Als Userinterfaces werden Webbrowser, Android- oder Apple iOS-Systeme unterstützt.

### Weitere Merkmale 

*   Sitemap - openHAB hat ein generisch konfigurierbares User Interface (UI), die sogenannte Sitemap. Die Sitemap ist eine Baumstruktur von Widgets, die die verschiedenen Seiten und den Inhalt des UI definieren. Widgets können Items sein, die den aktuellen Status darstellen oder auch Schalter oder Grafiken.
*   Persistence - Der Persistence Service ermöglicht das Speichern von Status der einzelnen Items. Somit können Verläufe visualisiert, historische Daten abgefragt oder bei einem Systemneustart der Status wiederhergestellt werden.
*   Regeln - Zum Erstellen von Automatisierungslogiken kommen Regeln zum Einsatz.
*   Bindings - (Java Plug-Ins) um weitere Geräte anzuschliessen.

### Installation 

Am einfachsten ist es den [Docker Container](https://hub.docker.com/r/openhab/openhab/) zu verwenden.

Diesen im Modus für "advanced user" starten:

	docker run \
	  --name openhab \
	  --net=host \
	  -v /etc/localtime:/etc/localtime:ro \
	  -v /etc/timezone:/etc/timezone:ro \
	  -v /opt/openhab/addons:/openhab/addons \
	  -v /opt/openhab/conf:/openhab/conf \
	  -v /opt/openhab/userdata:/openhab/userdata \
	  openhab/openhab:2.1.0-amd64

Anschliessend das IoTKit Bindings holen und in Addons Verzeichnis kopieren.

	cd /opt/openhab/addons
	sudo wget https://github.com/mc-b/IoTKit/releases/download/V1.0/ch.iotkit.smarthome.binding.mbedRPC_1.0.0.201511131556.jar

**ACHTUNG:** Damit die IoTKit Geräte sichtbar werden, muss evtl. der Container gestoppt und frisch gestartet werden.

### User Interface / APP 

*   [RPCHTTPServerSmartHomeV2](../mbedRPC/RPCHTTPServerSmartHomeV2/) auf Board laden
*   Browser - [http://localhost:8080](http://localhost:8080) 
*   Paper UI auswählen, ggf. zuerst Demo Setup wählen.
*   Mittels -> Configuration -> Things -> + -> IoTKit Bindings auswählen
*   Zuerst "IoTKit SMD Shield Ethernet gateway" mit IP des mbed Boards einrichten
*   Anschliessend die IoTKit Sensoren, Aktoren etc.

Das komplettes Beispiel in C++ und Java, welches für die /ch/open Workshoptage 2015 entstanden ist, findet man [hier](https://developer.mbed.org/teams/ch-open-wstage2015/wiki/SmartHome).
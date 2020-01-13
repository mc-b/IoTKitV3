## Edge Computing

Edge Computing bezeichnet im Gegensatz zum Cloud Computing die dezentrale Datenverarbeitung am Rand des Netzwerks, der sogenannten Edge (engl. für Rand oder Kante).

## Raspberry Pi als Edge aufsetzen

Der Raspberry Pi eignet sich als Edge. Zuerst muss dieser allerdings wie folgt aufgesetzt werden:

* Raspbian Lite wie auf [raspberrypi.org](https://www.raspberrypi.org/) beschrieben, downloaden und auf SD Karte speichern.
* Auf dem Neuen Laufwerk eine Datei «ssh» ohne Endung erstellen.
* Auf Windows Git/Bash oder Putty o.ä. installieren.
* Raspberry Pi via Kabel mit dem Router LERNKUBE verbinden und via ssh Verbinden
    
Grundinstallation:
  
    ssh 192.168.2.xx -l pi
    PW: raspberry
    WLAN, Zeitzone etc. in raspi-config Einstellen
    sudo raspi-config

Quelle: https://howtoraspberrypi.com/how-to-raspberry-pi-headless-setup/ 

Anschliessend bietet sich [Docker](https://docker.com) als Container Umgebung an. Diese kann wie folgt installier werden:

    ssh 192.168.2.xx -l pi
    sudo -i
    cd /tmp
    wget -O get-docker.sh http://get.docker.com
    sh get-docker.sh
    sudo usermod -aG docker pi
    exit

Testen der Docker Umgebung:

    ssh 192.168.2.xx -l pi
    docker run hello-world
    
Nach der Installation der benötigten Grundinfrastruktur können wir loslegen und die eigentlich benötigte Software als Container starten.

Wir verwenden wie im [Workflow Beispiel](../workflow) [Node-RED](https://nodered.org/) und bauen das Beispiel dann Stück für Stück aus.

    docker run -d -p 1880:1880 nodered/node-red
    
Die eigentliche Applikation Node-RED ist via Browser <IP-Raspberry Pi:1880> zugreifbar.

### Node-RED

Um die Beispiele z.B. vom Kurs [MODTEC](https://github.com/mc-b/modtec) auszuführen brauchen wir noch ein paar zusätzliche Plugins.

Diese können in Node-RED mittels Pulldownmenu rechts -> `Palette verwalten`, Tab `Installieren` hinzugefügt werden. Es handelt es sich um die Plugins:
* node-red-contrib-kafka-node-latest - mindestens Version 0.2
* node-red-contrib-kafka-manager - letzte Version

Dadurch erhalten wird neu `Nodes` für die Integration mit [Apache Kafka](https://kafka.apache.org/).    

Topics auslesen, lesen und schreiben auf Topics in Kafka Container, siehe [Projekt duk](https://github.com/mc-b/duk/tree/master/kafka)




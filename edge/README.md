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

Wir verwenden wie im [Workflow Beispiel](../workflow) [Node-RED](https://nodered.org/), Mosquitto und bauen das Beispiel dann Stück für Stück aus.

    docker run -d -p 1880:1880 nodered/node-red
    docker run -d -p 1883:1883 eclipse-mosquitto
    
Die eigentliche Applikation Node-RED ist via Browser <IP-Raspberry Pi:1880> zugreifbar.

## Cloud Umgebung (Edge - REST)

Für das *Internet of Everything* brauchen wir noch eine Geschäftsprozess (BPMN) Workflow Umgebung und ein entsprechender Prozess:

    kubectl apply -f https://raw.githubusercontent.com/mc-b/misegr/master/bpmn/camunda.yaml
    wget https://raw.githubusercontent.com/mc-b/misegr/master/bpmn/RechnungStep3.bpmn -O RechnungStep3.bpmn
    
warten bis die Workflow Umgebung gestartet ist und veröffentlichen des Rechnungsprozesses:

    curl -k -w "\n" \
    -H "Accept: application/json" \
    -F "deployment-name=rechnung" \
    -F "enable-duplicate-filtering=true" \
    -F "deploy-changed-only=true" \
    -F "Rechnung.bpmn=@RechnungStep3.bpmn" \
    https://localhost:30443/engine-rest/deployment/create    
        
Details zu BPMN und des Prozesses [siehe](https://github.com/mc-b/misegr/tree/master/bpmn).

### Node-RED (Edge - REST)

![](../images/NodeREDMQTT.png)

- - -

* [Mosquitto](https://mosquitto.org/) installieren.
* [Node-RED](https://nodered.org/) installieren.
* In Node-RED
    * `mqtt` Input Node auf Flow 1 platzieren, mit Mosquitto Server verbinden und als Topic `iotkit` eintragen.
    * `debug` Output Node auf Flow 1 platzieren und mit Input Node verbinden.
    * Programm mittels `Deploy` veröffentlichen.
* mbed Teil
    * [MQTTPublish](../mqtt#mqtt-publish-beispiel) Beispiel in mbed Compiler importieren und ca. auf Zeile 21 den `hostname` mit der IP-Adresse auswechseln wo der Mosquitto Server läuft. 
    * Programm Compilieren und auf Board laden.
    
Ändert den Workflow so, dass statt der Ausgabe in Node-RED jetzt ein Prozess in der Camunda BPM Workflow Engine gestartet wird.

Der URL wie ein Prozess gestartet werden kann steht im [Frontend](https://github.com/mc-b/misegr/tree/master/bpmn) Beispiel bei `$.post`.

## Cloud Umgebung (Edge, MQTT - Cloud - Messaging) 

In der [MODTEC](https://github.com/mc-b/modtec) Umgebung starten wie die benötigten Services:

    # IoT Umgebung 
    kubectl apply -f https://raw.githubusercontent.com/mc-b/duk/master/iot/mosquitto.yaml
    kubectl apply -f https://raw.githubusercontent.com/mc-b/duk/master/iot/nodered.yaml

    # Messaging Umgebung 
    kubectl apply -f https://raw.githubusercontent.com/mc-b/duk/master/kafka/zookeeper.yaml
    kubectl apply -f https://raw.githubusercontent.com/mc-b/duk/master/kafka/kafka.yaml

    # Kafka Streams 
    kubectl apply -f https://raw.githubusercontent.com/mc-b/iot.kafka/master/iot-kafka-alert.yaml
    kubectl apply -f https://raw.githubusercontent.com/mc-b/iot.kafka/master/iot-kafka-consumer.yaml
    kubectl apply -f https://raw.githubusercontent.com/mc-b/iot.kafka/master/iot-kafka-pipe.yaml


### Node-RED (Edge, MQTT - Cloud, Messaging)

Um die Beispiele z.B. vom Kurs [MODTEC](https://github.com/mc-b/modtec) auszuführen brauchen wir noch ein paar zusätzliche Plugins.

Diese können in Node-RED mittels Pulldownmenu rechts -> `Palette verwalten`, Tab `Installieren` hinzugefügt werden. Es handelt es sich um die Plugins:
* node-red-contrib-kafka-node-latest - mindestens Version 0.2
* node-red-contrib-kafka-manager - letzte Version

Dadurch erhalten wird neu `Nodes` für die Integration mit [Apache Kafka](https://kafka.apache.org/).    

Topics auslesen, lesen und schreiben auf Topics in Kafka Container, siehe [Projekt duk](https://github.com/mc-b/duk/tree/master/kafka).

* mbed Teil
    * [MQTTPublish](../mqtt#mqtt-publish-beispiel) Beispiel in mbed Compiler importieren und ca. auf Zeile 21 den `hostname` mit der IP-Adresse auswechseln wo der Mosquitto Server läuft. 
    * Programm Compilieren und auf Board laden.

* In Node-RED (1. Teil - MQTT)
    * `mqtt` Input Node auf Flow 1 platzieren, mit Mosquitto Server verbinden und als Topic `iotkit` eintragen.
    * `debug` Output Node auf Flow 1 platzieren und mit Input Node verbinden.
    * Programm mittels `Deploy` veröffentlichen.
    
* In Node-RED (2. Teil - MQTT -> Kafka)
    * Kafka Producer auf Flow 1 platzieren mit Kafka Server (kafka:9092) verbinden
    * `mqtt` Input Node mit Kafka Producer verbinden, evtl. braucht es zusätzliche Plugins um die MQTT Topics `iotkit/#` nach `broker_message` für Kafka zu wandeln.
    * Das Ergebnis kann mittels `logs iot-kafka-consumer` angeschaut werden. Dort sollten die MQTT Messages umgewandelt als Kafka Messages erscheinen.
    


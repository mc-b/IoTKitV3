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

Für das *Internet of Everything* brauchen wir noch eine Geschäftsprozess (BPMN) Workflow Umgebung und einen entsprechenden Prozess.

**Variante a) Manuelle Installation**

Installieren von 
* [Camunda BPMN Workflow Engine](https://camunda.com/)
* [Camunda Modeler](https://camunda.com/)
* Download des Rechnungsprozesses vom Projekt [misegr](https://raw.githubusercontent.com/mc-b/misegr/master/bpmn/RechnungStep3.bpmn)
* Import des Rechnungsprozesses [RechnungStep3.bpmn](https://raw.githubusercontent.com/mc-b/misegr/master/bpmn/RechnungStep3.bpmn) in den Modeler
* Export des Rechnungsprozesse vom Modeler in die BPMN Workflow Engine.

**Variante b) in einer Kubernetes Umgebung**

Starten der [Camunda BPMN Workflow Engine](https://camunda.com/). Download Rechnungsprozesses [RechnungStep3.bpmn](https://raw.githubusercontent.com/mc-b/misegr/master/bpmn/RechnungStep3.bpmn). 

    kubectl apply -f https://raw.githubusercontent.com/mc-b/misegr/master/bpmn/camunda.yaml
    wget https://raw.githubusercontent.com/mc-b/misegr/master/bpmn/RechnungStep3.bpmn -O RechnungStep3.bpmn
    
warten bis die Workflow Umgebung gestartet ist und veröffentlichen des Rechnungsprozesses, mittels REST Schnittstelle:

    curl -k -w "\n" \
    -H "Accept: application/json" \
    -F "deployment-name=rechnung" \
    -F "enable-duplicate-filtering=true" \
    -F "deploy-changed-only=true" \
    -F "Rechnung.bpmn=@RechnungStep3.bpmn" \
    https://localhost:30443/engine-rest/deployment/create    
        
Details zu BPMN und des Prozesses [siehe](https://github.com/mc-b/misegr/tree/master/bpmn).

### Node-RED (Edge - REST)

![](../images/NodeREDREST.png)

- - -

Die MQTT Messages vom IoTKit Board sollen vom MQTT Protokoll in das HTTP/REST Protokoll umgewandelt werden.

Um dies zu Demonstrieren erstellen wir eine Input MQTT Node welche das Topic `iotkit/alert` empfängt, eine Node welche eine JSON Struktur erzeugt und eine Node welche die JSON Daten via HTTP/REST an die BPMN Workflow Umgebung weiterleitet.

* [Mosquitto](https://mosquitto.org/) installieren.
* [Node-RED](https://nodered.org/) installieren.
* In Node-RED
    * `mqtt` Input Node auf Flow 1 platzieren, mit Mosquitto Server verbinden und als Topic `iotkit/alert` eintragen.
    * `debug` Output Node auf Flow 1 platzieren und mit Input Node verbinden - damit können wir die MQTT Messages kontrollieren
    * `change` Node auf Flow 1 platzieren und als `msg.payload` folgenden JSON String `{"variables":{"rnr":{"value":"123","type":"long"},"rbetrag":{"value":"200.00","type":"String"}}}` eintragen.
    * `http request` Node auf Flow 1 platzieren, als Methode `POST` und als URL `http://camunda:8080/engine-rest/process-definition/key/RechnungStep3/start` eintragen
    * Zur Kontrolle ebenfalls eine `debug` noch hinten platzieren.
    * Alle Nodes wie oben in der Grafik verbinden und veröffentlichen (deploy).
* mbed Teil
    * [MQTTPublish](../mqtt#mqtt-publish-beispiel) Beispiel in mbed Compiler importieren und ca. auf Zeile 21 den `hostname` mit der IP-Adresse auswechseln wo der Mosquitto Server läuft. 
    * Programm Compilieren und auf Board laden.
    * Magnet an Hall Sensor halten.
* In Camunda BPMN Workflow Engine [https://localhost:30443/camunda](https://localhost:30443/camunda) (URL kann abweichen, je nach Umgebung) einloggen mittels User/Password `demo/demo`. Bei jedem Alarm welcher vom Board (Hall Sensor) mittels Magneten ausgelöst wird, sollte ein neuer Rechnungsprozess gestartet werden.
    
Details zum BPMN Prozess und der URL wie ein Prozess gestartet werden kann steht im [Frontend](https://github.com/mc-b/misegr/tree/master/bpmn) Beispiel bei `$.post`.

Der Flow zum importieren und anpassen, siehe [Node-RED-REST.json](Node-RED-REST.json).

## Cloud Umgebung (Edge, MQTT - Cloud - Messaging) 

In Kubernetes starten wie die benötigten Services:

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


![](../images/NodeREDKafka.png)

- - -

Die MQTT Message sollen nun an [Apache Kafka](https://kafka.apache.org/) weitergeleitet werden. Das hat den Vorteil, dass wir diese
* in andere Formate, z.B. von Binär nach JSON, umwandeln können
* sie Persistieren können
* ein Eventlog erhalten
* etc.

Um [Apache Kafka](https://kafka.apache.org/) anzusprechen brauchen wir ein paar zusätzliche Plugins.

Diese können in Node-RED mittels Pulldownmenu rechts -> `Palette verwalten`, Tab `Installieren` hinzugefügt werden. Es handelt es sich um die Plugins:
* node-red-contrib-kafka-node-latest - mindestens Version 0.2
* node-red-contrib-kafka-manager - letzte Version

Dadurch erhalten wird neu `Nodes` für die Integration mit [Apache Kafka](https://kafka.apache.org/).    

* In Node-RED
    * `mqtt` Input Node auf Flow 1 platzieren, mit Mosquitto Server verbinden, als Topic `iotkit/#` und bei Output `a String` eintragen.
    * `debug` Output Node auf Flow 1 platzieren und mit Input Node verbinden - damit können wir die MQTT Messages kontrollieren
    * `change` Node auf Flow 1 platzieren und als Regel `Ändern` Wert `msg.topic` von `iotkit/alert` in `broker_message`, weitere Regel hinzufügen und gleich verfahren für `iotkit/sensor` nach `broker_message`.
    * Kafka Producer auf Flow 1 platzieren und mit Kafka Server (kafka:9092) verbinden
    * Alle Nodes wie oben in der Grafik verbinden und veröffentlichen (deploy).

* mbed Teil
    * [MQTTPublish](../mqtt#mqtt-publish-beispiel) Beispiel in mbed Compiler importieren und ca. auf Zeile 21 den `hostname` mit der IP-Adresse auswechseln wo der Mosquitto Server läuft. 
    * Programm Compilieren und auf Board laden.
* Kubernetes    
    * Das Ergebnis kann mittels `logs iot-kafka-consumer`, logs iot-kafka-pipe` angeschaut werden. Dort sollten die MQTT Messages umgewandelt als Kafka Messages erscheinen.
* In Camunda BPMN Workflow Engine [https://localhost:30443/camunda](https://localhost:30443/camunda) (URL kann abweichen, je nach Umgebung) einloggen mittels User/Password `demo/demo`. Bei jedem Alarm welcher vom Board (Hall Sensor) mittels Magneten ausgelöst wird, sollte ein neuer Rechnungsprozess gestartet werden.
    

Topics auslesen, lesen und schreiben auf Topics in Kafka Container, siehe [Projekt duk](https://github.com/mc-b/duk/tree/master/kafka).

Der Flow zum importieren und anpassen, siehe [Node-RED-Kafka.json](Node-RED-Kafka.json).


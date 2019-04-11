## MQTT Publish

Mittels Publish (unten) kann eine Meldung zum MQTT Broker bzw. Topic gesendet werden.

Ein anderes Board oder der Mosquitto Client mosquitto_sub kann dieses Topic Abonnieren (subscribe).

### Client

Beispiele für das Abonieren der MQTT Publish Meldungen via [Mosquitto](https://projects.eclipse.org/projects/technology.mosquitto) Client Utility mosquitto_sub.

Abfragen der Werte von Temperatur und Luftfeuchtigkeit (Ausgabe: I2C Id, Temperatur, Luftfeuchtigkeit, Motorlaufgeschwindigkeit)

	mosquitto_sub -h broker.hivemq.com -t iotkit/sensor/#
	0xBC,22.90,36.9,low
	0xBC,28.00,36.7,middle
	0xBC,32.90,36.7,high

Abfragen ob jemand einen Magneten an den Hall Sensor gehalten hat
	
	mosquitto_sub -h broker.hivemq.com -t iotkit/alert/#

Sollte der Server nicht Antworten ist der MQTT Broker zu wechseln (main.cpp nicht Vergessen). Eine Liste von Öffentlichen MQTT gibt es [hier](https://github.com/mqtt/mqtt.github.io/wiki/public_brokers).

### Links

*  [Arm Mbed Online Compiler](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/MQTTPublish/)

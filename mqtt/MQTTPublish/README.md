## MQTT Publish

Mittels Publish (unten) kann eine Meldung zum MQTT Broker bzw. Topic gesendet werden.

Ein anderes Board oder der Mosquitto Client mosquitto_sub kann dieses Topic Abonnieren (subscribe).

### Client

	mosquitto_sub -h iot.eclipse.org -t mbed/k64f/iotkit/light/#
		0.165866
		0.165393
		0.165057
	
	mosquitto_sub -h iot.eclipse.org -t mbed/k64f/iotkit/poti/#
		0.378256
		0.378180
		0.372290

Abonieren der MQTT Publish Meldungen via [Mosquitto](https://projects.eclipse.org/projects/technology.mosquitto) Client Utility mosquitto_sub.

### Links

*  [Arm Mbed Online Compiler](https://os.mbed.com/compiler/#import:/teams/IoTKitV3/code/MQTTPublish/)

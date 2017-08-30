/** MQTT Publish von Sensordaten */
#include "mbed.h"
#include "MQTTEthernet.h"
#include "MQTTClient.h"

// Topic's
char* topicLight = "mbed/k64f/iotkit/light";
char* topicPoti = "mbed/k64f/iotkit/poti";
// MQTT Brocker
char* hostname = "iot.eclipse.org";
int port = 1883;
// MQTT Message
MQTT::Message message;
// I/O Buffer
char buf[100];
// UI
DigitalOut led1( LED1 );
// Poti
AnalogIn   poti( A0 );
// Lichtsensor
AnalogIn   light( A1 );

/** Hilfsfunktion zum Publizieren auf MQTT Broker */
void publish( MQTTEthernet &ipstack, MQTT::Client<MQTTEthernet, Countdown> &client )
{
    printf("Connecting to %s:%d\n", hostname, port);
    int rc = ipstack.connect(hostname, port);
    if ( rc != 0 )
        printf("rc from TCP connect is %d\n", rc);

    // mit MQTT Broker verbinden
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    data.clientID.cstring = "mbed-sample";
    data.username.cstring = "testuser";
    data.password.cstring = "testpassword";
    if ( (rc = client.connect(data)) != 0 )
        printf("rc from MQTT connect is %d\n", rc);

    // Message als JSON aufbereiten und senden
    sprintf( buf, "%f", light.read() );
    printf( "Publish: %s\n", buf );
    message.qos = MQTT::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void*) buf;
    message.payloadlen = strlen(buf)+1;
    client.publish( topicLight, message);
    
    // Message als JSON aufbereiten und senden
    sprintf( buf, "%f", poti.read() );
    printf( "Publish: %s\n", buf );
    message.qos = MQTT::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void*) buf;
    message.payloadlen = strlen(buf)+1;
    client.publish( topicPoti, message);    
    
    // Verbindung beenden, ansonsten ist nach 4x Schluss
    client.disconnect();
    ipstack.disconnect();
}

/** Hauptprogramm */
int main()
{
    // Ethernet und MQTT initialisieren (muss in main erfolgen)
    MQTTEthernet ipstack = MQTTEthernet();
    MQTT::Client<MQTTEthernet, Countdown> client = MQTT::Client<MQTTEthernet, Countdown>(ipstack);

    while   ( 1 ) 
    {
        led1 = 1;
        publish( ipstack, client );
        led1 = 0;
        wait    ( 2.0 );
    }
}

/** MQTT Subscribe und Publish
    Wartet auf eine Publish Nachricht und sendet
    dann die dazugehoerende Nachricht zurueck */
#include "mbed.h"
#include "MQTTEthernet.h"
#include "MQTTClient.h"
#include "Servo.h"

// UI
DigitalOut led1( LED1 );
// Licht Poti
AnalogIn poti( A0 );
// Licht Sensor
AnalogIn light( A1 );
// Servos
Servo servo1 ( D9 );

// MQTT Brocker
//char* hostname = "iot.eclipse.org";
char* hostname = "raspi2x";
int port = 1883;
// Client als Pointer, wird in main gesetzt.
MQTT::Client<MQTTEthernet, Countdown> *clientGlobal;

// Topic's subscribe
char* topicSensors = "mbed/k64f/iotkit/get/#";
// Topic's publish
char* topicPoti = "mbed/k64f/iotkit/post/poti";
char* topicLight = "mbed/k64f/iotkit/post/light";

// MQTT Message
MQTT::Message message;
// I/O Buffer
char buf[100];

/** Hilfsfunktion zum Publizieren auf MQTT Broker */
void publish( char* topic, float value )
{
    // Message als JSON aufbereiten und senden
    sprintf( buf, "%f", value );
    printf( "Publish: %s/%s\n", topic, buf );
    message.qos = MQTT::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void*) buf;
    message.payloadlen = strlen(buf)+1;
    clientGlobal->publish( topic, message);
}

/** Daten empfangen von MQTT Broker */
void messageArrived( MQTT::MessageData& md )
{
    float value;
    MQTT::Message &message = md.message;
    printf("Message arrived: qos %d, retained %d, dup %d, packetid %d\n", message.qos, message.retained, message.dup, message.id);
    printf("Topic %.*s, ", md.topicName.lenstring.len, (char*) md.topicName.lenstring.data );
    printf("Payload %.*s\n", message.payloadlen, (char*) message.payload);
    
    // Sensoren
    // in C sind Zeiger auf char immer Positionsangaben, deshalb sind Additionen und Subtraktionen moeglich.
    if  ( strncmp( (char*) md.topicName.lenstring.data + md.topicName.lenstring.len - 4, "poti", 4 ) == 0 )
    {
        printf( "Poti %f\n", poti.read() );
        publish( topicPoti, poti.read() );
    }
    if  ( strncmp( (char*) md.topicName.lenstring.data + md.topicName.lenstring.len - 5, "light", 5) == 0 )
    {
        printf( "Light %f\n", light.read() );
        publish( topicLight, light.read() );
    }  
    
    // Aktoren
    if  ( strncmp( (char*) md.topicName.lenstring.data + md.topicName.lenstring.len - 6, "servo1", 6) == 0 )
    {
        sscanf( (char*) message.payload, "%f", &value );
        servo1 = value;
        printf( "Servo1 %f\n", value );
    }               
}

int main()
{   
    // Ethernet und MQTT initialisieren (muss in main erfolgen)
    MQTTEthernet ipstack = MQTTEthernet();
    MQTT::Client<MQTTEthernet, Countdown> client = MQTT::Client<MQTTEthernet, Countdown>(ipstack);
    // HACK um client anderen Funktionen zur Verfuegung zu stellen
    clientGlobal = &client;
    
    printf("Connecting to %s:%d\n", hostname, port);
    int rc = ipstack.connect(hostname, port);
    if (rc != 0)
        printf("rc from TCP connect is %d\n", rc);
 
    // mit MQTT Broker verbinden
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;       
    data.MQTTVersion = 3;
    data.clientID.cstring = "mbed-sample";
    data.username.cstring = "testuser";
    data.password.cstring = "testpassword";
    rc = client.connect(data);
    printf("rc from MQTT connect is %d\n", rc);
    
    rc = client.subscribe( topicSensors, MQTT::QOS0, messageArrived );
    printf("rc from MQTT subscribe is %d\n", rc);

    while   ( 1 )
    {
        led1 = 0;
        client.yield(1000);         // MQTT Client darf empfangen
        led1 = 1;
        wait( 0.2 );
    }
    
    if ((rc = client.unsubscribe(topicSensors)) != 0)
        printf("rc from unsubscribe was %d\n", rc);
    
    if ((rc = client.disconnect()) != 0)
        printf("rc from disconnect was %d\n", rc);
    
    ipstack.disconnect();
    return 0;
}

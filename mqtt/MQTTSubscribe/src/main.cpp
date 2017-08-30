/** MQTT Subscribe */
#include "mbed.h"
#include "MQTTEthernet.h"
#include "MQTTClient.h"

// Topic's
char* topicLight = "mbed/k64f/iotkit/light";
// MQTT Brocker
//char* hostname = "iot.eclipse.org";
char* hostname = "raspi2x";
int port = 1883;
// UI
DigitalOut led1( LED1 );

void messageArrived( MQTT::MessageData& md )
{
    MQTT::Message &message = md.message;
    printf("Message arrived: qos %d, retained %d, dup %d, packetid %d\n", message.qos, message.retained, message.dup, message.id);
    printf("Payload %.*s\n", message.payloadlen, (char*) message.payload);
}

int main()
{   
    // Ethernet und MQTT initialisieren (muss in main erfolgen)
    MQTTEthernet ipstack = MQTTEthernet();
    MQTT::Client<MQTTEthernet, Countdown> client = MQTT::Client<MQTTEthernet, Countdown>(ipstack);
    
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
    
    rc = client.subscribe( topicLight, MQTT::QOS0, messageArrived );
    printf("rc from MQTT subscribe is %d\n", rc);

    while   ( 1 )
    {
        led1 = 0;
        client.yield(1000);         // MQTT Client darf empfangen
        led1 = 1;
        wait( 0.2 );
    }
    
    if ((rc = client.unsubscribe(topicLight)) != 0)
        printf("rc from unsubscribe was %d\n", rc);
    
    if ((rc = client.disconnect()) != 0)
        printf("rc from disconnect was %d\n", rc);
    
    ipstack.disconnect();
    return 0;
}

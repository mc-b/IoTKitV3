/** Kitchen Helper Project - MQTT Version
*/
#include "mbed.h"
#include "rtos.h"
#include "OLEDDisplay.h"
#include "MQTTEthernet.h"
#include "MQTTClient.h"
#include "RemoteCooker.h"

// Topic's
char* topicTimer = "cooker/timer";
char* topicMenu = "cooker/menu";
char* topicKeepwarm = "cooker/keepwarm";

// MQTT Brocker
char* hostname = "iotkit.mc-b.ch";
//char* hostname = "iot.eclipse.org";
int port = 1883;
DigitalOut led1( LED2 );

// Kocher
#include "Cooker.h"
#include "RemoteCooker.h"

// Kochfeld Remote Zugriff 
RemoteCooker cooker = RemoteCooker( D11, D12, D13, D10 );

// OLED Display
OLEDDisplay oled;

// HTTP GET (REST, IFTTT)
#include "HTTPClient.h"

// HTTP Hilfsklassen
HTTPClient http;
// I/O Buffer
char message[256];
char payload[16];

char *finishMsg = "https://maker.ifttt.com/trigger/cooker_finish/with/key/mY3_IZhJSfm-tj3UVytotaqtD1L5AIEUMcal8nDy4dJ";

/** Aufruf vom Kochfeld - kochen beendet - hier darf kein printf oder http.get stehen, weil Aufruf von Timer */
void finishCooker()
{
    http.get( finishMsg, message, sizeof(message) );
    oled.printf( "==> ready \r\n" );
}

/** MQTT Callbacks */
// Timer
void messageTimerArrived( MQTT::MessageData& md )
{
    MQTT::Message &message = md.message;
    printf("Message Timer arrived: qos %d, retained %d, dup %d, packetid %d\r\n", message.qos, message.retained, message.dup, message.id);
    printf("Payload %.*s\n", message.payloadlen, (char*) message.payload);
    
    strncpy( payload, (char*) message.payload, message.payloadlen );
    payload[ message.payloadlen ] = '\0';
    
    oled.clear();
    oled.cursor( 0, 0 );
    oled.printf( "timer %s\r\n", payload );
    oled.printf( "==> ready \r\n" );    
    
    cooker.timer( atoi( payload ) );
}

// Menu
void messageMenuArrived( MQTT::MessageData& md )
{
    MQTT::Message &message = md.message;
    printf("Message Menu arrived: qos %d, retained %d, dup %d, packetid %d\r\n", message.qos, message.retained, message.dup, message.id);
    printf("Payload %.*s\n", message.payloadlen, (char*) message.payload);
    
    strncpy( payload, (char*) message.payload, message.payloadlen );
    payload[ message.payloadlen ] = '\0';
    
    oled.clear();
    oled.cursor( 0, 0 );
    oled.printf( "cook menu %s\r\n", payload );
        
    cooker.menu( atoi( payload ) );
}

// Keepwarm
void messageKeepwarmArrived( MQTT::MessageData& md )
{
    MQTT::Message &message = md.message;
    printf("Message Keepwarm arrived: qos %d, retained %d, dup %d, packetid %d\r\n", message.qos, message.retained, message.dup, message.id);
    printf("Payload %.*s\n", message.payloadlen, (char*) message.payload);
    
    strncpy( payload, (char*) message.payload, message.payloadlen );
    payload[ message.payloadlen ] = '\0';
    
    oled.clear();
    oled.cursor( 0, 0 );
    oled.printf( "keepwarm %s\r\n", payload );
    oled.printf( "==> ready \r\n" );    
        
    cooker.keepwarm( atoi( payload ) );
}

/** Hauptprogramm */
int main()
{
    int rc;
    
    // OLED Display
    oled.clear();
    oled.setRotation( 2 );    
    oled.printf( "MQTT KitchenHelper\r\n" );
    
    printf( "\n\n\n\n\nMQTT Kitchen Helper Project\n" );
    // Ethernet und MQTT initialisieren (muss in main erfolgen)
    MQTTEthernet ipstack = MQTTEthernet();
    MQTT::Client<MQTTEthernet, Countdown> client = MQTT::Client<MQTTEthernet, Countdown>(ipstack);
        
    oled.printf("Connecting to %s:%d\n", hostname, port);
    if  ( (rc = ipstack.connect( hostname, port ) ) != 0 )
        error( "rc from TCP connect is %d\n", rc );
 
    // mit MQTT Broker verbinden
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;       
    data.MQTTVersion = 3;
    data.clientID.cstring = "mbed-sample";
    data.username.cstring = "testuser";
    data.password.cstring = "testpassword";
    if  ( (rc = client.connect(data) ) < 0 )
        error("rc from MQTT connect is %d\n", rc);
    
    if  ( (rc = client.subscribe( topicTimer, MQTT::QOS0, messageTimerArrived ) ) != 0 )
        error("rc from MQTT subscribe %s is %d\n", topicTimer, rc);
    
    if  ( (rc = client.subscribe( topicMenu, MQTT::QOS0, messageMenuArrived ) ) != 0 )
        error("rc from MQTT subscribe %s is %d\n", topicMenu, rc); 
       
    if  ( (rc = client.subscribe( topicKeepwarm, MQTT::QOS0, messageKeepwarmArrived ) ) != 0 )
        error("rc from MQTT subscribe %s is %d\n", topicKeepwarm, rc);   
    
    printf( "%d - Wasser (1 Liter)\n", Wasser );
    printf( "%d - Reis 250 g in 327 ml Wasser\n", Reis );
    printf( "%d - Kartoffeln 650 g in 500 ml Wasser\n", Kartoffeln );
    printf( "%d - Spaghetti 500 in 1000 ml Wasser\n", Spaghetti );
    printf( "%d - Gemuese 600 g\n", Gemuese );
    printf( "%d - 4 Spiegeleier\n", Spiegelei );
    printf( "%d - 4 Eier kochen in 750 ml Wasser\n", Ei );
    printf( "%d - Steaks 300 g kurzbraten\n", Steak );
    printf( "%d - Schnitzel 400 g kurzbraten\n", Schnitzel );
    printf( "%d - Soucen 500 ml\n\n", Soucen );
    printf( "Befehle\n" );
    printf( "Timer     : mosquitto_pub -h %s -t cooker/timer -m <Sekunden> -q 1\n", hostname );
    printf( "Menu      : mosquitto_pub -h %s -t cooker/menu -m <Menu-Nr>\n", hostname );
    printf( "Warmhalten: mosquitto_pub -h %s -t cooker/keepwarm -m <0|1>\n", hostname );
    
    // Callback
    cooker.attachFinish( &finishCooker );
    
    oled.printf( "==> ready\r\n" );
    
    while   ( 1 )
    {
        led1 = 0;
        client.yield(1000);         // MQTT Client darf empfangen
        led1 = 1;
        wait( 0.2 );
    }
    
    if ((rc = client.disconnect()) != 0)
        printf("rc from disconnect was %d\n", rc);
    
    ipstack.disconnect();
    return 0;    
}

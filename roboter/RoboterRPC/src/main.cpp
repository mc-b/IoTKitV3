/** IoTKit Roboter mittels Internet steuern
*/

#include "mbed.h"
#include "rtos.h"
#include "EthernetInterface.h"
#include "HTTPServer.h"
#include "mbed_rpc.h"
#include "RpcClassesExt.h"
#include "OLEDDisplay.h"

EthernetInterface eth;
OLEDDisplay oled;

/** Hauptprogramm */
int main()
{
    printf("Robot Server\n");
    oled.printf("Robot Server\n");
    eth.init(); //Use DHCP
    eth.connect();
    printf("IP: %s\n\r", eth.getIPAddress());
    
    oled.printf("http://%s/rpc/foot/min | max | move+0.x\n", eth.getIPAddress());
     
    // Aktoren 
    RPC::construct<RpcRobotServo, PinName, float, float, const char*>( D6, 0.25f, 0.75f, "foot" ); 
    RPC::construct<RpcRobotServo, PinName, float, float, const char*>( D7, 0.275f, 0.65f, "base" ); 
    RPC::construct<RpcRobotServo, PinName, float, float, const char*>( D5, 0.275f, 0.6f, "arm" ); 
    RPC::construct<RpcRobotServo, PinName, float, float, const char*>( D10, 0.04f, 0.3f, "pincer" ); 

    // Handler
    HTTPServerAddHandler<RPCHandler>("/rpc");
    
    // Start HTTP Server auf Port 80
    printf( "ready\n" );
    HTTPServerStart(80);
}
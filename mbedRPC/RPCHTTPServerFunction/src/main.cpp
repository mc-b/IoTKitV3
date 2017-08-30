/** HTTP RPC Server mit vordefinierten Objekten
*/
#include "mbed.h"
#include "rtos.h"
#include "EthernetInterface.h"
#include "HTTPServer.h"
#include "mbed_rpc.h"
#include "Servo.h"

EthernetInterface eth;

// Servo + aktuelle Werte
Servo servo1 ( D9 );
Servo servo2 ( D10 );

// Update Servo Werte
void updateServo( Arguments * input, Reply * output )
{
    servo1 = input->getArg<float>();
    servo2 = input->getArg<float>();
}

int main()
{
    printf("RPC HTTP Server\n");
    eth.init(); //Use DHCP
    eth.connect();
    printf("IP Address is %s\n\r", eth.getIPAddress());
    
    // Klassen
    RPC::add_rpc_class<RpcDigitalOut>();
    RPC::add_rpc_class<RpcDigitalIn>();
    //RPC::add_rpc_class<RpcAnalogIn>(); // bringt Link Fehler     
    RPC::add_rpc_class<RpcPwmOut>();    
    
    // Objekte
    //RPC::construct<RpcDigitalOut, PinName, const char*>(D10, "led1"); // durch Servo belegt
    RPC::construct<RpcDigitalOut, PinName, const char*>(D11, "led2");
    RPC::construct<RpcPwmOut, PinName, const char*>(D12, "led3");
    RPC::construct<RpcDigitalIn, PinName, const char*>(A1, "b1");
    RPC::construct<RpcAnalogIn, PinName, const char*>(A0, "light");
    RPCFunction rpcFunc( &updateServo, "servos" );

    // Handler
    HTTPServerAddHandler<RPCHandler>("/rpc");
    
    // Start HTTP Server auf Port 80
    printf( "Starte Server\n" );
    HTTPServerStart(80);
}


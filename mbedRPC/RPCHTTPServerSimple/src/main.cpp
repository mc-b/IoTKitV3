/** Minimalistischer Remote Procedure Call (RPC) HTTP Server
*/
#include "mbed.h"
#include "rtos.h"
#include "EthernetInterface.h"
#include "HTTPServer.h"
#include "mbed_rpc.h"

EthernetInterface eth;

int main()
{
    printf("RPC HTTP Server\n");
    eth.init(); //Use DHCP
    eth.connect();
    printf("IP Address is %s\n\r", eth.getIPAddress());
        
    // Klassen
    RPC::add_rpc_class<RpcDigitalOut>();
    RPC::add_rpc_class<RpcDigitalIn>();
    RPC::add_rpc_class<RpcAnalogIn>(); 
    RPC::add_rpc_class<RpcPwmOut>();    
    
    // Objekte
    RPC::construct<RpcDigitalOut, PinName, const char*>(D10, "led1");
    RPC::construct<RpcDigitalOut, PinName, const char*>(D11, "led2");
    RPC::construct<RpcPwmOut, PinName, const char*>(D12, "led3");
    RPC::construct<RpcAnalogIn, PinName, const char*>(A0, "poti");
    RPC::construct<RpcAnalogIn, PinName, const char*>(A1, "light");
    RPC::construct<RpcDigitalIn, PinName, const char*>(A2, "b1");

    // Handler
    HTTPServerAddHandler<RPCHandler>("/rpc");
    
    // Start HTTP Server auf Port 80
    printf( "Starte Server\n" );
    HTTPServerStart(80);
}
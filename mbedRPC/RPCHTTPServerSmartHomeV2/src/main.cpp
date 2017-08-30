/** Remote Procedure Call (RPC) HTTP Server fuer Eclipse SmartHome (openHAB2)
*/
#include "mbed.h"
#include "rtos.h"
#include "EthernetInterface.h"
#include "HTTPServer.h"
#include "mbed_rpc.h"
#include "RpcClassesExt.h"
#include "OLEDDisplay.h"

EthernetInterface eth;

// OLED Display
OLEDDisplay oled;

int main()
{
    printf("RPC HTTP Server - SmartHome\n");
    eth.init(); //Use DHCP
    eth.connect();
    printf("IP Address is %s\n\r", eth.getIPAddress());
    
    // OLED Display
    oled.clear();
    oled.printf( "SmartHome Demo\r\n" );
    oled.printf( "%s\r\n", eth.getIPAddress() );
    wait( 5.0f );  
    
    // Klassen
    RPC::add_rpc_class<RpcDigitalOut>();
    RPC::add_rpc_class<RpcDigitalIn>();
    RPC::add_rpc_class<RpcAnalogIn>(); 
    RPC::add_rpc_class<RpcPwmOut>();   
    RPC::add_rpc_class<RpcServo>(); 
    RPC::add_rpc_class<RpcMotor>(); 
    RPC::add_rpc_class<RpcStepper>(); 
            
    // LED's
    RPC::construct<RpcPwmOut, PinName, const char*>(D10, "led1");
    RPC::construct<RpcPwmOut, PinName, const char*>(D11, "led2");
    RPC::construct<RpcPwmOut, PinName, const char*>(D12, "led3");
    RPC::construct<RpcPwmOut, PinName, const char*>(D13, "led4");
    RPC::construct<RpcLEDStrip, PinName, PinName, PinName, const char*>( D5, D6, D7, "ledstrip");
    
    // Sensoren
    RPC::construct<RpcAnalogIn, PinName, const char*>(A0, "poti");
    RPC::construct<RpcAnalogIn, PinName, const char*>(A1, "light");
    RPC::construct<RpcAnalogIn, PinName, const char*>(A2, "hall"); 
    RPC::construct<RpcTMP75, PinName, PinName, const char*>(D14, D15, "temp"); 
     
    // Aktoren 
    RPC::construct<RpcMotor, PinName, PinName, PinName, const char*>( D3, D2, D4, "motor1" );
    RPC::construct<RpcStepper, const char*>( "stepper1" );
    RPC::construct<RpcServo, PinName, const char*>( D9, "servo1" ); // muss als letzer Eintrag kommen, ansonsten wird Signal gestoert

    // Handler
    HTTPServerAddHandler<RPCHandler>("/rpc");
    
    // Start HTTP Server auf Port 80
    printf( "Starte Server\n" );
    HTTPServerStart(80);
}

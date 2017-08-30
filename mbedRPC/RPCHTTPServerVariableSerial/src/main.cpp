/** RPC Server ueber die Serielle Schnittstelle mit vordefinierten Objekten
*/
#include "mbed.h"
#include "rtos.h"
#include "mbed_rpc.h"
#include "Servo.h"

Serial pc(USBTX, USBRX);

// Servo + aktuelle Werte
Servo servo1 ( D9 );
Servo servo2 ( D10 );
float val1, val2;
Ticker servos;

// Update Servo Werte
void updateServo()
{
    servo1 = val1;
    servo2 = val2;
}

int main()
{
    printf("RPC Serial Server\n");
    servos.attach( &updateServo, 1.0 );
        
    // Klassen
    RPC::add_rpc_class<RpcDigitalOut>();
    RPC::add_rpc_class<RpcDigitalIn>();
    //RPC::add_rpc_class<RpcAnalogIn>(); // bringt Link Fehler     
    RPC::add_rpc_class<RpcPwmOut>();    
    
    // Objekte
    RPC::construct<RpcDigitalOut, PinName, const char*>(D11, "led1");
    RPC::construct<RpcDigitalOut, PinName, const char*>(D12, "led2");
    RPC::construct<RpcPwmOut, PinName, const char*>(D13, "led3");
    RPC::construct<RpcAnalogIn, PinName, const char*>(A0, "poti");
    RPC::construct<RpcAnalogIn, PinName, const char*>(A1, "light");
    RPC::construct<RpcDigitalIn, PinName, const char*>(A2, "b1");
    RPCVariable<float> rpcVal1( &val1, "servo1" );
    RPCVariable<float> rpcVal2( &val2, "servo2" );

    char buf[256], outbuf[256];
    while(1) 
    {
        pc.gets(buf, 256);
        //Call the static call method on the RPC class
        RPC::call(buf, outbuf); 
        pc.printf("%s\n", outbuf);
    }
}


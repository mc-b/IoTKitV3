/**
 * Ansteuerung Mi-Light Lampe via UDP
 * Details siehe: http://www.msxfaq.de/lync/impresence/iwylight.htm
 */

#include "mbed.h"
#include "EthernetInterface.h"

EthernetInterface eth;
UDPSocket sock;
Endpoint server;

const char* SERVER_ADDRESS = "192.168.178.37";
const int SERVER_PORT = 8899;
char buf[3];

void on()
{
    buf[0] = 0x42, buf[1] = 0x00, buf[2] = 0x55;
    sock.sendTo( server, buf, sizeof(buf) ); 
    wait( 0.1f );   
}

void off()
{
    buf[0] = 0x41, buf[1] = 0x00, buf[2] = 0x55;
    sock.sendTo( server, buf, sizeof(buf) ); 
    wait( 0.1f );
}

void brightness( char b )
{
    on();
    buf[0] = 0x4E, buf[1] = b, buf[2] = 0x55;
    sock.sendTo( server, buf, sizeof(buf) );
    wait( 0.05f ); 
}

void color( char b )
{
    on();
    buf[0] = 0x40, buf[1] = b, buf[2] = 0x55;
    sock.sendTo( server, buf, sizeof(buf) ); 
}

/** Hauptprogramm */
int main() 
{
    eth.init(); //Use DHCP
    eth.connect();
    printf("\nClient IP Address is %s \n", eth.getIPAddress());
    
    sock.init();
    server.set_address( SERVER_ADDRESS, SERVER_PORT );
    
    while   ( 1 )
    {
        // Helligkeitstest
        printf( "Helligkeit %s:%d\n", SERVER_ADDRESS, SERVER_PORT );
        for ( char i = 0x02; i < 0x1B; i++ )
            brightness( i );
        wait( 1.0f );
        
        // Farben
        printf( "Farben %s:%d\n", SERVER_ADDRESS, SERVER_PORT );
        for ( char i = 0x00; i < 0xFF; i++ )
            color( i );
        wait( 1.0f );
               
        off();
        wait( 2.0f );        
            
    }
    sock.close();
    eth.disconnect();
}
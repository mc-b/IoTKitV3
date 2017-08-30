/** Ethernet Interface initialisieren
*/
#include "mbed.h"
#include "EthernetInterface.h"       

EthernetInterface eth;
// wird nur benoetigt, damit bei Eclipse/gcc4mbed die Ethernet Libraries richtig gelinkt werden
TCPSocketConnection sock;

int main()
{
    printf("EthernetInterface Setting up...\r\n");
    if( eth.init() != 0 ) 
    {                             //for DHCP Server
        printf("EthernetInterface Initialize Error \r\n");
        return -1;
    }
    if( eth.connect() != 0 ) 
    {
        printf("EthernetInterface Connect Error \r\n");
        return -1;
    }
    printf("IP Address is %s\r\n", eth.getIPAddress());
    printf("NetMask is %s\r\n", eth.getNetworkMask());
    printf("Gateway Address is %s\r\n", eth.getGateway());
    printf("MAC Address is %s\r\n", eth.getMACAddress());
    printf("Ethernet Setup OK\r\n");
    
    while   ( 1 )
    {
        // hier kommen die Zugriffe auf das Internet ...
    }
} 

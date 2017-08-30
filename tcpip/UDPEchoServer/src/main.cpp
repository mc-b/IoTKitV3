#include "mbed.h"
#include "EthernetInterface.h"

#define ECHO_SERVER_PORT   7

int main (void) {
    EthernetInterface eth;
    eth.init(); //Use DHCP
    eth.connect();
    printf("\nServer IP Address is %s\n", eth.getIPAddress());
    
    UDPSocket server;
    server.bind(ECHO_SERVER_PORT);
    
    Endpoint client;
    char buffer[256];
    while (true) {
        printf("\nWaiting for UDP packet...\n");
        int n = server.receiveFrom(client, buffer, sizeof(buffer));
        buffer[n] = '\0';
        
        printf("Received packet from: %s\n", client.get_address());
        printf("Packet contents : '%s'\n",buffer);
        printf("Sending Packet back to Client\n");
        server.sendTo(client, buffer, n);
    }
}

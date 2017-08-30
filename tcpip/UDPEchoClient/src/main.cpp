#include "mbed.h"
#include "EthernetInterface.h"

const char* ECHO_SERVER_ADDRESS = "192.168.2.2";
const int ECHO_SERVER_PORT = 7;

int main() {
    EthernetInterface eth;
    eth.init(); //Use DHCP
    eth.connect();
    printf("\nClient IP Address is %s \n", eth.getIPAddress());
    
    UDPSocket sock;
    sock.init();
    
    Endpoint echo_server;
    echo_server.set_address(ECHO_SERVER_ADDRESS, ECHO_SERVER_PORT);
    
    char out_buffer[] = "Hello World";
    printf("Sending  message '%s' to server (%s)\n",out_buffer,ECHO_SERVER_ADDRESS);
    sock.sendTo(echo_server, out_buffer, sizeof(out_buffer));
    
    char in_buffer[256];
    int n = sock.receiveFrom(echo_server, in_buffer, sizeof(in_buffer));
    
    in_buffer[n] = '\0';
    printf("Received message from server: '%s'\n", in_buffer);
    
    sock.close();
    
    eth.disconnect();
    while(1) {}
}
#include "mbed.h"
#include "EthernetInterface.h"

const char* ECHO_SERVER_ADDRESS = "192.168.2.2";
const int ECHO_SERVER_PORT = 7;

int main() {
    EthernetInterface eth;
    eth.init(); //Use DHCP
    eth.connect();
    printf("\nClient IP Address is %s\n", eth.getIPAddress());
    
    // Connect to Server
    TCPSocketConnection socket;
    while (socket.connect(ECHO_SERVER_ADDRESS, ECHO_SERVER_PORT) < 0) {
        printf("Unable to connect to (%s) on port (%d)\n", ECHO_SERVER_ADDRESS, ECHO_SERVER_PORT);
        wait(1);
    }
    printf("Connected to Server at %s\n",ECHO_SERVER_ADDRESS);
    
    // Send message to server
    char hello[] = "Hello World";
    printf("Sending  message to Server : '%s' \n",hello);
    socket.send_all(hello, sizeof(hello) - 1);
    
    // Receive message from server
    char buf[256];
    int n = socket.receive(buf, 256);
    buf[n] = '\0';
    printf("Received message from server: '%s'\n", buf);
    
    // Clean up
    socket.close();
    eth.disconnect();
    
    while(true) {}
}

/** Minimalistischer WebServer
*/
#include "mbed.h"
#include "EthernetInterface.h"

EthernetInterface eth;
TCPSocketServer server;
TCPSocketConnection client;
// I/O Buffer
char buffer[1024] = {};

DigitalOut led1(LED1); //server listning status

int main (void)
{
    eth.init(); //Use DHCP
    eth.connect();
    printf("IP Address is %s\n\r", eth.getIPAddress());

    // Listen an Port 80 mit max. 1 Socket
    server.bind( 80 );
    server.listen( 1 );

    //listening for http GET request
    while ( 1 ) 
    {
        printf( "tcp server is listening...\n" );
        // Client sendet Daten
        if  ( server.accept( client ) == 0 ) 
            // Daten empfangen
            if  ( client.receive(buffer, 1023) > 0 ) 
            {
                printf( "connection success!\n\rIP: %s\n\r",client.get_address() );
                led1 = 1;

                printf( "Recieved Data: %d\n\r\n\r%.*s\n\r", strlen(buffer), strlen(buffer), buffer );
                if( strncmp( buffer, "GET", 3) == 0 ) 
                {
                    // Header
                    // HTTP/1.1 200 OK - GET erfolgreich
                    // Server: mbed - Server ID
                    // Content-Length: 11 - laenge der Daten (Nachrichtenrumpf)
                    // Connection: close - Verbindung schliessen
                    // Access-Control-Allow-Origin: * - Zugriff via AJAX von einem fremden Host erlauben
                    // Content-Type: text/plain - MIME Type
                    // \n\n
                    // Daten (Nachrichtenrumpf)
                    sprintf( buffer, "HTTP/1.1 200 OK\nServer: mbed\nContent-Length: 11\nConnection: close\nAccess-Control-Allow-Origin: *\nContent-Type: text/plain\n\n%s\n", "Hallo Welt" );
                    client.send( buffer, strlen(buffer) );
                }
                printf( "close connection.\n" );
                client.close();
                led1 = 0;
            }
    }
}

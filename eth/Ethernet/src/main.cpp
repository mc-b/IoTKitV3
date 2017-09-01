/** Ethernet Interface initialisieren
*/

#include "mbed.h"
#include "easy-connect.h"

int main()
{
    // Connect to the network (see mbed_app.json for the connectivity method used)
    NetworkInterface* network = easy_connect(true);
    if ( !network )
    {
        printf("Cannot connect to the network, see serial output");
        return 1;
    }

    printf("IP Address is %s\r\n", network->get_ip_address());
    printf("MAC Address is %s\r\n", network->get_mac_address());
    printf("Ethernet Setup OK\r\n");
    
    while   ( 1 )
    {
        // hier kommen die Zugriffe auf das Internet ...
    }
} 

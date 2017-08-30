/** Kitchen Helper Project
*/
#include "mbed.h"
#include "rtos.h"
#include "EthernetInterface.h"
#include "HTTPServer.h"
#include "mbed_rpc.h"
#include "OLEDDisplay.h"

// Kocher
#include "Cooker.h"
#include "RPCCooker.h"

EthernetInterface eth;

// OLED Display
OLEDDisplay oled;

// HTTP GET (REST, IFTTT)
#include "HTTPClient.h"

// HTTP Hilfsklassen
HTTPClient http;
// I/O Buffer
char message[256];

char *finishMsg = "https://maker.ifttt.com/trigger/cooker_finish/with/key/mY3_IZhJSfm-tj3UVytotaqtD1L5AIEUMcal8nDy4dJ";

/** Aufruf vom Kochfeld - kochen beendet - hier darf kein printf oder http.get stehen, weil Aufruf von Timer */
void finishCooker()
{
    http.get( finishMsg, message, sizeof(message) );
}

/** Hauptprogramm */
int main()
{
    printf( "\n\n\n\n\nRPC HTTP Server - Kitchen Helper Project\n" );
    eth.init(); //Use DHCP
    eth.connect();
    
    // OLED Display
    oled.clear();
    oled.printf( "KitchenHelper\r\n" );
    oled.printf( "%s\r\n", eth.getIPAddress() );
    wait( 5.0f );   
    
    printf( "%d - Wasser (1 Liter)\n", Wasser );
    printf( "%d - Reis 250 g in 327 ml Wasser\n", Reis );
    printf( "%d - Kartoffeln 650 g in 500 ml Wasser\n", Kartoffeln );
    printf( "%d - Spaghetti 500 in 1000 ml Wasser\n", Spaghetti );
    printf( "%d - Gemuese 600 g\n", Gemuese );
    printf( "%d - 4 Spiegeleier\n", Spiegelei );
    printf( "%d - 4 Eier kochen in 750 ml Wasser\n", Ei );
    printf( "%d - Steaks 300 g kurzbraten\n", Steak );
    printf( "%d - Schnitzel 400 g kurzbraten\n", Schnitzel );
    printf( "%d - Soucen 500 ml\n\n", Soucen );
    printf( "Befehle\n" );
    printf( "Timer     : http://%s/rpc/cooker/timer+<Sekunden>\n", eth.getIPAddress());
    printf( "Menu      : http://%s/rpc/cooker/menu+<Menu-Nr>\n", eth.getIPAddress());
    printf( "Warmhalten: http://%s/rpc/cooker/keepwarm<0|1>\n", eth.getIPAddress());

    // Kochfeld Remote Zugriff 
    RpcCooker cooker = RpcCooker( D11, D12, D13, "cooker" );
    RPC::add_rpc_class<RpcCooker>(); 
    // Callback
    cooker.attachFinish( &finishCooker );
    
    // Handler
    HTTPServerAddHandler<RPCHandler>("/rpc");
    
    // Start HTTP Server auf Port 80
    printf( "Starte Server - Bereit\n" );
    HTTPServerStart(80);
}

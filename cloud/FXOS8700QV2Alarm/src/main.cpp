/** 6 Achsen Sensor auf FRDM-K64F Board mit Alarm via IFTTT
*/
#include "mbed.h"
#include "FXOS8700Q.h"
#include "OLEDDisplay.h"
#include "HTTPClient.h"
#include "data/HTTPText.h"
#include "EthernetInterface.h"

OLEDDisplay oled;

// Lage Sensor am Standard I2C Bus
FXOS8700Q_acc acc( D14, D15, FXOS8700CQ_SLAVE_ADDR1 );

// HTTP Hilfsklassen
EthernetInterface eth;
HTTPClient http;
char *finishMsg = "https://maker.ifttt.com/trigger/cooker_finish/with/key/mY3_IZhJSfm-tj3UVytotaqtD1L5AIEUMcal8nDy4dJ";
// I/O Buffer
char message[256];

DigitalOut led1( D10 );
DigitalOut led2( D11 );
DigitalIn reset( A0 );

int main(void)
{
    // Ethernet
    eth.init();
    eth.connect();
    
    float x, y, z;
    oled.clear();
    oled.printf( "6 Achsen Alarm" );
    acc.enable();
    
    led1 = 0;
    led2 = 1;
    while (true) 
    {
        acc.getX( &x );     // X Achse
        acc.getY( &y );     // Y Achse
        acc.getZ( &z );     // Z Achse - wird benoetigt um festzustellen ob das Board auf dem Kopf liegt

        oled.cursor( 1, 0 );
        oled.printf( "x=%3.2f\ny=%3.2f\nz=%3.2f\n", x, y, z );
            
        // Alarm scharf
        if  ( led1 == 0 )
        {
            oled.cursor( 0, 0 );
            oled.printf( "scharf          " );
            if  ( z < 0 )
            {
                oled.cursor( 0, 0 );
                oled.printf( "ALARM !!!       " );
                http.get( finishMsg, message, sizeof(message) );
                led1 = 1;
                led2 = 0;                
            }
        }
        else
        {
            if  ( reset == 0 )
            {
                oled.cursor( 0, 0 );
                oled.printf( "reset         " );                
                led1 = 0;
                led2 = 1;
            }
        }                    

        wait( 0.2f );
    }
}

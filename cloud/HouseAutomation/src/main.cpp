/** Haus Automation mit Alarm via IFTTT
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

// Alarm 
DigitalOut led1( D10 );
DigitalOut led2( D11 );
DigitalIn reset( A0 );

// Lichtschaltung
AnalogIn lightSensor( A1 );
DigitalOut licht( D13 );

// Fenstersicherung
AnalogIn hallSensor( A2 );

// Bewegungssicherung
DigitalIn pirSensor( A5 );

int main(void)
{
    // Ethernet
    eth.init();
    eth.connect();
    
    float x, y, z;
    oled.clear();
    oled.setRotation( 2 );
    oled.printf( "Haus Automation" );
    acc.enable();
    
    led1 = 0;
    led2 = 1;
    while (true) 
    {
        // Alarm scharf
        while  ( led1 == 0 )
        {
            oled.cursor( 0, 0 ); 
            acc.getX( &x );     // X Achse
            acc.getY( &y );     // Y Achse
            acc.getZ( &z );     // Z Achse - wird benoetigt um festzustellen ob das Board auf dem Kopf liegt            
            // Lage Alarm           
            if  ( z < 0 )
            {
                oled.clear();
                oled.printf( "ALARM !!!       \r\n" );
                oled.printf( "Lage z (%3.2f)", z );
                http.get( finishMsg, message, sizeof(message) );
                led1 = 1;
                led2 = 0;    
                break;            
            }
            else
            {
                oled.cursor ( 0, 0 );
                oled.printf( "Lage z (%3.2f)", z );
            }
            // Alarm - Fenster
            if  ( hallSensor < 0.4f || hallSensor > 0.6f )
            {
                oled.clear();
                oled.printf( "ALARM !!!       \r\n" );     
                oled.printf( "Fenster (%3.2f)", hallSensor.read() );           
                http.get( finishMsg, message, sizeof(message) );
                led1 = 1;
                led2 = 0;  
                break;                 
            }
            else
            {
                oled.cursor( 1, 0 );
                oled.printf( "Fenster OK (%3.2f)", hallSensor.read() ); 
            }                
            // Alarm Bewegung
            if  ( pirSensor == 1 )
            {
                oled.clear();
                oled.printf( "ALARM !!!       \r\n" );     
                oled.printf( "Bewegung" );           
                http.get( finishMsg, message, sizeof(message) );
                led1 = 1;
                led2 = 0;     
                break;           
            }
            else
            {
                oled.cursor( 2, 0 );
                oled.printf( "Bewegung - OK" );
            }
            // Lichtsteuerung
            oled.cursor( 3, 0 );
            oled.printf( "Licht (%3.2f)", lightSensor.read() );
            if  ( lightSensor < 0.6f )
                licht = 1;
            else
                licht = 0;
        }
        
        // Alarm RESET
        if  ( reset == 0 )
        {
            oled.cursor( 0, 0 );
            oled.printf( "Alarme OFF        " );                
            led1 = 0;
            led2 = 1;
        }

        wait( 0.2f );
    }
}

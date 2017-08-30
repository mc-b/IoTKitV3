/** 7.4 Sensordaten schreiben via HTTP POST
*/
#include "mbed.h"
#include "HTTPClient.h"
#include "data/HTTPText.h"
#include "EthernetInterface.h"
#include "TMP175.h"

EthernetInterface eth;
// HTTPClient Hilfsklasse
HTTPClient http;
// I/O Buffer
char str[512];

// Sensoren
AnalogIn poti  ( A0 );
AnalogIn light ( A1 );
AnalogIn hall  ( A2 );
TMP175 temp    ( D14, D15 );
// Separater Buffer um die Sensorwerte als String abzustellen
char fa[4] [12];

DigitalOut myled(LED1);

/** Float nach String wandeln
 * @param pos Position in I/O Buffer
 * @param value Wert
 * @return Pointer auf I/O Buffer
 */
char* ftoa( int pos, float value )
{
    sprintf( fa[pos], "%4.4f", value );
    return  ( fa[pos] );
}

int main()
{
    printf("HTTP Client - POST\n");
    eth.init();
    eth.connect();
    
    temp.vSetConfigurationTMP175( SHUTDOWN_MODE_OFF | COMPARATOR_MODE | POLARITY_0 |FAULT_QUEUE_6 | RESOLUTION_12, 0x48 );
    temp.vSetTemperatureLowTMP175( 0.0 );
    temp.vSetTemperatureHighTMP175( 60.0 );    

    while(1) 
    {
        myled = 1;

        // Hilfsklasse um die Response vom Server zu formatieren     
        HTTPText inText(str, 512);
        
        // MAP (Argument=Wert) 
        HTTPMap map;
        map.put( "poti", ftoa( 0, poti.read() ) );
        map.put( "light", ftoa(1, light.read() ) );
        map.put( "hall", ftoa( 2, hall.read() ) );
        map.put( "temp", ftoa( 3, temp.fReadTemperatureTMP175() ) );
        
        // lokale Variante mit CGI-Script auf IoT USB Stick. Wenn nicht Funktioniert: iot-stick durch IP-Adresse ersetzen
        int ret = http.post("http://iotkit/rest/cgi-bin/restsql", map, &inText);
        if ( ! ret ) 
        {
            printf("Executed POST successfully - read %d characters\n", strlen(str));
            printf("Result: %s\n", str);
        } 
        else 
        {
            printf("Error - ret = %d - HTTP return code = %d\n", ret, http.getHTTPResponseCode());
        }
        
        myled = 0;

        wait(10);
    }
    //eth.disconnect();
} 

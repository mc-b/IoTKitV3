/** Beispiel Abfrage Yahoo Weather fuer Zuerich
 */
#include "mbed.h"
#include "HTTPClient.h"
#include "data/HTTPText.h"
#include "EthernetInterface.h"
#include "spdomparser.hpp"
#include "spxmlnode.hpp"
#include "spxmlhandle.hpp"

EthernetInterface eth;
// HTTPClient Hilfsklasse
HTTPClient http;
// I/O Buffer
char message[6000];

DigitalOut myled(LED1);

int main()
{
    printf("\tYahoo Weather\n");
    eth.init();
    eth.connect();

    // Yahoo Weather fuer Zuerich
    while(1) 
    {
        myled = 1;
        HTTPText inText( message, sizeof(message) );
        // MAP (Argument=Wert) 
        HTTPMap map;
        map.put( "q", "select * from weather.forecast where woeid=784794" );
        map.put( "format", "xml" );
        int ret = http.post( "https://query.yahooapis.com/v1/public/yql", map, &inText );
        if ( !ret ) 
        {
            // XML Parser
            SP_XmlDomParser parser;
            // char[] bzw. XML parsen
            parser.append( message, strlen( message ) );
            SP_XmlHandle rootHandle( parser.getDocument()->getRootElement() );
            SP_XmlElementNode * results = rootHandle.getChild( "results" ).toElement();
            SP_XmlHandle hresults( results );              
            SP_XmlElementNode * node = hresults.getChild( "channel" ).toElement();
            SP_XmlHandle handle(node);
            SP_XmlElementNode * condition = handle.getChild( "item" ).getChild("yweather:condition").toElement();
            
            // Allgemeine Lage, Sonnig, Bewoelkt etc.
            printf( "%s, ", condition->getAttrValue("text") );
            // Temperatur in Celsius
            printf( "%4.2fC, ", (atof( condition->getAttrValue("temp") ) - 32.0) * 0.555555f  );
            // Datum und Zeit letzte Aktualisierung
            printf( "%s\n", condition->getAttrValue("date") );
            
            // Forecast fuer die naechsten Drei Tage
            for ( int day = 1; day < 4; day++ )
            {
                SP_XmlElementNode * forecast = handle.getChild( "item" ).getChild("yweather:forecast", day ).toElement(); 
                if  ( forecast )
                {
                    // Allgemeine Lage, Sonnig, Bewoelkt etc.
                    printf( "%s: %s, ", forecast->getAttrValue("date"), forecast->getAttrValue("text") );
                    // Temperatur in Celsius
                    printf( "low %4.2fC, ", (atof( forecast->getAttrValue("low") ) - 32.0) * 0.555555f  );
                    printf( "high %4.2fC\n", (atof( forecast->getAttrValue("high") ) - 32.0) * 0.555555f  );
                }
                else
                    printf( "missing forcast\n" );
            }
        } 
        else
            printf("Error - ret = %d - HTTP return code = %d\n", ret, http.getHTTPResponseCode());

        myled = 0;

        wait(10);
    }
    //eth.disconnect();
}

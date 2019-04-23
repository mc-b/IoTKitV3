/** Beispiel Abfrage Cloud Dienst Sunrise / Sunset
 */
#include "mbed.h"
#include "http_request.h"
#include "network-helper.h"
#include "spdomparser.hpp"
#include "spxmlnode.hpp"
#include "spxmlhandle.hpp"

DigitalOut myled( MBED_CONF_IOTKIT_LED1 );

int main()
{
    printf("\tYahoo Weather\n");
    // Connect to the network with the default networking interface
    // if you use WiFi: see mbed_app.json for the credentials
    NetworkInterface* network = connect_to_default_network_interface();

    if (!network) {
        printf("Cannot connect to the network, see serial output\n");
        return 1;
    }

    while( 1 )
    {
        myled = 1;
        HttpRequest* get_req = new HttpRequest(network, HTTP_GET, "http://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid=784794");

        HttpResponse* post_res = get_req->send();
        if (!post_res)
        {
            printf("HttpRequest failed (error code %d)\n", get_req->get_error());
            return 1;
        }
        printf("\n----- HTTP POST response -----\n");
        printf("\nBody (%d bytes):\n\n%s\n", post_res->get_body_length(), post_res->get_body_as_string().c_str());

        // XML Parser
        SP_XmlDomParser parser;
        // char[] bzw. XML parsen
        parser.append( post_res->get_body_as_string().c_str(), strlen( post_res->get_body_as_string().c_str() ) );
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
        delete get_req;
        myled = 0;
        wait(10);
    }
}

/** Beispiel XML Parser
*/
#include "mbed.h"

#include "spdomparser.hpp"
#include "spxmlnode.hpp"
#include "spxmlhandle.hpp"

const char xml[] =  "<a>"\
                    "<b>"\
                    "<c>"\
                    "<d c=\"123\">eins</d>"\
                    "<e>zwei</e>"\
                    "<f>drei</f>"\
                    "</c>"\
                    "</b>"\
                    "</a>";

int main()
{
    // XML Parser
    SP_XmlDomParser parser;
    // char[] bzw. XML parsen 
    parser.append( xml, strlen( xml ) );

    // Zugriff auf root
    SP_XmlHandle rootHandle( parser.getDocument()->getRootElement() );
    printf( "root %s\n", parser.getDocument()->getRootElement()->getName() );

    // Zugriff auf 3. Hierarchie
    SP_XmlElementNode * child2 = rootHandle.getChild( "b" ).getChild( "c").getChild( "d").toElement();
    printf( "%s, attr c=%s, text=", child2->getName(), child2->getAttrValue( "c" ) );
    const SP_XmlNodeList * list = child2->getChildren();
    for ( int i = 0; i < list->getLength(); i++ )
        printf( "%s\n", ((SP_XmlCDataNode*) list->get( i ))->getText() );

    // Zugriff auf f
    child2 = rootHandle.getChild( "b" ).getChild( "c").getChild( "f").toElement();    
    printf( "%s, text=", child2->getName() );    
    list = child2->getChildren();
    for ( int i = 0; i < list->getLength(); i++ )
        printf( "%s\n", ((SP_XmlCDataNode*) list->get( i ))->getText() );    
}
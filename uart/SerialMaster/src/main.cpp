/** UART Kommunikation - Master
 *  Serial Header uebers Kreuz verbinden.
*/
#include "mbed.h"

Serial serial( D1, D0 );
char *cmd[] = { "red", "green", "blue" };
char buf[128];

/** eine Zeile vom UART lesen */
void readline()
{
    int c = 0;
    while  ( 1 )
    {
        char rc = serial.getc();
        
        buf[c] = rc;
        if  ( buf[c] == '\n' || c >= sizeof(buf) )
        {
            buf[c] = '\0';
            break;
        }
        c++;
    }     
}

int main()
{
    // Schmutz auf Leitung entfernen
    serial.printf( "....\n" );
    readline();
    
    while ( 1 ) 
    {
        for ( int i = 0; i < 3; i++ )
        {
            serial.printf( "%s\n", cmd[i] );
            readline();
            wait( 0.1f );
        }
    }
}                   

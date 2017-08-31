/** UART Kommunikation - Slave
*/
#include "mbed.h"

DigitalOut led[] = { DigitalOut( D10, 1 ), DigitalOut( D11, 1 ), DigitalOut( D12, 1 ) };
Serial serial( USBTX, USBRX );
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
    while ( 1 ) 
    {
        readline();
        // Pause ansonsten erfolgt ein TimeOut
        //wait( 0.01f );
        
        if  ( strcmp( buf, "red" ) == 0 )
        {
            led[0] = ! led[0];
            serial.printf( "OK\n" );
        }
        else if  ( strcmp( buf, "green" ) == 0 )
        {
            led[1] = ! led[1]; 
            serial.printf( "OK\n" );
        }
        else if  ( strcmp( buf, "blue" ) == 0 )
        {
            led[2] = ! led[2];
            serial.printf( "OK\n" );
        }
        else
            serial.printf( "N.A.\n" );
    }
}                   

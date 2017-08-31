/** ESP 8266 WLAN Modem initialisieren 
 *  - muss als erstes erfolgen, damit die Verbindung zum AP steht
 *  - wenn das Modem nicht sauber oder zu langsam funktoniert, wait Zeiten erhoehen
*/
#include "mbed.h"

RawSerial  pc( USBTX, USBRX );
RawSerial  dev( A1, A0 );
// Reset Modem
DigitalOut rst( D10 );
DigitalOut led1( D11 );
DigitalOut led4( D12 );

/** Lesen von Modem, Ausgabe auf UART USB */
void recv()
{
    led1 = !led1;
    while( dev.readable() ) 
        pc.putc( dev.getc() );
}

/** Schreiben auf Modem ab UART USB */
void send()
{
    led4 = !led4;
    while( pc.readable() ) 
        dev.putc( pc.getc() );
}

/** Senden eines Strings an das Modem */
void send( char* out )
{
    while   ( *out != '\0' )
    {
        dev.putc( *out );
        out++;
    }
    dev.putc( '\r' );
    dev.putc( '\n' );
}

int main()
{
    rst = 0;
    // 1. Teil: Initialisierung - Baudraten muessen identisch sein
    pc.baud( 115200 );
    dev.baud( 115200 );
    wait( 1.0f );
    rst = 1;

    pc.attach( &send, Serial::RxIrq );
    dev.attach( &recv, Serial::RxIrq );
    
    send( "AT+RST" );       // RESET Modem
    wait( 2.0f );
    
    send( "AT+GMR" );       // Ausgabe Firmware Version - optional
    wait( 2.0f );    
    
    send( "AT+CWMODE=1" );  // Station Mode, d.h. Modem = Client zu AP
    wait( 1.0f ); 
    
    //send( "AT+CWLAP" );     // List AP - optional
    //wait( 10.0f );     
    
    send( "AT+CWJAP=\"mcbmobile_2EX\",\"android%123\"" );  // Verbindung AP (SSID, PW)
    wait( 10.0f );    
    
    send( "AT+CIFSR" );  // Ausgabe IP-Adresse
    wait( 1.0f );
    
    // 2. Teil: Webseite von google.com holen
    send( "AT+CIPMUX=1" );  // Mehrere Verbindungen aktivieren
    wait( 1.0f );    
    
    send( "AT+CIPSTART=4,\"TCP\",\"google.com\",80" );  // Socket zu google.com oeffnen
    wait( 1.0f ); 
    
    send( "AT+CIPSEND=4,18" );  // 18 Zeichen senden
    wait( 1.0f );     
    
    send( "GET / HTTP/1.0\r\n" );  // HTTP GET
    wait( 2.0f );     
    
    // Passthrough USB - Modem (alle Befehle von Terminal 1:1 an Modem leiten und umgekehrt)
    while(1) 
    {
        sleep();
    }    
}

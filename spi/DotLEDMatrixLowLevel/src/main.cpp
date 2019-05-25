/** Dot LED Matrix - LowLevel via SPI angesteuert
*/
#include "mbed.h"

SPI spi( MBED_CONF_IOTKIT_DOTLED_MOSI, MBED_CONF_IOTKIT_DOTLED_MISO, MBED_CONF_IOTKIT_DOTLED_SCLK );
DigitalOut ss( MBED_CONF_IOTKIT_DOTLED_SS );   // Steuerpin!!!

// Systemregister Dot LED Matrix
#define reg_decodeMode   0x09
#define reg_intensity    0x0a
#define reg_scanLimit    0x0b
#define reg_shutdown     0x0c

/** Schreibe 1 Byte in Register
 * @param r = Register
 * @param v = Wert
*/
void writeToReg( int r, int v )
{
    ss = 0;
    spi.write( r );
    spi.write( v );
    ss = 1;
}

/** Hauptprogramm */
int main()
{
    // Initialisierung
    spi.format( 8,0 );
    spi.frequency( 1000000 );
    
    writeToReg( reg_decodeMode, 0x00 );
    writeToReg( reg_intensity, 0x0f );
    writeToReg( reg_scanLimit, 0x07 );
    writeToReg( reg_shutdown, 0x01 );
    writeToReg( 0xff, 0x00 );    
    
    while   ( 1 )
    {
        // Dot LED Matrix Anzeige loeschen
        for ( int r = 1; r <= 8; r++ )
            writeToReg( r, 0 );
            
        wait( 0.5f );
        
        for ( int r = 1; r <= 8; r++ )
            for ( int c = 0; c < 256; c++ )
            {
                writeToReg( r, c );
                wait( 0.01f );
            }
        wait( 0.5f );
    }
}

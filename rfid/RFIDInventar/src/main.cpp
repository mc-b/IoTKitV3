/** Inventar mittels RFID Tag's durchfuehren
*/
#include "mbed.h"
#include "MFRC522.h"
#include "OLEDDisplay.h"

// NFC/RFID Reader (SPI)
MFRC522    rfidReader( D11, D12, D13, D10, D8 );
OLEDDisplay oled;

DigitalOut led1( D10 );

// erlaubte RFID Tag's
char ids[4] [4] = {
    { 0x84, 0x66, 0x19, 0x1d },
    { 0x14, 0x63, 0x19, 0x1d },
    { 0xb4, 0x72, 0x19, 0x1d },
    { 0x83, 0x2c, 0xb8, 0x02 },
};

/** Anzahl Gegenstaende vom Typ x */
int counts[4] = { 0, 0, 0, 0 };

int main(void)
{
    // OLED Display
    oled.clear();
    oled.setRotation( 2 );
    oled.printf( "RFID Inventar\n" );
    
    // Init. RC522 Chip
    rfidReader.PCD_Init();
    oled.printf( "bereit\n" );

    while (true) 
    {
        led1 = 0;

        // Look for new cards
        if ( rfidReader.PICC_IsNewCardPresent())
            if ( rfidReader.PICC_ReadCardSerial()) 
            {
                led1   = 1;

                // Print Card UID (2-stellig mit Vornullen, Hexadecimal)
                printf("Card UID: ");
                for ( int i = 0; i < rfidReader.uid.size; i++ )
                    printf("%02X:", rfidReader.uid.uidByte[i]);
                printf("\n");

                // alle ids durchlaufen (r = ids, c = position)
                for ( int r = 0; r < 4; r++ ) 
                {
                    int ok = true;
                    for ( int c = 0; c < 4; c++ ) 
                    {
                        if  ( rfidReader.uid.uidByte[c] != ids[r] [c] ) 
                        {
                            ok = false;
                            break;
                        }
                    }
                    // RFID Tag's erkannt?
                    if  ( ok ) 
                    {
                        counts[r] += 1;
                        oled.cursor( 0, 0 );        
                        oled.printf( "Container: %4d\r\n", counts[0] );
                        oled.printf( "Kochtopf : %4d\r\n", counts[1] );
                        oled.printf( "Tank     : %4d\r\n", counts[2] );
                        oled.printf( "Diverses : %4d\r\n", counts[3] );                        
                        break;
                    }
                }
            }
        wait ( 0.2f );
    }
}

/** Beispiel fuer das Auslesen von RFID Tags mittels RFID Reader
*/
#include "mbed.h"
#include "MFRC522.h"
#include "OLEDDisplay.h"

// OLED Display
OLEDDisplay oled( PTE26, PTE0, PTE1 );

// NFC/RFID Reader (SPI)
MFRC522    rfidReader( PTA16, PTC7, PTC5, D10, D8 );

int main()
{
    // OLED Display
    oled.clear();
    oled.printf( "RFID Demo\r\n" );
        
    printf("RFID Reader MFRC522 Test\n");
    rfidReader.PCD_Init();

    while   ( 1 ) 
    {
        // RFID Reader
        if ( rfidReader.PICC_IsNewCardPresent())
            if ( rfidReader.PICC_ReadCardSerial()) 
            {
                oled.cursor( 1, 0 );                
                // Print Card UID (2-stellig mit Vornullen, Hexadecimal)
                oled.printf("UID: ");
                for ( int i = 0; i < rfidReader.uid.size; i++ )
                    oled.printf("%02X:", rfidReader.uid.uidByte[i]);
                oled.printf("\r\n");
                
                // Print Card type
                int piccType = rfidReader.PICC_GetType(rfidReader.uid.sak);
                oled.printf("PICC Type: %s \r\n", rfidReader.PICC_GetTypeName(piccType) );
            }
        wait( 0.2f );
    }
}

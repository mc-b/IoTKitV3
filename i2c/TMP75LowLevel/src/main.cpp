/** Temperatursensor TMP75 auf SMD Shield 
    via I2C Methoden angesprochen.
*/
#include "mbed.h"

I2C i2c( D14, D15 );

// Adresse + I/O Buffer
int addr = 0x48 << 1;
char cmd[4];

// Konfigurationsvariablen
char configReg = 0x01;  // Address of Configuration Register
char bitConv = 0x60;    // Set to 12 bit conversion
char rdOnly = 0x00;     // Set to Read

int main()
{
    // Initialisierung
    cmd[0] = configReg;
    cmd[1] = bitConv;
    i2c.write( addr, cmd, 2 );

    cmd[0] = rdOnly;
    i2c.write( addr, cmd, 1 );

    while   ( 1 ) 
    {
        i2c.read( addr, cmd, 2 );
        // Being a 12 bit integer use 2's compliment for negative temperature values
        int t = (((cmd[0] << 8) | cmd[1]) >> 4);
        // From Datasheet the TMP75 has a quantisation value of 0.0625 degreesC per bit
        float temp = ( t * 0.0625 );
        printf  ( "Temperatur %f C\n", temp );
        wait( 1.0 );
    }
}

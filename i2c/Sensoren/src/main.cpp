/** Anzeigen von Sensoredaten auf dem Display
*/
#include "mbed.h"
#include "OLEDDisplay.h"

// Sensoren
AnalogIn poti  ( A0 );
AnalogIn light ( A1 );
AnalogIn hall  ( A2 );
I2C i2c( D14, D15 );

// Adresse + I/O Buffer
int addr = 0x48 << 1;
char cmd[4];

// Konfigurationsvariablen
char configReg = 0x01;  // Address of Configuration Register
char bitConv = 0x60;    // Set to 12 bit conversion
char rdOnly = 0x00;     // Set to Read

DigitalOut myled( D10 );

OLEDDisplay oled;

int main()
{
    // Initialisierung Temperatur Sensor
    cmd[0] = configReg;
    cmd[1] = bitConv;
    i2c.write( addr, cmd, 2 );

    cmd[0] = rdOnly;
    i2c.write( addr, cmd, 1 );
    
    // OLED Display
    oled.clear();
    oled.printf( "Sensoren Demo\r\n" );
    
    oled.clear();
    while(1) 
    {
        myled != myled;
        i2c.read( addr, cmd, 2 );
        // Being a 12 bit integer use 2's compliment for negative temperature values
        int t = (((cmd[0] << 8) | cmd[1]) >> 4);
        // From Datasheet the TMP75 has a quantisation value of 0.0625 degreesC per bit
        float temp = ( t * 0.0625 );
                
        printf( "Poti : %4.2f\r\n", poti.read()  );
        printf( "Light: %4.2f\r\n", light.read() );
        printf( "Hall : %4.2f\r\n", hall.read() );
        printf( "Temp : %4.2f\r\n", temp );
        
        oled.cursor( 0, 0 );        
        oled.printf( "Poti : %4.3f\r\n", poti.read()  );
        oled.printf( "Light: %4.3f\r\n", light.read() );
        oled.printf( "Hall : %4.3f\r\n", hall.read() );
        oled.printf( "Temp : %4.3f\r\n", temp );
        
        wait( 1.0f );
    }
} 
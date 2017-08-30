/** mbed nach Arduino mittels I2C Bus 
    Arduino Sketch siehe Kommentar am Schluss
*/
#include "mbed.h"

// I2C Master
I2C i2c( D14, D15 );

// CMD Buffer (cmd, addr, arg) 
char cmd[4] = { 0x00, 0x00, 0x00, 0x00 };
int slave = 0x10 << 1;

int main()
{
    printf  ( "I2C Master Test\n" );
    
    int status = 0;
    while (1) 
    {
        // write I2C
        for ( int i = 4; i <= 7; i++ ) 
        {
            cmd[0] = 'w';
            cmd[1] = i;
            cmd[2] = 1;
            printf( "write to %d, %d - ", slave, (int) cmd[2] );
            status = i2c.write( slave, cmd, 3 );
            printf("Status %d\n", status );
            wait( 1.0 );

            cmd[0] = 'w';
            cmd[1] = i;
            cmd[2] = 0;
            printf( "write to %d, %d - ", slave, (int) cmd[2] );
            status = i2c.write( slave, cmd, 3 );
            printf("Status %d\n", status );
            wait( 1.0 );
        }
    }
}

/** Arduino Sketch 

#include <Wire.h>

byte buf[2];                         // I/O Buffer
int a3;                              // Poti

// I2C Empfangerfunktion 
void receiveEvent(int howMany)
{
  int cmd = Wire.read();            // Command (ignored)
  int addr = Wire.read();           // Adresse
  int value = Wire.read();          // Wert
  
  digitalWrite( addr, value );
}

// I2C Request i2c.read() abhandeln 
void requestEvent()
{
  buf[0] = a3 / 256;          // hoeherwertiges Byte
  buf[1] = a3 % 256;          // niederwertiges Byte
  Wire.write( buf, 2 );
}

// Initialiserierung 
void setup()
{
  Wire.begin( 0x10 );               // join i2c bus with address #10
  Wire.onReceive( receiveEvent );   // register event
  Wire.onRequest( requestEvent ); 
  
  pinMode( 4, OUTPUT );
  pinMode( 5, OUTPUT );
  pinMode( 6, OUTPUT );
  pinMode( 7, OUTPUT );
  
  pinMode( A3, INPUT );
  
  Serial.begin( 9600 );
  Serial.println( "ready\n" );
}

// Hauptprogramm 
void loop()
{
  a3 = analogRead( A3 );
  Serial.println( a3 );
  delay(1000);

}
*/

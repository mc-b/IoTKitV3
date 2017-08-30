/** Lage Sensor als Fitness Tracker
*/
#include "mbed.h"
#include "FXOS8700Q.h"
#include "OLEDDisplay.h"

// Lage Sensor am Standard I2C Bus
FXOS8700Q_acc acc( D14, D15, FXOS8700CQ_SLAVE_ADDR1 );

// OLED Display
OLEDDisplay oled;

// Anzahl Schritte
long step = 0;
// letzte Z Lage
float last;
// Schwellenwerte (anpassen!)
float _min = -0.2;
float _max = 0.2;

int main(void)
{
    float x, y, z;
    
    // OLED Display
    oled.clear();
    oled.printf( "Fitnessband Demo\r\n" );
    
    acc.enable();
    while (true) 
    {
        acc.getX( &x );     // X Achse
        acc.getY( &y );     // Y Achse
        acc.getZ( &z );     // Z Achse - wird benoetigt um festzustellen ob das Board auf dem Kopf liegt

        wait( 0.2f );
        printf( "X: %1.2f, Y: %1.2f, Z: %1.2f, step: %d\n", x, y, z, step );
        
        oled.cursor( 0, 8 );
        oled.printf( "Anzahl Schritte %d", step );
        
        if  ( (z > _max) && (last < _min) )
            step++;
        
        last = z;        
    }
}

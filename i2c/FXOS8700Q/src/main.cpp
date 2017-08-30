/** Lage Sensor auf FRDM-K64F Board 
*/
#include "mbed.h"
#include "FXOS8700Q.h"

// Lage Sensor am Standard I2C Bus
FXOS8700Q_acc acc( D14, D15, FXOS8700CQ_SLAVE_ADDR1 );

int main(void)
{
    float x, y, z;
    
    acc.enable();
    while (true) 
    {
        acc.getX( &x );     // X Achse
        acc.getY( &y );     // Y Achse
        acc.getZ( &z );     // Z Achse - wird benoetigt um festzustellen ob das Board auf dem Kopf liegt

        printf( "Achse x=%3.2f, y=%3.2f, z=%3.2f\n", x, y, z );

        wait(1.5);
    }
}
/**
 * Infrarot Abstand- und Licht-Sensor
 *
 * Abstand-Sensor geht offiziell bis 100 mm
 */

#include "mbed.h"
#include <VL6180x.h>
#include "OLEDDisplay.h"

// UI
OLEDDisplay oled( PTE26, PTE0, PTE1);

#define VL6180X_ADDRESS 0x52

VL6180xIdentification identification;
// mbed uses 8bit addresses shift address by 1 bit left
VL6180x sensor( PTE0, PTE1, VL6180X_ADDRESS);
// enable, verhindert Init Fehler
DigitalOut sensor_ce( PTE3 );

void printIdentification(struct VL6180xIdentification *temp)
{
    printf("Model ID = ");
    printf("%d\n",temp->idModel);

    printf("Model Rev = ");
    printf("%d",temp->idModelRevMajor);
    printf(".");
    printf("%d\n",temp->idModelRevMinor);

    printf("Module Rev = ");
    printf("%d",temp->idModuleRevMajor);
    printf(".");
    printf("%d\n",temp->idModuleRevMinor);

    printf("Manufacture Date = ");
    printf("%d",((temp->idDate >> 3) & 0x001F));
    printf("/");
    printf("%d",((temp->idDate >> 8) & 0x000F));
    printf("/1");
    printf("%d\n",((temp->idDate >> 12) & 0x000F));
    printf(" Phase: ");
    printf("%d\n",(temp->idDate & 0x0007));

    printf("Manufacture Time (s)= ");
    printf("%d\n",(temp->idTime * 2));
    printf("\n\n");
}
int main()
{
    oled.clear();
    oled.printf( "FlightSense\n" );

    sensor_ce = 1;
    sensor.getIdentification(&identification); // Retrieve manufacture info from device memory
    printIdentification(&identification); // Helper function to print all the Module information

    if(sensor.VL6180xInit() != 0) {
        printf("FAILED TO INITALIZE\n"); //Initialize device and check for errors
    };
    sensor.VL6180xDefautSettings(); //Load default settings to get started.

    wait_ms(1000); // delay 1s

    while(1)
    {
        //Get Ambient Light level and report in LUX
        printf("Ambient Light Level (Lux) = %f\n",sensor.getAmbientLight(GAIN_1) );

        //Get Distance and report in mm
        printf("Distance measured (mm) = %d\n", sensor.getDistance() );

        wait( 0.5f );

        oled.cursor( 1, 0 );
        oled.printf( "Lux: %3.2f\nmm : %5d\n", sensor.getAmbientLight(GAIN_1), sensor.getDistance() );

        wait( 0.5f );
    }
}

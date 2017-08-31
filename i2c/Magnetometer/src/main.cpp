/** Magnetometer auswerten
*/
#include "mbed.h"
#include "OLEDDisplay.h"

// Sensors drivers present in the BSP library
#include <Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01_magneto.h>

OLEDDisplay oled;
DigitalOut led(LED1);

int main()
{
    int16_t pDataXYZ[3] = {0};

    BSP_MAGNETO_Init();
    oled.clear();
        
    while(1) 
    {
        led = 1;

        BSP_MAGNETO_GetXYZ(pDataXYZ);
        printf("\nMAGNETO_X = %d\n", pDataXYZ[0]);
        printf("MAGNETO_Y = %d\n", pDataXYZ[1]);
        printf("MAGNETO_Z = %d\n", pDataXYZ[2]);
        
        oled.cursor( 0, 0 );  
        oled.printf("Magnetometer\n");
        oled.printf("X = %d\n", pDataXYZ[0]);
        oled.printf("Y = %d\n", pDataXYZ[1]);
        oled.printf("Z = %d\n", pDataXYZ[2]);                
        
        led = 0;
        wait(1);
    }
}

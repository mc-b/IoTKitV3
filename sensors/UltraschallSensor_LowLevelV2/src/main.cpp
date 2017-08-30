#include "mbed.h"
#include "OLEDDisplay.h" 
 
DigitalIn echo( A4 );
DigitalOut trigger( A5 );
Timer t;
OLEDDisplay oled;
 
float i;
 
int main() 
{
    t.start();
    printf(" ===[ Ultrasonic Range ]===");
 
    // OLED Display
    oled.clear();
 
    while (1) 
    {
        oled.clear();
        oled.printf( "Ultrasonic Range" );

        // send pulse
        trigger=1;
        wait(0.000004);
        trigger=0;
 
        // wait for the echo line to go high
        while (!echo);
 
        // measure the length of the pulse
        t.reset();
        while (echo);
        i = t.read_us();
 
        // display result
        printf("\n\n\rPulselength %6.0f uS",i);
        oled.printf("\n\rPulselength %6.0f uS",i);
        i=i/58;
        printf("\n\n\rDistance %4.0f cm",i);
        oled.printf("\rDistance %4.0f cm",i);
        wait(2);
    }
}
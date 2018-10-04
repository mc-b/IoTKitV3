/** Servo am Digital Pin D3.
    Das orange Kabel (Signal) ist links.
*/

#include "mbed.h"

//Program to 'sweep' test a 'standard RC type servo
//Define some parameters using compiler directive '#define'
//Check Servo DATA if 0.75ms to 2.25ms then use min=750 and max=2250
//NB be values in microseconds (Following are generic values)

#define MID         1500
#define MIN          750
#define MAX         2250
#define STEP          25
//Time delay between steps in milliseconds
#define TIME         100

PwmOut myServo( D9 );

int main() {
    
    myServo.period_ms(20);
    myServo.pulsewidth_us(MID); //NB in microseconds

    while(true)
    {
        for (int i=MIN;i<=MAX;i+=STEP)
        {
            myServo.pulsewidth_us(i);
            wait_ms(TIME);
        }
        for (int i=MAX;i>=MIN;i-=STEP)
        {
            myServo.pulsewidth_us(i);
            wait_ms(TIME);
        }
    }
}                                       
  

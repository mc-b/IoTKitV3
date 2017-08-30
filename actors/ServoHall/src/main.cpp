/** Servo am Digital Pin D9 in Kombination mit Hall Sensor.
    Wenn der Hall Sensor anspricht, stoppt der Servo.
    Das orange Kabel (Signal) ist links.
*/
#include "mbed.h"
#include "Servo.h"

Servo servo( D9 );
AnalogIn hallSensor( A2 );
DigitalOut led1( D10 );
DigitalOut led2( D11 );

int main()
{
    float start = 0.0f;
    float value = 0.0f; 
   
    while   ( 1 ) 
    {
        led1 = led2 = 0;
        
        // Servo langsam bewegen (immer in der Mitte Anfangen mit Tests, sonst besteht die Gefahr von Schäden)
        for ( float p = 0.0f; p < 1.0f; p += 0.0001f )
        {
            servo = p;
            value = hallSensor.read();
            // Hall Sensor ausgeloest?
            if  ( value < 0.4f || value > 0.6f )
            {
                p -= 0.01f;
                start = p;          // aktuelle Position = Startposition
                break;
            }
            wait(0.001);
        }
        // wenn Hall Sensor ausgeloest dann LED anschalten, ansonsten Position auf Anfang
        if  ( value < 0.4f )
            led1 = 1;
        else if ( value > 0.6f )
            led2 = 1;  
        else
            start = 1.0f;
            
        wait( 1.0 );  
        led1 = led2 = 0;
        
        // und die andere Seite       
        for ( float p = start; p >= 0.0f; p -= 0.0001f )
        {
            servo = p;
            wait(0.001);
        }
        wait( 0.5 );            
    }
}                                       
  
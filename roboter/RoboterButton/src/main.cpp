/** IoTKit Roboter mittels Button gesteuert
*/

#include "mbed.h"
#include "ServoRobot.h"

// Servos
ServoRobot foot( D6, 0.25f, 0.75f);
ServoRobot base( D7, 0.275f, 0.65f );
ServoRobot arm( D9, 0.275f, 0.6f );
ServoRobot pincer( D10, 0.04f, 0.3f );

DigitalIn buttonFoot( A0 );
DigitalIn buttonBase( A1 );
DigitalIn buttonPincer( A2 );

/** Hauptprogramm */
int main()
{
    // Arme auf und Anfangsposition
    base.moveMax();
    arm.moveMin();      
    pincer.moveMax();      
    foot.moveMax();
    
    // Button Abhandlung
    while   ( 1 )
    {
        // Fuss
        if  ( buttonFoot == 0 )
        {
            if  ( foot.getMin() == foot )
                foot.moveMax();
            else
                foot.moveMin();
        }       
        // Roboter Arm (unten) 
        if  ( buttonBase == 0 )
        {
            if  ( base.getMin() == base )
                base.moveMax();
            else
                base.moveMin();
        } 
        // Klemme
        if  ( buttonPincer == 0 )
        {
            if  ( pincer.getMin() == pincer )
                pincer.moveMax();
            else
                pincer.moveMin();
        }          
        wait( 0.2f );
    }
}
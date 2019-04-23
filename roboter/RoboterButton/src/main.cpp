/** IoTKit Roboter mittels Button gesteuert - braucht ein Steckplatine mit 3 Tastern
*/

#include "mbed.h"
#include "ServoRobot.h"

// Servos
ServoRobot foot( MBED_CONF_IOTKIT_SERVO1, 0.25f, 0.75f);
ServoRobot base( MBED_CONF_IOTKIT_SERVO2, 0.275f, 0.65f );
ServoRobot arm( MBED_CONF_IOTKIT_SERVO3, 0.275f, 0.6f );
ServoRobot pincer( MBED_CONF_IOTKIT_SERVO4, 0.04f, 0.3f );

DigitalIn buttonFoot( MBED_CONF_IOTKIT_BUTTON1 );
DigitalIn buttonBase( MBED_CONF_IOTKIT_BUTTON2 );
DigitalIn buttonPincer( MBED_CONF_IOTKIT_BUTTON3 );

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

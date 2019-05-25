/* ServoRobot - Erweiterte Servo Library
 * Copyright (c) 2016 Marcel mc-b Bernet
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
#include "mbed.h"
#include "Servo.h"
 
#ifndef SERVO_ROBOT
#define SERVO_ROBOT

/** ServoRobot - fuer einen Roboter optimierte Servo Library
 *
 *  @code
    ServoRobot arm( D9, 0.35f, 0.6f );
    arm.moveMax();   
    @endcode
*/
 
class ServoRobot : public Servo
{
public:
    ServoRobot( PinName pin, float min = 0.25f, float max = 0.75f, float step = 0.000025f, float range = 0.0009, float degrees = 90.0 ) : Servo( pin ), 
                min(min), max(max), step(step)
    {
    }
    
    /** Roboterarm von aktueller Position nach end bewegen */
    void move( float end )
    {
        float start = read();
        if  ( start < end )
        {
            for ( float i = start; i < end; i += step )
            {
                write( i );
                wait    ( 0.00005f );
            }
        }
        else
        {
            for ( float i = start; i > end; i -= step )
            {
                write( i );
                wait    ( 0.00005f );
            }        
        }        
    }
    
    /** Roboterarm von aktueller Position nach Min bewegen */
    void moveMin()
    {
        move( min );
        write( min );
    }
    
    /** Roboterarm von aktueller Position nach Max bewegen */
    void moveMax()
    {
        move( max );
        write( max );
    } 
    
    float getMin()   
    {
        return  ( min );
    }
    
    float getMax()
    {
        return  ( max );
    }

private:
    float min;
    float max;
    float step;
};

#endif // ServoRobot

/* IoTKit OLED Display Library
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
#include <stdarg.h>
#include "Adafruit_SSD1306.h"

#ifndef OLED_DISPLAY
#define OLED_DISPLAY

/** OLED Display 
 *
 * Vereinfachte Version zur Ansteuerung eines Displays
 * auf Basis von I2C und SSD1306 Interface
 *
 * Example:
 * @code
 * #include "mbed.h"
 * #include "OLEDDisplay.h"
 * 
 * DigitalOut led( D10 );
 * OLEDDisplay oled;
 * 
 * int main()
 * {
 *     int i = 0;
 *     oled.clear();
 *     oled.printf( "Test\r\n" );
 *     
 *     while (true) 
 *     {
 *         oled.cursor( 1, 0 );
 *         oled.printf( "ON %d, %d\n", led.read(), i );
 *         led = 1;
 *         wait( 1.0f ); 
 *         
 *         oled.cursor( 2, 0 );
 *         oled.printf( "OFF %d, %d\n", led.read(), i );
 *         led = 0;
 *         i++;
 *         wait( 1.0f );
 *     }
 * }
 * @endcode
 */

class OLEDDisplay
{
public:
    OLEDDisplay( PinName rst = D9, PinName sca = D14, PinName scl = D15, uint8_t addr = 0x78 ) : i2c( sca, scl ), oled( i2c, rst, addr )
    {
    }
    
    /** clear Display */
    void clear()
    {
        oled.clearDisplay();
        oled.setTextCursor( 0, 0 );                
    }
    /** Set the display rotation, 1 = down, 2 = up, 3 = left, or 4 = right*/
    void setRotation(uint8_t r)
    {
        oled.setRotation( r );
    }
    
    /** printf formatted with display */
    void printf( const char *format, ... )
    {
        static char buffer[128];
        
        va_list args;
        va_start(args, format);
        vsprintf(buffer, format, args);
        va_end(args);
        
        oled.printf( buffer );
        oled.display();
    }

    /// Set the text cursor location, based on the size of the text
    void cursor( int16_t y, int16_t x ) 
    { 
        oled.setTextCursor( x * 6 , y * 8 ); 
    }

    
private:
        I2C i2c;
        Adafruit_SSD1306_I2c oled;
};

#endif // OLED_DISPLAY
/* Cooker Library
 * Copyright (c) 2016 Marcel (mc-b) Bernet
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
#ifndef COOKER_H
#define COOKER_H

#include "FunctionPointer.h"
#include "TMP175.h"

// Systemregister Dot LED Matrix
#define reg_decodeMode   0x09
#define reg_intensity    0x0a
#define reg_scanLimit    0x0b
#define reg_shutdown     0x0c

/** 
 * Herdplatte (simuliert mittels DOT LED Matrix 
 */
class Cooker
{
private:
    SPI spi;
    DigitalOut dss;     // Steuerpin!!!
    long activation;          // Startzeit
    long timer;          // Zeit zum Starten
    long cook;           // Kochzeit
    int warm;           // Warmhalten
    FunctionPointer finishCall;  /**< Callback. */
    TMP175 temp;        // Temperatursensor
    AnalogIn poti;      // Schwellenwert ueberkochen
    
    /** Schreibe 1 Byte in Register
     * @param r = Register
     * @param v = Wert
     */
    void writeToReg( int r, int v )
    {
        dss.write( 0 );
        spi.write( r );
        spi.write( v );
        dss.write( 1 );
    } 

public:
    Cooker( PinName mo = D11, PinName mi = D12, PinName sck = D13, PinName ss = D10 ) : spi( mo, mi, sck ), dss( ss ), temp( D14, D15 ), poti( A0 ) {}

    /** Initialisierung der SPI Schnittstelle und der DOT LED Matrix */
    void init()
    {
        // Initialisierung Herdplatte
        spi.format( 8,0 );
        spi.frequency( 1000000 );
        
        writeToReg( reg_decodeMode, 0x00 );
        writeToReg( reg_intensity, 0x0f );
        writeToReg( reg_scanLimit, 0x07 );
        writeToReg( reg_shutdown, 0x01 );
        writeToReg( 0xff, 0x00 );  
        
        // Defaultwerte = OFF
        activation = -1;
        timer = -1;
        cook = -1;
        warm = false;
        
        // Temperatursensor initialisieren
        temp.vSetConfigurationTMP175( SHUTDOWN_MODE_OFF | COMPARATOR_MODE | POLARITY_0 |FAULT_QUEUE_6 | RESOLUTION_12, 0x48 );
        temp.vSetTemperatureLowTMP175( 0.0 );
        temp.vSetTemperatureHighTMP175( 60.0 );        
    }
    
    void setTimer( long t )
    {
        timer = t;
    }
    
    void setCookTime( long t )
    {
        cook =  t;
    }
    
    void setKeepWarm( int w )
    {
        warm = w;
        if  ( warm == 0 && activation <= 0 )
            off();
    }
    
    void start()
    {
        activation = (clock() / CLOCKS_PER_SEC);
    }
    
    /** Kochen */
    void full()
    {   
        if  ( temp.fReadTemperatureTMP175() < (poti.read() * 50) )    
        {
            for ( int r = 1; r <= 8; r++ )
                writeToReg( r, 255 );  
        }
        // Zurueckschalten um Ueberkochen zu verhindern
        else
        {
            writeToReg( 1, 0 );  
            for ( int r = 2; r <= 7; r++ )
                writeToReg( r, 126 );  
            writeToReg( 8, 0 );  
        }
    }

    /** Warmhalten */
    void keepWarm()
    {
        writeToReg( 1, 0 );        
        writeToReg( 2, 0 );        
        for ( int r = 3; r <= 6; r++ )
            writeToReg( r, 24 );  
        writeToReg( 7, 0 );        
        writeToReg( 8, 0 );             
    }

    /** Kocher off */
    void off()
    {
        for ( int r = 1; r <= 8; r++ )
            writeToReg( r, 0 ); 
    }    

    /** Kochen */
    int run()
    {
        // Timer oder Kochzeit aktiv
        if   ( activation > 0 )
        {
            printf( "temp %f, %f\n", temp.fReadTemperatureTMP175(), (poti.read() * 50) );

            long now = clock() / CLOCKS_PER_SEC;
            // Kocher starten in x Sekunden
            if  ( timer > 0 )
            {
                if  ( now < (activation + timer)  )
                    return ( true );
                timer = -1;
                activation = now;
            }
            // Kochen
            if  ( cook > 0 )
            {
                // wir kochen
                if  ( now < (activation + cook) )
                {
                    full();
                    return ( true );
                }
                activation = -1; 
                cook = -1;
                finishCall.call();
            }
            // weder Timer noch Kocher aktiv
            if  ( warm )
                keepWarm();
            else
                off();
        }
        return  ( false );
    }
    
    /** Methode welche optional aufgerufen werden kann beim Ende des Kochvorganges */
    void attachFinish( void (*fptr)(void) )
    {
        finishCall.attach( fptr );
    }    
};

#endif

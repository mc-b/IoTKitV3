/* RemoteCooker Library
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
 
#ifndef REMOTE_COOKER_H
#define REMOTE_COOKER_H

#include "Cooker.h"

// Menues
enum Menues { OFF, Wasser, Reis, Kartoffeln, Spaghetti, Gemuese, Spiegelei, Ei, Steak, Schnitzel, Soucen };
// Kochzeiten
int menuTable[10][2] = 
{
    { Wasser, 6 },
    { Reis, 20 },
    { Kartoffeln, 28 },
    { Spaghetti, 20 },
    { Gemuese, 12 },
    { Spiegelei, 5 },
    { Ei, 10 },
    { Steak, 15 },
    { Schnitzel, 15 },
    { Soucen, 8 }
};

class RemoteCooker
{
private:
    Cooker cooker;
    Ticker run;
    
    /** Kocher ueberwachen und kochen */
    void updateCooker()
    {
        cooker.run();
    }
    
public:
    /** Default Konstruktor + Initialisierung */
    RemoteCooker(PinName mo = D11, PinName mi = D12, PinName sck = D13, PinName ss = D9 ) : cooker( mo, mi, sck, ss ) 
    {
        cooker.init();
        cooker.full();
        wait( 1.0f );
        cooker.off(); 
        // Kocher Ueberwachung und kochen - siehe menu()
        //run.attach( this, &RpcCooker::updateCooker, 1.0 );       
    }

    /** Evtl. Timer (Start in x Sekunden setzen */
    void timer( int t )
    {
        // Kocker aktiv - Aenderungen Menu und Timer ignorieren
        if  ( cooker.run() )
            return;
            
        cooker.setTimer( t );  
        printf("Timer %d\n", t );              
    }    

    /** Menu bzw. Kochzeiten setzen */
    void menu( int m ) 
    { 
        // Kocker aktiv - Aenderungen Menu und Timer ignorieren
        if  ( cooker.run() )
            return;
            
        // Kochdauer anhand Menukarte setzen
        for ( int i = 0; i < 10; i++ )
            if  ( menuTable[i][0] == m )
            {
                cooker.setCookTime( menuTable[i] [1] );
                cooker.start();
                printf( "Start: Menu %d, Kochdauer %d\n", m,  menuTable[i] [1] );
                // HACK: besser waere es Ticker zu verwenden, dann gibt aber http.get nicht
                while   ( cooker.run() )
                    wait( 1.0f );
                printf( "Ende: Menu %d, Kochdauer %d\n", m,  menuTable[i] [1] );
                break;
            }
    }
    
    /** Gericht warmhalten (nach dem Kochen) */
    void keepwarm( int kw )
    {
        // Warmhaltefunktion kann immmer gesetzt werden
        cooker.setKeepWarm( kw );   
        printf( "KeepWarm %d\n", kw );     
    }
    
    /** Methode welche optional aufgerufen werden kann beim Ende des Kochvorganges */
    void attachFinish( void (*fptr)(void) )
    {
        cooker.attachFinish( fptr );
    }  
};

#endif // REMOTE_COOKER_H
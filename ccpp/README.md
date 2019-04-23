Kleine C/C++ Einführung
----------------------------
***

> [⇧ **Home**](../README.md)

### Inhaltsverzeichnis

* [Objektorientierung](#objektorientierung)
* [Programmbibliotheken (Libraries))](#programmbibliotheken)
* [Variablen](#variablen)
* [Operatoren](#operatoren)
* [Programmablauf](#programmablauf)
* [Prozeduren und Funktionen](#prozeduren-und-funktionen)
* [Programmaufbau](#programmaufbau)

**Online Bücher / Tutorials zu C / C++** 

*   [C++ Programmierung](http://de.wikibooks.org/wiki/C%2B%2B-Programmierung) (WikiBooks)
*   [C++ Tutorial](http://www.cplusplus.com/doc/tutorial/) (english)

## Objektorientierung
***

> [⇧ **Nach oben**](#inhaltsverzeichnis)

Der objektoriente Ansatz versucht, die den Problemen der Welt zugrundeliegende Komplexität durch **Abstraktion** unseres Wissens und **Kapselung** dieses Wissens in Objekten überschaubar zu machen.

Was ist ein Objekt?

*   Ein Objekt bildet, in der Regel, Dinge der Realen Welt ab, z.B. Auto, Kontaktstift (GPIO Pin), Sensor, Aktor
*   Ein Objekt kapselt Methoden (Verhalten) und Attribute (Daten)
*   Ein Objekt kann andere Objekte beinhalten, z.B. Auto beinhaltet Temperatursensor, Motor etc.
*   Ein Objekt kann mehrfach Instanziert werden, z.B. für GPIO Pin D2, D3, D4 etc.
*   Objekte werden in Klassen definiert
*   Ein oder mehrere Klassen werden in Programmbibliotheken (Libraries) zusammenfasst
*   [Klassen Definitionen](http://de.wikipedia.org/wiki/Deklaration_(Programmierung)) werden in Dateien mit der Endung **.h** abgelegt
*   Klassen Implementierungen werden in Dateien mit der Endung **.cpp** abgelegt.

Beispiele Objekte:

    DigitalOut led1( D10 ); // Instanzieren eines Objektes mit dem Namen led1 anhand der Klasse DigitalOut, als Pin (Daten) wird D10 übergeben.
    DigitalOut led2( D11 ); // Gleiche Klasse (DigitalOut), neues Objekt, neuer Name (led2) und andere Daten (D11)
    led1.write( 1 );        // Aufruf der Methode write mit Wert 1, welches die LED zum Leuchten bringt.
    led2.write( 0 );
    // Kurzform
    led1 = 1;
    led2 = 0;

    AnalogIn light( A0 );   // Instanzieren eines Objektes mit dem Namen light anhand der Klasse AnalogIn, als Pin (Daten) wird A0 übergeben
    light.read();           // Auslesen des aktuellen Analogen Wertes an Pin A0, mittels der Methode read()

    Motor motor1( D3, D2, D4 ); // Instanzieren Motor Objekt
    motor1.speed( 0.5 );        // Setzen der Geschwindigkeit des Motors
    
## Programmbibliotheken
***

> [⇧ **Nach oben**](#inhaltsverzeichnis)

Ein oder mehrere Klassen werden in Programmbibliotheken (Libraries) zusammenfasst.

Programmbibliotheken (Libraries) werden, von der mbed Plattform (IDE, Compiler), in Repositories gespeichert.

Beispiel Klassen und Programmbibliotheken (Libraries)

![](../images/ObjectLibrary.png) 

* [mbed-os](https://github.com/ARMmbed/mbed-os/) ist eine Programmbibliothek (Library) welche die Grundklassen der mbed Plattform beinhaltet
* [IoTKit](https://os.mbed.com/teams/IoTKitV3/code/IoTKit/) ist die Programbibliothek des IoTKits mit u.a. Definition der [IoTKits-Pins](https://os.mbed.com/teams/IoTKitV3/code/IoTKit/file/4bf5081be024/mbed_lib.json/).
* [AnalogIn](https://os.mbed.com/docs/mbed-os/latest/apis/analogin.html), [DigitalOut](https://os.mbed.com/docs/mbed-os/latest/apis/digitalout.html) etc. sind Klassen.

Weitere Beispiele siehe [mbed Komponenten Verzeichnis](http://developer.mbed.org/components/)

## Variablen
***

> [⇧ **Nach oben**](#inhaltsverzeichnis)

*   Variablen dienen zum Zwischenspeichern von Ganz-, Gleitkommazahlen oder Zeichen.
*   Variablen haben einen Namen
*   Der durch eine Variable repräsentierte Wert kann zur Laufzeit des Programmes verändert werden.
*   Mehrere Variablen desselben Typs können zu einem Array (im Deutschen bisweilen auch Datenfeld oder Vektor genannt) zusammenfasst werden.
*   Zusätzlich kennt C struct, welches verschiedene Komponenten zu Strukturen (Records) zusammenfasst. Der Zugriff auf die Felder erfolgt mittels ".", Beispiel myStruct.data.

### Beispiele Variablen

    int i;              // Definition Ganzzahl ohne Initialwert
    int x = 4;          // Definition Ganzzahl mit Initialwert 4
    float v = 4.1f;     // Definition Gleitkommazahlen mit Initialwert 4.1

### Beispiele Array 

    int feld[10];                                       // Anlegen ohne Initialisierung
    int feld[]   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };   // Mit Initialisierung (automatisch 10 Elemente)
    int feld[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };   // Fehleranfällig, weil der Compiler ein 11tes Element nicht als Fehler erkennt                    
    char host[]  = "mbed-myboard";                      // Zeichenkette es wird automatisch ein &#039;\0&#039; als Abschluss angefügt

### Beispiel struct 

    struct
    {
        int pin;
        char data[4];
        float servo;
    } myStruct;

#### Ganzzahlen

| **Typ** | **Speicherplatz** | **Wertebereich (dezimal)** |
| --- | --- | --- |
| char | 1 Byte | -128 bis +127 bzw. 0 bis 255 |
| signed char | 1 Byte | -128 bis +127 |
| unsigned char | 1 Byte | 0 bis 255 |
| short | 2 Byte | -32768 bis +32767 |
| unsigned short | 2 Byte | 0 bis 65535 |
| int | 4 Byte | -2147483648 bis +2147483647 |
| unsigned int | 4 Byte | 0 bis 4294967295 |
| long | 4 Byte | -2147483648 bis +2147483647 |
| unsigned long | 4 Byte | 0 bis 4294967295 |

#### Gleitkommazahlen 

| Typ | Speicherplatz | Wertebereich | kleinste positive Zahl | Genauigkeit |
| --- | --- | --- | --- | --- |
| float | 4 Byte | ![\pm3,4 \cdot 10^{38}](http://upload.wikimedia.org/math/f/2/2/f22878e81ba7a1664130b682e0e638a1.png) | ![1,2 \cdot 10^{-38}](http://upload.wikimedia.org/math/4/b/f/4bf9db5e2192b1cb5d66608e53fe8148.png) | 6 Stellen |
| double | 8 Byte | ![\pm1,7 \cdot 10^{308}](http://upload.wikimedia.org/math/5/b/7/5b74eae05be4a33d1a06c0174573ead2.png) | ![2,3 \cdot 10^{-308}](http://upload.wikimedia.org/math/2/1/7/2175075f3bb3195f8bcd38c94b57e977.png) | 12 Stellen |
| long double | 10 Byte | ![\pm1,1 \cdot 10^{4932}](http://upload.wikimedia.org/math/4/d/5/4d573ec2a7218446baf2e1755df98c73.png) | ![3,4 \cdot 10^{-4932}](http://upload.wikimedia.org/math/5/8/7/587c6c95f3fd15779bea0f43dbc12767.png) | 18 Stellen |

[Weitere Informationen](http://de.wikibooks.org/wiki/C%2B%2B-Programmierung/_Einf%C3%BChrung_in_C%2B%2B/_Variablen,_Konstanten_und_ihre_Datentypen)

## Operatoren
***

> [⇧ **Nach oben**](#inhaltsverzeichnis)

*   Es gibt zwei Arten von Operatoren: Mathematische und Logische
*   Das Ergebnis eines Mathematischen Operators ist immer eine Zahl
*   Das Ergebnis eines Logischen Operators ist "wahr" oder "unwahr"
*   Logische Operatoren kommen bei Bedingungen zum Einsatz (siehe Programmfluss)

### Beispiel Mathematische Operatoren 

    i = i + 1;  // Addition
    i = i - 1;  // Subtraktion
    i = i * 4;  // Multiplikation
    i = i / 4;  // Division
    i = i % 4;  // Rest aus Division
    // Kurzform
    i += 1;
    i -= 1;
    i *= 4;
    i /= 4;
    i %= 4;
    // noch Kürzer
    i++;
    i--;

### Beispiel Logische Operatoren 

    2 >  1              // 2 grösser als 1 = wahr  
    2 >= 1              // 2 grösser oder gleich 1 = wahr  
    2 <  1              // 2 kleiner als 1 = unwahr
    2 
    
## Programmablauf
***

> [⇧ **Nach oben**](#inhaltsverzeichnis)

Der Ablauf eines Programmes kann durch Verzweigungen, Schleifen und Auswahlen gesteuert werden.

### [Verzweigungen](http://de.wikibooks.org/wiki/C%2B%2B-Programmierung/_Einf%C3%BChrung_in_C%2B%2B/_Verzweigungen)

*   **if** ( _Bedingung_ ) _Anweisung;_ // Wenn Bedingung (Logischer Operator) zutrifft Anweisung ausführen
*   **if** ( _Bedingung_ ) **{** _Anweisung;_ _Anweisung;_ **}** // Wenn Bedingung mehrere Anweisungen ausführen
*   **if** ( _Bedingung_ ) _Anweisung 1;_ **else** _Anweisung 2;_ // Wenn Zutrifft Anweisung 1 sonst 2 ausführen.

```cpp
    if  ( i > 2 )
        printf( "i ist grösser 2" );
    if  ( i < 2 )
        printf( "i ist kleiner 2" );
    else
        printf( "i ist grösser oder gleich 2" );
```        

### [Schleifen](http://de.wikibooks.org/wiki/C%2B%2B-Programmierung/_Einf%C3%BChrung_in_C%2B%2B/_Schleifen) 

*   **while** ( _Bedingung_ ) _Anweisung;_ // Solange Bedingung zutrifft Anweisung ausführen
*   **while** ( _Bedingung_ ) **{** _Anweisung;_ _Anweisung;_ **}** // Solange Bedingung zutrifft Anweisungen ausführen
*   **for** ( _Start_;_Bedingung_;_Aktion_ ) _Anweisung 1;_ // Start Zuweisung, Bedingung prüfen, wenn wahr Anweisung und Aktion ausführen

```cpp
    while   ( 1 )   // Endlosloop
        printf( "trifft zu" );
    int i = 0;
    while   ( i < 10 )
        i++;
    for ( int i = 0; i < 10; i++ )
        printf( "i = %d\n", i );
```        

### [Auswahl](http://de.wikibooks.org/wiki/C%2B%2B-Programmierung/_Einf%C3%BChrung_in_C%2B%2B/_Auswahl) 

*   **switch** ( _Ganzzahlige Variable_ ) **case** _Ganzzahl_:_Anweisung;_**break;****default:**_Anweisung;_

```cpp
    int i = 1;
    switch  ( i )
    {
        case 1:
            printf( "i = 1\n" );
            break;
        case 2:
            printf( "i = 2\n" );
            break;
        default:
            printf( "i ist weder 1 noch 2\n" );
    }
```

## Prozeduren und Funktionen
***

> [⇧ **Nach oben**](#inhaltsverzeichnis)

Unter einer Funktion (function, in anderen Programmiersprachen auch Prozedur oder Subroutine genannt) versteht man ein Unterprogramm, das eine bestimmte Aufgabe erfüllt. Funktionen sind unter anderem sinnvoll, um sich oft wiederholende Befehle zu kapseln, so dass diese nicht jedes mal neu geschrieben werden müssen. Zudem verbessert es die Übersichtlichkeit des Sourcecodes erheblich, wenn der Programmtext logisch in Abschnitte bzw. Funktionen unterteilt wird.

*   Eine Funktion kann Parameter besitzen, oder nicht.
*   Eine Funktion kann einen Wert zurückgeben, oder nicht.

### Beispiele 

    int f( int x )    // Funktion
    {    
        return ( x * x );
    }  

    int a = f(5);   // Aufruf einer Funktion                  

[Weitere Informationen](http://de.wikibooks.org/wiki/C%2B%2B-Programmierung/_Weitere_Grundelemente/_Prozeduren_und_Funktionen)    

## Programmaufbau
***

> [⇧ **Nach oben**](#inhaltsverzeichnis)

Folgender Aufbau hat sich für embedded Systeme bewährt

    // Import Libraries
    // Definition der verwendeten Objekte.
    // Funktionen welche von Hauptprogramm aufgerufen werden.
    
    int main() // Hauptprogramm 
    {
        // Initialisierungen von Variablen und Feintuning von Objekten. 
        
        while ( 1 ) 
        { 
            // Anweisungen welche Endlos durchgeführt werden
        }
    }


### Beispiel

    // Import mbed Library
    #include "mbed.h"       
    
    // Definition der verwendeten Objekte 
    DigitalOut led(LED_RED);
    
    /** Hauptprogramm */
    int main()
    {
        while ( 1 ) 
        {
            led = !led;     // LED Wert umkehren (0 oder 1)
            wait ( 0.2f );  // warte 0.2 Sekunden
        }
    }

Das Hauptprogramm wird, in der Regel, in der **main.cpp** Datei gespeichert

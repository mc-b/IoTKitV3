## Programmablauf

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
    
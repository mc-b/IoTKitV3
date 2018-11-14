## Variablen

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